#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <stdint.h>

#include "retarget.h"
#if !defined(OS_USE_SEMIHOSTING)

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

USART_TypeDef *gHuart;
#define redirect_send(ch)   USART_SendData(gHuart, (uint16_t)ch);
#define redirect_recive(ch)   USART_ReceiveData(gHuart);


void RetargetInit(USART_TypeDef *huart)
{
    gHuart = huart;
    /* Disable I/O buffering for STDOUT stream, so that
     * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
}

int fputc (int ch, FILE *f)
{
    redirect_send(ch);

    return ch;
}

int _isatty(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    errno = EBADF;
    return 0;
}


int _write(int fd, char *ptr, int len)
{
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO)
    {
        for (int i = 0; i < len; i++)
        {
            redirect_send(*(ptr + i));
        }
        return len;
    }

    errno = EBADF;
    return -1;
}


int _close(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    errno = EBADF;
    return -1;
}


int _lseek(int fd, int ptr, int dir)
{
    (void) fd;
    (void) ptr;
    (void) dir;

    errno = EBADF;
    return -1;
}


int _read(int fd, char *ptr, int len)
{
    if (fd == STDIN_FILENO)
    {
        *ptr = redirect_recive();
         return 1;
    }
    errno = EBADF;
    return -1;
}


int _fstat(int fd, struct stat *st)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}

#endif //#if !defined(OS_USE_SEMIHOSTING) 
// 作者：稚晖君 https://www.bilibili.com/read/cv6308000?spm_id_from=333.999.0.0 出处：bilibili