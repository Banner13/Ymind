[libwebsockets Host page](https://libwebsockets.org/)

		起因：我需要一个能够传输图片的协议，但是又不想自己利用TCP或者UDP加上一些自定义协议，所以找上了libwebsockets。
		选择原因：基于C语言开发。

		开发环境：建议使用 Ubuntu20以上，如果使用Ubuntu16，还需要自行编译openssl(虽然也不是很麻烦，但是我不太想去做这种事情)。

		开发步骤:
			1.  git clone https://libwebsockets.org/repo/libwebsockets
			2.  cd libwebsockets
			3.  mkdir build && cd build
			4.  cmake ..				如果使用ubuntu16，在此处会提示需要openssl相关文件
				显示以下内容即为cmake配置成功
				-- Configuring done
				-- Generating done
				-- Build files have been written to: xxx/xxx/...
			5.  make
			6.  export PATH=xxx/libwebsockets/build/bin:$PATH	方便后续使用
			7.  cd ibwebsockets/minimal-examples-lowlevel/http-server/minimal-http-server			进入想要演示的demo文件夹
			8.  lws-minimal-http-server		启动demo
				显示一下内容即成功
				U: LWS minimal http server | visit http://localhost:7681
			9. 打开浏览器  输入 http://localhost:7681 即可查看内容
				localhost 为开启lws-minimal-http-server 的主机ID


	demo文件夹中存放笔者对 libwebsockets 中的理解，如若有误，还请见谅。
