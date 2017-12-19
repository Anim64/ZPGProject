#include "stdafx.h"
#include "Object.h"

//2880
//glDrawArrays(GL_TRIANGLES, 0, 2880);



class Sphere : public Object
{

public:
	Sphere(int shaderKey, glm::vec4);
	float getVerticesCount();

	static const float pocetPrvku;
	static const float sphere[];



};
