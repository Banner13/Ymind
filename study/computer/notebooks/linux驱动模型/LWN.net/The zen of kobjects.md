The "kobject" structure first made its appearance in the 2.5.45 development kernel. It was initially meant as a simple way of unifying kernel code which manages reference counted objects. The kobject has since encountered a bit of "mission creep," however; it is now the glue that holds much of the device model and its sysfs interface together. It is rare for a driver writer to have to work with kobjects directly; they are usually hidden in structures created by higher-level code. Kobjects have a certain tendency to leak through the intervening layers, however, and make their presence known. So a familiarity with what they are and how they work is a good thing to have. This document will cover the kobject type and related topics, but will gloss over most of the interactions between kobjects and sysfs (those will be covered separately, later on).

Part of the difficulty in understanding the driver model - and the kobject abstraction upon which it is built - is that there is no obvious starting place. Dealing with kobjects requires understanding a few different types, all of which make reference to each other. In an attempt to make things easier, we'll take a multi-pass approach, starting with vague terms and adding detail as we go. To that end, here are some quick definitions of some terms we will be working with.

- A **kobject** is an object of type struct kobject. Kobjects have a name and a reference count. A kobject also has a parent pointer (allowing kobjects to be arranged into hierarchies), a specific type, and, perhaps, a representation in the sysfs virtual filesystem.
    
    Kobjects are generally not interesting on their own; instead, they are usually embedded within some other structure which contains the stuff the code is really interested in.
    
- A **ktype** is a type associated with a kobject. The ktype controls what happens when a kobject is no longer referenced and the kobject's default representation in sysfs.
    
- A **kset** is a group of kobjects all of which are embedded in structures of the same type. The kset is the basic container type for collections of kobjects. Ksets contain their own kobjects, for what it's worth. Among other things, that means that a kobject's parent is usually the kset that contains it, though things do not normally have to be that way.
    
    When you see a sysfs directory full of entries, generally each of those entries corresponds to a kobject in the same kset.
    
- A **subsystem** is a collection of ksets which, collectively, make up a major sub-part of the kernel. Subsystems normally correspond to the top-level directories in sysfs.

We'll look at how to create and manipulate all of these types. A bottom-up approach will be taken, so we'll go back to kobjects.

### Embedding kobjects

It is rare (even unknown) for kernel code to create a standalone kobject; instead, kobjects are used to control access to a larger, domain-specific object. To this end, kobjects will be found embedded in other structures. If you are used to thinking of things in object-oriented terms, kobjects can be seen as a top-level, abstract class from which other classes are derived. A kobject implements a set of capabilities which are not particularly useful by themselves, but which are nice to have in other objects. The C language does not allow for the direct expression of inheritance, so other techniques - such as structure embedding - must be used.

So, for example, the 2.6.0-test6 version of struct cdev, the structure describing a char device, is:

    struct cdev {
	    struct kobject kobj;
		struct module *owner;
		struct file_operations *ops;
		struct list_head list;
    };

If you have a struct cdev structure, finding its embedded kobject is just a matter of using the kobj pointer. Code that works with kobjects will often have the opposite problem, however: given a struct kobject pointer, what is the pointer to the containing structure? You should avoid tricks (such as assuming that the kobject is at the beginning of the structure) and, instead, use the container_of() macro, found in <linux/kernel.h>:

	container_of(pointer, type, member)

where pointer is the pointer to the embedded kobject, type is the type of the containing structure, and member is the name of the structure field to which pointer points. The return value from container_of() is a pointer to the given type. So, for example, a pointer to a struct kobject embedded within a struct cdev called "kp" could be converted to a pointer to the containing structure with:

    struct cdev *device = container_of(kp, struct cdev, kobj);

Programmers will often define a simple macro for "back-casting" kobject pointers to the containing type.

### Initialization of kobjects

Code which creates a kobject must, of course, initialize that object. Some of the internal fields are setup with a (mandatory) call to kobject_init():

    void kobject_init(struct kobject *kobj);

Among other things, kobject_init() sets the kobject's reference count to one. Calling kobject_init() is not sufficient, however. Kobject users must, at a minimum, set the name of the kobject; this is the name that will be used in sysfs entries. If you dig through the kernel source, you will find code which copies a string directly into the kobject's name field, but that approach should be avoided. Instead, use:

    int kobject_set_name(struct kobject *kobj, const char *format, ...);

This function takes a printk-style variable argument list. Believe it or not, it is actually possible for this operation to fail; conscientious code should check the return value and react accordingly.

The other kobject fields which should be set, directly or indirectly, by the creator are its ktype, kset, and parent. We will get to those shortly.

### Reference counts

One of the key functions of a kobject is to serve as a reference counter for the object in which it is embedded. As long as references to the object exist, the object (and the code which supports it) must continue to exist. The low-level functions for manipulating a kobject's reference counts are:

    struct kobject *kobject_get(struct kobject *kobj);
    void kobject_put(struct kobject *kobj);

