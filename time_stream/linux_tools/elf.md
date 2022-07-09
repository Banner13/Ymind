
##ELF - 可执行和链接格式 (ELF) 文件
[原文链接](https://man7.org/linux/man-pages/man5/elf.5.html)

	elf.h

		一个使用ELF文件格式的可执行文件包括一个ELF头，后面跟着一个 program 头表或一个 section 头表，或两者都有。ELF头始终位于文件的偏移量0处。
		program 头表和 section 头表在文件中的偏移量在ELF头中定义。这两个表描述了文件的其余细节。
		在 elf.h 中以C语言结构定义了上述的 ELF头，还包括动态部分、重定位部分和符号表的结构。
![ELF header](./ELF-header.gif)

		ELF头定义：
		typedef struct {
               unsigned char e_ident[EI_NIDENT];
               uint16_t      e_type;
               uint16_t      e_machine;
               uint32_t      e_version;
               ElfN_Addr     e_entry;
               ElfN_Off      e_phoff;
               ElfN_Off      e_shoff;
               uint32_t      e_flags;
               uint16_t      e_ehsize;
               uint16_t      e_phentsize;
               uint16_t      e_phnum;
               uint16_t      e_shentsize;
               uint16_t      e_shnum;
               uint16_t      e_shstrndx;
           } ElfN_Ehdr;
		
		 e_ident 这个字节数组指定如何解释文件，独立于处理器或文件的剩余内容。在这个数组中，所有内容都由头文件中的宏命名，宏以前缀EI_开头，并可能包含以前缀ELF开头的值。例如:
		 
			#define EI_MAG0		0		/* File identification byte 0 index */
			#define ELFMAG0		0x7f		/* Magic number byte 0 */
			#define EI_MAG1		1		/* File identification byte 1 index */
			#define ELFMAG1		'E'		/* Magic number byte 1 */
			#define EI_MAG2		2		/* File identification byte 2 index */
			#define ELFMAG2		'L'		/* Magic number byte 2 */
			#define EI_MAG3		3		/* File identification byte 3 index */
			#define ELFMAG3		'F'		/* Magic number byte 3 */
		 