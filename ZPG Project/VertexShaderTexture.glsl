#version 400

layout(location = 0)in vec3 position;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 texCoord;
layout(location = 3)in vec3 tangent;

out vec3 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 TexCoord;
out vec3 ex_worldTangent;
//out vec3 EyeDirection_cameraspace;
//out vec3 LightDirection_cameraspace;

uniform mat4 ModelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;




void main () {

	gl_Position = (projectionMatrix * viewMatrix * ModelMatrix) * vec4 (position, 1.0);
	ex_worldPosition = (ModelMatrix * vec4(position, 1.0)).xyz;
  

  
	ex_worldNormal = mat3(transpose(inverse(ModelMatrix))) * normal;
	ex_worldTangent = tangent;


	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);

  

}
