

#####设置git编码
	git config --global core.quotepath false 
	git config --global gui.encoding utf-8
	git config --global i18n.commit.encoding utf-8 
	git config --global i18n.logoutputencoding utf-8 

#####设置编码
	bash 环境下
	export LESSCHARSET=utf-8

	cmd环境下：
	set LESSCHARSET=utf-8
	
#####删除新增文件
	git clean -xdf
	git clean -xdff
	
	git reset commit_id