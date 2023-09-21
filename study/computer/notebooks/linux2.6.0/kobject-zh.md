## 0.简介
kobject 基础架构执行基本的对象管理，大型数据结构和子系统可以利用这些管理，而不是重新实现类似的功能。这些功能主要涉及:
- 对象引用计数。
- 维护对象列表（集）。
- 对象集上锁。
- 用户空间显示。

该基础架构由许多对象类型组成，以支持这些功能。下文将详细介绍这些对象的编程接口，此处将作简要介绍：
- kobjects  一个简单的对象。
- kset  某种类型的一组对象。
- ktype  一种通用类型对象的辅助工具集。
- subsystem  一个控制多个 ksets 的对象。

kobject 基础架构与 sysfs 文件系统关系密切。每个在 kobject 核心注册的 kobject 都会在 sysfs 中获得一个目录。然后就可以导出 kobject 的属性。更多信息请参阅 Documentation/filesystems/sysfs.txt。

kobject 基础架构提供了灵活的编程接口、
并允许在未注册的情况下使用 kobjects 和 ksets（即不使用 sysfs 表示）。下文将对此进行介绍。