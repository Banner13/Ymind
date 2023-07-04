[TOC]

## Platform Devices and Drivers
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	See <linux/platform_device.h> for the driver model interface to the platform bus: platform_device, and platform_driver.
	This pseudo-bus is used to connect devices on busses with minimal infrastructure,
	like those used to integrate peripherals on many system-on-chip processors, or some "legacy" PC interconnects;
	as opposed to large formally specified ones like PCI or USB.
	参见<linux/platform_device.h>，了解平台总线的驱动模型接口：platform_device，和platform_driver。
	这种伪总线被用来连接具有最小基础设施的总线上的设备、
	像那些用于在许多片上系统处理器上集成外设的总线，或一些 "传统 "的PC互连；
	而不是像PCI或USB这样的大型公认的特殊总线。

### Platform devices
	~~~~~~~~~~~~~~~~
	Platform devices are devices that typically appear as autonomous entities in the system.
	This includes legacy port-based devices and host bridges to peripheral buses, and most controllers integrated into system-on-chip platforms.
	What they usually have in common is direct addressing from a CPU bus.
	Rarely, a platform_device will be connected through a segment of some other kind of bus;
	but its registers will still be directly addressable.
	平台设备是在系统中通常作为自主实体出现的设备。
	这包括传统的基于端口的设备和主机与外围总线的桥接，以及大多数集成到片上系统平台的控制器。
	它们通常的共同点是直接从CPU总线寻址。
	极少数情况下，一个平台设备会通过一些其他类型的总线段连接；
	但它的寄存器仍然可以直接寻址。
	
	Platform devices are given a name, used in driver binding, and a list of resources such as addresses and IRQs.
	平台设备被赋予一个名称，用于驱动程序绑定，以及一个资源列表，如地址和IRQ。
	
	struct platform_device {
		const char	*name;
		u32		id;
		struct device	dev;
		u32		num_resources;
		struct resource	*resource;
	};


### Platform drivers
	~~~~~~~~~~~~~~~~
	Platform drivers follow the standard driver model convention, where discovery/enumeration is handled outside the drivers,
	and drivers provide probe() and remove() methods.
	They support power management and shutdown notifications using the standard conventions.
	平台驱动遵循标准的驱动模型惯例，其中发现/枚举是在驱动之外处理的、
	驱动程序提供probe（）和remove（）方法。
	它们支持电源管理和使用标准惯例的关机通知。
	
	struct platform_driver {
		int (*probe)(struct platform_device *);
		int (*remove)(struct platform_device *);
		void (*shutdown)(struct platform_device *);
		int (*suspend)(struct platform_device *, pm_message_t state);
		int (*suspend_late)(struct platform_device *, pm_message_t state);
		int (*resume_early)(struct platform_device *);
		int (*resume)(struct platform_device *);
		struct device_driver driver;
	};
	
	Note that probe() should general verify that the specified device hardware actually exists;
	sometimes platform setup code can't be sure.
	The probing can use device resources, including clocks, and device platform_data.
	请注意，probe()通常应当验证指定的设备硬件是否真的存在；
	有时平台启动代码不能确定。
	探测可以使用设备资源，包括clocks和device platform_data。
	
	Platform drivers register themselves the normal way:
	平台驱动程序以正常方式进行自我注册：
	
		int platform_driver_register(struct platform_driver *drv);
	
	Or, in common situations where the device is known not to be hot-pluggable,
	the probe() routine can live in an init section to reduce the driver's runtime memory footprint:
	或者，在已知设备不能热插拔的常见情况下、
	probe()例程可以存在于init部分，以减少驱动程序的运行时内存占用：
	
		int platform_driver_probe(struct platform_driver *drv,
				  int (*probe)(struct platform_device *))


