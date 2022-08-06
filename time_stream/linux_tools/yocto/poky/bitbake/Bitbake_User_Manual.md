[原文地址](https://docs.yoctoproject.org/bitbake/2.0/index.html)

[TOC]
###1 概述

	欢迎使用 BitBake 用户手册。本手册提供了 BitBake 工具的相关信息。这些信息会尽量避免与使用了 BitBake 的构建系统相关，例如 OpenEmbedded 和 Yocto 项目。但在某些情况下，手册中使用了系统内容中的场景或示例来帮助理解。对于这些情况，手册中清楚地说明了其上下文。

####1.1 简介

	从根本上说，BitBake 是一个通用的任务执行引擎，允许 shell 和 Python 任务在复杂的任务间依赖约束下高效、并行运行。 BitBake 的主要用户之一，OpenEmbedded，采用这个核心并使用面向任务的方法构建嵌入式 Linux 软件堆栈。

	从概念上讲，BitBake 在某些方面类似于 GNU Make，但有显着差异：
        I BitBake 根据提供的构建任务的元数据执行任务。元数据存储在配方 (.bb) 和相关配方“附加” (.bbappend) 文件、配置 (.conf) 和底层包含 (.inc) 文件以及类 (.bbclass) 文件中。元数据为 BitBake 提供了有关要运行哪些任务以及这些任务之间的依赖关系的说明。
        II BitBake 包含一个获取器库，用于从本地文件、源代码控制系统或网站等不同位置获取源代码。
        III 每个要构建的单元（例如一个软件）的指令被称为“配方”文件，并包含有关该单元的所有信息（依赖关系、源文件位置、校验和、描述等）。
        IV BitBake 包含一个客户端/服务器抽象，可以从命令行使用，也可以通过 XML-RPC 用作服务，并具有多种不同的用户界面。

####1.2 历史和目标

	BitBake 最初是 OpenEmbedded 项目的一部分。它的灵感来自于 Gentoo Linux 发行版使用的 Portage 包管理系统。 2004 年 12 月 7 日，OpenEmbedded 项目组成员 Chris Larson 将项目分成两个不同的部分：
        I BitBake，一个通用的任务执行器。
        II OpenEmbedded，BitBake 使用的元数据集。

    今天，BitBake 是 OpenEmbedded 项目的主要基础，该项目被用于构建和维护 Linux 发行版，例如在 Yocto 项目的保护下开发的 Poky Reference Distribution。

    在 BitBake 之前，没有其他构建工具能够充分满足所有的嵌入式 Linux 发行版的需求。传统桌面 Linux 发行版使用的所有构建系统都缺乏重要的功能，并且在嵌入式领域流行的基于 Buildroot 的临时系统都没有可扩展性或可维护性。

    BitBake 的一些重要的初衷是：
        I 处理交叉编译。
        II 处理包间依赖关系（在目标架构构建时、本机架构构建时，还有运行时）。
        III 支持在给定包中运行任意数量的任务，包括但不限于获取上游源数据、解包、打补丁、配置等。
        IV 无需指定构建和目标系统的 Linux 发行版。
        V 与架构无关。
        VI 支持多种构建和目标操作系统（例如 Cygwin、BSD 等）。是独立的，而不是紧密集成到构建机器的根文件系统中。
        VII 处理目标架构、操作系统、发行版和机器上的条件元数据。
        VIII 为本地元数据和操作包提供易于使用的工具。
        IX 易于使用 BitBake 在多个项目之间进行协作以进行构建。
        X 提供一种继承机制以在许多包之间共享通用元数据。

    随着时间的推移，很明显需要一些进一步的要求：
        I 处理基本配方的变体（例如 native、sdk 和 multilib）。
        II 将元数据分层并允许层进行扩展或覆盖其他层。
        III 允许将给定的一组输入变量表示为校验和。基于该校验和，允许使用预构建组件加速构建。

    BitBake满足所有原始要求，并通过对基本功能进行扩展以实现其他要求。灵活性和力量一直是首要任务。BitBake 具有高度可扩展性，并支持嵌入式 Python 代码和任意任务的执行。

####1.3 概念

    BitBake 是一个用 Python 语言编写的程序。在最高级别，BitBake 解释元数据，决定需要运行哪些任务，并执行这些任务。BitBake 控制软件的构建方式与 GNU Make 类似。 GNU Make 通过“makefile”实现控制，而 BitBake 使用“recipes”。
    BitBake 通过允许定义更复杂的任务（例如组装整个嵌入式 Linux 发行版）扩展了 GNU Make 等简单工具的功能。
    本节的其余部分介绍了几个应该理解的概念，以便更好地利用 BitBake 的强大功能。

#####1.3.1 配方
        BitBake Recipes 由文件扩展名 .bb 表示，是最基本的元数据文件。这些配方文件为 BitBake 提供以下内容：
            I 关于包的描述信息（作者、主页、许可证等）。
            II 配方的版本。
            III 现有依赖项（构建和运行时依赖项）。
            IV 源代码所在的位置以及如何获取它。
            V 源代码是否需要任何补丁，在哪里可以找到它们，以及如何应用它们。
            VI 如何配置和编译源代码。
            VII 如何将生成的工件组装成一个或多个可安装包。
            VIII 在目标机器上安装创建的包或包的位置。

        在 BitBake 的上下文中，或任何使用 BitBake 作为其构建系统的项目中，具有 .bb 扩展名的文件被称为配方。
        // 注
        “包”一词也常用于描述配方。但是，由于使用相同的词来描述项目的打包输出，因此最好保留一个描述性术语 - “配方”。换句话说，单个“配方”文件完全能够生成许多相关但可单独安装的“包”。事实上，这种能力相当普遍。
        // 注尾

#####1.3.2 配置文件
        由 .conf 扩展名表示的配置文件定义了管理项目构建过程的各种配置变量。这些文件分为定义机器配置、发行版配置、可能的编译器调整、一般通用配置和用户配置的几个区域。主要配置文件是示例 bitbake.conf 文件，它位于 BitBake 源代码树 conf 目录中。

#####1.3.3 类
        由 .bbclass 扩展名表示的类文件包含有助于在元数据文件之间共享信息。 BitBake 源代码树目前带有一个名为 base.bbclass 的类元数据文件。您可以在 classes 目录中找到此文件。 base.bbclass 类文件很特殊，因为它总是自动包含在所有配方和类中。此类包含标准基本任务的定义，例如获取、解包、配置（默认为空）、编译（运行任何存在的 Makefile）、安装（默认为空）和打包（默认为空）。这些任务通常被项目开发过程中添加的其他类覆盖或扩展。

#####1.3.4 层
        层允许您将不同类型的自定义相互隔离。虽然您可能会发现在处理单个项目时将所有内容都放在一个层中很诱人，但元数据越模块化，就越容易应对未来的变化。
        为了说明如何使用层来保持模块化，请考虑您可能进行的自定义以支持特定的目标机器。这些类型的定制通常位于一个特殊层，而不是一个通用层，称为板支持包 (BSP) 层。此外，例如，机器定制应该与支持新 GUI 环境的配方和元数据隔离开来。这种情况为您提供了几层：一层用于机器配置，一层用于 GUI 环境。然而，重要的是要理解，BSP 层仍然可以对 GUI 环境层中的配方进行特定于机器的添加，而不会因这些特定于机器的更改而污染 GUI 层本身。您可以通过作为 BitBake 附加 (.bbappend) 文件的配方来完成此操作。

#####1.3.5 附加文件
        附加文件（具有 .bbappend 文件扩展名的文件）扩展或覆盖现有配方文件中的信息。
        BitBake 期望每个附加文件都有一个相应的配方文件。此外，附加文件和相应的配方文件必须使用相同的根文件名。文件名只能在使用的文件类型后缀上有所不同（例如 formfactor_0.0.bb 和 formfactor_0.0.bbappend）。
        附加文件中的信息扩展或覆盖了底层、类似名称的配方文件中的信息。
        命名附加文件时，可以使用“%”通配符来匹配配方名称。例如，假设您有一个名为如下的附加文件：
            busybox_1.21.%.bbappend
        该附加文件将匹配任何busybox_1.21.x.bb 版本的配方。因此，附加文件将匹配以下配方名称：
            busybox_1.21.1.bb
            busybox_1.21.2.bb
            busybox_1.21.3.bb
        // 注
        “%”字符的使用受到限制，因为它只能直接在附加文件名称的.bbappend 部分前面使用。您不能在名称的任何其他位置使用通配符。
        // 注尾
        如果busybox 配方更新为busybox_1.3.0.bb，附加名称将不匹配。但是，如果您将附加文件命名为busybox_1.%.bbappend，那么您将得到一个匹配项。
        在最一般的情况下，您可以将附加文件命名为简单的busybox_%.bbappend 以完全独立于版本。

####1.4 获取 BitBake

    您可以通过几种不同的方式获取 BitBake：
        I 克隆 BitBake：使用 Git 克隆 BitBake 源代码存储库是获取 BitBake 的推荐方法。克隆存储库可以轻松修复错误并访问稳定分支和主分支。克隆 BitBake 后，应使用最新的稳定分支进行开发，因为主分支用于 BitBake 开发，可能包含不太稳定的更改。
        您通常需要与您正在使用的元数据匹配的 BitBake 版本。元数据通常向后兼容，但不向前兼容。
        这是一个克隆 BitBake 存储库的示例：
            $ git clone git://git.openembedded.org/bitbake
        此命令将 BitBake Git 存储库克隆到名为 bitbake 的目录中。或者，如果您想将新目录称为 bitbake 以外的名称，您可以在 git clone 命令之后指定一个目录。这是一个将目录命名为 bbdev 的示例：
            $ git clone git://git.openembedded.org/bitbake bbdev

        II 使用您的分发包管理系统安装：不建议使用此方法，因为您的分发包管理系统提供的 BitBake 版本在大多数情况下落后 BitBake 存储库快照几个版本。

        III 拍摄 BitBake 的快照：从源代码存储库下载 BitBake 的快照可让您访问 BitBake 的已知分支或版本。
        // 注
        如前所述，克隆 Git 存储库是获取 BitBake 的首选方法。随着补丁添加到稳定的分支，克隆存储库可以更容易地更新。
        // 注尾

        以下示例下载 BitBake 版本 1.17.0 的快照：
            $ wget https://git.openembedded.org/bitbake/snapshot/bitbake-1.17.0.tar.gz
            $ tar zxpvf bitbake-1.17.0.tar.gz
        使用 tar 实用程序解压缩 tarball 后，您将拥有一个名为 bitbake-1.17.0 的目录。

        IV 使用随您的构建检查附带的 BitBake：获取 BitBake 副本的最后一种可能性是，它已经随您检查更大的基于 BitBake 的构建系统，例如 Poky。您可以检查整个构建系统，而不是手动检查各个层并将它们粘合在一起。打包时已经包含一个经过全面测试与其他组件的兼容性的 BitBake 版本。有关如何检查特定基于 BitBake 的构建系统的信息，请查阅该构建系统的支持文档。

####1.5 BitBake 命令

    bitbake 命令是 BitBake 工具的主要接口。本节介绍 BitBake 命令语法并提供几个运行示例。

#####1.5.1 用法和语法
        以下是 BitBake 的用法和语法：
    $ bitbake -h
    用法：bitbake [options] [recipename/target recipe:do_task ...]

    为给定的一组目标配方（.bb 文件）执行指定的任务（默认为“构建”）。
    假设在 cwd 或 BBPATH 中有一个 conf/bblayers.conf 可用，它将提供层、BBFILES 和其他配置信息。

        选项：
        --version 显示程序的版本号并退出
        -h, --help 显示此帮助信息并退出
        -b BUILDFILE, --buildfile=BUILDFILE
            直接从特定的 .bb 配方执行任务。
            警告：不会处理来自其他配方的任何依赖项。
        -k, --continue 出错后尽可能继续。
                虽然失败的目标和任何依赖它的东西都不能被建造，尽可能在建造之前停止。
        -f, --force 强制指定的目标/任务运行（使任何现有的文件戳无效）。
        -c CMD, --cmd=CMD 指定要执行的任务。 可用的确切选项取决于元数据。
                一些示例可能是 'compile' 或 'populate_sysroot' 或 'listtasks' 可能会给出可用任务的列表。
        -C INVALIDATE_STAMP，--clear-stamp=INVALIDATE_STAMP
                指定例如'compile'任务的标记无效， 然后运行目标的默认任务。
        -r PREFILE, --read=PREFILE
                在 bitbake.conf 之前读取指定文件。
        -R POSTFILE，--postread=POSTFILE
                在 bitbake.conf 之后读取指定的文件。
        -v, --verbose 启用 shell 任务跟踪（使用“set -x”）。
                同时将 bb.note(...) 消息打印到标准输出（此外，将它们写入 ${T}/log.do_<task>)。
        -D, --debug 提高调试级别。
                您可以多次指定它。
                -D 将调试级别设置为 1，其中仅将 bb.debug(1, ...) 消息打印到标准输出；
                -DD 将调试级别设置为 2，其中同时打印 bb.debug(1, ...) 和 bb.debug(2, ...) 消息，以此类推。
                如果没有 -D，则不会打印任何调试消息。
                请注意，-D 仅影响到标准输出的输出。无论调试级别如何，所有调试消息都写入 ${T}/log.do_taskname。
        -q, --quiet 向终端输出较少的日志消息数据。你可以多次指定。
        -n, --dry-run 不执行，只做动作。
        -S SIGNATURE_HANDLER, --dump-signatures=SIGNATURE_HANDLER
                转出签名构造信息，不执行任何任务。
                SIGNATURE_HANDLER 参数传递给处理程序。
                两个常用值是 none 和 printdiff，但处理程序可以定义更多/更少。
                none 意味着只转储签名，printdiff 意味着将转储的签名与缓存的签名进行比较。
        -p, --parse-only 解析 BB 配方后退出。
        -s, --show-versions 显示所有配方的当前和首选版本。
        -e, --environment 显示全局或每个配方环境以及有关变量设置/更改位置的信息。
        -g, --graphviz 以dot语法保存指定目标的依赖关系树信息。
        -I EXTRA_ASSUME_PROVIDED，--ignore-deps=EXTRA_ASSUME_PROVIDED
                假设这些依赖项不存在并且已经提供（相当于 ASSUME_PROVIDED）。 有助于使依赖图更具吸引力。
        -l DEBUG_DOMAINS, --log-domains=DEBUG_DOMAINS
                显示指定日志记录域的调试日志记录
        -P, --profile 配置命令并保存报告。
        -u UI, --ui=UI 要使用的用户界面（knotty、ncurses、taskexp 或 teamcity - 默认为 knotty）。
        --token=XMLRPCTOKEN 指定连接到远程服务器时要使用的连接令牌。
        --revisions-changed 根据上游浮动修订是否已更改设置退出代码。
        --server-only 在没有 UI 的情况下运行 bitbake，仅启动服务器（cooker）进程。
        -B BIND, --bind=BIND 要绑定到的 bitbake xmlrpc 服务器的名称/地址
        -T SERVER_TIMEOUT, --idle-timeout=SERVER_TIMEOUT
                由于不活动而设置超时以卸载bitbake服务器，设置为-1表示不卸载，默认值：环境变量BB_SERVER_TIMEOUT。
        --no-setscene 不要运行任何场景任务。 sstate 将被忽略并构建所需的一切。
        --skip-setscene 如果它们将被执行，则跳过 setscene 任务。
                与 --no-setscene 不同，之前从 sstate 恢复的任务将被保留
        --setscene-only 只运行 setscene 任务，不运行任何实际任务。
        --remote-server=REMOTE_SERVER 连接到指定的服务器。
        -m, --kill-server 终止任何正在运行的 bitbake 服务器。
        --observe-only 作为仅观察客户端连接到服务器。
        --status-only 检查远程 bitbake 服务器的状态。
        -w WRITEEVENTLOG，--write-log=WRITEEVENTLOG
                将构建的事件日志写入 bitbake 事件 json 文件。 使用 ''（空字符串）自动分配名称。
        --runall=RUNALL 为指定目标的任务图中的任何配方运行指定的任务（即使它不会运行）。
        --runonly=RUNONLY 仅运行指定目标的任务图中的指定任务（以及这些任务可能具有的任何任务依赖项）。

#####1.5.2 示例

    本节提供一些示例，展示如何使用 BitBake。

