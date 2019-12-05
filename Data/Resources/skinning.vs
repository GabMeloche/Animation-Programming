
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	int boneIndex1 = int(boneIndices[0]);
	int boneIndex2 = int(boneIndices[1]);
	int boneIndex3 = int(boneIndices[2]);
	int boneIndex4 = int(boneIndices[3]);

	vec4 pos = vec4(inputPosition, 1.0f);
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 animPos = vec4(
		(boneWeights[0] * (pos * skin.mat[boneIndex1]))
		+ (boneWeights[1] * (pos * skin.mat[boneIndex2]))
		+ (boneWeights[2] * (pos * skin.mat[boneIndex3]))
		+ (boneWeights[3] * (pos * skin.mat[boneIndex4]))
		+ vec4(0, 50, 0, 0));


	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(animPos.xyz, 1.0f));
	outNormal = mat3(modelViewMatrix) * normal;

	outNormal = normalize(outNormal);
}
