#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class DoublePendulum
{
	//coordinates of joint holding the pendulum
	float jointX;
	float jointY;

	//coordinates of masses 1 and 2 respectively
	float x1;
	float x2;

	float y1;
	float y2;

	//angle between the rod and vertical axis
	float theta1;
	float theta2;

	//angular velocity
	float omega1;
	float omega2;

	//lengths of the rods
	float length1;
	float length2;

	//values of the masses
	float m1;
	float m2;

	//increase of time (used for Runge-Kutta method)
	float dt;

	//gravity constant
	float g;

	//default values
	float presets[2];

public:
	DoublePendulum():g(9.81) {};
	void SetCoordinatesFromAngle();

	void IncreaseRodLength(int id, float amount);
	void IncreaseParticleMass(int id, float amount);
	void DoublePendulum::IncreaseAngle(int id, float amount);

	void Init(float lenghtOne, float lengthTwo, float mass1, float mass2, float thetaOne, float thetaTwo, 
			  float jX, float jY);

	float CalculateAcceleration(float angle1, float omega1, float angle2, float omega2, int id);
	
	void RungeKuttaMethod();

	void Update();
	void Render();
};