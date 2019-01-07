#version 330 core

struct DirectionalLight
{
	vec4 diffuseColour;
	vec4 specularColour;
	vec3 direction;
};

struct PointLight
{
	vec4 diffuseColour;
	vec4 specularColour;
	vec3 position;
};

const int MAX_NO_OF_POINT_LIGHTS=8;

in vec4 vertexColourOut;
in vec2 vertexTextureCoordOut;
in vec3 vertexNormalOut;
in vec3 viewDirection;
in vec3 worldVertexPosition;

out vec4 colour;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

uniform sampler2D diffuseTextureTree;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularMaterialPower;
uniform float lightIntensity;

uniform DirectionalLight directionalLight;                               //

uniform PointLight pointLights[MAX_NO_OF_POINT_LIGHTS];                //
uniform int numberOfPointLights;                                           //

uniform vec4 ambientLightColour;

// The number of different shades of light on the cel shaded model
const float levels = 4.0;


vec4 CalculateLightColour(vec4 diffuseLightColour,vec4 specularLightColour,vec3 lightDirection,vec4 diffuseTextureColour,vec4 specularTextureColour)
{
	float nDotl=clamp(dot(vertexNormalOut,normalize(-lightDirection)),0.0,1.0);

	// Restricts the surface brightness value to one of only a few levels, causing discrete levels of brightness instead of a smooth gradient. 
	// This causes a toon shading effect.
	float brightness = max(nDotl, 0.0); // A brightness value between 1 and zero
	float level = floor(brightness * levels);   // The brightness multiplied by number of total levels rounded down to the nearest int gives
											    // you the the level that brightness value is on.
	brightness = level / levels; // The new brightness lower limit level between 0 and 1.

	vec3 halfWay=normalize(-lightDirection+viewDirection);
	float nDoth=pow(clamp(dot(vertexNormalOut,halfWay),0.0,1.0),specularMaterialPower);

	return 	(diffuseLightColour*nDotl*diffuseMaterialColour*diffuseTextureColour*brightness)+
			(specularLightColour*nDoth*specularMaterialColour*specularTextureColour*0); //eliminate specular lighting for the moment
}

vec4 CalculatePointLight(int currentLightIndex,vec4 diffuseTextureColour,vec4 specularTextureColour)
{
	vec3 lightDirection=worldVertexPosition-pointLights[currentLightIndex].position;
	float lightDistance=length(lightDirection);
	lightDirection=normalize(lightDirection);

	vec4 colour=CalculateLightColour(pointLights[currentLightIndex].diffuseColour,
									pointLights[currentLightIndex].specularColour,
									lightDirection,
									diffuseTextureColour,specularTextureColour);

	// As lightIntensity changes in game update, the strength of the light changeson the models
	float attenuation=1.0/(1.0+0.1*lightIntensity*0.001*lightDistance+0.01*lightDistance*lightDistance);

	return colour*attenuation;
}

vec4 CalculateDirectionLightColour(vec4 diffuseTextureColour,vec4 specularTextureColour)
{
	return CalculateLightColour(directionalLight.diffuseColour,
								directionalLight.specularColour,
								directionalLight.direction,
								diffuseTextureColour,specularTextureColour);
}


void main()
{
	

	

	vec4 diffuseTextureColour=texture(diffuseTexture,vertexTextureCoordOut);

	vec4 specularTextureColour=texture(specularTexture,vertexTextureCoordOut);

	vec4 finalColour=CalculateDirectionLightColour(diffuseTextureColour,specularTextureColour);

	for (int i=0;i<numberOfPointLights;i++)
	{
		finalColour+=CalculatePointLight(i,diffuseTextureColour,specularTextureColour);
	}

	colour=(ambientLightColour*ambientMaterialColour)+finalColour;
}