
#####附录A总结：
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
		
___
		// 对于需要可变长数组的地方  请使用 alloca 而不是使用下列的方法
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
___
	整数转换：
		char -1 		unchar y
		整数 x 转无符号类型 y
		满足(x % y) == (x % (y(max) + 1))的最小y
		
	参数不定式
		void test(int a, ...)
		
	一元表达式自右向左
	x + 表达式