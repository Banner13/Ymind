# c

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