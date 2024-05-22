#include "BaseScene.h"

void BaseScene::beginDraw()
{
	window->clearBackBuffer(DirectX::XMFLOAT4(bgColour.x,bgColour.y,bgColour.z, 1.f));
	window->bindRTV();
}

void BaseScene::endDraw()
{
	window->getSwapChain()->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

