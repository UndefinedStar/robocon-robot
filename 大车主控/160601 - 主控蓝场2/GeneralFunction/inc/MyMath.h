#ifndef _MYMATH_H
#define _MYMATH_H

#include <math.h>
#include "rundriver.h"
#include "filter.h"

extern POSITION DTPosition;
extern POSITION CarPosition;
extern SPEED CarSpeeds;
extern float ArmAngle;
extern float DT50distance;

#define PI ((float)3.141592654)

int fsign(float a);
void car_position(void);

#endif
