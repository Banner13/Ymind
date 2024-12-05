[TOC]


## start
	#!/bin/bash

    $#	参数个数
    $@	将输入参数视为整体
    $*	将输入参数独立成每一个

``` shell
while true; do 
	# 在这里放置你要循环执行的命令 
	echo "正在循环执行命令..." 
	sleep 1 # 暂停 1 秒，避免命令执行过快 
done
```

``` shell
for i in {1..10}; do 
	echo "第 $i 次执行命令" 
	sleep 1 
done
```
## 内置命令
### help shell的新手村指南
	不明白的就找它(仅作用于shell内部命令，即‘shell builtin’)

### type 查看命令类型
	命令类型有 `alias', `keyword', `function', `builtin', `file' or ''
