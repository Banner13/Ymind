[原文地址](https://docs.yoctoproject.org/bitbake/2.0/index.html)


	
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
        VI 支持多种构建和目标操作系统（例如 Cygwin、BSD 等）。
        是独立的，而不是紧密集成到构建机器的根文件系统中。
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

[](./1525_1.png)

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

	邮票的确切格式是部分可配置的。在现代版本的 BitBake 中，将哈希附加到标记上，以便如果配置更改，标记将变为无效并且任务会自动重新运行。此散列或使用的签名由配置的签名策略管理（有关信息，请参阅校验和（签名）部分）。也可以使用 [stamp-extra-info] 任务标志将额外的元数据附加到图章。例如，OpenEmbedded 使用此标志来使某些任务特定于机器。

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
＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿
＿＿＿

＿＿＿

＿＿＿
