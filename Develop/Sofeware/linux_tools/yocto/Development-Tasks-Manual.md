Reserve
Kirkstone(4.0.999)
<pre>
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
</pre>