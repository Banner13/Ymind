

###poky用于构建你自己的发行版本，包含了 bitbake和一组 meta(元数据)
		Poky is a reference distribution of the Yocto Project®. It contains the OpenEmbedded Build System (BitBake and OpenEmbedded Core) as well as a set of metadata to get you started building your own distro. To use the Yocto Project tools, you can download Poky and use it to bootstrap your own distribution. Note that Poky does not contain binary files – it is a working example of how to build your own custom Linux distribution from source.
		
###build step
	1. The first stages of building a recipe are to fetch and unpack the source code
		获取源代码
	
	2. Once source code is fetched and unpacked, BitBake locates patch files and applies them to the source files
		打patch
		variable
			SRC_URI
			FILESPATH
			
	3. After source code is patched, BitBake executes tasks that configure and compile the source code.
		Once compilation occurs, the files are copied to a holding area (staged) in preparation for packaging
		执行配置、编译、存放编译完成的文件
		
		3.1 do_prepare_recipe_sysroot (optional)
			构建了两个sysroot目录，确保在打包过程中包含了任务配方中所依赖的内容。
		3.2 do_configure
			This task configures the source by enabling and disabling any build-time and configuration options for the software being built.
			解析配置文件
		3.3 do_compile
			Once a configuration task has been satisfied, BitBake compiles the source using the do_compile task.
			进行编译
		3.4 do_install
			After compilation completes, BitBake executes the do_install task.
			编译完成后，将文件放入指定目录
			
	4. After source code is configured, compiled, and staged, the build system analyzes the results and splits the output into packages
	
	5. Once packages are split and stored in the Package Feeds area, the build system uses BitBake to generate the root filesystem image.

	6. The OpenEmbedded build system uses BitBake to generate the Software Development Kit (SDK) installer scripts for both the standard SDK and the extensible SDK (eSDK):