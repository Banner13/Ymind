Host: WSL2 Ubuntu18


## 1. 下载基本工具
```bash
sudo apt-get install -y libncurses5-dev build-essential lib32readline-gplv2-dev
```

## 2. 安装gcc-4.4
[[develop/ToolsChain/ARM-Gcc/install#安装gcc-4.4|安装gcc-4.4]]

## 3. 获取linux2.6.24源代码并修改
```bash
wget --no-check-certificate https://mirror.bjtu.edu.cn/kernel/linux/kernel/v2.6/linux-2.6.24.tar.xz
tar -xvJf linux-2.6.24.tar.xz
cd linux-2.6.24/
```
做出以下修改
```patch
diff --git a/Makefile b/Makefile
index 189d8ef4..4196f763 100644
--- a/Makefile
+++ b/Makefile
@@ -431,7 +431,7 @@ ifeq ($(config-targets),1)
 include $(srctree)/arch/$(SRCARCH)/Makefile
 export KBUILD_DEFCONFIG

-config %config: scripts_basic outputmakefile FORCE
+%config: scripts_basic outputmakefile FORCE
        $(Q)mkdir -p include/linux include/config
        $(Q)$(MAKE) $(build)=scripts/kconfig $@

@@ -1500,7 +1500,7 @@ endif
        $(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)

 # Modules
-/ %/: prepare scripts FORCE
+%/: prepare scripts FORCE
        $(cmd_crmodverdir)
        $(Q)$(MAKE) KBUILD_MODULES=$(if $(CONFIG_MODULES),1) \
        $(build)=$(build-dir)
diff --git a/arch/x86/boot/boot.h b/arch/x86/boot/boot.h
index d2b5adf4..634bf900 100644
--- a/arch/x86/boot/boot.h
+++ b/arch/x86/boot/boot.h
@@ -109,19 +109,19 @@ typedef unsigned int addr_t;
 static inline u8 rdfs8(addr_t addr)
 {
        u8 v;
-       asm volatile("movb %%fs:%1,%0" : "=r" (v) : "m" (*(u8 *)addr));
+       asm volatile("movb %%fs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
        return v;
 }
 static inline u16 rdfs16(addr_t addr)
 {
        u16 v;
-       asm volatile("movw %%fs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
+       asm volatile("movw %%fs:%1,%0" : "=q" (v) : "m" (*(u16 *)addr));
        return v;
 }
 static inline u32 rdfs32(addr_t addr)
 {
        u32 v;
-       asm volatile("movl %%fs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
+       asm volatile("movl %%fs:%1,%0" : "=q" (v) : "m" (*(u32 *)addr));
        return v;
 }

@@ -141,19 +141,19 @@ static inline void wrfs32(u32 v, addr_t addr)
 static inline u8 rdgs8(addr_t addr)
 {
        u8 v;
-       asm volatile("movb %%gs:%1,%0" : "=r" (v) : "m" (*(u8 *)addr));
+       asm volatile("movb %%gs:%1,%0" : "=q" (v) : "m" (*(u8 *)addr));
        return v;
 }
 static inline u16 rdgs16(addr_t addr)
 {
        u16 v;
-       asm volatile("movw %%gs:%1,%0" : "=r" (v) : "m" (*(u16 *)addr));
+       asm volatile("movw %%gs:%1,%0" : "=q" (v) : "m" (*(u16 *)addr));
        return v;
 }
 static inline u32 rdgs32(addr_t addr)
 {
        u32 v;
-       asm volatile("movl %%gs:%1,%0" : "=r" (v) : "m" (*(u32 *)addr));
+       asm volatile("movl %%gs:%1,%0" : "=q" (v) : "m" (*(u32 *)addr));
        return v;
 }

diff --git a/arch/x86/kernel/Makefile_32 b/arch/x86/kernel/Makefile_32
index a7bc93c2..c73320d2 100644
--- a/arch/x86/kernel/Makefile_32
+++ b/arch/x86/kernel/Makefile_32
@@ -58,7 +58,7 @@ targets += vsyscall-note_32.o vsyscall_32.lds

 # The DSO images are built using a special linker script.
 quiet_cmd_syscall = SYSCALL $@
-      cmd_syscall = $(CC) -m elf_i386 -nostdlib $(SYSCFLAGS_$(@F)) \
+      cmd_syscall = $(CC) -m32 -nostdlib $(SYSCFLAGS_$(@F)) \
                          -Wl,-T,$(filter-out FORCE,$^) -o $@

 export CPPFLAGS_vsyscall_32.lds += -P -C -Ui386
```
变更点：
顶层Makefile：make语法变更
arch/x86/boot/boot.h：32位不能使用"=r"，切换为"=q"
arch/x86/kernel/Makefile_32：gcc语法变更  -m elf_i386 改为 -m32

如果是linux2.6.26，仅需要需改两处，并且支持KGDB。
```
diff --git a/Makefile b/Makefile
index e3c5eb66..8d1556b3 100644
--- a/Makefile
+++ b/Makefile
@@ -431,7 +431,7 @@ ifeq ($(config-targets),1)
 include $(srctree)/arch/$(SRCARCH)/Makefile
 export KBUILD_DEFCONFIG

-config %config: scripts_basic outputmakefile FORCE
+%config: scripts_basic outputmakefile FORCE
        $(Q)mkdir -p include/linux include/config
        $(Q)$(MAKE) $(build)=scripts/kconfig $@

@@ -1547,7 +1547,7 @@ endif
        $(Q)$(MAKE) $(build)=$(build-dir) $(target-dir)$(notdir $@)

 # Modules
-/ %/: prepare scripts FORCE
+%/: prepare scripts FORCE
        $(cmd_crmodverdir)
        $(Q)$(MAKE) KBUILD_MODULES=$(if $(CONFIG_MODULES),1) \
        $(build)=$(build-dir)
diff --git a/kernel/timeconst.pl b/kernel/timeconst.pl
index eb51d76e..04612394 100644
--- a/kernel/timeconst.pl
+++ b/kernel/timeconst.pl
@@ -370,7 +370,7 @@ if ($hz eq '--can') {
        }

        @val = @{$canned_values{$hz}};
-       if (!defined(@val)) {
+       if (!@val) {
                @val = compute_values($hz);
        }
        output($hz, @val);
```


```bash
make ARCH=i386 defconfig
make -j20
#成功编译出
Root device is (8, 32)
Setup is 10292 bytes (padded to 10752 bytes).
System is 2592 kB
Kernel: arch/x86/boot/bzImage is ready  (#4)
```



