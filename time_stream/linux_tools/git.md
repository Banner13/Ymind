

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

#####子模块
	git submodule init
	git submodule update
	git submodule add <url> <path>

#####删除远程branch
	git push origin --delete oring_brance
#####题外话
	git运行的大致原理
	每个文件生成一个哈希值
	所有文件的哈希值生成了一个tree哈希值
	变更时，会改变tree哈希和变更文件的哈希值
	所以，当你把一个文件从一个目录移到另一个目录时，该文件的哈希值不会变化


#####git stash pop 冲突恢复
	git reset --hard

#####git stash -p 交互

##### 希望别再用到
	git rebase --onto branch commit1 commit2

##### 删除.ssh下的 know_host 后，以前的ssh访问会出现错误，请重新建立连接