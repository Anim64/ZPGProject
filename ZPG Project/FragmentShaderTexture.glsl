#version 400

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 TexCoord;
in vec3 ex_worldTangent;


out vec4 frag_colour;




uniform mat4 ModelMatrix;
uniform mat4 viewMatrix;
uniform vec3 cameraPosition;
uniform vec3 objectColour;

uniform sampler2D textura;
uniform sampler2D normalMapTex;

#define MAX_LIGHTS 10;
uniform int numberOfLights;

struct Light
{
	vec4 position;
	vec3 intensities; //a.k.a the color of the light
	float attenuation;
	float ambientCoefficient;
	float coneAngle;
	vec3 coneDirection;
};

uniform Light allLights[10];


vec3 ApplyLight(Light light, vec3 normal, vec3 surfaceColour, vec3 worldPosition, vec3 surfaceToCamera)
{
	vec3 surfaceToLight;
	float attenuation = 1.0;
	if (light.position.w == 0.0) {
		//directional light
		surfaceToLight = normalize(light.position.xyz);
		attenuation = 1.0; //no attenuation for directional lights
	}
	else {
		//point light
		surfaceToLight = normalize(light.position.xyz - ex_worldPosition);
		float distanceToLight = length(light.position.xyz - ex_worldPosition);
		attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

		float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
		if (lightToSurfaceAngle > light.coneAngle) {
			attenuation = 0.0;
		}
	}

	vec3 ambient = light.ambientCoefficient * surfaceColour.rgb * light.intensities;

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * surfaceColour.rgb * light.intensities;

	float specularCoefficient = 0.0;
	if (diffuseCoefficient > 0.0)
	{
	
		specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))), 1.5);
	}
	

	vec3 specular = specularCoefficient * light.intensities;


	return ambient + attenuation*(diffuse + specular);
}

vec3 calcNormal()
{
	vec3 normal = normalize(ex_worldNormal);
	vec3 tangent = normalize(ex_worldTangent);
	//Gram–Schmidt process
	tangent = normalize(tangent - dot(tangent, normal) * normal);
	vec3 bitangent = cross(tangent, normal);
	vec3 bumpMapNormal = texture(normalMapTex, TexCoord).xyz;
	//pøevod z vektoru barvy o rozsahu <0,1> do vektoru normály <-1,1>
	bumpMapNormal = 2.0 * bumpMapNormal - vec3(1.0, 1.0, 1.0);
	// Transformaèní  matice TBN
	mat3 TBN = mat3(tangent, bitangent, normal);
	return normalize(TBN * bumpMapNormal);
}


void main() {

	vec4 TexColour = texture(textura, TexCoord);

	//vec3 N = normalize(ex_worldNormal);

	vec3 N = calcNormal();
	vec3 surfaceToCamera = normalize(cameraPosition - ex_worldPosition);


	vec3 result = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < numberOfLights; i++)
	{
		result += ApplyLight(allLights[i], N ,TexColour.rgb, ex_worldPosition, surfaceToCamera);
	}



	frag_colour = vec4(result, 1.0f);


}