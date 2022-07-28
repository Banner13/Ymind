
[The Yocto Project](https://docs.yoctoproject.org/4.0.1/)



###4 源目录结构
	源目录由许多文件、目录和子目录组成；了解它们的位置和内容是有效使用 Yocto 项目的关键。本章介绍源目录并提供有关这些文件和目录的信息。
	有关如何在开发系统上建立本地源目录的信息，请参阅 Yocto 项目开发任务手册中的“定位 Yocto 项目源文件”部分。
<pre>Note
OpenEmbedded 构建系统不支持包含空格的文件或目录名称。确保您使用的源目录不包含这些类型的名称。
</pre>

####4.1 顶层核心组件
	本节介绍源目录的顶级组件。

#####4.1.1 bitbake/
	该目录包含一个 BitBake 的副本以方便使用。该副本通常与 BitBake 项目中当前稳定的 BitBake 版本相匹配。元数据解释器 BitBake 读取 Yocto 项目元数据并运行由该数据定义的任务。失败通常是由元数据中的错误引起的，而不是由 BitBake 本身引起的。
	当您运行 bitbake 命令时，主 BitBake 可执行文件（位于 bitbake/bin/ 目录中）将启动。获取环境设置脚本（即 oe-init-build-env）会将 scripts/ 和 bitbake/bin/ 目录（按此顺序）放入 shell 的 PATH 环境变量中。
	有关 BitBake 的更多信息，请参阅 BitBake 用户手册。

#####4.1.2 build/
	此目录包含用户配置文件和 OpenEmbedded 构建系统在其标准配置中生成的输出，其中源树与输出相结合。构建目录最初是在您获取 OpenEmbedded 构建环境设置脚本（即 oe-init-build-env）时创建的。
	还可以通过在获取设置脚本时提供目录名称来将输出和配置文件放置在与源目录不同的目录中。有关从本地源目录文件（通常描述为“树外”构建）分离输出的信息，请参阅“oe-init-build-env”部分。

#####4.1.3 documentation/
	该目录包含 Yocto Project 文档的源代码以及允许您生成手册的 PDF 和 HTML 版本的模板和工具。每本手册都包含在其自己的子文件夹中；例如，本参考手册的文件位于 ref-manual/ 目录中。

#####4.1.4 meta/
	此目录包含最小的底层 OpenEmbedded-Core 元数据。该目录包含严格模拟目标（qemux86、qemuarm 等）的配方、通用类和机器配置。

#####4.1.5 meta-poky/
	在 meta/ 内容之上设计，这个目录添加了足够的元数据来定义 Poky 参考分布。

#####4.1.6 meta-yocto-bsp/
	此目录包含 Yocto 项目参考硬件板支持包 (BSP)。有关 BSP 的更多信息，请参阅 Yocto 项目板支持包开发人员指南。

#####4.1.7 meta-selftest/
	此目录添加 OpenEmbedded 自测使用的附加配方和附加文件，以验证构建系统的行为。除非您想运行自测，否则您不必将此层添加到您的 bblayers.conf 文件中。

#####4.1.8 meta-skeleton/
	此目录包含 BSP 和内核开发的模板配方。

#####4.1.9 scripts/
	此目录包含在 Yocto 项目环境中实现额外功能的各种集成脚本（例如 QEMU 脚本）。 oe-init-build-env 脚本将此目录添加到 shell 的 PATH 环境变量中。
	scripts 目录包含有助于回馈 Yocto 项目的有用脚本，例如 create-pull-request 和 send-pull-request。

#####4.1.10 oe-init-build-env/
	此脚本设置 OpenEmbedded 构建环境。在 shell 中使用 source 命令运行此脚本会更改 PATH 并根据当前工作目录设置其他核心 BitBake 变量。在运行 BitBake 命令之前，您需要运行环境设置脚本。该脚本使用脚本目录中的其他脚本来完成大部分工作。
	当你运行这个脚本时，你的 Yocto 项目环境就设置好了，一个构建目录被创建，你的工作目录变成了构建目录，你会看到一些关于下一步做什么的简单建议，包括一些可能的目标列表建造。这是一个例子：
<pre>$ source oe-init-build-env

### Shell environment set up for builds. ###

You can now run 'bitbake <target>'

Common targets are:
    core-image-minimal
    core-image-sato
    meta-toolchain
    meta-ide-support

You can also run generated QEMU images with a command like 'runqemu qemux86-64'
</pre>

	oe-init-build-env 脚本的默认输出来自 conf-notes.txt 文件，该文件位于源目录的 meta-poky 目录中。如果您设计自定义发行版，则可以包含您自己的此配置文件版本，以提及您的发行版定义的目标。有关详细信息，请参阅 Yocto 项目开发任务手册中的“创建自定义模板配置目录”部分。
	默认情况下，在没有 Build Directory 参数的情况下运行此脚本会在您当前的工作目录中创建 build/ 目录。如果在获取脚本时提供 Build Directory 参数，则指示 OpenEmbedded 构建系统创建您选择的构建目录。例如，以下命令在源目录之外创建一个名为 mybuilds/ 的构建目录：
<pre>$ source oe-init-build-env ~/mybuilds</pre>

	OpenEmbedded 构建系统使用模板配置文件，这些文件默认位于源目录的 meta-poky/conf/ 目录中。有关详细信息，请参阅 Yocto 项目开发任务手册中的“创建自定义模板配置目录”部分。
<pre>Note
OpenEmbedded 构建系统不支持包含空格的文件或目录名称。如果您尝试从文件名或目录名中包含空格的源目录运行 oe-init-build-env 脚本，则该脚本会返回一个错误，指示没有此类文件或目录。请务必使用名称中不含空格的源目录。
</pre>

#####4.1.11 LICENSE, README, and README.hardware
	这些文件是标准的顶级文件。
