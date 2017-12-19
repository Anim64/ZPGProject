#version 400

layout(location = 0)in vec3 position;




out vec3 TexCoords;


uniform mat4 ModelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;




void main () {

	vec4 pos = (projectionMatrix * viewMatrix * ModelMatrix) * vec4(position, 1.0);
	gl_Position = pos.xyww;
	

	TexCoords = position;

  

}
