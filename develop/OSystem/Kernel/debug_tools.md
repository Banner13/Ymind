[TOC]

### dump_stack()
	打印函数调用关系

### 应用层实现
```
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void dump_stack(void) {
    void* stack_trace[10];
    int stack_depth = backtrace(stack_trace, 10);
    char** stack_symbols = backtrace_symbols(stack_trace, stack_depth);

    printf("Stack trace:\n");
    for (int i = 0; i < stack_depth; i++) {
        printf("  %s\n", stack_symbols[i]);
    }

    free(stack_symbols);
}
```