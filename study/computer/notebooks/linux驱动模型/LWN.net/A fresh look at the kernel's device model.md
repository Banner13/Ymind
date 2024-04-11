## A fresh look at the kernel's device model
May 27, 2015
This article was contributed by Neil Brown
[link](https://lwn.net/Articles/645810/)

Understanding the Linux device model is (or should be, at least) central to working with device drivers in Linux — and drivers constitute over half of the kernel code. I've been working with a variety of device drivers at differing levels of involvement for some years but until recently I didn't feel that I really understood the model. This is potentially dangerous as, without a good understanding, it is easy to make poor choices.

The problem, or at least my problem, is firmly rooted in the terminology. The device model involves things called "device" and "driver", "bus" and "class". To be able to understand the model, I need accurate definitions of these terms, and useful definitions are hard to find.

An [[Driver porting: Device model overview|LWN article]] from 2003 is an excellent example, as it clearly presents some definitions of the sort that can be found in other documentation and in the source code. It declares a device to be: "A physical or virtual object which attaches to a (possibly virtual) bus". This sounds good and highly general, but it doesn't actually match reality, even the reality of twelve years ago when the article was written.

For example, in the device model, a partition on a hard drive is a "device" much like the hard drive as a whole is. The hard drive as a whole may attach to a "bus", but the partition certainly doesn't: at best it attaches to the whole drive. Also, there are devices that don't attach to anything, let alone a "bus". The devices listed in directories under /sys/devices/virtual are not "attached" to anything. That "virtual" directory is not a special bus called "virtual", it is simply a place to put things that don't belong anywhere else.

Similar oversimplifications are found when trying to find definitions of the other objects. This is very likely because the driver model was still under development and the meanings that would end up being useful had not yet fully crystallized. Now, over a decade later, the available documentation still refers to the same terms and generally uses the same imprecise definitions.

### The eye of the beholder

The epiphany that allowed me to form a coherent understanding of the device model was that none of these terms really have an external meaning at all. They are defined purely by the code that implements them. A device is simply any data structure that contains an embedded struct device, no more and no less.

Meaning comes only from the mind of the developer working with the code. Having multiple independent developers will likely result in multiple different meanings. The meanings that seem to be associated with the terms and that are found in documentation are the meanings that the early developers were thinking about. Those ideas have been revised over time, and other developers have had other thoughts.

The definition "anything with a struct device" may be accurate, but is not useful for someone considering the implementation of a new driver or modification to an old one. Similarly "what other developers are thinking" is too nebulous to be useful. With a bit of effort, and some carefully chosen examples, each of these can be fleshed out a bit and together form a picture that is, hopefully, a good start. So, to present my understanding of the device model, and particularly of those four terms, I will present some examples to show what other developers have thought, and what value a struct device provides.

The first example revolves around the [TCA6507](http://www.ti.com/product/tca6507) chip from Texas Instruments. This is a simple piece of hardware that accepts requests over an "i2c" bus, and responds by draining current through seven separate pins with various on/off patterns. This is particularly intended to pull electrical current through an LED to make it glow, but can equally pull current through a resistor to create logic 0 or 1 levels. This example is chosen because it is the most "device-like" of devices that I am familiar with — it perfectly fits the earlier definition.

The second example is the [workqueue](https://www.kernel.org/doc/Documentation/workqueue.txt) mechanism in Linux. It allows arbitrary tasks to be handed off for asynchronous completion, either promptly or after a delay, and will attempt to make optimal use of resources in doing so. It is also the least "device-like" thing I came across.

With these examples in mind, together with the previously mentioned block devices, we can proceed to those definitions.

### Devices

A device is an instance. It is corresponds to a thing, or maybe an "object" in the most general sense of the word. A device gains its thing-hood primarily by a person thinking that it is something worth identifying. A device may sometimes correspond to a specific piece of hardware like an integrated circuit, but it could equally correspond to a collection of such circuits or just one component of the functionality of a circuit. Hardware need not exist at all — a device could be virtualized or could represent something that has no real physical equivalent at all. It is just a "thing".

The TCA6507 chip is represented in Linux by a device. Each of the seven controllable pins may be connected to something and this may lead to more devices. If a pin is attached to an LED, for example, then there will be a separate device that represents that LED, though arguably it could be seen as representing the signalling capability of the "LED plus pin" combination. Different people will probably look at this in different ways.

If a pin is connected to a "pull-up" resistor and used to signal a logic level, then it will be represented in Linux as a "GPIO" — General Purpose I/O pin. In terms of the device model, all of the pins that are configured as GPIOs are presented as a single "gpiochip" device. So while there is one device for _each_ LED, there is one device for _all_ GPIOs.

Each individual GPIO can be configured and used internally, or may be exported to user space through sysfs. When a GPIO is exported, a new device is created to represent just that one GPIO. This is visible as a directory under /sys/class/gpio; files are available there that can be used to set the output level to 1 or 0.

There are two important lessons in this example. One is that choices are context-dependent and probably very developer-dependent as well. Grouping GPIOs into a "chip" seems to make sense, while doing the same with LEDs doesn't seem to be a priority, though there has been a [suggestion](http://comments.gmane.org/gmane.linux.leds/1929) that there might be value in that. The second lesson is that one reason to make a "thing" into a "device" in the device model is so that it can appear in sysfs and be directly examined or manipulated.

Moving on to our second example we find something that is not at all "device-like". There are many "things" or "instances" in Linux that are not device-like and are not represented as devices: filesystems and processes are obvious examples. One that _is_ represented as a device is the workqueue.

The workqueue subsystem in Linux creates a "device" to represent each distinct queue. The [apparent reason](https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=226223ab3c4118ddd10688cc2c131135848371ab) for this is much like the reason for (sometimes) making devices for GPIOs — it allows the thing (i.e. the workqueue) to be examined and managed via sysfs. A thing doesn't _have_ to be a device to appear in sysfs, modules and filesystems are clear counter-examples to that idea. But making something a "device" is a relatively easy and well-worn path to sysfs access.

The compelling reason to use a "device" to represent some "thing" seems to be the interfaces. A "device" not only has standard interfaces in sysfs, it also has standard interfaces for power management, and may make use of internal services (like the [devm resource management API](https://lwn.net/Articles/222860/)) that are only provided to devices. There is also useful functionality for grouping "like" devices together, for varying definitions of "like".

### Classes

A "class" is both the implementation of a set of devices, and the set of devices themselves. A class can be thought of as a driver in the more general sense of the word. The device model has specific objects called "drivers" but a "class" is not one of those.

All the devices in a particular class tend to expose much the same interface, either to other devices or to user space (via sysfs or otherwise). Exactly how uniform the included devices are is really up to the class though. It is not unusual for there to be optional aspects of an interface that not all devices in a class present. It is not unheard-of for some devices in the same class to be completely different from others.

So far we have met three classes in our examples. A device that represents an LED attached to a TCA6507 is a member of the "leds" class. This class supports the blinking, flashing, and brightness control features of physical LEDs. The class requires an underlying device to be available, such as a TCA6507 or a GPIO or any of various other options. This underlying device must be able to turn the LED on or off, may be able to set the brightness, and might even provide timer functionality to autonomously blink the LED with a given period and duty cycle. The "leds" class hides as much of this detail as it can to provide a simple abstract device.

Similar to the "leds" class is the "gpio" class; it provides a uniform interface to a variety of devices that can generate (output) or can sense (input) an electrical logic level. If the underlying device can generate an interrupt on a level change, "gpio" can translate that to a notification via poll() or can route it to the interrupt handler for some other device. The gpio class provides both the "gpiochip" devices and the individual "gpio" devices.

The third class we have met is the "disk" class which provides both whole hard drives and partitions within drives. As with the "leds" class, there are a few different interfaces to storage functionality that can be provided and the "disk" class presents a unified interface to that functionality.

There is some obvious similarity between the "gpio" class implementing both "gpios" and "gpiochips", and the "disk" class implementing both "disks" and "partitions". There are also differences. One of those is that "gpio" and "gpiochip" provide completely different interfaces, while "disk" and "partition" have a lot of commonality in their interfaces — both have block sizes and support I/O, but only a "disk" can be "removable".

Another, less obvious difference involves another aspect of the device model. Each "device" can have a "type". This type is often presented in the "uevent" file in the relevant sysfs directory. For example, the command:

    grep DEVTYPE /sys/class/block/*/uevent

will show the type of every block device on your system. The different types in the "gpio" class are not known to the device model, though, so they are not reported by the uevent file. A human or a script would need to deduce the type from the device names if it was important.

Each of the classes listed here can be seen as providing a generic interface over a range of different hardware. This seems to be part of the original intention of the "class" facility. However "generic" isn't a very precise term. What one developer sees as "generic" another developer might see as "specific". These perspectives can change over time too, particularly if a simple or successful interface gets used more broadly than its initial context.

To enforce this point it is worth briefly considering the "backlight" class of devices. A backlight for a graphics display can use a number of different underlying technologies, including a device of the "leds" class. So depending on your perspective, an LED might be a generic interface for signaling, or a specific underlying technology for backlighting. It depends on whose eye is beholding.

