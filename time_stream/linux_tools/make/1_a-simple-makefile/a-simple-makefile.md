

##Make
___
####基本规则
	目标文件(输出文件) ： 生成目标文件所需要的文件(输入文件)
		执行动作
		
	eg.1
	main.o : main.c
		gcc main.c -o main.o		// 注： "执行动作" 前请使用 Tab 而不是空格，若需要其他符号，使用.RECIPEPREFIX修改
		
####A Simple Makefile
	edit : main.o kbd.o command.o display.o insert.o search.o files.o utils.o
			cc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o
	// cc 在Make中相当于 gcc的别名，可以修改
	main.o : main.c defs.h
			cc -c main.c
	kbd.o : kbd.c defs.h command.h
			cc -c kbd.c
	command.o : command.c defs.h command.h
			cc -c command.c
	display.o : display.c defs.h buffer.h
			cc -c display.c
	insert.o : insert.c defs.h buffer.h
			cc -c insert.c
	search.o : search.c defs.h buffer.h
			cc -c search.c
	files.o : files.c defs.h buffer.h command.h
			cc -c files.c
	utils.o : utils.c defs.h
			cc -c utils.c
	clean :
			rm edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o
			
	// 在上述demo中，所有C文件都依赖了 defs.h ,其余 .h文件是根据依赖所添加的 
	// 如果一行的内容过长  可以使用 \ 进行换行
	// eg.2 cc -o edit main.o kbd.o command.o display.o insert.o search.o files.o utils.o
	// 与   cc -o edit main.o kbd.o command.o display.o \
	//			insert.o search.o files.o utils.o   // 等效
	// 完成Makefile后，在Makefile所在的目录下，使用 make 即可生成 edit 的目标文件
	// 注： 请注意依赖文件与Makefile的相对路径
![avatar](a-simple-makefile.gif)

###make运行规则原文
	Before recompiling an object file, make considers updating its prerequisites, the source file and header files. This makefile does not specify anything to be done for them—the ‘.c’ and ‘.h’ files are not the targets of any rules—so make does nothing for these files. But make would update automatically generated C programs, such as those made by Bison or Yacc, by their own rules at this time.

	After recompiling whichever object files need it, make decides whether to relink edit. This must be done if the file edit does not exist, or if any of the object files are newer than it. If an object file was just recompiled, it is now newer than edit, so edit is relinked.
	// 注： 先检查处理依赖文件，然后检查目标文件，最后根据执行命令生成目标文件。
___
###题外话
	make判断源文件是否发生改变的依据是该文件的时间戳(明显这依赖于操作系统)。