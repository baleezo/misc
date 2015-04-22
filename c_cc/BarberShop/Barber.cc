#include <cstdio>
#include "BarberShop.h"
#include "Barber.h"

#define FREE(x) do {\
								if ((x) != NULL)\
								{\
									free(x);\
									x = NULL;\
								}\
								} while (0)

void *aBarber(void *pvParam)
{
	TThreadParam *ptThreadParam = (TThreadParam *) pvParam;
	CBarberShop *pBarberShop = ptThreadParam->pBarberShop;
	int iBarberID = ptThreadParam->iBarberID;
	
	while (pBarberShop->ShopOpening())
	{
		pBarberShop->GetNextCustomer(iBarberID);
	}
	
	printf("Barber %d relaxes\n", iBarberID + 1);
	pthread_exit(0);
}

CBarber::CBarber(CBarberShop *pBarberShop):
	m_Barbers(),
	m_patThreadParam((TThreadParam *)calloc(NUM_OF_BARBERS, sizeof (TThreadParam))),
	m_attr()
{
	pthread_attr_init(&m_attr);
	pthread_attr_setscope(&m_attr, PTHREAD_SCOPE_SYSTEM);
	for (int i = 0; i < NUM_OF_BARBERS; i++)
	{
		m_patThreadParam[i].iBarberID = i;
		m_patThreadParam[i].pBarberShop = pBarberShop;
		pthread_t tid = 0;
		int iRes = pthread_create(&tid, &m_attr, aBarber, (void *) &m_patThreadParam[i]);
		if (iRes != 0)
		{
			printf ("WARNING: Barber %d does not work\n", i + 1);
		}
		else
		{
			m_Barbers.push_back(tid);
		}
	}
}

CBarber::~CBarber()
{
	FREE(m_patThreadParam);
	pthread_attr_destroy(&m_attr);
}

void CBarber::WaitBarberFinish() const
{
	for (pthread_t tid : m_Barbers)
		pthread_join(tid, NULL);
	
	printf("\nAll the barbers have done their job\n");
}
