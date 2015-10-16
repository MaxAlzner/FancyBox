#version 150

in vec2 texcoord;
in vec4 vertex_ls;
in vec3 vertex_ss;
in vec3 view_ss;

in vec4 vertex_def;
in vec3 normal_def;
in vec3 tangent_def;
in vec3 binormal_def;

in vec3 directionalLight_ss;
in PointLight
{
	vec4 position;
	vec4 color;
	float intensity;
	float range;
} pointLights_ss[4];

out vec4 outColor;

uniform sampler2D colorMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D luminanceMap;

uniform vec4 directionalLight_color;
uniform float directionalLight_intensity;
uniform int numOfPointLights;

uniform vec4 overlay;
uniform vec4 highlight;
uniform float roughness;
uniform float refIndex;

uniform vec2 screenSize;
uniform vec2 mapSize;
uniform vec2[128] randomFilter;
uniform float randomFilterRadius;
uniform float gamma;

uniform int mode;

const float ambient = 0.2;
const float radius = 5.2;

const vec3 falloff = vec3(1.0, 0.4, 0.2);
const vec3 reinhard = vec3(0.2126, 0.7152, 0.0722);
const float middleGray = 0.18;
const float whiteCutoff = 0.8;

const float nearZ = 1.0;
const float farZ = 24.0;

float average(vec3 v)
{
	return (v.r + v.g + v.b) / 3.0;
}
float gray(vec3 color)
{
	return clamp((reinhard.r * color.r) + (reinhard.g * color.g) + (reinhard.b * color.b), 0.0, 1.0);
}
float luminance(vec3 color)
{
	return clamp((reinhard.r * pow(color.r, gamma)) + (reinhard.g * pow(color.g, gamma)) + (reinhard.b * pow(color.b, gamma)), 0.0, 1.0);
}

vec3 unpackNormal(vec3 normal)
{
	return normalize((normal * 2.0) - 1.0);
}
vec3 packNormal(vec3 normal)
{
	return normalize((normal * 0.5) + 0.5);
}

float readDepth(in vec2 coord)
{
	float depth = average(texture(colorMap, coord).rgb);
	float d = (2.0 * nearZ) / ((farZ + nearZ) - (depth * (farZ - nearZ)));
	return 1.0 - clamp(d, 0.0, 1.0);
}

void pointLight_albedo(inout vec3 diffuse, inout vec3 specular, in vec3 n, in vec3 v, in int light)
{
	vec3 position = pointLights_ss[light].position.xyz;
	vec4 color = pointLights_ss[light].color;
	vec3 l = normalize(position - vertex_ss);
	vec3 h = normalize(l + v);
	float intensity = pointLights_ss[light].intensity;
	float range = pointLights_ss[light].range;
	float dist = distance(position, vertex_ss);
	float atten = (range / (falloff.x + (falloff.y * dist) + (falloff.z * dist * dist))) * intensity;
	float n_dot_l = dot(n, l);
	float n_dot_h = dot(n, h);
	float n_dot_v = dot(n, v);
	float h_dot_v = dot(h, v);
	float h_dot_l = dot(h, l);
	float g1 = (2.0 * n_dot_h * n_dot_v) / h_dot_v;
	float g2 = (2.0 * n_dot_h * n_dot_l) / h_dot_v;
	float g = 1.0;
	if (g1 < g) g = g1;
	if (g2 < g) g = g2;
	float m = roughness * roughness;
	float r = (1.0 / (m * pow(n_dot_h, 4.0))) * exp((pow(n_dot_h, 2.0) - 1.0) / (m * pow(n_dot_h, 2.0)));
	float f = (refIndex + pow(1.0 - h_dot_v, 5.0)) * (1.0 - refIndex);
	float brdf = max((abs(f * r * g) / n_dot_v), 0.0);
	float lambert = max(n_dot_l, ambient);

	diffuse += color.rgb * lambert * atten;
	specular += brdf * lambert * atten;
}
void directionalLight_albedo(inout vec3 diffuse, inout vec3 specular, in vec3 n, in vec3 v)
{
	vec3 l = normalize(directionalLight_ss);
	float n_dot_l = dot(n, l);
	float lambert = max(n_dot_l, ambient);
	diffuse += directionalLight_color.rgb * lambert * directionalLight_color.a * directionalLight_intensity;
}

void main()
{
	vec4 colorSample = texture(colorMap, texcoord);
	vec4 specularSample = texture(specularMap, texcoord);

	vec3 n = unpackNormal(texture(normalMap, texcoord).rgb);
	vec3 v = normalize(view_ss - vertex_ss);

	vec3 color = colorSample.rgb;
	vec3 shine = specularSample.rgb;
	vec3 diffuse = vec3(0.0);
	vec3 specular = vec3(0.0);

#if 1
	directionalLight_albedo(diffuse, specular, n, v);
#endif
	
#if 1
	for (int i = 0; i < numOfPointLights; i++)
	{
		pointLight_albedo(diffuse, specular, n, v, i);
	}
#endif
	
	vec3 albedo = (color * diffuse) + (shine * specular);
	
	outColor = vec4(albedo, 1.0);
}