######1.5.2.1 针对单个配方执行任务
        为单个配方文件执行任务相对简单。您指定有问题的文件，BitBake 会解析它并执行指定的任务。如果您不指定任务，BitBake 会执行默认任务，即“ build ”。 BitBake 这样做时遵循任务间依赖关系。
        以下命令在 foo_1.0.bb 配方文件上运行构建任务，这是默认任务：
            $ bitbake -b foo_1.0.bb
        以下命令对 foo.bb 配方文件运行 clean 任务：
            $ bitbake -b foo.bb -c clean
        // 注
        “-b”选项不会处理配方依赖关系。除了出于调试目的之外，建议您使用下一节中介绍的语法。
        // 注尾

######1.5.2.2 针对一组配方文件执行任务
        当想要管理多个 .bb 文件时，会引入许多额外的复杂性。显然，需要有一种方法来告诉 BitBake 哪些文件可用，以及哪些文件是您想要执行的。每个配方还需要有一种方法来表达其依赖关系，包括构建时和运行时。当多个配方提供相同的功能时，或者当一个配方有多个版本时，您必须有一种方法来表达配方偏好。
        bitbake 命令在不使用“–buildfile”或“-b”时只接受“PROVIDES”。你不能提供其他任何东西。默认情况下，配方文件通常“PROVIDES”其“packagename”，如下例所示：
            $ bitbake foo
        下一个示例“PROVIDES”包名称并使用“-c”选项告诉 BitBake 只执行 do_clean 任务：
            $ bitbake -c clean foo

######1.5.2.3 执行任务列表和配方组合
	当您指定多个目标时，BitBake 命令行支持为各个目标指定不同的任务。例如，假设您有两个目标（或配方）myfirstrecipe 和 mysecondrecipe，并且您需要 BitBake 为第一个配方运行 taskA，为第二个配方运行 taskB：
		$ bitbake myfirstrecipe:do_taskA mysecondrecipe:do_taskB

######1.5.2.4 生成依赖图
	BitBake 能够使用点语法生成依赖关系图。您可以使用 Graphviz 的点工具将这些图形转换为图像。
    生成依赖图时，BitBake 会将两个文件写入当前工作目录：
    	• task-depends.dot：显示任务之间的依赖关系。这些依赖项与 BitBake 的内部任务执行列表相匹配。
		• pn-buildlist：显示要构建的目标的简单列表。
	要停止依赖公共依赖，请使用 -I depend 选项，BitBake 从图中省略它们。忽略这些信息可以产生更易读的图表。这样，您可以从继承的类（例如 base.bbclass）中从图中删除 DEPENDS。
    以下是创建依赖图的两个示例。第二个示例省略了图中 OpenEmbedded 中常见的依赖：
    	$ bitbake -g foo
		$ bitbake -g -I virtual/kernel -I eglibc foo

######1.5.2.5 执行多配置构建
	BitBake 能够使用单个命令构建多个图像或包，其中不同的目标需要不同的配置（多个配置构建）。在这种情况下，每个目标都称为“multiconfig”。
	要完成多配置构建，您必须使用构建目录中的并行配置文件分别定义每个目标的配置。这些 multiconfig 配置文件的位置是特定的。它们必须驻留在名为 multiconfig 的 conf 子目录中的当前构建目录中。以下是两个单独目标的示例：

![](./1525_1.png)

	之所以需要这种文件层次结构，是因为在解析层之前不会构造 BBPATH 变量。因此，除非它位于当前工作目录中，否则无法将配置文件用作预配置文件。
	最低限度，每个配置文件必须定义机器和 BitBake 用于构建的临时目录。建议的做法是不要重叠构建期间使用的临时目录。
	除了每个目标的单独配置文件之外，您还必须启用 BitBake 以执行多个配置构建。通过在 local.conf 配置文件中设置 BBMULTICONFIG 变量来实现启用。例如，假设您在构建目录中定义了 target1 和 target2 的配置文件。 local.conf 文件中的以下语句使 BitBake 能够执行多个配置构建并指定两个额外的多重配置：
		BBMULTICONFIG = "target1 target2"
    一旦目标配置文件到位并启用 BitBake 以执行多个配置构建，请使用以下命令表单启动构建：
		$ bitbake [mc:multiconfigname:]target [[[mc:multiconfigname:]target] ... ]
    这是两个额外多重配置的示例：target1 和 target2：
    	$ bitbake mc::target mc:target1:target mc:target2:target

######1.5.2.6 启用多个配置构建依赖
	有时，多配置构建中的目标（多配置）之间可能存在依赖关系。例如，假设为了构建特定架构的映像，需要存在用于不同架构的另一个构建的根文件系统。换句话说，第一个 multiconfig 的映像取决于第二个 multiconfig 的根文件系统。这种依赖关系本质上是配方中构建一个 multiconfig 的任务依赖于构建另一个 multiconfig 的配方中任务的完成。
	要在多配置构建中启用依赖项，您必须使用以下语句形式在配方中声明依赖项：
    	task_or_package[mcdepends] = "mc:from_multiconfig:to_multiconfig:recipe_name:task_on_which_to_depend"
    为了更好地展示如何使用此语句，请考虑一个包含两个多重配置的示例：target1 和 target2：
    	image_task[mcdepends] = "mc:target1:target2:image2:rootfs_task"
    在此示例中，from_multiconfig 为“target1”，to_multiconfig 为“target2”。其配方包含 image_task 的镜像所执行的任务取决于用于构建 image2 的 rootfs_task 的完成，该镜像与“target2”multiconfig 相关联。
    设置此依赖项后，您可以使用 BitBake 命令构建“target1”multiconfig，如下所示：
    	$ bitbake mc:target1:image1
    此命令执行为“target1”multiconfig 创建 image1 所需的所有任务。由于依赖关系，BitBake 还通过 rootfs_task 执行“target2”多配置构建。
	拥有一个依赖于另一个构建的根文件系统的配方可能看起来没有那么有用。考虑对 image1 配方中的语句的这种更改：
    	image_task[mcdepends] = "mc:target1:target2:image2:image_task"
	在这种情况下，BitBake 必须为“target2”构建创建 image2，因为“target1”构建依赖于它。
	因为“target1”和“target2”为多个配置构建启用并且具有单独的配置文件，BitBake 将每个构建的工件放置在各自的临时构建目录中。

___
###2 执行
	运行 BitBake 的主要目的是生成某种输出，例如单个可安装包、内核、软件开发工具包，甚至是完整的、特定于板的可引导 Linux 映像，包括引导加载程序、内核和根文件系统。当然，您可以使用选项执行 bitbake 命令，使其执行单个任务、编译单个配方文件、捕获或清除数据，或者简单地返回有关执行环境的信息。
	本章描述了使用 BitBake 创建镜像时从头到尾的执行过程。使用以下命令形式启动执行过程：
		$ bitbake target
	有关 BitBake 命令及其选项的信息，请参阅“BitBake 命令”部分。

	Note
	在执行 BitBake 之前，您应该通过在项目的 local.conf 配置文件中设置 BB_NUMBER_THREADS 变量来利用构建主机上可用的并行线程执行。
	为您的构建主机确定此值的常用方法是运行以下命令：
		$ grep processor /proc/cpuinfo
    此命令返回考虑到超线程的处理器数量。因此，具有超线程的四核构建主机最有可能显示八个处理器，这是您随后将分配给 BB_NUMBER_THREADS 的值。
	一个可能更简单的解决方案是一些 Linux 发行版（例如 Debian 和 Ubuntu）提供 ncpus 命令。

####2.1 解析基础配置元数据
	BitBake 做的第一件事是解析基本配置元数据。基本配置元数据由项目的 bblayers.conf 文件（用于确定 BitBake 需要识别哪些层）、所有必要的 layer.conf 文件（每层一个）和 bitbake.conf 组成。数据本身有多种类型：
        • 食谱：有关特定软件的详细信息。
        • 类数据：通用构建信息的抽象（例如如何构建 Linux 内核）。
        • 配置数据：特定于机器的设置、策略决策等。配置数据充当将所有内容绑定在一起的粘合剂。
	layer.conf 文件用于构造关键变量，例如 BBPATH 和 BBFILES。 BBPATH 用于分别在 conf 和 classes 目录下搜索配置文件和类文件。 BBFILES 用于定位配方和配方附加文件（.bb 和 .bbappend）。如果没有 bblayers.conf 文件，则假定用户直接在环境中设置了 BBPATH 和 BBFILES。
	接下来，使用刚刚构建的 BBPATH 变量定位 bitbake.conf 文件。 bitbake.conf 文件还可以包含使用 include 或 require 指令的其他配置文件。
	在解析配置文件之前，BitBake 会查看某些变量，包括：
        • BB_ENV_PASSTHROUGH
        • BB_ENV_PASSTHROUGH_ADDITIONS
        • BB_PRESERVE_ENV
        • BB_ORIGENV
        • BITBAKE_UI
	此列表中的前四个变量与 BitBake 在任务执行期间如何处理 shell 环境变量有关。默认情况下，BitBake 会清理环境变量并提供对 shell 执行环境的严格控制。但是，通过使用前四个变量，您可以对允许 BitBake 在执行任务期间在 shell 中使用的环境变量进行控制。有关它们如何工作以及如何使用它们的更多信息，请参阅“将信息传递到构建任务环境”部分以及变量词汇表中有关这些变量的信息。

    基本配置元数据是全局的，因此会影响所有执行的配方和任务。

    BitBake 首先在当前工作目录中搜索可选的 conf/bblayers.conf 配置文件。该文件应包含一个 BBLAYERS 变量，该变量是一个以空格分隔的“层”目录列表。回想一下，如果 BitBake 找不到 bblayers.conf 文件，则假定用户已直接在环境中设置了 BBPATH 和 BBFILES 变量。

    对于此列表中的每个目录（层），都会定位并解析一个 conf/layer.conf 文件，其中 LAYERDIR 变量设置为找到该层的目录。这个想法是这些文件自动为给定的构建目录正确设置 BBPATH 和其他变量。

    然后 BitBake 期望在用户指定的 BBPATH 中的某处找到 conf/bitbake.conf 文件。该配置文件通常包含用于提取任何其他元数据的指令，例如特定于架构、机器、本地环境等的文件。

    BitBake .conf 文件中只允许使用变量定义和包含指令。一些变量直接影响 BitBake 的行为。这些变量可能是从环境中设置的，具体取决于前面提到的或在配置文件中设置的环境变量。 “变量词汇表”一章提供了完整的变量列表。

    在解析完配置文件后，BitBake 使用其基本的继承机制，即通过类文件来继承一些标准的类。当遇到负责获取该类的继承指令时，BitBake 会解析该类。

    始终包含 base.bbclass 文件。还包括在配置中使用 INHERIT 变量指定的其他类。 BitBake 在 BBPATH 路径下的 classes 子目录中搜索类文件，方式与配置文件相同。

    了解执行环境中使用的配置文件和类文件的一个好方法是运行以下 BitBake 命令：
    	$ bitbake -e > mybb.log

    检查 mybb.log 的顶部会显示执行环境中使用的许多配置文件和类文件。

    	Note
        您需要了解 BitBake 如何解析花括号。如果配方在函数中使用右花括号并且字符没有前导空格，则 BitBake 会产生解析错误。如果在 shell 函数中使用一对花括号，则右花括号不能位于没有前导空格的行首。

		这是导致 BitBake 产生解析错误的示例：
            fakeroot create_shar() {
               cat << "EOF" > ${SDK_DEPLOY}/${TOOLCHAIN_OUTPUTNAME}.sh
            usage()
            {
               echo "test"
               ######  The following "}" at the start of the line causes a parsing error ######
            }
            EOF
            }

            Writing the recipe this way avoids the error:
            fakeroot create_shar() {
               cat << "EOF" > ${SDK_DEPLOY}/${TOOLCHAIN_OUTPUTNAME}.sh
            usage()
            {
               echo "test"
               ###### The following "}" with a leading space at the start of the line avoids the error ######
             }
            EOF
            }

####2.2 定位和解析配方
	在配置阶段，BitBake 将设置 BBFILES。 BitBake 现在使用它来构造要解析的配方列表，以及要应用的任何附加文件 (.bbappend)。 BBFILES 是可用文件的空格分隔列表，并支持通配符。一个例子是：
		BBFILES = "/path/to/bbfiles/*.bb /path/to/appends/*.bbappend"

	BitBake 解析位于 BBFILES 中的每个配方和附加文件，并将各种变量的值存储到数据存储中。
		Note
        附加文件按照它们在 BBFILES 中遇到的顺序应用。

	对于每个文件，都会制作一份基本配置的新副本，然后逐行解析配方。任何继承语句都会导致 BitBake 使用 BBPATH 作为搜索路径查找并解析类文件 (.bbclass)。最后，BitBake 按顺序解析在 BBFILES 中找到的任何附加文件。

	一种常见的约定是使用配方文件名来定义元数据。例如，在 bitbake.conf 中，配方名称和版本用于设置变量 PN 和 PV：
		PN = "${@bb.parse.vars_from_file(d.getVar('FILE', False),d)[0] or 'defaultpkgname'}"
		PV = "${@bb.parse.vars_from_file(d.getVar('FILE', False),d)[1] or '1.0'}"

	在此示例中，名为“something_1.2.3.bb”的配方会将 PN 设置为“something”，将 PV 设置为“1.2.3”。

	当一个配方的解析完成时，BitBake 有一个配方定义的任务列表和一组由键和值组成的数据以及有关任务的依赖信息。

	BitBake 不需要所有这些信息。它只需要一小部分信息来决定配方。因此，BitBake 会缓存它感兴趣的值，而不存储其余信息。经验表明，重新解析元数据比尝试将其写入磁盘然后重新加载要快。

	在可能的情况下，后续 BitBake 命令会重复使用此配方信息缓存。该缓存的有效性是通过首先计算基本配置数据的校验和（参见 BB_HASHCONFIG_IGNORE_VARS）然后检查校验和是否匹配来确定的。如果该校验和与缓存中的内容匹配并且配方和类文件没有更改，则 BitBake 能够使用缓存。然后，BitBake 会重新加载有关配方的缓存信息，而不是从头开始重新解析它。

	配方文件集合的存在允许用户拥有多个包含相同包的 .bb 文件存储库。例如，人们可以轻松地使用它们来制作自己的上游存储库的本地副本，但可以进行不希望上游的自定义修改。这是一个例子：
		BBFILES = "/stuff/openembedded/*/*.bb /stuff/openembedded.modified/*/*.bb"
        BBFILE_COLLECTIONS = "upstream local"
        BBFILE_PATTERN_upstream = "^/stuff/openembedded/"
        BBFILE_PATTERN_local = "^/stuff/openembedded.modified/"
        BBFILE_PRIORITY_upstream = "5"
        BBFILE_PRIORITY_local = "10"

		Note
        层机制现在是收集代码的首选方法。虽然集合代码仍然存在，但它的主要用途是设置层优先级并处理层之间的重叠（冲突）。

####2.3 提供者
	假设 BitBake 已被指示执行一个目标并且所有配方文件都已被解析，BitBake 开始弄清楚如何构建目标。 BitBake 查看每个食谱的 PROVIDES 列表。 PROVIDES 列表是可以知道配方的名称列表。每个配方的 PROVIDES 列表是通过配方的 PN 变量隐式创建的，并通过配方的 PROVIDES 变量显式创建，这是可选的。

	当一个配方使用 PROVIDES 时，该配方的功能可以在一个或多个替代名称下找到，而不是隐式 PN 名称。例如，假设名为 keyboard_1.0.bb 的配方包含以下内容：
		PROVIDES += "fullkeyboard"

	这个配方的 PROVIDES 列表变为“keyboard”，这是隐式的，“fullkeyboard”，这是显式的。因此，keyboard_1.0.bb 中的功能可以在两个不同的名称下找到。

