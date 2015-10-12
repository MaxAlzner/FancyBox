#version 150

in vec4 vertex;
in vec2 uv;
in vec3 normal;
in vec3 tangent;
in vec3 binormal;
in ivec4 weights;
in ivec4 boneIndices;

out vec2 texcoord;
out vec4 vertex_ls;
out vec3 vertex_ss;
out vec3 view_ss;

out vec4 vertex_def;
out vec3 normal_def;
out vec3 tangent_def;
out vec3 binormal_def;

out vec3 directionalLight_ss;
out PointLight
{
	vec4 position;
	vec4 color;
	float intensity;
	float range;
} pointLights_ss[4];

uniform mat4 os_to_ws;
uniform mat4 ws_to_cs;
uniform mat4 ws_to_ls;
uniform mat4 projection;
uniform mat4 bones[32];

uniform vec3 directionalLight_ws;
uniform PointLight
{
	vec4 position;
	vec4 color;
	float intensity;
	float range;
} pointLights_ws[4];
uniform int numOfPointLights;

uniform vec2 uvRepeat;
uniform vec2 uvOffset;

uniform int mode;

void main()
{
	texcoord = (uv * uvRepeat) + uvOffset;
	vec4 vertex_ws = os_to_ws * vertex;
	vec4 vertex_cs = ws_to_cs * vertex_ws;
	gl_Position = projection * vertex_cs;
	
#if 0
	vertex_ls = ws_to_ls * vertex_ws;
#endif
	
	mat4 os_to_cs = ws_to_cs * os_to_ws;
	vec3 normal_cs =   normalize((os_to_cs * vec4(normal, 0.0)).xyz);
	vec3 tangent_cs =  normalize((os_to_cs * vec4(tangent, 0.0)).xyz);
	vec3 binormal_cs = normalize((os_to_cs * vec4(binormal, 0.0)).xyz);
	
	mat3 cs_to_ss = mat3(tangent_cs, binormal_cs, normal_cs);
	vertex_ss = vertex_cs.xyz * cs_to_ss;
	view_ss = vec3(0.0, 0.0, 0.0) * cs_to_ss;
	
#if 0
	vertex_def = vertex_cs;
	normal_def = normal;
	tangent_def = tangent;
	binormal_def = binormal;
#endif
	
	vec3 directionalLight_cs = normalize((ws_to_cs * vec4(directionalLight_ws, 0.0)).xyz);
	directionalLight_ss = -directionalLight_cs * cs_to_ss;
	
#if 1
	if (numOfPointLights > 0)
	{
		pointLights_ss[0].position = vec4((ws_to_cs * pointLights_ws[0].position).xyz * cs_to_ss, 1.0);
		pointLights_ss[0].color = pointLights_ws[0].color;
		pointLights_ss[0].intensity = pointLights_ws[0].intensity;
		pointLights_ss[0].range = pointLights_ws[0].range;
	}
	
	if (numOfPointLights > 1)
	{
		pointLights_ss[1].position = vec4((ws_to_cs * pointLights_ws[1].position).xyz * cs_to_ss, 1.0);
		pointLights_ss[1].color = pointLights_ws[1].color;
		pointLights_ss[1].intensity = pointLights_ws[1].intensity;
		pointLights_ss[1].range = pointLights_ws[1].range;
	}
	
	if (numOfPointLights > 2)
	{
		pointLights_ss[2].position = vec4((ws_to_cs * pointLights_ws[2].position).xyz * cs_to_ss, 1.0);
		pointLights_ss[2].color = pointLights_ws[2].color;
		pointLights_ss[2].intensity = pointLights_ws[2].intensity;
		pointLights_ss[2].range = pointLights_ws[2].range;
	}
	
	if (numOfPointLights > 3)
	{
		pointLights_ss[3].position = vec4((ws_to_cs * pointLights_ws[3].position).xyz * cs_to_ss, 1.0);
		pointLights_ss[3].color = pointLights_ws[3].color;
		pointLights_ss[3].intensity = pointLights_ws[3].intensity;
		pointLights_ss[3].range = pointLights_ws[3].range;
	}
#endif
}
