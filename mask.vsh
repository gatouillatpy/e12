
struct VS_IN_OUT
{
	float4 vPosition : POSITION;
	float2 vTexcoord : TEXCOORD0;
};

VS_IN_OUT VS_Default ( VS_IN_OUT tVertex )
{
	return tVertex;
}
