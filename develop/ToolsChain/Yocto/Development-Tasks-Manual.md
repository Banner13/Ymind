[TOC]



## Yocto Project Develoment Tasks Manual
<p>Kirkstone(4.0.999)</p>

### 1 Yocto 项目开发任务手册
#### 1.1 Welcome
<p>欢迎使用 Yocto 项目开发任务手册。本手册提供了在 Yocto Project 环境中开发所需的相关程序（即开发在目标设备上运行的嵌入式 Linux 映像和用户空间应用程序）。本手册将相关过程分组为更高级别的部分。根据主题，过程可以由高级步骤或低级步骤组成。<br />
本手册提供以下内容：
<li />帮助您开展 Yocto 项目的程序；例如，向您展示如何设置构建主机和使用 Yocto 项目源存储库的过程。
<li />向您展示如何向 Yocto 项目提交更改的程序。更改可以是改进、新功能或错误修复。
<li />与您在使用 Yocto 项目开发图像和应用程序时执行的“日常”任务相关的过程，例如创建新层、自定义图像、编写新配方等。<br />
本手册不提供以下内容：<br />
<li />冗余的分步说明：例如，<u>[Yocto 项目应用程序开发和可扩展软件开发工具包 (eSDK)](https://docs.yoctoproject.org/current/sdk-manual/index.html)</u> 手册包含有关如何安装用于为目标硬件开发应用程序的 SDK 的详细说明。
<li />参考或概念材料：此类材料位于适当的参考手册中。例如，系统变量记录在 <u>[Yocto 项目参考手册](https://docs.yoctoproject.org/current/ref-manual/index.html)</u>中。
<li />不特定于 Yocto 项目的详细公共信息：例如，关于如何使用 Git 版本控制系统的详尽信息，最好通过 Internet 搜索和官方 Git 文档来覆盖，而不是通过Yocto 项目文档。
</p>

#### 1.2 其他信息
<p>由于本手册提供了许多不同主题的信息，因此建议提供补充信息以便全面理解。有关 Yocto 项目的介绍信息，请参阅 <u>[Yocto 项目网站](https://www.yoctoproject.org/)</u>。如果你想在不了解 Yocto Project 的情况下构建一个镜像来快速测试它，请参阅 <u>[Yocto Project 快速构建文档](https://docs.yoctoproject.org/current/brief-yoctoprojectqs/index.html)</u>。<br />
有关链接和其他文档的完整列表，请参阅 Yocto 项目参考手册中的“<u>[链接和相关文档](https://docs.yoctoproject.org/current/ref-manual/resources.html#links-and-related-documentation)</u>”部分。
</p>

### 2 设置使用 Yocto 项目
<p>本章提供有关如何准备使用 Yocto 项目的指导。您可以了解如何创建团队环境以使用 Yocto 项目进行开发、如何设置<u>[构建主机](https://docs.yoctoproject.org/current/dev-manual/start.html#preparing-the-build-host)</u>、如何定位 Yocto 项目源存储库以及如何创建本地 Git 存储库。
</p>

#### 2.1 创建团队开发环境
<p>您可能无法立即清楚如何在团队开发环境中使用 Yocto 项目，或者如何为大型开发团队扩展它。您可以使 Yocto 项目适应许多不同的用例和场景；但是，如果您尝试创建可有效扩展的工作设置，这种灵活性可能会导致困难。<br />
为了帮助您了解如何设置这种类型的环境，本节介绍了一个过程，该过程为您提供了可以帮助您获得所需结果的信息。该程序是高层次的，并展示了该项目的一些最成功的经验、实践、解决方案以及过去证明行之有效的可用技术；但是，请记住，这里的过程只是一个起点。您可以构建这些步骤并自定义程序以适应任何特定的工作环境和实践集。
<ol>
<li><b>确定谁将被开发：</b>您首先需要了解谁将做与 Yocto 项目相关的任何事情并确定他们的角色。做出这一决定对于完成后续步骤至关重要，这些步骤是将您的设备组装在一起并设置您的开发环境的硬件拓扑。
<ul>
<li /><b>应用程序开发人员：</b>这种类型的开发人员在现有软件堆栈之上进行应用程序级工作。
<li /><b>核心系统开发人员：</b>这种类型的开发人员致力于操作系统映像本身的内容。
<li /><b>构建工程师：</b>这种类型的开发人员管理 Autobuilders 和发布。根据环境的具体情况，并非所有情况都需要构建工程师。
<li /><b>测试工程师：</b>这种类型的开发人员创建和管理用于确保所有应用程序和核心系统开发符合所需质量标准的自动化测试。</ul>
<li><b>收集硬件：</b>根据团队的规模和组成，收集硬件。理想情况下，任何开发、构建或测试工程师都使用运行受支持的 Linux 发行版的系统。一般来说，这些系统应该是高性能的（例如，具有 24 GB RAM 和充足磁盘空间的双、六核 Xeon）。您可以通过让任何用于测试或运行 Autobuilders 的机器尽可能高性能来帮助确保效率。
<div class="admonition note">
Note
如果有足够的处理能力，您还可以考虑构建 Yocto Project 开发容器以在 Docker 下运行，这将在后面介绍。
</div>
<li /><b>了解环境的硬件拓扑：</b>一旦了解了所涉及的硬件和团队的组成，就可以了解开发环境的硬件拓扑。您可以直观地了解机器及其在整个开发环境中的角色。<br />
<li /><b>使用 Git 作为您的源代码控制管理器 (SCM)：</b>建议将您的<u>[元数据](https://docs.yoctoproject.org/current/ref-manual/terms.html#term-Metadata)</u>（即配方、配置文件、类等）和您正在开发的任何软件置于与 OpenEmbedded 构建系统兼容的 SCM 系统的控制之下.在 BitBake 支持的所有 SCM 中，Yocto 项目团队强烈建议使用 <u>[Git](https://docs.yoctoproject.org/current/overview-manual/development-environment.html#git)</u>。 Git 是一个易于备份的分布式系统，允许您远程工作，然后连接回基础架构。
<div class="admonition note">
Note
有关 BitBake 的信息，请参阅 <u>[BitBake 用户手册](https://docs.yoctoproject.org/bitbake/2.2/index.html)</u>。
</div>
设置 Git 服务和创建基础设施（如 <u>https://git.yoctoproject.org/</u>）相对容易，它基于名为 <code>gitolite</code> 的服务器软件，使用 <code>cgit</code> 生成可让您查看存储库的 Web 界面。 <code>gitolite</code> 软件使用 SSH 密钥识别用户，并允许对存储库进行基于分支的访问控制，您可以根据需要控制多少或多少。
<div class="admonition note">
Note
这些服务的设置超出了本手册的范围。但是，这里有描述如何执行设置的站点：
<ul><li /><u>[Gitolite](https://gitolite.com/)</u>：关于 gitolite 的信息。
<li /><u>[接口、前端和工具](https://git.wiki.kernel.org/index.php/Interfaces,_frontends,_and_tools)</u>：有关如何为 Git 创建接口和前端的文档。
</ul></div>
<li /><b>设置应用程序开发机器：</b>如前所述，应用程序开发人员正在现有软件堆栈之上创建应用程序。以下是设置用于应用程序开发的机器的一些最佳实践：
<ul><li />使用包含软件堆栈本身的预构建工具链。然后，在堆栈顶部开发应用程序代码。这种方法适用于少量相对孤立的应用程序。
<li />保持您的交叉开发工具链更新。您可以通过提供新工具链下载或通过使用 opkg 的包更新机制更新现有工具链来实现此目的。如何以及何时执行此操作的确切机制取决于当地政策。
<li />使用本地安装到不同位置的多个工具链以允许跨版本开发。</ul>
<li /><b>设置核心开发机器：</b>如前所述，核心开发人员致力于操作系统本身的内容。以下是设置用于开发图像的机器的一些最佳实践：
<ul><li />在开发人员工作站上提供 OpenEmbedded 构建系统，以便开发人员可以运行自己的构建并直接重建软件堆栈。
<li />尽可能保持核心系统不变，在核心系统之上分层做你的工作。在升级到新版本的核心系统或板级支持包 (BSP) 时，这样做可以为您提供更高水平的可移植性。
<li />在特定项目的开发人员之间共享层，并包含定义项目的策略配置。</ul>
<li /><b>设置自动构建器：</b>自动构建器通常是开发环境的核心。正是在这里，来自各个开发人员的更改被汇集在一起并集中测试。基于这个自动化的构建和测试环境，可以做出关于发布的后续决定。 Autobuilders 还允许对软件组件进行“持续集成”风格的测试以及回归识别和跟踪。<br />
有关更多信息和 buildbot 的链接，请参阅“<u>[Yocto Project Autobuilder](https://autobuilder.yoctoproject.org/)</u>”。 Yocto 项目团队发现此实施在此角色中运行良好。一个公开的例子是 Yocto Project Autobuilders，Yocto Project 团队使用它来测试项目的整体健康状况。<br />
该系统的特点是：<br />
<ul><li />提交中断构建时突出显示。
<li />填充 <u>[sstate 缓存](https://docs.yoctoproject.org/current/overview-manual/concepts.html#shared-state-cache)</u>，开发人员可以从中提取而不需要本地构建。
<li />允许提交钩子触发器，它在提交时触发构建。
<li />允许在 QuickEMUlator (QEMU) 下触发自动映像引导和测试。
<li />支持增量构建测试和从头开始构建。
<li />共享允许开发人员测试和历史回归调查的输出。
<li />创建可用于发布的输出。
<li />允许对构建进行调度，以便有效地使用资源。</ul>
<li /><b>设置测试机器：</b>使用少量共享的高性能系统进行测试。开发人员可以使用这些系统进行更广泛、更广泛的测试，同时继续使用他们的主要开发系统进行本地开发。<br />
<li /><b>文档政策和变更流程：</b>Yocto 项目使用层次结构和拉动模型。有一些脚本可以创建和发送拉取请求（即 <code>create-pull-request</code> 和 <code>send-pull-request</code>）。该模型与其他开源项目一致，其中维护者负责项目的特定区域，并且单个维护者处理最终的“树顶”合并。
<div class="admonition note">
Note
您还可以使用更集体的推送模型。 <code>gitolite</code> 软件很容易同时支持推拉模型。</div>
与任何开发环境一样，重要的是记录所使用的策略以及任何主要项目指南，以便每个人都理解它们。拥有结构良好的提交消息也是一个好主意，这通常是项目指南的一部分。当回顾过去并试图理解为什么进行更改时，良好的提交消息是必不可少的。<br />
如果您发现项目的核心层需要更改，值得尽快与社区分享。很有可能，如果您发现需要更改，社区中的其他人也需要更改。<br />
<li /><b>开发环境总结：</b>除了前面的步骤，以下是 Yocto Project 开发环境中的最佳实践：
<ul><li />使用 <u>[Git](https://docs.yoctoproject.org/current/overview-manual/development-environment.html#git)</u> 作为源代码控制系统。
<li />在对您的情况有意义的层中维护您的元数据。有关层的更多信息，请参阅 Yocto 项目概述和概念手册中的“<u>[Yocto 项目层模型](https://docs.yoctoproject.org/current/overview-manual/yp-intro.html#the-yocto-project-layer-model)</u>”部分和“[理解和创建层](https://docs.yoctoproject.org/current/dev-manual/common-tasks.html#understanding-and-creating-layers)”部分。
<li />使用单独的 Git 存储库分离项目的元数据和代码。有关这些存储库的信息，请参阅 Yocto 项目概述和概念手册中的“<u>[Yocto 项目源存储库](https://docs.yoctoproject.org/current/overview-manual/development-environment.html#yocto-project-source-repositories)</u>”部分。有关如何为相关上游 Yocto 项目 Git 存储库设置本地 Git 存储库的信息，请参阅“<u>[查找 Yocto 项目源文件](https://docs.yoctoproject.org/current/dev-manual/start.html#locating-yocto-project-source-files)</u>”部分。
<li />为有意义的共享状态缓存 (<u>[SSTATE_DIR](https://docs.yoctoproject.org/current/ref-manual/variables.html#term-SSTATE_DIR)</u>) 设置目录。例如，在同一组织中的开发人员使用的系统上设置 sstate 缓存，并在他们的机器上共享相同的源目录。
<li />设置一个 Autobuilder 并让它填充 sstate 缓存和源目录。
<li />Yocto Project 社区鼓励您向项目发送补丁以修复错误或添加功能。如果您确实提交了补丁，请遵循项目提交指南以编写良好的提交消息。请参阅“<u>[向 Yocto 项目提交更改](https://docs.yoctoproject.org/current/dev-manual/common-tasks.html#submitting-a-change-to-the-yocto-project)</u>”部分。
<li />尽早将更改发送到核心，因为其他人可能会遇到相同的问题。有关要使用的邮件列表的一些指导，请参阅“向 Yocto 项目提交更改”部分中的列表。有关可用<u>[邮件列表](https://docs.yoctoproject.org/current/ref-manual/resources.html#resources-mailinglist)</u>的描述，请参阅 Yocto 项目参考手册中的“邮件列表”部分。</ul>
</p>

#### 2.2 准备构建主机
<p>本节提供了设置系统以用作<u>[构建主机](https://docs.yoctoproject.org/current/ref-manual/terms.html#term-Build-Host)</u>以使用 Yocto 项目进行开发的过程。您的构建主机可以是本机 Linux 机器（推荐），也可以是使用 <u>[CROPS](https://github.com/crops/poky-container)</u>（利用 <u>[Docker 容器](https://www.docker.com/)</u>）的机器（Linux、Mac 或 Windows），也可以是能够运行版本 2 的 Windows 子系统 Linux (WSL 2)的 Windows 机器。
<div class="admonition note">
Note
Yocto 项目与适用于 Windows 子系统 Linux 的版本 1 不兼容。它与 WSL 2 兼容，但既没有官方支持也没有经过验证。如果您仍然决定使用 WSL，请升级到 WSL 2。
</div>
一旦您的构建主机设置为使用 Yocto 项目，就需要进一步的步骤，具体取决于您要完成的任务。有关如何准备板级支持包 (BSP) 开发和内核开发的信息，请参阅以下参考资料：
<ul><li /><b>BSP 开发：</b>请参阅 Yocto 项目板支持包 (BSP) 开发人员指南中的“<u>[准备构建主机以使用 BSP 层](https://docs.yoctoproject.org/current/bsp-guide/bsp.html#preparing-your-build-host-to-work-with-bsp-layers)</u>”部分。
<li /><b>内核开发：</b>请参阅 Yocto Project Linux 内核开发手册中的“<u>[准备构建主机以在内核上工作](https://docs.yoctoproject.org/current/kernel-dev/common.html#preparing-the-build-host-to-work-on-the-kernel)</u>”部分。
</ul></p>

##### 2.2.1 设置原生 Linux 主机
<p>
按照以下步骤准备本机 Linux 机器作为 Yocto 项目构建主机：
<ol>
<li /><b>使用受支持的 Linux 发行版：</b>您应该拥有一个相当流行的基于 Linux 的主机系统。使用最新版本的 Fedora、openSUSE、Debian、Ubuntu、RHEL 或 CentOS，您将获得最佳结果，因为这些版本经常针对 Yocto 项目进行测试并得到官方支持。有关正在验证的发行版及其状态的列表，请参阅 Yocto 项目参考手册中的“<u>[支持的 Linux 发行版](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#detailed-supported-distros)</u>”部分和<u>[发行版支持](https://wiki.yoctoproject.org/wiki/Distribution_Support)</u>的 wiki 页面。
<li /><b>有足够的可用内存：</b>您的系统应该至少有 50 GB 的可用磁盘空间来构建映像。
<li /><b>满足最低版本要求：</b>OpenEmbedded 构建系统应该能够在具有以下 Git、tar、Python、gcc 和 make 版本的任何现代发行版上运行。
<ul>
<li />Git 1.8.3.1 或更高版本。
<li />tar 1.28 或更高版本。
<li />Python 3.6.0 或更高版本。
<li />gcc 7.5 或更高版本。
<li />GNU make 4.0 或更高版本
</ul>
如果您的构建主机不满足任何这些列出的版本要求，您可以采取措施准备系统，以便您仍然可以使用 Yocto 项目。有关信息，请参阅 Yocto 项目参考手册中的“<u>[必需的 Git、tar、Python、make 和 gcc 版本](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#required-git-tar-python-make-and-gcc-versions)</u>”部分。
<li /><b>安装开发主机包：</b>所需的开发主机包取决于您的构建主机以及您希望对 Yocto 项目执行的操作。总的来说，如果您希望能够涵盖所有情况，则所需的软件包数量很大。

有关所有场景所需包的列表，请参阅 Yocto 项目参考手册中的“<u>[构建主机所需的包](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#required-packages-for-the-build-host)</u>”部分。
</ol>
完成前面的步骤后，您就可以在本机 Linux 机器上继续使用给定的开发路径了。如果您打算使用 BitBake，请参阅“<u>[克隆 poky 存储库](https://docs.yoctoproject.org/current/dev-manual/start.html#cloning-the-poky-repository)</u>”部分。如果您要使用可扩展 SDK，请参阅 Yocto 项目应用程序开发和可扩展软件开发工具包 (eSDK) 手册中的“<u>[使用可扩展 SDK](https://docs.yoctoproject.org/current/sdk-manual/extensible.html)</u>”一章。如果您想在内核上工作，请参阅 <u>[Yocto Project Linux 内核开发手册](https://docs.yoctoproject.org/current/kernel-dev/index.html)</u>。如果您要使用Toaster，请参阅烤面包机用户手册中的“<u>[设置和使用Toaster](https://docs.yoctoproject.org/current/toaster-manual/setup-and-use.html)</u>”部分。
</p>

##### 2.2.2 设置使用 CROss 平台 (CROPS)
<p>
借助利用 <u>[Docker 容器](https://www.docker.com/)</u>的 <u>[CROPS](https://github.com/crops/poky-container)</u>，您可以创建与操作系统无关的 Yocto 项目开发环境。您可以设置一个容器，您可以在其中使用 Yocto 项目在 Windows、Mac 或 Linux 机器上进行开发。<br />
按照以下一般步骤准备 Windows、Mac 或 Linux 机器作为 Yocto Project 构建主机：



<ol>
<li /><b>确定您的构建主机需要什么：</b>您应该拥有一个相当流行的基于 Linux 的主机系统。使用最新版本的 Fedora、openSUSE、Debian、Ubuntu、RHEL 或 CentOS，您将获得最佳结果，因为这些版本经常针对 Yocto 项目进行测试并得到官方支持。有关正在验证的发行版及其状态的列表，请参阅 Yocto 项目参考手册中的“<u>[支持的 Linux 发行版](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#detailed-supported-distros)</u>”部分和<u>[发行版支持](https://wiki.yoctoproject.org/wiki/Distribution_Support)</u>的 wiki 页面。
<li /><b>选择要安装的内容：</b>您的系统应该至少有 50 GB 的可用磁盘空间来构建映像。
<li /><b>转到您平台的安装站点：</b>OpenEmbedded 构建系统应该能够在具有以下 Git、tar、Python、gcc 和 make 版本的任何现代发行版上运行。
如果您的构建主机不满足任何这些列出的版本要求，您可以采取措施准备系统，以便您仍然可以使用 Yocto 项目。有关信息，请参阅 Yocto 项目参考手册中的“<u>[必需的 Git、tar、Python、make 和 gcc 版本](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#required-git-tar-python-make-and-gcc-versions)</u>”部分。
<li /><b>安装软件：</b>所需的开发主机包取决于您的构建主机以及您希望对 Yocto 项目执行的操作。总的来说，如果您希望能够涵盖所有情况，则所需的软件包数量很大。
<ul>
<li />为满足要求的 Windows 构建主机安装 Docker Desktop on Windows。
<li />为满足要求的 Mac 构建主机安装 Docker Desktop on Mac。
<li />在 CentOS 上为运行 CentOS 发行版的 Linux 构建主机安装 Docker 引擎。
为运行 CentOS 发行版的 CentOS 构建主机安装 <u>[Docker Engine for Fedora。
为运行 Debian 发行版的 Debian 构建主机安装 <u>[Docker Engine for Fedora。
<li />在运行 Debian 发行版的 Debian for Linux 构建主机上安装 Docker Engine。
<li />为运行 Fedora 发行版的 Linux 构建主机安装 <u>[Docker Engine for Fedora。
<li />为运行 Ubuntu 发行版的 Linux 构建主机安装 <u>[Docker Engine for Ubuntu]()</u>。
</ul>
有关所有场景所需包的列表，请参阅 Yocto 项目参考手册中的“<u>[构建主机所需的包](https://docs.yoctoproject.org/current/ref-manual/system-requirements.html#required-packages-for-the-build-host)</u>”部分。
</ol>

</p>
###3 常见任务
	本章描述了创建层、添加新软件包、扩展或自定义映像、将工作移植到新硬件（添加新机器）等基本过程。您会发现这里记录的过程经常出现在使用 Yocto 项目的开发周期中。

####3.1 理解和创建层
	OpenEmbedded 构建系统支持将元数据组织成多个层。层允许您将不同类型的自定义相互隔离。有关 Yocto 项目层模型的介绍信息，请参阅 Yocto Project Overview and Concepts Manual 中的“The Yocto Project Layer Model”部分。

#####3.1.1 创建自己的层
	Note:
	创建自己的层以与 OpenEmbedded 构建系统一起使用非常容易，因为 Yocto 项目附带了加速创建层的工具。本节介绍您手动创建图层的步骤，以便您更好地理解它们。有关层创建工具的信息，请参阅 Yocto 项目板支持包 (BSP) 开发人员指南中的“使用 bitbake-layers 脚本创建新的 BSP 层”部分和“使用 bitbake-layers 脚本创建通用层”部分”本手册后面的部分。
    按照以下一般步骤在不使用工具的情况下创建图层：
    	1.检查现有图层：在创建新图层之前，您应该确保尚未有人创建包含您需要的元数据的图层。您可以在 OpenEmbedded 元数据索引中查看来自 OpenEmbedded 社区的可用于 Yocto 项目的层列表。您可以找到与您需要的相同或接近的图层。
    	2.创建目录：为您的图层创建目录。创建图层时，请务必在与 Yocto 项目源目录无关的区域（例如克隆的 poky 存储库）中创建目录。
		虽然不是严格要求，但在目录名称前加上字符串“meta-”。例如：
            meta-mylayer
            meta-GUI_xyz
            meta-mymachine
        除了极少数例外，层的名称遵循以下形式：
        	meta-root_name
        当工具、组件或变量“假定”您的层名称以“meta-”开头时，遵循此层命名约定可以为您省去麻烦。一个值得注意的示例是在配置文件中，如以下步骤所示，其中不带“meta-”字符串的层名称被附加到配置中使用的几个变量中。
          # We have a conf and classes directory, add to BBPATH
            BBPATH .= ":${LAYERDIR}"

            # We have recipes-* directories, add to BBFILES
            BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \
                        ${LAYERDIR}/recipes-*/*/*.bbappend"

            BBFILE_COLLECTIONS += "yoctobsp"
            BBFILE_PATTERN_yoctobsp = "^${LAYERDIR}/"
            BBFILE_PRIORITY_yoctobsp = "5"
            LAYERVERSION_yoctobsp = "4"
            LAYERSERIES_COMPAT_yoctobsp = "dunfell"
        下面是层配置文件的解释：
        BBPATH：将图层的根目录添加到 BitBake 的搜索路径中。通过使用 BBPATH 变量，BitBake 定位类文件 (.bbclass)、配置文件以及包含在 include 和 require 语句中的文件。对于这些情况，BitBake 使用与 BBPATH 中找到的名称匹配的第一个文件。这类似于 PATH 变量用于二进制文件的方式。因此，建议您在自定义层中使用唯一的类和配置文件名。
        BBFILES：定义层中所有配方的位置。
        BBFILE_COLLECTIONS：通过一个唯一标识符建立当前层，该标识符在整个 OpenEmbedded 构建系统中用于引用该层。在此示例中，标识符“yoctobsp”是名为“meta-yocto-bsp”的容器层的表示。
        BBFILE_PATTERN：在解析过程中立即展开以提供层的目录。
        BBFILE_PRIORITY：当 OpenEmbedded 构建在不同层中找到同名的配方时，建立用于层中配方的优先级。
        LAYERVERSION：建立层的版本号。在使用 LAYERDEPENDS 变量时，您可以使用此版本号将图层的此确切版本指定为依赖项。
        LAYERDEPENDS：列出该层所依赖的所有层（如果有）。
        LAYERSERIES_COMPAT：列出当前版本兼容的 Yocto Project 版本。此变量是指示您的特定图层是否为当前图层的好方法。

		4.添加内容：根据图层的类型，添加内容。如果该层添加了对机器的支持，请将机器配置添加到该层内的 conf/machine/ 文件中。如果该层添加了发行版策略，请在该层内的 conf/distro/ 文件中添加发行版配置。如果该层引入了新的配方，请将您需要的配方放在该层内的 recipes-* 子目录中。
		Note:
		有关与 Yocto 项目兼容的层层次结构的说明，请参阅 Yocto 项目板支持包 (BSP) 开发人员指南中的“示例文件系统布局”部分。
        5.可选地测试兼容性：如果您希望获得将 Yocto 项目兼容性徽标与您的图层或使用您的图层的应用程序一起使用的权限，请执行以下步骤以申请兼容性。有关更多信息，请参阅“确保您的层与 Yocto 项目兼容”部分。
