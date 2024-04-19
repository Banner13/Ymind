kobject "结构首次出现在 2.5.45 开发内核中。它最初是作为统一内核代码的一种简单方法，用于管理引用计数对象。不过，kobject 后来遇到了一些 "任务蠕变"；现在，它是将大部分设备模型及其 sysfs 接口粘合在一起的粘合剂。驱动程序编写者很少需要直接与 kobjects 打交道；它们通常隐藏在由深层代码创建的结构中。不过，Kobjects 有一定的倾向性，会通过中间层泄露出来，让人知道它们的存在。因此，熟悉它们是什么以及如何工作是一件好事。本文档将介绍 kobject 类型和相关主题，但对 kobject 与 sysfs 之间的大部分交互关系则一笔带过（稍后将单独介绍）。

理解驱动程序模型（以及作为其基础的 kobject 抽象）的部分困难在于没有一个明显的起点。处理 kobjects 需要了解几种不同的类型，而所有这些类型都会相互引用。为了让事情变得更简单，我们将采取多通道方法，从模糊的术语开始，然后逐步增加细节。为此，下面是我们将使用的一些术语的快速定义。

- 一个 **kobject** 是 struct kobject 类型的对象。对象有一个名称和一个引用计数。一个 kobject 也有一个父指针（允许 kobject 被排列成层次结构）、一个特定的类型，也许还有在 sysfs 虚拟文件系统中的表示。
    
    Kobject 本身通常并不引人关注；相反，它们通常被嵌入到其他结构中，而这些结构中包含了代码真正感兴趣的内容。
    
- 一个**ktype**是与 kobject 相关联的类型。ktype 控制着 kobject 不再被引用时的情况，以及 kobject 在 sysfs 中的默认表示。
    
- 一个 **kset** 是一组 kobjects，所有这些 kobjects 都嵌入了相同类型的结构。Kset 是 Kobjects 集合的基本容器类型。值得一提的是，Kset 包含自己的 kobjects。这意味着一个 kobject 的kset 通常在他的父kobject中，但通常情况下也不一定非得如此。
    
    当你看到 sysfs 目录里有很多条目时，通常每个条目都对应着同一个 kset 中的一个 kobject。
    
- **subsystem**是 ksets 的集合，它们共同构成了内核的一个主要子部分。子系统通常与 sysfs 中的顶级目录相对应。

我们将研究如何创建和操作所有这些类型。我们将采用自下而上的方法，因此我们将回到 kobjects。

### 嵌入 kobjects
内核代码很少（甚至不知道）创建独立的 kobject；相反，kobjects 被用来控制对更大的、特定领域对象的访问。为此，kobjects 被嵌入到其他结构中。如果你习惯于用面向对象的术语来思考问题，那么 kobjects 可以被看作是一个顶级的抽象类，其他类都是从它派生出来的。一个 kobject 实现了一系列功能，这些功能本身并不特别有用，但在其他对象中却很好用。C 语言不允许直接表达继承，因此必须使用结构嵌入等其他技术。

例如，描述 char 设备的结构 struct cdev 的 2.6.0-test6 版本就是这样：

    struct cdev {
	    struct kobject kobj;
		struct module *owner;
		struct file_operations *ops;
		struct list_head list;
    };

如果有一个 struct cdev 结构，那么只需使用 kobj 指针就可以找到其嵌入的 kobject。然而，使用 kobjects 的代码通常会遇到相反的问题：给定一个 struct kobject 指针，那么指向包含结构的指针是什么呢？你应该避免使用技巧（比如假设 kobject 位于结构的开头），而是使用 <linux/kernel.h> 中的 container_of() 宏：

	container_of(pointer, type, member)

其中 pointer 是指向嵌入 kobject 的指针，type 是包含结构的类型，member 是指针指向的结构字段的名称。container_of() 的返回值是指向给定类型的指针。因此，举例来说，一个指向嵌入到名为 "kp "的 struct cdev 中的 struct kobject 的指针，可以通过以下方式转换为指向包含结构的指针：

    struct cdev *device = container_of(kp, struct cdev, kobj);

