
### 标准词汇
	access 访问
	alignment 对齐
	argument 参数
	behavior 外表或行为
	implementation-defined behavior 具体实现
	locale-specific behavior 特定行为
	undefined behavior 未定义行为
	unspecified behavior 未指明行为
	bit 位
	byte 字节
	character
	multibyte character
	wide character
	constraint 约束
	correctly rounded result 正确的结果
	diagnostic message 诊断信息
	forward reference 参考前文
	implementation 实现
	implementation limit 条件实现
	memory location
	object
	parameter
	recommended practice
	runtime-constraint 运行条件
	value
	implementation-defined value
	indeterminate value
	unspecified value
	trap representation
	perform a trap

### 预处理单元
	进行预处理前的所有头文件和源文件
	
### 转换单元
	预处理单元经过预处理后
	经过预处理的转换单元可以单独保存，也可以存放在lib中，

## decomposed
### Translation phases
	1. 多字节字符转化位源字符（ascii or other）,行结束添加换行字符，三字节序列替换为单字符表示
	2. \ 连接，非空的源文件应以换行符结束
	3. 源文件分解到预处理标记和空白字符序列（包括注释）
	4. 进行预处理、展开宏，通过标记链接产生了通用字符名称的字符序列
	5. 字符常量和字符串字面量和专一虚拟进行转换为可执行字符集的相应成员；若字符集不包含，转换为除null以外的实现定义的成员
	6. 相邻字符串进行连接
	7. 每个预处理符号都被转换成一个标号
	8. 链接外部对象和函数引用，生产可执行image



### 转换构造函数
	声明时不带函数说明符 explicit 的拥有单个无默认值形参的 (C++11 前)构造函数被称作转换构造函数
	构造函数（除了复制或移动）和用户定义转换函数都可以是函数模板；explicit 的含义不变。

### 关键字

	explicit   明确的
	指定构造函数或转换函数 (C++11 起)或推导指引 (C++17 起)为显式，即它不能用于隐式转换和复制初始化。

### 引用、指针
	（1）指针在定义的时候可以不初始化，但引用在定义的时候必须初始化。

	（2）指针可以为空，引用不能为空。

	（3）指针可以改变他的指向的对象，但引用不可以。

	（4）引用的大小是所指向的变量的大小，因为引用只是一个别名而已；指针是指针本身的大小，4个字节。

	（5）引用比指针更安全。由于不存在空引用，并且引用一旦被初始化为指向一个对象，它就不能被改变为另一个对象的引用，因此引用很安全。对于指针来说，它可以随时指向别的对象，并且可以不被初始化，或为NULL，所以不安全。const 指针虽然不能改变指向，但仍然存在空指针，并且有可能产生野指针（即多个指针指向一块内存，free掉一个指针之后，别的指针就成了野指针）。