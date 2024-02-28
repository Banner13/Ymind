
#C++之旅——Bjarne Stroustrup(第二版)

<pre>
(Addison-Wesley)安迪生韦斯利出版社

	制造商和销售商用来区分其产品的许多名称都被称为商标。如果这些名称出现在这本书中，并且出版商知道商标权利要求，这些名称已经以大写字母或所有大写字母印刷。

	作者和出版商在本书的编写过程中都非常谨慎，但不作任何明示或暗示的保证，也不对错误或遗漏承担任何责任。对于与使用本网站所载资讯或程式有关或因使用本网站所载资讯或程式而引致的附带或后果性损害，本网站不承担任何责任。

	有关大量购买本书籍的信息，或特殊销售机会(可能包括电子版本;定制的封面设计;以及与您的业务、培训目标、营销重点或品牌利益相关的内容)，请联系我们的公司销售部corpsales@pearsoned.com或(800)382-3419。

	如需政府销售咨询，请联系governmentsales@pearsoned.com。

	关于美国以外的销售问题，请联系intlcs@pearson.com。

	访问我们的网站:informit.com/aw美国国会图书馆控制编号:2018941627版权所有©2018皮尔森教育有限公司

	保留所有权利。本出版物受版权保护，在禁止复制、储存于检索系统或以任何形式或方式(电子、机械、影印、录音等)传送本出版物之前，必须获得出版者的许可。有关培生教育全球权利与权限部门的权限、请求表格和相关联系方式的信息，请访问www.pearsoned.com/permissions/。

	这本书被作者在《时代》和《Helvetica》上排版。

	ISBN-10: 0-13-499783- 3第三次打印，2019年3月3 19
</pre>

## 目录
[TOC]

___

### 前言

    When you wish to instruct,be brief.
                                        – Cicero

        c++感觉像是一门新语言。是的，比起c++98，今天我可以更清晰、更简单、更直接地表达我的想法。此外，生成的程序得到了编译器更好的检查，也运行得更快。
        本书概述了目前ISO c++标准c++17定义的c++，并由主要的c++发布者实现。此外，它提到了在ISO技术规范和当前使用中定义的概念和模块，但直到c++ 20才计划纳入标准。
        像其他现代语言一样，c++很大，需要大量的库来有效地使用。这本薄薄的书旨在让有经验的程序员了解现代c++是由什么组成的。它涵盖了大多数主要的语言特性和主要的标准库组件。这本书可以在几个小时内读完，但很明显，要写出好的c++，一天的学习是远远不够的。然而，这里的目标不是精通，而是给出一个概述，给出关键的例子，并帮助程序员入门。
        假设您以前编写过程序。如果没有，在继续之前，请考虑阅读教科书，例如《编程:使用c++的原理与实践》(第二版)[Strous-trup,2014]。即使您以前编写过程序，您使用的语言或您编写的应用程序可能与本文介绍的c++风格非常不同。
        想象一次城市观光旅行，比如哥本哈根或纽约。在短短几个小时内，你可以快速浏览主要景点，了解一些背景故事，并就下一步该怎么做给出一些建议。这样的游览之后你就不了解这个城市了。你不了解你所看到和听到的一切。你不知道如何驾驭管理城市生活的正式和非正式规则。要想真正了解一座城市，你必须住在里面，通常要住上好几年。然而，如果运气好的话，你会对这座城市的概况有所了解，对它的特别之处有所了解，对你感兴趣的东西有所了解。游览结束后，真正的探索就可以开始了。
        本文介绍了c++语言的主要特性，因为它们支持编程风格，比如面向对象和泛型编程。它不试图提供详细的、参考手册式的、逐项查看该语言的视图。按照最好的教科书传统，我在使用一个特性之前会先解释它，但这并不总是可能的，也不是每个人都严格按照顺序阅读文本。
        因此，建议读者使用交叉引用和索引。
        类似地，本文将以示例的形式介绍标准库，而不是详尽地介绍。它没有描述ISO标准之外的库。读者可以根据需要查找辅助材料。[Stroustrup,2013]和[Stroustrup,2014]是这样的材料的例子，但在网络上有大量的材料(质量不一)，例如[Cppreference]。例如，当我提到一个标准库函数或类时，可以很容易地查找它的定义，通过检查它的文档，可以找到许多相关的工具。
        本文将把c++作为一个完整的整体来介绍，而不是一层一层的蛋糕。因此，它不能识别C中存在的语言特性，c++ 98的一部分，或c++ 11、c++ 14或c++ 17中的新特性。这些信息可以在第十六章(历史和兼容性)中找到。我专注于基本原理，尽量简短，但我没有完全抵制住过度表现新颖特征的诱惑。这似乎也满足了许多读者的好奇心，他们已经知道一些较早版本的c++。
        编程语言参考手册或标准只是简单地说明可以做什么，但程序员通常更感兴趣的是学习如何更好地使用语言。这方面的内容部分在所涉及主题的选择中，部分在文本中，特别是在建议部分中。关于如何构成优秀的现代c++的更多建议可以在c++核心指南[Stroustrup,2015]中找到。本书的核心指导方针可以成为进一步探讨本书所提出思想的一个很好的来源。你可能会注意到，《核心指南》和本书在建议的制定乃至建议的编号方面有显著的相似性。一个原因是第一版的《c++之旅》是最初核心指南的主要来源。

    鸣谢
    	这里介绍的一些材料是从TC++PL4 [Stroustrup,2013]中借来的，所以感谢所有帮助完成这本书的人。
    	感谢所有帮助完成和纠正第一版“c++之旅”的人。“感谢摩根士丹利(Morgan Stanley)给我时间写这本书的第二版。感谢哥伦比亚大学2018年春季“使用c++设计”类在这本书的早期草稿中发现了许多错别字和bug，并提出了许多建设性的建议。
    	感谢Paul Anderson、Chuck Allison、Peter Gottschling、William Mon、Charles Wilson和Sergey Zubkov对该书的评论和许多改进建议。
    	曼哈顿,纽约
        																	Bjarne Stroustrup
___

### 1 基础

	The first thing we do, let’skill all the language lawyers.	– Henry VI, Part II
    •	介绍
    •	程序
            Hello, World!
    •	函数
    •	类型、变量和运算
            算术;初始化
    •	作用域和生存期
    •	常量
    •	指针、数组和引用
            空指针
    •	测试
    •	映射到硬件
            赋值;初始化
    •	建议


#### 1.1 介绍
		本章非正式地介绍了c++的符号，c++的内存和计算模型，以及将代码构建为程序的基本机制。这些语言工具支持C语言中最常见的风格，有时也被称为过程式编程(面向过程编程)^1^。
	^1^ 译注

#### 1.2 程序
		C++ 是一种编译语言。一个程序的运行，首先它的源文本(source text)需要被编译器(compiler)处理，生成目标(object)文件，然后通过链接器(linker)将它们合并到一起，产生一个可执行程序。一个c++程序通常由许多源代码文件(通常简称为源文件)组成。
    	可执行程序是为特定的硬件/系统组合而创建的;它不能从Mac电脑移植到Windows电脑上。当我们谈论c++程序的可移植性时，我们通常指的是源代码的可移植性;也就是说，源代码可以成功地编译并在各种系统上运行。
    	ISO c++标准定义了两种实体:
        • 核心语言特性，如内置类型(如char和int)和循环(如for声明和while声明)。
        • 标准库组件，如容器(如vector和map)和I/O操作(如<<和getline())。
        标准库组件是由每个c++实现提供的非常普通的c++代码。也就是说，c++标准库可以用c++本身实现，而且确实是这样的(在线程上下文切换等事情上只需要很少的机器代码)。这意味着c++对于最苛刻的系统编程任务具有足够的表现力和效率。
        c++是一种静态类型语言。也就是说，编译器在使用每个实体(例如，对象、值、名称和表达式)时必须知道它的类型。对象的类型决定了适用于该对象的操作集。

##### 1.2.1 Hello,World!
		最小的c++程序是
        	int main() { } // the minimal C++ program
            这定义了一个名为main的函数，它不接受参数，也不执行任何操作。
            花括号，{}，在c++中表示分组。在这里，它们表示函数体的开始和结束。
            双斜杠，//，注释开始一直延伸到行尾的。注释是写给人类读者的;编译器会忽略注释。
        每个c++程序必须只有一个名为main()的全局函数。程序从执行该函数开始。main()返回的int整型值(如果有的话)是程序返回给“系统”的值。如果没有返回值，系统将接收到一个指示成功完成的值。main()中的非零值表示失败。并不是每个操作系统和执行环境都使用这个返回值:基于Linux/ unix的环境会这样做，但基于windows的环境很少这样做。
       	通常，程序会产生一些输出。这里有一个写 Hello, World! 的程序：
```c++
#include <iostream>
int main()
{
	std::cout << "Hello, World!\n";
}
```
		#include <iostream> 这一行告诉编译器需要编译的内容还包含 iostream 文件。没有这些声明，表达式：
    	std::cout << "Hello, World!\n"
    	没有任何意义。	// 译注：该文件为标准库中的文件，存放在编译器目录下，提供标准I/O流的功能。
    操作符<< (" put to ")将其第二个参数写入其第一个参数。在本例中，字符串字面量“Hello, World!”\n”被写入标准输出流std::cout。字符串字面量是由双引号包围的字符序列。在字符串字面量中，反斜杠字符\后跟另一个字符表示单个“特殊字符”。在本例中，\n是换行字符，因此写入的字符是Hello, World!后跟换行符。
    	std::指定名称cout在标准库命名空间中找到(§3.4)。在讨论标准特性时，我通常会省略std::;§3.4展示了如何在没有显式限定的情况下使名称空间中的名称可见。
        实际上，所有可执行代码都放在函数中，并直接或间接地从main()调用。例如:
```c++
#include <iostream> // include (‘‘import’’) the declarations for the I/O stream librar y
using namespace std; // make names from std visible without std:: (§3.4)
double square(double x) // square a double precision floating-point number
{
	return x∗x;
}
void print_square(double x)
{
	cout << "the square of " << x << " is " << square(x) << "\n";
}
int main()
{
	print_square(1.234); // pr int: the square of 1.234 is 1.52276
}
```
		“返回类型”void表示函数不返回值。

####1.3 函数
	// 译注：Function 大多数时候翻译为"函数"，也可翻译为"功能"。
    // 对于计算机的初衷(一种计算工具)来说，Function的目的就是一组数据通过这个Function而得到一组输出，就像数学中的 Y = f(x)， 这个f() 就等是y对于x的函数表达式，所以称为函数。
    // 然后往上抽象，对于软件开发人员来说，我们实现的简称为功能，所以只是叫法不同。

    	在c++程序中完成某件事的主要方法是调用函数。定义函数就是指定如何执行操作的方式。除非事先声明过，否则不能调用函数。
        函数声明给出了函数的名称、返回值的类型(如果有的话)以及调用中必须提供的参数的数量和类型。例如:
            Elem∗ next_elem(); // 无参数; 返回Elem类型的指针 (an Elem*)
            void exit(int); // int类型参数; 无返回
            double sqrt(double); // double类型参数; 返回double类型
        在函数声明中，返回类型在函数名之前，参数类型在函数名之后的括号中。
        参数传递的语义与初始化的语义相同(§3.6.1)。也就是说，检查实参类型，必要时进行隐式实参类型转换(§1.4)。例如:
        	double s2 = sqrt(2); // 使用double类型的2，调用sqrt()函数
			double s3 = sqrt("three"); // 错误 : sqrt() 需要 double 类型的参数
        这种编译时检查和类型转换的价值不应低估。
        函数声明可以包含参数名。这对程序的读者是有帮助的，但是除非声明也是一个函数定义，否则编译器会简单地忽略这些名称。例如:
        	double sqrt(double d); // 返回d的平方根
			double square(double); // 返回参数的平方
        函数的类型由它的返回类型和参数类型的序列组成。例如:
        	double get(const vector<double>& vec, int index); //类型: double(const vector<double>&,int)
        函数可以是类的成员(§2.3，§4.2.1)。对于这样的成员函数，其类名也是函数类型的一部分。例如:
        	char& String::operator[](int index); //类型: char& String::(int)
        我们希望我们的代码是可理解的，因为这是实现可维护性的第一步。可理解性的第一步是将计算任务分解成有意义的块(以函数和类的形式表示)并命名它们。然后，这些函数提供基本的计算词汇，就像类型(内置的和用户定义的)提供基本的数据词汇一样。c++标准算法(如find、sort和iota)提供了一个良好的开端(第12章)。接下来，我们可以将表示普通或专门任务的函数组合成更大的计算。
        代码中的错误数量与代码的数量和代码的复杂性密切相关。这两个问题都可以通过使用更多更短的函数来解决。使用函数来完成特定的任务通常可以避免我们在其他代码中编写特定的代码片段;使它成为一个函数将迫使我们命名活动并记录其依赖关系。
        如果两个函数定义为同名，但实参类型不同，编译器将为每次调用选择最合适的函数来调用。例如:
        	void print(int); // 接受一个int参数
            void print(double); // 接受一个double参数
            void print(string); // 接受一个string参数
            void user()
            {
                print(42); // 调用 print(int)
                print(9.65); // 调用 print(double)
                print("Barcelona"); // 调用 print(str ing)
            }
        如果可以调用两个可选函数，但两者都可以使用，则该调用被认为是二义性的，编译器会给出错误。例如:
			void print(int,double);
            void print(double ,int);
            void user2()
            {
            	print(0,0); // error : ambiguous
            }
        定义多个同名函数被称为函数重载，这是泛型编程的基本部分之一(§7.2)。当一个函数被重载时，每个相同名称的函数应该实现相同的语义。print()函数就是这样一个例子;每个print()都会打印它的参数。

