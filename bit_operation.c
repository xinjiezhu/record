/*
 * bit operation
 */

#define u16 unsigned short
#define VOLAT_U16(x)     (*(volatile u16 *)(&(x))) /*get value from memory every time, other than buffer*/
#define BIT 6
u16 x;

bit_operation:
    clear:
        VOLAT_U16(x) &= ~(u16)(1<<BIT);
    set:
        VOLAT_U16(x) |= (u16)(1<<BIT);
    check:
        VOLAT_U16(x) &= (u16)(1<<BIT) ? 1:0;