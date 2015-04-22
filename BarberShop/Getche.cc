#include <cstdio>
#include <unistd.h>
#include "Getche.h"

CGetche::CGetche():
	m_tOld_tio()
{
	tcgetattr(STDIN_FILENO, &m_tOld_tio);
	struct termios tNew_tio = m_tOld_tio;
	tNew_tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &tNew_tio);
}

CGetche::~CGetche()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &m_tOld_tio);
}

int CGetche::getche() const
{
	return getchar();
}