A successful call to kobject_get() will increment the kobject's reference counter and return the pointer to the kobject. If, however, the kobject is already in the process of being destroyed, the operation will fail and kobject_get() will return NULL. This return value must always be tested, or no end of unpleasant race conditions could result.

When a reference is released, the call to kobject_put() will decrement the reference count and, possibly, free the object. Note that kobject_init() sets the reference count to one, so the code which sets up the kobject will need to do a kobject_put() eventually to release that reference.

Note that, in many cases, the reference count in the kobject itself may not be sufficient to prevent race conditions. The existence of a kobject (and its containing structure) may well, for example, require the continued existence of the module which created that kobject. It would not do to unload that module while the kobject is still being passed around. That is why the cdev structure we saw above contains a struct module pointer. The reference counting for struct cdev is implemented as follows:

    struct kobject *cdev_get(struct cdev *p)
    {
	    struct module *owner = p->owner;
	    struct kobject *kobj;

	    if (owner && !try_module_get(owner))
		    return NULL;
	    kobj = kobject_get(&p->kobj);
	    if (!kobj)
		    module_put(owner);
	    return kobj;
    }

Creating a reference to a cdev structure requires creating a reference also to the module which owns it. So cdev_get() uses try_module_get() to attempt to increment that module's usage count. If that operation succeeds, kobject_get() is used to increment the kobject's reference count as well. That operation could fail, of course, so the code checks the return value from kobject_get() and releases its reference to the module if things don't work out.

### Hooking into sysfs

An initialized kobject will perform reference counting without trouble, but it will not appear in sysfs. To create sysfs entries, kernel code must pass the object to kobject_add():

    int kobject_add(struct kobject *kobj);

As always, this operation can fail. The function:

    void kobject_del(struct kobject *kobj);

will remove the kobject from sysfs.

There is a kobject_register() function, which is really just the combination of the calls to kobject_init() and kobject_add(). Similarly, kobject_unregister() will call kobject_del(), then call kobject_put() to release the initial reference created with kobject_register() (or really kobject_init()).

### ktypes and release methods

One important thing still missing from the discussion is what happens to a kobject when its reference count reaches zero. The code which created the kobject generally does not know when that will happen; if it did, there would be little point in using a kobject in the first place. Even predicatable object lifecycles become more complicated when sysfs is brought in; user-space programs can keep a reference to a kobject (by keeping one of its associated sysfs files open) for an arbitrary period of time.

The end result is that a structure protected by a kobject cannot be freed before its reference count goes to zero. The reference count is not under the direct control of the code which created the kobject. So that code must be notified asynchronously whenever the last reference to one of its kobjects goes away.

This notification is done through a kobject's release() method. Usually such a method has a form like:

    void my_object_release(struct kobject *kobj)
    {
    	    struct my_object *mine = container_of(kobj, struct my_object, kobj);

	    /* Perform any additional cleanup on this object, then... */
	    kfree (mine);
    }

One important point cannot be overstated: every kobject must have a release() method, and the kobject must persist (in a consistent state) until that method is called. If these constraints are not met, the code is flawed.

Interestingly, the release() method is not stored in the kobject itself; instead, it is associated with the ktype. So let us introduce struct kobj_type:

    struct kobj_type {
	    void (*release)(struct kobject *);
	    struct sysfs_ops	*sysfs_ops;
	    struct attribute	**default_attrs;
    };

This structure is used to describe a particular type of kobject (or, more correctly, of containing object). Every kobject needs to have an associated kobj_type structure; a pointer to that structure can be placed in the kobject's ktype field at initialization time, or (more likely) it can be defined by the kobject's containing kset.

The release field in struct kobj_type is, of course, a pointer to the release() method for this type of kobject. The other two fields (sysfs_ops and default_attrs) control how objects of this type are represented in sysfs; they are beyond the scope of this document.

### ksets

In many ways, a kset looks like an extension of the kobj_type structure; a kset is a collection of identical kobjects. But, while struct kobj_type concerns itself with the _type_ of an object, struct kset is concerned with aggregation and collection. The two concepts have been separated so that objects of identical type can appear in distinct sets.

A kset serves these functions:

- It serves as a bag containing a group of identical objects. A kset can be used by the kernel to track "all block devices" or "all PCI device drivers."
    
- A kset is the directory-level glue that holds the device model (and sysfs) together. Every kset contains a kobject which can be set up to be the parent of other kobjects; in this way the device model hierarchy is constructed.
    
- Ksets can support the "hotplugging" of kobjects and influence how hotplug events are reported to user space.

In object-oriented terms, "kset" is the top-level container class; ksets inherit their own kobject, and can be treated as a kobject as well.