####2.4 偏好
	PROVIDES 列表只是找出目标配方的解决方案的一部分。因为目标可能有多个提供者，BitBake 需要通过确定提供者偏好来优先考虑提供者。

	一个目标具有多个提供程序的常见示例是“虚拟/内核”，它位于每个内核配方的 PROVIDES 列表中。每台机器通常通过在机器配置文件中使用类似于以下的行来选择最佳内核提供程序：
		PREFERRED_PROVIDER_virtual/kernel = "linux-yocto"

	默认的 PREFERRED_PROVIDER 是与目标同名的提供者。 BitBake 遍历它需要构建的每个目标，并使用此过程解决它们及其依赖关系。

	由于给定提供程序可能存在多个版本，因此了解如何选择提供程序变得复杂。 BitBake 默认为提供程序的最高版本。使用与 Debian 相同的方法进行版本比较。您可以使用 PREFERRED_VERSION 变量来指定特定版本。您可以使用 DEFAULT_PREFERENCE 变量来影响顺序。

	默认情况下，文件的首选项为“0”。将 DEFAULT_PREFERENCE 设置为“-1”使得配方不太可能被使用，除非它被明确引用。将 DEFAULT_PREFERENCE 设置为“1”可能会使用配方。 PREFERRED_VERSION 会覆盖任何 DEFAULT_PREFERENCE 设置。 DEFAULT_PREFERENCE 通常用于标记更新和更具实验性的配方版本，直到它们经过足够的测试被认为是稳定的。

	当给定配方有多个“版本”时，BitBake 默认选择最新版本，除非另有说明。如果有问题的配方的 DEFAULT_PREFERENCE 设置低于其他配方（默认为 0），则不会选择它。这允许维护配方文件存储库的个人或个人指定他们对默认选定版本的偏好。此外，用户可以指定他们的首选版本。

	如果第一个配方命名为 a_1.1.bb，则 PN 变量将设置为“a”，而 PV 变量将设置为 1.1。

	因此，如果存在名为 a_1.2.bb 的配方，BitBake 将默认选择 1.2。但是，如果您在 BitBake 解析的 .conf 文件中定义以下变量，则可以更改该首选项：
		PREFERRED_VERSION_a = "1.1"

		Note
        配方提供两个版本是很常见的——一个稳定的、编号的（和首选的）版本，以及一个从源代码存储库中自动签出的版本，该版本被认为更“前沿”，但只能显式选择。

		例如，在 OpenEmbedded 代码库中，有一个用于 BusyBox 的标准版本化配方文件，busybox_1.22.1.bb，但也有一个基于 Git 的版本，busybox_git.bb，它明确包含以下行
			DEFAULT_PREFERENCE = "-1"
		以确保始终首选编号的稳定版本，除非开发人员另有选择。

####2.5 依赖关系
	每个目标 BitBake 构建都包含多个任务，例如获取、解包、修补、配置和编译。为了在多核系统上获得最佳性能，BitBake 将每个任务视为具有自己的一组依赖项的独立实体。

	依赖关系是通过几个变量定义的。您可以在本手册末尾附近的变量词汇表中找到有关 BitBake 使用的变量的信息。在基本级别上，知道 BitBake 在计算依赖项时使用 DEPENDS 和 RDEPENDS 变量就足够了。

	有关 BitBake 如何处理依赖项的更多信息，请参阅依赖项部分。

####2.6 任务列表
	根据生成的提供者列表和依赖信息，BitBake 现在可以准确计算它需要运行哪些任务以及运行它们需要的顺序。执行任务部分有更多关于 BitBake 如何选择接下来要执行的任务的信息。

	现在，构建开始于 BitBake 将线程分叉到 BB_NUMBER_THREADS 变量中设置的限制。只要有准备运行的任务、这些任务的所有依赖项都满足并且没有超过线程阈值，BitBake 就会继续分叉线程。

	值得注意的是，您可以通过正确设置 BB_NUMBER_THREADS 变量来大大加快构建时间。

	随着每个任务的完成，时间戳将写入由 STAMP 变量指定的目录。在随后的运行中，BitBake 会在 tmp/stamps 中的构建目录中查找，并且不会重新运行已经完成的任务，除非发现时间戳无效。目前，仅在每个配方文件的基础上考虑无效时间戳。因此，例如，如果配置标记的时间戳大于给定目标的编译时间戳，则编译任务将重新运行。但是，再次运行 compile 任务对依赖于该目标的其他提供程序没有影响。

	时间戳的确切格式是部分可配置的。在现代版本的 BitBake 中，将哈希附加到标记上，以便如果配置更改，标记将变为无效并且任务会自动重新运行。此散列或使用的签名由配置的签名策略管理（有关信息，请参阅校验和（签名）部分）。也可以使用 [stamp-extra-info] 任务标志将额外的元数据附加到图章。例如，OpenEmbedded 使用此标志来使某些任务特定于机器。

		Note
        一些任务被标记为“nostamp”任务。运行这些任务时不会创建时间戳文件。因此，“nostamp”任务总是会重新运行。

	有关任务的更多信息，请参阅任务部分。

####2.7 执行任务
	任务可以是 shell 任务或 Python 任务。对于 shell 任务，BitBake 将一个 shell 脚本写入 ${T}/run.do_taskname.pid 然后执行该脚本。生成的 shell 脚本包含所有导出的变量，以及扩展了所有变量的 shell 函数。 shell 脚本的输出到文件 ${T}/log.do_taskname.pid。查看运行文件中扩展的 shell 函数和日志文件中的输出是一种有用的调试技术。

	对于 Python 任务，BitBake 在内部执行任务并将信息记录到控制终端。未来版本的 BitBake 会将函数写入文件，类似于处理 shell 任务的方式。日志也将以类似于 shell 任务的方式处理。

	BitBake 运行任务的顺序由其任务调度程序控制。可以配置调度程序并为特定用例定义自定义实现。有关详细信息，请参阅这些控制行为的变量：
        • BB_SCHEDULER
        • BB_SCHEDULERS
	可以在任务的主函数之前和之后运行函数。这是使用列出要运行的函数的任务的 [prefuncs] 和 [postfuncs] 标志来完成的。

####2.8 校验和（签名）
	校验和是任务输入的唯一签名。任务的签名可用于确定是否需要运行任务。因为触发任务运行的是任务输入的变化，BitBake 需要检测给定任务的所有输入。对于 shell 任务，这变得相当容易，因为 BitBake 为每个任务生成一个“运行”shell 脚本，并且可以创建一个校验和，让您很好地了解任务的数据何时发生变化。

	使问题复杂化的是，校验和中不应包含某些内容。首先，给定任务的实际特定构建路径 - 工作目录。工作目录是否更改并不重要，因为它不应该影响目标包的输出。排除工作目录的简单方法是将其设置为某个固定值并为“运行”脚本创建校验和。 BitBake 更进一步，使用 BB_BASEHASH_IGNORE_VARS 变量来定义生成签名时永远不应包含的变量列表。

	另一个问题是“运行”脚本包含可能会或可能不会被调用的函数。增量构建解决方案包含计算 shell 函数之间依赖关系的代码。此代码用于将“运行”脚本修剪到最小集，从而缓解此问题并使“运行”脚本更具可读性作为奖励。

	到目前为止，我们已经有了 shell 脚本的解决方案。 Python 任务呢？即使这些任务更加困难，同样的方法也适用。该过程需要弄清楚 Python 函数访问哪些变量以及它调用了哪些函数。同样，增量构建解决方案包含的代码首先确定变量和函数依赖关系，然后为用作任务输入的数据创建校验和。

	与工作目录的情况一样，存在应该忽略依赖关系的情况。对于这些情况，您可以使用如下行指示构建过程忽略依赖项：
		PACKAGE_ARCHS[vardepsexclude] = "MACHINE"
	此示例确保 PACKAGE_ARCHS 变量不依赖于 MACHINE 的值，即使它确实引用了它。

	同样，在某些情况下，我们需要添加 BitBake 无法找到的依赖项。您可以通过使用如下行来完成此操作：
    	PACKAGE_ARCHS[vardeps] = "MACHINE"

	此示例显式添加 MACHINE 变量作为 PACKAGE_ARCHS 的依赖项。

	例如，考虑使用内联 Python 的情况，BitBake 无法找出依赖关系。在调试模式下运行时（即使用 -DDD），BitBake 会在发现无法确定依赖关系的内容时生成输出。

	到目前为止，本节的讨论仅限于对任务的直接输入。基于直接输入的信息在代码中称为“basehash”。但是，仍然存在任务间接输入的问题——那些已经构建并存在于构建目录中的东西。特定任务的校验和（或签名）需要添加特定任务所依赖的所有任务的哈希值。选择要添加的依赖项是一项策略决策。但是，效果是生成一个主校验和，它结合了 basehash 和任务依赖项的哈希值。

	在代码级别，可以通过多种方式影响 basehash 和相关任务哈希。在 BitBake 配置文件中，我们可以给 BitBake 一些额外的信息来帮助它构建 basehash。以下语句有效地产生了一个全局变量依赖排除列表——变量从未包含在任何校验和中。此示例使用 OpenEmbedded 中的变量来帮助说明该概念：
    	BB_BASEHASH_IGNORE_VARS ?= "TMPDIR FILE PATH PWD BB_TASKHASH BBPATH DL_DIR \
        SSTATE_DIR THISDIR FILESEXTRAPATHS FILE_DIRNAME HOME LOGNAME SHELL \
        USER FILESPATH STAGING_DIR_HOST STAGING_DIR_TARGET COREBASE PRSERV_HOST \
        PRSERV_DUMPDIR PRSERV_DUMPFILE PRSERV_LOCKDOWN PARALLEL_MAKE \
        CCACHE_DIR EXTERNAL_TOOLCHAIN CCACHE CCACHE_DISABLE LICENSE_PATH SDKPKGSUFFIX"

	前面的示例不包括工作目录，它是 TMPDIR 的一部分。

	决定通过依赖链包含哪些依赖任务的哈希的规则更复杂，通常使用 Python 函数完成。 meta/lib/oe/sstatesig.py 中的代码显示了这两个示例，还说明了如何在需要时将自己的策略插入系统。该文件定义了 OpenEmbedded-Core 使用的两个基本签名生成器：“OEBasic”和“OEBasicHash”。默认情况下，BitBake 中启用了一个虚拟的“noop”签名处理程序。这意味着行为与以前的版本没有变化。默认情况下，OE-Core 通过 bitbake.conf 文件中的此设置使用“OEBasicHash”签名处理程序：
    	BB_SIGNATURE_HANDLER ?= "OEBasicHash"

	“OEBasicHash” BB_SIGNATURE_HANDLER 与“OEBasic”版本相同，但将任务哈希添加到戳文件中。这会导致任何会更改任务哈希的元数据更改，从而自动导致任务再次运行。这消除了增加 PR 值的需要，并且对元数据的更改会自动在整个构建中产生涟漪效应。

	还值得注意的是，这些签名生成器的最终结果是使某些依赖项和哈希信息可用于构建。这些信息包括：

        • BB_BASEHASH_task-taskname：配方中每个任务的基本哈希。
        • BB_BASEHASH_filename:taskname：每个依赖任务的基本哈希。
        • BB_TASKHASH：当前运行任务的哈希值。

	值得注意的是，BitBake 的“-S”选项可以让您调试 BitBake 对签名的处理。传递给 -S 的选项允许使用不同的调试模式，可以使用 BitBake 自己的调试功能，也可以使用元数据/签名处理程序本身中定义的那些。要传递的最简单的参数是“none”，这会导致将一组签名信息写入与指定目标相对应的 STAMPS_DIR。另一个当前可用的参数是“printdiff”，它会导致 BitBake 尝试建立最接近的签名匹配（例如在 sstate 缓存中），然后在匹配上运行 bitbake-diffsigs 以确定这两个戳树所在的戳和增量发散。

    	Note
        未来版本的 BitBake 很可能会提供通过附加“-S”参数触发的其他签名处理程序。

    您可以在 Task Checksums and Setscene 部分找到有关校验和元数据的更多信息。

####2.9 场景
	setscene 过程使 BitBake 能够处理“预建”工件。处理和重用这些工件的能力使 BitBake 不必每次都从头开始构建东西。相反，BitBake 可以在可能的情况下使用现有的构建工件。

	BitBake 需要有可靠的数据来指示工件是否兼容。上一节中描述的签名提供了一种表示工件是否兼容的理想方式。如果签名相同，则可以重用对象。

	如果一个对象可以被重用，那么问题就变成了如何用预先构建的工件替换给定的任务或一组任务。 BitBake 通过“setscene”过程解决了这个问题。

	当要求 BitBake 构建给定目标时，在构建任何东西之前，它首先询问缓存信息是否可用于它正在构建的任何目标或任何中间目标。如果缓存信息可用，BitBake 将使用此信息而不是运行主要任务。

	BitBake 首先调用由 BB_HASHCHECK_FUNCTION 变量定义的函数，其中包含任务列表和要构建的相应哈希值。此函数旨在快速并返回它认为可以获得工件的任务列表。

	接下来，对于作为可能性返回的每个任务，BitBake 执行可能的工件涵盖的任务的场景版本。任务的 Setscene 版本在任务名称后附加了字符串“_setscene”。因此，例如，名称为 xxx 的任务有一个名为 xxx_setscene 的 setscene 任务。任务的场景版本执行并提供返回成功或失败的必要工件。

	如前所述，一个工件可以涵盖多个任务。例如，如果您已经拥有已编译的二进制文件，则获取编译器是没有意义的。为了处理这个问题，BitBake 为每个成功的场景任务调用 BB_SETSCENE_DEPVALID 函数，以了解它是否需要获取该任务的依赖关系。

	您可以在任务校验和和 Setscene 部分中找到有关 setscene 元数据的更多信息。

####2.10 日志记录
	除了用于控制执行时如何详细构建的标准命令行选项之外，bitbake 还支持通过 BB_LOGCONFIG 变量对 Python 日志记录工具进行用户定义的配置。此变量定义了一个 json 或 yaml 日志配置，它将智能地合并到默认配置中。使用以下规则合并日志记录配置：

        • 如果顶级键 bitbake_merge 设置为值 False，用户定义的配置将完全替换默认配置。在这种情况下，所有其他规则都将被忽略。
        • 用户配置必须具有必须与默认配置的值匹配的顶级版本。
        • 在处理程序、格式化程序或过滤器中定义的任何键都将合并到默认配置中的同一部分，如果发生冲突，用户指定的键将替换默认键。实际上，这意味着如果默认配置和用户配置都指定了一个名为 myhandler 的处理程序，则用户定义的处理程序将替换默认值。为了防止用户无意中替换默认处理程序、格式化程序或过滤器，所有默认处理程序都以“BitBake”前缀命名。
        • 如果用户定义了一个记录器，并将键 bitbake_merge 设置为 False，则该记录器将完全由用户配置替换。在这种情况下，不会有其他规则适用于该记录器。
        • 给定记录器的所有用户定义的过滤器和处理程序属性将与默认记录器的相应属性合并。例如，如果用户配置向 BitBake.SigGen 添加了一个名为 myFilter 的过滤器，而默认配置添加了一个名为 BitBake.defaultFilter 的过滤器，则这两个过滤器都将应用于记录器

	例如，考虑以下用户日志记录配置文件，该文件将 VERBOSE 或更高级别的所有 Hash Equivalence 相关消息记录到名为 hashequiv.log 的文件中
        {
            "version": 1,
            "handlers": {
                "autobuilderlog": {
                    "class": "logging.FileHandler",
                    "formatter": "logfileFormatter",
                    "level": "DEBUG",
                    "filename": "hashequiv.log",
                    "mode": "w"
                }
            },
            "formatters": {
                    "logfileFormatter": {
                        "format": "%(name)s: %(levelname)s: %(message)s"
                    }
            },
            "loggers": {
                "BitBake.SigGen.HashEquiv": {
                    "level": "VERBOSE",
                    "handlers": ["autobuilderlog"]
                },
                "BitBake.RunQueue.HashEquiv": {
                    "level": "VERBOSE",
                    "handlers": ["autobuilderlog"]
                }
            }
        }

###3 语法和运算符
	BitBake 文件有自己的语法。该语法与其他几种语言有相似之处，但也有一些独特的功能。本节介绍可用的语法和运算符，并提供示例。

####3.1 基本语法
	本节提供了一些基本的语法示例。

#####3.1.1 基本变量设置
	以下示例将 VARIABLE 设置为“value”。这个赋值在语句被解析时立即发生。这是一项“艰巨”的任务。
		VARIABLE = "value"
	正如预期的那样，如果您在分配中包含前导或尾随空格，则保留空格：
		VARIABLE = " value"
		VARIABLE = "value "
	将 VARIABLE 设置为“”会将其设置为空字符串，而将变量设置为“”会将其设置为空格（即它们不是相同的值）。
		VARIABLE = ""
		VARIABLE = " "
	设置变量值时，可以使用单引号代替双引号。这样做允许您使用包含双引号字符的值：
		VARIABLE = 'I have a " in my value'

		Note:
		与 Bourne shell 不同，单引号在所有其他方面与双引号的工作方式相同。它们不抑制变量扩展。

