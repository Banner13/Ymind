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
		struct lws_http_mount
		struct lws_context_creation_info
		struct lws_context