### Device Enumeration
	~~~~~~~~~~~~~~~~~~
	As a rule, platform specific (and often board-specific) setup code will register platform devices:
	一般来说，平台特定的（通常是板子特定的）启动代码将注册平台设备：
	
		int platform_device_register(struct platform_device *pdev);
	
		int platform_add_devices(struct platform_device **pdevs, int ndev);
	
	The general rule is to register only those devices that actually exist, but in some cases extra devices might be registered.
	For example, a kernel might be configured to work with an external network adapter that might not be populated on all boards,
	or likewise to work with an integrated controller that some boards might not hook up to any peripherals.
	一般的规则是只注册那些实际存在的设备，但是在某些情况下，额外的设备可能被注册。
	例如，一个内核可能被配置为与一个外部网络适配器一起工作，而这个网络适配器可能不是在所有的板子上都有的、
	或者同样地，一些板子可能没有连接到任何外围设备，而要与一个集成控制器一起工作。


	In some cases, boot firmware will export tables describing the devices that are populated on a given board.
	Without such tables, often the only way for system setup code to set up the correct devices is to build a kernel for a specific target board.
	Such board-specific kernels are common with embedded and custom systems development.
	在某些情况下，启动固件会输出描述特定电路板上的设备的表格。
	如果没有这样的表格，系统设置代码设置正确设备的唯一方法就是为特定的目标板建立一个内核。
	这种针对特定板子的内核在嵌入式和定制系统开发中很常见。


	In many cases, the memory and IRQ resources associated with the platform device are not enough to let the device's driver work.
	Board setup code will often provide additional information using the device's platform_data field to hold additional information.
	在许多情况下，与平台设备相关的内存和IRQ资源不足以让设备的驱动程序工作。
	板卡启动代码通常会使用设备的platform_data字段来保存额外的信息。


	Embedded systems frequently need one or more clocks for platform devices, which are normally kept off until they're actively needed (to save power).
	System setup also associates those clocks with the device, so that that calls to clk_get(&pdev->dev, clock_name) return them as needed.
	嵌入式系统经常需要一个或多个平台设备的时钟，这些时钟通常在主动需要之前是关闭的（以节省电力）。
	系统设置也将这些时钟与设备联系起来，这样，调用clk_get(&pdev->dev, clock_name)就可以根据需要返回这些时钟。


### Legacy Drivers:  Device Probing
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Some drivers are not fully converted to the driver model, because they take on a non-driver role:
	the driver registers its platform device, rather than leaving that for system infrastructure.
	Such drivers can't be hotplugged or coldplugged, since those mechanisms require device creation to be in a different system component than the driver.
	有些驱动没有完全转换为驱动模型，因为它们承担了非驱动的角色：
	驱动程序注册它的平台设备，而不是把它留给系统基础设施。
	这样的驱动程序不能被热插拔或冷插拔，因为这些机制要求设备创建在与驱动程序不同的系统组件中。


	The only "good" reason for this is to handle older system designs which,
	like original IBM PCs, rely on error-prone "probe-the-hardware" models for hardware configuration.
	Newer systems have largely abandoned that model, in favor of bus-level support for dynamic configuration (PCI, USB),
	or device tables provided by the boot firmware (e.g. PNPACPI on x86).
	There are too many conflicting options about what might be where, and even educated guesses by an operating system will be wrong often enough to make trouble.
	这样做的唯一 "好 "理由是为了处理旧的系统设计、
	像最初的IBM PC一样，依靠容易出错的 "探测硬件 "模式进行硬件配置。
	新的系统在很大程度上放弃了这种模式，而采用总线级的动态配置支持（PCI、USB）、
	或由启动固件提供的设备表（例如X86上的PNPACPI）。
	关于什么东西可能在哪里，有太多相互冲突的选择，即使是操作系统的有根据的猜测也会经常出错，从而造成麻烦。


	This style of driver is discouraged.
	If you're updating such a driver, please try to move the device enumeration to a more appropriate location, outside the driver.
	This will usually be cleanup, since such drivers tend to already have "normal" modes,
	such as ones using device nodes that were created by PNP or by platform device setup.
	不建议使用这种风格的驱动。
	如果你正在更新这样的驱动程序，请尝试将设备枚举移到一个更合适的位置，在驱动程序之外。
	这通常是清理，因为这些驱动程序往往已经有 "正常 "模式、
	例如，使用PNP或平台设备设置创建的设备节点的模式。
	
	None the less, there are some APIs to support such legacy drivers.
	Avoid using these calls except with such hotplug-deficient drivers.
	尽管如此，还是有一些API来支持这种传统的驱动程序。
	避免使用这些调用，除非使用这种有热拔插缺陷的驱动程序。
	
		struct platform_device *platform_device_alloc(
				const char *name, int id);
	
	You can use platform_device_alloc() to dynamically allocate a device, which you will then initialize with resources and platform_device_register().
	A better solution is usually:
	你可以使用platform_device_alloc()来动态分配一个设备，然后用资源和platform_device_register()来初始化它。
	一个更好的解决方案通常是：
	
		struct platform_device *platform_device_register_simple(
				const char *name, int id,
				struct resource *res, unsigned int nres);
	
	You can use platform_device_register_simple() as a one-step call to allocate and register a device.
	你可以使用platform_device_register_simple()作为第一步调用来分配和注册一个设备。

