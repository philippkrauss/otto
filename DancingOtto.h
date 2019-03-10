#ifndef __DANCING_OTTO_H__
#define __DANCING_OTTO_H__

#include "Otto.h"

class DancingOtto
{
  public:
	void setup();
	void dance();

  private:
	void obstacleMode();
	Otto Otto;
	bool obstacleDetected = false;
	int distance = 0;
};

#endif // __DANCING_OTTO_H__ //