#ifndef _BARBER_H
#define _BARBER_H

typedef struct T_Thread_Param
{
	int iBarberID;
	CBarberShop *pBarberShop;
} TThreadParam;

class CBarberShop;

class CBarber
{
public:
	CBarber(CBarberShop *pBarberShop);
	~CBarber();
	void WaitBarberFinish() const;
private:
	// Disable copying
	CBarber(const CBarber &barber);
	CBarber &operator=(const CBarber &barber);
	
	std::vector <pthread_t> m_Barbers;
	TThreadParam *m_patThreadParam;
	pthread_attr_t m_attr;
};

#endif
