
struct VS_IN
{
	float3 vPosition : POSITION;
	float2 vTexcoord : TEXCOORD0;
};

struct VS_OUT
{
	float4 vPosition : POSITION;
	float2 vTexcoord : TEXCOORD0;
	float2 vOffset : TEXCOORD1;
};

VS_OUT VS_Default ( VS_IN tIn )
{
	float x = (tIn.vPosition.x * 2.0f) - 1.0f;
	float y = 1.0f - (tIn.vPosition.y * 2.0f);

	VS_OUT tOut;
	
	tOut.vPosition = float4( x, y, 0.0f, 1.0f );
	tOut.vTexcoord = tIn.vTexcoord;
	tOut.vOffset = tIn.vPosition;
	
	return tOut;
}
