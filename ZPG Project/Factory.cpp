#include "stdafx.h"

#include "Factory.h"

Camera* Factory::createCamera(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	return new Camera(eye, target, up);
}

Light Factory::createDirectionalLight(glm::vec3 position, glm::vec3 intensities, float ambientCoefficient)
{
	LightStruct directionalLight;
	directionalLight.position = glm::vec4(position, 0); 
	directionalLight.intensities = intensities; 
	directionalLight.ambientCoefficient = ambientCoefficient;

	Light light(directionalLight);
	return light;
	
}


Light Factory::createPointLight(glm::vec3 position, glm::vec3 intensities, float attenuation, float ambientCoefficient)
{
	LightStruct pointLight;
	pointLight.position = glm::vec4(position, 1);
	pointLight.intensities = intensities;
	pointLight.ambientCoefficient = ambientCoefficient;
	pointLight.attenuation = attenuation;
	pointLight.coneAngle = 360.0;
	pointLight.coneDirection = glm::vec3(0, 1, 0);

	Light light(pointLight);
	return light;
}

Light Factory::createSpotLight(glm::vec3 position, glm::vec3 intensities, float attenuation, float ambientCoefficient, float coneAngle, glm::vec3 coneDirection)
{
	LightStruct pointLight;
	pointLight.position = glm::vec4(position, 1);
	pointLight.intensities = intensities;
	pointLight.ambientCoefficient = ambientCoefficient;
	pointLight.attenuation = attenuation;
	pointLight.coneAngle = coneAngle;
	pointLight.coneDirection = coneDirection;

	Light light(pointLight);
	return light;


}