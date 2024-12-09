``` shell
# 创建用户和密码
@ useradd jackzhou -m
@ passwd jackzhou

# 从磁盘创建分区并进行挂载
@ fdisk /dev/sdb
@ mkfs.ext4 /dev/sdb5
@ mount /dev/sdb5 /home/jackzhou

# 修改用户文件夹权限
@ chown jackzhou:jackzhou /home/jackzhou

# 修改用户默认终端
@ chsh -s /bin/bash jackzhou

# 开机自动挂载用户分区
@ echo '/dev/sdb5    /home/jackzhou   ext4    defaults    0    2' >> /etc/fstab

```

``` shell
#!/bin/bash

# 检查是否为root用户
if [ "$(id -u)" -ne 0 ]; then
    echo "请以root用户运行该脚本"
    exit 1
fi

# 检查是否传入用户名
if [ -z "$1" ]; then
    echo "用法: $0 <用户名>"
    exit 1
fi

DISK="/dev/sdb"

get_input_form_user() {
    local input="$1"

    read userinput
    if [ ! -z "$userinput" ]; then
        input = userinput
    fi

    echo "$input"
}

# 自动创建分区的函数
auto_create_partition() {
    local DISK="$1"

    # 检查磁盘设备是否存在
    if [ ! -b "$DISK" ]; then
        echo "磁盘设备 $DISK 不存在，请检查设备名称。"
        exit 1
    fi

    # 使用 fdisk 创建新分区并获取分区号
    PARTITION_NUMBER=$( (
        echo n      # 添加新分区
        # echo e      # 扩展分区（如果所有主分区已用完）
        # echo        # 由 fdisk 自动分配分区编号
        echo        # 默认起始扇区
        echo +64G   # 默认结束扇区（使用 64G 大小）
        echo w      # 写入分区表并退出
    ) | fdisk "$DISK" 2>&1 | awk '/Adding logical partition/ {print $4}')

    local CMD="mkfs.ext4 ${DISK}${PARTITION_NUMBER} > /dev/null "

    echo -n "是否执行$CMD(Y)" >&2
    local pass="Y"
    input=$(get_input_form_user "$pass")
    if [ "$input" != "$pass" ]; then
        exit 1
    fi

    eval $CMD
    if [ $? -ne 0 ]; then
        echo "执行命令失败：$CMD"
        exit 1
    fi

    # 返回分区号
    echo "$PARTITION_NUMBER"
}

PARTITION_NUMBER=$(auto_create_partition "$DISK")
if [ -z "$PARTITION_NUMBER" ]; then
    echo "分区创建失败"
    exit 1
fi
echo -e "函数返回的分区号是：$PARTITION_NUMBER\n"

USERNAME=$1
DEFAULT_PASSWORD="123456"
# 创建用户并设置默认密码
CMD="useradd ${USERNAME} -m > /dev/null "

echo -n "是否执行$CMD(Y)"
pass="Y"
input=$(get_input_form_user "$pass")
if [ "$input" != "$pass" ]; then
    exit 1
fi
eval $CMD
if [ $? -ne 0 ]; then
    echo "执行命令失败：$CMD"
    exit 1
fi
echo -e "用户创建成功:$CMD\n"

CMD="echo ${USERNAME}:${DEFAULT_PASSWORD} | chpasswd > /dev/null "

echo -n "是否执行$CMD"
pass="Y"
input=$(get_input_form_user "$pass")
if [ "$input" != "$pass" ]; then
    exit 1
fi
eval $CMD
if [ $? -ne 0 ]; then
    echo "执行命令失败：$CMD"
    exit 1
fi
echo -e "密码创建成功:$CMD\n"

CMD="mount ${DISK}${PARTITION_NUMBER} /home/${USERNAME} 2>&1"
echo -n "是否执行$CMD"
pass="Y"
input=$(get_input_form_user "$pass")
if [ "$input" != "$pass" ]; then
    exit 1
fi
eval $CMD
if [ $? -ne 0 ]; then
    echo "执行命令失败：$CMD"
    exit 1
fi
echo -e "分区挂载成功:$CMD\n"

CMD="chown ${USERNAME}:${USERNAME} /home/${USERNAME}"
echo -n "是否执行$CMD"
pass="Y"
input=$(get_input_form_user "$pass")
if [ "$input" != "$pass" ]; then
    exit 1
fi
eval $CMD
if [ $? -ne 0 ]; then
    echo "执行命令失败：$CMD"
    exit 1
fi
echo -e "权限修改成功:$CMD\n"

CMD="chsh -s /bin/bash ${USERNAME}"
echo -n "是否执行$CMD"
pass="Y"
input=$(get_input_form_user "$pass")
if [ "$input" != "$pass" ]; then
    exit 1
fi
eval $CMD
if [ $? -ne 0 ]; then
    echo "执行命令失败：$CMD"
    exit 1
fi
echo -e "shell修改成功:$CMD\n"

echo "${DISK}${PARTITION_NUMBER}    /home/${USERNAME}   ext4    defaults    0    2" >> /etc/fstab
if [ $? -ne 0 ]; then
    echo "执行命令失败:sssss"
    exit 1
fi
echo -e "开机挂载已写入:$CMD\n"

CMD="ln -s /home/zwo/readme.txt /home/${USERNAME}/readme.txt"
eval $CMD
```