#####3.1.2 修改现有变量
	有时您需要修改现有变量。以下是您可能会发现要修改现有变量的一些情况：
		- 自定义使用该变量的配方。
		- 更改 *.bbclass 文件中使用的变量的默认值。
		- 更改 *.bbappend 文件中的变量以覆盖原始配方中的变量。
		- 更改配置文件中的变量，以便该值覆盖现有配置。
	更改变量值有时可能取决于最初分配值的方式以及更改的预期意图。特别是，当您将值附加到具有默认值的变量时，结果值可能不是您所期望的。在这种情况下，您提供的值可能会替换该值，而不是附加到默认值。

	如果在您更改了变量的值之后发生了无法解释的事情，您可以使用 BitBake 检查可疑变量的实际值。您可以对配置和配方级别更改进行这些检查：

		- 对于配置更改，请使用以下命令：
			$ bitbake -e
		此命令在配置文件（即 local.conf、bblayers.conf、bitbake.conf 等）被解析后显示变量值。

		Note:
		导出到环境的变量在命令输出中以字符串“export”开头。

		- 要查找特定配方中给定变量的更改，请使用以下命令：
			$ bitbake recipename -e | grep VARIABLENAME=\"
		这个命令检查变量是否真的进入了一个特定的配方。

#####3.1.3 行连接
	在函数之外，BitBake 在解析语句之前将任何以反斜杠字符（“\”）结尾的行与以下行连接起来。 “\”字符最常见的用途是将变量分配拆分为多行，如下例所示：
		FOO = "bar \
			   baz \
			   qaz"
	加入行时，“\”字符和其后的换行符都会被删除。因此，FOO 的值中没有换行符。

	考虑这个附加示例，其中两个分配都将“barbaz”分配给 FOO：
		FOO = "barbaz"
		FOO = "bar\
		baz"

		Note:
		BitBake 不会解释变量值中的“\n”等转义序列。要使这些生效，必须将值传递给一些解释转义序列的实用程序，例如 printf 或 echo -n。

#####3.1.4 变量展开
	变量可以使用类似于 Bourne shell 中的变量扩展的语法来引用其他变量的内容。以下分配导致 A 包含“aval”，而 B 评估为“preavalpost”。
		A = "aval"
		B = "pre${A}post"

		Note:
		与 Bourne shell 不同，花括号是强制性的：只有 ${FOO} 而不是 $FOO 被识别为 FOO 的扩展。

	“=”运算符不会立即展开右侧的变量引用。相反，扩展被推迟到实际使用分配给的变量。结果取决于引用变量的当前值。以下示例应阐明此行为：
		A = "${B} baz"
		B = "${C} bar"
		C = "foo"
		*At this point, ${A} equals "foo bar baz"*
		C = "qux"
		*At this point, ${A} equals "qux bar baz"*
		B = "norf"
		*At this point, ${A} equals "norf baz"*
	将此行为与立即变量扩展 (:=) 运算符进行对比。

	如果对不存在的变量使用变量扩展语法，则字符串保持原样。例如，给定以下赋值，只要 FOO 不存在，BAR 就会扩展为文字字符串“${FOO}”。
		BAR = "${FOO}"

#####3.1.5 设置默认值 (?=)
	您可以使用“?=”运算符来实现对变量的“更软”赋值。如果在解析语句时未定义变量，这种类型的赋值允许您定义变量，但如果变量有值，则不理会该值。这是一个例子：
		A ?= "aval"
	如果在解析此语句时设置了 A，则变量保留其值。但是，如果未设置 A，则将变量设置为“aval”。

		Note:
		这个任务是即时的。因此，如果存在对单个变量的多个“？=”赋值，则其中第一个最终会被使用。

#####3.1.6 设置弱默认值（??=）
	通过使用“??=”运算符，可以使用比上一节中“更弱”的赋值。这个赋值的行为与“?=”相同，只是赋值是在解析过程结束时而不是立即进行的。因此，当存在多个“??=”分配时，使用最后一个。此外，任何“=”或“?=”赋值都会覆盖用“??=”设置的值。这是一个例子：
		A ??= "somevalue"
		A ??= "someothervalue"
	如果在解析上述语句之前设置了 A，则变量保留其值。如果未设置 A，则将变量设置为“someothervalue”。

	同样，此分配是“惰性”或“弱”分配，因为它直到解析过程结束才会发生。

#####3.1.7 立即变量展开 (:=)
	“:=”操作符导致变量的内容立即展开，而不是在实际使用变量时：
		T = "123"
		A := "test ${T}"
		T = "456"
		B := "${T} ${C}"
		C = "cval"
		C := "${C}append"
	在此示例中，A 包含“test 123”，即使 T 的最终值为“456”。变量 B 最终将包含“456 cvalappend”。这是因为对未定义变量的引用在（立即）扩展期间保持原样。这与 GNU Make 形成对比，其中未定义的变量扩展为空。变量 C 包含“cvalappend”，因为 ${C} 立即扩展为“cval”。

#####3.1.8 使用空格附加 (+=) 和前置 (=+)
	附加和前置值很常见，可以使用“+=”和“=+”运算符来完成。这些运算符在当前值和前置或附加值之间插入一个空格。

	这些运算符在解析过程中立即生效。这里有些例子：
		B = "bval"
		B += "additionaldata"
		C = "cval"
		C =+ "test"
	变量 B 包含“bval Additionaldata”，C 包含“test cval”。

#####3.1.9 没有空格的附加 (.=) 和前置 (=.)
	如果要在没有插入空格的情况下附加或前置值，请使用“.=”和“=”。运营商。

	这些运算符在解析过程中立即生效。这里有些例子：
		B = "bval"
		B .= "additionaldata"
		C = "cval"
		C =. "test"
	变量 B 包含“bvaladditionaldata”，C 包含“testcval”。

#####3.1.10 附加和前置（覆盖样式语法）
	您还可以使用覆盖样式语法附加和前置变量的值。使用此语法时，不会插入空格。

	这些运算符与“:=”、“.=”、“=.”、“+=”和“=+”运算符的不同之处在于它们的效果是在可变扩展时间应用而不是立即应用。这里有些例子：
		B = "bval"
		B:append = " additional data"
		C = "cval"
		C:prepend = "additional data "
		D = "dval"
		D:append = "additional data"
	变量 B 变为“bval 附加数据”，C 变为“附加数据 cval”。变量 D 变为“dvaladditional data”。

		Note:
		使用覆盖语法时必须控制所有间距。

	还可以附加和前置到 shell 函数和 BitBake 样式的 Python 函数。有关示例，请参见“Shell 函数”和“BitBake 样式 Python 函数”部分。

#####3.1.11 移除（覆盖样式语法）
	您可以使用删除覆盖样式语法从列表中删除值。指定要删除的值会导致从变量中删除该值的所有出现。

	当您使用此语法时，BitBake 需要一个或多个字符串。保留了周围的空间和间距。这是一个例子：
		FOO = "123 456 789 123456 123 456 123 456"
		FOO:remove = "123"
		FOO:remove = "456"
		FOO2 = " abc def ghi abcdef abc def abc def def"
		FOO2:remove = "\
			def \
			abc \
			ghi \
			"
	变量 FOO 变为“789 123456”，FOO2 变为“abcdef”。

	像“:append”和“:prepend”一样，“:remove”在变量扩展时应用。

#####3.1.12 覆盖式操作优势
	与“+=”和“=+”运算符相比，覆盖样式操作“:append”、“:prepend”和“:remove”的一个优点是覆盖样式运算符提供有保证的操作。例如，考虑一个需要将值“val”添加到变量 FOO 的类 foo.bbclass，以及一个使用 foo.bbclass 的配方，如下所示：
		inherit foo
		FOO = "initial"
	如果 foo.bbclass 使用“+=”运算符，如下所示，那么 FOO 的最终值将是“初始值”，这不是我们想要的：
		FOO += "val"
	另一方面，如果 foo.bbclass 使用“:append”运算符，那么 FOO 的最终值将是“initial val”，如预期的那样：
		FOO:append = " val"

		Note
		从来没有必要将“+=”与“:append”一起使用。以下分配序列将“barbaz”附加到 FOO：
			FOO:append = "bar"
			FOO:append = "baz"
		将前面示例中的第二个赋值更改为使用“+=”的唯一效果是在附加值中的“baz”之前添加一个空格（由于“+=”运算符的工作原理）。

	覆盖样式操作的另一个优点是您可以将它们与“条件语法（覆盖）”部分中所述的其他覆盖结合起来。

#####3.1.13 变量标志语法
	变量标志是 BitBake 对变量属性或属性的实现。这是一种将额外信息标记到变量上的方法。您可以在“变量标志”部分找到更多关于一般变量标志的信息。

	您可以为变量标志定义、附加和附加值。前面提到的所有标准语法操作都适用于变量标志，除了覆盖样式语法（即“:prepend”、“:append”和“:remove”）。

	以下是一些显示如何设置变量标志的示例：
		FOO[a] = "abc"
		FOO[b] = "123"
		FOO[a] += "456"
	变量 FOO 有两个标志：[a] 和 [b]。这些标志立即分别设置为“abc”和“123”。 [a] 标志变为“abc 456”。

	无需预先定义变量标志。您可以简单地开始使用它们。一个非常常见的应用是将一些简短的文档附加到 BitBake 变量中，如下所示：
		CACHE[doc] = "The directory holding the cache of the metadata."

#####3.1.14 内联 Python 变量扩展
	您可以使用内联 Python 变量扩展来设置变量。这是一个例子：
		DATE = "${@time.strftime('%Y%m%d',time.gmtime())}"
	此示例导致将 DATE 变量设置为当前日期。

	此功能最常见的用途可能是从 BitBake 的内部数据字典 d 中提取变量的值。以下几行分别选择包名称及其版本号的值：
		PN = "${@bb.parse.vars_from_file(d.getVar('FILE', False),d)[0] or 'defaultpkgname'}"
		PV = "${@bb.parse.vars_from_file(d.getVar('FILE', False),d)[1] or '1.0'}"

		Note:
		就“=”和“:=”运算符而言，内联 Python 表达式的工作方式与变量扩展类似。给定以下分配，每次扩展 FOO 时都会调用 foo()：
			FOO = "${@foo()}"
		将此与以下立即分配进行对比，其中 foo() 仅调用一次，而分配被解析：
			FOO := "${@foo()}"

	有关在解析期间使用 Python 代码设置变量的不同方法，请参阅“匿名 Python 函数”部分。

#####3.1.15 取消设置变量
	可以使用“unset”关键字从 BitBake 的内部数据字典中完全删除变量或变量标志。这是一个例子：
		unset DATE
		unset do_fetch[noexec]
	这两个语句删除了 DATE 和 do_fetch[noexec] 标志。

#####3.1.16 提供路径名
	指定用于 BitBake 的路径名时，请勿使用波浪号 (“~”) 字符作为主目录的快捷方式。这样做可能会导致 BitBake 无法识别路径，因为 BitBake 不会以与 shell 相同的方式扩展此字符。

	相反，请提供更完整的路径，如下例所示：
		BBLAYERS ?= " \
			/home/scott-lenovo/LayerA \
		"

####3.2 将变量导出到环境
	您可以使用 export 关键字将变量导出到运行任务的环境中。例如，在以下示例中，do_foo 任务在运行时打印“来自环境的值”：
		export ENV_VARIABLE
		ENV_VARIABLE = "value from the environment"

		do_foo() {
			bbplain "$ENV_VARIABLE"
		}

		Note:
		在这种情况下，BitBake 不会扩展 $ENV_VARIABLE ，因为它缺少强制性的 {} 。相反，$ENV_VARIABLE 由 shell 扩展。

	导出 ENV_VARIABLE 出现在分配给 ENV_VARIABLE 之前还是之后都没有关系。

	还可以将导出与设置变量值结合使用。这是一个例子：
		export ENV_VARIABLE = "variable-value"
	在 bitbake -e 的输出中，导出到环境的变量前面带有“export”。

	通常导出到环境的变量包括 CC 和 CFLAGS，它们被许多构建系统采用。

####3.3 条件语法（覆盖）
	BitBake 使用 OVERRIDES 来控制在 BitBake 解析配方和配置文件后覆盖哪些变量。本节介绍如何将 OVERRIDES 用作条件元数据，讨论与 OVERRIDES 相关的键扩展，并提供一些示例以帮助理解。

#####3.3.1 条件元数据
	您可以使用 OVERRIDES 有条件地选择变量的特定版本，并有条件地附加或前置变量的值。

		Note:
		覆盖只能使用小写字符、数字和破折号。特别是，在覆盖名称中不允许使用冒号，因为它们用于将覆盖之间以及与变量名称分开。

	- 选择变量： OVERRIDES 变量是一个以冒号字符分隔的列表，其中包含您要满足条件的项目。因此，如果您有一个以“arm”为条件的变量，并且“arm”在 OVERRIDES 中，则使用变量的“arm”特定版本而不是非条件版本。这是一个例子：
		OVERRIDES = "architecture:os:machine"
		TEST = "default"
		TEST:os = "osspecific"
		TEST:nooverride = "othercondvalue"
		在此示例中，OVERRIDES 变量列出了三个覆盖：“architecture”、“os”和“machine”。变量 TEST 本身具有默认值“default”。您可以通过将“os”覆盖附加到变量（即 TEST:os）来选择 TEST 变量的特定于操作系统的版本。
		为了更好地理解这一点，请考虑一个假设基于 OpenEmbedded 元数据的 Linux 内核配方文件的实际示例。配方文件中的以下行首先将内核分支变量 KBRANCH 设置为默认值，然后根据构建的体系结构有条件地覆盖该值：
			KBRANCH = "standard/base"
			KBRANCH:qemuarm = "standard/arm-versatile-926ejs"
			KBRANCH:qemumips = "standard/mti-malta32"
			KBRANCH:qemuppc = "standard/qemuppc"
			KBRANCH:qemux86 = "standard/common-pc/base"
			KBRANCH:qemux86-64 = "standard/common-pc-64/base"
			KBRANCH:qemumips64 = "standard/mti-malta64"

	- 附加和前置：BitBake 还支持根据特定项目是否在 OVERRIDES 中列出来对变量值进行附加和前置操作。这是一个例子：
		DEPENDS = "glibc ncurses"
		OVERRIDES = "machine:local"
		DEPENDS:append:machine = "libmad"
		在本例中，DEPENDS 变为“glibc ncurses libmad”。
		同样，使用基于 OpenEmbedded 元数据的内核配方文件作为示例，以下行将有条件地附加到基于架构的 KERNEL_FEATURES 变量中：
		KERNEL_FEATURES:append = " ${KERNEL_EXTRA_FEATURES}"
		KERNEL_FEATURES:append:qemux86=" cfg/sound.scc cfg/paravirt_kvm.scc"
		KERNEL_FEATURES:append:qemux86-64=" cfg/sound.scc cfg/paravirt_kvm.scc"

	- 为单个任务设置变量：BitBake 支持仅在单个任务期间设置变量。这是一个例子：
		FOO:task-configure = "val 1"
		FOO:task-compile = "val 2"
		在前面的示例中，FOO 在执行 do_configure 任务时具有值“val 1”，而在执行 do_compile 任务时具有值“val 2”。
		在内部，这是通过将任务（例如“task-compile:”）添加到 do_compile 任务的本地数据存储的 OVERRIDES 值来实现的。
		您还可以将此语法与其他组合（例如“:prepend”）一起使用，如下例所示：
			EXTRA_OEMAKE:prepend:task-compile = "${PARALLEL_MAKE} "

			Note:
			在 BitBake 1.52 (Honister 3.4) 之前，OVERRIDES 的语法使用 _ 而不是 :，因此您仍然会发现很多使用 _append、_prepend 和 _remove 的文档。
			有关详细信息，请参阅 Yocto Project 手动迁移说明中的 Overrides Syntax Changes 部分。

#####3.3.2 密钥扩展
	完成 BitBake 数据存储时会发生密钥扩展。为了更好地理解这一点，请考虑以下示例：
		A${B} = "X"
		B = "2"
		A2 = "Y"
	在这种情况下，在所有解析完成后，BitBake 将 ${B} 扩展为“2”。这种扩展导致在扩展之前设置为“Y”的 A2 变为“X”。

