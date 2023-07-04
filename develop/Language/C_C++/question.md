[TOC]

### 如果函数定义缺少变量名是否还能使用变量？
	结论：可以，但是很难。
	例如：即使缺少形参，变量的内容依然传递到了特定地址，如果特别熟悉汇编指令的产生(编译器、处理器等不同)，依然是能获取到的。
```c
#include <stdio.h>

int add(int, int);

int add(int , int )
{

    int c = 0;
    asm("mov     $0, %eax");
    asm("add     %edi, %eax");
    asm("add     %esi, %eax");
    asm("pop     %rbp");
    asm("ret");
    return c;
}

int main(void)
{
    int a, b, c;

    a = 1;
    b = 5;
    c = add(a, b);

    printf("c = %d\r\n", c);
    return 0;
}
```
### 强制修改 const 变量会怎么样？
	结论：产生UB(undefined behavior)行为，错误行为。
	例如：结果是不确定的。
```c
/* Type your code here, or load an example. */
#include <stdio.h>

void a();

int main()
{
    a();
    return 0;
}

void a()
{
    char const ch = 'a';
    char* p;
    const char* q;
    printf("ch is %c\r\n", ch);
    printf("ch_addr is %p\r\n\r\n", &ch);

    p = (char*)&ch;
    *p = 'b';
    printf("*p is %c\r\n", *p);
    printf("*p_addr is %p\r\n\r\n", p);

    q = &ch;
    // *q = 'c';
    printf("*q is %c\r\n", *q);
    printf("*q_addr is %p\r\n\r\n", q);

    printf("ch2 is %c\r\n", ch);
    printf("ch2_addr is %p\r\n\r\n", &ch);

    printf("addr is %p\r\n", (const char*)&ch);
    printf("addr_data is %c\r\n\r\n", *(const char*)&ch);

/*
ch is a
ch_addr is 0x7ffe7a62392f

*p is b
*p_addr is 0x7ffe7a62392f

*q is b
*q_addr is 0x7ffe7a62392f

ch2 is a
ch2_addr is 0x7ffe7a62392f

addr is 0x7ffe7a62392f
addr_data is b
*/
}
```

### 在头文件中使用static 变量
```
// t.h
#ifndef T_H
#define T_h

static int test_value;

#endif
```
	不同的源文件都可以使用该头文件中的 test_value 变量，但不是同一个变量，而是每个源文件各自的变量。可以通过打印变量地址查看。

### 字符常量是否可以通过地址引用的方式去修改
	结论：不可以，常量分配至OnlyRead-Data段或是 Test段，尝试修改地址会引起段错误。

### sizeof 是怎么获取数组长度的？为什么数组和数组指针的sizeof不同？
	熟悉汇编变量声明可知：
```asm
array:          .space	40
array——ptr:     .world	0
```
	sizeof 不关心你是不是数组，只关心该数据类型的大小。数组类型是由元素类型和数组长度决定的。对其struct 和 union 的计算，在对齐后，依次计算每个元素所占用的长度进行叠加。
