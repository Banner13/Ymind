[TOC]

##Part 1: Getting started with Python for science
	Scipy讲义的这一部分是一个独立的介绍，介绍了在科学中使用Python所需要的一切，从语言本身，到数值计算或绘图。

###第一章：Python科学计算生态系统
	作者：Fernando Perez, Emmanuelle Gouillart, Gaël Varoquaux, Valentin Haenel

####1.1 为什么选择 Python ?
#####1.1.1 科学家的需求
- 获取数据(仿真、实验控制)，
- 操作和处理数据，
- 可视化结果，快速理解，但也有准确的的数字，为了报告或出版物。

#####1.1.2 Python的优势
- 电池包括丰富的现有砖块的经典数值方法，绘图或数据处理工具。我们不想重新编程绘制曲线，傅里叶变换或拟合算法。别白费力气了!
- 大多数科学家不是以程序员的身份获得报酬的，他们也没有接受过程序员的培训。他们需要能够画出一条曲线，使信号平滑，在几分钟内完成傅里叶变换。
- 为了让代码在实验室或公司中保持活力，它应该像一本书一样易于合作者、学生或客户阅读。Python语法很简单，避免了奇怪的符号或冗长的例程规范，以免读者从数学或科学的角度理解代码。、
- Python数值模块的计算效率很高。但不用说，如果花费太多的时间来编写非常快的代码，它就会变得毫无用处。Python的目标是快速开发时间和快速执行时间。
- 通用Python是一种用于解决许多不同问题的语言。学习Python可以避免为每个新问题学习一款新软件。

#####1.1.3 Python与其他解决方案相比如何?
	编译语言:C, c++， Fortran…
		优点：
			- 非常快。对于繁重的计算，很难超越这些语言。
		缺点：
			- 痛苦的用法:开发期间没有交互，强制编译步骤，冗长的语法，手动的内存管理。这些语言对于非程序员来说是困难的。

	Matlab脚本语言
		优点：
			- 非常丰富的库集合与众多算法，为许多不同的领域。快速执行，因为这些库通常是用编译语言编写的。
			- 良好的开发环境:全面帮助、集成编辑等。
			- 可以获得商业支持。
		缺点：
			- 基本语言非常差，对于高级用户来说可能会变得很有限制。
			- 不是免费的。

	Julia
		优点：
			• 快速的代码，但交互式和简单。
			• 轻松连接Python或C语言。
		缺点：
			• 生态系统仅限于数值计算。
			• 还年轻。

	Other scripting languages: Scilab, Octave, R, IDL, etc.
		优点：
			• 开源，免费，或者至少比Matlab便宜。
			• 一些功能可以非常高级(R中的统计数据等)
		缺点：
			• 可用的算法比Matlab更少，语言也没有更高级。
			• 一些软件专用于一个域。例如:Gnuplot绘制曲线。这些程序非常强大，但是它们仅限于一种使用类型，例如绘图。

	Python
		优点：
			• 非常丰富的科学计算库
			• 经过深思熟虑的语言，允许编写可读性强、结构良好的代码:我们“代码即所想”。
			• 许多超越科学计算的库(web服务器、串口访问等)(网络服务器，串口访问等)
			• 免费开源软件，广泛传播，拥有一个充满活力的社区。
			• 各种强大的工作环境，如IPython, Spyder, Jupyter笔记本，Pycharm, Visual Studio Code
		缺点：
			• 并非所有的算法都能在更专业的软件或工具箱中找到。

####1.2 科学Python生态系统
	与Matlab或R不同，Python没有为科学计算提供一组预先绑定的模块。
	以下是可以组合起来获得科学计算环境的基本构件:

	Python，一种通用的现代计算语言
		• 语言:流控制、数据类型(字符串、int)、数据集合(列表、字典)等。
		• 标准库模块:字符串处理，文件管理，简单网络协议。
		• 大量用Python编写的专门模块或应用程序:web框架等. . . .和科学计算。
		• 开发工具(自动测试，文档生成)
	参考：
	chapter on Python language

	主要数学库
		• Numpy:具有强大的数值数组对象和操作它们的例程的数值计算。http://www.numpy.org/
		参考：
			chapter on numpy
		• Scipy:高级数值例程。优化，回归，插值等http://www.scipy.org/
		参考：
			chapter on scipy
		• Matplotlib:二维可视化，“出版就绪”绘图http://matplotlib.org/
		参考：
			chapter on matplotlib

	先进的交互式环境:
		• IPython，一个高级的Python控制台http://ipython.org/
		• Jupyter，notebooks在浏览器http://jupyter.org/

	领域特定的包,
		三维可视化 Mayavi
		统计数据 pandas, statsmodels, seaborn
		符号计算 sympy
		图像处理 scikit-image
		机器学习 scikit-image
	还有更多scipy讲义中没有记录的软件包。
	参考：
		chapters on advanced topics
		chapters on packages and applications

####1.3 开始前:安装工作环境
	Python有很多版本，安装它的方法也很多。但是，我们建议安装科学计算分布，它很容易与科学模块的优化版本一起提供。

		警告:您应该安装Python 3
		Python 2.7已经结束使用寿命，并且在2020年1月1日之后将不再进行维护。
		使用Python 2.7的风险由您自己承担。不要期待太多的支持。
			• Official announcement
			• The end is nigh

	在Linux下
		如果您使用的是最新的发行版，那么大多数工具可能都是打包的，建议使用您的包管理器。
	其他系统
		有几个功能齐全的Scientific Python发行版:
			• Anaconda
			• EPD
			• WinPython