### Device Naming and Driver Binding
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The platform_device.dev.bus_id is the canonical name for the devices.
	It's built from two components:
	platform_device.dev.bus_id是设备的典范名称。
	它是由两个部分组成的：
	
		* platform_device.name ... which is also used to for driver matching.
		* platform_device.name ......这也被用来进行驱动匹配。
	
		* platform_device.id ... the device instance number, or else "-1" to indicate there's only one.
		* platform_device.id ......设备实例编号，否则就用"-1"表示只有一个。
	
	These are concatenated, so name/id "serial"/0 indicates bus_id "serial.0", and "serial/3" indicates bus_id "serial.3";
	both would use the platform_driver named "serial".  While "my_rtc"/-1 would be bus_id "my_rtc" (no instance id) and use the platform_driver called "my_rtc".
	这些都是串联的，所以名称/id "serial"/0表示总线_id "serial.0"，"serial/3 "表示总线_id "serial.3"；
	两者都将使用名为 "serial "的平台驱动程序。 而 "my_rtc"/-1表示总线ID为 "my_rtc"（没有实例ID），并使用名为 "my_rtc "的平台驱动。
	
	Driver binding is performed automatically by the driver core, invoking driver probe() after finding a match between device and driver.
	If the probe() succeeds, the driver and device are bound as usual.
	There are three different ways to find such a match:
	驱动程序的绑定是由驱动内核自动执行的，在找到设备和驱动程序之间的匹配后，调用驱动probe（）。
	如果probe()成功，驱动和设备就会像平常一样被绑定。
	有三种不同的方法来寻找这种匹配：
	
		- Whenever a device is registered, the drivers for that bus are checked for matches.
		  Platform devices should be registered very early during system boot.
		- 每当一个设备被注册，该总线的驱动就会被检查是否匹配。
		  平台设备应该在系统启动时很早就被注册。
	
		- When a driver is registered using platform_driver_register(), all unbound devices on that bus are checked for matches.
		  Drivers usually register later during booting, or by module loading.
		- 当使用platform_driver_register()注册一个驱动程序时，该总线上所有未绑定的设备都会被检查是否匹配。
		  驱动程序通常在启动时或通过模块加载时注册。
	
		- Registering a driver using platform_driver_probe() works just like using platform_driver_register(),
		  except that the driver won't be probed later if another device registers.
		  (Which is OK, since this interface is only for use with non-hotpluggable devices.)
		- 使用platform_driver_probe()注册一个驱动程序的工作方式与使用platform_driver_register()一样、
		  除了如果有其他设备注册，该驱动将不会被探测到。
		  (这很好，因为这个接口只适用于非热插拔设备)。

