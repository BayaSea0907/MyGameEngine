#include "RenderEngine.h"


CRenderEngine::CRenderEngine()
{
	Camera = NULL;
}


CRenderEngine::~CRenderEngine()
{
}

void CRenderEngine::Initialize(HWND hWnd_)
{
}

void CRenderEngine::Rendering(HWND hWnd_)
{
	// インタラクティブな入力に基づいて、まずは所定のパスに従って
	// カメラ変換を更新する
	UpdateCamera();

	// シーン内の任意の動的要素の位置、姿勢、
	// その他の関連した視覚状態を更新する。
	UpdateSceneElements();

	// 製紙フレームを、オフスクリーンの「バックバッファ」という
	// フレームバッファにレンダリングする。
	RenderScene();

	// バックバッファをフロントバッファに入れ替えて（スワップ）、最後にレンダリングされた
	// 画像を画面上に出す（または、ウィンドウ表示モードでは、
	// バックバッファのコンテンツをフロントバッファにコピーする。）
	SwapBuffers();
}

void CRenderEngine::Release()
{

}

void CRenderEngine::SetCamera(GCamera* sCamera_)
{
	if (sCamera_ == NULL) {
		throw invalid_argument("CRenderEngine::SetCamera() : This pointer in null.");
	}

	Camera = sCamera_;
}


void CRenderEngine::RenderScene()
{
	//登録された全てのRenderComponentを描画
}


void CRenderEngine::InitRenderComp(CComponent* comp_)
{
	dynamic_cast<CRenderComponent*>(comp_)->Initialize();
}

/*
void CRenderEngine::PushRenderComp(CComponent* rComp_)
{
	PushRenderComp(dynamic_cast<CRenderComponent*>(rComp_));
}

void CRenderEngine::PushRenderComp(CRenderComponent* rComp_)
{
	RenderCompList.push_back(rComp_);
}
*/
// EOF