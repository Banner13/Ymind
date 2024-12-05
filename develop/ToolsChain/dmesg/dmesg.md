在应用层，可以通过`syslog`函数或使用`/dev/kmsg`文件来将消息打印到内核日志中，这样消息就会出现在`dmesg`中。以下是两种方法：

### 方法 1: 使用 `syslog` 函数

你可以使用 C 语言的 `syslog` 函数来将消息写入内核日志。

c

复制代码

`#include <syslog.h> #include <stdio.h>  int main() {     // 打开与 syslog 的连接     openlog("myapp", LOG_CONS | LOG_PID, LOG_USER);      // 打印消息到内核日志中     syslog(LOG_INFO, "This is a test message from user space.");      // 关闭与 syslog 的连接     closelog();      return 0; }`

编译并运行此程序后，消息会出现在 `dmesg` 的输出中。

### 方法 2: 使用 `/dev/kmsg` 文件

你也可以直接向 `/dev/kmsg` 写入，这也是一种将消息发送到内核日志的方式。

c

复制代码

`#include <stdio.h> #include <fcntl.h> #include <unistd.h>  int main() {     int fd = open("/dev/kmsg", O_WRONLY);     if (fd < 0) {         perror("open");         return 1;     }      const char *message = "This is a test message from user space.\n";     write(fd, message, strlen(message));      close(fd);     return 0; }`

这段代码直接向 `/dev/kmsg` 写入日志。编译并运行该程序后，你也可以在 `dmesg` 中看到消息。

**注意**: 直接向 `/dev/kmsg` 写入消息可能需要管理员权限，因此在执行时可能需要使用 `sudo`。

4o

##### 您说：

第一个没打印 第二个能打印

###### ChatGPT 说：

ChatGPT

第一个方法使用 `syslog` 函数时，消息默认会被发送到系统日志而非内核日志，因此不会出现在 `dmesg` 中。它的日志会被发送到 `/var/log/messages` 或 `/var/log/syslog` 之类的文件中，而不是内核日志。

如果你希望在应用层将日志直接发送到 `dmesg`，使用第二种方法是更直接有效的选择。`/dev/kmsg` 是一个直接接口，它将消息写入内核消息缓冲区，所以更适合你想要的效果。

需要注意的是，直接写入 `/dev/kmsg` 时，通常需要以 `root` 权限运行，因为该设备文件默认只允许管理员写入。