#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 vp;
uniform mat4 model;
uniform vec3 lightDir;
uniform vec4 lightColor;

void main(void)
{
	crntPos = vec3(model* vec4(aPos, 1.0f));
	Normal =mat3(transpose(inverse(model))) * aNormal;

 	vec4 tmp = lightColor * 0.3 + lightColor * max(dot(Normal, lightDir), 0.0);
	color=tmp.rgb;

	gl_Position = vp *vec4(crntPos,1.0);
}
