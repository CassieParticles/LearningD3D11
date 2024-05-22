#pragma once

#include <string>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <DirectXMath.h>

class GLFWwindow;

class Window
{
	template<typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	//Get or create window instance
	static Window* initializeWindow(const std::string& windowTitle, int windowWidth, int windowHeight);

	static Window* Instance();

	bool windowShouldClose();
	void pollEvents();

	const GLFWwindow* getWindow() { return window; }

	const ComPtr<ID3D11Device>& getDevice() { return device; }
	const ComPtr<ID3D11DeviceContext>& getDeviceContext() { return deviceContext; }
	const ComPtr<IDXGIFactory2>& getFactory() { return factory; }
	const ComPtr<IDXGISwapChain1>& getSwapChain() { return swapChain; }
	const ComPtr<ID3D11Texture2D> getBackBuffer() { return backBuffer; }
	const ComPtr<ID3D11Texture2D> getDepthBuffer() { return depthBuffer; }

	const ComPtr<ID3D11RenderTargetView> getRTV() { return renderTargetView; }
	const ComPtr<ID3D11DepthStencilView> getDSV() { return depthStencilView; }

	const int getWidth() { return width; }
	const int getHeight() { return height; }
	const DirectX::XMFLOAT2 getSize() { return DirectX::XMFLOAT2( width,height ); }

	void clearBackBuffer(DirectX::XMFLOAT4 colour);
	void presentBackBuffer();

	void bindRTV();

protected:
	Window(const std::string& windowTitle, int windowWidth, int windowHeight);
	~Window();

	bool createWindow(const std::string& windowTitle, int windowWidth, int windowHeight);

	//Window pointers
	GLFWwindow* window;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGIFactory2> factory;
	ComPtr<IDXGISwapChain1> swapChain;
	ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11Texture2D> depthBuffer;

	ComPtr<ID3D11RenderTargetView> renderTargetView;
	ComPtr<ID3D11DepthStencilView> depthStencilView;

	//Window size
	int width{};
	int height{};
	void setSize(int width, int height);

	//Single instance
	static Window* instance;

	static void handleResize(GLFWwindow* window, int width, int height);
};