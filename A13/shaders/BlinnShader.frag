#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;


layout(binding = 1) uniform sampler2D tex;

layout(binding = 2) uniform GlobalUniformBufferObject {
	vec3 lightPos;	// position of the spotlight
	vec3 lightDir;	// direction of the spotlight
	vec4 lightColor;// color of the spotlight	
	vec3 eyePos;	// position of the viewer
} gubo;

layout(binding = 3) uniform sampler2D texEmit;

const float beta = 2.0f;	// decay exponent of the spotlight
const float g = 3;			// target distance of the spotlight
const float cosout = 0.5;	// cosine of the outer angle of the spotlight
const float cosin  = 0.95;	// cosine of the inner angle of the spotlight

// coefficients for the spehrical harmonics ambient light term
const vec3 C00  = vec3( .38f, .43f, .45f)/8.0f;
const vec3 C1m1 = vec3( .29f, .36f, .41f)/8.0f;
const vec3 C10  = vec3( .04f, .03f, .01f)/8.0f;
const vec3 C11  = vec3(-.10f,-.10f,-.09f)/8.0f;
const vec3 C2m2 = vec3(-.06f,-.06f,-.04f)/8.0f;
const vec3 C2m1 = vec3( .01f,-.01f,-.05f)/8.0f;
const vec3 C20  = vec3(-.09f,-.13f,-.15f)/8.0f;
const vec3 C21  = vec3(-.06f,-.05f,-.04f)/8.0f;
const vec3 C22  = vec3( .02f, .00f,-.05f)/8.0f;

void main() {
	vec3 N = normalize(fragNorm);				// surface normal
	vec3 V = normalize(gubo.eyePos - fragPos);	// viewer direction
	vec3 MD = texture(tex, fragUV).rgb;			// diffuse color
	vec3 MA = MD;								// ambient color
	vec3 MS = vec3(1);							// specular color
	vec3 ME = texture(texEmit, fragUV).rgb;		// emission color

	// Write the shader here

	float gamma = 1000.0f;						// gamma exponent for Blinn specular model; initially not provided, 
												// determined by trial-and-error to obtain a result similar to the expected one

	// Compute missing values for spotlight
	vec3 L = normalize(gubo.lightPos-fragPos);		// light direction
	float pointLightDecay = pow(g/length(gubo.lightPos-fragPos), beta);
	vec4 I0 = gubo.lightColor * pointLightDecay;	// point light intensity
	float clampFactor = clamp((dot(L,gubo.lightDir)-cosout)/(cosin-cosout), 0.0f, 1.0f);
	vec4 I = I0 * clampFactor;
	// Emission
	vec3 emission = ME;
	// Diffuse (Lambert)
	vec3 diffuse = MD * max(dot(L,N), 0);
	// Specular (Blinn)
	vec3 H = normalize(L+V);
	vec3 specular = MS * pow(clamp(dot(N,H), 0.0f, 1.0f), gamma);
	// Ambient
	vec3 LA = C00 + N.x*C11 + N.y*C1m1 + N.z*C10 + (N.x * N.y)*C2m2 + (N.y * N.z)*C1m1 + (N.z * N.x)*C11 + (N.x*N.x - N.y*N.y)*C22 + (3*N.z*N.z -1)*C20;
	vec3 ambient = LA * MA;

	
	outColor = vec4(clamp(emission + I.rgb*(diffuse + specular) + ambient, 0.0f, 1.0f), 1.0f);	// output color
}