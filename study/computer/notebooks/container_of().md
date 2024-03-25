
```c
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif
```
offsetof 通过将TYPE * 类型指针指向 0x00000000地址进行对齐，然后获取到 MEMBER 的偏移。

``` c
// include/linux/kernel.h
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
```
源指针 - offsetof() 得到的偏移得到目标指针。



