#include "common.glh"

varying vec2 texCoord0;

#if defined(VS_BUILD)
#include "filter.vsh"
#elif defined(FS_BUILD)
uniform vec3 R_blurScale;
uniform sampler2D R_filterTexture;

DeclareFragOutput(0, vec4);
void main()
{
	vec4 color = vec4(0.0);

	color += texture2D(R_filterTexture, texCoord0 + (vec2(-3.0) * R_blurScale.xy)) * (1.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(-2.0) * R_blurScale.xy)) * (6.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(-1.0) * R_blurScale.xy)) * (15.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(0.0) * R_blurScale.xy))  * (20.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(1.0) * R_blurScale.xy))  * (15.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(2.0) * R_blurScale.xy))  * (6.0/64.0);
	color += texture2D(R_filterTexture, texCoord0 + (vec2(3.0) * R_blurScale.xy))  * (1.0/64.0);

	SetFragOutput(0, color);
}
#endif
