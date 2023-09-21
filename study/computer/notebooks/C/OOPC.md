[TOC]



## OOP in C

### 私有变量声明

```c
// Obj.c
#include <stdlib.h>
#include <assert.h>
#include "Obj.h"

struct Private {
        int age;
        int other;
};

Human_t* CreateHuman(void)
{
        Human_t *human = NULL;
        Private_t *unknow;

        human = (Human_t*)malloc(sizeof(Human_t));
        unknow = (Private_t*)malloc(sizeof(Private_t));

        assert(human);
        assert(unknow);

        human->unknow = unknow;
        unknow->age = 10;

        return human;
}

void KillHuman(Human_t *human)
{
        assert(human->unknow);
        assert(human);

        free(human->unknow);
        free(human);

        human->unknow = NULL;
        human = NULL;
}

int GetAge(Human_t *human)
{
        assert(human->unknow);
        assert(human);

        return human->unknow->age;
}

void SetAge(Human_t *human, int age)
{
        assert(human->unknow);
        assert(human);

        human->unknow->age = age;
}
```

```c
// Obj.h
#ifndef OBJ_H
#define OBJ_H

typedef struct Private Private_t;

typedef struct {
    int skinColor;
    int height;
    Private_t *unknow;
} Human_t;

Human_t* CreateHuman(void);
void KillHuman(Human_t *human);

int GetAge(Human_t *human);
void SetAge(Human_t *human, int age);


#endif // OBJ_H
```

```c
#include <stdio.h>
#include "Obj.h"

int main(void)
{
    Human_t *human;

    human = CreateHuman();

    human->skinColor = 0x12;
    human->height    = 0xFF;

    // error
    // human->unknow->age = 0x11;

    *(int*)human->unknow = 0x13;
    printf("age = %d\n", GetAge(human));

    KillHuman(human);
    return 0;
}
```

