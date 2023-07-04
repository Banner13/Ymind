

## 进程
	程序 ---> 任务 ---> 进程
	代码 ---> 列表 ---> 活动中

### 进程的创建、终止
#### 系统调用 fork、execve、kill
	父进程fork、execve
	自愿退出：正常退出、出错退出
	非自愿退出：严重错误、被杀死(kill)

### 进程的状态
#### 系统调用 block、pause
	程序运行过程中的瞬时状态：Running、Ready、Blocked

## 进程调度器
### 进程表

<table> <tr> <td>内核:
寄存器
程序计数器
程序状态字
栈指针
进程状态
当前调度优先权
最大调度优先权
Scheduling ticks left
配额大小
使用的CPU时间
消息队列指针
挂起的信号位
各种标志位
进程名字</td> <td>进程管理:
正文段指针
数据段指针
bss段指针
退出状态
信号状态
进程标识号
父进程
进程组
子进程的CPU时间
真实UID
有效UID
真实GID
有效GID
代码段共享所需文件信息
信号位图
各种标志位
进程名字</td> <td>文件管理:
UMASK掩码
根目录
工作目录
文件描述符
真实UID
有效UID
真实GID
有效GID
控制tty
用于read/write的保护区
系统调用参数
各种标志位</td> </tr> </table>

### 线程

### 进程间通信
#### 信息传递
	send、receive
#### 临界区问题
	理想形式
               A进入临界区                    A离开临界区
	_______________|================|==========|_________________   进程A
				   |                |          |           |
				   |                |          |           |
				   |                |          |           |
	_______________|________________|..........|===========|______  进程B
	                          B试图进入  阻塞  B进入       B离开
##### 解决方法
###### 关闭中断
	1. 不适用于用户程序
	2. 不适用于多核CPU

##### 互斥锁lock、unlock
	pthread_mutex_init
	pthread_mutex_lock
	pthread_mutex_unlock
	pthread_mutex_destroy
	pthread_mutex_trylock
##### sleep和wakeup
##### 信号量up、down
	sem_init
	sem_post
	sem_wait
	sem_destroy
##### 条件变量wait、signal

#### 顺序问题
#### 经典IPC问题
	哲学家进餐
	读者 - 写者问题

### 进程调度
	时间片轮转调度
	优先级调度(动态/静态)
	保证调度算法
	彩票调度算法
	公平分享调度

	优先级+多级队列+评分系统(占用时间、有效使用率、等待时间)紧急、重要

	注重用户体验：终端 >

### 线程调度
	用户调度
	系统调度 == 进程调度

### 实时调度系统
#### 系统调用nice

### MINIX3 进程的实现

