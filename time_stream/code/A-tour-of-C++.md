[TOC]
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

##目录

	前言.......................................................xi

    1 基础
        1.1	介绍
        1.2	
        1.3	
        1.4	
        1.5	
        1.6	
        1.7	
        1.8	
        1.9	
        1.10	
___

###前言

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

###1 基础

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


####1.1 介绍
		本章非正式地介绍了c++的符号，c++的内存和计算模型，以及将代码构建为程序的基本机制。这些语言工具支持C语言中最常见的风格，有时也被称为过程式编程(面向过程编程)^1^。
	^1^ 译注

####1.2 程序
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
---
            #include <iostream>
            int main()
            {
                std::cout << "Hello, World!\n";
            }
---
		#include <iostream> 这一行告诉编译器需要编译的内容还包含 iostream 文件。没有这些声明，表达式：
    	std::cout << "Hello, World!\n"
    	没有任何意义。	// 译注：该文件为标准库中的文件，存放在编译器目录下，提供标准I/O流的功能。
    操作符<< (" put to ")将其第二个参数写入其第一个参数。在本例中，字符串字面量“Hello, World!”\n”被写入标准输出流std::cout。字符串字面量是由双引号包围的字符序列。在字符串字面量中，反斜杠字符\后跟另一个字符表示单个“特殊字符”。在本例中，\n是换行字符，因此写入的字符是Hello, World!后跟换行符。
    	std::指定名称cout在标准库命名空间中找到(§3.4)。在讨论标准特性时，我通常会省略std::;§3.4展示了如何在没有显式限定的情况下使名称空间中的名称可见。
        实际上，所有可执行代码都放在函数中，并直接或间接地从main()调用。例如:
---
        #include <iostream> // include (‘‘impor t’’) the declarations for the I/O stream librar y
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
---
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
            virtual double& operator[](int) = 0; // pure virtual function
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

。
。
。
。
。
。