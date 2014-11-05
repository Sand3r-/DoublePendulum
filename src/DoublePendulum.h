#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class DoublePendulum
{
	float x1;
	float x2;

	float y1;
	float y2;
	
	float v1;
	float v2;

	float a1;
	float a2;

	float theta1;
	float theta2;

	float omega1;
	float omega2;

	float length1;
	float length2;

	float m1;
	float m2;

	float dt;

public:
	DoublePendulum();
	~DoublePendulum();

	float GetX(int id) const;
	float GetY(int id) const;

	void SetCoordinatesFromAngle();

	void Init(float lenghtOne, float lengthTwo, float mass1, float mass2, float thetaOne, float thetaTwo);
	void Update();
	void Render();
};