程序员通常会定义一个简单的宏，用于将对象指针 "反投 "到包含类型。

### kobjects 的初始化

创建 kobject 的代码当然必须初始化该对象。一些内部字段是通过调用 kobject_init()（强制）设置的：

    void kobject_init(struct kobject *kobj)；

其中，kobject_init() 会将 kobject 的引用计数设置为 1。不过，调用 kobject_init() 并不够。Kobject 用户至少必须设置 kobject 的名称；这是将在 sysfs 条目中使用的名称。如果深入研究内核源代码，你会发现有代码直接将字符串复制到 kobject 的名称字段，但这种方法应该避免。请使用

    int kobject_set_name(struct kobject *kobj, const char *format, ...)；

该函数使用 printk 样式的变量参数列表。不管你信不信，这个操作实际上是有可能失败的；认真的代码应该检查返回值并做出相应的反应。

创建者应直接或间接设置的其他 kobject 字段包括 ktype、kset 和 parent。我们很快就会讲到这些。

### 引用计数

kobject 的主要功能之一是作为嵌入对象的引用计数器。只要对象的引用存在，对象（以及支持对象的代码）就必须继续存在。用于操作 kobject 引用计数的底层函数有

    struct kobject *kobject_get(struct kobject *kobj)；
    void kobject_put(struct kobject *kobj)；

成功调用 kobject_get()后，kobject 的引用计数器将递增，并返回指向该 kobject 的指针。但是，如果 kobject 已在销毁过程中，则操作将失败，kobject_get() 将返回 NULL。必须始终对该返回值进行测试，否则可能会导致令人不快的竞赛条件。

释放引用时，调用 kobject_put() 将递减引用计数，并可能会释放对象。请注意，kobject_init() 会将引用计数设置为 1，因此设置 kobject 的代码最终需要执行 kobject_put()来释放引用。

请注意，在很多情况下，kobject 本身的引用计数可能不足以防止出现竞赛条件。例如，一个 kobject（及其包含的结构）的存在可能需要创建该 kobject 的模块继续存在。当 kobject 仍在传递时，卸载该模块是不行的。这就是我们上面看到的 cdev 结构包含一个 struct module 指针的原因。struct cdev 的引用计数实现如下：

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

创建对 cdev 结构的引用需要同时创建对该模块拥有者的引用。因此，cdev_get() 使用 try_module_get() 来尝试增加模块的使用次数。如果操作成功，则使用 kobject_get()来增加 kobject 的引用计数。当然，该操作也可能失败，因此代码会检查 kobject_get() 的返回值，如果不成功，则释放对模块的引用。

### 与 sysfs 挂钩

初始化后的 kobject 可以顺利进行引用计数，但不会出现在 sysfs 中。要创建 sysfs 条目，内核代码必须将对象传递给 kobject_add()：

    int kobject_add(struct kobject *kobj)；

和往常一样，这个操作可能会失败。函数：

    void kobject_del(struct kobject *kobj)；

将从 sysfs 中删除 kobject。

还有一个 kobject_register()函数，实际上就是 kobject_init() 和 kobject_add() 调用的组合。类似地，kobject_unregister() 会调用 kobject_del()，然后调用 kobject_put()，以释放通过 kobject_register()（或真正的 kobject_init()）创建的初始引用。

### ktype和释放方法

讨论中还缺少一件重要的事情，那就是当 kobject 的引用计数为零时，它会发生什么。创建 kobject 的代码通常不知道何时会发生这种情况(其他用户也在使用)；如果知道，那么使用 kobject 就没有什么意义了。如果引入 sysfs，即使是可预测的对象生命周期也会变得更加复杂；用户空间程序可以在任意时间段内（通过打开相关的 sysfs 文件）保持对 kobject 的引用。

