
#include <stdio.h>

#include "engine.h"



int main( int argc, char* argv[])
{
	ENGINE12* pEngine = new ENGINE12;

	WINDOW12* pWindow = pEngine->AddWindow( "MAIN", "HLSL to S12 Converter", -800, -600, 400, 300 );

	RENDER12* pRender = pEngine->AddRender();
	pRender->Initialize( pWindow );

	HRESULT hr;

	SHADER12* pShader = pRender->AddShader();

	for ( int k = 1 ; k < argc ; k++ )
	{
		if ( _stricmp(argv[k], "-vs") == 0 )
		{
			if ( k + 3 >= argc )
			{
				printf("-vs : missing arguments ; usage : -vs file profile function\n");
			}
			else if ( _stricmp(argv[k+2], "vs_1_1") && _stricmp(argv[k+2], "vs_2_0") && _stricmp(argv[k+2], "vs_2_x") && _stricmp(argv[k+2], "vs_2_sw") && _stricmp(argv[k+2], "vs_3_0") && _stricmp(argv[k+2], "vs_3_sw") )
			{
				printf("-vs : unknown profile ; compatibility : vs_1_1 ; vs_2_0 ; vs_2_x ; vs_2_sw ; vs_3_0 ; vs_3_sw\n");
			}
			else
			{
				printf("compiling vertex shader %s ...", argv[k+1]);
			
				if ( FAILED( hr = pShader->CompileVSFile( argv[k+1], argv[k+2], argv[k+3] ) ) )
					printf("\n > %s...failed.\n", pShader->GetError());
				else
					printf("success.\n");

				k += 3;
			}
		}
		if ( _stricmp(argv[k], "-ps") == 0 )
		{
			if ( k + 3 >= argc )
			{
				printf("-ps : missing arguments ; usage : -ps file profile function\n");
			}
			else if ( _stricmp(argv[k+2], "ps_1_1") && _stricmp(argv[k+2], "ps_1_2") && _stricmp(argv[k+2], "ps_1_3") && _stricmp(argv[k+2], "ps_1_4") && _stricmp(argv[k+2], "ps_2_0") && _stricmp(argv[k+2], "ps_2_x") && _stricmp(argv[k+2], "ps_2_sw") && _stricmp(argv[k+2], "ps_3_0") && _stricmp(argv[k+2], "ps_3_sw") )
			{
				printf("-ps : unknown profile ; compatibility : ps_1_1 ; ps_1_2 ; ps_1_3 ; ps_1_4 ; ps_2_0 ; ps_2_x ; ps_2_sw ; ps_3_0 ; ps_3_sw\n");
			}
			else
			{
				printf("compiling pixel shader %s ...", argv[k+1]);

				if ( FAILED( hr = pShader->CompilePSFile( argv[k+1], argv[k+2], argv[k+3] ) ) )
					printf("\n > %s...failed.\n", pShader->GetError());
				else
					printf("success.\n");

				k += 3;
			}
		}
		if ( _stricmp(argv[k], "-fx") == 0 )
		{
			if ( k + 3 >= argc )
			{
				printf("-fx : missing arguments ; usage : -fx file technique pass\n");
			}
			else
			{
				printf("compiling effect %s ...", argv[k+1]);

				UINT nPass;
				sscanf(argv[k+3], "%d", &nPass);

				if ( FAILED( hr = pShader->CompileEffect( argv[k+1], argv[k+2], nPass ) ) )
					printf("\n > %s...failed.\n", pShader->GetError());
				else
					printf("success.\n");

				k += 3;
			}
		}
		if ( _stricmp(argv[k], "-to") == 0 )
		{
			if ( k + 1 >= argc )
			{
				printf("missing output file\n");
			}
			else
			{
				printf("writing %s ...", argv[k+1]);

				if ( FAILED( hr = pShader->Save( argv[k+1] ) ) )
					printf("failed.\n");
				else
					printf("success.\n");

				k += 1;
			}
		}
		if ( _stricmp(argv[k], "-help") == 0 )
		{
			printf("usage : hlslconv.exe [-vs file profile function] [-ps file profile function] [-fx file technique pass] -to file");
		}
	}

	delete pEngine;

	return 0;
}
