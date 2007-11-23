@echo off
cd..
cd release

hlslconv.exe -vs ..\engine\final.vsh vs_3_0 VS_Default -ps ..\engine\final.psh ps_3_0 PS_Default -to ..\data\final.s12
hlslconv.exe -vs ..\engine\cylinder.vsh vs_3_0 VS_Default -ps ..\engine\cylinder.psh ps_3_0 PS_Default -to ..\data\cylinder.s12
hlslconv.exe -vs ..\engine\surface.vsh vs_3_0 VS_Default -ps ..\engine\surface.psh ps_3_0 PS_Default -to ..\data\surface.s12

cd..
cd engine

pause