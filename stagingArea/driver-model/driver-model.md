Linux 驱动模型起源于对当时PCI和USB总线驱动的分析，从2.5.1版本开始引入内核。
最初的目标是为计算机中的每一个设备提供一种通用的表示和操作方法，便于支持现代电源管理中的挂起和恢复。

除了电源管理信息以外，提出了以下通用概念：
Devices  设备
Device drivers  设备驱动
Bus drivers  总线驱动:与某种类型的外围总线通信
Device Classes  设备类型:描述设备的功能
Device Interfaces  设备接口

设备就是具体存在于计算机上的每一个设备
没有设备模型之前的流程就是设备通过对应的驱动提供某些设备接口提供给用户使用。但是随着驱动的数量和种类日益增加之后，对于用户来说，同一种类的设备(例如摄像头、音频、温度传感器)它们的接口由各自的驱动提供，而驱动来源于不同的开发者，所以对于同一个功能(例如使用摄像头拍摄一张图片，从温度传感器获取温度)会出现不同的接口，这样对用户来说同一个的功能要针对不同的设备来使用不同的接口是一中无意义的开销，因此出现了设备类型。
对内核来说，它需要做的是建立与设备的通信，而设备的通信与硬件总线(PCI、USB、I2C)相关联，因此出现总线驱动。
在驱动模型中，内核维护了设备与驱动之间的通信，用户只需按照设备类型调用对应的接口不在受设备差异影响，驱动开发者则需要实现设备的功能，并提供合适的设备类型接口。
(内心独白: 终于搞清楚class bus 的作用了，对于驱动开发者来说，要想写出好的驱动，需要了解很多信息，提供设备设备对应的接口，而不是自己定义!!!)

模型对以上的每一种类型都提供了与其相关联的功能函数，极大程度上简化了内核和用户操作设备的流程。

kobject 以及sysfs 是驱动模型输出中最重要的两个概念，因为更通用所以从驱动模型中分离出来。
