
#line 2 "rasterizer_uniformcolor.vsh"



struct VS_INPUT
{
	float4 vPosition	: POSITION;
};

struct VS_OUTPUT
{
	float4 vPosition	: POSITION;
};



float4x4 matWorldViewProj;



VS_OUTPUT VS_Default( VS_INPUT IN )
{
	VS_OUTPUT OUT;

	OUT.vPosition = mul( IN.vPosition, matWorldViewProj );

	return OUT;    
}
