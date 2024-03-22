## A fresh look at the kernel's device model
May 27, 2015
This article was contributed by Neil Brown
[link](https://lwn.net/Articles/645810/)

Understanding the Linux device model is (or should be, at least) central to working with device drivers in Linux — and drivers constitute over half of the kernel code. I've been working with a variety of device drivers at differing levels of involvement for some years but until recently I didn't feel that I really understood the model. This is potentially dangerous as, without a good understanding, it is easy to make poor choices.
在 Linux 中使用设备驱动程序的核心是了解 Linux 设备模型是（至少应该是）——而驱动程序构成了内核代码的一半以上。多年来，我一直在不同程度地参与各种设备驱动程序的工作，但直到最近，我才觉得自己真正理解了这种模式。这具有潜在的危险性，因为如果没有充分的了解，就很容易做出错误的选择。

The problem, or at least my problem, is firmly rooted in the terminology. The device model involves things called "device" and "driver", "bus" and "class". To be able to understand the model, I need accurate definitions of these terms, and useful definitions are hard to find.
这个问题，或者至少是我的问题，根源在于术语。设备模型涉及 "device"、"driver"、"bus "和 "class "等术语。为了理解这个模型，我需要这些术语的准确定义，而有用的定义却很难找到。

An [LWN article](https://lwn.net/Articles/31185/) from 2003 is an excellent example, as it clearly presents some definitions of the sort that can be found in other documentation and in the source code. It declares a device to be: "A physical or virtual object which attaches to a (possibly virtual) bus". This sounds good and highly general, but it doesn't actually match reality, even the reality of twelve years ago when the article was written.
LWN 2003 年的一篇文章就是一个很好的例子，因为它清楚地介绍了在其他文档和源代码中可以找到的一些定义。它将设备定义为 ""连接到（可能是虚拟的）总线的物理或虚拟对象""。这听起来不错，也很笼统，但实际上与现实不符，甚至与十二年前撰写这篇文章时的现实也不符。

For example, in the device model, a partition on a hard drive is a "device" much like the hard drive as a whole is. The hard drive as a whole may attach to a "bus", but the partition certainly doesn't: at best it attaches to the whole drive. Also, there are devices that don't attach to anything, let alone a "bus". The devices listed in directories under /sys/devices/virtual are not "attached" to anything. That "virtual" directory is not a special bus called "virtual", it is simply a place to put things that don't belong anywhere else.
例如，在设备模型中，硬盘上的分区是一个 "设备"，就像整个硬盘一样。硬盘作为一个整体可以连接到 "总线 "上，但分区肯定不是：它充其量只能连接到整个硬盘。此外，有些设备什么都不连接，更不用说 "总线 "了。列在 /sys/devices/virtual 目录下的设备并没有 "连接 "到任何设备。虚拟 "目录并不是一条名为 "虚拟 "的特殊总线，它只是一个用来放置不属于其他地方的东西的地方。

Similar oversimplifications are found when trying to find definitions of the other objects. This is very likely because the driver model was still under development and the meanings that would end up being useful had not yet fully crystallized. Now, over a decade later, the available documentation still refers to the same terms and generally uses the same imprecise definitions.
在试图找到其他对象的定义时，也发现了类似的过度简化现象。这很可能是因为驱动程序模型仍在开发中，最终有用的含义尚未完全明确。十多年后的今天，现有的文档仍在提及相同的术语，并普遍使用相同的不精确定义。