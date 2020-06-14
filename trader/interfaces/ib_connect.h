/*
	Title:
		IB Connect

	Description:
		This class is responsible for the platform side connection to the
		TWS platform. The main object of this class is to interface with
		the IB Wrapper and extend functionality as needed.

	Author:
		Elvis Payano
*/

#ifndef IB_CONNECT_H
#define IB_CONNECT_H

// Interface Includes
#include "ib_wrapper.h"

class IBConnect : public IBWrapper {
public:
	IBConnect(void);
	~IBConnect(void);
};

#endif /* IB_CONNECT_H */