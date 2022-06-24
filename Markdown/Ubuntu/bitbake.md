###BitBake User Manual
	Metadata is stored in
		recipe (.bb)　　　　基本食谱
		related recipe “append” (.bbappend)    keep things modular
		configuration (.conf)    构建过程中的配置变量
		underlying include (.inc)
		in class (.bbclass) 定义基本的标准任务
			例如  fetching, unpacking, configuring (empty by default),
				  compiling (runs any Makefile present), installing (empty by default) and packaging (empty by default)
				  
###基本命令
	bitbake -g foo
	bitbake -c clean foo
	bitbake firstfoo:do_taskA secondfoo:do_taskB
	bitbake -g -u taskexp task　　生成bitbake task依赖图    taskexp or depexp
	bitbake -g -I virtual/kernel -I eglibc foo  省略常见依赖项