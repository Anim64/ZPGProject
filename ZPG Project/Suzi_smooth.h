#include "stdafx.h"
#include "Object.h"

//2880
//glDrawArrays(GL_TRIANGLES, 0, 2880);



class Suzi_smooth : public Object
{

public:
	Suzi_smooth(int shaderKey, glm::vec4);
	float getVerticesCount();

	static const float pocetPrvku;
	static const float suzi_smooth[];



};