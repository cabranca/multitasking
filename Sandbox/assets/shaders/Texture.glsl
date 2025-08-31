#type vertex
#version 460 core
			
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 tex;
layout(location = 3) in float texIndex;
layout(location = 4) in float tilingFactor;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord;
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

void main()
{
	v_TexCoord = tex;
	v_Color = col;
	v_TexIndex = texIndex;
	v_TilingFactor = tilingFactor;
	gl_Position = u_ViewProjection * vec4(pos, 1.0);
}

#type fragment
#version 460 core
			
layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
	color = texture(u_Textures[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
}