#####3.3.3 示例
	尽管前面的解释显示了变量定义的不同形式，但是当变量运算符、条件覆盖和无条件覆盖组合在一起时，很难准确计算出会发生什么。本节介绍了一些常见场景以及对通常使用户感到困惑的可变交互的解释。

	关于覆盖和各种“附加”运算符生效的顺序经常会出现混淆。回想一下，使用“:append”和“:prepend”的追加或前置操作不会像“+=”、“.=”、“=+”或“=.”那样导致立即赋值。考虑以下示例：
		OVERRIDES = "foo"
		A = "Z"
		A:foo:append = "X"
	对于这种情况，A 无条件设置为“Z”，“X”无条件立即附加到变量 A:foo。由于尚未应用覆盖，因此 A:foo 由于追加而设置为“X”，而 A 简单地等于“Z”。

	然而，应用覆盖会改变一些事情。由于“foo”列在 OVERRIDES 中，条件变量 A 被替换为“foo”版本，等于“X”。如此有效地，A:foo 替换了 A。

	下一个示例更改了覆盖和附加的顺序：
		OVERRIDES = "foo"
		A = "Z"
		A:append:foo = "X"
	对于这种情况，在处理覆盖之前，A 设置为“Z”，A:append:foo 设置为“X”。但是，一旦应用了“foo”的覆盖，A 就会附加“X”。因此，A 变为“ZX”。请注意，未附加空格。

	下一个示例将追加和覆盖的顺序与第一个示例相反：
		OVERRIDES = "foo"
		A = "Y"
		A:foo:append = "Z"
		A:foo:append = "X"
	对于这种情况，在解决任何覆盖之前，使用立即分配将 A 设置为“Y”。在这个立即赋值之后，A:foo 设置为“Z”，然后进一步附加“X”，将变量设置为“ZX”。最后，对“foo”应用覆盖会导致条件变量 A 变为“ZX”（即 A 被 A:foo 替换）。

	最后一个示例混合了一些不同的运算符：
		A = "1"
		A:append = "2"
		A:append = "3"
		A += "4"
		A .= "5"
	对于这种情况，附加运算符的类型会影响分配的顺序，因为 BitBake 会多次通过代码。最初，A 设置为“1 45”，因为三个语句使用立即运算符。完成这些分配后，BitBake 应用“:append”操作。这些操作导致 A 变为“1 4523”。

####3.4 共享功能
	BitBake 允许通过包含文件 (.inc) 和类文件 (.bbclass) 共享元数据。例如，假设您有一个通用功能，例如您希望在多个配方之间共享的任务定义。在这种情况下，创建一个包含通用功能的 .bbclass 文件，然后在您的配方中使用inherit 指令来继承该类将是共享任务的常用方法。

	本节介绍 BitBake 提供的允许您在配方之间共享功能的机制。具体来说，这些机制包括 include、inherit、INHERIT 和 require 指令。

#####3.4.1 定位包含和类文件
	BitBake 使用 BBPATH 变量来定位所需的包含和类文件。此外，BitBake 在当前目录中搜索 include 和 require 指令。

			Note:
			BBPATH 变量类似于环境变量 PATH 。

	为了让 BitBake 找到包含和类文件，它们需要位于可以在 BBPATH 中找到的“类”子目录中。

#####3.4.2 继承指令
	在编写配方或类文件时，您可以使用inherit 指令来继承类（.bbclass）的功能。 BitBake 仅在配方和类文件（即 .bb 和 .bbclass）中使用时才支持此指令。

	继承指令是指定配方所需的类文件中包含的功能的基本方法。例如，您可以轻松地抽象出构建使用 Autoconf 和 A​​utomake 的包所涉及的任务，并将这些任务放入类文件中，然后让您的配方继承该类文件。

	例如，您的食谱可以使用以下指令来继承 autotools.bbclass 文件。类文件将包含使用 Autotools 的通用功能，这些功能可以在配方之间共享：
		inherit autotools
	在这种情况下，BitBake 会在 BBPATH 中搜索目录 classes/autotools.bbclass。

			Note:
			您可以在“inherit”语句之后覆盖配方中继承类的任何值和函数。

	如果要使用该指令继承多个类，请用空格分隔它们。以下示例显示如何继承 buildhistory 和 rm_work 类：
		inherit buildhistory rm_work
	与 include 和 require 指令相比，inherit 指令的一个优点是您可以有条件地继承类文件。您可以通过在继承语句后使用变量表达式来完成此操作。这是一个例子：
		inherit ${VARNAME}
	如果要设置 VARNAME，则需要在解析继承语句之前设置它。在这种情况下实现条件继承的一种方法是使用覆盖：
		VARIABLE = ""
		VARIABLE:someoverride = "myclass"
	另一种方法是使用匿名 Python。这是一个例子：
		python () {
			if condition == value:
				d.setVar('VARIABLE', 'myclass')
			else:
				d.setVar('VARIABLE', '')
		}
	或者，您可以使用以下形式的内联 Python 表达式：
		inherit ${@'classname' if condition else ''}
		inherit ${@functionname(params)}
	在所有情况下，如果表达式的计算结果为空字符串，则该语句不会触发语法错误，因为它变成了无操作。

#####3.4.3 include指令
	BitBake 理解include指令。该指令使 BitBake 解析您指定的任何文件，并将该文件插入该位置。该指令与 Make 中的等效指令非常相似，只是如果在包含行中指定的路径是相对路径，BitBake 会定位它可以在 BBPATH 中找到的第一个文件。

	与仅限于类（即 .bbclass）文件的inherit指令相比，include指令是一种更通用的包含功能的方法。 include 指令适用于不适合 .bbclass 文件的任何其他类型的共享或封装功能或配置。

	例如，假设您需要一个配方来包含一些自测定义：
		include test_defs.inc

			Note:
			当找不到文件时，include 指令不会产生错误。因此，如果您要包含的文件预计存在，建议您使用 require 而不是 include 。这样做可确保在找不到文件时产生错误。

#####3.4.4 require指令
	BitBake 理解 require 指令。该指令的行为与 include 指令类似，但如果找不到要包含的文件，BitBake 会引发解析错误。因此，您需要的任何文件都将插入到该指令所在位置正在解析的文件中。

	与之前描述的 include 指令一样，require 指令是一种更通用的包含功能的方法，与仅限于类（即 .bbclass）文件的继承指令相比。 require 指令适用于不适合 .bbclass 文件的任何其他类型的共享或封装功能或配置。

	与 BitBake 处理 include 的方式类似，如果在 require 行中指定的路径是相对路径，BitBake 会在 BBPATH 中找到它可以找到的第一个文件。

	例如，假设您有两个版本的配方（例如 foo_1.2.2.bb 和 foo_2.0.0.bb），其中每个版本都包含一些可以共享的相同功能。您可以创建一个名为 foo.inc 的包含文件，其中包含构建“foo”所需的通用定义。您需要确保 foo.inc 也与您的两个配方文件位于同一目录中。设置这些条件后，您可以使用每个配方中的 require 指令共享功能：
		require foo.inc

#####3.4.5 INHERIT 配置指令
	创建配置文件 (.conf) 时，您可以使用 INHERIT 配置指令来继承类。 BitBake 仅在配置文件中使用时才支持此指令。

	例如，假设您需要从配置文件中继承一个名为 abc.bbclass 的类文件，如下所示：
		INHERIT += "abc"
	此配置指令导致在解析期间在指令点继承命名类。与inherit 指令一样，.bbclass 文件必须位于BBPATH 中指定的目录之一的“classes”子目录中。

			Note:
			因为 .conf 文件在 BitBake 执行期间首先被解析，所以使用 INHERIT 继承一个类有效地继承了全局类（即对于所有配方）。

	如果要使用该指令来继承多个类，可以在 local.conf 文件的同一行中提供它们。使用空格分隔类。以下示例显示如何继承 autotools 和 pkgconfig 类：
		INHERIT += "autotools pkgconfig"

####3.5 函数
	与大多数语言一样，函数是用于将操作构建到任务中的构建块。 BitBake 支持以下类型的函数：
		- Shell 函数：用 shell 脚本编写的函数，可以直接作为函数、任务或两者同时执行。它们也可以被其他 shell 函数调用。
		- BitBake 风格的 Python 函数：用 Python 编写并由 BitBake 或其他 Python 函数使用 bb.build.exec_func() 执行的函数。
		- Python 函数：用 Python 编写并由 Python 执行的函数。
		- 匿名 Python 函数：在解析期间自动执行的 Python 函数。
	无论函数类型如何，您只能在类（.bbclass）和配方（.bb 或 .inc）文件中定义它们。

#####3.5.1 shell函数
	用 shell 脚本编写的函数可以直接作为函数、任务或两者同时执行。它们也可以被其他 shell 函数调用。这是一个示例 shell 函数定义：
		some_function () {
			echo "Hello World"
		}
	当您在配方或类文件中创建这些类型的函数时，您需要遵循 shell 编程规则。脚本由 /bin/sh 执行，它可能不是 bash shell，但可能是 dash 之类的东西。您不应该使用特定于 Bash 的脚本（bashisms）。

	覆盖和覆盖样式的运算符，如 :append 和 :prepend 也可以应用于 shell 函数。最常见的是，此应用程序将在 .bbappend 文件中用于修改主配方中的功能。它还可以用于修改从类继承的函数。

	例如，考虑以下情况：
			do_foo() {
				bbplain first
				fn
			}

			fn:prepend() {
				bbplain second
			}

			fn() {
				bbplain third
			}

			do_foo:append() {
				bbplain fourth
			}
	运行 do_foo 会打印以下内容：
			recipename do_foo: first
			recipename do_foo: second
			recipename do_foo: third
			recipename do_foo: fourth

			Note：
			覆盖和覆盖样式的运算符可以应用于任何 shell 函数，而不仅仅是任务。

	在应用所有覆盖后，您可以使用 bitbake -e recipename 命令查看最终组装的函数。

#####3.5.2 BitBake 风格的 Python 函数
	这些函数是用 Python 编写的，并由 BitBake 或其他 Python 函数使用 bb.build.exec_func() 执行。

	一个示例 BitBake 函数是：
		python some_python_function () {
			d.setVar("TEXT", "Hello World")
			print d.getVar("TEXT")
		}
	因为 Python “bb” 和 “os” 模块已经导入，所以不需要导入这些模块。同样在这些类型的函数中，数据存储（“d”）是一个全局变量，并且始终自动可用。

			Note:
			变量表达式（例如 ${X} ）不再在 Python 函数中展开。此行为是有意的，以便您可以自由地将变量值设置为可扩展表达式，而不会过早地扩展它们。如果您确实希望在 Python 函数中扩展变量，请使用 d.getVar("X") 。或者，对于更复杂的表达式，使用 d.expand()。

	与 shell 函数类似，您还可以将覆盖和覆盖样式的运算符应用于 BitBake 样式的 Python 函数。

	例如，考虑以下情况：
			python do_foo:prepend() {
				bb.plain("first")
			}

			python do_foo() {
				bb.plain("second")
			}

			python do_foo:append() {
				bb.plain("third")
			}
	运行 do_foo 会打印以下内容：
			recipename do_foo: first
			recipename do_foo: second
			recipename do_foo: third
	在应用所有覆盖后，您可以使用 bitbake -e recipename 命令查看最终组装的函数。

#####3.5.3 Python 函数
	这些函数是用 Python 编写的，并由其他 Python 代码执行。 Python 函数的示例是您打算从内联 Python 或其他 Python 函数中调用的实用程序函数。这是一个例子：
			def get_depends(d):
				if d.getVar('SOMECONDITION'):
					return "dependencywithcond"
				else:
					return "dependency"

			SOMECONDITION = "1"
			DEPENDS = "${@get_depends(d)}"

	他会导致 DEPENDS 包含dependencywithcond。

	以下是有关 Python 函数的一些知识：
			- Python 函数可以接受参数。
			- BitBake 数据存储不会自动可用。因此，您必须将其作为参数传递给函数。
			- “bb” 和 “os” Python 模块自动可用。您不需要导入它们。

#####3.5.4 BitBake 风格的 Python 函数与 Python 函数
	以下是 BitBake 风格的 Python 函数与使用“def”定义的常规 Python 函数之间的一些重要区别：
			- 只有 BitBake 风格的 Python 函数可以是任务。
			- 覆盖和覆盖样式的运算符只能应用于 BitBake 样式的 Python 函数。
			- 只有常规的 Python 函数可以接受参数和返回值。
			- [dirs]、[cleandirs] 和 [lockfiles] 等变量标志可用于 BitBake 样式的 Python 函数，但不能用于常规 Python 函数。
			- BitBake 风格的 Python 函数生成一个单独的 ${T}/run.function-name.pid 脚本，该脚本被执行以运行该函数，并且还会在 ${T}/log.function-name.pid 中生成一个日志文件，如果它们作为任务执行。
			- 常规 Python 函数执行“内联”并且不会在 ${T} 中生成任何文件。
			- 使用通常的 Python 语法调用常规 Python 函数。 BitBake 风格的 Python 函数通常是任务，由 BitBake 直接调用，但也可以使用 bb.build.exec_func() 函数从 Python 代码中手动调用。这是一个例子：
				bb.build.exec_func("my_bitbake_style_function", d)

			Note:
			bb.build.exec_func() 也可用于从 Python 代码运行 shell 函数。如果要在同一任务中在 Python 函数之前运行 shell 函数，则可以使用父辅助 Python 函数，该函数首先使用 bb.build.exec_func() 运行 shell 函数，然后运行 ​​Python 代码。

		要检测使用 bb.build.exec_func() 执行的函数的错误，您可以捕获 bb.build.FuncFailed 异常。

			Note:
			元数据（配方和类）中的函数本身不应引发 bb.build.FuncFailed。相反，应该将 bb.build.FuncFailed 视为被调用函数因引发异常而失败的一般指标。例如，由 bb.fatal() 引发的异常将在 bb.build.exec_func() 中捕获，并且将引发 bb.build.FuncFailed 作为响应。

	由于它们的简单性，您应该更喜欢常规 Python 函数而不是 BitBake 样式 Python 函数，除非您需要特定于 BitBake 样式 Python 函数的功能。元数据中的常规 Python 函数是比 BitBake 风格的 Python 函数更近的发明，旧代码倾向于更频繁地使用 bb.build.exec_func()。

#####3.5.5 匿名 Python 函数
	有时在解析期间以编程方式设置变量或执行其他操作很有用。为此，您可以定义在解析结束时运行的特殊 Python 函数，称为匿名 Python 函数。例如，以下根据另一个变量的值有条件地设置一个变量：
			python () {
				if d.getVar('SOMEVAR') == 'value':
					d.setVar('ANOTHERVAR', 'value2')
			}

	将函数标记为匿名函数的等效方法是将其命名为“__anonymous”，而不是没有名称。

	匿名 Python 函数总是在解析结束时运行，无论它们是在哪里定义的。如果一个配方包含许多匿名函数，它们的运行顺序与它们在配方中定义的顺序相同。例如，考虑以下代码段：
			python () {
				d.setVar('FOO', 'foo 2')
			}

			FOO = "foo 1"

			python () {
				d.appendVar('BAR',' bar 2')
			}

			BAR = "bar 1"
	前面的示例在概念上等同于以下代码段：
			FOO = "foo 1"
			BAR = "bar 1"
			FOO = "foo 2"
			BAR += "bar 2"
	FOO 以值“foo 2”结束，BAR 以值“bar 1 bar 2”结束。就像在第二个片段中一样，为匿名函数中的变量设置的值对任务可用，这些任务总是在解析后运行。

	在匿名函数运行之前应用覆盖和覆盖样式的运算符，例如“:append”。在以下示例中，FOO 以“来自匿名的 foo”的值结束：
			FOO = "foo"
			FOO:append = " from outside"

			python () {
				d.setVar("FOO", "foo from anonymous")
			}
	有关可以与匿名 Python 函数一起使用的方法，请参阅“可以在 Python 中调用的函数”部分。有关在解析期间运行 Python 代码的不同方法，请参阅“内联 Python 变量扩展”部分。

#####3.5.6 类函数的灵活继承
	通过编码技术和 EXPORT_FUNCTIONS 的使用，BitBake 支持从一个类中导出一个函数，使得该类函数显示为该函数的默认实现，但如果继承该类的配方需要定义自己的版本功能。

	要了解此功能的好处，请考虑类定义任务函数并且您的配方继承该类的基本场景。在这个基本场景中，您的配方继承了类中定义的任务功能。如果需要，您的配方可以分别使用“:prepend”或“:append”操作添加到函数的开头和结尾，或者它可以完全重新定义函数。但是，如果它重新定义函数，它就没有办法调用函数的类版本。 EXPORT_FUNCTIONS 提供了一种机制，使配方的函数版本能够调用函数的原始版本。

	要使用此技术，您需要准备以下内容：
		- 该类需要定义函数如下：
				classname_functionname
		例如，如果您有一个类文件 bar.bbclass 和一个名为 do_foo 的函数，则该类必须按如下方式定义该函数：
				bar_do_foo
		- 该类需要包含 EXPORT_FUNCTIONS 语句，如下所示：
				EXPORT_FUNCTIONS functionname
		例如，继续相同的示例，bar.bbclass 中的语句如下：
				EXPORT_FUNCTIONS do_foo
		- 您需要从配方中适当地调用该函数。继续同一个例子，如果你的配方需要调用函数的类版本，它应该调用 bar_do_foo。假设 do_foo 是一个 shell 函数并且 EXPORT_FUNCTIONS 如上所述使用，配方的函数可以有条件地调用函数的类版本，如下所示：
				do_foo() {
					if [ somecondition ] ; then
						bar_do_foo
					else
						# Do something else
					fi
				}
		要调用配方中定义的函数的修改版本，请将其称为 do_foo。
	满足这些条件后，您的单个配方可以在类文件中定义的原始函数和配方中修改的函数之间自由选择。如果您不设置这些条件，则您只能使用一种功能或另一种功能。

