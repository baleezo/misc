#ifndef _BARBERSHOP_H
#define _BARBERSHOP_H
#include <cstdlib>
#include <pthread.h>
#include <queue>
#include <vector>
#include "Getche.h"
#define NUM_OF_BARBERS 3
#define NUM_OF_BENCHES 5
#define EMPTY 0
#define CHAIR_INIT -1

class CBarber;

class CBarberShop
{
public:
	CBarberShop();
	~CBarberShop();
	void OpenShop();
	void GetNextCustomer(const int iBarberID);
	bool ShopOpening() const
	{
		return m_bOpen;
	}

private:
	// Disable copying
	CBarberShop(const CBarberShop &barberShop);
	CBarberShop &operator=(const CBarberShop &barberShop);
	
	inline int GetEmptyChair() const;
	void NewCustomer(const int iCustomerID);
	void ReadyToClose();
	void CloseShop() const;
	
	CGetche m_Getche;
	CBarber *m_pBarbers;
	std::queue <int> m_Bench;
	std::vector <int> m_Chairs;
	int m_iIdleBarbers;
	bool m_bOpen;
	pthread_mutex_t m_mutex;
	pthread_cond_t m_wakeup_barber;
};
#endif
