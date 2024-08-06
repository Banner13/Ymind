###天子守国门，君王死社稷
	参考 man elf
##ELF

###概述
	ELF是一种可执行二进制文件格式。其内容包含了可执行文件，重定向对象文件，核心文件和共享对象。
___
###ELF组成
		一个可执行的ELF格式文件，在文件开头通常有一个 ELF header ，根据不同，还有一个 program table 或 section table 或两者皆有。关于 program table 和 section table ，在 ELF header 中有定义其存放的位置，它们描述了其余的信息。
___
####ELF header
		该头除了包含了 program table 和 section table 的相关信息外，还存放着一些与具体内容不相干却有一定意义的信息，例如 entry、machine 、 version 、flags等。
<pre>
typedef struct {
	unsigned char e_ident[EI_NIDENT];	// e_ident 这个字节数组指定了如何解释该文件，与处理器或文件的其余内容无关。
	uint16_t	  e_type;	// 定义了该文件的类别：核心文件、重定向文件、可执行文件或共享对象。
	uint16_t	  e_machine;	// 指定了单个文件所需的架构。 比如说：EM_386、EM_ARM、EM_X86_64。
	uint32_t	  e_version;	// 标识了文件的版本。
	ElfN_Addr	  e_entry;	// 给出了系统第一次转移控制权的虚拟地址，从而启动了这个进程。 如果文件没有相关的入口点，这个成员等于 0 。
	ElfN_Off	  e_phoff;	// 给出了 program table 在文件中的偏移，如果这个成员等于 0 。
	ElfN_Off	  e_shoff;	// 给出了 section table 在文件中的偏移，如果这个成员等于 0 。
	uint32_t	  e_flags;	// 定义与文件相关的处理器特定标志。目前，还没有定义任何标志。
	uint16_t	  e_ehsize;	// 定义 ELF header 的大小，单位是字节。
	uint16_t	  e_phentsize;	// 定义 program table 中一个条目的大小，以字节为单位；所有条目都是相同的大小。
	uint16_t	  e_phnum;	// 定义 program table 的条目数。
	uint16_t	  e_shentsize;	// 定义 section table 中一个条目的大小，以字节为单位；所有条目都是相同的大小。
	uint16_t	  e_shnum;	// 定义 section table 的条目数。
	uint16_t	  e_shstrndx;	// 定义了section table 中关联入口和 section name string table 的索引。
} ElfN_Ehdr;
</pre>
<pre>
typedef struct {
	EI_MAG0;		// 0x7f
	EI_MAG1;		// 'E'
	EI_MAG2;		// 'L'
	EI_MAG3;		// 'F'
	EI_CLASS;		// 定义了可执行文件的架构，64 or 32 bit。
	EI_DATA;		// 定义数据格式，大端 or 小端。
	EI_VERSION;		// 定义该ELF文件的版本号。
	EI_OSABI;		// 定义了该文件支持的操作系统和 ABI (application binary interface)。
	EI_ABIVERSION;	// 定义了该 ABI 的版本。
	EI_PAD;			// 填充的开始。 这些字节被保留并设置为零。
	Reserved;
	...
} e_ident;
</pre>

	总结：一方面，ELF header 主要为机器识别该文件的类型做出了贡献，另一方面，给 program table 和 section table 的出场留下了开幕的方式。
___
####Program header (Phdr)
		一个可执行文件或者共享对象的 program table 是一个结构数组，数组中的每一项都描述了程序执行所需要的一个 segment 或是其他信息。一个 segment 包含了一个或多个 sections 。以32bit(q其实与64bit无差异)的ELF 介绍：
<pre>
typedef struct {
	uint32_t		p_type;		// 定义了这个段的类别：PT_LOAD、 PT_DYNAMIC、PT_NULL等。
	Elf32_Off		p_offset;	// 定义该段内容的第一个字节在文件中的偏移。
	Elf32_Addr		p_vaddr;	// 定义该段内容的第一个字节在内存中的虚拟地址。
	Elf32_Addr		p_paddr;	// 定义该段内容的第一个字节在内存中的物理地址。
	uint32_t		p_filesz;	// 定义该段内容在文件镜像中的字节大小。
	uint32_t		p_memsz;	// 定义该段内容在内存镜像中的字节大小。
	uint32_t		p_flags;	// 定义该段的属性：PF_X、PF_W、PF_R。
	uint32_t		p_align;	// 定义该段在文件和内存中的对齐值。
} Elf32_Phdr;
</pre>

	总结：program table 主要包含了可执行内容和共享对象的相关信息、最后可执行的内容实现还是存放在 sections 中了。
___
####Section header (Shdr)
	section table 是一个结构数组，文件中的所有 sections 都可以通过 section table 来找到。
	在介绍 Section header 之前，先介绍几个宏定义。
		SHN_UNDEF		此值标记未定义、缺失、不相关或其他无意义的部分引用。
		SHN_LORESERVE		此值指定保留索引范围的下限。
		SHN_LOPROC, SHN_HIPROC		在包含范围 [SHN_LOPROC, SHN_HIPROC] 中更大的值保留用于特定于处理器的语义。
		SHN_ABS		此值指定相应参考的绝对值。例如，相对于节号 SHN_ABS 定义的符号具有绝对值，不受重定位的影响。
		SHN_COMMON		与本节相关的符号是通用符号，例如 FORTRAN COMMON 或未分配的 C 外部变量。
		SHN_HIRESERVE		此值指定保留索引范围的上限。系统保留 SHN_LORESERVE 和 SHN_HIRESERVE（含）之间的索引。
