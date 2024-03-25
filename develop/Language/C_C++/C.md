[TOC]

### 注释
	注释作用在预处理阶段前，所以不会在宏定义中起作用
	注释段会被 一个空格 代替
____
### 宏定义注意
	#define function(x,y)		atomic_store (p, (struct S){ a, b })
	会被解释为 function(p,(struct S){ a)  造成错误,请使用括号保护
	
	#define showlist(...)  function(#__VA_ARGS__)		# 字符串化参数
	
	#define S ss
	#define showlist(...)  function(S##__VA_ARGS__)		## “连接”或“记号粘贴”
___


### 关键词

	标识符 变量名/常量名
	int 标识符
	char 标识符

	实体： 存放于内存中的具体数值

	声明： 表示是否存在			// 声明后 空间即分配
	定义： 对其进行描述
	初始化： 赋值
___
### 四类命名空间： 同一作用域内、享同命名空间的描述符不得相同
	label 　　　　标号
	tag 　　　　　struct、enum、union同属于一个命名空间
	tag_sub　　　 struct、union成员
	other　　　　 其他描述符  // 变量名、函数名、函数参数、宏定义、typedef、enum成员
	
	注意：如果标识符出现重名的情况，宏定义会覆盖所有其它标识符，这是因为它在预处理阶段而不是编译阶段处理。
	除了宏定义之外其它类别的标识符，处理规则是：内层作用域会隐藏掉外层作用域的标识符。
___
### 作用域：

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

### 标号

	任何语句都能有标号，通过在语句自身前提供一个跟随冒号的名称。
	switch {
		case 1:xxx
		xxx:
		default:
		xxx
	}
	
	ERROR:xxx
___

### 复合语句
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
	
### static
	在C中，static 变量只能使用常量初始化。

### 运算符优先级
	前述符
	单目运算符
	双目运算符
	算术运算符
	移位
	关系运算符
	逻辑运算
	赋值运算
	条件运算

### 结构体对齐
```c
#pragma pack(n)
```
demo
```c
#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#pragma pack(4)

struct Test {
    int a;
    char b;
    int c;
};
#pragma pack()

int main(void)
{
    struct Test t;

    printf("Test.a offset is %d\n", offsetof(struct Test, a));
    printf("Test.b offset is %d\n", offsetof(struct Test, b));
    printf("Test.c offset is %d\n", offsetof(struct Test, c));

    return 0;
}

```

```out
Test.a offset is 0
Test.b offset is 4
Test.c offset is 8
```

### 附录A总结：
	C语言中的记号：关键字、运算符、其他分隔符、字符串字面值、常量、标识符。(空格、制表符、换行符，换页符和注释(统称空白符))用于分隔记号。
	空格（‘ ’）、换页（‘\f’）、换行（‘\n’）、回车（‘\r’）、水平制表符（‘\t’）、垂直制表符（‘\v’）、注释（‘\\ or \**\’）
	
	关键字：
	void signed unsigned \ sizeof char short int long \ double float
	do while , if else for, switch case continue default break , goto return
	auto const static extern register volatile
	struct union enum typedef
	
	标识符：
		变量名
		
		左值 = 标识符 + 引用。
		
		int x;	//声明：定义了 标识符 x	及其类型 int
		x = 0x01;	// x 引用 0x01
		x;	左值 x (=0x01)
		

###对于需要可变长数组的地方  请使用 alloca 而不是使用下列的方法
		#include<stdio.h>
		int main(void) {

			int x[3][2] = {{1, 2},{3, 4},{5, 6}};
			int (*p)[2] = &x[0];    // *p = int[2] -> p = &(int[2])
			int q[2] = {0}; // q = int[2]

			printf("%d \n", **x);
			printf("%d \n", **(p+1));
			printf("%d \n", **(p+2));

			return 0;
		}

### 整数转换：
		char -1 		unchar y
		整数 x 转无符号类型 y
		满足(x % y) == (x % (y(max) + 1))的最小y

### 参数不定式
		void test(int a, ...)

### 一元表达式自右向左
	x + 表达式

### 数组

```c
// --run--
char buffer[16];

struct A {
    int x,
    int y,
    char *p;
};

struct B {
    int x,
    int y,
    char p[2];
};

struct A A1;
struct B B1;

sprintf(A1.p, 2, "s");
sprintf(A2.p, 2, "s");

// 结论：数组就是数组，是大小相同、空间连续的存储空间。
// 指针是变量，变量，变量！
// char *q = A1.p;  和 char *q = B1.p; 作用完全不同
```