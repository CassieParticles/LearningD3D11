#pragma once

#include <vector>
#include <d3d11.h>

class VertexLayout
{
public:
	VertexLayout() {}
	~VertexLayout() {}

	//Add input layout, semantic name in shader, index of semantic, data format, input assembler vertex buffer slot used, byte offset if data is offset, input slot class, instanced data step rate
	void addVertexComponent(LPCSTR semanticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT AlignedByteOffset, D3D11_INPUT_CLASSIFICATION inputSlotClass, UINT InstanceDataStepRate);
	void addVertexComponent(D3D11_INPUT_ELEMENT_DESC element) { inputLayout.push_back(element); }

	D3D11_INPUT_ELEMENT_DESC* getLayout() { return inputLayout.data(); }
	int getSize() { return inputLayout.size(); }
protected:
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout;
};