####3.6 任务
	任务是 BitBake 执行单元，组成 BitBake 可以为给定配方运行的步骤。任务仅在配方和类中受支持（即在 .bb 文件和包含或从 .bb 文件继承的文件中）。按照惯例，任务的名称以“do_”开头。

#####3.6.1 将函数提升为任务
	任务是使用 addtask 命令提升为任务的 shell 函数或 BitBake 样式的 Python 函数。 addtask 命令还可以选择性地描述任务与其他任务之间的依赖关系。下面是一个示例，展示了如何定义任务和声明一些依赖项：
			python do_printdate () {
				import time
				print time.strftime('%Y%m%d', time.gmtime())
			}
			addtask printdate after do_fetch before do_build
	addtask 的第一个参数是要提升为任务的函数的名称。如果名称不以“do_”开头，则隐式添加“do_”，这强制执行所有任务名称以“do_”开头的约定。
	在前面的示例中，do_printdate 任务成为 do_build 任务的依赖项，这是默认任务（即由 bitbake 命令运行的任务，除非明确指定另一个任务）。此外，do_printdate 任务依赖于 do_fetch 任务。运行 do_build 任务会导致 do_printdate 任务首先运行。

			Note:
			如果您尝试前面的示例，您可能会看到 do_printdate 任务仅在您第一次使用 bitbake 命令构建配方时运行。这是因为 BitBake 在初始运行后认为任务是“最新的”。如果您想强制任务始终重新运行以进行实验，您可以使用 [nostamp] 变量标志使 BitBake 始终认为任务“过期”，如下所示：
				do_printdate[nostamp] = "1"
			您还可以显式运行任务并提供 -f 选项，如下所示：
				$ bitbake recipe -c printdate -f
			当使用 bitbake recipe -c task 命令手动选择要运行的任务时，您可以省略“do_”前缀作为任务名称的一部分。

	您可能想知道在不指定任何依赖项的情况下使用 addtask 的实际效果，如下例所示：
			addtask printdate
	在此示例中，假设未通过其他方式添加依赖项，运行任务的唯一方法是使用 bitbake recipe -c printdate 显式选择它。您可以使用 do_listtasks 任务列出配方中定义的所有任务，如以下示例所示：
			$ bitbake recipe -c listtasks
	有关任务依赖关系的更多信息，请参阅“依赖关系”部分。
	有关可用于任务的变量标志的信息，请参阅“变量标志”部分。

			Note:
			虽然不常见，但可以在调用 addtask 时将多个任务定义为依赖项。例如，下面是 OpenEmbedded 类文件 package_tar.bbclass 的片段：
				addtask package_write_tar before do_build after do_packagedata do_package
			请注意 package_write_tar 任务如何必须等到 do_packagedata 和 do_package 都完成。

#####3.6.2 删除任务
	除了能够添加任务外，您还可以删除它们。只需使用 deltask 命令即可删除任务。例如，要删除前面部分中使用的示例任务，您可以使用：
			deltask printdate
	如果您使用 deltask 命令删除任务并且该任务具有依赖关系，则不会重新连接依赖关系。例如，假设您有三个名为 do_a、do_b 和 do_c 的任务。此外，do_c 依赖于 do_b，而 do_b 又依赖于 do_a。给定这种场景，如果使用deltask删除do_b，do_c和do_a通过do_b的隐式依赖关系不再存在，do_c依赖也不会更新到包含do_a。因此，do_c 可以在 do_a 之前自由运行。

	如果您希望这些依赖项保持不变，请使用 [noexec] varflag 禁用任务，而不是使用 deltask 命令删除它：
			do_b[noexec] = "1"

#####3.6.3 将信息传递到构建任务环境
	在运行任务时，BitBake 会严格控制构建任务的 shell 执行环境，以确保来自构建机器的有害污染不会影响构建。

			Note:
			默认情况下，BitBake 会清理环境以仅包含导出或在其传递列表中列出的内容，以确保构建环境可重现且一致。您可以通过设置 BB_PRESERVE_ENV 变量来防止这种“清理”。

	因此，如果您确实希望将某些内容传递到构建任务环境中，则必须执行以下两个步骤：

	1.告诉 BitBake 将您想要的内容从环境加载到数据存储中。您可以通过 BB_ENV_PASSTHROUGH 和 BB_ENV_PASSTHROUGH_ADDITIONS 变量来执行此操作。例如，假设您想阻止构建系统访问您的 $HOME/.ccache 目录。以下命令将环境变量 CCACHE_DIR 添加到 BitBake 的直通列表中，以允许该变量进入数据存储：
			export BB_ENV_PASSTHROUGH_ADDITIONS="$BB_ENV_PASSTHROUGH_ADDITIONS CCACHE_DIR"

	2.告诉 BitBake 将您加载到数据存储中的内容导出到每个正在运行的任务的任务环境中。将环境中的某些内容加载到数据存储区（上一步）只会使其在数据存储区中可用。要将其导出到每个正在运行的任务的任务环境，请在本地配置文件 local.conf 或分发配置文件中使用类似于以下的命令：
			export CCACHE_DIR

			Note:
			前面步骤的副作用是 BitBake 将变量记录为构建过程的依赖项，例如设置场景校验和。如果这样做会导致不必要的任务重建，您还可以标记该变量，以便 setscene 代码在创建校验和时忽略依赖关系。

	有时，能够从原始执行环境中获取信息很有用。 BitBake 将原始环境的副本保存到名为 BB_ORIGENV 的特殊变量中。

	BB_ORIGENV 变量返回一个数据存储对象，该对象可以使用标准数据存储运算符（例如 getVar(, False)）进行查询。数据存储对象很有用，例如，用于查找原始 DISPLAY 变量。这是一个例子：
			origenv = d.getVar("BB_ORIGENV", False)
			bar = origenv.getVar("BAR", False)
	前面的示例从原始执行环境返回 BAR。

####3.7 变量标志
	变量标志 (varflags) 有助于控制任务的功能和依赖关系。 BitBake 使用以下命令形式读取和写入 varflags 到数据存储：
			variable = d.getVarFlags("variable")
			self.d.setVarFlags("FOO", {"func": True})
	使用 varflags 时，除了覆盖之外，同样的语法适用。换句话说，您可以像变量一样设置、附加和预先添加 varflags。有关详细信息，请参阅“变量标志语法”部分。

	BitBake 有一组定义的 varflags 可用于配方和类。任务支持许多控制任务的各种功能的标志：
		- [cleandirs]：应该在任务运行之前创建的空目录。已存在的目录将被删除并重新创建以清空它们。
		- [depends]：控制任务间的依赖关系。有关详细信息，请参阅 DEPENDS 变量和“任务间依赖关系”部分。
		- [deptask]：控制任务构建时的依赖关系。有关更多信息，请参阅 DEPENDS 变量和“构建依赖项”部分。
		- [dirs]：任务运行前应创建的目录。已经存在的目录保持原样。列出的最后一个目录用作任务的当前工作目录。
		- [lockfiles]：指定在任务执行时要锁定的一个或多个锁定文件。只有一个任务可能持有一个锁文件，任何尝试锁定已锁定文件的任务都将被阻塞，直到锁被释放。您可以使用此变量标志来完成互斥。
		- [noexec]：设置为“1”时，将任务标记为空，不需要执行。您可以使用 [noexec] 标志将任务设置为依赖占位符，或禁用在其他地方定义的特定配方中不需要的任务。
		- [nostamp]：当设置为“1”时，告诉 BitBake 不为任务生成戳文件，这意味着应该始终执行该任务。

			Caution:
			任何依赖于（可能是间接地）[nostamp] 任务的任务也总是会被执行。如果您不小心，这可能会导致不必要的重建。

		- [number_threads]：在执行期间将任务限制为特定数量的并发线程。当您的构建主机具有大量内核但某些任务由于各种资源限制（例如，避免网络节流）需要进行速率限制时，此 varflag 很有用。 number_threads 的工作方式与 BB_NUMBER_THREADS 变量类似，但特定于任务。
		全局设置值。例如，以下确保 do_fetch 任务使用不超过两个同时执行的线程： do_fetch[number_threads] = “2”

			Warning:
			在单个配方中而不是全局设置 varflag 会导致不可预知的行为。
			将 varflag 设置为大于 BB_NUMBER_THREADS 变量中使用的值会导致 number_threads 无效。

		- [postfuncs]：任务完成后要调用的函数列表。
		- [prefuncs]：任务执行前要调用的函数列表。
		- [rdepends]：控制任务间运行时依赖关系。有关详细信息，请参阅 RDEPENDS 变量、RRECOMMENDS 变量和“任务间依赖关系”部分。
		- [rdeptask]：控制任务运行时依赖关系。有关详细信息，请参阅 RDEPENDS 变量、RRECOMMENDS 变量和“运行时依赖项”部分。
		- [recideptask]：与 recrdeptask 一起设置时，指定应检查其他依赖项的任务。
		- [recrdeptask]：控制任务递归运行时依赖关系。有关详细信息，请参阅 RDEPENDS 变量、RRECOMMENDS 变量和“递归依赖项”部分。
		- [stamp-extra-info]：附加到任务标记的额外标记信息。例如，OpenEmbedded 使用此标志来允许特定于机器的任务。
		- [umask]：运行任务的 umask。
	有几个 varflags 可用于控制如何计算变量的签名。有关此过程的更多信息，请参阅“校验和（签名）”部分。
		- [vardeps]：指定以空格分隔的附加变量列表，以添加到变量的依赖项中，以计算其签名。将变量添加到此列表中很有用，例如，当函数以不允许 BitBake 自动确定变量被引用的方式引用变量时。
		- [vardepsexclude]：指定一个以空格分隔的变量列表，这些变量应该从变量的依赖项中排除，以便计算其签名。
		- [vardepvalue]：如果设置，则指示 BitBake 忽略变量的实际值，而在计算变量的签名时使用指定的值。
		- [vardepvalueexclude]：指定在计算变量签名时要从变量值中排除的字符串的管道分隔列表。

####3.8 事件
	BitBake 允许在配方和类文件中安装事件处理程序。事件在操作期间的某些点触发，例如针对给定配方（即 *.bb）的操作开始、给定任务的开始、任务失败、任务成功等。目的是让构建失败时的电子邮件通知等操作变得容易。

	以下是打印事件名称和 FILE 变量内容的示例事件处理程序：
			addhandler myclass_eventhandler
			python myclass_eventhandler() {
				from bb.event import getName
				print("The name of the Event is %s" % getName(e))
				print("The file we run for is %s" % d.getVar('FILE'))
			}
			myclass_eventhandler[eventmask] = "bb.event.BuildStarted
			bb.event.BuildCompleted"

	在前面的示例中，已经设置了一个事件掩码，因此处理程序只能看到“BuildStarted”和“BuildCompleted”事件。每次触发与事件掩码匹配的事件时，都会调用此事件处理程序。定义了一个全局变量“e”，它代表当前事件。使用 getName(e) 方法，您可以获得触发事件的名称。全局数据存储以“d”的形式提供。在遗留代码中，您可能会看到用于获取数据存储的“e.data”。但是，请意识到“e.data”已被弃用，您应该继续使用“d”。

	数据存储的上下文适用于相关事件。例如，“BuildStarted”和“BuildCompleted”事件在任何任务执行之前运行，因此将在全局配置数据存储命名空间中。该命名空间中不存在特定于配方的元数据。 “BuildStarted”和“BuildCompleted”事件也在主炊具/服务器进程而不是任何工作上下文中运行。因此，对数据存储所做的任何更改都将被当前构建中的其他炊具/服务器事件看到，但在该构建之外或任何工作人员上下文中都看不到。任务事件在所讨论的实际任务中运行，因此具有特定于配方和特定于任务的内容。这些事件在工作者上下文中运行，并在任务执行结束时被丢弃。

	在标准构建期间，可能会发生以下常见事件。以下事件是大多数元数据可能有兴趣查看的最常见类型的事件：
		- bb.event.ConfigParsed()：基本配置时触发；其中包括 bitbake.conf、base.bbclass 和任何全局 INHERIT 语句；已被解析。当每个工作人员解析基本配置或服务器更改配置并重新解析时，您可以看到多个此类事件。然而，任何给定的数据存储只有一个这样的事件对其执行。如果事件处理程序在数据存储中设置了 BB_INVALIDCONF，则会重新解析配置并触发新事件，从而允许元数据更新配置。
		- bb.event.HeartbeatEvent()：以一秒的固定时间间隔触发。您可以使用 BB_HEARTBEAT_EVENT 变量配置间隔时间。事件的“时间”属性是触发事件时的 time.time() 值。此事件对于系统状态监视等活动很有用。
		- bb.event.ParseStarted()：当 BitBake 即将开始解析食谱时触发。此事件的“total”属性表示 BitBake 计划解析的食谱数量。
		- bb.event.ParseProgress()：在解析过程中触发。此事件的“当前”属性是已解析的食谱数量以及“总”属性。
		- bb.event.ParseCompleted()：解析完成时触发。该事件的“cached”、“parsed”、“skipped”、“virtuals”、“masked”和“errors”属性提供解析结果的统计信息。
		- bb.event.BuildStarted()：新构建开始时触发。当启用多个配置 (multiconfig) 时，BitBake 会触发多个“BuildStarted”事件（每个配置一个）。
		- bb.build.TaskStarted()：任务开始时触发。此事件的“taskfile”属性指向任务源自的配方。 “taskname”属性，即任务名称，包含 do_ 前缀，“logfile”属性指向存储任务输出的位置。最后，“时间”属性是任务的执行开始时间。
		- bb.build.TaskInvalid()：如果 BitBake 尝试执行不存在的任务，则触发。
		- bb.build.TaskFailedSilent()：为失败的场景任务触发，不应详细地呈现给用户。
		- bb.build.TaskFailed()：为失败的正常任务触发。
		- bb.build.TaskSucceeded()：任务成功完成时触发。
		- bb.event.BuildCompleted()：构建完成时触发。
		- bb.cooker.CookerExit()：当 BitBake 服务器/炊具关闭时触发。这个事件通常只被 UI 视为他们也应该关闭的标志。
	下一个示例事件列表基于对服务器的特定请求而发生。这些事件通常用于将更大的信息从 BitBake 服务器传递到 BitBake 的其他部分，例如用户界面：
		- bb.event.TreeDataPreparationStarted()
		- bb.event.TreeDataPreparationProgress()
		- bb.event.TreeDataPreparationCompleted()
		- bb.event.DepTreeGenerated()
		- bb.event.CoreBaseFilesFound()
		- bb.event.ConfigFilePathFound()
		- bb.event.FilesMatchingFound()
		- bb.event.ConfigFilesFound()
		- bb.event.TargetsTreeGenerated()

####3.9 变体——类扩展机制
	BitBake 通过 BBCLASSEXTEND 变量支持配方文件的多个化身。

	BBCLASSEXTEND 变量是一个空格分隔的类列表，用于“扩展”每个变体的配方。这是一个导致当前配方的第二个化身可用的示例。这第二个化身将继承“本机”类。
			BBCLASSEXTEND = "native"

			Note:
			此类扩展的机制非常特定于实现。通常，配方的 PROVIDES 、 PN 和 DEPENDS 变量需要由扩展类修改。有关具体示例，请参阅 OE-Core native 、 nativesdk 和 multilib 类。


####3.10 依赖
	为了实现高效的并行处理，BitBake 在任务级别处理依赖关系。依赖关系既可以存在于单个配方中的任务之间，也可以存在于不同配方中的任务之间。以下是每个示例：
		- 对于单个配方中的任务，配方的 do_configure 任务可能需要在其 do_compile 任务运行之前完成。
		- 对于不同配方中的任务，一个配方的 do_configure 任务可能需要另一个配方的 do_populate_sysroot 任务首先完成，以便另一个配方提供的库和头文件可用。
	本节介绍了几种声明依赖关系的方法。请记住，即使以不同的方式声明依赖关系，它们都只是任务之间的依赖关系。

