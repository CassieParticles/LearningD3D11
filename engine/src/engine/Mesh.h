#pragma once



#include <vector>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>

class Mesh
{
public:
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	Mesh();
	~Mesh();

	void setStartSlot(int startSlot) { vertexStartSlot = startSlot; }

	void addVertexBuffer(ComPtr<ID3D11Buffer> vertexBuffer, int vertexStride, int vertexOffset);
	void addVertexBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size,int vertexStride,int vertexOffset);
	void addVertexBuffer(void* data, bool dynamic, int size, int vertexStride, int vertexOffset);
	void addIndexBuffer(ComPtr<ID3D11Buffer> indexBuffer, int indexOffset);
	void addIndexBuffer(D3D11_SUBRESOURCE_DATA* data, bool dynamic, int size, int indexOffset);
	void addIndexBuffer(int* data, bool dynamic, int size, int indexOffset);


	virtual void setBuffers();
protected:
	//Vertex buffer data
	ComPtr<ID3D11Buffer> vertexBuffers[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT]{};
	UINT vertexStrides[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT]{};
	UINT vertexOffsets[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT]{};
	int vertexStartSlot{};
	int bufferCount{};

	ComPtr<ID3D11Buffer> indexBuffer{};
	int indexOffset{};


};
