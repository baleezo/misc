#ifndef _GETCHE_H
#define _GETCHE_H
#include <termios.h>
class CGetche
{
public:
	CGetche();
	~CGetche();
	int getche() const;
private:
	struct termios m_tOld_tio;
};

#endif
