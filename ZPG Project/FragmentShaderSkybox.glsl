#version 400


in vec3 TexCoords;


out vec4 frag_colour;


uniform samplerCube skybox;




void main() {

	

	frag_colour = texture(skybox, TexCoords);
	//frag_colour = vec4(1,1,1,1);


}