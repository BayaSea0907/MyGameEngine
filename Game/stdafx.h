// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください

#include <algorithm>
#include <memory>

#pragma warning (disable:4005)
#pragma warning (disable:4838)
#pragma warning (disable:4238)

#include <mmsystem.h>

//DirectX 11の準備
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>

//リンクの準備 .libを結合
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

//定数の定義
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1280


//マクロの定義
#define SAFE_RELEASE(p)     { if((p)!=NULL){ (p)->Release();	(p)=NULL; } }
#define SAFE_DELETE(x)	    { if((x)!=NULL){ delete (x);		(x)=0; } }
#define SAFE_DELETE_ARRAY(x){ if(x)        { delete[] (x);        (x)=0}}


//EOF