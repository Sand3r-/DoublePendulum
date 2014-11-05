#include "DoublePendulum.h"
#include <math.h>

float DoublePendulum::GetX(int id) const
{
	id--;
	if(id)
		return x2;
	else
		return x1;
}

float DoublePendulum::GetY(int id) const
{
	id--;
	if(id)
		return y2;
	else
		return y1;
}

void DoublePendulum::SetCoordinatesFromAngle()
{
	  x1 = length1 * sin(theta1);
	  x2 = x1 + length2 * sin(theta2);
	  
	  y1 = -length1 * cos(theta1);
	  y2 = y1 -length2 * cos(theta2);
}

void DoublePendulum::Init(float lengthOne, float lengthTwo, float mass1, float mass2, float thetaOne, float thetaTwo)
{
	length1 = lengthOne;
	length2 = lengthTwo;

	m1 = mass1;
	m2 = mass2;

	theta1 = thetaOne;
	theta2 = thetaTwo;
}

void DoublePendulum::Update()
{
	
}

void DoublePendulum::Render()
{
	
}
