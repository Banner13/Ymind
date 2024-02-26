```powershell
> wsl --help
版权所有 (c) Microsoft Corporation。保留所有权利。
有关此产品的隐私信息，请访问 https://aka.ms/privacy。

用法: wsl.exe [Argument] [Options...] [CommandLine]

运行 Linux 二进制文件的参数:

    如果未提供命令行，wsl.exe 将启动默认 shell。

    --exec, -e <CommandLine>
        不使用默认 Linux shell 执行指定的命令。

    --shell-type <Type>
        使用提供的 shell 类型执行指定的命令。

        类型:
            standard
                使用默认 Linux shell 执行指定的命令。

            login
                使用默认 Linux shell 作为登录 shell 执行指定的命令。

            none
                不使用默认 Linux shell 执行指定的命令。

    --
        按原样传递命令行的剩余部分。

选项:
    --cd <Directory>
        将指定的目录设置为当前工作目录。
        如果使用 ~，则将使用 Linux 用户的主路径。如果路径以
        / 字符开头，它将解释为绝对 Linux 路径。
        否则，该值必须为绝对 Windows 路径。

    --distribution, -d <Distro>
        运行指定的分发。

    --user, -u <UserName>
        以指定的用户身份运行。

    --system
        为系统分发启动 shell。

用于管理适用于 Linux 的 Windows 子系统的参数:

    --help
        显示用法信息。

    --debug-shell
        打开 WSL2 调试 shell 以进行诊断。

    --event-viewer
        打开 Windows 事件查看器的应用视图。

    --install [Distro] [Options...]
        安装适用于 Linux 的 Windows 子系统分发。
        若要查看可用的分发列表，请使用 'wsl.exe --list --online'。

        选项:
            --no-launch, -n
                安装后不要启动分发。

            --web-download
                从 Internet 而不是 Microsoft Store 下载分发。

    --mount <Disk>
        在所有 WSL 2 分发中附加并装载物理或虚拟磁盘。

        选项:
            --vhd
                指定 <Disk> 代表虚拟硬盘。

            --bare
                将磁盘附加到 WSL2 但不装载。

            --name <Name>
                为装入点使用自定义名称装载磁盘。

            --type <Type>
                装载磁盘时使用的文件系统，如果未指定则默认为 ext4。

            --options <Options>
                其他装载选项。

            --partition <Index>
                要装载的分区索引，如果未指定则默认为整个磁盘。

    --release-notes
        打开 Web 浏览器查看 WSL 发行说明页面。

    --set-default-version <Version>
        更改新分发的默认安装版本。

    --shutdown
        立即终止所有正在运行的分发和 WSL 2
        轻型虚拟机。

    --status
        显示适用于 Linux 的 Windows 子系统的状态。

    --unmount [Disk]
        从所有 WSL2 分发中卸载并分离一个磁盘。
        如果未使用参数调用，则卸载并分离所有磁盘。

    --update
        更新适用于 Linux 的 Windows 子系统程序包。

        选项:
            --web-download
                从 Internet 而不是 Microsoft Store 下载更新。

            --pre-release
                如果可用，则下载预发布版本。表示使用 --web-download.

    --version, -v
        显示版本信息。

用于管理适用于 Linux 的 Windows 子系统中的分发的参数:

    --export <Distro> <FileName> [Options]
        将分发导出为 tar 文件。
        对于标准输出，文件名可以是“-”。

        选项:
            --vhd
                指定要导出为 .vhdx 文件的分发。

    --import <Distro> <InstallLocation> <FileName> [Options]
        将指定的 tar 导入为新分发。
        对于标准输入，文件名可以是“-”。

        选项:
            --version <Version>
                指定要为新分发使用的版本。

            --vhd
                指定提供的文件为 .vhdx 文件，而不是 tar 文件。
                此操作将在指定的安装位置生成一个 .vhdx 文件的副本。

    --import-in-place <Distro> <FileName>
        将指定的 .vhdx 导入为一个新分发。
        此虚拟硬盘必须使用 ext4 文件系统类型格式化。

    --list, -l [Options]
        列出分发。

        选项:
            --all
                列出所有分发，包括
                目前正在被安装或被卸载的分发。

            --running
                仅列出目前正在运行的分发。

            --quiet, -q
                仅显示分发名称。

            --verbose, -v
                显示所有分发的相关详细信息。

            --online, -o
                使用 'wsl.exe --install' 显示可以安装的可用分发列表。

    --set-default, -s <Distro>
        将分发设置为默认分发。

    --set-version <Distro> <Version>
        更改指定分发的版本。

    --terminate, -t <Distro>
        终止指定分发。

    --unregister <Distro>
        注销分发并删除根文件系统。
```


### WSL重启
```power shell
> wsl --shutdown <Distro>
```
