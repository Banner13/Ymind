
### 多线程调试

引用：
https://www.cnblogs.com/xuxm2007/archive/2011/04/01/2002162.html
https://www.cnblogs.com/WindSun/p/12785322.html


**info threads** 显示当前可调试的所有线程，每个线程会有一个GDB为其分配的ID，后面操作线程的时候会用到这个ID。 前面有*的是当前调试的线程。

**thread ID** 切换当前调试的线程为指定ID的线程。

**break thread_test.c:123 thread all** 在所有线程中相应的行上设置断点

**thread apply ID1 ID2 command** 让一个或者多个线程执行GDB命令command。 

**thread apply all command** 让所有被调试线程执行GDB命令command。

**set scheduler-locking off|on|step** 估计是实际使用过多线程调试的人都可以发现，在使用step或者continue命令调试当前被调试线程的时候，其他线程也是同时执行的，怎么只让被调试程序执行呢？通过这个命令就可以实现这个需求。off 不锁定任何线程，也就是所有线程都执行，这是默认值。 on 只有当前被调试程序会执行。 step 在单步的时候，除了next过一个函数的情况(熟悉情况的人可能知道，这其实是一个设置断点然后continue的行为)以外，只有当前线程会执行。

### 多线程调试控制指令

`thread apply ID1 ID2 ...IDn gdb_command` 指定多个线程执行gdb中的command指令

`thread apply all command` 指定所有线程执行gdb中的command指令

### non-stop模式

上面说过一个线程中断在一个断点上，其他所有的线程都会被freeze。新版本的GDB中，引入了non-stop模式，在这个模式下：

1. 当某个或多个线程在一个断点上，其他线程仍会并行运行
    
2. 你可以选择某个被中断的线程，只让他运行。
    
3. non-stop模式表示不停止模式，除了断点有关的进程会被停下来，其他线程会继续执行。
    

设置non-stop模式，打开gdb后，在开始r之前，首先连续输入下面的指令

hljs

```vbnet
set target-async 1
set pagination off
set non-stop on
```

## 总结调试多线程的命令

`info threads` 显示当前可调试的所有线程，每个线程会有一个GDB为其分配的ID，后面操作线程的时候会用到这个ID。 前面有*的是当前调试的线程

`thread ID(1,2,3…)` 切换当前调试的线程为指定ID的线程

`break thread_test.c:123 thread all`（例：在相应函数的位置设置断点break pthread_run1） 在所有线程中相应的行上设置断点

`thread apply ID1 ID2 command` 让一个或者多个线程执行GDB命令command

`thread apply all command` 让所有被调试线程执行GDB命令command

`set scheduler-locking` 选项 command 设置线程是以什么方式来执行命令

`set scheduler-locking off` 不锁定任何线程，也就是所有线程都执行，这是默认值

`set scheduler-locking on` 只有当前被调试程序会执行

`set scheduler-locking on step` 在单步的时候，除了next过一个函数的情况(熟悉情况的人可能知道，这其实是一个设置断点然后continue的行为)以外，只有当前线程会执行