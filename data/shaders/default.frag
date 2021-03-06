#version 130

in vec3 cameraSpacePosition;
in vec3 vertexNormal;

// Lighting parameters
uniform vec3 sunPosition;
uniform vec4 sunIntensity;
uniform vec4 ambientIntensity;
uniform vec4 diffuseColor;
uniform float attenuationFactor;
uniform float invgamma;

out vec4 outputColor;

vec4 applyLightIntensity(in vec3 cameraSpacePosition, out vec3 dirToLightSource)
{
    vec3 lightDifference =  sunPosition - cameraSpacePosition;
    float lightDistanceSqr = dot(lightDifference, lightDifference);
    dirToLightSource = lightDifference * inversesqrt(lightDistanceSqr);
    
    return sunIntensity / ( 1.0 + attenuationFactor * lightDistanceSqr);
}

void main()
{
	// Angle of incidence calculation
    vec3 dirToSun = vec3(0.0);
    vec4 attenIntensity = applyLightIntensity(cameraSpacePosition, dirToSun);
    float cosAI_sun = clamp(dot(vertexNormal, dirToSun), 0, 1);

    // Output including ambient and diffuse lighting
    outputColor = diffuseColor * ambientIntensity
            + diffuseColor * attenIntensity * cosAI_sun;
	
    // Gamma correction
	outputColor.xyz = pow(outputColor.xyz, vec3(invgamma));
}
