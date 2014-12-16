#include <allegro5/allegro_primitives.h>
#include "DoublePendulum.h"
#include <math.h>

using namespace std;

void DoublePendulum::SetCoordinatesFromAngle()
{
	  x1 = jointX + length1 * sin(theta1);
	  x2 = x1 + length2 * sin(theta2);
	  
	  y1 = jointY -length1 * cos(theta1);
	  y2 = y1 -length2 * cos(theta2);
}

void DoublePendulum::Init(float lengthOne, float lengthTwo, float mass1, float mass2, float thetaOne, float thetaTwo, 
						  float jX, float jY)
{
	presets[0] = thetaOne;
	presets[1] = thetaTwo;


	jointX = jX;
	jointY = jY;

	length1 = lengthOne;
	length2 = lengthTwo;

	m1 = mass1;
	m2 = mass2;

	theta1 = thetaOne;
	theta2 = thetaTwo;
	
	omega1 = 0;
	omega2 = 0;

	dt = 0.001;
}

void DoublePendulum::Update()
{
	RungeKuttaMethod();
	SetCoordinatesFromAngle();
}

void DoublePendulum::IncreaseRodLength(int id, float amount)
{
	if(-amount >= length1 || -amount >= length2) return;

	id--;
	if(id)
		length2 += amount;
	else
		length1 += amount;
	Init(length1, length2, m1, m2, presets[0], presets[1], jointX, jointY);
}

void DoublePendulum::IncreaseParticleMass(int id, float amount)
{
	if(-amount >= m1 || -amount >= m2) return;

	id--;
	if(id)
		m2 += amount;
	else
		m1 += amount;

	Init(length1, length2, m1, m2, presets[0], presets[1], jointX, jointY);
}

void DoublePendulum::IncreaseAngle(int id, float amount)
{
	if(theta1 + amount > 2*ALLEGRO_PI)
		theta1 = 0;
	else if(theta1 + amount < 0)
		theta1 = 2*ALLEGRO_PI;
	if(theta2 + amount > 2*ALLEGRO_PI)
		theta2 = 0;
	else if(theta2 + amount < 0)
		theta2 = 2*ALLEGRO_PI;
		
	id--;
	if(id)
		presets[0] += amount;
	else
		presets[1] += amount;

	Init(length1, length2, m1, m2, presets[0], presets[1], jointX, jointY);
}

float DoublePendulum::CalculateAcceleration(float angle1, float omega1, float angle2, 
											float omega2, int id)
{
	float deltaTheta = angle1 - angle2;
	
	id--;

	if(!id)
		return -(m2*length1*omega1*omega1 * sin(deltaTheta)*cos(deltaTheta) + m2*g*sin(theta2)*cos(deltaTheta) + m2*length2*omega2*omega2 * sin(deltaTheta) - (m1 + m2)*g*sin(theta1))/((m1 + m2)*length1 - m2*length1*cos(deltaTheta)*cos(deltaTheta));
	else
		return -(-m2*length2*omega2*omega2 * sin(deltaTheta)*cos(deltaTheta) + (m1 + m2)*(g*sin(theta1)*cos(deltaTheta) - length2*omega1*omega1*sin(deltaTheta) - g*sin(theta2)))/((m1 + m2)*length2 - m2*length2*cos(deltaTheta)*cos(deltaTheta));

}

void DoublePendulum::RungeKuttaMethod()
{
	float aux_theta1[4];
	float aux_theta2[4];
	float aux_omega1[4];
	float aux_omega2[4];
	float aux_epsilon1[4];
	float aux_epsilon2[4];

	aux_theta1[0] = theta1;
	aux_omega1[0] = omega1;
	aux_theta2[0] = theta2;
	aux_omega2[0] = omega2;

	aux_epsilon1[0] = CalculateAcceleration(aux_theta1[0], aux_omega1[0], aux_theta2[0], aux_omega2[0], 1);
	aux_epsilon2[0] = CalculateAcceleration(aux_theta1[0], aux_omega1[0], aux_theta2[0], aux_omega2[0], 2);

	aux_theta1[1] = aux_theta1[0] + 0.5 * aux_omega1[0] * dt;
	aux_omega1[1] = aux_omega1[0] + 0.5 * aux_epsilon1[0] * dt;
	aux_theta2[1] = aux_theta2[0] + 0.5 * aux_omega2[0] * dt;
	aux_omega2[1] = aux_omega2[0] + 0.5 * aux_epsilon2[0] * dt;

	aux_epsilon1[1] = CalculateAcceleration(aux_theta1[1], aux_omega1[1], aux_theta2[1], aux_omega2[1], 1);
	aux_epsilon2[1] = CalculateAcceleration(aux_theta1[1], aux_omega1[1], aux_theta2[1], aux_omega2[1], 2);

	aux_theta1[2] = aux_theta1[0] + 0.5 * aux_omega1[1] * dt;
	aux_omega1[2] = aux_omega1[0] + 0.5 * aux_epsilon1[1] * dt;
	aux_theta2[2] = aux_theta2[0] + 0.5 * aux_omega2[1] * dt;
	aux_omega2[2] = aux_omega2[0] + 0.5 * aux_epsilon2[1] * dt;

	aux_epsilon1[2] = CalculateAcceleration(aux_theta1[2], aux_omega1[2], aux_theta2[2], aux_omega2[2], 1);
	aux_epsilon2[2] = CalculateAcceleration(aux_theta1[2], aux_omega1[2], aux_theta2[2], aux_omega2[2], 2);

	aux_theta1[3] = aux_theta1[0] + 0.5 * aux_omega1[2] * dt;
	aux_omega1[3] = aux_omega1[0] + 0.5 * aux_epsilon1[2] * dt;
	aux_theta2[3] = aux_theta2[0] + 0.5 * aux_omega2[2] * dt;
	aux_omega2[3] = aux_omega2[0] + 0.5 * aux_epsilon2[2] * dt;

	aux_epsilon1[3] = CalculateAcceleration(aux_theta1[3], aux_omega1[3], aux_theta2[3], aux_omega2[3], 1);
	aux_epsilon2[3] = CalculateAcceleration(aux_theta1[3], aux_omega1[3], aux_theta2[3], aux_omega2[3], 2);

	theta1 = aux_theta1[0] + (dt/6.0) * (aux_omega1[0] + 2 * aux_omega1[1] + 2 * aux_omega1[2] + aux_omega1[3]);
	omega1 = aux_omega1[0] + (dt/6.0) * (aux_epsilon1[0] +  2 * aux_epsilon1[1] + 2 * aux_epsilon1[2] + aux_epsilon1[3]);

	theta2 = aux_theta2[0] + (dt/6.0) * (aux_omega2[0] + 2 * aux_omega2[1] + 2 * aux_omega2[2] + aux_omega2[3]);
	omega2 = aux_omega2[0] + (dt/6.0) * (aux_epsilon2[0] +  2 * aux_epsilon2[1] + 2 * aux_epsilon2[2] + aux_epsilon2[3]);
}

void DoublePendulum::Render()
{
	//rods
	al_draw_line(jointX, jointY, x1, y1, al_map_rgb(150, 150, 150), 10);
	al_draw_line(x1, y1, x2, y2, al_map_rgb(150, 150, 150), 10);

	//masses
	al_draw_filled_circle(x1, y1, 5*m1, al_map_rgb(40, 163, 204));
	al_draw_filled_circle(x2, y2, 5*m2, al_map_rgb(40, 163, 204));
}