最终的结果是，受 kobject 保护的结构在其引用计数归零之前无法被释放。引用计数不受创建 kobject 的代码的直接控制。因此，每当对其中一个 kobject 的最后一次引用消失时，必须异步通知该代码。

这种通知是通过 kobject 的 release() 方法完成的。通常，这种方法的形式如下

    void my_object_release(struct kobject *kobj)
    {
    	    struct my_object *mine = container_of(kobj, struct my_object, kobj);

	    /* Perform any additional cleanup on this object, then... */
	    kfree (mine);
    }

有一点再怎么强调也不为过：每个 kobject 都必须有一个 release() 方法，并且在调用该方法之前，kobject 必须持续存在（处于一致的状态）。如果不满足这些约束条件，代码就会有缺陷。

有趣的是，release() 方法并不存储在 kobject 本身中，而是与 ktype 相关联。因此，让我们介绍一下 struct kobj_type：

    struct kobj_type {
	    void (*release)(struct kobject *);
	    struct sysfs_ops	*sysfs_ops;
	    struct attribute	**default_attrs;
    };

该结构用于描述 kobject（或者更准确地说，是包含对象）的特定类型。每个 kobject 都需要有一个相关的 kobj_type 结构；指向该结构的指针可以在初始化时放在 kobject 的 ktype 字段中，或者（更有可能）由 kobject 的包含 kset 来定义。

当然，结构 kobj_type 中的 release 字段是指向该类型 kobject 的 release() 方法的指针。其他两个字段（sysfs_ops 和 default_attrs）控制着该类型对象在 sysfs 中的表示方式；它们超出了本文档的讨论范围。

### ksets

在许多方面，kset 看起来像是 kobj_type 结构的扩展；kset 是相同 kobjects 的集合。但是，struct kobj_type 关注的是对象的_type_，而 struct kset 关注的是聚合和集合。这两个概念的分离是为了让相同类型的对象可以出现在不同的集合中。

kset 就具有这些功能：
- 它就像一个袋子，里面装着一组相同的对象。内核可以使用 kset 来跟踪 "所有块设备 "或 "所有 PCI 设备驱动程序"。
    
- kset 是将设备模型（和 sysfs）整合在一起的目录级粘合剂。每个 kset 都包含一个 kobject，它可以被设置为其他 kobject 的父对象；设备模型的层次结构就是以这种方式构建的。
    
- Kset 可以支持 kobjects 的 "热插拔"，并影响向用户空间报告热插拔事件的方式。

在面向对象的术语中，"kset "是顶级容器类；ksets 继承了自己的 kobject，也可以被视为一个 kobject。

![](study/computer/notebooks/linux驱动模型/LWN.net/kobject.png)
kset 将其子节点保存在标准内核链表中。Kobjects 通过它们的 kset 字段指向包含它们的 kset。几乎在所有情况下，包含的 kobjects 在其父字段中也有一个指向 kset（或者严格来说，指向其嵌入的 kobject）的指针。因此，通常情况下，一个 kset 及其 kobjects 看上去就像右图所示。请注意：(1) 图中所有包含的 kobject 其实都嵌入了其他类型，甚至可能是其他 ksets；(2) 并不要求 kobject 的父对象就是包含的 kset。

在初始化和设置方面，ksets 的界面与 kobjects 的界面非常相似。有以下函数:

    void kset_init(struct kset *kset);
    int kset_add(struct kset *kset);
    int kset_register(struct kset *kset);
    void kset_unregister(struct kset *kset);

在大多数情况下，这些函数只是在 kset 的嵌入 kobject 上调用类似的 kobject_ 函数。

在管理 ksets 的引用计数方面，情况也大致相同：

    kobject_set_name(my_set->kobj, "The name");

Ksets 也有一个指向描述它所包含的 kobject 的 kobj_type 结构的指针（在 ktype 字段中）。这种类型将应用于任何不包含指向自身 kobj_type 结构指针的 kobject。

