[TOC]

### 指针与布尔逻辑
```c
void *p;
if (!p)  和  if (NULL == p)  
```

### memcpy对齐
64bit 机器上，使用 memcpy(p1, p2, size);
bus error
p1 没有64bit对齐
