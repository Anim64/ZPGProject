#pragma once
#include <GL\glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/quaternion.hpp>
#include "Shader.h"
#include "Subject.h"



class Camera: public Subject {
private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	
	float fov;
	float mouseSensitivity;
	float speed;
	float horizontalAngle;
	float verticalAngle;

	glm::mat4 viewMatrix;
	glm::mat4 projectMatrix;
	float movementSpeed;
	

public:
	Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up);
	glm::mat4 getCamera();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();
	void strafeLeft();
	void strafeRight();
	void forward();
	void backward();

	void mouseUpdate(double newXPos, double newYPos);

	void forceNotify();

	
};