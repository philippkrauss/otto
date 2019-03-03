
#include "LedMatrix.h"

#include "Arduino.h"

void LedMatrix::writeFull(unsigned long value)
{
	// Otto's original mouth definitions are for a 5 row x 6 column Matrix.
	// value's last 6 bits are therefore the last row of the matrix.
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 6; col++) {
			maxMatrix.setDot(6 - col, 4 - row, (0x01 & (value >> row*6+col)));
		}
	}
}

void LedMatrix::clearMatrix(void)
{
	maxMatrix.clear();
}