kset 的另一个属性是一组热插拔操作；每当一个 kobject 进入或离开 kset 时，这些操作都会被调用。这些操作可以决定是否为这种变化生成用户空间热插拔事件，并影响该事件的显示方式。热插拔操作超出了本文档的讨论范围；稍后将与 sysfs 一起讨论。

也许有人会问，既然没有函数来执行 kobject 添加到 kset 中的功能，那么到底是如何添加到 kset 中的呢？答案是由 kobject_add() 来完成。当一个 kobject 传递给 kobject_add()时，它的 kset 成员应该指向该 kobject 所属于的 kset。目前还没有其他方法可以在不直接接触列表指针的情况下将 kobject 添加到 kset 中。

最后，一个 kset 包含一个子系统指针（称为 subsys）。因此，是时候谈谈子系统了。

#### Subsystems

Subsystems是整个内核高级部分的代表。它实际上是一个简单的结构：

    struct subsystem {
	    struct kset		kset;
	    struct rw_semaphore	rwsem;
    };

因此，子系统实际上只是一个 kset 的包装。事实上，情况并非如此简单；一个子系统可以包含多个 ksets。这种包含由 struct kset 中的 subsys 指针表示；因此，如果一个子系统中有多个 ksets，就无法直接从子系统结构中找到所有的 ksets。

每个 kset 都必须属于一个子系统；子系统的 rwsem 信号用于序列化对 kset 内部链接列表的访问。

Subsystems通常用一个特殊的宏来声明：

    decl_subsys(char *name, struct kobj_type *type, 
                struct kset_hotplug_ops *hotplug_ops);

该宏只是创建一个结构子系统（其名称为宏的名称，后加 _subsys），内部 kset 用给定的类型和 hotplug_ops 初始化。

子系统具有常用的设置和拆卸功能：

    void subsystem_init(struct subsystem *subsys);
    int subsystem_register(struct subsystem *subsys);
    void subsystem_unregister(struct subsystem *subsys);
    struct subsystem *subsys_get(struct subsystem *subsys)
    void subsys_put(struct subsystem *subsys);

这些操作大多只对子系统的 kset 起作用。

### 再次初始化 Kobject

既然我们已经介绍了所有这些内容，那么就可以详细谈谈 kobject 在内核中的存在准备工作了。下面是所有必须以某种方式初始化的 kobject 结构字段：

- name 和 k_name - 对象的名称。这些字段应始终使用 kobject_set_name()进行初始化。
    
- refcount 是 kobject 的引用计数，由 kobject_init() 进行初始化。
    
- parent 是 kobject 在其所属层次结构中的父对象。它可以由创建者明确设置。如果调用 kobject_add() 时 parent 为 NULL，它将被设置为包含 kset 的 kobject。
    
- kset 是指向包含此 kobject 的 kset 的指针；应在调用 kobject_add() 之前设置。
    
- ktype 是 kobject 的类型。如果 kobject 包含在一个 kset 中，且该 kset 在其 ktype 字段中设置了类型，那么 kobject 中的这个字段将不会被使用。否则，应将其设置为合适的 kobj_type 结构。

通常，kobject 的大部分初始化工作都是由管理包含 kset 的层处理的。因此，回到我们以前的例子，char 驱动程序可能会创建一个 struct cdev，但它不必担心在嵌入式 kobject 中设置任何字段（名称除外）。其他一切都由 char 设备层处理。

### 展望未来

到目前为止，我们已经介绍了用于设置和操作 kobjects 的操作。核心概念相对简单：kobjects 可以用来：（1）维护对象的引用计数，并在对象不再使用时进行清理；（2）通过 kset 成员身份创建分层数据结构。

目前还缺少的是 kobjects 如何向用户空间展示自己。kobjects 的 sysfs 接口可以轻松地向用户空间输出信息（以及从用户空间接收信息）。sysfs 的符号链接功能允许在不同的 kobject 层次结构中创建指针。请继续关注我们对这一切工作原理的描述。
