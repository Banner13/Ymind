
- 使用 `diff -u` 生成补丁，比较原始源码和修改后的源码：
``` bash
diff -uNr <source_dir>.orig <source_dir> > my_patch.patch

#- 其中：
#    - `-u` 选项生成统一格式的补丁。
#    - `-N` 选项表示处理新增的文件。
#    - `-r` 选项表示递归比较子目录。
```