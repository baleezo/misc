#include <cstdio>
#include <unistd.h>
#include <ctime>
#include "BarberShop.h"
#include "Barber.h"
#define ADD_CUSTOMER    '1'
#define CLOSE_SHOP      '2'
#define SERVE_PERIOD_MAX 5
#define NOT_FOUND       -1
#define SERVING         -2

CBarberShop::CBarberShop():
	m_Getche(),
	m_pBarbers(NULL),
	m_Bench(),
	m_Chairs(NUM_OF_BARBERS, CHAIR_INIT),
	m_iIdleBarbers(0),
	m_bOpen(false),
	m_mutex(),
	m_wakeup_barber()
{
	srand(time(NULL));
	pthread_mutex_init(&m_mutex, NULL);
	pthread_cond_init(&m_wakeup_barber, NULL);
}

CBarberShop::~CBarberShop()
{
	if (m_pBarbers != NULL)
	{
		delete m_pBarbers;
		m_pBarbers = NULL;
	}
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_wakeup_barber);
}

void CBarberShop::OpenShop()
{
	printf("The barbershop is open\n");
	
	m_bOpen = true;

	m_pBarbers = new CBarber(this);
	
	int iKin = 0, iCustomer = 0;

	while ((iKin = m_Getche.getche()) != CLOSE_SHOP)
	{
		if (iKin == ADD_CUSTOMER)
		{
			iCustomer++;
			printf("Customer %d enters the shop\n", iCustomer);
			NewCustomer(iCustomer);
		}
	}
	
	ReadyToClose();
}

inline int CBarberShop::GetEmptyChair() const
{
	for (int i = 0; i < NUM_OF_BARBERS; i++)
	{
		if (m_Chairs[i] == EMPTY)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

void CBarberShop::NewCustomer(const int iCustomerID)
{
	pthread_mutex_lock(&m_mutex);

	int iEmptyChair = NOT_FOUND;
	if ((iEmptyChair = GetEmptyChair()) != NOT_FOUND)
	// Checks if there is idle barber?
	// If yes, go to the seat and wakeup the barber
	{
		m_Chairs[iEmptyChair] = iCustomerID;
		pthread_cond_broadcast(&m_wakeup_barber);
	}
	else if (m_Bench.size() < NUM_OF_BENCHES)
	// Checks if there is empty bench; if yes, go to wait
	{
		printf("Customer %d goes to bench seat %d\n", iCustomerID, (int) m_Bench.size() + 1);
		m_Bench.push(iCustomerID);
	}
	else
	// All barbers are busy and bench is full, leaves the shop
	{
		printf("Bench is full, customer %d leaves\n", iCustomerID);
	}

	pthread_mutex_unlock(&m_mutex);
}

void CBarberShop::GetNextCustomer(const int iBarberID)
{
	bool bServeCustomer = true;
	int  iCustomerID    = 0;

	pthread_mutex_lock(&m_mutex);

	if (!m_Bench.empty())
	// Checks if there is any customer waiting on the bench
	{
		iCustomerID = m_Bench.front();
		m_Bench.pop();
	}
	else
	// Go to sleep and wait new customer
	{
		m_Chairs[iBarberID] = EMPTY;//declare the chair is empty
		while (m_bOpen && m_Chairs[iBarberID] == EMPTY)
		{
			pthread_cond_wait(&m_wakeup_barber, &m_mutex);
		}
		iCustomerID = m_Chairs[iBarberID]; 
	}
	
	// Ready to serve customer
	bServeCustomer = m_bOpen;
	m_Chairs[iBarberID] = SERVING;
	
	pthread_mutex_unlock(&m_mutex);

	if (bServeCustomer)
		// Serves Customer
	{
		printf("Barber %d serves Customer %d\n", iBarberID + 1, iCustomerID);
		int iServeTime = (rand() % SERVE_PERIOD_MAX) + 1;
		sleep(iServeTime);
		printf("Barber %d has done Customer %d\n", iBarberID + 1, iCustomerID);
	}

}

void CBarberShop::ReadyToClose()
{
	printf("\nReady to close\n\n");

	pthread_mutex_lock(&m_mutex);

	m_bOpen = false;

	for(int i = 0; i < NUM_OF_BARBERS; i++)
		if (m_Chairs[i] > 0)
		//m_Chairs[i] != EMPTY, SERVING, and  CHAIR_INIT
			printf("Customer %d leaves\n", m_Chairs[i]);
	
	while (m_Bench.size() != 0)
	{
		int iCustomerID = m_Bench.front();
		m_Bench.pop();
		printf("Customer %d leaves\n", iCustomerID);
	}
	
	pthread_cond_broadcast(&m_wakeup_barber);

	pthread_mutex_unlock(&m_mutex);
	
	// Wait barbers finish jobs
	m_pBarbers->WaitBarberFinish();

	// Really close the shop
	CloseShop();
}

void CBarberShop::CloseShop() const
{
	printf("\nClose shop\n\n");
}
