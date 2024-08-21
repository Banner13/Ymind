
	参考资料
		《鸟哥私房菜》

	命令别名 alias (shell)
		$ alias ll='ls -l'
	取消别名 unalias

	查询指令类型 type (shell)

	命令换行输入 \+Enter
		\ 和 Enter 之间无空格

	变量设置
		PATH=$pwd:$PATH
		使用变量是，需加前缀 $ ,命名时不需要；

		var="lang is $LANG"		双引号可使用变量		lang is zh_TW.UTF-8
		var=‘lang is $LANG’		单引号表纯文字			lang is $LANG
		跳脱字符“ \ ”将特殊符号（如 [Enter], $, \, 空白字符, '等）变成一般字符

		指令需要加参数 version=$（uname -r） 或使用反单引号 `` 不是 ''

		扩展变量  PATH=$PATH(附加内容) 或者 PATH=(附加内容)$PATH
				例如 PATH=$PATH:/usr/bin 即为 $PATH + ':/usr/bin'

		通常大写字符为系统默认变量，自行设置变量可以使用小写字符，方便判断
		取消变量的方法为使用 unset ：“unset 变量名称”
		
		用 set 观察所有变量 （含环境变量与自订变量）
		$?	上条指令执行情况
		$$	该线程 PID
		
		变量内容的删除、取代与替换 （Optional）
		${variable#/*local/bin:}
		#	正向最短匹配删除
		##	正向最长匹配删除
		%	反向最短匹配删除
		%%	反向最长匹配删除
		/	替换第一个			${path/sbin/SBIN}
		//	替换所有			${path/sbin//SBIN}
		
		${username-root}		如果存在则不变，不存在则 username = root
		${username:-root}		强制 username = root
		16bit 随机值 $RANDOM

	为变量增加特殊属性	declare
	
	查看命令使用历史 history
	! number
	!command
	!!

	快捷键		  [ctrl]+u	从光标处向前删除指令串
				[ctrl]+k  从光标处向后删除指令串
				[ctrl]+a  光标移动到指令串前
				[ctrl]+e  光标移动到指令串后
	
	列出所有的相关文件文件名 locate xxx
	
	显示当前环境变量	env
	
	
	>	创建或覆盖
	>>	创建或追加
	1>> stdout标准输出


	/dev/null	垃圾桶黑洞
	指令执行顺序
	1. 以相对/绝对路径执行指令，例如“ /bin/ls ”或“ ./ls ”；
	2. 由 alias 找到该指令来执行；
	3. 由 bash 内置的 （builtin） 指令来执行；
	4. 通过 $PATH 这个变量的顺序搜寻到的第一个指令来执行。



	cut
	awk
	grep
	
	sort, wc, uniq, tee
	tr, col, join, paste, expand
	
	split xargs

#### 追踪脚本执行过程
``` bash
#!/bin/bash -v or -x
```
