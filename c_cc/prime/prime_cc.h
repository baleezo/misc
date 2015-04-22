#ifndef __PRIME
#define __PRIME

#define SETBIT(table, n) (table[n>>5] |= 1<<(n & 31))
#define RESETBIT(table, n) (table[n>>5] &= ~(1 << (n &31)))
#define TESTBIT(table, n) (table[n >> 5] >> (n & 31) & 1)

class Prime{
	public:
		Prime(int n);
		bool isprime(int n)const;
	protected:
		int range;
		char *ctable;
};

class Prime_Bitmap{
	public:
		Prime_Bitmap(int range);
		bool isprime(int n)const;
	protected:
		int range;
		unsigned long *table;
};
#endif
