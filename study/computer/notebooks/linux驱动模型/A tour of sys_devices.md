## # A tour of /sys/devices
June 3, 2015
This article was contributed by Neil Brown
[link](https://lwn.net/Articles/646617/)


Modern Linux systems have a directory tree at /sys/devices that contains information about all of the "devices" represented in the device model. Having [clarified](https://lwn.net/Articles/645810/) exactly what each of "devices", "buses", and "classes" are (or maybe what they aren't), I am now in a position to address a shortcoming I had to admit in a [recent article](https://lwn.net/Articles/604413/) where I stated that /sys/devices "has a structure that, in all honesty, is rather hard to describe".
现代 Linux 系统在 /sys/devices 处有一个目录树，其中包含有关设备模型中表示的所有“devices”的信息。