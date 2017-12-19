#pragma once
#include "stdafx.h"
#include "Subject.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/quaternion.hpp>

struct LightStruct
{
	glm::vec4 position;
	glm::vec3 intensities; //a.k.a. the color of the light
	float attenuation;
	float ambientCoefficient;
	float coneAngle; // new
	glm::vec3 coneDirection;
};



class Light{
public:
	Light(LightStruct lightStruct);

	void changePosition(float, float, float);
	void rotateAroundPoint(glm::vec3, glm::vec3);

	LightStruct getLightProperties();

	


private:
	LightStruct light;

	
};