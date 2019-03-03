#ifndef __LEDMATRIX_H__
#define __LEDMATRIX_H__

#include "MaxMatrix.h"

class LedMatrix
{
public:
	LedMatrix(char din_pin = 10, char clk_pin = 11, char cs_pin = 12) : maxMatrix(din_pin, cs_pin, clk_pin, 1) 
	{
		maxMatrix.init();
	}

	void writeFull(unsigned long value);

	void clearMatrix(void);
private:
	MaxMatrix maxMatrix;

};

#endif // LEDMATRIX_H //