![](study/computer/notebooks/linux驱动模型/LWN.net/kobject.png)
A kset keeps its children in a standard kernel linked list. Kobjects point back to their containing kset via their kset field. In almost all cases, the contained kobjects also have a pointer to the kset (or, strictly, its embedded kobject) in their parent field. So, typically, a kset and its kobjects look something like what you see in the diagram to the right. Do bear in mind that (1) all of the contained kobjects in the diagram are actually embedded within some other type, possibly even other ksets, and (2) it is not required that a kobject's parent be the containing kset.

For initialization and setup, ksets have an interface very similar to that of kobjects. The following functions exist:  



    void kset_init(struct kset *kset);
    int kset_add(struct kset *kset);
    int kset_register(struct kset *kset);
    void kset_unregister(struct kset *kset);

For the most part, these functions just call the analogous kobject_ function on the kset's embedded kobject.

For managing the reference counts of ksets, the situation is about the same:

    struct kset *kset_get(struct kset *kset);
    void kset_put(struct kset *kset);

A kset, too, has a name, which is stored in the embedded kobject. So, if you have a kset called my_set, you would set its name with:

    kobject_set_name(my_set->kobj, "The name");

Ksets also have a pointer (in the ktype field) to the kobj_type structure describing the kobjects it contains. This type will be applied to any kobject which does not contain a pointer to its own kobj_type structure.

Another attribute of a kset is a set of hotplug operations; these operations are invoked whenever a kobject enters or leaves the kset. They are able to determine whether a user-space hotplug event is generated for this change, and to affect how that event is presented. The hotplug operations are beyond the scope of this document; they will be discussed later with sysfs.

One might ask how, exactly, a kobject is added to a kset, given that no functions which perform that function have been presented. The answer is that this task is handled by kobject_add(). When a kobject is passed to kobject_add(), its kset member should point to the kset to which the kobject will belong. kobject_add() will handle the rest. There is currently no other way to add a kobject to a kset without directly messing with the list pointers.

Finally, a kset contains a subsystem pointer (called subsys). So it must be time to talk about subsystems.

### Subsystems

A subsystem is a representation for a high-level portion of the kernel as a whole. It is actually a simple structure:

    struct subsystem {
	    struct kset		kset;
	    struct rw_semaphore	rwsem;
    };

A subsystem, thus, is really just a wrapper around a kset. In fact, life is not quite that simple; a single subsystem can contain multiple ksets. This containment is represented by the subsys pointer in struct kset; so, if there are multiple ksets in a subsystem, it will not be possible to find all of them directly from the subsystem structure.

Every kset must belong to a subsystem; the subsystem's rwsem semaphore is used to serialize access to a kset's internal linked list.

Subsystems are often declared with a special macro:

    decl_subsys(char *name, struct kobj_type *type, 
                struct kset_hotplug_ops *hotplug_ops);

This macro just creates a struct subsystem (its name is the name given to the macro with _subsys appended) with the internal kset initialized with the given type and hotplug_ops.

Subsystems have the usual set of setup and teardown functions:

    void subsystem_init(struct subsystem *subsys);
    int subsystem_register(struct subsystem *subsys);
    void subsystem_unregister(struct subsystem *subsys);
    struct subsystem *subsys_get(struct subsystem *subsys)
    void subsys_put(struct subsystem *subsys);

Most of these operations just act upon the subsystem's kset.

### Kobject initialization again

Now that we have covered all of that stuff, we can talk in detail about how a kobject should be prepared for its existence in the kernel. Here are all of the struct kobject fields which must be initialized somehow:

- name and k_name - the name of the object. These fields should always be initialized with kobject_set_name().
    
- refcount is the kobject's reference count; it is initialized by kobject_init()
    
- parent is the kobject's parent in whatever hierarchy it belongs to. It can be set explicitly by the creator. If parent is NULL when kobject_add() is called, it will be set to the kobject of the containing kset.
    
- kset is a pointer to the kset which will contain this kobject; it should be set prior to calling kobject_add().
    
- ktype is the type of the kobject. If the kobject is contained within a kset, and that kset has a type set in its ktype field, then this field in the kobject will not be used. Otherwise it should be set to a suitable kobj_type structure.

Often, much of the initialization of a kobject is handled by the layer that manages the containing kset. Thus, to get back to our old example, a char driver might create a struct cdev, but it need not worry about setting any of the fields in the embedded kobject - except for the name. Everything else is handled by the char device layer.

### Looking forward

So far, we have covered the operations used to set up and manipulate kobjects. The core concept is relatively simple: kobjects can be used to (1) maintain a reference count for an object and clean up when the object is no longer used, and (2) create a hierarchical data structure through kset membership.

What is missing so far is how kobjects represent themselves to user space. The sysfs interface to kobjects makes it easy to export information to (and to receive information from) user space. The symbolic linking features of sysfs allow the creation of pointers across distinct kobject hierarchies. Stay tuned for a description of how all that works.