##libwebsockets的第一个demo

	路径：
		libwebsockets/minimal-examples-lowlevel/http-server/minimal-http-server

	内容：
		.
		├── CMakeLists.txt						// cmake 文件
		├── minimal-http-server.c				// main 函数
		├── mount-origin						// 存放页面内容
		│   ├── 404.html						// 错误提示页面
		│   ├── favicon.ico						// 浏览器页面图标
		│   ├── index.html						// 页面主页
		│   ├── libwebsockets.org-logo.svg		// 页面图标 1
		│   └── strict-csp.svg					// 页面图标 2
		└── README.md

		1 directory, 8 files

	说明：最简单的demo了，主要涉及到以下结构体
[struct lws_http_mount](../../../../struct/lws_http_mount.md)

	static const struct lws_http_mount mount = {
		.mountpoint			= "/",		    /* mountpoint URL */
		.origin			= "./mount-origin", /* serve from dir */
		.def				= "index.html",	  /* default filename */
		.origin_protocol		= LWSMPRO_FILE,	    /* files in a dir */
		.mountpoint_len			= 1,		        /* char count */
	};
	将 origin 的路径作为 mountpoint 使用，即 ./mount-origin 作为 http 网页的 '/' 根目录。
	选择了文件协议，并定义默认主页为 index.html。


[struct lws_context_creation_info](../../../../struct/lws_context_creation_info.md)
[struct lws_context]()

		struct lws_context_creation_info info;
		struct lws_context *context;

		info.port = 7681;
		info.mounts = &mount;
		info.error_document_404 = "404.html";
		info.options =
			LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

		if (lws_cmdline_option(argc, argv, "--h2-prior-knowledge"))
			info.options |= LWS_SERVER_OPTION_H2_PRIOR_KNOWLEDGE;

		context = lws_create_context(&info);
		利用 info 生成了 context, 类似于句柄。

		while (n >= 0 && !interrupted)
			n = lws_service(context, 0);
		会处理挂起的websocket包