####1.4 类型、变量和运算
		每个名称和每个表达式都有一个类型，该类型决定了可能对其执行的操作。例如，声明
    		int inch;
    	指定inch为int类型;也就是说，inch是一个整数变量。
    	声明是将实体引入程序的语句。它指定了实体的类型:
        	• 类型定义了一组可能的值和一组操作(对于对象)。
            • 对象是存储某种类型值的内存。
            • 值是根据类型解释的位的集合。
            • 变量是一个命名对象。
        c++提供了一个基本类型的小型动物园，但由于我不是动物学家，我就不一一列出了。你可以在参考资料中找到它们，比如[Stroustrup,2013]或[Cppreference]。例子有:
            bool // Boolean, possible values are true and false
            char // character, for example, 'a', 'z', and '9'
            int // integer, for example, -273, 42, and 1066
            double // double-precision floating-point number, for example, -273.15, 3.14, and 6.626e-34
            unsigned // non-negative integer, for example, 0, 1, and 999 (use for bitwise logical operations)
        每一种基本类型都直接对应于硬件设施，并具有固定的大小，决定了可以存储在其中的值的范围:
		一个char变量具有在给定机器上保存一个字符的自然大小(通常是8位字节)，而其他类型的变量的大小是一个char大小的倍数。类型的大小是由实现定义的(即，它可以在不同的机器上变化)，可以通过sizeeof操作符获得;例如，sizeof(char)等于1，而sizeof(int)通常是4。
        数字可以是浮点数或整数。
        • 浮点数可由小数点(如3.14)或指数(如3e−2)识别。
		• 整数字面值默认为十进制(例如，42表示42)。
        	0b前缀表示二进制(基数2)整数字面值(例如0b10101010)。
            0x前缀表示十六进制(以16为基数)整数字面值(例如0xBAD1234)。
            0前缀表示八进制(以8为基数)整数字面值(例如，0334)。
        为了使长文字更便于人类阅读，我们可以使用单引号(')作为数字分隔符。例如，π约为3.14159'26535'89793'23846'26433'83279'50288，或者你更喜欢十六进制的0x3.243F'6A88'85A3'08D3。

#####1.41 运算
		算术运算符可用于基本类型的适当组合:
            x+y // plus
            +x // unar y plus
            x−y // minus
            −x // unar y minus
            x∗y / / multiply
            x/y // divide
            x%y // remainder (modulus) for integers
        比较操作符也可以:
            x==y // equal
            x!=y // not equal
            x<y // less than
            x>y // greater than
            x<=y // less than or equal
            x>=y // greater than or equal
        此外，还提供了逻辑操作符:
            x&y // bitwise and
            x|y // bitwise or
            xˆy // bitwise exclusive or
            ˜x // bitwise complement
            x&&y // logical and
            x||y // logical or
            !x // logical not (negation)
        按位逻辑运算符产生对每个位执行操作的操作数类型的结果。逻辑操作符&&和||根据其操作数的值返回true或false。
		在赋值和算术运算中，c++执行基本类型之间所有有意义的转换，以便它们可以自由混合:
            void some_function() // function that doesn’t return a value
            {
                double d = 2.2; // initialize floating-point number
                int i = 7; // initialize integer
                d = d+i; // assign sum to d
                i = d∗i; // assign product to i; beware: truncating the double d*i to an int
            }
		表达式中使用的转换称为通常的算术转换，目的是确保以其操作数的最高精度计算表达式。例如，double类型和int类型的加法运算使用双精度浮点运算。
		注意=是赋值操作符，而==测试是否相等。
		除了传统的算术和逻辑运算符外，c++还提供了更具体的修改变量的操作:
            x+=y // x = x+y
            ++x // increment: x = x+1
            x−=y // x = x-y
            −−x // decrement: x = x-1
            x∗=y // scaling: x = x*y
            x/=y // scaling: x = x/y
            x%=y // x = x%y
        这些操作符简洁、方便、使用频率很高。
		表达式的求值顺序是从左到右，但赋值是从右到左的。不幸的是，函数参数的求值顺序没有指定。

#####1.42 初始化
		在使用一个对象之前，必须给它一个值。c++提供了表示初始化的各种表示法，例如上面使用的=，以及基于带花括号限制的初始化列表的通用形式:
            double d1 = 2.3; // initialize d1 to 2.3
            double d2 {2.3}; // initialize d2 to 2.3
            double d3 = {2.3}; // initialize d3 to 2.3 (the = is optional with { ... })
            complex<double> z = 1; // a complex number with double-precision floating-point scalars
            complex<double> z2 {d1,d2};
            complex<double> z3 = {d1,d2}; // the = is optional with { ... }
            vector<int> v {1,2,3,4,5,6}; // a vector of ints
        =形式是传统的，可以追溯到C语言，但如果有疑问，可以使用通用的{}-list形式。除此之外，它还可以避免在转换过程中丢失信息:
            int i1 = 7.8; // i1 becomes 7 (surpr ise?)
            int i2 {7.8}; // error : floating-point to integer conversion
        不幸的是，当您使用=时，允许并隐式应用丢失信息的转换，例如double到int和int到char的收缩转换(但当您使用{}时则不允许)。隐式收缩转换带来的问题是C兼容性所付出的代价(§16.3)。
        常量(§1.6)不能不初始化，变量只有在极其罕见的情况下才应该不初始化。在有合适的值之前不要引入名称。用户定义的类型(如string、vector、Matrix、Motor_controller和Orc_warrior)可以被定义为隐式初始化(§4.2.1)。
        当定义一个变量时，当它可以从初始化式推导出来时，你不需要显式地声明它的类型:
            auto b = true; // a bool
            auto ch = 'x'; // a char
            auto i = 123; // an int
            auto d = 1.2; // a double
            auto z = sqrt(y); // z has the type of whatever sqr t(y) retur ns
            auto bb {true}; // bb is a bool
        对于auto，我们倾向于使用=，因为不涉及潜在的麻烦的类型转换，但如果您喜欢始终使用{}初始化，您可以这样做。
        在没有特定原因需要显式提及类型时，我们使用auto。“特殊原因”包括:
        • 定义在一个很大的范围内，我们想让类型对代码的读者清晰可见。
        • 我们想要明确变量的范围或精度(例如，double而不是float)。
        使用auto，可以避免冗余和编写长类型名。这在泛型编程中尤其重要，因为程序员很难知道对象的确切类型，而且类型名称可能很长(§12.2)。

####1.5 作用域和生存周期
		声明将其名称引入作用域:
            •局部作用域:在函数(§1.3)或lambda(§6.3.2)中声明的名称称为局部名称。
            它的范围从声明点扩展到发生声明的块的末尾。块由{}对分隔。函数参数名被认为是局部名称。
            •类作用域:定义在类(§2.2，§2.3,Chapter 4)、函数(§1.3)、lambda(§6.3.2)或enum类(§2.5)之外的名称称为成员名(或类成员名)。它的范围从其附随声明的开头一直延伸到该声明的结尾。
            •命名空间作用域:如果一个名字定义在任何函数、lambda(§6.3.2)、class(§2.2、§2.3、Chapter 4)或enum类(§2.5)之外的命名空间(§3.4)，这个名字就被称为命名空间成员名。它的作用域从声明点扩展到命名空间的末尾。
		没有在任何其他构造中声明的名称称为全局名称，并被称为在全局命名空间中。
        此外，我们还可以使用没有名称的对象，例如temporary和new创建的对象(§4.2.2)。例如:
            vector<int> vec; // vec is global (a global vector of integers)
            struct Record {
            string name; // name is a member or Record (a string member)
            // ...
            };
            void fct(int arg) // fct is global (a global function)
            // arg is local (an integer argument)
            {
                string motto {"Who dares wins"}; // motto is local
                auto p = new Record{"Hume"}; // p points to an unnamed Record (created by new)
                // ...
            }
        对象必须在使用之前被构造(初始化)，并在其作用域结束时被销毁。对于命名空间对象，销毁点是程序的结尾。对于成员，销毁点由其所属对象的销毁点决定。由new “lives” 创建的对象直到被delete(§4.2.2)销毁为止。

####1.6 常量
        c++支持两种不可变的概念:
            • const:大致意思是“我保证不改变这个值。这主要用于指定接口，以便使用指针和引用将数据传递给函数，而不用担心数据被修改。编译器强制执行const所做的承诺。const的值可以在运行时计算。
            • constexpr:大致意思是“在编译时进行评估”。这主要用于指定常量，允许将数据放置在只读内存中(在那里数据不太可能被损坏)，以及提高性能。编译器必须计算constexpr的值。
        例如:
            constexpr int dmv = 17; // dmv is a named constant
            int var = 17; // var is not a constant
            const double sqv = sqrt(var); // sqv is a named constant, possibly computed at run time
            double sum(const vector<double>&); // sum will not modify its argument (§1.7)
            vector<double> v {1.2, 3.4, 4.5}; // v is not a constant
            const double s1 = sum(v); // OK: sum(v) is evaluated at run time
            constexpr double s2 = sum(v); // error : sum(v) is not a constant expression
        要使函数在常量表达式中可用，也就是说，在将被编译器求值的表达式中，它必须被定义为constexpr。例如:
            constexpr double square(double x) { return x∗x; }
            constexpr double max1 = 1.4∗square(17); // OK 1.4*square(17) is a constant expression
            constexpr double max2 = 1.4∗square(var); // error : var is not a constant expression
            const double max3 = 1.4∗square(var); // OK, may be evaluated at run time
        constexpr函数可以用于非常量参数，但当这样做时，结果不是常量表达式。我们允许在不需要常量表达式的上下文中使用非常量表达式参数调用constexpr函数。这样，我们就不必定义两次本质上相同的函数:一次用于常量表达式，一次用于变量。
        要成为constexpr，函数必须相当简单，不能有副作用，只能使用传递给它的信息作为参数。特别地，它不能修改非局部变量，但它可以有循环并使用自己的局部变量。例如:
            constexpr double nth(double x, int n) // assume 0<=n
            {
                double res = 1;
                int i = 0;
                while (i<n)
                { // while-loop: do while the condition is true (§1.7.1)
                    res∗=x;
                    ++i;
                }
                return res;
            }
        在一些地方，语言规则需要常量表达式(例如，数组边界(§1.7)、case标签(§1.8)、模板值参数(§6.2)和使用constexpr声明的常量)。在其他情况下，编译时评估对性能很重要。与性能问题无关，不变性(状态不变的对象)的概念是一个重要的设计问题。

####1.7 指针、数组和引用
		最基本的数据集合是连续分配的相同类型的元素序列，称为数组。这基本上就是硬件所提供的。char类型的元素数组可以这样声明:
        	char v[6]; // array of 6 characters
        类似地，指针可以这样声明:
        	char∗ p; // pointer to character
        在声明中，[]表示“的数组”，而∗表示“指向的指针”。所有数组的下界都是0，所以v有6个元素，从v[0]到v[5]。数组的大小必须是常量表达式(§1.6)。
		指针变量可以保存适当类型的对象的地址:
            char∗ p = &v[3]; // p points to v’s four th element
            char x = ∗p; // *p is the object that p points to
        在表达式中，前缀unary∗表示“的内容”，前缀unary &表示“的地址”。
        考虑将10个元素从一个数组复制到另一个数组:
            void copy_fct()
            {
                int v1[10] = {0,1,2,3,4,5,6,7,8,9};
                int v2[10]; // to become a copy of v1
                for (auto i=0; i!=10; ++i) // copy elements
                v2[i]=v1[i];
                // ...
            }
        这个for语句可以读作“设i为零;当i不是10时，复制第i个元素并使i递增。”当应用于整数或浮点变量时，自增操作符++只增加1。
		c++还提供了一种更简单的for-statement，称为range-for-statement，用于以最简单的方式遍历序列:
            void print()
            {
                int v[] = {0,1,2,3,4,5,6,7,8,9};
                for (auto x : v) // for each x in v
                	cout << x << '\n';
                for (auto x : {10,21,32,43,54,65})
                	cout << x << '\n';
                // ...
            }
        第一个range-for语句可以读作“对于v中的每个元素，从第一个到最后一个，在x中放置一个副本并打印出来”。注意，当我们用列表初始化它时，不需要指定数组绑定。range-for语句可用于任何元素序列(§12.1)。
		如果我们不想将v中的值复制到变量x中，而只是让x指向一个元素，我们可以这样写:
            void increment()
            {
                int v[] = {0,1,2,3,4,5,6,7,8,9};
                for (auto& x : v) // add 1 to each x in v
                	++x;
                // ...
            }
        在声明中，一元后缀&表示“引用”。引用类似于指针，只是不需要使用前缀∗来访问引用引用的值。另外，不能在初始化后引用另一个对象。
		引用在指定函数参数时特别有用。例如:
        	void sort(vector<double>& v); // sor t v (v is a vector of doubles)
        通过使用引用，我们确保对于调用或t(my_vec)，我们没有复制my_vec，并且排序的是my_vec，而不是它的副本。
        当我们不想修改实参，但又不想花费复制的代价时，我们使用const引用(§1.6)。例如:
        	double sum(const vector<double>&)
        接受const引用的函数非常常见。
        当在声明中使用时，操作符(比如&、∗和[])被称为声明符:
            T a[n] // T[n]: a is an array of n Ts
            T∗ p / / T*: p is a pointer to T
            T& r // T&: r is a reference to T
            T f(A) // T(A): f is a function taking an argument of type A returning a result of type T

#####1.7.1 空指针
		我们试图确保指针始终指向对象，以便对其解除引用是有效的。如果没有对象可指向，或者需要表示“无对象可用”的概念(例如，列表的末尾)，则为指针赋值nullptr(“空指针”)。所有指针类型只共享一个nullptr:
        	double∗ pd = nullptr;
            Link<Record>∗ lst = nullptr; // pointer to a Link to a Record
            int x = nullptr; // error : nullptr is a pointer not an integer
        检查指针参数是否确实指向某些东西通常是明智的:
            int count_x(const char∗ p, char x)
            // count the number of occurrences of x in p[]
            // p is assumed to point to a zero-ter minated array of char (or to nothing)
            {
                if (p==nullptr)
                	return 0;
                int count = 0;
                for (; ∗p!=0; ++p)
                	if (∗p==x)
                		++count;
                return count;
            }
        注意，我们可以使用++将指针推进到数组的下一个元素，如果不需要，可以在for语句中省略初始化式。
		count_x()的定义假设∗这个字符是一个c风格的字符串，也就是说，这个指针指向一个以零结尾的字符数组。字符串字面值中的字符是不可变的，因此为了处理count_x("Hello!")，我声明count_x()为一个const char *实参。
		在旧代码中，通常使用0或NULL来代替nullptr。然而，使用nullptr消除了整数(如0或NULL)和指针(如nullptr)之间的潜在混淆。
		在count_x()示例中，我们没有使用for语句的初始化器部分，因此可以使用更简单的while语句:
            int count_x(const char∗ p, char x)
            // count the number of occurrences of x in p[]
            // p is assumed to point to a zero-ter minated array of char (or to nothing)
            {
                if (p==nullptr)
                	return 0;
                int count = 0;
                while (∗p) {
                    if (∗p==x)
                    	++count;
                    ++p;
                }
                return count;
            }
        while语句一直执行，直到它的条件变为false。
		数值的测试(例如，count_x()中的while(∗p)等价于将该值与0进行比较(例如，while(∗p!=0))。对指针值的测试(例如，if (p))等价于将该值与nullptr比较(例如，if (p!=nullptr))。
		没有“空引用”。引用必须指向一个有效的对象(实现假定它是有效的)。我们可以通过一些模糊而巧妙的方式去违反这一规则;不要这样做。

####1.8 测试
		c++提供了一组常规的语句来表示选择和循环，比如if语句、switch语句、while-loops和for-loops。例如，下面是一个简单的函数，它提示用户并返回一个指示响应的布尔值:
            bool accept()
            {
                cout << "Do you want to proceed (y or n)?\n"; // wr ite question
                char answer = 0; // initialize to a value that will not appear on input
                cin >> answer; // read answer
                if (answer == 'y')
                    return true;
                return false;
            }
        为了匹配<<输出操作符(" put To ")，使用>>操作符(" get from ")作为输入;cin是标准输入流(第10章)。>>的右操作数的类型决定了接受什么输入，它的右操作数是输入操作的目标。输出字符串末尾的\n字符表示换行符(§1.2.1)。
		注意，answer的定义出现在需要它的地方(而不是之前)。声明可以出现在语句可以出现的任何地方。
        这个例子可以通过考虑n(表示“no”)来改进:
            bool accept2()
            {
                cout << "Do you want to proceed (y or n)?\n"; // wr ite question
                char answer = 0; // initialize to a value that will not appear on input
                cin >> answer; // read answer

                switch (answer)
                {
                    case 'y':
                    	return true;
                    case 'n':
                    	return false;
                    default:
                    	cout << "I'll take that for a no.\n";

                    return false;
                }
            }
        switch语句针对一组常量测试一个值。这些称为case-labels的常量必须是不同的，如果所测试的值与它们中的任何一个都不匹配，则选择默认值。如果值不匹配任何大小写标签，并且没有提供缺省值，则不采取任何操作。
        我们不需要通过从包含switch语句的函数返回来退出case。
		通常，我们只是想用switch语句后面的语句继续执行。我们可以使用break语句来实现这一点。举个例子来说吧，在一款简单的命令电子游戏中使用一个非常聪明但却非常原始的解析器:
            void action()
            {
                while (true)
                {
                    cout << "enter action:\n"; // request action
                    string act;
                    cin >> act; // read characters into a string
                    Point delta {0,0}; // Point holds an {x,y} pair
                    for (char ch : act)
                    {
                        switch (ch)
                        {
                            case 'u': // up
                            case 'n': // nor th
                            	++delta.y;
                            	break;
                            case 'r': // right
                            case 'e': // east
                            	++delta.x;
                            	break;
                            // ... more actions ...
                            default:
                            	cout << "I freeze!\n";
                        }
                        move(current+delta∗scale);
                        update_display();
                    }
                }
            }
        与for语句(§1.7)类似，if语句也可以引入一个变量并对其进行测试。例如:
        	void do_something(vector<int>& v)
            {
                if (auto n = v.size(); n!=0)
                {
                    // ... we get here if n!=0 ...
                }
                // ...
            }
        在这里，整数n被定义在if语句中使用，用v.size()初始化，并立即由n!=0条件后的分号。在条件中声明的名称在if-语句的两个分支上都有作用域。
        与for语句一样，在if语句的条件中声明名称的目的是限制变量的作用域，以提高可读性和最小化错误。
		最常见的情况是针对0(或nullptr)测试变量。要做到这一点，只需省略对条件的显式提及。例如:
            void do_something(vector<int>& v)
            {
                if (auto n = v.size())
                {
                    // ... we get here if n!=0 ...
                }
                // ...
            }
        如果可以的话，更喜欢使用这种简洁和简单的形式。

####1.9 硬件对应关系
		c++提供了到硬件的直接映射。当您使用一种基本操作时，实现是由硬件提供的，通常是单个机器操作。例如，两个整数相加，x+y执行一个整数相加机指令。
        c++的实现将机器的内存视为一个内存位置序列，它可以将(类型化的)对象放入其中，并使用指针寻址它们:
        指针在内存中表示为机器地址。“基本语言构造到硬件的简单映射对于原始的低级性能至关重要，而这正是C和c++几十年来闻名的地方。C和c++的基本机器模型是基于计算机硬件，而不是某种形式的数学。

#####1.9.1 赋值
		内置类型的赋值是一个简单的机器复制操作。考虑:
            int x = 2;
            int y = 3;
            x = y ; / / x becomes 3
            // Note: x==y
        注意，这两个对象是独立的。我们可以改变y的值而不影响x的值。例如，x=99不会改变y的值。与Java、c#和其他语言不同，但与C一样，这对所有类型都适用，而不仅仅是int。
        如果我们想要不同的对象引用相同(共享)的值，就必须这么说。我们可以使用指针:
            int x = 2;
            int y = 3;
            int∗ p = &x;
            int∗ q = &y; // now p!=q and *p!=*q
            p = q ; / / p becomes &y; now p==q, so (obviously)*p == *q
        也就是说，p=q得到p==q。在p=q之后，两个指针都指向y。
        引用和指针都引用/指向对象，并且都在内存中表示为机器地址。但是，使用它们的语言规则不同。对引用赋值不会改变引用的对象，而是赋值给被引用的对象:
        	int x = 2;
            int y = 3;
            int& r = x; // r refers to x
            int& r2 = y; // now r2 refers to y
            r = r2; // read through r2, write through r: x becomes 3
        要访问指针指向的值，可以使用∗;这将自动(隐式)为引用执行。
		在x=y之后，对于每一种内置类型和设计良好的用户定义类型(第2章)，我们都有 x==y，它提供了=(赋值)和==(相等比较)。

#####1.9.2 初始化
		初始化不同于赋值。一般来说，要使赋值正确工作，赋值对象必须有一个值。另一方面，初始化的任务是将未初始化的内存块变成有效的对象。对于几乎所有类型，读写未初始化变量的效果都是未定义的。对于内置类型，这在引用中最明显:
            int x = 7;
            int& r {x}; // bind r to x (r refers to x)
            r = 7 ; / / assign to whatever r refers to
            int& r2; // error : uninitialized reference
            r2 = 99; // assign to whatever r2 refers to
        幸运的是，我们不能有未初始化的引用;如果可以，那么r2=99将把99分配给某个未指定的内存位置;这样的结果最终会导致糟糕的结果或崩溃。
		你可以使用=来初始化引用，但请不要让它迷惑你。例如:
        	int& r = x; // bind r to x (r refers to x)
        这仍然是初始化，并将r绑定到x，而不是任何形式的值复制。
		初始化和赋值之间的区别对于许多用户定义的类型也至关重要，例如string和vector，赋值对象拥有最终需要释放的资源(§5.3)。
		参数传递和函数值返回的基本语义是初始化(§3.6)。例如，这就是我们如何获得引用传递。

####1.10 建议
		这里的建议是c++核心指南的一个子集[Stroustrup,2015]。参考指南是这样的[CG: ES.23]，意思是表达式和陈述部分的第23条规则。
	一般来说，核心指南提供了进一步的原理和示例。
        [1]不要恐慌!假以时日，一切都会变得清晰;§1.1;[CG: In.0]。
        [2]不要单独或单独使用内置功能。相反，基本的(内置的)特性通常最好通过库来间接使用，比如ISO c++标准库(第8-15章);[CG: P .10]。
        [3]你不必知道c++的每一个细节才能写出好的程序。
        [4]关注编程技术，而不是语言特性。
        [5]关于语言定义问题的最终答案，请参阅ISO c++标准;§16.1.3;(CG: P。2)。
        [6]“打包”有意义的操作作为精心命名的函数;§1.3;[CG: F.1]。
        [7]函数应该执行单个逻辑操作;§1.3 [CG: F.2]。
        [8]保持函数简短;§1.3;[CG: F.3]。
        [9]当函数在不同类型上执行概念上相同的任务时，使用重载;§1.3。
        [10]如果一个函数需要在编译时求值，请将它声明为constexpr;§1.6;(CG:无)。
        [11]理解语言原语如何映射到硬件;§1.4、§1.7、§1.9、§2.3、§4.2.2、§4.4。
        [12]使用数字分隔符使大的文字可读;§1.4;[CG: NL.11]。
        [13]避免复杂表达式;[CG: ES.40]。
        [14]避免收缩转换;§1.4.2;[CG: ES.46]。
        [15]最小化变量的作用域;§1.5。
        [16]避免“魔法常量”;使用符号常量;§1.6;[CG: ES.45]。
        [17]首选不可变数据;§1.6;[CG: P .10]。
        [18]每个声明只声明一个名称;[CG: ES.10]。
        [19]保持普通名称和本地名称较短，保持不常用名称和非本地名称较长;[CG: ES.7]。
        [20]避免相似的名字;[CG: ES.8]。
        [21]避免ALL_CAPS名称;[CG: ES.9]。
        [22]使用命名类型声明的{}初始化器语法;§1.4;[CG: ES.23]。
        [23]使用auto来避免重复类型名;§1.4.2;[CG: ES.11]。
        [24]避免未初始化的变量;§1.4;[CG: ES.20]。
        [25]保持范围小;§1.5;[CG: ES.5]。
        [26]在if语句的条件中声明变量时，首选对0进行隐式测试的版本;§1.8。
        [27]仅对位操作使用unsigned;§1.4;[cg: .101] [cg: .106]
        [28]保持指针的使用简单明了;§1.7;[CG: ES.42]。
        [29]使用nullptr而不是0或NULL;§1.7;[CG: ES.47]。
        [30]在你有初始化变量的值之前不要声明变量;§1.7,§1.8;[CG: ES.21]。
        [31]不要在注释中说代码中可以清楚表述的内容;[CG: NL.1]。
        [32]注释中的状态意图;[CG: NL.2]。
        [33]保持一致的缩进风格;[CG: NL.4]。
___
###2 用户定义类型
	Don’t Panic!	– Douglas Adams
    • 介绍
    • 结构体
    • 类
    • 联合体
    • 枚举
    • 建议

####2.1 介绍
	我们将可由基本类型(§1.4)、const修饰符(§1.6)和声明符操作符(§1.7)构建的类型称为内置类型。c++的内置类型和操作集很丰富，但故意放在底层。它们直接而有效地反映了传统计算机硬件的能力。但是，它们没有为程序员提供高级的工具来方便地编写高级应用程序。相反，c++通过一组复杂的抽象机制来扩展内置的类型和操作，程序员可以利用这些抽象机制来构建这样的高级工具。
		c++抽象机制主要是为了让程序员设计和实现他们自己的类型，使用合适的表示和操作，并让程序员简单而优雅地使用这些类型。使用c++的抽象机制从其他类型构建的类型称为用户定义类型。它们被称为类和枚举。用户定义的类型可以基于内置类型和其他用户定义的类型构建。本书主要介绍用户定义类型的设计、实现和使用。用户定义类型通常比内置类型更受欢迎，因为它们更容易使用、更不容易出错，而且通常与直接使用内置类型相比效率更高，甚至更快。
        本章的其余部分将介绍定义和使用类型的最简单和最基本的工具。第4-7章更完整地描述了抽象机制及其支持的编程风格。第8-15章介绍了标准库的概况，由于标准库主要由用户定义的类型组成，它们提供了可以使用第1-7章中介绍的语言工具和编程技术构建的示例。

####2.2 结构体
	构建新类型的第一步通常是将它需要的元素组织成一个数据结构，即结构:
    	struct Vector {
        int sz; // number of elements
        double∗ elem; // pointer to elements
        };
    这个Vector的第一个版本由一个int和一个double∗组成。
    	Vector类型的变量可以这样定义:
        	Vector v;
    然而，它本身并没有多大用处，因为v的elem指针并没有指向任何东西。为了使它有用，我们必须给v一些指向的元素。例如，我们可以像这样构造一个Vector:
    	void vector_init(Vector& v, int s)
        {
            v.elem = new double[s]; // allocate an array of s doubles
            v.sz = s;
        }
    也就是说，v的elem成员获得一个由new操作符产生的指针，而v的sz成员获得元素的数量。Vector&中的&表示通过非const引用传递v(§1.7);这样，vector_init()就可以修改传递给它的向量。
		new操作符从一个称为自由存储(也称为动态内存和堆)的区域分配内存。在自由存储区中分配的对象是独立于创建它们的作用域的，并且在使用delete操作符销毁它们之前是“活动”的(§4.2.2)。
        double read_and_sum(int s)
        // read s integers from cin and return their sum; s is assumed to be positive
        {
            Vector v;
            vector_init(v,s); // allocate s elements for v
            for (int i=0; i!=s; ++i)
            	cin>>v.elem[i]; // read into elements
            double sum = 0;
            for (int i=0; i!=s; ++i)
            	sum+=v.elem[i]; // compute the sum of the elements
            return sum;
        }
    在我们的Vector变得像标准库Vector一样优雅和灵活之前，还有很长的路要走。
	特别是，Vector的用户必须知道Vector表示的每个细节。本章的其余部分以及接下来的两章将逐步改进Vector作为语言特性和技术的示例。第11章介绍了标准库vector，它包含许多不错的改进。
    	我使用vector和其他标准库组件作为示例
        • 来说明语言特性和设计技术，并且
        • 帮助您学习和使用标准库组件。
    不要重新创建标准库组件，比如vector和string;使用它们。
	我们使用.(dot)通过名称(和引用)访问struct成员，而−>通过指针访问struct成员。例如
    	void f(Vector v, Vector& rv, Vector∗ pv)
        {
            int i1 = v.sz; // access through name
            int i2 = rv.sz; // access through reference
            int i3 = pv−>sz; // access through pointer
        }

####2.3 类
	将数据与对其进行的操作分开指定具有一些好处，比如可以以任意方式使用数据。但是，用户定义的类型需要在表示和操作之间建立更紧密的连接，以拥有“真实类型”所需的所有属性。“特别地，我们经常希望保持用户无法访问的表示，以方便使用，保证数据的一致使用，并允许我们以后改进表示。要做到这一点，我们必须区分类型的接口(供所有人使用)和它的实现(可以访问无法访问的数据)。这种语言机制称为类。类有一组成员，可以是数据成员、函数成员或类型成员。接口由类的public成员定义，而private成员只能通过该接口访问。
	例如:
    	class Vector {
        public:
            Vector(int s) :elem{new double[s]}, sz{s} { } // constr uct a Vector
            double& operator[](int i) { return elem[i]; } // element access: subscripting
            int size() { return sz; }
        private:
            double∗ elem; // pointer to the elements
            int sz; // the number of elements
        };
    因此，我们可以定义一个新类型Vector的变量:
    	Vector v(6); // a Vector with 6 elements
	基本上，Vector对象是一个“句柄”，包含指向元素(elem)和元素数量(sz)的指针。Vector对象和Vector对象的元素数量(例子中是6)是不同的，一个Vector对象在不同的时间可以有不同数量的元素(§4.2.3)。然而，Vector对象本身总是相同的大小。这是在c++中处理不同数量信息的基本技术:一个固定大小的句柄，引用“别处”的可变数量的数据(例如，在new;§4.2.2)。如何设计和使用这些对象是第四章的主要主题。
    	这里，Vector(成员elem和sz)的表示只能通过公共成员提供的接口访问:Vector()、operator[]()和siz e()。§2.2中的read_and_sum()例子简化为:
        	double read_and_sum(int s)
            {
                Vector v(s); // make a vector of s elements
                for (int i=0; i!=v.siz e(); ++i)
                	cin>>v[i]; // read into elements
                double sum = 0;
                for (int i=0; i!=v.siz e(); ++i)
                	sum+=v[i]; // take the sum of the elements
                return sum;
            }
    与类同名的成员“函数”称为构造函数，即用于构造类对象的函数。因此，构造函数Vector()替换了§2.2中的vector_init()。
	与普通函数不同，构造函数保证用于初始化其类的对象。
	因此，定义构造函数消除了类未初始化变量的问题。
    	Vector(int)定义了Vector类型对象的构造方式。特别地，它说它需要一个整数来完成这一点。该整数用作元素的个数。构造函数使用成员初始化列表初始化Vector成员:
    		:elem{new double[s]}, sz{s}
    也就是说，首先用指向从自由存储区获得的s个double类型元素的指针初始化elem。然后，我们将sz初始化为s。
    	对元素的访问由一个下标函数operator[]提供。它返回对适当元素的引用(double&允许读取和写入)。
        提供size()函数是为了给用户提供元素的数量。
		显然，错误处理是完全没有的，但我们将在§3.5中回到这一点。类似地，我们没有提供一种机制来“返回”new获取的双精度数组;§4.2.2展示了如何使用析构函数来优雅地实现这一点。
		结构和类之间没有根本的区别;struct只是一个默认成员为public的类。例如，可以为结构定义构造函数和其他成员函数。

####2.4 联合体
	联合是一种结构体，其中所有成员都分配在相同的地址，以便联合只占用与其最大成员相同的空间。当然，联合一次只能保存一个成员的值。例如，考虑一个包含名称和值的符号表条目。它的值可以是Node *或int:
		enum Type { ptr, num }; // a T ype can hold values ptr and num (§2.5)
        struct Entry {
            string name; // str ing is a standard-librar y type
            Type t;
            Node∗ p; // use p if t==ptr
            int i; // use i if t==num
        };
        void f(Entry∗ pe)
        {
            if (pe−>t == num)
            	cout << pe−>i;
            // ...
        }
    成员p和i永远不会同时使用，因此浪费了空间。通过指定两者都应该是一个联盟的成员，可以很容易地恢复它，像这样:
    	union Value {
            Node∗ p;
            int i;
        };
    语言不会跟踪union所保存的值的类型，因此程序员必须这样做:
    	struct Entry {
            string name;
            Type t;
            Value v; // use v.p if t==ptr; use v.i if t==num
        };
        void f(Entry∗ pe)
        {
            if (pe−>t == num)
                cout << pe−>v.i;
            // ...
        }
    维护类型字段(这里是t)与联合中保存的类型之间的对应关系容易出错。为了避免错误，我们可以通过将联合和type字段封装在类中并仅通过正确使用联合的成员函数提供访问来强制这种通信。
	在应用程序级别，依赖于这种带标记的联合的抽象是常见且有用的。“直率的”联合体的使用最好尽量减少。
    	标准库类型 variant 可用于消除对联合的最直接使用。 variant 存储一组可选类型之一的值(§13.5.1)。例如， variant<Node∗,int>可以包含Node∗或int。
        使用 variant，Entry的例子可以写成:
        struct Entry {
        	string name;
        	variant<Node∗,int> v;
        };
        void f(Entry∗ pe)
        {
        	if (holds_alternative<int>(pe−>v)) // does *pe hold an int? (see §13.5.1)
        		cout << get<int>(pe−>v); // get the int
        	// ...
        }
    在许多情况下，variant 比 union 更简单、更安全。
####2.5 枚举
	除了类之外，c++还支持一种简单的用户定义类型，我们可以枚举其值:
    	enum class Color { red, blue , green };
        enum class Traffic_light { green, yellow, red };
        Color col = Color::red;
        Traffic_light light = Traffic_light::red;
	请注意，枚举器(例如，red)在它们的枚举类的作用域内，因此它们可以在不同的枚举类中重复使用，而不会造成混淆。例如，Color::red是Color的红色，与Traffic_light::red不同。
    	枚举用于表示整数值的小集合。与不使用符号(和助记)枚举器名称相比，它们使代码更具可读性，更不容易出错。
        枚举后的类指定枚举是强类型的，并且其枚举数是作用域的。作为独立的类型，enum类有助于防止意外误用常量。特别地，我们不能混合Traffic_light和Color的值:
        	Color x = red; // error : which red?
            Color y = Traffic_light::red; // error : that red is not a Color
            Color z = Color::red; // OK
    类似地，我们不能隐式地混合Color和整型值:
        int i = Color::red; // error : Color ::red is not an int
		Color c = 2; // initialization error: 2 is not a Color
    捕获对enum的尝试转换是一种很好的防御错误的方法，但通常我们希望用其底层类型的值初始化enum(默认为int)，所以这是允许的，从底层类型的显式转换也是允许的:
		Color x = Color{5}; // OK, but verbose
        Color y {6}; // also OK
    默认情况下，enum类只有赋值、初始化和比较(例如==和<;§1.4)定义的。但是，枚举是用户定义的类型，因此可以为其定义操作符:
    	Traffic_light& operator++(Traffic_light& t) // prefix increment: ++
        {
            switch (t)
            {
                case Traffic_light::green: 		return t=Traffic_light::yellow;
                case Traffic_light::yellow: 	   return t=Traffic_light::red;
                case Traffic_light::red: 		  return t=Traffic_light::green;
            }
        }
        Traffic_light next = ++light; // next becomes T raffic_light::green
    如果您不想显式限定枚举器名称，并希望枚举器值为整数(不需要显式转换)，您可以从enum类中移除类以获得一个“普通”enum。来自“普通”enum的枚举器与它们的enum名称进入相同的作用域，并隐式转换为它们的整数值。例如:
    	enum Color { red, green, blue };
    	int col = green;
    这里，col的值为1。默认情况下，枚举数的整数值从0开始，每增加一个枚举数就加1。“普通”枚举从最早的时候就出现在c++(和C)中了，所以尽管它们的表现不太好，但它们在当前代码中很常见。

####2.6 建议
	[1]当内置类型太低时，首选定义良好的用户定义类型而不是内置类型;§2.1。
    [2]将相关数据组织成结构(结构或类);§2.2;[CG: C.1]。
    [3]表示接口和使用类的实现之间的区别;§2.3;[CG: C.3]。
    [4]struct只是一个默认成员为public的类;§2.3。
    [5]定义构造函数来保证和简化类的初始化;§2.3;[CG: C.2]。
    [6]避免“直接”联合体;用类型字段将它们封装在一个类中;§2.4;[CG: C.181]。
    [7]使用枚举来表示命名常量集;§2.5;[CG: Enum.2]。
    [8]首选类枚举而不是“普通”枚举，以减少意外;§2.5;[CG: Enum.3]。
    [9]为枚举定义操作，安全且简单;§2.5;[CG: Enum.4]。
___
###3 模块化
	Don’t interrupt me while I’m interrupting.	– Winston S. Churchill
    • 简介
    • 单独编译
    • 模块
    • 命名空间
    • 错误处理
        异常;不变量;错误处理方案;合同;静态断言
    • 函数参数和返回值
        参数传递;返回值;结构化绑定
    • 建议

####3.1 介绍
	c++程序由许多独立开发的部分组成，例如函数(§1.2.1)、用户定义的类型(第2章)、类层次结构(第4.5章)和模板(第6章)。管理这些部分的关键是清楚地定义这些部分之间的交互。第一步也是最重要的一步是区分部件的接口及其实现。在语言层面，c++通过声明来表示接口。声明指定了使用函数或类型所需的所有内容。例如:
        double sqrt(double); // the square root function takes a double and returns a double
        class Vector {
        public:
            Vector(int s);
            double& operator[](int i);
            int size();
        private:
            double∗ elem; // elem points to an array of sz doubles
            int sz;
        };
    这里的重点是，函数体和函数定义在“在别的地方”。对于这个例子，我们可能也希望Vector的表示形式为“在别的地方”，但我们将在后面处理(抽象类型;§4.3)。sqrt()的定义如下:
        double sqrt(double d) // definition of sqrt()
        {
         	// ... algorithm as found in math textbook ...
        }
    对于Vector，我们需要定义所有三个成员函数:
        Vector::Vector(int s) // definition of the constructor
        :elem{new double[s]}, sz{s} // initialize members
        {
        }
        double& Vector::operator[](int i) // definition of subscripting
        {
        	return elem[i];
        }
        int Vector::size() // definition of size()
        {
        	return sz;
        }
    必须定义Vector函数，但不能定义sqrt()，因为它是标准库的一部分。然而，这并没有真正的区别:库只是“我们碰巧使用的一些其他代码”，用我们使用的相同的语言工具编写的。
		一个实体可以有很多声明，比如函数，但只有一个定义。

####3.2 单独的编译
	c++支持单独编译的概念，用户代码只能看到所使用的类型和函数的声明。这些类型和函数的定义位于单独的源文件中，并分别编译。这可以用来将程序组织成一组半独立的代码片段。这种分离可用于最小化编译时间，并严格执行程序中逻辑上不同的部分的分离(从而最大限度地减少错误的机会)。库通常是一个单独编译的代码片段的集合(例如，函数)。
    	通常，我们将指定模块接口的声明放在一个文件中，该文件的名称表明其预期用途。例如:
        	// Vector.h:
            class Vector {
            public:
                Vector(int s);
                double& operator[](int i);
                int size();
            private:
                double∗ elem; // elem points to an array of sz doubles
                int sz;
            };
	这个声明将放在Vector.h文件中。然后用户包含该文件，称为头文件，以访问该接口。例如:
    	// user.cpp:
        #include "Vector.h" // get Vector’s interface
        #include <cmath> // get the standard-librar y math function interface including sqrt()
        double sqrt_sum(Vector& v)
        {
            double sum = 0;
            for (int i=0; i!=v.siz e(); ++i)
                sum+=std::sqr t(v[i]); // sum of square roots
            return sum;
        }
	为了帮助编译器确保一致性，提供Vector实现的.cpp文件还将包含提供其接口的.h文件:
    	// Vector.cpp:
        #include "Vector.h" // get Vector’s interface
        Vector::Vector(int s)
        :elem{new double[s]}, sz{s} // initialize members
        {
        }
        double& Vector::operator[](int i)
        {
        	return elem[i];
        }
        int Vector::siz e()
        {
        	return sz;
        }
	user.cpp和Vector.cpp中的代码共享Vector.h中提供的Vector接口信息，但是这两个文件在其他方面是独立的，可以单独编译。
    严格地说，使用单独编译不是一个语言问题;问题在于如何最好地利用特定的语言实现。然而，它具有重要的现实意义。组织程序的最佳方法是将程序视为一组具有良好定义的依赖关系的模块，通过语言特性在逻辑上表示该模块性，然后通过文件在物理上利用该模块性进行有效的单独编译。
		一个由自己编译的.cpp文件(包括它#包含的h文件)被称为翻译单元。一个程序可以由数千个翻译单元组成。

####3.3 模块(C++20)
	#include的使用是一种非常古老的、容易出错的、而且相当昂贵的用部分组合程序的方式。如果你在101个翻译单元中使用#include header.h，那么header.h的文本将被编译器处理101次。如果在header2.h之前包含header1.h, header1.h中的声明和宏可能会影响header2.h中的代码的含义。如果你改为#include header2.h在header1.h之前，这可能会影响header1.h中的代码。显然，这并不理想，事实上，自1972年该机制首次引入C以来，它一直是成本和bug的主要来源。
    	我们终于可以用c++更好地表达物理模块了。这个语言特性，称为模块，还不是ISO c++，但它是ISO技术规范[ModulesTS]，并将成为c++ 20的一部分。实现正在使用中，所以我冒险在这里推荐它，尽管细节可能会发生变化，而且在生产代码中使用它可能需要数年时间。
	旧代码(在本例中使用#include的代码)可以“存活”很长一段时间，因为更新它的成本很高，耗时也很长。
    	考虑如何使用模块来表达§3.2中的Vector和sqr t_sum()示例:
			// file Vector.cpp:
            module; // this compilation will define a module
            // ... here we put stuff that Vector might need for its implementation ...
            export module Vector; // defining the module called "Vector"
            export class Vector {
            public:
                Vector(int s);
                double& operator[](int i);
                int size();
            private:
                double∗ elem; // elem points to an array of sz doubles
                int sz;
            };
            Vector::Vector(int s)
            :elem{new double[s]}, sz{s} // initialize members
            {
            }
            double& Vector::operator[](int i)
            {
            	return elem[i];
            }
            int Vector::size()
            {
            	return sz;
            }
            export int size(const Vector& v) { return v.size(); }
    这定义了一个名为Vector的模块，该模块导出Vector类、其所有成员函数和非成员函数size()。
    	我们使用这个模块的方式是在我们需要它的地方导入它。例如:
        	// file user.cpp:
            import Vector; // get Vector’s interface
            #include <cmath> // get the standard-librar y math function interface including sqrt()
            double sqrt_sum(Vector& v)
            {
                double sum = 0;
                for (int i=0; i!=v.siz e(); ++i)
                    sum+=std::sqr t(v[i]); // sum of square roots
                return sum;
            }
	我也可以导入标准库的数学函数，但我使用老式的#include只是为了说明可以混合使用新旧函数。这种混合对于逐步将旧代码从使用#include升级为import是必不可少的。
        头文件和模块之间的区别不仅仅是语法上的。
        • 一个模块只编译一次(而不是在使用它的每个翻译单元中)。
        • 两个模块可以在不改变其含义的情况下以任意顺序导入。
        • 如果你导入了一些东西到一个模块中，模块的用户不会隐式地获得你导入的东西的访问权(也不会被打扰):importort是不可传递的。
        	这对可维护性和编译时性能的影响可能是惊人的。

####3.4 命名空间
	除了函数(§1.3)、类(§2.3)和枚举(§2.5)之外，c++还提供了命名空间作为一种机制，来表示某些声明属于一起，并且它们的名称不应与其他名称冲突。例如，我可能想尝试自己的复数类型(§4.2.1，§14.4):
        namespace My_code {
            class complex
            {
                // ...
            };
            complex sqrt(complex);
            // ...
            int main();
        }
        int My_code::main()
        {
            complex z {1,2};
            auto z2 = sqrt(z);
            std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
            // ...
        }
        int main()
        {
        	return My_code::main();
        }
	通过将我的代码放入命名空间My_code中，我确保我的名称不会与命名空间std中的标准库名称冲突(§3.4)。这种谨慎是明智的，因为标准库确实提供了对复杂算术的支持(§4.2.1，§14.4)。
		访问另一个名称空间中的名称最简单的方法是用名称空间名称限定它(例如，std::cout和My_code::main)。“real main()”是在全局命名空间中定义的，也就是说，不是定义的命名空间、类或函数的局部名称空间。
		如果重复限定一个名称变得乏味或分散注意力，我们可以使用using-声明将该名称引入作用域:
        void my_code(vector<int>& x, vector<int>& y)
        {
            using std::swap; // use the standard-librar y sw ap
            // ...
            swap(x,y); // std::swap()
            other::swap(x,y); // some other swap()
            // ...
        }
	using-声明使名称空间中的名称可用，就好像它是在出现的作用域中声明的一样。在使用std::swap之后，就像在my_code()中声明了swap一样。
		要获得对标准库命名空间中所有名称的访问权，可以使用using-directive:
        using namespace std;
    using-directive使得命名空间中的非限定名可以从我们放置指令的作用域中访问。所以在std的using指令之后，我们可以简单地写cout而不是std::cout。通过使用using-directive，我们就失去了选择性地使用来自该名称空间的名称的能力，因此应该谨慎地使用该功能，通常用于应用程序中普遍存在的库(例如std)，或者用于不使用名称空间的应用程序的转换期间。
    	命名空间主要用于组织更大的程序组件，比如库。他们把独立开发的部分简化成一个程序。

####3.5 错误处理
	错误处理是一个庞大而复杂的主题，它所关注的问题和影响远远超出了语言工具，延伸到了编程技术和工具。但是，c++提供了一些功能来提供帮助。主要的工具是类型系统本身。我们不必费力地从内置类型(如char、int和double)和语句(如if、while和for)构建应用程序，而是构建适合应用程序的类型(如string、map和regex)和算法(如sort()、find_if()和draw_all())。这样的高级结构简化了我们的编程，限制了我们出错的机会(例如，您不太可能尝试对对话框应用树遍历)，并增加了编译器捕捉错误的机会。大多数c++语言构造都致力于设计和实现优雅而高效的抽象(例如，使用它们的用户定义类型和算法)。这种抽象的一个影响是，可以检测到运行时错误的点与可以处理错误的点是分离的。随着程序的发展，特别是当库被广泛使用时，处理错误的标准就变得重要起来。在程序开发的早期阐明错误处理策略是一个好主意。

#####3.5.1 异常
	再次考虑Vector的例子。当我们试图访问§2.3中超出vector范围的元素时，应该怎么做?
    	• Vector的编写者不知道在这种情况下用户想要做什么(通常，Vector的编写者甚至不知道Vector将在哪个程序中运行)。
        • Vector的用户不能始终检测到问题(如果用户可以，超出范围的访问就不会发生在第一个地方)。
    假设超出范围的访问是我们想要恢复的一种错误，解决方案是由Vector实现者检测尝试的超出范围的访问，并告诉用户它。
	然后，用户可以采取适当的操作。例如，Vector::operator[]()可以检测到一个试图超出范围的访问，并抛出一个out_of_range异常:
        double& Vector::operator[](int i)
        {
            if (i<0 || size()<=i)
                throw out_of_range{"Vector::operator[]"};
            return elem[i];
        }
    throw将控制传递给某个函数中out_of_range类型异常的处理程序，该函数直接或间接调用Vector::operator[]()。为此，实现将根据需要展开函数调用堆栈，以返回调用者的上下文。也就是说，异常处理机制将根据需要退出作用域和函数，返回到表示有兴趣处理此类异常的调用者那里，并在需要的时候调用析构函数(§4.2.2)。
	例如:
        void f(Vector& v)
        {
            // ...
            try
            { / / exceptions here are handled by the handler defined below
                v[v.siz e()] = 7; // tr y to access beyond the end of v
            }
            catch (out_of_rang e& err)
            { // oops: out_of_range error
                // ... handle range error ...
                cerr << err.what() << '\n';
            }
            // ...
        }
    我们将对处理异常感兴趣的代码放入一个try块中。试图分配给v[v.size()]将失败。因此，将输入为out_of_range类型异常提供处理程序的catch子句。out_of_range类型在标准库中定义(在<stdexept>中)，实际上被一些标准库容器访问函数使用。
    	我通过引用捕获了异常，以避免复制，并使用what()函数打印抛出点处放入其中的错误消息。
    	使用异常处理机制可以使错误处理更简单、更系统、更可读。要实现这一点，不要过度使用try语句。使错误处理简单和系统的主要技术(称为资源获取是初始化;§4.2.2对此有解释。RAII背后的基本思想是，构造函数获取类操作所需的所有资源，并让析构函数释放所有资源，从而使资源释放具有保证性和隐式。
		一个不应该抛出异常的函数可以声明为noexcept。例如:
        void user(int sz) noexcept
        {
            Vector v(sz);
            iota(&v[0],&v[sz],1); // fill v with 1,2,3,4... (see §14.3)
            // ...
        }
    如果所有正常的意图和计划都失败了，因此user()仍然会抛出问题，则调用std::terminate()来立即终止程序。

#####3.5.2 不变量
	使用异常来表示超出范围的访问是一个例子，函数检查它的参数并拒绝行动，因为一个基本的假设、前提条件不成立。如果我们正式地指定Vector的下标操作符，我们就会说“索引必须在[0:size())范围内”，这实际上就是我们在操作符[]()中测试的内容。[a:b)表示法指定半开放范围，这意味着a是范围的一部分，但b不是。当我们定义一个函数时，我们必须考虑它的前提条件是什么，并考虑是否要检验这些前提条件(§3.5.3)。对于大多数应用程序来说，测试简单的不变量是个好主意;参见§3.5.4。
    	然而，operator[]()作用于Vector类型的对象，除非Vector的成员具有“合理”的值，否则没有任何意义。特别地，我们确实说过“elem指向一个sz双精度数组”，但我们只是在一个注释中说过。对于一个类来说，这样一个被假定为正确的陈述被称为类不变量，或者简单地称为不变量。构造函数的职责是为其类建立不变式(以便成员函数可以依赖于它)，成员函数的职责是确保在退出时保持不变式。不幸的是，Vector构造函数只完成了部分工作。它正确地初始化了Vector成员，但未能检查传递给它的参数是否合理。考虑:
			Vector v(−27);
    这很可能会引起混乱。
		这里有一个更合适的定义:
        Vector::Vector(int s)
        {
            if (s<0)
                throw length_error{"Vector constructor: negative size"};
            elem = new double[s];
            sz = s;
        }
    我使用标准库异常length_error来报告非正数的元素，因为一些标准库操作使用该异常来报告此类问题。如果操作符new找不到要分配的内存，它就会抛出一个std::bad_alloc。我们现在可以这样写:
            void test()
            {
                try
                {
                Vector v(−27);
            	}
                catch (std::length_error& err)
                {
                    // handle negative size
                }
                catch (std::bad_alloc& err)
                {
                    // handle memory exhaustion
                }
            }
    你可以定义自己的类作为异常使用，并让它们携带从检测到可以处理错误的任意信息(§3.5.1)。
    	通常，在抛出异常后，函数无法完成分配给它的任务。
		然后，“处理”异常意味着做一些最小的局部清理并重新抛出异常。例如:
            void test()
            {
                try
                {
                    Vector v(−27);
                }
                catch (std::length_error&)
                { // do something and rethrow
                    cerr << "test failed: length error\n";
                    throw; // rethrow
                }
                catch (std::bad_alloc&)
                { // Ouch! this program is not designed to handle memory exhaustion
                    std::terminate(); // ter minate the program
                }
            }
    在设计良好的代码中，try块很少出现。通过系统地使用RAII技术避免过度使用(§4.2.2，§5.3)。
    	不变量的概念是类设计的核心，前提条件在函数设计中也扮演着类似的角色。不变量
        • 帮助我们准确地理解我们想要什么
		• 迫使我们具体化;这为我们(在调试和测试之后)获得正确代码提供了更好的机会。
    不变量的概念是c++资源管理概念的基础，构造函数(第4章)和析构函数(§4.2.2和§13.2)都支持这种概念。

#####3.5.3 错误处理选项
	错误处理是所有现实软件中的一个主要问题，因此自然有各种各样的方法。如果检测到错误，并且无法在函数中本地处理它，那么函数必须以某种方式将问题传达给某些调用者。抛出异常是c++最常用的处理机制。
    	在某些语言中，异常的设计只是为了提供返回值的替代机制。c++不是这样一种语言:异常被设计用来报告未能完成给定任务。异常与构造函数和析构函数集成，为错误处理和资源管理提供了一个一致的框架(§4.2.2，§5.3)。编译器经过优化，返回一个值比抛出相同的值作为异常要便宜得多。
		抛出异常并不是报告无法在本地处理的错误的唯一方法。
	函数可以通过以下方式表示它不能执行分配的任务:
    	• 抛出异常
        • 以某种方式返回指示失败的值
        • 终止程序(通过调用terminate()、exit()或abor t()等函数)。
    我们返回一个错误指示器(一个“错误代码”)：
    	• 失败是正常的，也是意料之中的。例如，打开一个文件的请求失败是很正常的(可能没有该名称的文件，或者可能文件无法以所请求的权限打开)。
		• 可以合理地期望立即调用者来处理故障。
    我们抛出一个异常：
        • 一个错误是如此罕见，以至于程序员可能会忘记检查它。例如，上次检查printf()的返回值是什么时候?
        • 一个错误不能被直接调用者处理。相反，错误必须渗透回最终调用者。例如，让应用程序中的每个功能都可靠地处理每次分配失败或网络中断是不可行的。
        • 新的错误类型可以添加到应用程序的低级别模块中，这样就不会编写高级模块来处理此类错误。例如，当将以前的单线程应用程序修改为使用多个线程或将资源远程放置以便通过网络访问时。
        • 错误码没有合适的返回路径。例如，构造函数没有返回值供“调用者”检查。特别是，可能会为多个局部变量或部分构造的复杂对象调用构造函数，因此基于错误代码的清理将会非常复杂。
        • 函数的返回路径变得更加复杂或昂贵，因为它需要返回一个值和一个错误指示器(例如，一对;§13.4.3)，可能导致使用外部参数、非本地错误状态指示器或其他变通方法。
        • 错误必须通过调用链向上传输到“最终调用方”。“反复检查错误代码将是乏味、昂贵且容易出错的。
        • 从错误中恢复依赖于多个函数调用的结果，导致需要在调用和复杂的控制结构之间维护局部状态。
        • 发现错误的函数是回调函数(函数参数)，因此直接调用者甚至可能不知道被调用的是什么函数。
        • 一个错误意味着需要一些“撤消操作”。
    我们终止
    	• 错误是一种我们无法挽回的错误。例如，对于许多(但不是所有)系统，没有合理的方法从内存耗尽中恢复。
        • 该系统的错误处理是基于每当检测到重大错误时重新启动线程、进程或计算机。
    确保终止的一种方法是向函数中添加noexcept，这样函数实现中任何地方的throw都将变成terminate()。请注意，有些应用程序不能接受无条件终止，因此必须使用替代方案。
    	不幸的是，这些条件在逻辑上并不总是不相关的，并且很容易应用。程序的大小和复杂性很重要。有时，随着应用程序的发展，权衡也会发生变化。
    经验是必需的。当有疑问时，首选异常，因为它们的使用伸缩性更好，并且不需要外部工具来检查所有错误是否得到处理。
    	不要认为所有的错误代码或异常都是坏的;两者都有明确的用途。此外，不要相信异常处理是缓慢的神话;这通常比正确处理复杂或罕见的错误条件和重复测试错误代码要快。
		RAII(§4.2.2，§5.3)对于使用异常进行简单而有效的错误处理至关重要。充斥着try块的代码通常只是反映了为错误代码设计的错误处理策略的最糟糕的方面。

#####3.5.4 约定
	目前还没有通用和标准的方法来编写不变量、前提条件等的可选运行时测试。为c++ 20 [Garcia,2016] [Garcia,2018]提出了一个契约机制。其目的是支持那些希望依靠测试来获得正确程序的用户——使用大量的运行时检查来运行程序——但随后使用最少的检查来部署代码。这在依赖于系统和广泛检查的组织中的高性能应用程序中很流行。
    	就目前而言，我们必须依靠专门的机制。例如，我们可以使用命令行宏来控制运行时检查:
		double& Vector::operator[](int i)
        {
            if (RANGE_CHECK && (i<0 || size()<=i))
                throw out_of_rang e{"Vector::operator[]"};
            return elem[i];
        }
    标准库提供了调试宏assert()来断言一个条件必须在运行时保持。例如:
    	void f(const char∗ p)
        {
            asser t(p!=nullptr); // p must not be the nullptr
            // ...
        }
    如果assert()的条件在“调试模式”中失败，程序将终止。如果我们没有处于调试模式，则不会检查assert()。这是相当粗糙和不灵活的，但通常足够了。

#####3.5.5 静态断言
	异常报告运行时发现的错误。如果可以在编译时找到错误，那么最好这样做。这就是大部分类型系统和为用户定义类型指定接口的工具的用途。但是，我们也可以对大部分属性执行简单的检查，这些属性在编译时已知，并报告不符合我们预期的编译器错误消息。例如:
    	static_assert(4<=sizeof(int), "integers are too small"); // check integer size
    如果4<=sizeof(int)不成立，将写入整数太小;也就是说，如果这个系统上的int没有至少4个字节。我们称这样的期望声明为断言。
		static_assert机制可以用于任何可以用常量表达式表示的东西(§1.6)。例如:
        constexpr double C = 299792.458; // km/s
        void f(double speed)
        {
            constexpr double local_max = 160.0/(60∗60); // 160 km/h == 160.0/(60*60) km/s
            static_assert(speed<C,"can't go that fast"); // error : speed must be a constant
            static_assert(local_max<C,"can't go that fast"); // OK
            // ...
        }
    通常，如果A不为真，static_assert(A,S)会打印S作为编译器错误消息。如果你不想打印一个特定的消息，省略S，编译器将提供一个默认消息:
    	static_asser t(4<=sizeof(int)); // use default message
    默认消息通常是static_assert的源位置加上断言谓词的字符表示。
    	当我们在泛型编程中断言作为参数使用的类型时，static_asser最重要的用途就出现了(§7.2，§13.9)。

####3.6 函数参数和返回值
	将信息从程序的一个部分传递到另一个部分的主要方法是通过函数调用。执行任务所需的信息作为参数传递给函数，产生的结果作为返回值传递回来。例如:
    	int sum(const vector<int>& v)
        {
            int s = 0;
            for (const int i : v)
            	s + = i ;
            return s;
        }
        vector fib = {1,2,3,5,8,13,21};
        int x = sum(fib); // x becomes 53
	函数之间还可以通过其他途径传递信息，比如全局变量(§1.5)、指针和引用形参(§3.6.1)以及类对象中的共享状态(第4章)。强烈反对将全局变量作为已知的错误来源，状态通常只应该在共同实现定义良好的抽象的函数之间共享(例如，类的成员函数;§2.3)。
    	考虑到在函数之间传递信息的重要性，有各种不同的方式来传递信息也就不足为奇了。关键担心的是:
        • 对象是复制的还是共享的?
        • 如果一个对象是共享的，它是可变的吗?
        • 一个对象移动了，留下了一个“空对象”(§5.2.2)?
    参数传递和返回值的默认行为都是“copy”(§1.9)，但有些copy可以隐式地优化为move。
    	在sum()的例子中，得到的int是从sum()中复制出来的，但将可能非常大的向量复制到sum()中效率低下且毫无意义，因此参数通过引用传递(由&;§1.7)。
        sum()没有理由修改它的参数。这种不可变性通过声明vector实参const(§1.6)来表示，因此vector对象通过const引用传递。

#####3.6.1参数传递
	首先考虑如何将值输入函数。默认情况下，复制(“按值传递”)，如果要引用调用者环境中的对象，则使用引用(“按值传递”)。
	例如:
        void test(vector<int> v, vector<int>& rv) // v is passed by value; rv is passed by reference
        {
            v[1] = 99; // modify v (a local var iable)
            rv[2] = 66; // modify whatever rv refers to
        }
        int main()
        {
            vector fib = {1,2,3,5,8,13,21};
            test(fib,fib);
            cout << fib[1] << ' ' << fib[2] << '\n'; // prints 2 66
        }
    当我们关心性能时，我们通常是按值传递小值，按引用传递大值。在这里，“small”指的是“很容易复制的东西”。“小”的确切含义取决于机器架构，但“两三个指针或更少的大小”是一个很好的经验法则。
    	如果出于性能考虑，需要按引用传递参数，但又不需要修改参数，则可以像sum()示例中那样按const-reference传递参数。到目前为止，这是普通优秀代码中最常见的情况:它快速且不容易出错。
        函数实参有一个默认值是很常见的;也就是说，该值被认为是首选值或最常见的值。可以通过默认函数实参指定这样的默认值。例如:
        void print(int value , int base =10); // print value in base "base"
        print(x,16); // hexadecimal
        print(x,60); // sexagesimal (Sumerian)
        print(x); // use the dafault: decimal
    这是一种符号上更简单的重载替代方法:
    	void print(int value , int base); // print value in base "base"
        void print(int value) // print value in base 10
        {
        	print(value ,10);
        }

#####3.6.2 返回值
	一旦我们计算出一个结果，我们需要将它从函数中取出并返回给调用者。同样，返回值的默认值是复制，对于小对象来说这是理想的。只有当我们想要授予调用者访问非函数本地内容的权限时，才返回“通过引用”。例如:
        class Vector {
        public:
            // ...
            double& operator[](int i) { return elem[i]; } // retur n reference to ith element
        private:
            double∗ elem; // elem points to an array of sz
            // ...
        };
    Vector对象的第i个元素独立于下标操作符的调用而存在，因此可以返回对它的引用。
    	另一方面，局部变量在函数返回时消失，所以我们不应该返回指向它的指针或引用:
        int& bad()
        {
            int x;
            // ...
            return x; // bad: return a reference to the local var iable x
        }
    幸运的是，所有主要的c++编译器都会捕捉bad()中的明显错误。
    	返回引用或“小”类型的值是有效的，但是我们如何从函数中传递大量的信息呢?考虑:
        Matrix operator+(const Matrix& x, const Matrix& y)
        {
            Matrix res;
            // ... for all res[i,j], res[i,j] = x[i,j]+y[i,j] ...
            return res;
        }
        Matrix m1, m2;
        // ...
        Matrix m3 = m1+m2; // no copy
    即使在现代硬件上，矩阵也可能非常大，而且复制成本很高。所以我们不复制，而是给Matrix一个转移构造函数(§5.2.2)，并很容易地将Matrix从操作符+()中移出。不需要退回到使用手动内存管理:
    	Matrix∗ add(const Matrix& x, const Matrix& y) // complicated and error-prone 20th century style
        {
            Matrix∗ p = new Matrix;
            // ... for all *p[i,j], *p[i,j] = x[i,j]+y[i,j] ...
            return p;
        }
        Matrix m1, m2;
        // ...
        Matrix∗ m3 = add(m1,m2); // just copy a pointer
        // ...
        delete m3; // easily forgotten
    不幸的是，通过返回指向大对象的指针返回大对象在旧代码中很常见，这也是很难找到错误的主要来源。不要编写这样的代码。注意，operator+()与add()一样有效，但是更容易定义、更容易使用、更不容易出错。
    	如果一个函数不能执行它所要求的任务，它可以抛出异常(§3.5.1)。这可以帮助避免代码被“异常问题”的错误代码测试弄得一团糟。
        函数的返回类型可以从它的返回值推断出来。例如:
        auto mul(int i, double d) { return i∗d; } // here, "auto" means "deduce the return type"
    这很方便，特别是对于泛型函数(函数模板;(§6.3.1)和lambdas(§6.3.3)，但是应该谨慎使用，因为推导的类型不能提供稳定的接口:对函数(或lambda)实现的更改可能会改变类型。

#####3.6.3 结构化绑定
	函数只能返回一个值，但这个值可以是一个具有多个成员的类对象。
	这允许我们高效地返回许多值。例如:
        struct Entry {
            string name;
            int value;
        };
        Entry read_entry(istream& is) // naive read function (for a better version, see §10.5)
        {
            string s;
            int i;
            is >> s >> i;
            return {s,i};
        }
        auto e = read_entry(cin);
		cout << "{ " << e.name << " , " << e.value << " }\n";
    这里，{s,i}被用来构造entry y的返回值。类似地，我们可以将entry y的成员“解包”到局部变量中:
        auto [n,v] = read_entry(is);
        cout << "{ " << n << " , " << v << " }\n";
    auto [n,v]声明了两个局部变量n和v，它们的类型从read_entry y()的返回类型推导而来。这种为类对象的成员指定局部名称的机制称为结构化绑定。
    	考虑另一个例子:
        	map<string,int> m;
            // ... fill m ...
            for (const auto [key,value] : m)
            	cout << "{" << key "," << value << "}\n";
    和往常一样，我们可以用const和&来装饰auto。例如:
        void incr(map<string,int>& m) // increment the value of each element of m
        {
            for (auto& [key,value] : m)
            	++value;
        }
    当对没有私有数据的类使用结构化绑定时，很容易看到绑定是如何完成的:为绑定定义的名称数量必须与类的非静态数据成员的数量相同，绑定中引入的每个名称都是对应的成员。
	与显式使用复合对象相比，目标代码的质量不会有任何区别;结构化绑定的使用完全是关于如何最好地表达一个想法。
    	还可以处理通过成员函数访问的类。例如:
        complex<double> z = {1,2};
		auto [re,im] = z+2; // re=3; im=2
    complex函数有两个数据成员，但是它的接口由访问函数组成，比如real()和imag()。将复杂的映射到两个局部变量(如re和im)是可行且有效的，但是这样做的技术超出了本书的范围。

####3.7 建议
    [1] 区分声明(用作接口)和定义(用作实现);§3.1。
    [2] 使用头文件表示接口，强调逻辑结构;§3.2;[CG: SF.3]。
    [3] 在源文件中包含实现其函数的头文件;§3.2;[CG: SF.5]。
    [4] 避免在头文件中定义非内联函数;§3.2;[CG: SF.2]。
    [5] 优先选择模块而不是头文件(支持模块);§3.3。
    [6] 使用名称空间表达逻辑结构;§3.4;[CG: SF.20]。
    [7] 在转换、基础库(如std)或局部作用域内使用using-directive;§3.4;[cg: sf.6] [cg: sf.7]
    [8] 不要在头文件中放入using-directive;§3.4;[CG: SF.7]。
    [9] 抛出异常，表示无法执行分配的任务;§3.5;[CG: E.2]。
    [10] 仅将异常用于错误处理;§3.5.3;[CG: E.3]。
    [11] 当期望立即调用者处理错误时使用错误代码;§3.5.3。
    [12] 如果预期错误将通过多个函数调用向上渗透，则抛出异常;§3.5.3。
    [13] 如果不确定是使用异常还是错误代码，首选exceptions;§3.5.3。
    [14] 在设计早期制定错误处理策略;§3.5;[CG: E.12]。
    [15] 使用专门设计的用户定义类型作为异常(不是内置类型);§3.5.1。
    [16] 不要试图捕捉每个函数中的每个异常;§3.5;[CG: E.7]。
    [17] 宁愿选择RAII而不是显式的try -blocks;§3.5.1,§3.5.2;[CG: E.6]。
    [18] 如果你的函数不抛出，声明它noexcept;§3.5;[CG: E.12]。
    [19] 让构造函数建立一个不变式，如果不能，则抛出;§3.5.2;[CG: E.5]。
    [20] 围绕不变量设计错误处理策略;§3.5.2;[CG: E.4]。
    [21] 在编译时可以检查的通常最好在编译时检查;§3.5.5 [cg: p .4] [cg: p .5]
    [22] 通过值传递“小”值，通过引用传递“大”值;§3.6.1;[CG: F.16]。
    [23] 优先选择通过const-reference传递而不是普通的通过引用传递;§3.6.1;[CG: F.17]。
    [24] 返回值作为函数返回值(而不是通过输出参数);§操作;[cg: f.20] [cg: f.21]。
    [26] 不要过度使用返回类型的扣除;§操作。
    [27] 不要过度使用结构化绑定;使用命名返回类型通常更清晰的文档;§3.6.3。
___
###4 类
	Those types are not “abstract”;they are as real as int and float.	– Doug McIlroy
    • 介绍
    • 具体类型
        一个算术类型;一个容器;初始化容器
    • 抽象类型
    • 虚函数
    • 类层次结构
        受益于层次结构;导航层次结构;避免资源泄漏
    • 建议

####4.1 介绍
	本章和后面三章的目的是让你了解c++对抽象和资源管理的支持，而不是深入讨论很多细节:
        • 本章非正式地介绍了定义和使用新类型(用户定义类型)的方法。
		特别是，它展示了用于具体类、抽象类和类层次结构的基本属性、实现技术和语言设施。
        • 第五章介绍了c++中定义了含义的操作，如构造函数、析构函数和赋值。它概述了组合使用这些规则来控制对象的生命周期，并支持简单、高效和完整的资源管理。
        • 第6章介绍了模板作为一种用(其他)类型和算法参数化类型和算法的机制。用户定义和内置类型的计算表示为函数，有时泛化为模板函数和函数对象。
        • 第7章概述了作为通用编程基础的概念、技术和语言特性。通用编程的基础。 重点是定义和使用概念，以精确指定模板的接口，并指导设计。介绍了五种不同的模板，用于 介绍了各种模板，用于指定最通用和最灵活的接口。
    这些语言工具支持被称为面向对象编程和泛型编程的编程风格。第8-15章接着介绍了标准库设施及其使用的例子。
        c++的核心语言特性是类。类是用户定义的类型，用于表示程序代码中的概念。每当我们的程序设计中有一个有用的概念、想法、实体等，我们就会尝试将其表示为程序中的一个类，这样想法就会存在于代码中，而不是只存在于我们的头脑中、设计文档或一些注释中。根据精心选择的一组类构建的程序要比直接根据内置类型构建所有内容的程序更容易理解和实现。特别地，类通常是库所提供的。
        基本上，除了基本类型、操作符和语句之外，所有的语言工具都是为了帮助定义更好的类或更方便地使用它们。我说的“更好”是指更正确、更容易维护、更高效、更优雅、更容易使用、更容易阅读、更容易推理。大多数编程技术都依赖于特定类型的类的设计和实现。程序员的需求和品味千差万别。因此，对类的支持是广泛的。这里，我们只考虑对三种重要类的基本支持:
            •具体类(§4.2)
            •抽象类(§4.3)
            •类层次中的类(§4.5)
        大量有用的类都是这三种类型中的一种。甚至更多的类可以被视为这些类型的简单变体，或者使用用于这些类型的技术的组合来实现。

####4.2 具体类型
	具体类的基本思想是它们的行为“就像内置类型一样”。例如，复数类型和无限精度整数很像内置int，当然，它们有自己的语义和操作集。类似地，vector和string很像内置数组，只是它们的表现更好(§9.2、§10.3、§11.2)。
    	具体类型的定义特征是其表示是其定义的一部分。在许多重要的情况下，比如vector，这种表示形式只是一个或多个指向存储在其他地方的数据的指针，但这种表示形式存在于具体类的每个对象中。这允许实现在时间和空间上达到最佳效率。特别是，它允许我们
        • 将具体类型的对象放置在栈上、静态分配的内存中以及其他对象中(§1.5);
        • 直接引用对象(不只是通过指针或引用);
        • 立即并完全初始化对象(例如，使用构造函数;§2.3);
        • 复制和移动对象(§5.2)。
    表示形式可以是私有的(就像Vector;§2.3)，只能通过成员函数来访问，但它是存在的。因此，如果表示发生了重大变化，用户必须重新编译。这是为了让具体类型的行为与内置类型完全一样而付出的代价。对于不经常更改的类型，以及局部变量提供急需的清晰性和效率的类型，这是可以接受的，通常也是理想的。为了增加灵活性，具体类型可以将其表示的主要部分保存在自由存储区(动态内存、堆)，并通过存储在类对象本身中的部分来访问它们。这就是vector和string的实现方式;它们可以被视为具有精心设计的接口的资源句柄。

#####4.2.1 算术类型
	“经典用户定义算术类型”是complex:
        class complex {
        	double re, im; // representation: two doubles
        public:
        	complex(double r, double i) :re{r}, im{i} {} // constr uct complex from two scalars
        	complex(double r) :re{r}, im{0} {} // constr uct complex from one scalar
        	complex() :re{0}, im{0} {} // default complex: {0,0}
        	double real() const { return re; }
        	void real(double d) { re=d; }
        	double imag() const { return im; }
        	void imag(double d) { im=d; }
            complex& operator+=(complex z)
            {
                re+=z.re; // add to re and im
                im+=z.im;
                return ∗this; // and return the result
            }
            complex& operator−=(complex z)
            {
            	re−=z.re;
            	im−=z.im;
            	return ∗this;
            }
            complex& operator∗=(complex); // defined out-of-class somewhere
            complex& operator/=(complex); // defined out-of-class somewhere
        };
    这是标准库综合体的一个稍微简化的版本(§14.4)。类定义本身只包含需要访问表示的操作。这种表示方法简单而常规。出于实际原因，它必须与Fortran 60年前提供的操作符兼容，我们需要一组传统的操作符。除了逻辑需求之外，复杂必须是高效的，否则它将被闲置。这意味着简单操作必须内联。
	也就是说，简单的操作(例如构造函数、+=和imag())必须在生成的机器码中不调用函数来实现。默认情况下，类中定义的函数是内联的。可以通过在函数声明前加上关键字inline来显式地请求内联。
    	可以不带参数调用的构造函数称为默认构造函数。因此，complex()是complex的默认构造函数。通过定义默认构造函数，消除了该类型未初始化变量的可能性。
        返回实部和虚部的函数的const说明符指示这些函数不修改它们所调用的对象。const成员函数可以被const对象和非const对象调用，但是非const成员函数只能被非const对象调用。例如:
        complex z = {1,0};
        const complex cz {1,3};
        z = cz; // OK: assigning to a non-const var iable
        cz = z; // error : complex::operator=() is a non-const member function
        double x = z.real(); // OK: complex::real() is a const member function
	许多有用的操作不需要直接访问complex的表示，所以它们可以与类定义分开定义:
		complex operator+(complex a, complex b) { return a+=b; }
        complex operator−(complex a, complex b) { return a−=b; }
        complex operator−(complex a) { return {−a.real(), −a.imag()}; } // unar y minus
        complex operator∗(complex a, complex b) { return a∗=b; }
        complex operator/(complex a, complex b) { return a/=b; }
    在这里，我使用了复制按值传递的参数这一事实，以便可以在不影响调用方副本的情况下修改参数，并使用结果作为返回值。
    	==和!=的定义很简单:
        bool operator==(complex a, complex b) // equal
        {
        	return a.real()==b.real() && a.imag()==b.imag();
        }
        bool operator!=(complex a, complex b) // not equal
        {
        	return !(a==b);
        }
        complex sqr t(complex); // the definition is elsewhere
        // ...
    类complex可以这样使用:
    	void f(complex z)
        {
            complex a {2.3}; // constr uct {2.3,0.0} from 2.3
            complex b {1/a};
            complex c {a+z∗complex{1,2.3}};
            // ...
            if (c != b)
                c = −(b/a)+2∗b;
        }
	编译器将涉及复数的操作符转换为适当的函数调用。例如,c !=b表示运算符!=(c,b)， 1/a表示运算符/(复数{1}，a)。
		用户定义的操作符(“重载操作符”)应该谨慎而常规地使用。
	语法是由语言固定的，所以不能定义一元/。此外，不可能更改内置类型操作符的含义，因此不能将+重定义为减去整型。

#####4.2.2 容器
	容器是保存元素集合的对象。之所以称Vector类为容器，是因为Vector类型的对象也是容器。正如§2.3所定义的，Vector并不是一个不合理的双精度对象容器:它易于理解，建立了一个有用的不变式(§3.5.2)，提供了范围检查访问(§3.5.1)，并提供了size()来允许我们迭代它的元素。然而，它确实有一个致命的缺陷:它使用new分配元素，但从不释放它们。这并不是一个好主意，因为尽管c++定义了垃圾收集器的接口(§5.3)，但并不能保证该接口可以使未使用的内存用于新对象。在某些环境中，您不能使用收集器，通常出于逻辑或性能原因，您希望对销毁进行更精确的控制。我们需要一种机制来确保由构造函数分配的内存被释放;该机制是析构函数:
        class Vector {
        public:
            Vector(int s) :elem{new double[s]}, sz{s} // constr uctor: acquire resources
            {
                for (int i=0; i!=s; ++i) // initialize elements
                    elem[i]=0;
            }
            ˜Vector() { delete[] elem; } // destr uctor: release resources
            double& operator[](int i);
            int size() const;
        private:
            double∗ elem; // elem points to an array of sz doubles
            int sz;
        };
	析构函数的名称是补操作符，˜，后面是类的名称;它是构造函数的补码。Vector的构造函数使用new操作符在自由存储区(也称为堆或动态存储区)上分配一些内存。析构函数通过使用delete[]操作符释放内存来进行清理。普通delete删除单个对象，delete[]删除一个数组。
    	这一切都是在没有Vector用户干预的情况下完成的。用户可以像使用内置类型的变量一样简单地创建和使用vector。例如:
        void fct(int n)
        {
            Vector v(n);
            // ... use v ...
            {
                Vector v2(2∗n);
                // ... use v and v2 ...
            } / / v2 is destroyed here
            // ... use v ..
        } / / v is destroyed here
	Vector在命名、作用域、分配、生存期等方面遵循与内置类型(如int和char)相同的规则(§1.5)。这个Vector简化了错误处理;看到§3.5。
    	构造函数/析构函数组合是许多优雅技术的基础。特别是，它是大多数c++通用资源管理技术的基础(§5.3，§13.2)。
        构造函数适当地分配元素并初始化Vector成员。析构函数释放元素。这个句柄到数据模型非常常用来管理在对象生命周期内大小可能不同的数据。在构造函数中获取资源并在析构函数中释放资源的技术(称为Resource Acquisition Is Initialization或RAII)允许我们消除“裸露的新操作”，也就是说，避免在一般代码中分配资源，并将它们隐藏在行为良好的抽象的实现中。同样，应该避免“直接的 new 操作”。避免直接 new 和直接 delete使得代码更不容易出错，更容易避免资源泄漏(§13.2)。

#####4.2.3 初始化容器
	容器的存在是为了保存元素，因此显然需要方便的方法将元素放入容器中。我们可以使用适当数量的元素创建Vector，然后对它们进行赋值，但通常其他方法更优雅。在这里，我只提到两种最喜欢的:
    	• 初始化列表构造函数:用元素列表进行初始化。
        • push_back():在序列的末尾添加一个新元素。
	它们可以这样声明:
        class Vector {
        public:
        	Vector(std::initializ er_list<double>); // initialize with a list of doubles
        	// ...
        	void push_back(double); // add element at end, increasing the size by one
        	// ...
        };
	push_back()对于输入任意数量的元素非常有用。例如
        Vector read(istream& is)
        {
            Vector v;
            for (double d; is>>d; ) // read floating-point values into d
            	v.push_back(d); // add d to v
            return v;
        }
    输入循环被文件结束符或格式错误终止。在此之前，读取的每一个数字都会被添加到Vector容器中，这样在最后，v的大小就是读取的元素数量。我使用for语句而不是更传统的while语句来将d的作用域限制在循环中。为Vector提供一个转移构造函数，以便从read()返回潜在的大量数据，这种方法很便宜，在§5.2.2中有解释:
    	Vector v = read(cin); // no copy of Vector elements here
    §11.2中介绍了使用std::vector实现push_back()和其他改变vector大小的操作的方法。
    	用于定义初始化列表构造函数的std::initializ er_list是编译器知道的标准库类型:当我们使用{}-list时，例如{1,2,3,4}，编译器将创建一个initializ er_list类型的对象给程序。所以，我们可以这样写:
        Vector v1 = {1,2,3,4,5}; // v1 has 5 elements
        Vector v2 = {1.23, 3.45, 6.7, 8}; // v2 has 4 elements
        Vector的初始化列表构造函数可以这样定义:
        Vector::Vector(std::initializ er_list<double> lst) // initialize with a list
        :elem{new double[lst.siz e()]}, sz{static_cast<int>(lst.siz e())}
        {
        	copy(lst.begin(),lst.end(),elem); // copy from lst into elem (§12.6)
        }
    不幸的是，标准库对大小和下标使用无符号整数，所以我需要使用难看的static_cast来显式地将初始化列表的大小转换为int。这显得有些死板，因为手写列表中元素数量大于最大整数(16位整数为32,767,32位整数为2,147,483,647)的概率相当低。然而，类型系统没有常识。它知道变量的可能值，而不是实际值，所以它可能会在没有实际冲突的地方抱怨。这样的警告有时可以避免程序员犯严重错误。
    static_cast不会检查它转换的值;程序员可以正确地使用它。这并不总是一个好的假设，所以如果有疑问，请检查值。最好避免显式类型转换(通常称为强制转换，以提醒您使用它们来支持损坏的内容)。尝试只对系统的最低级别使用非检查类型转换。他们是容易出错的。
    其他类型强制转换包括reinterpret_cast和const_cast，分别用于将对象简单地视为一个字节序列，以及“抛出const”。“明智地使用类型系统和设计良好的库允许我们在更高级别的软件中消除未检查的类型转换。

####4.3 抽象类型
	像complex和Vector这样的类型被称为具体类型，因为它们的表示是它们定义的一部分。因此，它们类似于内置类型。相比之下，抽象类型是将用户与实现细节完全隔离开来的类型。为此，我们将接口与表示解耦，并放弃真正的局部变量。由于我们对抽象类型的表示法一无所知(甚至不知道它的大小)，所以必须在自由存储区中分配对象(§4.2.2)，并通过引用或指针(§1.7、§13.2.1)来访问它们。
		首先，定义Container类的接口，将其设计为Vector的更抽象版本:
		class Container {
        public:
            virtual double& operator[]\(int\) = 0; // pure virtual function
            virtual int size() const = 0; // const member function (§4.2.1)
            virtual ˜Container() {} // destr uctor (§4.2.2)
        };
    这个类是稍后定义的特定容器的纯接口。“virtual”这个词的意思是“可以在以后派生出的一个类中重新定义。”不出意外，一个声明为virtual的函数被称为虚函数。从Container派生的类提供了Container接口的实现。奇怪的=0语法表示函数是纯虚的;也就是说，某个派生于Container的类必须定义该函数。因此，不可能只定义一个Container对象。例如:
    	Container c; // error : there can be no objects of an abstract class
		Container∗ p = new Vector_container(10); // OK: Container is an interface
	Container只能作为实现operator[]()和size()函数的类的接口。具有纯虚函数的类称为抽象类。
		这个容器可以这样使用:
        void use(Container& c)
        {
            const int sz = c.size();
            for (int i=0; i!=sz; ++i)
            	cout << c[i] << '\n';
        }
    注意use()是如何在完全忽略实现细节的情况下使用Container接口的。它使用size()和[]，但不知道具体是哪种类型提供了它们的实现。提供各种其他类接口的类通常被称为多态类型。
    	和抽象类一样，Container没有构造函数。毕竟，它没有任何要初始化的数据。另一方面，Container确实有一个析构函数，并且该析构函数是virtual实际的，因此从Container派生的类可以提供实现。同样，这对于抽象类来说很常见，因为它们倾向于通过引用或指针来操作，而通过指针销毁Container的人并不知道它的实现拥有哪些资源;参见§4.5。
		抽象类Container只定义了一个接口，没有定义任何实现。为了使Container有用，我们必须实现一个实现其接口所需函数的容器。
		class Vector_container : public Container { // Vector_container implements Container
        public:
            Vector_container(int s) : v(s) { } // Vector of s elements
            ˜Vector_container() {}
            double& operator[](int i) override { return v[i]; }
            int size() const override { return v.siz e(); }
        private:
        	Vector v;
        };
    public可理解为“派生自”或“是的子类型”。类Vector_container被认为是类Container的派生类，而类Container被认为是类Vector_container的基类。
	另一种术语分别称为Vector_container和Container子类和超类。派生类被称为从其基类继承成员，因此使用基类和派生类通常被称为继承。
    	成员操作符[]()和size()被认为覆盖基类Container中的对应成员。我使用了显式override来明确目标。override的使用是可选的，但是显式允许编译器捕捉错误，比如函数名的拼写错误，或者实际函数的类型与其预期覆盖之间的细微差别。override的显式使用在更大的类层次结构中特别有用，否则就很难知道什么应该重写什么。
        析构函数(˜Vector_container())重写基类析构函数。注意，成员析构函数(˜Vector())由其类的析构函数隐式调用(˜Vector_container())。
		对于像use(Container&)这样的函数在完全不知道实现细节的情况下使用Container，其他一些函数必须创建一个它可以操作的对象。例如:
        void g()
        {
            Vector_container vc(10); // Vector of ten elements
            // ... fill vc ...
            use(vc);
        }
    因为use()不知道Vector_containers，而只知道Container接口，所以它同样适用于容器的不同实现。例如:
    	class List_container : public Container
        { // List_container implements Container
        public:
            List_container() { } // empty List
            List_container(initializ er_list<double> il) : ld{il} { }
            ˜List_container() {}
            double& operator[](int i) override;
            int size() const override { return ld.size(); }
        private:
            std::list<double> ld; // (standard-librar y) list of doubles (§11.3)
        };
        double& List_container::operator[](int i)
        {
            for (auto& x : ld)
            {
                if (i==0)
                	return x;
                −−i;
            }
            throw out_of_range{"List container"};
        }
    这里的表示形式是标准库列表。通常，我不会使用列表来实现带有下标操作的容器，因为与向量下标相比，列表下标的性能太差了。然而，这里我只是想展示一个与通常的实现截然不同的实现。
    	函数可以创建一个List_container，并使用use()来使用它:
		void h()
        {
            List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            use(lc);
        }
    关键是，use(container &)不知道它的参数是Vector_container, List_container，或其他类型的容器;它不需要知道。它可以使用任何类型的容器。它只知道由Container定义的接口。因此，如果List_container的实现发生了变化，或者使用了从Container派生的全新类，则无需重新编译use(Container&)。
		这种灵活性的另一面是，必须通过指针或引用来操作对象(§5.2，§13.2.1)。

####4.4 虚函数
	再次考虑Container的使用:
        void use(Container& c)
        {
            const int sz = c.size();
            for (int i=0; i!=sz; ++i)
                cout << c[i] << '\n';
        }
    如何将use()中的调用c[i]解析为正确的操作符[]()?当h()调用use()时，必须调用List_container的操作符[]()。当g()调用use()时，必须调用Vector_container的操作符[]()。要实现此解决方案，Container对象必须包含信息，以便在运行时选择要调用的正确函数。通常的实现技术是编译器将虚函数的名称转换为索引，再转换为指向函数的指针表。这个表通常被称为虚函数表或vtbl。每个具有虚函数的类都有自己的标识其虚函数的vtbl。
    vtbl中的函数允许正确使用对象，即使调用者不知道对象的大小及其数据布局。调用者的实现只需要知道vtbl的指针在Container中的位置以及每个虚拟函数使用的索引。这种虚拟调用机制几乎可以与“普通函数调用”机制一样高效(在25%以内)。它的空间开销是具有虚函数的类的每个对象中的一个指针，以及每个此类类的一个vtbl。


####4.5 类层次结构
	Container 的例子是一个非常简单的类层次结构的例子。类层次结构是由派生(例如:public)创建的格中有序排列的一组类。我们使用类层次来表示具有层次关系的概念，例如“消防车是一种卡车，它是一种交通工具”和“笑脸是一种圆圈，它是一种形状”。“巨大的层次结构，包含数百个类，深度和广度都很常见。
    	类层次结构通常是从最基本的类(根类)向下延伸到(后来定义的)派生类。要在代码中表示这个简单的图，必须首先指定一个定义所有形状通用属性的类:
        class Shape {
        public:
            virtual Point center() const =0; // pure virtual
            virtual void move(Point to) =0;
            virtual void draw() const = 0; // draw on current "Canvas"
            virtual void rotate(int angle) = 0;
            virtual ˜Shape() {} // destr uctor
            // ...
        };
    自然地，这个接口是一个抽象类:就表示而言，对于每个Shape来说，没有什么是通用的(除了指向vtbl的指针的位置)。根据这个定义，我们可以编写操作形状指针vector的一般函数:
        void rotate_all(vector<Shape∗>& v, int angle) // rotate v’s elements by angle degrees
        {
            for (auto p : v)
                p−>rotate(angle);
        }
    要定义一个特定的形状，我们必须说它是一个形状，并指定它的特定属性(包括它的虚函数):
        class Circle : public Shape {
        public:
            Circle(Point p, int rad); // constr uctor
            Point center() const override
            {
                return x;
            }
            void move(Point to) override
            {
                x = to;
            }
            void draw() const override;
            void rotate(int) override {} // nice simple algorithm
        private:
            Point x; // center
            int r; // radius
        };
    到目前为止，与Container和Vector_container的例子相比，Shape和Circle的例子没有提供什么新内容，但我们可以进一步构建:
        class Smiley : public Circle {  // use the circle as the base for a face
        public:
            Smiley(Point p, int rad) : Circle{p,rad}, mouth{nullptr} { }
            ˜Smiley()
            {
                delete mouth;
                for (auto p : eyes)
                	delete p;
            }
            void move(Point to) override;
            void draw() const override;
            void rotate(int) override;
            void add_eye(Shape∗ s)
            {
            	ey es.push_back(s);
            }
            void set_mouth(Shape∗ s);
            vir tual void wink(int i); // wink eye number i
            // ...
        private:
            vector<Shape∗> eyes; // usually two eyes
            Shape∗ mouth;
        };
    vector的push_back()成员将其参数作为最后一个元素复制到vector中，并将vector的大小增加1。
    	现在可以通过调用Smiley的基类和成员draw()来定义Smiley::draw():
		void Smiley::draw() const
        {
            Circle::draw();
            for (auto p : eyes)
            	p−>draw();
            mouth−>draw();
        }
    请注意Smiley将其眼睛保存在标准库vector中，并在析构函数中删除它们的方式。Shape的析构函数是vir的，而Smiley的析构函数会重写它。虚析构函数对于抽象类至关重要，因为派生类的对象通常是通过其抽象基类提供的接口来操作的。特别是，可以通过指向基类的指针删除它。然后，虚函数调用机制确保调用正确的析构函数。
	然后，该析构函数隐式调用基类和成员的析构函数。
    	在这个简化的例子中，程序员的任务是将眼睛和嘴巴适当地放在代表脸的圆圈内。
		在通过派生定义新类时，可以添加数据成员、操作或两者都添加。这提供了很大的灵活性，同时也带来了相应的混乱和糟糕设计的机会。

#####4.5.1 受益于层次结构
	类层次结构提供了两种好处:
    	• 接口继承:派生类的对象可以在需要基类对象的地方使用。也就是说，基类充当派生类的接口。容器和形状类就是例子。这样的类通常是抽象类。
        • 实现继承:基类提供简化派生类实现的函数或数据。Smiley使用Circle的构造函数和Circle::draw()就是一个例子。这样的基类通常有数据成员和构造函数。
    具体类——特别是具有小表示的类——很像内置类型:我们将它们定义为局部变量，使用它们的名称访问它们，复制它们，等等。类层次结构中的类是不同的:我们倾向于使用new在自由存储区中分配它们，并通过指针或引用访问它们。例如，考虑一个函数，它从输入流读取描述形状的数据，并构造适当的Shape对象:
    	enum class Kind { circle, triangle , smiley };
        Shape∗ read_shape(istream& is) // read shape descriptions from input stream is
        {
            // ... read shape header from is and find its Kind k ...
            switch (k) {
            case Kind::circle:
            	// read circle data {Point,int} into p and r
            	return new Circle{p,r};
            case Kind::triangle:
            	// read triangle data {Point,Point,Point} into p1, p2, and p3
            	return new Triangle{p1,p2,p3};
            case Kind::smiley:
            	// read smiley data {Point,int,Shape,Shape,Shape} into p, r, e1, e2, and m
            	Smiley∗ ps = new Smiley{p,r};
            	ps−>add_eye(e1);
           		ps−>add_eye(e2);
            	ps−>set_mouth(m);
            	return ps;
            }
        }
    程序可以这样使用read_shape:
    	void user()
        {
            std::vector<Shape∗> v ;
            while (cin)
            	v.push_back(read_shape(cin));
            draw_all(v); // call draw() for each element
            rotate_all(v,45); // call rotate(45) for each element
            for (auto p : v) // remember to delete elements
            	delete p;
        }
    显然，这个示例被简化了—特别是在错误处理方面—但是它生动地说明了user()完全不知道它操作的是哪种形状。user()代码可以编译一次，稍后用于添加到程序中的新形状。注意，user()之外没有指向形状的指针，所以user()负责释放它们。这是通过delete操作符完成的，并且主要依赖于Shape的虚析构函数。因为该析构函数是虚的，所以delete调用派生类最多的析构函数。这是至关重要的，因为派生类可能已经获得了需要释放的各种资源(如文件句柄、锁和输出流)。在本例中，Smiley删除它的eyes和mouth对象。完成之后，它会调用Circle的析构函数。对象由构造函数“自底向上”(基类优先)构造，由析构函数“自顶向下”(派生优先)销毁。

#####4.5.2 层级导航
	read_shape()函数返回∗Shape，这样我们就可以相同地处理所有形状。但是，如果我们想使用只有特定派生类(如Smiley 's wink())提供的成员函数，该怎么办呢?我们可以问“这个形状是Smiley的一种吗?”使用dynamic_cast操作符:
    	Shape∗ ps {read_shape(cin)};
        if (Smiley∗ p = dynamic_cast<Smiley∗>(ps))
        { // ... does ps point to a Smiley? ...
        	// ... a Smiley; use it
        }
        else {
        	// ... not a Smiley, try something else ...
        }
    如果在运行时dynamic_cast(这里是ps)的参数所指向的对象不是预期的类型(这里是Smiley)或派生自预期类型的类，dynamic_cast将返回nullptr。
		当指向不同派生类对象的指针是有效参数时，将dynamic_cast转换为指针类型。然后测试结果是否为nullptr。这个测试通常可以方便地放在条件中变量的初始化中。
		当不同的类型不可接受时，可以简单地将dynamic_cast转换为引用类型。如果对象不是预期的类型，dynamic_cast会抛出bad_cast异常:
        	Shape∗ ps {read_shape(cin)};
			Smiley& r {dynamic_cast<Smiley&>(∗ps)}; // somewhere, catch std::bad_cast
	当有约束地使用dynamic_cast时，代码会更干净。如果我们能避免使用类型信息，我们可以编写更简单、更有效的代码，但偶尔会丢失类型信息，必须恢复。当我们将一个对象传递给某个接受基类指定的接口的系统时，通常会发生这种情况。当系统稍后将对象传回给我们时，我们可能需要恢复原始类型。与dynamic_cast类似的操作被称为“关于什么的类型”和“关于什么的实例”操作。

#####4.5.3 避免资源泄漏
	有经验的程序员会注意到我留下了三个犯错的机会:
        • Smiley的实现可能无法删除指向mouth的指针。
        • 使用read_shape()函数的用户可能无法删除返回的指针。
        • Shape指针容器的所有者可能无法删除所指向的对象。
	从这个意义上说，指向在自由存储区中分配的对象的指针是危险的:不应该使用“普通的旧指针”来表示所有权。例如:
        void user(int x)
        {
            Shape∗ p = new Circle{Point{0,0},10};
            // ...
            if (x<0) throw Bad_x{}; // potential leak
            if (x==0) return; // potential leak
            // ...
            delete p;
        }
	除非x是正数，否则会泄漏。将new的结果赋值给“裸指针”是在自找麻烦。
		解决这类问题的一个简单方法是在需要删除时使用标准库unique_ptr(§13.2.1)而不是“裸指针”:
        class Smiley : public Circle {
        // ...
        private:
            vector<unique_ptr<Shape>> eyes; // usually two eyes
            unique_ptr<Shape> mouth;
        };
    这是一个简单、通用、高效的资源管理技术(§5.3)的例子。
    	这个更改的一个令人愉快的副作用是，我们不再需要为Smiley定义析构函数。
	编译器将隐式地生成一个函数来销毁vector中的unique_ptrs(§5.3)。使用unique_ptr的代码将与正确使用原始指针的代码一样有效。
    	现在考虑read_shape()的用户:
    unique_ptr<Shape> read_shape(istream& is) // read shape descriptions from input stream is
    {
        // read shape header from is and find its Kind k
        switch (k) {
        case Kind::circle:
        	// read circle data {Point,int} into p and r
        	return unique_ptr<Shape>{new Circle{p,r}}; // §13.2.1
        // ...
    }
    void user()
    {
        vector<unique_ptr<Shape>> v;
        while (cin)
        	v.push_back(read_shape(cin));
        draw_all(v); // call draw() for each element
        rotate_all(v,45); // call rotate(45) for each element
    } / / all Shapes implicitly destroyed
	现在，每个对象都属于一个unique_ptr，当对象不再需要时，即当其unique_ptr超出作用域时，该对象将被删除。
		要让user()的unique_ptr版本起作用，我们需要版本的draw_all()和rotate_all()接受vector>s。编写许多这样的_all()函数可能会变得乏味，所以§6.3.2给出了另一种选择。

####4.6 建议
    [1] 在代码中直接表达思想;§4.1;(CG: P.1)。
    [2] 具体类型是最简单的类。在适用的情况下，选择具体的类型，而不是更复杂的类和普通的数据结构;§4.2;[CG: C.10]。
    [3] 用具体的类表示简单的概念;§4.2。
    [4] 对于性能关键的组件，选择具体的类而不是类层次结构;§4.2。
    [5] 定义构造函数来处理对象的初始化;§4.2.1;§5.1.1;[cg: c.40][cg: c.41]。
    [6] 只有当一个函数需要直接访问一个类的表示形式时，该函数才成为成员;§4.2.1;[CG: C.4]。
    [7] 定义操作符主要模仿常规用法;§4.2.1;[CG: C.160]。
    [8] 对称操作符使用非成员函数;§4.2.1;[CG: C.161]。
    [9] 声明一个不修改const对象状态的成员函数;§4.2.1。
    [10] 如果构造函数获得资源，其类需要析构函数来释放资源;§4.2.2;[CG: C.20]。
    [11] 避免"裸"新建和删除操作;§4.2.2;[CG: R.11]。
    [12] 使用资源句柄和RAII来管理资源;§4.2.2;[CG: R.1]。
    [13] 如果类是容器，给它一个初始化列表构造函数;§4.2.3;[CG: C.103]。
    [14] 当需要将接口和实现完全分离时，使用抽象类作为接口;§4.3;[CG: C.122]。
    [15] 通过指针和引用访问多态对象;§4.3。
    [16] 抽象类通常不需要构造函数;§4.3;[CG: C.126]。
    [17] 使用类层次结构来表示具有固有层次结构的概念;§4.5。
    [18] 具有虚函数的类应该有虚析构函数;§4.5;[CG: C.127]。
    [19] 使用override使重写在大型类层次结构中显式;§4.5.1;[CG: C.128]。
    [20] 在设计类层次结构时，区分实现继承和接口继承;§4.5.1;[CG: C.129]。
    [21] 当类层次导航不可避免时使用dynamic_cast;§4.5.2;[CG: C.146]。
    [22] 当无法找到所需的类被认为是失败时，使用dynamic_cast到引用类型;§4.5.2;[CG: C.147]。
    [23] 当无法找到所需的类被认为是有效的替代时，使用dynamic_cast到指针类型;§4.5.2;[CG: C.148]。
    [24] 使用unique_ptr或shared_ptr来避免忘记删除使用new创建的对象;§4.5.3;[CG: C.149]。

___
###5 基本操作
	When someone says I want a programming language in which I need only say what I wish done, give him a lollipop.	– Alan Perlis
    • 介绍
        基本操作;转换;成员初始化
    • 复制和移动
        复制容器;移动的容器
    • 资源管理
    • 传统操作
        比较;容器操作;输入输出操作符;用户定义的文字;swap(); hash<>
    • 建议

####5.1 介绍
	一些操作，如初始化、赋值、复制和移动，是基本的，因为语言规则对它们进行了假设。其他操作，如==和<<，具有传统意义，忽略它们是危险的。

#####5.1.1 基本操作
	对象的构造在许多设计中起着关键作用。这种广泛的用途反映在支持初始化的语言特性的范围和灵活性上。
		类型的构造函数、析构函数以及复制和移动操作在逻辑上不是独立的。
	我们必须将它们定义为匹配的集合，否则就会出现逻辑或性能问题。如果类X有一个析构函数来执行一些重要的任务，比如释放自由存储空间或释放锁，则类可能需要完整的函数补充:
		class X {
        public:
            X(Sometype); // ‘‘ordinar y constr uctor’’: create an object
            X(); // default constructor
            X(const X&); // copy constr uctor
            X(X&&); // move constr uctor
            X& operator=(const X&); // copy assignment: clean up target and copy
            X& operator=(X&&); // move assignment: clean up target and move
            ˜X(); // destr uctor: clean up
            // ...
        };
    对象可以复制或移动的情况有五种:
    	• 作为赋值源
        • 作为对象初始化器
        • 作为函数参数
        • 作为函数返回值
        • 作为异常
	赋值操作使用复制或移动赋值操作符。原则上，其他情况使用复制或移动构造函数。然而，复制或移动构造函数调用通常通过在目标对象中构造用于初始化的对象而被优化掉。例如:
    	X make(Sometype);
		X x = make(value);
    在这里，编译器通常会直接在X中从make()构造X;从而消除(“省略”)副本。
		除了初始化命名对象和自由存储区中的对象外，构造函数还用于初始化临时对象和实现显式类型转换。
		除了“普通构造函数”之外，这些特殊的成员函数将由编译器根据需要生成。如果你想显式地生成默认实现，你可以:
		class Y {
        public:
            Y(Sometype);
            Y(const Y&) = default; // I really do want the default copy constr uctor
            Y(Y&&) = default; // and the default move constr uctor
            // ...
        };
    如果显式指定了一些默认值，则不会生成其他默认值定义。
    	当类有指针成员时，显式地执行复制和移动操作通常是一个好主意。原因是指针可能指向类需要删除的内容，在这种情况下，默认的成员复制将是错误的。或者，它可能指向类不能删除的内容。无论哪种情况，代码的读者都想知道。如§5.2.1所示。
        一个好的经验法则(有时称为零规则)是要么定义所有的基本操作，要么不定义(使用默认的all)。例如:
        struct Z {
            Vector v;
            string s;
        };
        Z z1; // default initialize z1.v and z1.s
        Z z2 = z1; // default copy z1.v and z1.s
    在这里，编译器将根据需要合成具有正确语义的成员默认构造、复制、移动和析构函数。
	当补全=default时，我们用 =delete表示不生成该操作。类层次结构中的基类是不允许成员复制的典型例子。例如:
    	class Shape {
        public:
            Shape(const Shape&) =delete; // no copy operations
            Shape& operator=(const Shape&) =delete;
            // ...
        };
        void copy(Shape& s1, const Shape& s2)
        {
        	s1 = s2; // error : Shape copy is deleted
        }
    =delete将导致试图使用已删除函数的编译时错误;=delete可用于抑制任何函数，而不仅仅是基本成员函数。

#####5.1.2 转换
	接受单个参数的构造函数定义了与其参数类型的转换。例如，complex(§4.2.1)提供了一个double类型的构造函数:
    	complex z1 = 3.14; // z1 becomes {3.14,0.0}
		complex z2 = z1∗2; // z2 becomes z1*{2.0,0} == {6.28,0.0}
	这种隐式转换有时是理想的，但并不总是如此。例如，Vector(§4.2.2)提供了一个int类型的构造函数:
    	Vector v1 = 7; // OK: v1 has 7 elements
    这通常被认为是不幸的，而且标准库的vector不允许这种整型到vector的“转换”。
    	避免这个问题的方法是只允许显式的“转换”;也就是说，我们可以这样定义构造函数:
		class Vector {
        public:
            explicit Vector(int s); // no implicit conversion from int to Vector
            // ...
        };
	这给我们:
    	Vector v1(7); // OK: v1 has 7 elements
		Vector v2 = 7; // error : no implicit conversion from int to Vector
    当涉及到转换时，像Vector这样的类型比像复杂的显式构造函数(接受单个参数)的类型更多，除非有很好的理由不接受单个参数。

#####5.1.3 成员初始化
    定义类的数据成员时，可以提供一个默认初始化式，称为默认成员初始化式。考虑对complex修改(§4.2.1):
    	class complex {
            double re = 0;
            double im = 0; // representation: two doubles with default value 0.0
        public:
            complex(double r, double i) :re{r}, im{i} {} // constr uct complex from two scalars: {r,i}
            complex(double r) :re{r} {} // constr uct complex from one scalar: {r,0}
            complex() {} // default complex: {0,0}
            // ...
        }
    当构造函数没有提供值时使用默认值。这简化了代码，并帮助我们避免意外地留下未初始化的成员。


####5.2 复制和转换
	默认情况下，可以复制对象。对于用户定义类型的对象和内置类型都是如此。copy的默认含义是memberwise copy:复制每个成员。例如，使用§4.2.1中的complex:
        void test(complex z1)
        {
            complex z2 {z1}; // copy initialization
            complex z3;
            z3 = z2; // copy assignment
            // ...
        }
    现在，z1、z2和z3具有相同的值，因为赋值和初始化都复制了两个成员。
    	在设计类时，必须始终考虑是否复制对象以及如何复制对象。对于简单的具体类型，成员复制通常是正确的语义。对于一些复杂的具体类型，如Vector，成员复制并不是Copy的正确语义;对于抽象类型，它几乎从来都不是。

#####5.2.1 复制容器
	当类是资源句柄时——也就是说，当类负责通过指针访问对象时——默认的成员复制通常是一个灾难。成员式复制会违反资源句柄的不变量(§3.5.2)。例如，默认的副本会留下一个Vector对象的副本，该副本引用的元素与原Vector对象相同:
	void bad_copy(Vector v1)
    {
        Vector v2 = v1; // copy v1’s representation into v2
        v1[0] = 2; // v2[0] is now also 2!
        v2[1] = 3; // v1[1] is now also 3!
	}
	幸运的是，Vector有析构函数这一事实强烈暗示默认的(memberwise)复制语义是错误的，编译器至少应该对这个示例发出警告。我们需要定义更好的复制语义。
	类对象的复制由两个成员定义:复制构造函数和复制赋值:
        class Vector {
        private:
            double∗ elem; // elem points to an array of sz doubles
            int sz;
        public:
            Vector(int s); // constr uctor: establish invariant, acquire resources
            ˜Vector() { delete[] elem; } // destr uctor: release resources
            Vector(const Vector& a); // copy constr uctor
            Vector& operator=(const Vector& a); // copy assignment
            double& operator[](int i);
            const double& operator[](int i) const;
            int size() const;
        };
	Vector的复制构造函数的适当定义是，为基本操作元素分配空间，然后将所有元素复制到Vector中，这样，每次复制之后，Vector都有自己的元素副本:
        Vector::Vector(const Vector& a) // copy constr uctor
        :elem{new double[a.sz]}, // allocate space for elements
        sz{a.sz}
        {
            for (int i=0; i!=sz; ++i) // copy elements
            	elem[i] = a.elem[i];
        }
    当然，除了复制构造函数，我们还需要一个复制赋值:
        Vector& Vector::operator=(const Vector& a) // copy assignment
        {
            double∗ p = new double[a.sz];
            for (int i=0; i!=a.sz; ++i)
            	p[i] = a.elem[i];
            delete[] elem; // delete old elements
            elem = p;
            sz = a.sz;
            return ∗this;
        }
    this是在成员函数中预定义的名称，指向调用成员函数的对象。

#####5.2.2移动容器
	我们可以通过定义复制构造函数和复制赋值来控制复制，但是对于大型容器来说，复制的成本很高。通过使用引用将对象传递给函数时，可以避免复制的成本，但不能返回对局部对象的引用作为结果(在调用者有机会查看它时，局部对象将被销毁)。考虑:
        Vector operator+(const Vector& a, const Vector& b)
        {
            if (a.size()!=b.siz e())
            	throw Vector_siz e_mismatch{};
            Vector res(a.size());
            for (int i=0; i!=a.size(); ++i)
            	res[i]=a[i]+b[i];
            return res;
        }
    从a +返回需要将结果从局部变量res复制到调用者可以访问的地方。我们可以像这样使用+:
        void f(const Vector& x, const Vector& y, const Vector& z)
        {
            Vector r;
            // ...
            r = x+y+z;
            // ...
        }
	这将至少复制Vector两次(每次使用+操作符都复制一次)。如果向量很大，比如10000倍，那就很尴尬了。最令人尴尬的部分是，操作符+()中的res在复制后永远不会再使用。我们并不是真的想要副本;我们只是想从函数中得到结果:我们想移动一个Vector，而不是复制它。幸运的是，我们可以声明这个意图:
        class Vector {
            // ...
            Vector(const Vector& a); // copy constr uctor
            Vector& operator=(const Vector& a); // copy assignment
            Vector(Vector&& a); // move constr uctor
            Vector& operator=(Vector&& a); // move assignment
        };
	给定该定义，编译器将选择move构造函数来实现将返回值传递出函数。这意味着r=x+y+z将不涉及向量的复制。
	相反，向量只是移动。
    	通常情况下，Vector的move构造函数定义起来很简单:
        Vector::Vector(Vector&& a)
        :elem{a.elem}, // "grab the elements" from a
        sz{a.sz}
        {
            a.elem = nullptr; // now a has no elements
            a.sz = 0;
        }
    &&表示“右值引用”，是一个可以绑定右值的引用。“右值”这个词是用来补充“左值”的，“左值”大致的意思是“可以出现在赋值的左边的东西”。因此，右值是一个你不能赋值的值，比如函数调用返回的整数。因此，右值引用是对其他人不能赋值的对象的引用，所以我们可以安全地“窃取”它的值。vector的operator+()中的res局部变量就是一个例子。
		move构造函数不接受const参数:毕竟，move构造函数应该从其参数中移除该值。move赋值的定义类似。
		当将右值引用用作初始化式或赋值操作的右侧时，将应用移动操作。
		在移动之后，move-from对象应该处于允许运行析构函数的状态。通常，我们还允许对从move-from对象赋值。标准库算法(第12章)假设。我们的向量就是这样。
		当程序员知道某个值不会再被使用，但又不能指望编译器足够聪明来找出这个值时，程序员可以指定:
            Vector f()
            {
                Vector x(1000);
                Vector y(2000);
                Vector z(3000);
                z = x ; / / we get a copy (x might be used later in f())
                y = std::move(x); // we get a move (move assignment)
                // ... better not use x here ...
                return z; // we get a move
            }
    标准库函数move()实际上并不移动任何东西。相反，它返回一个指向可移动的实参的引用——一个右值引用;这是一种cast(§4.2.3)。
	在返回之前，我们有:
	当我们从f()返回时，z的元素被返回函数移出f()后，z就被销毁了。
	但是，y的析构函数会删除[]的元素。
		编译器(根据c++标准)必须消除与初始化相关的大多数副本，因此move构造函数的调用并不像您想象的那么频繁。这种复制省略甚至可以消除移动中非常小的开销。另一方面，通常不可能隐式地从赋值中消除复制或移动操作，因此移动赋值对性能至关重要。

####5.3 资源管理
	通过定义构造函数、复制操作、移动操作和析构函数，程序员可以提供对所包含资源(如容器的元素)生命周期的完全控制。此外，move构造函数允许对象简单而廉价地从一个作用域移动到另一个作用域。这样一来，我们不能或不想复制出范围的对象就可以简单而廉价地移出。考虑一个表示并发活动(§15.2)的标准库线程和一个100万倍的Vector。我们不能复制前者，也不想复制后者。
        std::vector<thread> my_threads;
        Vector init(int n)
        {
            thread t {heartbeat}; // run hear tbeat concurrently (in a separate thread)
            my_threads.push_back(std::move(t)); // move t into my_threads (§13.2.2)
            // ... more initialization ...
            Vector vec(n);
            for (int i=0; i!=vec.size(); ++i)
            	vec[i] = 777;
            return vec; // move vec out of init()
        }
        auto v = init(1'000'000); // start heartbeat and initialize v
	在许多情况下，Vector和thread等资源句柄是直接使用内置指针的较好的替代方法。事实上，标准库中的“智能指针”，比如unique_ptr，本身就是资源句柄(§13.2.1)。
    	我使用标准库vector来保存线程，因为在§6.2之前，我们还没有使用元素类型参数化简单vector。
		就像new和delete从应用程序代码中消失一样，我们可以让指针消失在资源句柄中。在这两种情况下，结果都是更简单和更可维护的代码，没有额外的开销。特别是我们可以实现强大的资源安全;也就是说，我们可以消除资源的一般概念的资源泄漏。例如，向量持有内存，线程持有系统线程，fstreams持有文件句柄。
    	在许多语言中，资源管理主要委托给垃圾收集器。c++还提供了一个垃圾收集接口，以便您可以插入垃圾收集器。然而，我认为垃圾收集是在资源管理的更清洁、更通用、更好的本地化替代方案用尽之后的最后选择。我的理想是不制造任何垃圾，这样就不需要垃圾收集器:不要乱扔垃圾!垃圾收集基本上是一种全局内存管理方案。聪明的实现可以弥补这一点，但是随着系统变得更加分布式(比如缓存、多核和集群)，局部性比以往任何时候都更加重要。
		此外，内存并不是唯一的资源。资源是在使用后必须被获取和(显式或隐式)释放的任何东西。例如内存、锁、套接字、文件句柄和线程句柄。不出所料，不只是内存的资源被称为非内存资源。一个好的资源管理系统可以处理各种资源。在任何长时间运行的系统中都必须避免泄漏，但是过多的资源保留几乎与泄漏一样糟糕。例如，如果系统占用内存、锁、文件等的时间是原来的两倍，那么就需要为系统提供两倍的资源。
    	在进行垃圾收集之前，系统地使用资源句柄:让每个资源在某个范围内拥有一个所有者，并在默认情况下在其所有者范围结束时释放资源。在c++ 中，这被称为RAII(资源获取即初始化)，并以异常的形式与错误处理集成在一起。资源可以使用移动语义或“智能指针”从一个作用域移动到另一个作用域，共享所有权可以用“共享指针”来表示(§13.2.1)。
        在c++标准库中，RAII无处不在:例如内存(字符串、向量、map、unordered_map等)、文件(ifstream、ofstream等)、线程(thread)、锁(lock_guard、unique_lock等)和一般对象(通过unique_ptr和shared_ptr)。其结果是隐式的资源管理，在通常的使用中是不可见的，并导致较低的资源保留时间。

####5.4 常规操作
	在为类型定义时，有些操作具有常规含义。程序员和库(尤其是标准库)通常会假定这些传统意义，因此在设计操作适用的新类型时，遵循这些传统意义是明智的。
    • 比较:==，!=，<，<=，>，和>=(§5.4.1)
    • 容器操作:size()， begin()， end()(§5.4.2)
    • 输入和输出操作:>>和<<(§5.4.3)
    • 用户定义的字面量(§5.4.4)
    • swap() (§5.4.5)
    • Hash函数:Hash <>(§5.4.6)

#####5.4.1 比较
	相等比较(==和!=)的意义与复制密切相关。在一个副本之后，两个副本的比较应该相等:
        X a = something;
        X b = a ;
        asser t(a==b); // if a!=b here, something is very odd (§3.5.4).
    在定义==时，还要定义!=，并确保a!= b意味着! (= = b)。
		类似地，如果你定义<，也定义<=，>，>=，并确保通常的等价保持:
            • a<=b means (a<b)||(a==b) and !(b<a).
            • a>b means b<a.
            • a>=b means (a>b)||(a==b) and !(a<b).
        要对二元操作符(如==)的两个操作数进行相同的处理，最好将其定义为类命名空间中的独立函数。。例如:
        namespace NX
        {
            class X
            {
            	// ...
            };
            bool operator==(const X&, const X&);
            // ...
        };

#####5.4.2 容器操作
	除非有很好的理由，否则就按照标准库容器的风格来设计容器(第11章)。特别是，通过将容器资源实现为一个句柄，并进行适当的基本操作(§5.1.1，§5.2)，来保证容器资源的安全。
		标准库容器都知道它们的元素数量，可以通过调用size()来获取。例如:
		for (size _ t i = 0 ; i<c.size(); ++i) // size_t is the name of the type returned by a standard-library size()
			c[i] = 0;
	然而，标准算法(第12章)并没有使用从0到size()的索引遍历容器，而是使用了由一对迭代器分隔的序列的概念:
		for (auto p = c.begin(); p!=c.end(); ++p)
			∗p = 0 ;
	在这里，c.begin()是指向c的第一个元素的迭代器，c.end()指向c后面的一个元素。与指针一样，迭代器支持++移动到下一个元素，并支持∗访问所指向元素的值。这种迭代器模型(§12.3)具有极大的通用性和效率。迭代器用于将序列传递给标准库算法。例如:
    	sort(v.begin(),v.end());
    要了解更多容器操作的详细信息，请参见第11章和第12章。
		另一种隐式使用元素数量的方法是range-for循环:
        for (auto& x : c)
			x = 0 ;
    这隐式地使用了c.begin()和c.end()，大致相当于更显式的循环。

#####5.4.3 输入和输出操作
	对于整数对，<<表示左移，>表示右移。然而，对于iostream，它们分别是输出操作符和输入操作符(§1.8，第10章)。更多I/O操作请参见第10章。

#####5.4.4 用户定义的文字
	类的一个目的是使程序员能够设计和实现接近内置类型的类型。构造函数提供的初始化等同于或超过内置类型初始化的灵活性和效率，但对于内置类型，我们有文字:
        • 123 is an int.
        • 0xFF00u is an unsigned int.
        • 123.456 is a double.
        • "Surprise!" is a const char[10].
	为用户定义的类型提供这样的文字也会很有用。这是通过为字面定义合适的后缀的含义来实现的，因此我们可以得到
		• "Surprise!"s is a std::string.
        • 123s is seconds.
        • 12.7i is imaginary so that 12.7i+47 is a complex number (i.e., {47,12.7}).
	特别地，我们可以通过使用合适的头文件和名称空间从标准库中获得这些示例:
		Standard-Library Suffixes for Literals
        <chrono> 		std::literals::chrono_literals 	h, min, s, ms, us, ns
        <string> 		std::literals::string_literals 	s
        <string_view> 	std::literals::string_literals 	sv
        <complex> 		std::literals::complex_literals 	i, il, if
	不出意外，带有用户定义后缀的字面量称为用户定义字面量或udl。这些文字是使用文字操作符定义的。文字操作符将参数类型的文字后跟下标转换为返回类型。例如，i表示虚线y后缀，可以这样实现:
        constexpr complex<double> operator""i(long double arg) // imaginar y literal
        {
        	return {0,arg};
        }
	Here
        • 操作符""表示定义的是文字操作符。
        • “文字指示符” ""后面的i是操作符赋予意义的后缀。
        • 参数类型为long double，表示为浮点字面值定义了后缀(i)。
        • 返回类型complex指定了结果文字的类型。
	有了这个，我们可以写
		complex<double> z = 2.7182818+6.283185i;

#####5.4.5 swap()
	许多算法，最著名的是sort()，使用swap()函数交换两个对象的值。这种算法通常假定swap()非常快，并且不会抛出异常。
	标准库提供了一个std::swap(a,b)，实现为三个移动操作:(tmp=a, a=b, b=tmp)。如果您设计的类型复制成本很高，而且可能被交换(例如，通过排序函数)，那么给它一个move操作或一个swap()或两者兼有。请注意，标准库中的容器(第11章)和字符串(§9.2.1)都有快速move操作。

#####5.4.6 hash<>
	标准库unordered_map是一个哈希表，K是键类型，V是值类型(§11.5)。要使用类型X作为键，必须定义hash。标准库为常见类型(如std::string)做了这些。

####5.5 建议
    [1] 控制对象的构造、复制、移动和销毁;§5.1.1;[CG: R.1]。
    [2] 将构造函数、赋值函数和析构函数设计为匹配的操作集;§5.1.1;[CG: C.22]。
    [3] 定义所有基本操作或无;§5.1.1;[CG: C.21]。
    [4] 如果默认构造函数、赋值函数或析构函数合适，让编译器生成它(不要自己重写);§5.1.1;[CG: C.20]。
    [5] 如果类有指针成员，考虑它是否需要用户定义的或删除的析构函数，复制和移动;§5.1.1;[cg: c.32] [cg: c.33]
    [6] 如果一个类有用户定义的析构函数，它可能需要用户定义或删除的复制和移动;§5.2.1。
    [7] 默认情况下，将单参数构造函数声明为explicit;§5.1.1;[CG: C.46]。
    [8] 如果类成员有一个合理的默认值，将其作为数据成员初始化器提供;§5.1.3;[CG: C.48]。
    [9] 如果默认值不适合某个类型，则重新定义或禁止复制;§5.2.1,§4.6.5;[CG: C.61]。
    [10] 按值返回容器(依靠移动来提高效率);§5.2.2;[CG: F.20]。
    [11] 对于大操作数，使用const引用实参类型;§5.2.2;[CG: F.16]。
    [12] 提供强大的资源安全性;也就是说，永远不要泄露任何你认为是资源的东西;§5.3;[CG: R.1]。
    [13] 如果类是资源句柄，它需要用户定义的构造函数、析构函数和非默认的复制操作;§5.3;[CG: R.1]。
    [14] 模拟常规用法的过载操作;§5.4;[CG: C.160]。
    [15] 遵循标准库容器设计;§5.4.2;[CG: C.100]。

___
###6 模板
	Your quote here.	– B. Stroustrup
    • 介绍
    • 参数化类型
        约束模板参数;值模板参数;模板参数推导
    • 参数化操作
        函数模板;函数对象;Lambda表达式
    • 模板机制
        可变模板;别名;编译时if
    • 建议

####6.1 介绍
	使用向量的人不可能总是想要一个双精度的向量。向量是一个通用的概念，独立于浮点数的概念。因此，向量的元素类型应该独立表示。模板是用一组类型或值参数化的类或函数。我们使用模板来表示最容易理解的概念，通过指定实参可以生成特定的类型和函数，例如vector的元素类型double。

####6.2 参数化类型
	我们可以将双精度向量类型推广为任意向量类型，方法是将其作为模板，并用类型形参替换特定的双精度向量类型。例如:
        template<typename T>
        class Vector
        {
        private:
            T∗ elem; // elem points to an array of sz elements of type T
            int sz;
        public:
            explicit Vector(int s); // constr uctor: establish invariant, acquire resources
            ˜Vector() { delete[] elem; } // destr uctor: release resources
            // ... copy and move operations ...
            T& operator[](int i); // for non-const Vectors
            const T& operator[](int i) const; // for const Vectors (§4.2.1)
            int size() const { return sz; }
        };
	template<typename T> 前缀使T成为其前缀声明(typename)的参数。它是c++版本的数学“适用于所有T”，或者更准确地说，“适用于所有类型T”。如果你想要数学上的“对于所有的T，如P(T)”，你需要概念(§6.2.1，§7.2)。使用class引入类型形参等价于使用typename，在旧代码中，我们经常看到template<class T>作为前缀。
		成员函数可以类似地定义:
            template<typename T>
            Vector<T>::Vector(int s)
            {
                if (s<0)
                    throw Negative_size{};
                elem = new T[s];
                sz = s;
            }
            template<typename T>
            const T& Vector<T>::operator[](int i) const
            {
                if (i<0 || size()<=i)
                    throw out_of_range{"Vector::operator[]"};
                return elem[i];
            }
	有了这些定义，我们可以这样定义vector:
        Vector<char> vc(200); // vector of 200 characters
        Vector<string> vs(17); // vector of 17 strings
        Vector<list<int>> vli(45); // vector of 45 lists of integers
	Vector<list<int>> 中的>>终止了嵌套模板参数。它不是一个错位的输入操作符。
		我们可以这样使用向量:
        void write(const Vector<string>& vs) // Vector of some strings
        {
            for (int i = 0; i!=vs.size(); ++i)
            	cout << vs[i] << '\n';
        }
	为了支持Vector对象的range-for循环，必须定义合适的begin()和end()函数:
        template<typename T>
        T∗ begin(Vector<T>& x)
        {
        	return x.size() ? &x[0] : nullptr; // pointer to first element or nullptr
        }
        template<typename T>
        T∗ end(Vector<T>& x)
        {
        	return x.size() ? &x[0]+x.size() : nullptr; // pointer to one-past-last element
        }
	有了这些，我们可以这样写:
		void f2(Vector<string>& vs) // Vector of some strings
        {
            for (auto& s : vs)
            	cout << s << '\n';
        }
	类似地，我们可以将列表、向量、映射(即关联数组)、无序映射(即哈希表)等定义为模板(第11章)。
		模板是一种编译时机制，因此与手工编写的代码相比，使用模板不会产生运行时开销。事实上，为Vector<double>生成的代码与第4章中Vector版本生成的代码完全相同。而且，为标准库vector生成的代码可能更好(因为在它的实现中做了更多的工作)。
		模板加上一组模板参数称为实例化或特化。在编译过程的后期，在实例化时，程序中使用的每个实例化都会生成代码(§7.5)。生成的代码是类型检查的，因此生成的代码与手写代码一样是类型安全的。不幸的是，这种类型检查通常发生在编译过程的后期，也就是实例化时。

#####6.2.1 受约束的模板参数(c++ 20)
	通常，模板只对满足特定条件的模板参数有意义。例如，Vector通常提供复制操作，如果它提供复制操作，它必须要求其元素必须是可复制的。也就是说，我们必须要求Vector的模板实参不只是typename，而是Element，其中" Element "指定了可以是元素的类型的要求:
        template<Element T>
        class Vector {
        private:
            T∗ elem; // elem points to an array of sz elements of type T
            int sz;
            // ...
        }
	这个 template<Element T>前缀是c++版本的数学“对于所有这样的T Element(T)”;也就是说，Element是一个检查T是否具有Vector所要求的所有属性的谓词。
	这样的谓词称为概念(§7.2)。为其指定概念的模板参数称为受约束参数，为其指定受约束参数的模板称为受约束模板。
		如果试图用不符合要求的类型实例化模板，则会出现编译时错误。例如:
		Vector<int> v1; // OK: we can copy an int
		Vector<thread> v2; // error : we can’t copy a standard thread (§15.2)
	由于c++在c++ 20之前还没有正式支持概念，所以旧的代码使用不受约束的模板参数，并将需求留给文档。

#####6.2.2 值模板参数
	除了类型参数外，模板还可以接受值参数。例如:
        template<typename T, int N>
        struct Buffer {
            using value_type = T;
            constexpr int size() { return N; }
            T[N];
            // ...
        };
	提供了别名(value_type)和constexpr函数，以允许用户(只读)访问模板参数。
    	值参数在很多情况下都很有用。例如，Buffer允许我们创建任意大小的缓冲区，而不使用自由存储区(动态内存):
        Buffer<char,1024> glob; // global buffer of characters (statically allocated)
        void fct()
        {
            Buffer<int,10> buf; // local buffer of integers (on the stack)
            // ...
        }
	模板值参数必须是常量表达式。

#####6.2.3 模板参数推导
	考虑使用标准库模板 pair:
		pair<int,double> p = {1,5.2};
	许多人认为指定模板实参类型很繁琐，因此标准库提供了一个函数make_pair()，它从函数实参返回的一对模板实参中推导出它们:
		auto p = make_pair(1,5.2); // p is a pair<int,double>
	这就引出了一个明显的问题:“为什么我们不能从构造函数参数中推导模板参数呢?”所以，在c++ 17中，我们可以。那就是:
		pair p = {1,5.2}; // p is a pair<int,double>
	这不仅仅是pair的问题;Make_函数非常常见。考虑一个简单的例子:
        template<typename T>
        class Vector {
        public:
            Vector(int);
            Vector(initializ er_list<T>); // initializer-list constructor
            // ...
        };
        Vector v1 {1,2,3}; // deduce v1’s element type from the initializer element type
        Vector v2 = v1; // deduce v2’s element type from v1’s element type
        auto p = new Vector{1,2,3}; // p points to a Vector<int>
        Vector<int> v3(1); // here we need to be explicit about the element type (no element type is mentioned)
	显然，这简化了表示法，并可以消除由于错误输入冗余模板参数类型而引起的麻烦。然而，它并不是万灵药。演绎可能会带来意外(对于make_函数和构造函数)。考虑:
        Vector<string> vs1 {"Hello", "World"}; // Vector<string>
        Vector vs {"Hello", "World"}; // deduces to Vector<const char*> (Surprise?)
        Vector vs2 {"Hello"s, "World"s}; // deduces to Vector<string>
        Vector vs3 {"Hello"s, "World"}; // error : the initializer list is not homogenous
	c风格字符串字面量的类型是const char *(§1.7.1)。如果不是这样，使用s后缀使其成为一个合适的字符串(§9.2)。如果初始化列表的元素有不同的类型，则无法推导出唯一的元素类型，因此会得到错误。
		当无法从构造函数实参推导出模板实参时，我们可以通过提供演绎指南来提供帮助。考虑:
            template<typename T>
            class Vector2 {
            public:
                using value_type = T;
                // ...
                Vector2(initializ er_list<T>); // initializer-list constructor
                template<typename Iter>
                Vector2(Iter b, Iter e); // [b:e) range constructor
                // ...
            };
            Vector2 v1 {1,2,3,4,5}; // element type is int
            Vector2 v2(v1.begin(),v1.begin()+2);
	显然，v2应该是Vector2，但是如果没有帮助，编译器无法推断出这一点。该代码只声明同一类型的一对值有一个构造函数。如果没有对概念的语言支持(§7.2)，编译器就无法对该类型做出任何假设。为了允许演绎，我们可以在Vector2声明后添加演绎指南:
        template<typename Iter>
        Vector2(Iter,Iter) −> Vector2<typename Iter::value_type>;
	也就是说，如果看到一对迭代器初始化的Vector2，就应该推断Vector2::value_type是迭代器的值类型。
		演绎指南的效果通常是微妙的，所以最好设计类模板，这样就不需要演绎指南了。然而，标准库中有很多类(还)没有使用概念(§7.2)，并且有这样的歧义，所以它使用了相当多的演绎指南。

####6.3 参数化操作
	模板的用途远不止简单地用元素类型参数化容器。特别地，它们在标准库中被广泛地用于类型和算法的参数化(§11.6，§12.6)。
		有三种方式来表示通过类型或值参数化的操作:
            • 函数模板
            • 函数对象:可以携带数据并像函数一样调用的对象
            • lambda表达式:函数对象的速记符号

#####6.3.1 函数模板
	我们可以编写一个函数，计算rangefor可以遍历的任意序列(例如容器)元素值的和，如下所示:
        template<typename Sequence, typename Value>
        Value sum(const Sequence& s, Value v)
        {
            for (auto x : s)
            	v+=x;
            return v;
        }
	Value模板参数和函数参数v的存在是为了允许调用者指定累加器的类型和初始值(累加器是用来累加和的变量):
        void user(Vector<int>& vi, list<double>& ld, vector<complex<double>>& vc)
        {
            int x = sum(vi,0); // the sum of a vector of ints (add ints)
            double d = sum(vi,0.0); // the sum of a vector of ints (add doubles)
            double dd = sum(ld,0.0); // the sum of a list of doubles
            auto z = sum(vc,complex{0.0,0.0}); // the sum of a vector of complex<double>s
        }
	在double中添加整型数的目的是优雅地处理比最大整型数更大的数字。注意sum的模板实参类型是如何从函数实参推导出来的。幸运的是，我们不需要显式地指定这些类型。
		这个sum()是标准库accumulate()的简化版本(§14.3)。
		函数模板可以是成员函数，但不能是虚成员。编译器不会知道程序中这样一个模板的所有实例化，所以它不能生成vtbl(§4.4)。

#####6.3.2 函数对象
	一种特别有用的模板是函数对象(有时称为函子)，它用于定义可以像函数一样调用的对象。例如:
        template<typename T>
        class Less_than {
        	const T val; // value to compare against
        public:
            Less_than(const T& v) :val{v} { }
            bool operator()(const T& x) const { return x<val; } // call operator
        };
	名为operator()的函数实现了“函数调用”、“调用”或“应用程序”操作符()。
		我们可以为某些参数类型定义Less_than类型的命名变量:
        Less_than lti {42}; // lti(i) will compare i to 42 using < (i<42)
        Less_than lts {"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")
        Less_than<string> lts2 {"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <
	我们可以调用这样的对象，就像调用函数一样:
        void fct(int n, const string& s)
        {
            bool b1 = lti(n); // tr ue if n<42
            bool b2 = lts(s); // tr ue if s<"Backus"
            // ...
        }
	这样的函数对象被广泛用作算法的参数。例如，我们可以计算谓词返回true的值的出现次数:
        template<typename C, typename P>
        // requires Sequence<C> && Callable<P ,Value_type<P>>
        int count(const C& c, P pred)
        {
            int cnt = 0;
            for (const auto& x : c)
            	if (pred(x))
            		++cnt;
            return cnt;
        }
	我们可以调用谓词来返回true或false。例如:
        void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
        {
            cout << "number of values less than " << x << ": " << count(vec,Less_than{x}) << '\n';
            cout << "number of values less than " << s << ": " << count(lst,Less_than{s}) << '\n';
        }
	这里，Less_than{x}构造了一个Less_than类型的对象，调用操作符将其与名为x的int进行比较;Less_than{s}构造了一个与名为s的字符串进行比较的对象。这些函数对象的美妙之处在于它们携带了要与之进行比较的值。我们不需要为每个值(和每个类型)编写单独的函数，也不需要引入讨厌的全局变量来保存值。而且，对于像Less_than这样的简单函数对象，内联也很简单，因此调用Less_than比间接调用要高效得多。携带数据的能力加上它们的效率使得函数对象作为算法的参数特别有用。
		用于指定通用算法关键操作含义的函数对象(例如用于count()的Less_than)通常被称为策略对象。

#####6.3.3 Lambda表达式
	在§6.3.2中，我们将Less_than与它的使用分开定义。这很不方便。因此，有一种隐式生成函数对象的符号:
        void f(const Vector<int>& vec, const list<string>& lst, int x, const string& s)
        {
            cout << "number of values less than " << x
            	<< ": " << count(vec,[&](int a){ return a<x; })
            	<< '\n';
            cout << "number of values less than " << s
            	<< ": " << count(lst,[&](const string& a){ return a<s; })
            	<< '\n';
        }
	符号[&](int a){return a{x}完全相同的函数对象。[&]是一个捕获列表，指定lambda体中使用的所有本地名称(如x)将通过引用访问。如果我们只想“捕获”x，我们可以这样说:[&x]。如果我们想给生成的对象一个x的副本，我们可以这样说:[=x]。Capture nothing为[]，Capture all local names by reference为[&]，Capture all local names by value为[=]。
		使用lambdas既方便又简洁，但也有些晦涩。对于重要的操作(比如，不只是一个简单的表达式)，我更喜欢给操作命名，以便更清楚地说明它的目的，并使它可以在程序中的多个地方使用。
		在§4.5.3中，我们注意到必须编写许多函数来对指针和unique_ptrs的vector元素进行操作，例如draw_all()和rotate_all()。函数对象(特别是lambdas)可以通过允许我们将容器的遍历与对每个元素执行的操作的说明分开来提供帮助。
		首先，我们需要一个对指针容器元素所指向的每个对象应用操作的函数:
        template<typename C, typename Oper>
        void for_all(C& c, Oper op) // assume that C is a container of pointers
        // requires Sequence<C> && Callable<Oper,Value_type<C>> (see §7.2.1)
        {
            for (auto& x : c)
            	op(x); // pass op() a reference to each element pointed to
        }
	现在，我们可以编写§4.5版本的user()，而不用编写一组_all函数:
        void user2()
        {
            vector<unique_ptr<Shape>> v;
            while (cin)
            	v.push_back(read_shape(cin));
            for_all(v,[](unique_ptr<Shape>& ps){ ps−>draw(); }); // draw_all()
            for_all(v,[](unique_ptr<Shape>& ps){ ps−>rotate(45); }); // rotate_all(45)
        }
	我将unique_ptr&传递给lambda，以便for_all()不必关心对象到底是如何存储的。特别是，那些for_all()调用不会影响传递的Shapes的生命周期，lambdas的主体使用参数就像使用普通的指针一样。
		与函数一样，lambda也可以是泛型的。例如:
        template<class S>
        void rotate_and_draw(vector<S>& v, int r)
        {
        	for_all(v,[](auto& s){ s−>rotate(r); s−>draw(); });
        }
	在这里，就像变量声明一样，auto意味着任何类型都被接受为初始化器(在调用中，参数被认为是初始化形参)。这使得带有自动参数的lambda成为模板，一个泛型lambda。由于标准委员会的政治原因，目前功能参数不允许使用auto。
		我们可以用任何可以使用draw()和rotate()的对象容器来调用这个通用的rotate_and_draw()。例如:
        void user4()
        {
            vector<unique_ptr<Shape>> v1;
            vector<Shape∗> v2;
            // ...
            rotate_and_draw(v1,45);
            rotate_and_draw(v2,90);
        }
	使用lambda，我们可以将任何语句转换为表达式。这主要用于提供作为参数值计算值的操作，但这种能力是通用的。考虑一个复杂的初始化:
        enum class Init_mode { zero, seq, cpy, patrn }; // initializer alternatives
        // messy code:
        // int n, Init_mode m, vector<int>& arg, and iterators p and q are defined somewhere
        vector<int> v;
        switch (m)
        {
        case zero:
        	v = vector<int>(n); // n elements initialized to 0
        	break;
        case cpy:
        	v = arg ;
        break;
        };
        // ...
        if (m == seq)
        	v.assign(p,q); // copy from sequence [p:q)
        // ...
	这是一个程式化的例子，但不幸的是并不是典型的。我们需要在初始化数据结构的一组备选方案中进行选择(这里是v)，我们需要对不同的备选方案进行不同的计算。这样的代码通常很混乱，被认为是“效率”的关键，也是bug的来源:
        • 变量可以在得到预期值之前使用。
        • “初始化代码”可能与其他代码混合，使其难以理解。
        • 当“初始化代码”与其他代码混合时，很容易忘记一个案例。
        • 这不是初始化，这是赋值。
	相反，我们可以将其转换为用作初始化器的lambda:
        // int n, Init_mode m, vector<int>& arg, and iterators p and q are defined somewhere
        vector<int> v = [&] {
        switch (m)
        {
        case zero:
        	return vector<int>(n); // n elements initialized to 0
        case seq:
        	return vector<int>{p,q}; // copy from sequence [p:q)
        case cpy:
        	return arg;
        }
        }();
        // ...
	我仍然“忘记”一个案子，但现在很容易发现。

####6.4 模板机制
	为了定义好的模板，我们需要一些支持的语言工具:•依赖于type: variable模板的V值(§6.4.1)。
        • 值依赖于一个类型:变量模板(§6.4.1)。
		• 类型和模板的别名:别名模板(§6.4.2)。
        • 一个编译时选择机制:if constexpr(§6.4.3)。
        • 一种查询类型和表达式属性的编译时机制:requiresexpressions(§7.2.3)。
	此外，constexpr函数(§1.6)和static_asser函数(§3.5.5)也经常参与模板的设计和使用。
		这些基本机制主要是用于构建通用的、基础性的抽象的工具。

#####6.4.1 变量模板
	在使用类型时，我们通常需要该类型的常量和值。当然，当我们使用类模板时也是如此:当我们定义C时，我们通常需要类型为T的常量和变量，以及依赖于T的其他类型。下面是一个来自流体动力学模拟的例子[Garcia,2015]:
        template <class T>
        	constexpr T viscosity = 0.4;
        template <class T>
        	constexpr space_vector<T> external_acceleration = { T{}, T{−9.8}, T{} };
        auto vis2 = 2∗viscosity<double>;
        auto acc = external_acceleration<float>;
	这里，space_vector是一个三维向量。
		当然，我们可以使用合适类型的任意表达式作为初始化式。考虑:
        template<typename T, typename T2>
        	constexpr bool Assignable = is_assignable<T&,T2>::value; // is_assignable is a type trait (§13.9.1)
        template<typename T>
        void testing()
        {
            static_asser t(Assignable<T&,double>, "can't assign a double");
            static_asser t(Assignable<T&,string>, "can't assign a string");
        }
	经过一些重大的变化后，这一观点成为概念定义的核心(§7.2)。

#####6.4.2 别名
	通常，为类型或模板引入同义词是非常有用的。例如，标准头文件包含别名size_t的定义，可能:
		using size_t = unsigned int;
	实际名为size_t的类型依赖于实现，因此在另一个实现中size_t可能是无符号long。别名size_t允许程序员编写可移植的代码。
		参数化类型通常会为与其模板参数相关的类型提供别名。例如:
        template<typename T>
        class Vector {
        public:
            using value_type = T;
            // ...
        };
	事实上，每个标准库容器都提供value_type作为其值类型的名称(第11章)。这允许我们编写适用于每个遵循此约定的容器的代码。
	例如:
        template<typename C>
        using Value_type = typename C::value_type; // the type of C’s elements
        template<typename Container>
        void algo(Container& c)
        {
            Vector<Value_type<Container>> vec; // keep results here
            // ...
        }
	通过绑定部分或全部模板参数，可以使用别名机制来定义一个新模板。例如:
        template<typename Key, typename Value>
        class Map
        {
        	// ...
        };
        template<typename Value>
        using String_map = Map<string,Value>;
        String_map<int> m; // m is a Map<str ing,int>

#####6.4.3编译时if
	考虑编写可以使用两个操作之一的操作slow_and_safe(T)或simple_and_fast(T)。这样的问题在基本代码中比比皆是，这些代码的通用性和最优性能至关重要。传统的解决方案是编写一对重载函数，并根据特征(§13.9.1)选择最合适的函数，例如标准库is_pod。如果涉及到类层次结构，基类可以提供slow_and_safe通用操作，派生类可以使用simple_and_fast实现重写。
		在c++ 17中，我们可以使用编译时if:
        template<typename T>
        void update(T& target)
        {
            // ...
            if constexpr(is_pod<T>::value)
            	simple_and_fast(target); // for "plain old data"
            else
            	slow_and_safe(target);
            // ...
        }
	is_pod是一个类型特征(§13.9.1)，它告诉我们一个类型是否可以被轻松复制。
		只实例化if constexpr的选定分支。这种解决方案提供了最优的性能和优化的位置。
		重要的是，if constexpr不是一种文本操作机制，不能用来打破语法、类型和范围等常规规则。例如:
        template<typename T>
        void bad(T arg)
        {
            if constexpr(Something<T>::value)
            	try
                { / / syntax error
					g(arg);
            		if constexpr(Something<T>::value)
            	} catch(...) { /* ... */ } // syntax error
        }
	允许这样的文本操作可能会严重损害代码的可读性，并给依赖于现代程序表示技术的工具(如“抽象语法树”)带来问题。

####6.5 建议
    [1] 使用模板表示可应用于多种参数类型的算法;§6.1;[CG: T.2]。
    [2] 使用模板表达容器;§6.2;[CG: T.3]。
    [3] 使用模板提升代码的抽象级别;§6.2;[CG: T.1]。
    [4] 模板是类型安全的，但是检查太晚了;§6.2。
    [5] 让构造函数或函数模板推导类模板参数类型;§6.2.3。
    [6] 使用函数对象作为算法的参数;§6.3.2; [CG: T.40]。
    [7] 如果您只需要在一个地方放置一个简单的函数对象，则使用lambda;§6.3.2。
    [8] 虚函数成员不能是模板成员函数;§6.3.1。
    [9] 使用模板别名简化表示法，隐藏实现细节;§6.4.2。
    [10] 要使用模板，请确保它的定义(不仅仅是声明)在作用域中;§7.5。
    [11] 模板提供编译时的" duck typing ";§7.5。
    [12] 不需要单独编译模板:#在每个使用模板的翻译单元中包含模板定义。

___
###7 概念和泛型编程
	Programming: you have to start with interesting algorithms.	– Alex Stepanov
    • 介绍
    • 概念
        使用的概念;基于概念的重载；;有效代码;概念的定义
    • 泛型编程
        使用的概念;抽象使用模板
    • 可变参数模板
        折叠表达式;传递参数
    • 模板编译模型
    • 建议

####7.1 介绍
	模板有什么用？ 换句话说，当您使用模板时，哪些编程技术是有效的？ 模板提供：
        • 能够传递类型(以及值和模板)作为参数而不丢失信息。这意味着内联有很好的机会，目前的实现充分利用了内联的优势。
        • 有机会在实例化时将来自不同上下文的信息编织在一起。这意味着优化机会。
        • 能够传递常量值作为参数。这意味着可以进行编译时计算。
	换句话说，模板为编译时计算和类型操作提供了强大的机制，可以生成非常紧凑和高效的代码。记住，类型(类)可以同时包含代码(§6.3.2)和值(§6.2.2)。
		模板的第一个用途也是最常见的用途是支持泛型编程，即专注于通用算法的设计、实现和使用的编程。这里，“通用”意味着一个算法可以被设计成接受各种各样的类型，只要它们满足算法对参数的要求。连同概念，模板是c++对泛型编程的主要支持。模板提供(编译时)参数多态性。

####7.2 概念(C + + 20)
	考虑§6.3.1中的sum():
        template<typename Seq, typename Num>
        Num sum(Seq s, Num v)
        {
            for (const auto& x : s)
            	v+=x;
            return v;
        }
	任何支持begin()和end()的数据结构都可以调用它，这样range-for就可以工作了。这样的结构包括标准库的vector、list和map。此外，数据结构的元素类型仅受其用途的限制:它必须是可以添加到Value参数中的类型。例如int、double和Matrix(对于任何合理的Matrix定义)。可以说sum()算法在两个维度上是泛型的:用于存储元素的数据结构的类型(“序列”)和元素的类型。
		所以sum()要求它的第一个模板参数是某种序列，而它的第二个模板参数是某种数字。我们将这种需求称为概念。
		对概念的语言支持还没有ISO c++，但它是一个ISO技术规范[ConceptsTS]。实现正在使用中，所以我冒险在这里推荐它，尽管细节可能会发生变化，而且在生产代码中使用它可能需要数年时间。

####7.2.1 概念的使用
	大多数模板参数必须满足特定的要求，才能正确编译模板，生成的代码才能正常工作。也就是说，大多数模板必须是受约束的模板(§6.2.1)。类型名称导入器typename是约束最少的，只要求参数是类型。通常我们可以做得更好。再次考虑sum():
        template<Sequence Seq, Number Num>
        Num sum(Seq s, Num v)
        {
            for (const auto& x : s)
                v+=x;
            return v;
        }
	这是更清晰。一旦我们定义了Sequence和Number这两个概念的含义，编译器就可以通过只查看sum()的接口而不是查看其实现来拒绝错误的调用。这改进了错误报告。
		然而，sum()接口的规范并不完整:我“忘了”说我们应该能够将Sequence元素添加到Number中。我们可以这样做:
        template<Sequence Seq, Number Num>
        	requires Arithmetic<Value_type<Seq>,Num>
        Num sum(Seq s, Num n);
    序列的Value_type是序列中元素的类型。 Arithmetic<X,Y>是一个概念，指定我们可以用X和Y类型的数量进行算术运算。这使我们免于意外地尝试计算 vector<string> 或 vector<int∗> 的 sum()，同时仍然接受 vector<int> 和 vector<complex<double>>。
		在这个例子中，我们只需要+=，但是为了简单和灵活，我们不应该把模板参数约束得太紧。特别是，我们可能有一天想要用+和=而不是+=来表示sum()，然后我们会很高兴我们使用了一个普遍的概念(这里是算术)，而不是“有+=”的狭窄要求。
		部分规范(如第一个使用概念的sum())可能非常有用。除非规范已经完成，否则直到实例化时才会发现一些错误。然而，部分规范可以提供很多帮助，表达意图，并且对于平稳的增量开发是必要的，因为我们最初并没有认识到我们需要的所有需求。有了成熟的概念库，初始的规范将接近完美。
        不出所料， requires Arithmetic<Value_type<Seq>,Num> 被称为需求子句。 template<Sequence Seq> 表示法只是显式使用 requires Sequence<Seq> 的简写。如果我喜欢冗长，我可以等效地写
        template<typename Seq, typename Num>
        	requires Sequence<Seq> && Number<Num> && Arithmetic<Value_type<Seq>,Num>
        Num sum(Seq s, Num n);
	另一方面，我们也可以利用这两种符号之间的等价性来写:
        template<Sequence Seq, Arithmetic<Value_type<Seq>> Num>
        Num sum(Seq s, Num n);
	在我们还不能使用概念的地方，我们不得不使用命名惯例和注释，例如:
        template<typename Sequence, typename Number>
        	// requires Arithmetic<Value_type<Sequence>,Number>
        Numer sum(Sequence s, Number n);
	无论我们选择什么表示法，设计一个对参数有语义意义约束的模板是很重要的(§7.2.4)。

#####7.2.2 基于概念的重载
	一旦我们正确地指定了模板及其接口，我们就可以根据它们的属性进行重载，就像对函数所做的那样。考虑一个稍微简化的标准库函数advance()，它将迭代器向前推进(§12.3):
        template<Forward_iterator Iter>
        void advance(Iter p, int n) // move p n elements forward
        {
        	while (n−−)
        		++p; // a forward iterator has ++, but not + or +=
        }
        template<Random_access_iterator Iter>
        void advance(Iter p, int n) // move p n elements forward
        {
        	p+=n; // a random-access iterator has +=
        }
	编译器将选择参数满足最强要求的模板。在这种情况下，list只提供前向迭代器，而vector提供随机访问迭代器，因此得到:
        void user(vector<int>::iterator vip, list<string>::iterator lsp)
        {
            advance(vip,10); // use the fast advance()
            advance(lsp,10); // use the slow advance()
        }
	与其他重载一样，这是一种编译时机制，意味着没有运行时成本，当编译器没有找到最佳选择时，它会产生歧义错误。基于概念的重载的规则比一般重载的规则要简单得多(§1.3)。首先考虑几个可选函数的单个参数:
            • 如果论点与概念不匹配，就不能选择替代方案。
            • 如果参数匹配的概念只有一个选项，该选项被选中。
            • 如果两个备选项的论点都能很好地匹配一个概念，那么我们就有了歧义。
            • 如果来自两个选项的参数匹配一个概念，并且其中一个比另一个更严格(匹配另一个或更多的所有要求)，该选项被选中。
        对于一个选择它必须是
            • 匹配其所有的论点，并且
            • 至少是一个同样好的匹配所有的论点作为其他的替代品，并且
            • 一个更好的匹配至少一个论点。

#####7.2.3 有效代码
	一组模板实参是否提供了模板对其模板形参的要求，这个问题最终归结为一些表达式是否有效。
		使用require表达式，我们可以检查一组表达式是否有效。例如:
        template<Forward_iterator Iter>
        void advance(Iter p, int n) // move p n elements forward
        {
            while (n−−)
                ++p; // a forward iterator has ++, but not + or +=
        }
        template<Forward_iterator Iter, int n>
        requires requires(Iter p, int i) { p[i]; p+i; } // Iter has subscripting and addition
        void advance(Iter p, int n) // move p n elements forward
        {
        	p+=n; // a random-access iterator has +=
        }
	不，这不是拼写错误。第一个require启动了requirements-子句，第二个require启动了requires−表达式
		requires(Iter p, int i) { p[i]; p+i; }
	A require - expression是一个谓词，如果其中的语句是有效代码，则为真，否则为假。
		我认为需求表达式是泛型编程的汇编代码。与普通的汇编代码一样，需求表达式非常灵活，不需要任何编程规则。
	以某种形式，它们位于最有趣的泛型代码的底部，就像汇编代码位于最有趣的普通代码的底部一样。与汇编代码一样，需求表达式不应该出现在“普通代码”中。“如果你在你的代码中看到需求，它可能是低级别的。
		require require in advance()的使用故意显得不优雅和粗俗。注意，我“忘记”为操作指定+=和所需的返回类型。你已经被警告过了!选择名称表明其语义含义的命名概念。
		喜欢使用正确命名的概念和明确的语义(§7.2.4)，并在这些概念的定义中使用需求表达式。

#####7.2.4 概念定义
	最终，我们希望找到有用的概念，例如库中的序列和算术，包括标准库。Ranges技术规范[RangesTS]已经提供了一套约束标准库算法的集合(§12.7)。然而，简单的概念并不难定义。
		概念是指定如何使用一种或多种类型的编译时谓词。首先来看一个最简单的例子:
        template<typename T>
        concept Equality_comparable =
            requires (T a, T b) {
                { a = = b } − > bool; // compare Ts with ==
                { a ! = b } − > bool; // compare Ts with !=
            };
	Equality_comparable是用来确保可以比较相等和不相等类型的值的概念。我们简单地说，给定该类型的两个值，它们必须使用==和!=进行比较，并且这些操作的结果必须可转换为bool类型。例如:
        static_asser t(Equality_comparable<int>); // succeeds
        struct S { int a; };
        static_asser t(Equality_comparable<S>); // fails because structs don’t automatically get == and !=
	概念Equality_comparable的定义完全等同于英文描述，不再。概念的值总是bool。
		定义Equality_comparable来处理非齐次比较几乎同样简单:
        template<typename T, typename T2 =T>
        concept Equality_comparable =
            requires (T a, T2 b) {
                { a = = b } − > bool; // compare a T to a T2 with ==
                { a ! = b } − > bool; // compare a T to a T2 with !=
                { b = = a } − > bool; // compare a T2 to a T with ==
                { b ! = a } − > bool; // compare a T2 to a T with !=
        };
	typename T2 =T表示，如果我们不指定第二个模板参数，T2将与T相同;T是一个默认模板参数。
		我们可以这样测试Equality_comparable:
		static_asser t(Equality_comparable<int,double>); // succeeds
        static_asser t(Equality_comparable<int>); // succeeds (T2 is defaulted to int)
        static_asser t(Equality_comparable<int,string>); // fails
	对于一个更复杂的例子，考虑一个序列:
        template<typename S>
        concept Sequence = requires(S a) {
            typename Value_type<S>; // S must have a value type.
            typename Iterator_type<S>; // S must have an iterator type.
            { begin(a) } −> Iterator_type<S>; // begin(a) must return an iterator
            { end(a) } −> Iterator_type<S>; // end(a) must return an iterator
            requires Same_type<Value_type<S>,Value_type<Iterator_type<S>>>;
            requires Input_iterator<Iterator_type<S>>;
        };
	如果S类型是Sequence类型，它必须提供Value_type(其元素的类型)和Iterator_type(其迭代器的类型;看到§12.1)。它还必须确保存在返回迭代器的begin()和end()函数，这是标准库容器的惯用方法(§11.3)。最后，Iterator_type实际上必须是与S元素类型相同的input_iterator。
		最难定义的概念是那些表示基本语言概念的概念。因此，最好使用来自已建立库的集合。关于有用的集合，见§12.7。

####7.3 泛型编程
	c++支持的泛型编程的形式是围绕着从具体的、高效的算法中抽象出来的思想，以获得可以与不同的数据表示相结合的泛型算法，从而产生各种各样的有用软件[Stepanov,2009]。表示基本操作和数据结构的抽象称为概念;它们作为模板参数的要求出现。

#####7.3.1 概念的使用
	好的、有用的概念是基本的，发现比设计更多。示例包括整数和浮点数(甚至在经典C中也有定义)、序列以及更一般的数学概念，如场和向量空间。它们代表了一个应用领域的基本概念。这就是为什么它们被称为“概念”。“识别和形式化概念到有效的泛型编程的必要程度可能是一项挑战。
		对于基本的使用，考虑常规的概念(§12.7)。当类型表现得很像int或vector时，它就是规则类型。常规类型的对象
        •可以默认构造。
        •可以使用构造函数或赋值进行复制(使用通常的copy语义，产生两个独立且比较相等的对象)。
        •可以用==和!=进行比较。
        •不会因为过于聪明的编程技巧而出现技术问题。
	字符串是常规类型的另一个例子。和int一样，string也是strictttotallorderdered(§12.7)。
	也就是说，可以使用具有适当语义的<、<=、>和>=来比较两个字符串。
		概念不仅仅是一个句法概念，它从根本上是关于语义的。例如，不要把+定义为除;这将不符合任何合理数字的要求。不幸的是，我们还没有任何语言支持来表示语义，因此我们必须依靠专家知识和常识来获得语义上有意义的概念。不要定义语义上没有意义的概念，比如可加和可减的概念。相反，要依赖领域知识来定义与应用程序领域中的基本概念相匹配的概念。

#####7.3.2 使用模板抽象
	好的抽象是从具体的例子中精心产生的。试图通过准备每一种可能的需求和技术来“抽象”并不是一个好主意;在这个方向上存在着不优雅和代码膨胀。相反，从一个——最好是更多——实际使用的具体例子开始，并尽量消除不必要的细节。考虑:
        double sum(const vector<int>& v)
        {
            double res = 0;
            for (auto x : v)
            	res += x;
            return res;
        }
	这显然是计算一串数字和的许多方法之一。
		考虑是什么让这段代码变得不那么通用:
        • 为什么只使用整数?
        • 为什么是向量?
        • 为什么要积累成double?
        • 为什么从0开始?
        • 为什么添加?
	通过将具体类型放入模板参数来回答前四个问题，我们得到了标准库accumulate算法的最简单形式:
        template<typename Iter, typename Val>
        Val accumulate(Iter first, Iter last, Val res)
        {
            for (auto p = first; p!=last; ++p)
            	res += ∗p;
            return res;
        }
	在这里,我们有:
        • 要遍历的数据结构被抽象为一对表示序列的迭代器(§12.1)。
        • 蓄电池的类型已做成参数。
        • 初始值现在是一个输入;累加器的类型就是这个初始值的类型。
	一个快速的检查或者更好的测量将显示，为使用各种数据结构的调用生成的代码与您从手工编码的原始示例中得到的代码是相同的。
	例如:
        void use(const vector<int>& vec, const list<double>& lst)
        {
            auto sum = accumulate(begin(vec),end(vec),0.0); // accumulate in a double
            auto sum2 = accumulate(begin(lst),end(lst),sum);
            //
        }
	在保持性能的同时，从一段具体代码(最好是从几段代码)泛化的过程称为提升。相反，开发模板的最佳方法通常是
        • 首先，写一个具体的版本
        • 然后，调试、测试和测量它
        • 最后，用模板参数替换具体类型。
	当然，begin()和end()的重复是很乏味的，所以我们可以稍微简化一下用户界面:
        template<Rang e R, Number Val> // a Range is something with begin() and end()
        Val accumulate(const R& r, Val res = 0)
        {
            for (auto p = begin(r); p!=end(r); ++p)
            	res += ∗p;
            return res;
        }
    为了完全一般化，我们还可以抽象+=操作;看到§14.3。

####7.4 可变模板
	模板可以被定义为接受任意类型的任意数量的参数。这样的模板被称为可变参数模板。考虑这样一个简单的函数，它可以写出带有<<操作符的任何类型的值:
        void user()
        {
            print("first: ", 1, 2.2, "hello\n"s); // first: 1 2.2 hello
            print("\nsecond: ", 0.2, 'c', "yuck!"s, 0, 1, 2, '\n'); // second: 0.2 c yuck! 0 1 2
        }
	传统上，实现可变参数模板是将第一个参数从其他参数中分离出来，然后递归地调用可变参数模板来获取参数的尾部:
        void print()
        {
        	// what we do for no arguments: nothing
        }
        template<typename T, typename ... Tail>
        void print(T head, Tail... tail)
        {
        	// what we do for each argument, e.g.,
        	cout << head << ' ';
        	print(tail...);
        }
	typename……表示Tail是一个类型序列。尾巴……表示tail是tail中类型的值的序列。用…声明的参数。称为参数包。这里，tail是一个(函数参数)形参包，其中的元素类型与(模板参数)形参包tail中的元素类型相同。因此，print()可以接受任意类型的任意数量的参数。
	调用print()将参数分离为头(第一个)和尾(其余)。打印头部，然后对尾部调用print()。当然，tail最终会变成空的，所以我们需要print()的无参数版本来处理它。如果我们不想允许零参数的情况，可以使用编译时语句消除print():
        template<typename T, typename ... Tail>
        void print(T head, Tail... tail)
        {
            cout << head << ' ';
            if constexpr(siz eof...(tail)> 0)
            	print(tail...);
        }
	我使用了编译时的if(§6.4.3)，而不是普通的运行时if，以避免生成从未调用的final、call print()。
		可变参数模板(有时也被称为variadics)的优点是它们可以接受您想给它们的任何参数。缺点包括
        • 递归实现可能很难做好。
        • 递归实现在编译时可能会非常昂贵。
        • 接口的类型检查可能是一个精心设计的模板程序。
	由于其灵活性，可变参数模板在标准库中被广泛使用，有时被过度使用。

#####7.4.1 折叠表达式
	为了简化简单可变参数模板的实现，c++ 17提供了对参数包元素的有限迭代形式。例如:
        template<Number... T>
        int sum(T... v)
        {
        	return (v + ... + 0); // add all elements of v starting with 0
        }
	这里，sum()可以接受任意类型的任意数量的参数。假设sum()确实添加了它的参数，我们得到:
        int x = sum(1, 2, 3, 4, 5); // x becomes 15
        int y = sum('a', 2.4, x); // y becomes 114 (2.4 is truncated and the value of ’a’ is 97)
	sum函数体使用了一个fold表达式:
		return (v + ... + 0); // add all elements of v to 0
	这里，(v+…+0)表示将v中从初始值0开始的所有元素相加。要添加的第一个元素是“最右”的元素(即索引最高的元素):(v[0]+(v[1]+(v[2]+(v[3]+(v[4]+0)))))。也就是说，从右边0的位置开始。它被称为右折。或者，我们可以使用左折:
        template<Number... T>
        int sum2(T... v)
        {
            return (0 + ... + v); // add all elements of v to 0
        }
	现在，要添加的第一个元素是“最左边”(索引最低的一个):(((((0+v[0])+v[1])+v[2])+v[3])+v[4])。也就是说，从0所在的左边开始。
		Fold是一个非常强大的抽象，显然与标准库accumulate()有关，在不同的语言和社区中有各种各样的名称。在c++中，目前对fold表达式的限制是为了简化可变参数模板的实现。折叠不需要执行数值计算。举一个著名的例子:
	template<typename ...T>
    void print(T&&... args)
    {
    	(std::cout << ... << args) << '\n'; // pr int all arguments
    }
    print("Hello!"s,' ',"World ",2017); // (((((std::cout << "Hello!"s) << ’ ’) << "Wor ld ") << 2017) << ’\n’);
	许多用例只涉及一组可以转换为通用类型的值。在这种情况下，简单地将实参复制到vector或所需类型通常会简化进一步的使用:
        template<typename Res, typename... Ts>
        vector<Res> to_vector(Ts&&... ts)
        {
            vector<Res> res;
            (res.push_back(ts) ...); // no initial value needed
            return res;
        }
	我们可以像这样使用to_vector:
        auto x = to_vector<double>(1,2,4.5,'a');
        template<typename ... Ts>
        int fct(Ts&&... ts)
        {
            auto args = to_vector<string>(ts...); // args[i] is the ith argument
            // ... use args here ...
        }
        int y = fct("foo", "bar", s);

#####7.4.2 传递参数
	通过接口传递不变的参数是可变参数模板的一个重要用途。考虑一个网络输入通道的概念，其中移动值的实际方法是一个参数。不同的传输机制有不同的构造函数参数集:
        template<typename Transpor t>
        	requires concepts::InputTranspor t<Transpor t>
        class InputChannel {
        public:
            // ...
            InputChannel(Transpor tArgs&&... transportArgs)
            	: _transpor t(std::forward<Transpor tArgs>(transpor tArgs)...)
            {}
            // ...
            Transpor t _transpor t;
        };
	标准库函数forward()(§13.2.2)用于将参数不变地从InputChannel构造函数移动到transport t构造函数。
		这里的要点是，InputChannel的编写者可以构造一个transport t类型的对象，而不需要知道构造一个特定的transport t需要什么参数。InputChannel的实现者只需要知道所有transport t对象的通用用户界面。
		转发在基础库中非常常见，这些库需要通用性和较低的运行时开销，非常通用的接口也很常见。

####7.5 模板编译模型
	假设有概念(§7.2)，模板的参数会根据它的概念进行检查。在这里发现的错误将被报告，程序员必须修复问题。在这一点上不能检查的，例如非约束模板参数的参数，被推迟到为模板和一组模板参数生成代码时:“在模板实例化时”。“对于概念之前的代码，这是所有类型检查发生的地方。在使用概念时，只有在概念验证成功后，我们才能到达这里。
		实例化时(后期)类型检查的一个不幸的副作用是，可能在很晚的时候发现类型错误，并导致非常糟糕的错误消息，因为编译器只有在组合了程序中几个地方的信息之后才发现问题。
		为模板提供的实例化时类型检查检查模板定义中参数的使用情况。这提供了通常被称为鸭子类型的编译时变体(“如果它像鸭子一样走路，它像鸭子一样呱呱叫，它就是鸭子”)。或者——使用更专业的术语——我们对值进行操作，操作的存在和意义完全取决于它的操作数值。这与另一种观点不同，即对象具有类型，类型决定操作的存在和意义。V在对象中赋值" live "。这就是c++中对象(例如变量)工作的方式，只有满足对象要求的值才能放入对象中。在编译时使用模板所做的大多不涉及对象，只涉及值。唯一的例外是在constexpr函数(§1.6)中作为编译器内部对象使用的局部变量。
		要使用不受约束的模板，它的定义(不仅仅是声明)必须在使用点的作用域中。例如，标准头文件保存vector的定义。在实践中，这意味着模板定义通常在头文件中找到，而不是.cpp文件。当我们开始使用模块(§3.3)时，这种情况发生了改变。通过使用模块，源代码的组织方式与普通函数和模板函数相同。在这两种情况下，定义都不会受到文本包含问题的影响。


####7.6 建议
    [1] 模板为编译时编程提供了一种通用机制;§7.1。
    [2] 在设计模板时，仔细考虑模板参数所假定的概念(需求);§7.3.2。
    [3] 在设计模板时，使用具体版本进行初始实现、调试和测量;§7.3.2。
    [4] 将概念作为设计工具;§7.2.1。
    [5] 为所有模板参数指定概念;§7.2;[CG: T.10]。
    [6] 尽可能使用标准概念(例如，Ranges概念);§7.2.4;[CG: T.11]。
    [7] 如果您只需要在一个地方放置一个简单的函数对象，则使用lambda;§6.3.2。
    [8] 不需要单独编译模板:#在每个使用模板的翻译单元中包含模板定义。
    [9] 使用模板表示容器和范围;§7.3.2;[CG: T.3]。
    [10] 避免没有意义语义的“概念”;§7.2;[CG: T.20]。
    [11] 对一个概念要求一组完整的操作;§7.2;[CG: T.21]。
    [12] 当你需要一个函数接受各种类型的可变数量的参数时，使用可变参数模板;§7.4。
    [13] 不要在同构参数列表中使用可变参数模板(首选初始化器列表);§7.4。
    [14] 要使用模板，请确保它的定义(不仅仅是声明)在作用域中;§7.5。
    [15] 模板提供编译时的" duck typing ";§7.5。

___
###8 关于库的预览
	Why waste time learning when ignorance is instantaneous?	– Hobbes
    • 介绍
    • 标准库组件
    • 标准库头和命名空间
    • 建议

####8.1 介绍
	没有任何重要的程序是只用一种简单的编程语言编写的。首先，开发一套库。这些构成了进一步工作的基础。大多数程序用简单的语言编写都是很乏味的，而几乎任何任务都可以通过使用好的库变得简单。
		从第1-7章继续，第9-15章快速浏览了关键的标准库设施。我非常简要地介绍了一些有用的标准库类型，如string、ostream、variant、vector、map、path、unique_ptr、thread、regex和complex，以及使用它们的最常见方法。
		正如第1-7章所述，强烈建议您不要因为对细节的不完全理解而分心或气馁。本章的目的是让读者对最有用的图书馆设施有一个基本的了解。
		本书中描述的标准库设施是每一个完整的c++实现的一部分。除了标准库组件之外，大多数实现还提供“图形用户界面”系统(gui)、Web界面、数据库界面等。类似地，大多数应用程序开发环境为企业或工业“标准”开发和/或执行环境提供了“基础库”。在这里，我不描述这样的系统和库。
		目的是提供标准定义的自包含的c++描述，并保持示例的可移植性。当然，我们鼓励程序员探索大多数系统上可用的更广泛的工具。

####8.2 标准库组件
	标准库提供的设施可以这样分类:
        • 运行时语言支持(例如，分配和运行时类型信息)。
        • C标准库(通过非常小的修改来最小化类型系统的冲突)。
        • 字符串(支持国际字符集、本地化和只读子字符串视图);看到§9.2。
        • 支持正则表达式匹配;看到§9.4。
        • I/O流是一个可扩展的输入和输出框架，用户可以在其中添加自己的类型、流、缓冲策略、地区和字符集(第10章)。还有一个用于以可移植的方式操作文件系统的库(§10.10)。
        • 容器框架(如vector和map)和算法(如find()、sort()和merge());参见第11章和第12章。这个框架通常被称为STL [Stepanov,1994]，是可扩展的，因此用户可以添加他们自己的容器和算法。
        • 支持数值计算(如标准数学函数，复数，算术运算向量，随机数生成器);参见§4.2.1和第14章。
        • 支持并发编程，包括线程和锁;看到第15章。并发支持是基础性的，因此用户可以将对新并发模型的支持添加为库。
        • 大多数STL算法和一些数值算法(如sor t()和reduce())的并行版本;见§12.9和§14.3.1。
        • 支持模板元编程的实用程序(例如，类型特征;§13.9)，stl风格的通用编程(例如，pair;§13.4.3)，通用规划(例如，可变和可选;§13.5.1、§13.5.2)和时钟(§13.7)。
        • 支持高效安全的通用资源管理，外加一个可选垃圾收集器的接口(§5.3)。
        • 用于资源管理的“智能指针”(例如，unique_ptr和shared_ptr;§13.2.1)。
        • 特殊用途的容器，如数组(§13.4.1)、bitset(§13.4.2)和元组(§13.4.3)。
        • 常用单位的后缀，例如ms表示毫秒，i表示虚数(§5.4.4)。

	在库中包含一个类的主要标准是:
        • 它可以帮助几乎每一个c++程序员(新手和专家)，
        • 它可以以一种通用的形式提供，与相同设施的简单版本相比，不会增加显著的开销，并且
        • 简单的用法应该容易学习(相对于其任务的固有复杂性)。

基本上，c++标准库提供了最常见的基本数据结构以及在这些结构上使用的基本算法。

####8.3 标准库头文件和命名空间
	每个标准库设施都是通过一些标准头文件提供的。例如:
        #include<string>
        #include<list>
	这使得标准字符串和列表可用。
		标准库定义在一个名为std的命名空间(§3.4)中，要使用标准库的功能，可以使用std::前缀:
        std::string sheep {"Four legs Good; two legs Baaad!"};
        std::list<std::string> slogans {"War is Peace", "Freedom is Slavery", "Ignorance is Strength"};
	为简单起见，我很少在示例中显式地使用std::前缀。我也不会总是显式地#include必要的头文件。要在这里编译和运行程序片段，必须#include包含适当的头文件，并使它们声明的名称可访问。例如:
        #include<string> // make the standard string facilities accessible
        using namespace std; // make std names available without std:: prefix
		string s {"C++ is a general−purpose programming language"}; // OK: string is std::string
	将名称空间中的每个名称都转储到全局名称空间中通常是不明智的做法。
	然而，在这本书中，我只使用标准库，最好知道它提供了什么。
		下面是一些标准库头文件的选择，它们都在命名空间std中提供声明:

    选择的标准库头文件
    <algorithm>       copy(), find(), sort()                        Chapter 12
    <array>           array                                         §13.4.1
    <chrono>          duration, time_point                          §13.7
    <cmath>           sqrt(), pow()                                 §14.2
    <complex>         complex, sqr t(), pow()                       §14.4
    <filesystem>      path                                          §10.10
    <forward_list>    forward_list                                  §11.6
    <fstream>         fstream, ifstream, ofstream                   §10.7
    <future>          future, promise                               §15.7
    <ios>             hex, dec, scientific, fixed, defaultfloat     §10.6
    <iostream>        istream, ostream, cin, cout                   Chapter 10
    <map>             map, multimap                                 §11.5
    <memory>          unique_ptr, shared_ptr, allocator             §13.2.1
    <random>          default_random_engine, normal_distribution    §14.5
    <regex>           regex, smatch                                 §9.4
    <string>          string, basic_string                          §9.2
    <set>             set, multiset                                 §11.6
    <sstream>         istringstream, ostringstream                  §10.8
	<stdexcept>       length_error, out_of_rang e, runtime_error    §3.5.1
	<thread>          thread                                        §15.2
	<unordered_map>   unordered_map, unordered_multimap             §11.5
	<utility>         move(), swap(), pair                          Chapter 13
	<variant>         variant                                       §13.5.1
	<vector>          vector                                        §11.2
	这个清单还远远不够。
		C标准库中的头文件，例如提供了<stdlib.h>。对于每个这样的头文件，都有一个以c为前缀的版本，并删除了.h。这个版本，例如<cstdlib>在std 命名空间替换了它的声明。

####8.4 建议
	[1] 不要白费力气;使用库;§8.1;CG:SL.1.]。
	[2] 如果可以选择，首选标准库而不是其他库;§8.1;[CG: SL.2]。
	[3] 不要认为标准库是一切的理想选择;§8.1。
	[4] 记得包含您使用的设施的头文件;§8.3。
	[5] 记住，标准库设施是在命名空间std中定义的;§8.3;[CG: SL.3]。

___
###9 字符串和正则表达式
	Prefer the standard to the offbeat.	– Strunk & White
	•介绍
	•字符串
		字符串的实现;
	•字符串视图
	•正则表达式
		搜索;正则表达式的符号;迭代器
	•建议

####9.1 介绍
	文本操作是大多数程序的主要部分。c++标准库提供了一个字符串类型，使大多数用户不必通过指针操作C风格的字符数组。string_view类型允许我们以任意方式操作字符序列(例如，在std::string或char[]中)。此外，还提供正则表达式匹配来帮助查找文本中的模式。正则表达式的提供形式与大多数现代语言中常见的形式类似。字符串和regex对象都可以使用各种字符类型(例如Unicode)。

####9.2 字符串
	标准库提供了一个string类型来补充string字面量(§1.2.1);string是一个Regular类型(§7.2，§12.7)，用于拥有和操作各种字符类型的字符序列。string类型提供了各种有用的字符串操作，例如连接。例如:
		string compose(const string& name, const string& domain)
		{
			return name + '@' + domain;
		}
		auto addr = compose("dmr","bell−labs.com");
	此处addr初始化为字符序列dmr@bell−labs.com。字符串的“加法”意味着连接。你可以连接一个字符串，一个字符串字面值，一个c风格的字符串，或一个字符到一个字符串。标准字符串有一个move构造函数，因此即使按值返回较长的字符串也很有效(§5.2.2)。
		在许多应用程序中，最常见的连接形式是在字符串末尾添加内容。这由+=操作直接支持。例如:
		void m2(string& s1, string& s2)
		{
			s1 = s1 + '\n'; // append newline
			s2 += '\n'; // append newline
		}
	在字符串末尾进行添加的两种方法在语义上是相同的，但我更喜欢后者，因为它更明确地说明它所做的事情，更简洁，而且可能更有效。
		字符串是可变的。除了=和+=之外，还支持下标(使用[])和子字符串操作。例如:
		string name = "Niels Stroustrup";
		void m3()
		{
			string s = name.substr(6,10); // s = "Stroustrup"
			name.replace(0,5,"nicholas"); // name becomes "nicholas Stroustrup"
			name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup"
		}
	substr()操作返回一个字符串，该字符串是由其参数指定的子字符串的副本。
	第一个参数是字符串的索引(位置)，第二个参数是所需子字符串的长度。由于索引从0开始，s的值为Stroustrup。
		replace()操作将子字符串替换为值。在本例中，从0开始、长度为5的子字符串是Niels;取而代之的是nicholas。最后，我将初始字符替换为大写的等效字符。因此，name的最终值是Nicholas Stroustrup。请注意，替换字符串的大小不需要与它要替换的子字符串相同。
		在许多有用的字符串操作中，赋值(使用=)，下标(使用[]或at();§11.2.2)、比较(使用==和!=)、字典排序(使用<、<=、>和>=)、迭代(使用迭代器作为vector;§12.2)、输入(§10.3)和流(§10.8)。
		当然，字符串可以相互比较，与c风格的字符串§1.7.1进行比较，也可以与字符串字面量进行比较。例如:
		string incantation;
		void respond(const string& answer)
		{
			if (answer == incantation) {
			// perform magic
			}
			else if (answer == "yes") {
				// ...
			}
			// ...
		}
	如果您需要一个c风格的字符串(以零结尾的字符数组)，string提供对其包含的字符的只读访问。例如:
		void print(const string& s)
		{
			printf("For people who like printf: %s\n",s.c_str()); // s.c_str() returns a pointer to s’ characters
			cout << "For people who like streams: " << s << '\n';
		}
	根据定义，字符串字面值是一个const char *。要获得std::string类型的文字量，使用s后缀。例如:
		auto s = "Cat"s; // a std::str ing
		auto p = "Dog"; // a C-style string: a const char*
	要使用s后缀，需要使用命名空间std::literals::string_literals(§5.4.4)。

#####9.2.1字符串实现
	实现字符串类是一个流行而有用的练习。然而，对于一般用途，我们精心设计的第一次尝试在便利性或性能方面很少与标准字符串匹配。
	现在，字符串通常使用短字符串优化来实现。也就是说，短字符串值保存在string对象本身中，只有较长的字符串被放置在自由存储中。考虑:
		string s1 {"Annemarie"}; // shor t string
		string s2 {"Annemarie Stroustrup"}; // long string
	当一个字符串的值从短字符串变为长字符串时(反之亦然)，它的表示形式会相应调整。一个“短”字符串可以有多少个字符?这是实现定义的，但“大约14个字符”是一个不错的猜测。
		字符串的实际性能很大程度上取决于运行时环境。特别是，在多线程实现中，内存分配可能会相对昂贵。此外，当使用许多不同长度的字符串时，可能会导致内存碎片。这些都是短字符串优化变得普遍的主要原因。
		要处理多个字符集，string实际上是一个通用模板basic_string的别名，其字符类型为char:
		template<typename Char>
		class basic_string {
			// ... string of Char ...
		};
		using string = basic_string<char>;
	用户可以定义任意字符类型的字符串。例如，假设我们有一个日文字符类型Jchar，我们可以这样写:
		using Jstring = basic_string<Jchar>;
	现在，我们可以对Jstring(一串日文字符)进行所有常见的字符串操作。

####9.3 字符串视图
	字符序列最常见的用法是将其传递给某个函数来读取。这可以通过按值传递字符串、对字符串的引用或c风格字符串来实现。在许多系统中还有其他选择，比如标准不提供的字符串类型。在所有这些情况下，当我们想要传递子字符串时，会有额外的复杂性。为了解决这个问题，标准库提供了string_view;string_view基本上是一个(指针，长度)对，表示一个字符序列:
	string_view提供了对连续字符序列的访问。字符可以以多种方式存储，包括字符串和c风格字符串。string_view就像一个指针或引用，它不拥有它所指向的字符。在这一点上，它类似于STL的一对迭代器(§12.3)。
		考虑一个连接两个字符串的简单函数:
		string cat(string_view sv1, string_view sv2)
		{
			string res(sv1.length()+sv2.length());
			char∗ p = &res[0];
			for (char c : sv1) // one way to copy
				∗p++ = c;
			copy(sv2.begin(),sv2.end(),p); // another way
			return res;
		}
	我们可以将其命名为cat():
		string king = "Harold";
		auto s1 = cat(king,"William"); // string and const char*
		auto s2 = cat(king,king); // string and string
		auto s3 = cat("Edward","Stephen"sv); // const char * and string_view
		auto s4 = cat("Canute"sv,king);
		auto s5 = cat({&king[0],2},"Henry"sv); // HaHenry
		auto s6 = cat({&king[0],2},{&king[2],4}); // Harold
	与接受const字符串和参数(§9.2)的compose()相比，cat()有三个优点:
		•它可以用于以许多不同的方式管理字符序列。
		•不为c风格的字符串参数创建临时字符串参数。
		•我们可以轻松地传递子字符串。
	注意使用了sv(“字符串视图”)后缀。我们需要利用它
		using namespace std::literals::string_view_literals; // §5.4.4
	何苦呢?原因是当我们传递"Edward"时，我们需要用一个* const char构造一个string_view，这需要计算字符数。对于"Stephen"sv，长度在编译时计算。
		返回string_view时，记住它很像指针;它需要指向一些东西:
		string_view bad()
		{
			string s = "Once upon a time";
			return {&s[5],4}; // bad: returning a pointer to a local
		}
	返回一个指向字符串字符的指针，在使用这些字符之前，该指针将被销毁。
		string_view的一个重要限制是它是其字符的只读视图。例如，不能使用string_view向将参数修改为小写的函数传递字符。为此，你可以考虑使用gsl::span或gsl::string_span(§13.3)。
		string_view的越界访问行为未指定。如果你想要保证范围检查，可以使用at()，它会抛出out_of_range，也可以使用gsl::string_span(§13.3)，或者“只是要小心”。

####9.4 正则表达式
	正则表达式是文本处理的强大工具。它们提供了一种简单而简洁地用文本描述模式的方法(例如，美国邮政编码，如TX 77845，或iso风格的日期，如2009−06−07)，并有效地找到这种模式。在<regex>中，标准库以std::regex类及其支持函数的形式提供对正则表达式的支持。为了体验一下regex库的风格，让我们定义并打印一个模式:
		regex pat {R"(\w{2}\s∗\d{5}(−\d{4})?)"}; // U.S. postal code pattern: XXddddd-dddd and variants
	在任何语言中使用过正则表达式的人都会发现* w{2}\s∗\d{5}(−\d{4})?熟悉。它指定了一个模式，以两个字母开始，可选地后跟一些空格* *，后跟五位数\d{5}，可选地后跟一个破折号和四位数−\d{4}。如果你不熟悉正则表达式，这可能是了解它们的好时机([Stroustrup,2009]， [Maddock,2009]， [Friedl,1997])。
		为了表示该模式，我使用了以R"(以)"开头的原始字符串字面量。这允许在字符串中直接使用反斜杠和引号。原始字符串特别适合用于正则表达式，因为它们往往包含大量反斜杠。如果我使用传统的字符串，模式定义将是:
		regex pat {"\\w{2}\\s∗\\d{5}(−\\d{4})?"}; // U.S. postal code pattern
	在<regex>中，标准库提供了对正则表达式的支持:
		•regex_match():将正则表达式与字符串(已知长度)进行匹配(§9.4.2)。
		•regex_search():在(任意长的)数据流(§9.4.1)中搜索匹配正则表达式的字符串。
		•regex_replace():在任意长的数据流中搜索匹配正则表达式的字符串并替换它们。
		•regex_iterator:迭代匹配和子匹配(§9.4.3)。
		•regex_token_iterator:迭代非匹配项。

#####9.4.1 搜索
	使用模式最简单的方法是在流中搜索它:
		int lineno = 0;
		for (string line; getline(cin,line); ) { // read into line buffer
			++lineno;
			smatch matches; // matched strings go here
			if (regex_search(line,matches,pat)) // search for pat in line
				cout << lineno << ": " << matches[0] << '\n';
		}
	regex_search(line,matches,pat)在该行中搜索与存储在pat中的正则表达式匹配的任何内容，如果找到任何匹配，则将它们存储在matches中。如果没有找到匹配，regex_search(line,matches,pat)返回false。matches变量的类型为smatch。“s”代表“sub”或“string”，而smatch是字符串类型的子匹配向量。这里匹配[0]的第一个元素是完全匹配。regex_search()的结果是一个匹配的集合，通常表示为smatch:
		void use()
		{
			ifstream in("file.txt"); // input file
			if (!in) // check that the file was opened
				cerr << "no file\n";
			regex pat {R"(\w{2}\s∗\d{5}(−\d{4})?)"}; // U.S. postal code pattern
			int lineno = 0;
			for (string line; getline(in,line); ) {
				++lineno;
				smatch matches; // matched strings go here
				if (regex_search(line , matches, pat)) {
					cout << lineno << ": " << matches[0] << '\n'; // the complete match
					if (1<matches.siz e() && matches[1].matched) // if there is a sub-pattern
					// and if it is matched
						cout << "\t: " << matches[1] << '\n'; // submatch
				}
			}
		}
	该功能读取查找美国邮政编码的文件，如TX77845和DC 20500−0001。smatch类型是regex结果的容器。这里，匹配[0]是整个模式，匹配[1]是可选的四位子模式。
		换行符\n可以是模式的一部分，因此我们可以搜索多行模式。
	显然，如果我们想这样做，就不应该一次读取一行。
		正则表达式的语法和语义被设计成可以将正则表达式编译到状态机中以便高效执行[Cox,2007]。reg ex类型在运行时执行此编译。

#####9.4.2 正则表达式表示法
	regex库可以识别几种正则表达式表示法的变体。在这里，我使用默认表示法，这是ECMAScript(更常见的叫法是JavaScript)使用的ECMA标准的变体。
	正则表达式的语法基于具有特殊含义的字符:

	正则表达式特殊字符
	.   Any single character (a ‘‘wildcard’’)
	[   Begin character class
	]   End character class
	{   Begin count
	}   End count
	(   Begin grouping
	)   End grouping
	\   Next character has a special meaning
	∗   Zero or more (suffix operation)
	+   One or more (suffix operation)
	?   Optional (zero or one) (suffix operation)
	|   Alternative (or)
	ˆ   Start of line; negation
	$   End of line

	例如，我们可以指定一行以零个或多个 A 开头，后跟一个或多个 B，然后是可选的 C，如下所示：
		ˆA∗B+C?$
	相匹配的例子:
		AAAAAAAAAAAABBBBBBBBBC
		BC
		B
	不匹配的例子:
		AAAAA // no B
		  AAAABC // initial space
		AABBCC // too many Cs
	模式的一部分被认为是子模式(可以从一个smatch中单独提取)，如果它被括在括号中。例如:
		\d+−\d+ // no subpatterns
		\d+(−\d+) // one subpattern
		(\d+)(−\d+) // two subpatterns
	通过添加后缀，模式可以是可选的，也可以是重复的(默认是重复一次):
		Repetition
		{ n }     Exactly n times
		{ n , }   n or more times
		{n,m}     At least n and at most m times
		*         Zero or more, that is, {0,}
		+         One or more, that is, {1,}
		?         Optional (zero or one), that is {0,1}
	例如:
		A{3}B{2,4}C∗
	相匹配的例子:
		AAABBC
		AAABB
	不匹配的例子:
		AABBC // too few As
		AAABC // too few Bs
		AAABBBBBCCC // too many Bs
	一个后缀?在任何重复符号之后(?，∗，+，和{})使模式匹配器成为“惰性”或“非贪婪”。“也就是说，当寻找一个模式时，它会寻找最短的匹配而不是最长的匹配。默认情况下，模式匹配器总是寻找最长的匹配;这就是众所周知的马克思·蒙克法则。考虑:
		ababab
	模式(ab)+匹配所有ababab。Howev呃,(ab) + ?只匹配第一个ab。
		最常见的字符分类有名称:

		字符类
		alnum        任何字母数字字符
		alpha        任何字母字符
		blank        任何非行分隔符的空白字符
		cntrl        任何控制字符
		d            任何一个十进制数字
		digit        任何一个十进制数字
		graph        任何图形字符
		lower        任何小写字符
		print        任何可打印的字符
		punct        任何标点符号字符
		s            任何空白字符
		space        任何空白字符
		upper        任何大写字符
		w            任何单词字符(字母数字字符加上下划线)
		xdigit       任何十六进制数字字符

	在正则表达式中，字符类名必须用[::]括起来。例如，[:digit:]匹配十进制数字。此外，它们必须在定义字符类的[]对中使用。
		简写表示法支持几个字符类:
			字符类的缩写
			\d        A decimal digit                                    [[:digit:]]
			\s        A space (space, tab, etc.)                         [[:space:]]
			\w        A letter (a-z) or digit (0-9) or underscore (_)    [_[:alnum:]]
			\D        Not \d                                             [ˆ[:digit:]]
			\S        Not \s                                             [ˆ[:space:]]
			\W        Not \w                                             [ˆ_[:alnum:]]

	此外，支持正则表达式的语言通常提供:
		非标准(但常见)字符类缩写
		\l        A lowercase character     [[:lower:]]
		\u        An uppercase character    [[:upper:]]
		\L        Not \l                    [ˆ[:lower:]]
		\U        Not \u                    [ˆ[:upper:]]

	为了获得完全的可移植性，请使用字符类名而不是这些缩写。
		例如，考虑编写一个描述c++标识符的模式:一个下划线或一个字母，后面可能是字母、数字或下划线的空序列。为了说明其中的微妙之处，我列举了一些错误的尝试:
		[:alpha:][:alnum:]∗ // wrong: characters from the set ":alpha" followed by ...
		[[:alpha:]][[:alnum:]]∗ // wrong: doesn’t accept underscore ('_' is not alpha)
		([[:alpha:]]|_)[[:alnum:]]∗ // wrong: underscore is not part of alnum either
		([[:alpha:]]|_)([[:alnum:]]|_)∗ // OK, but clumsy
		[[:alpha:]_][[:alnum:]_]∗ // OK: include the underscore in the character classes
		[_[:alpha:]][_[:alnum:]]∗ // also OK
		[_[:alpha:]]\w∗ // \w is equivalent to [_[:alnum:]]
	最后，这里有一个函数，它使用regex_match()(§9.4.1)最简单的版本来测试一个字符串是否为标识符:
		bool is_identifier(const string& s)
		{
			reg ex pat {"[_[:alpha:]]\\w∗"}; // underscore or letter
			// followed by zero or more underscores, letters, or digits
			return regex_match(s,pat);
		}
	注意反斜杠的双引号以在普通字符串字面量中包含一个反斜杠。使用原始字符串字面值来缓解特殊字符的问题。例如:
		bool is_identifier(const string& s)
		{
			regex pat {R"([_[:alpha:]]\w∗)"};
			return regex_match(s,pat);
		}
	下面是一些模式的例子:
		Ax∗ // A, Ax, Axxxx
		Ax+ // Ax, Axxx Not A
		\d−?\d // 1-2, 12 Not 1--2
		\w{2}−\d{4,5} // Ab-1234, XX-54321, 22-5432 Digits are in \w
		(\d∗:)?(\d+) // 12:3, 1:23, 123, :123 Not 123:
		(bs|BS) // bs, BS Not bS
		[aeiouy] // a, o, u  An English vow el, not x
		[ˆaeiouy] // x, k Not an English vow el, not e
		[aˆeiouy] // a, ˆ, o, u  An English vow el or ˆ
	可能由sub_match表示的组(子模式)由圆括号分隔。如果需要不应定义子模式的括号，请使用(?:而不是普通的(。例如:
		(\s|:|,)∗(\d∗) / / optional spaces, colons, and/or commas followed by an optional number
	假设我们对数字前的字符不感兴趣(可能是分隔符)，我们可以这样写:
		(?:\s|:|,)∗(\d∗) / / optional spaces, colons, and/or commas followed by an optional number
	这将使正则表达式引擎不必存储第一个字符:: variant只有一个子模式。

		正则表达式分组示例
		\d∗\s\w+             No groups (subpatterns)
		(\d∗)\s(\w+)         Two groups
		(\d∗)(\s(\w+))+      Two groups (groups do not nest)
		(\s∗\w∗)+            One group; one or more subpatterns;only the last subpattern is saved as a sub_match
		<(.∗?)>(.∗?)</\1>    Three groups; the \1 means ‘‘same as group 1’’

	最后一个模式对于解析XML非常有用。它查找标记/标记结束标记。注意，我使用了一个非贪婪匹配(懒惰匹配)， .*? ，用于标记和结束标记之间的子模式。如果我使用了plain .∗，这个输入就会导致问题:
		Always look on the <b>bright</b> side of <b>life</b>.
	第一个子模式的贪婪匹配将第一个<与最后一个>匹配。这将是正确的行为，但不太可能是程序员想要的。
		有关正则表达式的更详尽的介绍，请参阅[Friedl,1997]。

#####9.4.3 迭代器
	可以定义一个regex_iterator，用于遍历字符序列，查找模式的匹配项。例如，我们可以使用一个sreg ex_iterator (a regex_iterator)输出字符串中所有以空格分隔的单词:
		void test()
		{
			string input = "aa as; asd ++eˆasdf asdfg";
			reg ex pat {R"(\s+(\w+))"};
			for (sreg ex_iterator p(input.begin(),input.end(),pat); p!=sregex_iterator{}; ++p)
				cout << (∗p)[1] << '\n';
		}
	这个输出:
		as
		asd
		asdfg
	我们漏掉了第一个单词aa，因为它前面没有空格。如果我们简化为R"((\w+))"，我们得到了
		aa
		as
		asd
		e
		asdf
		asdfg
	regex_iterator是一种双向迭代器，因此不能直接迭代istream (istream只提供输入迭代器)。另外，不能通过regex_iterator进行写操作，而默认的regex_iterator (regex_iterator{})是唯一可能的序列结束符。

####9.5 建议
	[1]使用std::string来拥有字符序列;§9.2;[CG: SL.str.1]。
	[2]比起c风格的字符串函数，更喜欢字符串操作;§9.1。
	[3]使用string来声明变量和成员，而不是作为基类;§9.2。
	[4]根据值返回字符串(依赖于move语义);§9.2,§9.2.1。
	[5]直接或间接使用substr()读取子字符串，使用replace()写入子字符串;§9.2。
	[6]字符串可以根据需要增长和收缩;§9.2。
	[7]当你需要范围检查时，使用at()而不是迭代器或[];§9.2。
	[8]想要优化速度时，使用迭代器和[]而不是at();§9.2。
	[9]字符串输入没有溢出;§9.2,§10.3。
	[10]使用c_str()来生成一个c风格的字符串表示(只有在必要的时候);§9.2。
	[11]使用stringstream或泛型值提取函数(例如to)进行字符串的数值转换;§10.8。
	[12]basic_string可用于创建任何类型的字符串;§9.2.1。
	[13]为标准库字符串字面值使用s后缀;§9.3 [CG: SL.str.12]。
	[14]将string_view作为需要读取以各种方式存储的字符序列的函数的参数;§9.3 [CG: SL.str.2]。
	[15]使用gsl::string_span作为需要以各种方式写入字符序列的函数的参数;§9.3. [CG: SL.str.2] [CG: SL.str.11]。
	[16]把string_view想象成一种带有大小的指针;它没有自己的性格;§9.3。
	[17]为字符串字面值使用sv后缀意味着标准库string_views;§9.3。
	[18]在正则表达式的大多数常规用法中使用regex;§9.4。
	[19]除了最简单的模式外，首选原始字符串字面值;§9.4。
	[20]使用regex_match()来匹配一个完整的输入;§9.4, §9.4.2。
	[21]使用regex_search()在输入流中搜索模式;§9.4.1。
	[22]正则表达式表示法可以调整以匹配各种标准;§9.4.2。
	[23]默认的正则表达式表示法是ECMAScript;§9.4.2。
	[24]被抑制;正则表达式可以很容易地成为一种只写的语言;§9.4.2。
	[25]注意\i允许你用前面的子模式来表示子模式;§9.4.2。
	[26]使用?使图案“懒”;§9.4.2。
	[27]使用reg ex_iterators在流上迭代寻找模式;§9.4.3。

___
###10 输入和输出
- 介绍
- 输出
- 输入
- I/O状态
- 自定义类型I/O
- 格式化
- 文件流
- 字符串流
- C风格 I/O
- 文件系统
- 建议

####10.1 介绍
	I/O流库提供了文本和数值的格式化和非格式化的缓冲I/O。
		ostream将类型化对象转换为字符流(字节流)；
		istream将字符流(字节流)转换为类型化对象；

	对stream和ostream的操作在§10.2和§10.3中有描述。这些操作是类型安全的、类型敏感的，并且可扩展以处理用户定义的类型(§10.5)。
		其他形式的用户交互，例如图形I/O，是通过不属于ISO标准的库来处理的，因此这里不作描述。
		这些流可以用于二进制I/O，可以用于各种字符类型，特定于地区，并使用高级缓冲策略，但这些主题超出了本书的范围。
		这些流可以用于输入和输出std::字符串(§10.3)，格式化到字符串缓冲区(§10.8)，以及文件I/O(§10.10)。
		I/O流类都有析构函数，该析构函数释放所有拥有的资源(如缓冲区和文件句柄)。也就是说，它们是“资源获取即初始化”(RAII;§5.3)。

####10.2 输出
	在<ostream>中，I/O流库定义了每种内置类型的输出。此外，定义用户定义类型的输出也很容易(§10.5)。操作符 << (" put to ")被用作ostream类型对象的输出操作符;Cout是标准输出流，cerr是报告错误的标准流。默认情况下，写入cout的值被转换为字符序列。例如，要输出十进制数字10，我们可以这样写:
		void f()
		{
			cout << 10;
		}
	这将在标准输出流中放置字符1后跟字符0。
		同样地，我们可以这样写:
		void g()
		{
			int x {10};
			cout << x;
		}
	不同类型的输出可以用明显的方式组合:
		void h(int i)
		{
			cout << "the value of i is ";
			cout << i;
			cout << '\n';
		}
	对于h(10)，输出为:
		the value of i is 10
	当输出几个相关项时，人们很快就会厌倦重复输出流的名称。
	幸运的是，输出表达式的结果本身可以用于进一步的输出。例如:
		void h2(int i)
		{
			cout << "the value of i is " << i << '\n';
		}
	这个h2()产生与h()相同的输出。
		字符常量是用单引号括起来的字符。注意，字符是作为字符输出的，而不是作为数值输出的。例如:
		void k()
		{
			int b = 'b'; // note: char implicitly converted to int
			char c = 'c';
			cout << 'a' << b << c;
		}
	字符'b'的整数值是98(在我使用的c++实现中使用的ASCII编码中)，因此将输出a98c。

####10.3 输入
	在<istream>中，标准库提供了用于输入的流。与ostream类似，istreams处理内置类型的字符串表示，并且可以很容易地进行扩展以处理用户定义的类型。
		操作符>> (" get from ")被用作输入操作符;Cin是标准的输入流。>>的右操作数的类型决定了接受什么输入以及输入操作的目标是什么。例如:
		void f()
		{
			int i;
			cin >> i; // read an integer into i
			double d;
			cin >> d; // read a double-precision floating-point number into d
		}
	它将一个数字(如1234)从标准输入读入整型变量i，并将一个浮点数(如12.34e5)读入双精度浮点变量d。
		像输出操作一样，输入操作也可以被链接，所以我可以等价地写:
		void f()
		{
			int i;
			double d;
			cin >> i >> d; // read into i and d
		}
	在这两种情况下，对整数的读取都以任何非数字的字符结束。默认情况下，>>跳过初始空白，因此合适的完整输入序列将
		1234
		12.34e5
	通常，我们想要读取一系列字符。一种方便的方法是读入字符串。例如:
		void hello()
		{
			cout << "Please enter your name\n";
			string str;
			cin >> str;
			cout << "Hello, " << str << "!\n";
		}
	如果你输入Eric，响应是:
		Hello, Eric!
	默认情况下，一个空白字符，如空格或换行符，终止读取，所以如果你输入Eric Bloodaxe假装是York的不幸之王，响应仍然是:
		Hello, Eric!
	你可以使用getline()函数读取整行内容。例如:
		void hello_line()
		{
			cout << "Please enter your name\n";
			string str;
			getline(cin,str);
			cout << "Hello, " << str << "!\n";
		}
	在这个程序中，输入Eric Bloodaxe会产生所需的输出:
		Hello, Eric Bloodaxe!
	终止该行的换行符被丢弃，因此cin可以开始下一个输入行。
		使用格式化的I/O操作通常比逐个操作字符更不容易出错、更高效、更少代码。特别地，流负责内存管理和范围检查。我们可以使用stringstreams(§10.8)来格式化与内存之间的数据。
		标准字符串有一个很好的特性，可以展开容纳你放入的东西;您不需要预先计算最大大小。因此，如果你输入了几兆字节的分号，程序就会回显好几页的分号。

####10.4 I/O状态
	iostream有一个状态，我们可以通过检查来确定操作是否成功。最常见的用法是读取一个值序列:
		vector<int> read_ints(istream& is)
		{
			vector<int> res;
			for (int i; is>>i; )
				res.push_back(i);
			return res;
		}
	这将从is中读取数据，直到遇到非正整数的数据。这个东西通常是输入的终点。这里发生的事情是，操作是>>i返回对is的引用，如果测试iostream流准备好进行另一个操作，则结果为true。
		通常，I/O状态保存所有读写所需的信息，例如格式化信息(§10.6)，错误状态(例如，是否已到达输入结束?)，以及使用哪种缓冲。特别地，用户可以设置状态来反映发生了错误(§10.5)，如果错误不严重，则清除该状态。例如，我们可以想象一个版本的read_int()，它接受一个终止字符串:
		vector<int> read_ints(istream& is, const string& terminator)
		{
			vector<int> res;
			for (int i; is >> i; )
				res.push_back(i);
			if (is.eof()) // fine: end of file
				return res;
			if (is.fail())
			{ 	// we failed to read an int; was it the terminator?
				is.clear(); // reset the state to good()
				is.unget(); // put the non-digit back into the stream
				string s;
				if (cin>>s && s==terminator)
					return res;
				cin.setstate(ios_base::failbit); // add fail() to cin’s state
			}
			return res;
		}
		auto v = read_ints(cin,"stop");

####10.5 自定义类型I/O
	除了内置类型和标准字符串的I/O外，iostream库还允许程序员为自己的类型定义I/O。例如，考虑一个简单类型Entry，我们可以用它来表示电话簿中的条目:
		struct Entry {
			string name;
			int number;
		};
	我们可以定义一个简单的输出操作符，使用类似于代码中初始化时使用的{"name"，number}格式来编写一个Entry:
		ostream& operator<<(ostream& os, const Entry& e)
		{
			return os << "{\"" << e.name << "\", " << e.number << "}";
		}
	用户定义的输出操作符将其输出流(通过引用)作为其第一个参数，并将其作为结果返回。
		相应的输入操作符更复杂，因为它必须检查正确的格式并处理错误:
		istream& operator>>(istream& is, Entry& e)
		// read { "name" , number } pair. Note: for matted with { " " , and }
		{
			char c, c2;
			if (is>>c && c=='{' && is>>c2 && c2=='"')
			{ 	// star t with a { "
				string name; // the default value of a string is the empty string: ""
				while (is.get(c) && c!='"') // anything before a " is part of the name
					name+=c;
				if (is>>c && c==',')
				{
					int number = 0;
					if (is>>number>>c && c=='}')
					{ 	// read the number and a }
						e = {name ,number}; // assign to the entry
						return is;
					}
				}
			}
			is.setstate(ios_base::failbit); // register the failure in the stream
			return is;
		}
	输入操作返回对其istream的引用，可用于测试操作是否成功。例如，当用作条件时，>>c表示“我们成功地将一个字符从is读入c了吗?””
		缺省情况下，is>>c跳过空格。get(c)没有，所以这个entry-input操作符忽略(跳过)名称字符串外的空白，而不是名称字符串内的空白。例如:
		{ "John Marwood Cleese", 123456 }
		{"Michael Edward Palin", 987654}
	我们可以这样从输入中读取这对值到输入y中:
		for (Entry ee; cin>>ee; ) // read from cin into ee
			cout << ee << '\n'; // write ee to cout
	输出是:
		{"John Marwood Cleese", 123456}
		{"Michael Edward Palin", 987654}
	关于识别字符流中的模式(正则表达式匹配)的更系统的技术参见§9.4。

####10.6 格式化
	iostream标准库提供了大量用于控制输入和输出格式的操作。最简单的格式化控件称为操纵符，可在<ios>,<istream>、<ostream>和<iomanip>中找到(用于带参数的操纵符)。例如，我们可以输出十进制(默认)、八进制或十六进制数的整数:
		cout << 1234 << ',' << hex << 1234 << ',' << oct << 1234 << '\n'; // print 1234,4d2,2322
	我们可以显式地设置浮点数的输出格式:
			constexpr double d = 123.456;
			cout << d << "; " // use the default for mat for d
				 << scientific << d << "; " // use 1.123e2 style for mat for d
				 << hexfloat << d << "; " // use hexadecimal notation for d
				 << fixed << d << "; " // use 123.456 style for mat for d
				 << defaultfloat << d << '\n'; // use the default for mat for d
	生成：
		123.456; 1.234560e+002; 0x1.edd2f2p+6; 123.456000; 123.456
	Precision是一个确定用于显示浮点数的位数的整数:
		• 通用格式(defaultfloat)让实现选择一种格式，以最好地保留可用空间中的值的样式来表示一个值。精度指定数字的最大位数。
		• 科学计数(scientific)表示一个小数点前有一位数字和一个指数的值。精度指定小数点后的最大位数。
		• 固定格式(fixed)以整数部分后跟小数点和小数部分的形式表示值。精度指定小数点后的最大位数。
	浮点值被四舍五入，而不仅仅是被截断，而且precision()不会影响整型输出。例如:
		cout.precision(8);
		cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
		cout.precision(4);
		cout << 1234.56789 << ' ' << 1234.56789 << ' ' << 123456 << '\n';
		cout << 1234.56789 << '\n';
	生成：
		1234.5679 1234.5679 123456
		1235 1235 123456
		1235
	这些浮点操纵符是“粘性的”;也就是说，它们的影响将持续到后续的浮点操作。

####10.7 文件流
	在<fstream>中，标准库提供了进出文件的流:
		• ifstreams用于从文件读取数据
		• ofstreams用于写入数据
		• fstreams用于读写数据
	例如:
		ofstream ofs {"target"}; // ‘‘o’’ for ‘‘output’’
		if (!ofs)
			error("couldn't open 'target' for writing");
	通常通过检查文件流的状态来测试文件流是否被正确打开。
		ifstream ifs {"source"}; // ‘‘i’’ for ‘‘input’’
		if (!ifs)
			error("couldn't open 'source' for reading");
	假设测试成功，ofs可以用作普通的ostream(就像cout)， if可以用作普通的istream(就像cin)。
		文件定位和更详细的文件打开方式控制是可能的，但超出了本书的范围。
		关于文件名和文件系统操作的组成，参见§10.10。

####10.8 字符串流
	在<sstream>中，标准库提供了与string对象来往的流:
		• istringstream 用于读取字符串的istringstreams
		• ostringstream 用于写入字符串的ostringstreams
		• stringstream 用于读取和写入字符串的stringstreams。
	例如:
		void test()
		{
			ostringstream oss;
			oss << "{temperature," << scientific << 123.4567890 << "}";
			cout << oss.str() << '\n';
		}
	ostringstream的结果可以使用str()读取。ostringstream的一个常见用途是在将结果字符串提供给GUI之前进行格式化。同样，从GUI接收到的字符串也可以通过将其放入istringstream中进行格式化输入操作(§10.3)来读取。
		字符串流既可用于读，也可用于写。例如，我们可以定义一个操作，将任何具有字符串表示的类型转换为另一种也可以表示为字符串的类型:
		template<typename Target =string, typename Source =string>
		Targ et to(Source arg) // convert Source to T arget
		{
			stringstream interpreter;
			Targ et result;
			if (!(interpreter << arg) // wr ite arg into stream
				|| !(interpreter >> result) // read result from stream
				|| !(interpreter >> std::ws).eof()) // stuff left in stream?
				throw runtime_error{"to<>() failed"};
			return result;
		}
	函数模板实参只有在不能推导或没有默认实参的情况下才需要显式提及(§7.2.4)，因此我们可以这样写:
		auto x1 = to<string,double>(1.2); // very explicit (and verbose)
		auto x2 = to<string>(1.2); // Source is deduced to double
		auto x3 = to<>(1.2); // T arget is defaulted to string; Source is deduced to double
		auto x4 = to(1.2); // the <> is redundant;
		// T arget is defaulted to string; Source is deduced to double
	如果所有函数模板参数都是默认值，则可以省略<>。
		我认为这是一个很好的例子，说明可以通过结合语言特性和标准库设施来实现通用性和易用性。

####10.9 C风格I/O
	c++标准库也支持C标准库的I/O，包括printf()和scanf()。
	从类型和安全性的角度来看，这个库的许多使用都是不安全的，所以我不推荐使用它。特别是，它很难用于安全、方便的输入。它不支持用户定义的类型。如果你不使用c风格的I/O并且关心I/O性能，调用
		ios_base::sync_with_stdio(false); // avoid significant overhead
	如果没有这个调用，iostream的速度会大大降低，以便与c风格的I/O兼容。

####10.10 文件系统
	大多数系统都有一个文件系统的概念，即提供对存储为文件的永久信息的访问。不幸的是，文件系统的属性和操作它们的方法差别很大。
	为了处理这个问题，<filesystem>中的文件系统库为大多数文件系统的大多数工具提供了统一的接口。使用<filesystem>，我们可以移植
		• 表示文件系统路径并在文件系统中导航
		• 检查文件类型和与它们相关的权限
	文件系统库可以处理unicode，但是如何解释超出了本书的范围。我推荐使用cppreference [cppreference]和Boost文件系统文档[Boost]获取详细信息。
		考虑一个例子:
		pathf = "dir/hypothetical.cpp"; // naming a file
		assert(exists(f)); // f must exist
		if (is_regular_file(f)) // is f an ordinary file?
			cout << f << " is a file; its size is " << file_siz e(f) << '\n';
	注意，操作文件系统的程序通常与其他程序一起运行在计算机上。因此，文件系统的内容可以在两个命令之间更改。例如，尽管我们首先谨慎地断言f存在，但在下一行中，当我们询问f是否是一个普通文件时，这可能就不再成立了。
		路径是一个相当复杂的类，能够处理许多操作系统的本机字符集和约定。特别地，它可以处理main()提供的命令行中的文件名;例如:
		int main(int argc, char∗ argv[])
		{
			if (argc < 2)
			{
				cerr << "arguments expected\n";
				return 1;
			}
			path p {argv[1]}; // create a path from the command line
			cout << p << " " << exists(p) << '\n'; // note: a path can be printed like a str ing
			// ...
		}
	在使用路径之前，不会检查路径的有效性。即使这样，它的有效性取决于程序运行所依赖的系统的惯例。
	当然，可以使用路径来打开文件
		void use(path p)
		{
			ofstream f {p};
			if (!f) error("bad file name: ", p);
			f << "Hello, file!";
		}
	除了path，<filesystem>还提供了用于遍历目录和查询所找到文件属性的类型:
		文件系统类型(部分)
		path                            目录路径
		filesystem_error                文件系统异常
		directory_entry                 目录条目
		directory_iterator              用于在目录上进行迭代
		recursive_directory_iterator    用于迭代一个目录及其子目录
	举一个简单但并非完全不现实的例子:
		void print_directory(path p)
			tr y
			{
				if (is_directory(p))
				{
					cout << p << ":\n";
					for (const directory_entry& x : director y_iterator{p})
						cout << " " << x.path() << '\n';
				}
			}
			catch (const filesystem_error& ex) {
			cerr << ex.what() << '\n';
		}
	字符串可以隐式转换为路径，因此可以像这样执行print_directory:
		void use()
		{
			print_directory("."); // current directory
			print_directory(".."); // parent directory
			print_directory("/"); // Unix root directory
			print_directory("c:"); // Windows volume C
			for (string s; cin>>s; )
				print_directory(s);
		}
	如果我也想列出子目录，我应该使用recursive_directory_iterator{p}。如果我想按字典序打印条目，我应该将路径复制到一个向量中，并在打印前对其进行排序。
		类路径提供了许多常见和有用的操作:
___
	路径操作(部分)
	P和p2是路径
	value_type                    文件系统本地编码使用的字符类型:
								  POSIX上的char, Windows上的wchar_t
	string_type                   std::basic_string<value_type>
	const_iterator                const双向迭代器，value_type为path
	iterator                      const_iterator的别名

	p=p2                          把p2赋值给p
	p/=p2                         P和p2使用文件名称分隔符连接起来(默认情况下为/)
	p+=p2                         P和p2串联(无分隔符)
	p.native()                    p的原生格式
	p.string()                    p的原生格式的字符串
	p.g eneric_string()           p的一般格式为字符串
	p.filename()                  p的文件名部分
	p.stem()                      p的根部
	p.extension()                 p的文件扩展名部分
	p.begin()                     p元素序列的开始部分
	p.end()                       p的元素序列的末尾
	p==p2, p!=p2                  p和p的等式和不等式
	p<p2, p<=p2, p>p2, p>=p2      词法比较
	is>>p, os<<p                  流I/O 到/从p
	u8path(s)                     来自UTF-8编码源s的路径
___
	例如:
		void test(path p)
		{
			if (is_directory(p))
			{
				cout << p << ":\n";
				for (const directory_entr y& x : director y_iterator(p))
				{
					const path& f = x; // refer to the path part of a director y entr y
					if (f.extension() == ".exe")
						cout << f.stem() << " is a Windows executable\n";
					else
					{
						string n = f.extension().string();
						if (n == ".cpp" || n == ".C" || n == ".cxx")
							cout << f.stem() << " is a C++ source file\n";
					}
				}
			}
		}
	我们使用路径作为字符串(如f.extension)，并且可以从路径中提取各种类型的字符串(如f.extension().string())。
		请注意，命名约定、自然语言和字符串编码都非常复杂。
	文件系统库抽象提供了可移植性和极大的简化。
___
	文件系统操作(部分)
	P p1 p2是路径;E是一个error_code;B是指示成功或失败的bool值
	exists(p)                 p是否指向一个现有的文件系统对象?
	copy(p1,p2)               将文件或目录从p1复制到p2;将错误报告为异常
	copy(p1,p2,e)             复制文件或目录;报告错误作为错误代码
	b=copy_file(p1,p2)        将文件内容从p1复制到p2;将错误报告为异常
	b=create_director y(p)    创建名为p的新目录;p上的所有中间目录必须存在
	b=create_directories(p)   创建名为p的新目录;在p上创建所有中间目录
	p=current_path()          p是当前工作目录
	current_path(p)           将当前工作目录设置为p
	s=file_siz e(p)           S是p的字节数
	b=remove(p)               如果是文件或空目录，请删除p
___
	许多操作都有需要额外参数的重载，例如操作系统权限。
	这些内容的处理远远超出了本书的范围，所以如果您需要它们，请查阅它们。
		和copy()一样，所有操作都有两个版本:
		• 表中列出的基本版本，例如，exists(p)。如果操作失败，函数将抛出filesystem_error。
		• 带有额外error_code参数的版本，例如exists(p,e)。操作是否成功。
		当操作在正常使用中预期频繁失败时，我们使用错误代码，当错误被认为是异常时，我们使用抛出操作。
		通常，使用查询函数是检查文件属性的最简单、最直接的方法。<filesystem>库知道一些常见的文件类型，并将其余文件分类为“other”:
___
	文件类型
	f路径或file_status

	is_block_file(f)            f是块设备吗?
	is_character_file(f)        f是一个字符设备吗?
	is_director y(f)            f是目录吗?
	is_empty(f)                 f是否为空文件或目录?
	is_fifo(f)                  f是有名管道吗?
	is_other(f)                 f是其他类型的文件吗?
	is_regular_file(f)          f是普通文件吗?
	is_socket(f)                f是命名的IPC套接字吗?
	is_symlink(f)               f是符号链接吗?
	status_known(f)             f的文件状态已知吗?
___

####10.11 建议
	[1] iostream是类型安全的、类型敏感的、可扩展的;§10.1。
	[2] 只有在必要时才使用字符级输入;§10.3;[CG: SL.io.1]。
	[3] 读取时，总是考虑格式错误的输入;§10.3;[CG: SL.io.2]。
	[4] 避免endl(如果你不知道endl是什么，你没有错过任何东西);[CG: SL.io.50]。
	[5] 为具有有意义的文本表示的用户定义类型定义<<和>>;§10.1,§10.2,§10.3。
	[6] 正常输出使用cout，错误使用cerr;§10.1。
	[7] 有普通字符和宽字符的iostream，你可以为任何类型的字符定义iostream;§10.1。
	[8] 支持二进制I/O;§10.1。
	[9] 对于标准I/O流、文件和字符串，有标准的iostream;§10.2、§10.3、§10.7、§10.8。
	[10] 链接<<操作用于更简洁的表示法;§10.2。
	[11] 链接>>操作，用于更简洁的表示法;§10.3。
	[12] 字符串的输入不溢出;§10.3。
	[13] 缺省情况下>>跳过初始空白;§10.3。
	[14] 使用流状态失败来处理可能可恢复的I/O错误;§10.4。
	[15] 你可以为自己的类型定义<<和>>操作符;§10.5。
	[16] 你不需要修改istream或ostream来添加新的<<和>操作符;§10.5。
	[17] 使用操纵符控制格式;§10.6。
	[18] precision()规范适用于以下所有浮点输出操作;§10.6。
	[19] 浮点格式规范(例如scientific)适用于以下所有浮点输出操作;§10.6。
	[20] #include<ios> 当使用标准操作符时;§10.6。
	[21] #include<iomanip>时使用标准操作符接受参数;§10.6。
	[22] 不要尝试复制文件流。
	[23] 在使用文件流之前，请记住检查文件流是否已附加到文件;§10.7。
	[24] 使用stringstreams在内存中格式化;§10.8。
	[25] 你可以定义任意两种类型之间的转换，它们都有字符串表示;§10.8。
	[26] C-style I/O不是类型安全的;§10.9。
	[27] 除非你使用printf家族函数，否则调用ios_base::sync_with_stdio(false);§10.9;[CG: SL.io.10]。
	[28] 选择<filesystem>而不是直接使用特定的操作系统接口;§10.10。




















	





。
。
。
。
。
。