### Early Platform Devices and Drivers
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The early platform interfaces provide platform data to platform device drivers early on during the system boot.
	The code is built on top of the early_param() command line parsing and can be executed very early on.
	早期的平台接口在系统启动时就向平台设备驱动程序提供平台数据。
	这些代码建立在early_param()命令行解析的基础上，可以在很早的时候执行。
	
	Example: "earlyprintk" class early serial console in 6 steps
	例子： "earlyprintk "类早期串行控制台的6个步骤
	
	1. Registering early platform device data
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The architecture code registers platform device data using the function early_platform_add_devices().
	In the case of early serial console this should be hardware configuration for the serial port.
	Devices registered at this point will later on be matched against early platform drivers.
	架构代码使用函数 early_platform_add_devices()注册平台设备数据。
	在早期串行控制台的情况下，这应该是串行端口的硬件配置。
	在这一点上注册的设备将在以后与早期平台驱动程序相匹配。
	
	2. Parsing kernel command line
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The architecture code calls parse_early_param() to parse the kernel command line.
	This will execute all matching early_param() callbacks.
	User specified early platform devices will be registered at this point.
	For the early serial console case the user can specify port on the kernel command line as "earlyprintk=serial.0" where "earlyprintk" is the class string,
	"serial" is the name of the platfrom driver and 0 is the platform device id. If the id is -1 then the dot and the id can be omitted.
	架构代码调用parse_early_param()来解析内核的命令行。
	这将执行所有匹配的early_param()回调。
	用户指定的早期平台设备将在这时被注册。
	对于早期串行控制台的情况，用户可以在内核命令行中指定端口为 "earlyprintk=serial.0"，其中 "earlyprintk "是类字符串、
	"serial "是平台驱动程序的名称，0是平台设备ID。如果id是-1，那么点和id可以省略。
	
	3. Installing early platform drivers belonging to a certain class
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The architecture code may optionally force registration of all early platform drivers belonging to a certain class using the function early_platform_driver_register_all(). 
	User specified devices from step 2 have priority over these.
	This step is omitted by the serial driver example since the early serial driver code should be disabled unless the user has specified port on the kernel command line.
	架构代码可以选择使用函数 early_platform_driver_register_all()强制注册所有属于某个类别的早期平台驱动。
	第2步中用户指定的设备比这些设备有优先权。
	串行驱动的例子省略了这一步，因为除非用户在内核命令行中指定了端口，否则早期串行驱动代码应该被禁用。
	
	4. Early platform driver registration
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Compiled-in platform drivers making use of early_platform_init() are automatically registered during step 2 or 3.
	The serial driver example should use early_platform_init("earlyprintk", &platform_driver).
	使用early_platform_init()编译的平台驱动在步骤2或3中被自动注册。
	串行驱动的例子应该使用 early_platform_init("earlyprintk", &platform_driver)。
	
	5. Probing of early platform drivers belonging to a certain class
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The architecture code calls early_platform_driver_probe() to match registered early platform devices associated with a certain class with registered early platform drivers.
	Matched devices will get probed().
	This step can be executed at any point during the early boot.
	As soon as possible may be good for the serial port case.
	架构代码调用early_platform_driver_probe()，将与某一类别相关的注册早期平台设备与注册早期平台驱动进行匹配。
	匹配的设备将得到探测（）。
	这个步骤可以在早期启动的任何时候执行。
	对于串行端口的情况来说，越快越好。
	
	6. Inside the early platform driver probe()
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	The driver code needs to take special care during early boot, especially when it comes to memory allocation and interrupt registration.
	The code in the probe() function can use is_early_platform_device() to check if it is called at early platform device or at the regular platform device time.
	The early serial driver performs register_console() at this point.
	驱动程序代码在早期启动时需要特别注意，特别是在内存分配和中断注册时。
	probe()函数中的代码可以使用is_early_platform_device()来检查它是在早期平台设备还是在常规平台设备时间被调用。
	早期的串行驱动在这时执行register_console()。
	
	For further information, see <linux/platform_device.h>.
	更多信息请参见<linux/platform_device.h>。