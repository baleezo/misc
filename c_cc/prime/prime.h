#ifndef __PRIME
#define __PRIME

#define SETBIT(table, n) (table[n>>5] |= 1<<(n & 31))
#define RESETBIT(table, n) (table[n>>5] &= ~(1 << (n &31)))
#define TESTBIT(table, n) (table[n >> 5] >> (n & 31) & 1)

unsigned long *table;
char *ctable;



void prime(int range);
void prime_bitmap(int range);

#endif
