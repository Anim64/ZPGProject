#version 400

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;



out vec4 frag_colour;


uniform mat4 ModelMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec4 objectColour;



void main () {
	
	vec3 lightColor = vec3(0.5, 0.5, 0.5);
	
	

	//ambient
	float ambientStrenght = 0.1f;
	vec3 ambient = ambientStrenght * lightColor;

	//diffuse

	vec3 N = normalize(ex_worldNormal);
	vec3 lightDirection = normalize(lightPosition - ex_worldPosition);
	float diff = max(dot(N, lightDirection), 0.0);

	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrenght = 1.0f;
	vec3 viewDirection = normalize(cameraPosition - ex_worldPosition);
	vec3 reflectDirection = reflect(-lightDirection, N);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
	vec3 specular = specularStrenght * spec * lightColor;


	vec3 result = (ambient + diffuse + specular);

	
	frag_colour = vec4(result, 1.0f) * objectColour;
	
	

	/*vec3 lightColor = vec3(1,1,1);
	float LightPower = 0.5f;


	vec3 MaterialDiffuseColor = vec3(0.385, 0.647, 0.812);
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

	// Distance to the light
	float distance = length(lightPosition - ex_worldPosition.xyz);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(ex_worldNormal);

	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(LightDirection_cameraspace);

	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(n, l), 0, 1);

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);

	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, n);

	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E, R), 0, 1);

	frag_colour =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor  * lightColor* LightPower * (cosTheta / (distance*distance)) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor  * lightColor* LightPower * (pow(cosAlpha, 5) / (distance*distance));*/

	

	
}

/*#version 400

in vec4 ex_worldPosition;
in vec4 ex_worldNormal;

out vec4 frag_colour;



void main() {
	vec4 lightColor = vec4(0.8, 0.0, 0.0, 1.0);
	vec4 N = normalize(ex_worldNormal);

	vec3 lightPos = vec3(0, 0, 0);
	vec4 lightVector = normalize(vec4(lightPos, 1));

	//difuse
	float diffuseStrength = 1.2;
	float dot_product = max(dot(lightVector, N), 0.0);
	vec4 diffuse = dot_product * vec4(0.5, 0.3, 0.2, 1.0) * diffuseStrength;


	//ambient
	float ambStrength = 0.3f;
	vec4 ambient = lightColor * ambStrength;


	




	frag_colour = (ambient + diffuse);



	vec4 lightVector = normalize(vec4(0.0,0.0,0.0,1.0));
	float dot_product = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);


	vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);

	vec4 ambient = lightColour;


	float specStrength = 25.0f;
	vec4 viewDir = normalize(vec4(viewPos, 1.0) - ex_worldPosition);
	vec4 reflectDir = reflect(-lightVector, normalize(ex_worldNormal));
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);
	vec4 specular = specStrength * spec * lightColour;

	frag_colour = (ambient + diffuse + specular);
}*/
