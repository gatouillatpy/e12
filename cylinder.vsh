
#line 2 "cylinder.vsh"

struct VS_INPUT
{
	float3 vPosition	: POSITION;
};

struct VS_OUTPUT
{
	float4 vPosition	: POSITION;
};

float4x4 matWorldViewProj;

VS_OUTPUT VS_Default( VS_INPUT IN )
{
	VS_OUTPUT OUT;
  
	OUT.vPosition = mul( matWorldViewProj, float4( IN.vPosition, 1.0f ) );
	
	return OUT;    
}
