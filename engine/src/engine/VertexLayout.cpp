#include "VertexLayout.h"

void VertexLayout::addVertexComponent(LPCSTR semanticName, UINT semanticIndex, DXGI_FORMAT format, UINT inputSlot, UINT AlignedByteOffset, D3D11_INPUT_CLASSIFICATION inputSlotClass, UINT InstanceDataStepRate)
{
	addVertexComponent(D3D11_INPUT_ELEMENT_DESC{ semanticName,semanticIndex,format,inputSlot,AlignedByteOffset,inputSlotClass,InstanceDataStepRate });
}