####1.4 工作流程:交互环境和文本编辑器
	测试和理解算法的交互式工作:在本节中，我们将描述一个结合了交互式工作和合并的工作流。
	Python是一种通用语言。因此，工作的环境不是唯一的，使用环境的方式也不是唯一的。虽然这使得初学者很难找到他们的方法，但它使Python被用于程序、web服务器或嵌入式设备成为可能。

#####1.4.1 互动工作
	我们推荐使用IPython控制台或其后代Jupyter notebook的交互式作品。
	它们对于探索和理解算法很方便。

	在 notebook 中
	要执行代码，请按“shift enter”

	Start ipython:
		In [1]: print('Hello world')
		Hello world

	通过使用?对象后的运算符:
		In [2]: print?
		Type: builtin_function_or_method
		Base Class: <type 'builtin_function_or_method'>
		String Form: <built-in function print>
		Namespace: Python builtin
		Docstring:
			print(value, ..., sep=' ', end='\n', file=sys.stdout)
			Prints the values to a stream, or to sys.stdout by default.
			Optional keyword arguments:
			file: a file-like object (stream); defaults to the current sys.stdout.
			sep: string inserted between values, default a space.
			end: string appended after the last value, default a newline.
	参考：
		• IPython user manual: https://ipython.readthedocs.io/en/stable/
		• Jupyter Notebook QuickStart: http://jupyter.readthedocs.io/en/latest/content-quickstart.html

#####1.4.2 在编辑器中精化作品
	随着您的发展，不仅要交互式地工作，而且要创建和重用Python文件，这一点非常重要。为此，一个强大的代码编辑器会让您走得更远。这里有几个好用的编辑器:
		•Spyder:集成了一个IPython控制台，一个调试器，一个分析器…
		•PyCharm:集成了IPython控制台，笔记本电脑，调试器…
		•Visual Studio Code:集成了一个Python控制台，笔记本，调试器，…
		•Atom
	其中一些由各种科学Python发行版提供，您可以在菜单中找到它们。
	作为练习，在代码编辑器中创建一个文件my_file.py，并添加以下行:
___
		s = 'Hello world'
		print(s)
___
	现在，您可以在IPython控制台或笔记本中运行它，并探索产生的变量:
___
		In [1]: %run my_file.py
		Hello world
		In [2]: s
		Out[2]: 'Hello world'
		In [3]: %whos
		Variable Type Data/Info
		----------------------------
		s str Hello world
___
	从脚本到函数
	虽然只使用脚本是很诱人的，这是一个充满指令的文件，遵循彼此，计划逐步发展脚本的一组函数:
	• 脚本不可重用，函数可重用。
	• 从功能的角度思考有助于将问题分解成小块。
___

#####1.4.3 IPython和Jupyter提示和技巧
	用户手册中包含了丰富的信息。这里我们将快速介绍四个有用的特性:历史记录、选项卡补全、神奇函数和别名。
	与UNIX shell一样，IPython控制台支持命令历史记录。向上和向下输入来导航前面输入的命令:
___
	In [1]: x = 10
	In [2]: <UP>
	In [2]: x = 10
___
	制表补全制表补全是一种方便的方式来探索你正在处理的任何对象的结构。只需输入object_name。查看对象的属性。除了Python对象和关键字，制表补全还可以用于文件和目录名
___
	In [1]: x = 10
	In [2]: x.<TAB>
	x.bit_length x.denominator x.imag x.real
	x.conjugate x.from_bytes x.numerator x.to_bytes
___
	控制台和notebook通过在命令前加上%字符来支持所谓的魔法函数。例如，上一节中的run和whoos函数是魔术函数。注意，默认情况下启用的设置automagic允许您省略前面的%符号。因此，只需输入这个神奇的函数，它就会工作。
	其他有用的神奇函数有:
		•%cd更改当前目录。
___
	In [1]: cd /tmp
	/tmp
___
		•%cpaste允许你粘贴代码，特别是来自那些以标准Python提示符(例如>>>)或以ipython提示符前缀的网站的代码，(例如[3]):
___
	In [2]: %cpaste
	Pasting code; enter '--' alone on the line to stop or use Ctrl-D.
	:>>> for i in range(3):
	:... print(i)
	:--
	0
	1
	2
___
%timeit允许你使用标准库中的timeit模块对短片段的执行进行计时:
___
	In [3]: %timeit x = 10
	10000000 loops, best of 3: 39 ns per loop
___
	参考:
		Chapter on optimizing code
	%debug允许您进入事后调试。也就是说，如果您试图执行的代码引发异常，使用%debug将在抛出异常的地方进入调试器。
___
	In [4]: x === 10
	File "<ipython-input-6-12fd421b5f28>", line 1
	x === 10
	^
	SyntaxError: invalid syntax
	In [5]: %debug
	> /.../IPython/core/compilerop.py (87)ast_parse()
	86 and are passed to the built-in compile function."""
	---> 87 return compile(source, filename, symbol, self.flags | PyCF_ONLY_AST, 1)
	88
	ipdb>locals()
	{'source': u'x === 10\n', 'symbol': 'exec', 'self':
	<IPython.core.compilerop.CachingCompiler instance at 0x2ad8ef0>,
	'filename': '<ipython-input-6-12fd421b5f28>'}
___
	参考:
		Chapter on debugging

	此外，IPython附带各种别名，这些别名模拟常见的UNIX命令行工具，如ls列出文件、cp复制文件和rm删除文件(输入别名时显示别名的完整列表)。
___
	获取帮助
		• 内置的备忘单可以通过神奇的%quickref函数访问。
		• 当输入%magic时，会显示所有可用的magic函数的列表。



















































