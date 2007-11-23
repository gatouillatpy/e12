
struct VS_IN_OUT
{
	float4 vPosition : POSITION;
};

VS_IN_OUT VS_Default ( VS_IN_OUT tVertex )
{
	return tVertex;
}
