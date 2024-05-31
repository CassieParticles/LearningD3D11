#pragma once

#include <wrl.h>
#include <d3d11.h>

class RasterizerState
{
	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	RasterizerState();
	RasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode, bool frontFaceCCW, int depthBias, float depthBiasClamp, float slopeScaledDepthBias, bool depthClipEnable, bool scissorTest, bool multisampleEnable, bool antialiasLineEnable);
	~RasterizerState() = default;

	void setFillMode(D3D11_FILL_MODE FillMode) { desc.FillMode = FillMode; }
	void setCullMode(D3D11_CULL_MODE CullMode) { desc.CullMode = CullMode; }
	void setFrontCCW(bool FrontCounterClockwise) { desc.FrontCounterClockwise = FrontCounterClockwise; }
	void setDepthBias(int DepthBias) { desc.DepthBias = DepthBias; }
	void setDepthBiasClamp(float DepthBiasClamp) { desc.DepthBiasClamp = DepthBiasClamp; }
	void setSlopeScaleDepthBias(float SlopeScaledDepthBias) { desc.SlopeScaledDepthBias = SlopeScaledDepthBias; }
	void setDepthClipEnable(bool DepthClipEnable) { desc.DepthClipEnable = DepthClipEnable; }
	void setScissorEnable(bool ScissorEnable) { desc.ScissorEnable = ScissorEnable; }
	void setMultisampleEnable(bool MultisampleEnable) { desc.MultisampleEnable = MultisampleEnable; }
	void setAntialiasedLineEnable(bool AntialiasedLineEnable) { desc.AntialiasedLineEnable = AntialiasedLineEnable; }

	bool createRasterizerState();

	void use();
protected:
	bool usable{};

	D3D11_RASTERIZER_DESC  desc;

	ComPtr<ID3D11RasterizerState> rasterizerState;
};