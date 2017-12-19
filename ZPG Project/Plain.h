#include "stdafx.h"
#include "Object.h"

//2880
//glDrawArrays(GL_TRIANGLES, 0, 2880);



class Plain : public Object
{

public:
	Plain(int shaderKey, glm::vec4);
	Plain(int shaderKey, int textureKey);
	float getVerticesCount();

	static const float pocetPrvku;
	static const float plain[];



};