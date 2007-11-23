
#line 2 "surface.vsh"

struct VS_INPUT
{
	float3 vPosition	: POSITION;
	float2 vTexture0	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 vPosition	: POSITION;
	float2 vTexture0	: TEXCOORD0;
};

float4x4 matWorldViewProj;

VS_OUTPUT VS_Default( VS_INPUT IN )
{
	VS_OUTPUT OUT;
  
	OUT.vPosition = mul( matWorldViewProj, float4( IN.vPosition, 1.0f ) );
	OUT.vTexture0 = IN.vTexture0;
	
	return OUT;    
}
