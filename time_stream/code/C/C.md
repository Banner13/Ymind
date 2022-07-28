###注释
	注释作用在预处理阶段前，所以不会在宏定义中起作用
	注释段会被 一个空格 代替
____
###宏定义注意
	#define function(x,y)		atomic_store (p, (struct S){ a, b })
	会被解释为 function(p,(struct S){ a)  造成错误,请使用括号保护
	
	#define showlist(...)  function(#__VA_ARGS__)		# 字符串化参数
	
	#define S ss
	#define showlist(...)  function(S##__VA_ARGS__)		## “连接”或“记号粘贴”
___


关键词

标识符 变量名/常量名
int 标识符
char 标识符

实体： 存放于内存中的具体数值

声明： 表示是否存在			// 声明后 空间即分配
定义： 对其进行描述
初始化： 赋值
___
###四类命名空间： 同一作用域内、享同命名空间的描述符不得相同
	label 　　　　标号
	tag 　　　　　struct、enum、union同属于一个命名空间
	tag_sub　　　 struct、union成员
	other　　　　 其他描述符  // 变量名、函数名、函数参数、宏定义、typedef、enum成员
	
	注意：如果标识符出现重名的情况，宏定义会覆盖所有其它标识符，这是因为它在预处理阶段而不是编译阶段处理。
	除了宏定义之外其它类别的标识符，处理规则是：内层作用域会隐藏掉外层作用域的标识符。
___
###作用域：

	C 拥有四种作用域：
	块作用域
	文件作用域
	函数作用域
	函数原型作用域 



语句是带顺序执行的 C 程序段。

	语句有五种类型：
	1) 复合语句
	2) 表达式语句
	3) 选择语句
	4) 循环语句
	5) 跳转语句
___

###标号

	任何语句都能有标号，通过在语句自身前提供一个跟随冒号的名称。
	switch {
		case 1:xxx
		xxx:
		default:
		xxx
	}
	
	ERROR:xxx
___

###复合语句
	if (expr) // if 语句的开始
	
	{
	  int n = 1; // 声明
	  printf("%d\n", n); // 表达式语句
	}
标签名： 所有声明为 struct 、union、以及enum名称的标识符。 以上三者共享同一命名空间。


API

	strstr()
	char *strstr(const char *haystack, const char *needle) 
	在字符串 haystack 中查找第一次出现字符串 needle 的位置，不包含终止符 '\0'。
	
	
	 sizeof是C语言的一种单目操作符，如C语言的其他操作符++、--等。它并不是函数。
	 sizeof操作符以字节形式给出了其操作数的存储大小。操作数可以是一个表达式或括在括号内的类型名。
	 操作数的存储大小由操作数的类型决定。
	
	
	