#####3.10.1 .bb 文件内部的依赖关系
	BitBake 使用 addtask 指令来管理给定配方文件内部的依赖关系。您可以使用 addtask 指令来指示任务何时依赖于其他任务或其他任务何时依赖于该配方。这是一个例子：
			addtask printdate after do_fetch before do_build
	在本例中，do_printdate 任务依赖于 do_fetch 任务的完成，do_build 任务依赖于 do_printdate 任务的完成。

			Note:
			对于要运行的任务，它必须是计划运行的某个其他任务的直接或间接依赖项。
			为了说明，这里有一些例子：
				- 指令 addtask mytask before do_configure 导致 do_mytask 在 do_configure 运行之前运行。请注意，do_mytask 仅在其输入校验和自上次运行后发生更改时才运行。对 do_mytask 的输入校验和的更改也间接导致 do_configure 运行。
				- do_configure 之后的指令 addtask mytask 本身永远不会导致 do_mytask 运行。 do_mytask 仍然可以手动运行，如下所示：
					$ bitbake recipe -c mytask
			将 do_mytask 声明为计划运行的其他一些任务的依赖项也会导致它运行。无论如何，任务在 do_configure 之后运行。

#####3.10.2 构建依赖
	BitBake 使用 DEPENDS 变量来管理构建时间依赖性。任务的 [deptask] varflag 表示 DEPENDS 中列出的每个项目的任务，必须完成才能执行该任务。这是一个例子：
			do_configure[deptask] = "do_populate_sysroot"
	在此示例中，DEPENDS 中每个项目的 do_populate_sysroot 任务必须在 do_configure 执行之前完成。

#####3.10.3 运行时依赖
	BitBake 使用 PACKAGES、RDEPENDS 和 RRECOMMENDS 变量来管理运行时依赖项。

	PACKAGES 变量列出运行时包。这些包中的每一个都可以具有 RDEPENDS 和 RRECOMMENDS 运行时依赖项。任务的 [rdeptask] 标志用于表示每个项目运行时依赖项的任务，该任务必须在执行该任务之前完成。
			do_package_qa[rdeptask] = "do_packagedata"
	在前面的例子中，RDEPENDS 中每一项的 do_packagedata 任务必须已经完成，do_package_qa 才能执行。尽管 RDEPENDS 包含来自运行时依赖命名空间的条目，但 BitBake 知道如何将它们映射回定义任务的构建时依赖命名空间。

#####3.10.4 递归依赖
	BitBake 使用 [recrdeptask] 标志来管理递归任务依赖关系。 BitBake 查看当前配方的构建时和运行时依赖项，查看任务的任务间依赖项，然后为列出的任务添加依赖项。一旦 BitBake 完成了这项工作，它就会递归地处理这些任务的依赖关系。迭代过程继续进行，直到发现并添加了所有依赖项。

	[recrdeptask] 标志最常用于需要等待某些任务“全局”完成的高级配方中。例如， image.bbclass 有以下内容：
			do_rootfs[recrdeptask] += "do_packagedata"
	该语句表示，当前配方的 do_packagedata 任务和从图像配方可到达的所有配方（通过依赖关系）必须在 do_rootfs 任务运行之前运行。

	BitBake 允许任务通过在任务列表中引用自身来递归地依赖自身：
			do_a[recrdeptask] = "do_a do_b"
	与以前一样，这意味着当前配方的 do_a 和 do_b 任务以及从配方可到达（通过依赖关系）的所有配方必须在 do_a 任务运行之前运行。在这种情况下，BitBake 将忽略当前配方对自身的 do_a 任务循环依赖。

#####3.10.5 任务间依赖
	BitBake 以更通用的形式使用 [depends] 标志来管理任务间依赖关系。这种更通用的形式允许对特定任务进行相互依赖检查，而不是检查 DEPENDS 中的数据。这是一个例子：
			do_patch[depends] = "quilt-native:do_populate_sysroot"
	在此示例中，目标 quilt-native 的 do_populate_sysroot 任务必须已完成，do_patch 任务才能执行。
	[rdepends] 标志以类似的方式工作，但在运行时命名空间而不是构建时依赖命名空间中获取目标。

####3.11 可以在 Python 中调用的函数
	BitBake 提供了许多可以从 Python 函数中调用的函数。本节列出了最常用的函数，并提到了在哪里可以找到其他函数。

#####3.11.1 访问数据存储变量的函数
	通常需要使用 Python 函数访问 BitBake 数据存储中的变量。 BitBake 数据存储有一个 API，允许您进行此访问。以下是可用操作的列表：
___
	Operation						Description
	d.getVar("X", expand)
		返回变量“X”的值。使用“expand=True”扩展值。如果变量“X”不存在，则返回“None”。
	d.setVar("X", "value")
		将变量“X”设置为“值”
	d.appendVar("X", "value")
		将“value”添加到变量“X”的末尾。如果变量“X”不存在，则类似于 d.setVar("X", "value")。
	d.prependVar("X", "value")
		将“value”添加到变量“X”的开头。如果变量“X”不存在，则行为类似于 d.setVar("X","value")。
	d.delVar("X")
		从数据存储中删除变量“X”。如果变量“X”不存在，则不执行任何操作。
	d.renameVar("X", "Y")
		将变量“X”重命名为“Y”。如果变量“X”不存在，则不执行任何操作。
	d.getVarFlag("X", flag, expand)
		返回变量“X”的值。使用“expand=True”扩展值。如果变量“X”或命名标志不存在，则返回“None”。
	d.setVarFlag("X", flag, "value")
		将变量“X”的命名标志设置为“值”。
	d.appendVarFlag("X", flag, "value")
		将“value”附加到变量“X”上的命名标志。如果命名标志不存在，则行为类似于 d.setVarFlag("X", flag, "value")。
	d.prependVarFlag("X", flag, "value")
		将“值”添加到变量“X”上的命名标志。如果命名标志不存在，则行为类似于 d.setVarFlag("X", flag, "value")。
	d.delVarFlag("X", flag)
		从数据存储中删除变量“X”上的命名标志。
	d.setVarFlags("X", flagsdict)
		设置 flagsdict() 参数中指定的标志。 setVarFlags 不会清除以前的标志。将此操作视为 addVarFlags。
	d.getVarFlags("X")
		返回变量“X”的标志的标志字典。如果变量“X”不存在，则返回“None”。
	d.delVarFlags("X")
		删除变量“X”的所有标志。如果变量“X”不存在，则不执行任何操作。
	d.expand(expression)
		展开指定字符串表达式中的变量引用。对不存在的变量的引用保持原样。例如，如果变量“X”不存在，d.expand("foo ${X}") 将扩展为文字字符串“foo ${X}”。
___

#####3.11.2 其他功能
	通过查看 bb 模块的源代码，您可以找到许多其他可以从 Python 调用的函数，该模块位于 bitbake/lib/bb 中。例如，bitbake/lib/bb/utils.py 包含常用的函数 bb.utils.contains() 和 bb.utils.mkdirhier()，它们都带有 docstrings。

####3.12 任务校验和和 Setscene
	BitBake 使用校验和（或签名）以及场景来确定是否需要运行任务。本节介绍该过程。为了帮助理解 BitBake 如何做到这一点，本节假设了一个基于 OpenEmbedded 元数据的示例。

	这些校验和存储在 STAMP 中。您可以使用以下 BitBake 命令检查校验和：
			$ bitbake-dumpsigs
	此命令以可读格式返回签名数据，允许您检查 OpenEmbedded 构建系统生成签名时使用的输入。例如，使用 bitbake-dumpsigs 可以检查 C 应用程序（例如 bash）的 do_compile 任务的“sigdata”。运行该命令还显示“CC”变量是散列输入的一部分。对此变量的任何更改都会使标记无效并导致 do_compile 任务运行。

	以下列表描述了相关变量：
		- BB_HASHCHECK_FUNCTION：指定要在任务执行的“setscene”部分调用的函数的名称，以验证任务哈希列表。
		- BB_SETSCENE_DEPVALID：指定 BitBake 调用的函数，该函数确定 BitBake 是否需要满足场景依赖关系。
		- BB_TASKHASH：在执行任务中，此变量保存当前启用的签名生成器返回的任务哈希。
		- STAMP：创建图章文件的基本路径。
		- STAMPCLEAN：同样，创建戳文件的基本路径，但可以使用通配符匹配一系列文件以进行干净操作。

####3.13 变量中的通配符支持
	对变量中通配符使用的支持因使用它的上下文而异。例如，某些变量和文件名允许通过“%”和“*”字符限制使用通配符。其他变量或名称支持 Python 的 glob 语法、fnmatch 语法或正则表达式 (re) 语法。
	对于支持通配符的变量，文档描述了通配符的形式、用途及其限制。

###4 文件下载支持
	BitBake 的 fetch 模块是一个独立的库代码，它处理从远程系统下载源代码和文件的复杂性。获取源代码是构建软件的基石之一。因此，该模块构成了 BitBake 的重要组成部分。

	当前的 fetch 模块称为“fetch2”，指的是它是 API 的第二个主要版本。原始版本已过时，已从代码库中删除。因此，在所有情况下，“fetch”在本手册中都是指“fetch2”。

####4.1 下载（Fetch）
	BitBake 在获取源代码或文件时需要几个步骤。 fetcher 代码库按顺序处理两个不同的过程：从某个地方（缓存或其他方式）获取文件，然后将这些文件解压缩到特定位置，也许以特定方式。获取和解压缩文件通常可以选择在打补丁之后进行。但是，此模块不涉及修补。
	执行这个过程的第一部分的代码，一个 fetch，看起来像下面这样：
			src_uri = (d.getVar('SRC_URI') or "").split()
			fetcher = bb.fetch2.Fetch(src_uri, d)
			fetcher.download()
	此代码设置 fetch 类的实例。该实例使用来自 SRC_URI 变量的以空格分隔的 URL 列表，然后调用 download 方法来下载文件。
	fetch 类的实例化之后通常是：
			rootdir = l.getVar('WORKDIR')
			fetcher.unpack(rootdir)
	此代码将下载的文件解压缩到 WORKDIR 指定的文件。

			Note:
			为方便起见，这些示例中的命名与 OpenEmbedded 使用的变量相匹配。如果您想查看上面的代码，请检查 OpenEmbedded 类文件 base.bbclass 。

	SRC_URI 和 WORKDIR 变量没有硬编码到 fetcher 中，因为这些 fetcher 方法可以（并且被）用不同的变量名调用。例如，在 OpenEmbedded 中，共享状态 (sstate) 代码使用 fetch 模块来获取 sstate 文件。

	当调用 download() 方法时，BitBake 会尝试通过按特定搜索顺序查找源文件来解析 URL：
			- 预镜像站点：BitBake 首先使用预镜像来尝试查找源文件。这些位置是使用 PREMIRRORS 变量定义的。
			- 源 URI：如果预镜像失败，BitBake 使用原始 URL（例如来自 SRC_URI）。
			- 镜像站点：如果发生获取失败，BitBake 接下来使用由 MIRRORS 变量定义的镜像位置。
	对于传递给 fetcher 的每个 URL，fetcher 调用处理该特定 URL 类型的子模块。当您为 SRC_URI 变量提供 URL 时，这种行为可能会造成一些混乱。考虑以下两个 URL：
			https://git.yoctoproject.org/git/poky;protocol=git
			git://git.yoctoproject.org/git/poky;protocol=http
	在前一种情况下，URL 被传递给 wget 提取器，它不理解“git”。因此，后一种情况是正确的形式，因为 Git 提取器确实知道如何使用 HTTP 作为传输。
	以下是一些显示常用镜像定义的示例：
			PREMIRRORS ?= "\
			   bzr://.*/.\*  http://somemirror.org/sources/ \
			   cvs://.*/.\*  http://somemirror.org/sources/ \
			   git://.*/.\*  http://somemirror.org/sources/ \
			   hg://.*/.\*   http://somemirror.org/sources/ \
			   osc://.*/.\*  http://somemirror.org/sources/ \
			   p4://.*/.\*   http://somemirror.org/sources/ \
			  svn://.*/.\*   http://somemirror.org/sources/"

			MIRRORS =+ "\
			   ftp://.*/.\*   http://somemirror.org/sources/ \
			   http://.*/.\*  http://somemirror.org/sources/ \
			   https://.*/.\* http://somemirror.org/sources/"
	请注意，BitBake 支持跨 URL。可以将 HTTP 服务器上的 Git 存储库镜像为 tarball。这就是前面示例中的 git:// 映射所做的。
	由于网络访问速度很慢，BitBake 会维护从网络下载的文件的缓存。任何非本地的源文件（即从 Internet 下载的）都放在下载目录中，该目录由 DL_DIR 变量指定。
	文件完整性对于复制构建至关重要。对于非本地存档下载，提取器代码可以验证 SHA-256 和 MD5 校验和，以确保存档已正确下载。您可以通过使用带有适当 varflags 的 SRC_URI 变量来指定这些校验和，如下所示：
			SRC_URI[md5sum] = "value"
			SRC_URI[sha256sum] = "value"
	您还可以将校验和指定为 SRC_URI 上的参数，如下所示：
			SRC_URI = "http://example.com/foobar.tar.bz2;md5sum=4a8e0f237e961fd7785d19d07fdb994d"
	如果存在多个 URI，您可以像前面的示例一样直接指定校验和，也可以命名 URL。以下语法显示了如何命名 URI：
			SRC_URI = "http://example.com/foobar.tar.bz2;name=foo"
			SRC_URI[foo.md5sum] = 4a8e0f237e961fd7785d19d07fdb994d
	下载文件并检查其校验和后，将在 DL_DIR 中放置一个“.done”标记。 BitBake 在后续构建期间使用此标记以避免再次下载或比较文件的校验和。

			Note:
			假定本地存储不受数据损坏的影响。如果不是这种情况，就会有更大的问题需要担心。

	如果设置了 BB_STRICT_CHECKSUM，任何没有校验和的下载都会触发错误消息。 BB_NO_NETWORK 变量可用于使任何尝试的网络访问都成为致命错误，这对于检查镜像是否完整以及其他事情很有用。

	如果 BB_CHECK_SSL_CERTS 设置为 0，则 SSL 证书检查将被禁用。此变量默认为 1，因此通常会检查 SSL 证书。

####4.2 拆包
	解压过程通常紧随下载之后。对于除 Git URL 之外的所有 URL，BitBake 使用通用的解包方法。

	您可以在 URL 中指定许多参数来控制解包阶段的行为：
		- unpack：控制是否对 URL 组件进行解包。如果设置为“1”（默认值），则解包组件。如果设置为“0”，解包阶段将单独保留文件。当您希望将存档复制进去而不是解压缩时，此参数很有用。
		- dos：适用于 .zip 和 .jar 文件，并指定是否对文本文件使用 DOS 行尾转换。
		- striplevel：在提取时从文件名中去除指定数量的前导组件（级别）
		- subdir：将特定 URL 解包到根目录中的指定子目录。

	unpack 调用会自动解压缩并解压缩带有“.Z”、“.z”、“.gz”、“.xz”、“.zip”、“.jar”、“.ipk”、“.rpm”的文件。 “.srpm”、“.deb”和“.bz2”扩展名以及tarball扩展名的各种组合。

	如前所述，Git fetcher 有自己的 unpack 方法，该方法已针对 Git 树进行了优化。基本上，此方法通过将树克隆到最终目录来工作。该过程使用引用完成，因此只需要一个 Git 元数据的中央副本。

####4.3 提取器
	如前所述，URL 前缀决定了 BitBake 使用哪个 fetcher 子模块。每个子模块可以支持不同的 URL 参数，这些参数将在以下部分中描述。

#####4.3.1 本地文件获取器（file://）
	该子模块处理以 file:// 开头的 URL。您在 URL 中指定的文件名可以是文件的绝对路径或相对路径。如果文件名是相对的，则 FILESPATH 变量的内容的使用方式与使用 PATH 查找可执行文件的方式相同。如果找不到该文件，则假定在调用 download() 方法时它在 DL_DIR 中可用。

	如果指定目录，则解压整个目录。

	以下是几个示例 URL，第一个相对 URL，第二个绝对 URL：
			SRC_URI = "file://relativefile.patch"
			SRC_URI = "file:///Users/ich/very_important_software"