<pre>
typedef struct {
	// 定义该 section 的名字，这个名字会作为索引出现在 the section header string table section
	uint32_t	sh_name;
	// 定义该 section 的类别，根据其内容和语义。SHT_REL、SHT_DYNAMIC。
	uint32_t	sh_type;
	// 定义该 section 的属性：SHF_WRITE、SHF_ALLOC。
	uint32_t	sh_flags;
	// 如果这个 section 出现在一个进程的内存映像中，定义该 section 的第一个字节的地址。
	Elf32_Addr	sh_addr;
	// 定义该 section 在文件中的偏移。
	Elf32_Off	sh_offset;
	// 定义该 section 在文件中所占字节数。
	uint32_t	sh_size;
	// 定义了一个在 section header table 中的索引链接，具体含义根据 sh_type 决定。
	uint32_t	sh_link;
	// 定义额外信息，具体含义根据 sh_type 决定。
	uint32_t	sh_info;
	// 定义该 section 的对齐要求。
	uint32_t	sh_addralign;
	// 有些 section 保存着一个固定大小的条目表，比如说 symbol table 。
	// 对于这样的 section ,这个成员给出了每个条目的大小（字节）。
	uint32_t	sh_entsize;
} Elf32_Shdr;
</pre>

	总结：在 section table 中，具体的描述了 section 的作用和使用方法。
___
####行文过半
	ELF文件由 ELF header 、 program table(option) 、 section table 组成。
	ELF header 管理着 program table 和 section table。
	如果存在 program table ， 那么 program table 管理着与其相关的 section 。
	section table 管理着所有的 section 信息，所以，最后让我们看一下 ELF 的最基本元素 section 。以及一些特殊的 tables 。
___
####sections
	section 种类繁多、该文会讲解较为常见的类型，以及笔者在学习过程中遇到的类型。
<pre>
.bss	这部分保存了未初始化的数据，对程序的内存映像有帮助。根据定义，当程序开始运行时，系统会用零来初始化这些数据。
.data	这部分存放了对程序的内存镜像有用的初始化数据。
.text	这部分存放程序的 "text"，即可执行的指令。
.debug	本 section 关于符号调试的信息。
</pre>

####String and symbol tables
		一个对象文件的符号表拥有定位和重定位程序所需的符号定义和引用信息。 String and symbol tables 是一个结构数组，而 String and symbol tables 的索引是这个数组的一个下标。
<pre>
typedef struct {
	// 记录该符号名称在 symbol string table 中的索引。
	// 在 symbol string table 中的索引值为其名称。
	uint32_t      st_name;
	// 该符号值的存放地址。
	Elf32_Addr    st_value;
	// 该符号值的长度。
	uint32_t      st_size;
	// 记录该符号的类型和绑定属性。  STT_FUNC、STB_GLOBAL、STB_LOCAL。
	unsigned char st_info;
	// 记录符号的可见性。
	unsigned char st_other;
	// 每个 symbol table entry 都是相对于某些部分“定义”的。定义该符号在 section header table 中的索引值。
	uint16_t      st_shndx;
} Elf32_Sym;
</pre>

####Relocation entries (Rel & Rela)
		重定位是将符号引用与符号定义连接起来的过程。 可重定位的文件必须有描述如何修改其部分内容的信息，从而使可执行文件和共享对象文件能够为进程的程序图像持有正确的信息。 重新定位条目就是这些数据。
<pre>
typedef struct {
	// 定义了重定位动作加载的位置。
	// 对于重定位文件，该值是从节开头到受重定位影响的存储单元的字节偏移量
	// 对于可执行文件或共享对象，该值是受重新定位影响的存储单元的虚拟地址。
	Elf32_Addr r_offset;
	// 这个成员给出了必须进行重定位的符号表索引和要应用的重定位类型。
	uint32_t   r_info;
	// 这个成员指定了一个常数附加值，用于计算要存储到可重定位字段的值。
	int32_t    r_addend;
} Elf32_Rela;
</pre>

####Dynamic tags (Dyn)
	.dynamic 部分包含了一系列的结构，用于保存相关的动态连接信息。
<pre>
typedef struct {
	Elf32_Sword	 d_tag;		// 定义该标签的内容。
	union {
		Elf32_Word d_val;	// 该成员表示具有各种解释的整数值。
		Elf32_Addr d_ptr;	// 这个成员代表程序虚拟地址。
	} d_un;
} Elf32_Dyn;
extern Elf64_Dyn _DYNAMIC[];	// 包含.dynamic部分的所有动态结构的数组。 这是由链接器自动填充的。
</pre>

####Notes (Nhdr)
		ELF注释允许附加任意的信息供系统使用。 它们主要由核心文件（ET_CORE的e_type）使用，但许多项目定义了他们自己的扩展集。例如，GNU工具链使用ELF注释来将信息从链接器传递给C库。
		注释部分包含一系列的注释（见下面的结构定义）。 每个注释后面都有一个名称字段（其长度在n_namesz中定义），然后是描述符字段 (其长度在n_descsz中定义)，其起始地址有4个字节的对齐。 这两个字段都没有在笔记结构中定义，因为它们的长度是任意的。
		解析两个连续注释的示例应该阐明它们在内存中的布局:
		
####留坑
	行文过半后，对后面的内容就感觉很难看进去了，准备从 SEE ALSO 入手，回过头来在填坑。
	SEE ALSO
       as(1), elfedit(1), gdb(1), ld(1), nm(1), objdump(1), patchelf(1), readelf(1), size(1), strings(1), strip(1), execve(2), dl_iterate_phdr(3), core(5), ld.so(8)

       Hewlett-Packard, Elf-64 Object File Format.

       Santa Cruz Operation, System V Application Binary Interface.

       UNIX System Laboratories, "Object Files", Executable and Linking Format (ELF).

       Sun Microsystems, Linker and Libraries Guide.

       AMD64 ABI Draft, System V Application Binary Interface AMD64 Architecture Processor Supplement.