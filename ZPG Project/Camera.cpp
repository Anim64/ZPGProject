#include "stdafx.h"
#include "Camera.h"


Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up)
{
	
	//this->viewMatrix = glm::mat4(1.0f);



	this->eye = eye;
	this->target = target;
	this->up = up;

	this->fov = 45.0f;

	horizontalAngle = 0.0f;
	verticalAngle = 0.0f;

	movementSpeed = 0.1f;
	
	this->mouseSensitivity = 0.005f;
	

	this->viewMatrix = getCamera();
	this->projectMatrix = glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
	
	
}





glm::mat4 Camera::getCamera() 
{
	return glm::lookAt(eye, eye + target, up);
}


glm::mat4 Camera::getViewMatrix()
{
	this->viewMatrix = getCamera();
	return this->viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return this->projectMatrix;
}



void Camera::strafeLeft()
{
	

	this->eye -= this->movementSpeed * glm::normalize(glm::cross(target, up));
	this->notify(this->getViewMatrix(), this->getProjectionMatrix(), eye);
	
	
}

void Camera::strafeRight()
{
	this->eye += this->movementSpeed * glm::normalize(glm::cross(target, up));
	this->notify(this->getViewMatrix(), this->getProjectionMatrix(),eye);
	
}



void Camera::backward()
{
	this->eye -= this->movementSpeed * target;
	this->notify(this->getViewMatrix(), this->getProjectionMatrix(), eye);
	
}

void Camera::forward()
{
	this->eye += this->movementSpeed * target;
	this->notify(this->getViewMatrix(), this->getProjectionMatrix(), eye);
	
}

void Camera::mouseUpdate(double newXPos, double newYPos)
{

	
	
	horizontalAngle += mouseSensitivity * float(800 / 2 - newXPos);
	verticalAngle += mouseSensitivity * float(600 / 2 - newYPos);

	target = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

	up = glm::cross(right, target);


	this->notify(this->getViewMatrix(), this->getProjectionMatrix(), eye);

	
	
}

void Camera::forceNotify()
{
	this->notify(this->getViewMatrix(), this->getProjectionMatrix(), eye);
}

glm::vec3 Camera::getPosition()
{
	return this->eye;
}