#####4.3.2 HTTP/FTP wget 获取 (http://, ftp://, https://)
	此提取器从 Web 和 FTP 服务器获取文件。在内部，提取器使用 wget 实用程序。

	使用的可执行文件和参数由 FETCHCMD_wget 变量指定，默认为合理值。 fetcher 支持参数“downloadfilename”，允许指定下载文件的名称。在处理多个同名文件时，指定下载文件的名称有助于避免 DL_DIR 中的冲突。

	如果在 SRC_URI 中指定了用户名和密码，则基本授权标头将添加到每个请求，包括跨重定向。要将 Authorization 标头限制为第一个请求，请将“redirectauth=0”添加到参数列表中。

	一些示例 URL 如下所示：
			SRC_URI = "http://oe.handhelds.org/not_there.aac"
			SRC_URI = "ftp://oe.handhelds.org/not_there_as_well.aac"
			SRC_URI = "ftp://you@oe.handhelds.org/home/you/secret.plan"



			Note
			由于 URL 参数由分号分隔，因此在解析也包含分号的 URL 时会引入歧义，例如：
				SRC_URI = "http://abc123.org/git/?p=gcc/gcc.git;a=snapshot;h=a5dd47"
			应该通过用“&”字符替换分号来修改此类 URL：
				SRC_URI = "http://abc123.org/git/?p=gcc/gcc.git&a=snapshot&h=a5dd47"
			在大多数情况下，这应该有效。万维网联盟 (W3C) 建议对查询中的分号和“&”一视同仁。请注意，由于 URL 的性质，您可能还必须指定下载文件的名称：
				SRC_URI = "http://abc123.org/git/?p=gcc/gcc.git&a=snapshot&h=a5dd47;downloadfilename=myfile.bz2"

#####4.3.3 CVS 提取器 ((cvs://)
	该子模块处理从 CVS 版本控制系统中检出文件。您可以使用许多不同的变量对其进行配置：
		- FETCHCMD_cvs：运行 cvs 命令时使用的可执行文件的名称。这个名字通常是“cvs”。
		- SRCDATE：获取 CVS 源代码时使用的日期。 “now”的特殊值会导致每次构建时都更新结帐。
		- CVSDIR：指定临时结账的保存位置。该位置通常是 DL_DIR/cvs。
		- CVS_PROXY_HOST：用作 cvs 命令的“proxy=”参数的名称。
		- CVS_PROXY_PORT：用作 cvs 命令的“proxyport=”参数的端口号。

	除了标准的用户名和密码 URL 语法，您还可以使用各种 URL 参数配置 fetcher：

	支持的参数如下：
			- “方法”：与 CVS 服务器通信的协议。默认情况下，此协议是“pserver”。如果“method”设置为“ext”，BitBake 会检查“rsh”参数并设置 CVS_RSH。您可以将“dir”用于本地目录。
			- “module”：指定要检出的模块。您必须提供此参数。
			- “tag”：描述应使用哪个 CVS TAG 进行结帐。默认情况下，TAG 为空。
			- “日期”：指定日期。如果未指定“日期”，则配置的 SRCDATE 用于签出特定日期。 “now”的特殊值导致每次构建时都更新结帐。
			- “localdir”：用于重命名模块。实际上，您正在重命名模块解压缩到的输出目录。您正在强制模块进入相对于 CVSDIR 的特殊目录。
			- “rsh”：与“method”参数结合使用。
			- “scmdata”：当设置为“keep”时，使 CVS 元数据保存在 fetcher 创建的 tarball 中。压缩包被展开到工作目录中。默认情况下，CVS 元数据被删除。
			- “fullpath”：控制生成的检出是在模块级别（默认）还是在更深的路径。
			- “norecurse”：使 fetcher 只签出指定的目录，而不递归到任何子目录。
			- “端口”：CVS 服务器连接的端口。

	一些示例 URL 如下所示：
			SRC_URI = "cvs://CVSROOT;module=mymodule;tag=some-version;method=ext"
			SRC_URI = "cvs://CVSROOT;module=mymodule;date=20060126;localdir=usethat"

#####4.3.4 子版本（SVN）提取器（svn://）
	这个 fetcher 子模块从 Subversion 源代码控制系统中获取代码。使用的可执行文件由 FETCHCMD_svn 指定，默认为“svn”。 fetcher 的临时工作目录由 SVNDIR 设置，通常为 DL_DIR/svn。
	支持的参数如下：
			- “module”：要签出的 svn 模块的名称。您必须提供此参数。您可以将此参数视为您想要的存储库数据的顶级目录。
			- “path_spec”：签出指定 svn 模块的特定目录。
			- “protocol”：要使用的协议，默认为“svn”。如果“protocol”设置为“svn+ssh”，也使用“ssh”参数。
			- “rev”：要签出的源代码的修订版本。
			- “scmdata”：设置为“keep”时，使“.svn”目录在编译时可用。默认情况下，这些目录被删除。
			- “ssh”：当“protocol”设置为“svn+ssh”时使用的可选参数。你可以使用这个参数来指定svn使用的ssh程序。
			- “transportuser”：需要时，设置传输的用户名。默认情况下，该参数为空。传输用户名不同于主 URL 中使用的用户名，后者被传递给 subversion 命令。

	以下是使用 svn 的三个示例：
			SRC_URI = "svn://myrepos/proj1;module=vip;protocol=http;rev=667"
			SRC_URI = "svn://myrepos/proj1;module=opie;protocol=svn+ssh"
			SRC_URI = "svn://myrepos/proj1;module=trunk;protocol=http;path_spec=${MY_DIR}/proj1"

#####4.3.5 Git 提取器 (git://)
	这个 fetcher 子模块从 Git 源代码控制系统中获取代码。提取器通过将远程的裸克隆创建到 GITDIR 中来工作，它通常是 DL_DIR/git2。然后，在检出特定树时，在解包阶段将此裸克隆克隆到工作目录中。这是通过使用替代品和参考来完成的，以最大限度地减少磁盘上的重复数据量并加快解包过程。可以使用 FETCHCMD_git 设置使用的可执行文件。
	此 fetcher 支持以下参数：
		- “协议”：用于获取文件的协议。设置主机名时，默认值为“git”。如果未设置主机名，则 Git 协议为“文件”。您还可以使用“http”、“https”、“ssh”和“rsync”。

					Note：
					当协议为“ssh”时，SRC_URI 中预期的 URL 与通常传递给 git clone 命令并由 Git 服务器提供以从中获取的 URL 不同。例如，通过 SSH 克隆时，GitLab 服务器为 mesa 返回的 URL 是 git@gitlab.freedesktop.org:mesa/mesa.git，但是 SRC_URI 中的预期 URL 如下：
						SRC_URI = "git://git@gitlab.freedesktop.org/mesa/mesa.git;branch=main;protocol=ssh;..."
					请注意：在项目路径之前为 / 更改了字符。

		- “nocheckout”：设置为“1”时，告诉 fetcher 在解包时不签出源代码。为有自定义例程检出代码的 URL 设置此选项。默认值为“0”。
		- “rebaseable”：表示上游 Git 存储库可以rebase。如果修订可以与分支分离，则应将此参数设置为“1”。在这种情况下，源镜像 tarball 是按修订完成的，这会降低效率。重新定位上游 Git 存储库可能会导致当前修订版从上游存储库中消失。此选项提醒 fetcher 小心保留本地缓存以备将来使用。此参数的默认值为“0”。
		- “nobranch”：告诉 fetcher 在设置为“1”时不检查分支的 SHA 验证。默认值为“0”。为引用对标记而不是分支有效的提交的配方设置此选项。
		- “bareclone”：告诉 fetcher 将一个裸克隆克隆到目标目录中，而不检查工作树。仅提供原始 Git 元数据。该参数也暗示了“nocheckout”参数。
		- “分支”：要克隆的 Git 树的分支。除非“nobranch”设置为“1”，否则这是一个强制参数。分支参数的数量必须与名称参数的数量相匹配。
		- “rev”：用于结帐的修订。默认为“主”。
		- “tag”：指定用于结帐的标签。要正确解析标签，BitBake 必须访问网络。因此，通常不使用标签。就 Git 而言，“tag”参数的行为实际上与“rev”参数相同。
		- “子路径”：将结帐限制为树的特定子路径。默认情况下，检出整个树。
		- “destsuffix”：放置结帐的路径的名称。默认情况下，路径是 git/。
		- “usehead”：允许本地 git:// URL 使用当前分支 HEAD 作为修订版，以与 AUTOREV 一起使用。 “usehead”参数意味着没有分支，并且仅在传输协议为 file:// 时才有效。

	以下是一些示例 URL：
			SRC_URI = "git://github.com/fronteed/icheck.git;protocol=https;branch=${PV};tag=${PV}"
			SRC_URI = "git://github.com/asciidoc/asciidoc-py;protocol=https;branch=main"
			SRC_URI = "git://git@gitlab.freedesktop.org/mesa/mesa.git;branch=main;protocol=ssh;..."

			Note:
			使用 git 作为软件主要源代码的 fetcher 时，应相应设置 S：
				S = "${WORKDIR}/git"

			Note:
			不支持直接在 git:// urls 中指定密码。有几个原因： SRC_URI 经常写到日志等地方，很容易泄露密码；在不删除密码的情况下共享元数据也很容易。 SSH 密钥、~/.netrc 和 ~/.ssh/config 文件可用作替代方案。

#####4.3.6 Git 子模块提取器（gitsm://）
	这个 fetcher 子模块继承自 Git fetcher，并通过获取存储库的子模块来扩展该 fetcher 的行为。 SRC_URI 被传递给 Git 提取器，如 Git Fetcher (git://) 部分中所述。

			Note:
			在“git://”和“gitsm://”URL 之间切换时，您必须清理配方。
			Git 子模块提取器不是完整的提取器实现。 fetcher 存在无法正确使用正常源镜像基础架构的已知问题。此外，它获取的子模块源对许可和源归档基础架构不可见。

#####4.3.7 ClearCase 提取器 (ccrc://)
	这个 fetcher 子模块从 ClearCase 存储库中获取代码。
	要使用此提取器，请确保您的配方具有正确的 SRC_URI、SRCREV 和 PV 设置。这是一个例子：
			SRC_URI = "ccrc://cc.example.org/ccrc;vob=/example_vob;module=/example_module"
			SRCREV = "EXAMPLE_CLEARCASE_TAG"
			PV = "${@d.getVar("SRCREV", False).replace("/", "+")}"
	提取器使用 rcleartool 或 cleartool 远程客户端，具体取决于哪个可用。
	以下是 SRC_URI 语句的选项：
		- vob：ClearCase VOB 的名称，必须包含前置“/”字符。此选项是必需的。
		- 模块：模块，必须包含前置“/”字符，在选定的 VOB 中。

				Note:
				module 和 vob 选项结合起来在视图配置规范中创建加载规则。例如，考虑本节开头 SRC_URI 语句中的 vob 和模块值。组合这些值会产生以下结果：
					load /example_vob/example_module

		- proto：协议，可以是http，也可以是https。
	默认情况下，提取器会创建一个配置规范。如果您希望将此规范写入默认值以外的区域，请使用配方中的 CCASE_CUSTOM_CONFIG_SPEC 变量来定义写入规范的位置。

			Nore:
			如果您指定此变量，SRCREV 将失去其功能。但是，SRCREV 仍然用于在获取后标记存档，即使它没有定义获取的内容。

	以下是一些值得一提的其他行为：
		- 使用 cleartool 时，cleartool 的登录由系统处理。登录不需要特殊步骤。
		- 为了对经过身份验证的用户使用 rcleartool，在使用 fetcher 之前需要“rcleartool 登录”。

#####4.3.8 Perforce 获取 (p4://)
	这个 fetcher 子模块从 Perforce 源代码控制系统中获取代码。使用的可执行文件由 FETCHCMD_p4 指定，默认为“p4”。 fetcher 的临时工作目录由 P4DIR 设置，默认为“DL_DIR/p4”。 fetcher 不使用 perforce 客户端，而是依靠 p4 文件来检索文件列表，并通过 p4 打印在本地传输这些文件的内容。
	要使用此提取器，请确保您的配方具有正确的 SRC_URI、SRCREV 和 PV 值。 p4 可执行文件能够使用系统的 P4CONFIG 环境变量定义的配置文件来定义 Perforce 服务器 URL 和端口、用户名和密码，如果您不希望将这些值保留在配方本身中。如果您选择不使用 P4CONFIG，或者显式设置 P4CONFIG 可以包含的变量，您可以指定 P4PORT 值，即服务器的 URL 和端口号，您可以直接在 SRC_URI 中的配方中指定用户名和密码。
	这是一个依赖 P4CONFIG 指定服务器 URL 和端口、用户名和密码并获取 Head Revision 的示例：
			SRC_URI = "p4://example-depot/main/source/..."
			SRCREV = "${AUTOREV}"
			PV = "p4-${SRCPV}"
			S = "${WORKDIR}/p4"
	这是一个示例，它指定服务器 URL 和端口、用户名和密码，并根据标签获取修订：
			P4PORT = "tcp:p4server.example.net:1666"
			SRC_URI = "p4://user:passwd@example-depot/main/source/..."
			SRCREV = "release-1.0"
			PV = "p4-${SRCPV}"
			S = "${WORKDIR}/p4"

			Note：
			您应该始终在您的配方中将 S 设置为“${WORKDIR}/p4”。

	默认情况下，提取器会从本地文件路径中删除软件仓库位置。在上面的例子中，example-depot/main/source/ 的内容会放在 ${WORKDIR}/p4 中。对于需要在本地保留部分远程仓库路径的情况，提取器支持两个参数：
		- “模块”：
			要获取的顶级仓库位置或目录。此参数的值也可以指向软件仓库中的单个文件，在这种情况下，本地文件路径将包括模块路径。
		- “远程路径”：
			当与值“keep”一起使用时，提取器将在本地镜像指定位置的完整仓库路径，甚至与模块参数结合使用。
	下面是使用 module 参数的示例：
			SRC_URI = "p4://user:passwd@example-depot/main;module=source/..."
	在这种情况下，顶级目录 source/ 的内容将被提取到 ${P4DIR}，包括目录本身。顶级目录可在 ${P4DIR}/source/ 访问。
	这是 remotepath 参数的示例用法：
			SRC_URI = "p4://user:passwd@example-depot/main;module=source/...;remotepath=keep"
	在这种情况下，顶级目录 source/ 的内容将被提取到 ${P4DIR}，但完整的 depot 路径将在本地镜像。可以在 ${P4DIR}/example-depot/main/source/ 访问顶级目录。

####4.3.9 Repo 获取 (repo://)
	这个 fetcher 子模块从 google-repo 源代码控制系统中获取代码。提取器通过启动存储库的源并将其同步到 REPODIR 来工作，通常是 ${DL_DIR}/repo。

	此 fetcher 支持以下参数：
		- “protocol”：获取存储库清单的协议（默认值：git）。
		- “branch”：要获取的存储库的分支或标记（默认值：master）。
		- “manifest”：清单文件的名称（默认值：default.xml）。
	以下是一些示例 URL：
		SRC_URI = "repo://REPOROOT;protocol=git;branch=some_branch;manifest=my_manifest.xml"
		SRC_URI = "repo://REPOROOT;protocol=file;branch=some_branch;manifest=my_manifest.xml"

####4.3.10 Az 获取 (at://)
	此子模块从 Azure 存储帐户获取数据，它从 HTTP wget 获取器继承其功能，但修改其行为以适应对非公共数据使用共享访问签名 (SAS)。

	此类功能由变量设置：
		- AZ_SAS：Azure 存储共享访问签名提供对资源的安全委托访问，如果设置了此变量，Az Fetcher 将在从云中获取工件时使用它。

	您可以指定 AZ_SAS 变量，如下所示：
			AZ_SAS = "se=2021-01-01&sp=r&sv=2018-11-09&sr=c&skoid=<skoid>&sig=<signature>"
	这是一个示例网址：
			SRC_URI = "az://<azure-storage-account>.blob.core.windows.net/<foo_container>/<bar_file>"

#####4.3.11 箱子提取器 (crate://)
	这个子模块获取对应于 Rust 库和程序的 Rust 语言“板条箱”的代码以进行编译。这样的 crate 通常在 https://crates.io/ 上共享，但这个 fetcher 也支持其他 crate 注册表。
	SRC_URI 设置的格式必须是：
			SRC_URI = "crate://REGISTRY/NAME/VERSION"
	这是一个示例网址：
			SRC_URI = "crate://crates.io/glob/0.2.11"

#####4.3.12 其他提取器
	Fetch 子模块也存在于以下：
		- Bazaar (bzr://)
		- Mercurial (hg://)
		- npm (npm://)
		- OSC (osc://)
		- Secure FTP (sftp://)
		- Secure Shell (ssh://)
		- Trees using Git Annex (gitannex://)

	目前没有关于这些较少使用的 fetcher 子模块的文档。但是，您可能会发现代码有用且易读。

####4.4 自动修订
	我们需要在此处记录 AUTOREV 和 SRCREV_FORMAT。









.
6.
7.＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿

＿＿＿

＿＿＿
