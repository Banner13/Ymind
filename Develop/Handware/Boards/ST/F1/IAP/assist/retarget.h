#ifndef _RETARGET_H__

#define _RETARGET_H__

#include "stm32f10x_usart.h"

#include <sys/stat.h>

#include <stdio.h>

void RetargetInit(USART_TypeDef *huart);

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

int _fstat(int fd, struct stat *st);

#endif //#ifndef _RETARGET_H__ 
// 作者：稚晖君 https://www.bilibili.com/read/cv6308000?spm_id_from=333.999.0.0 出处：bilibili