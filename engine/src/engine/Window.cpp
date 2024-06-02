#include "Window.h"
#include "Window.h"

#include <iostream>
#include <glfw3.h>
#include <d3dcompiler.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw3native.h>

Window* Window::instance = nullptr;

Window* Window::initializeWindow(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	return instance = new Window(windowTitle, windowWidth, windowHeight);
}

Window* Window::Instance()
{
	return instance;
}

bool Window::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}


void Window::clearBackBuffer(DirectX::XMFLOAT4 colour)
{
	float clearColour[4] = { colour.x,colour.y,colour.z,colour.w };
	deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColour);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.f, 0.f);
}

void Window::presentBackBuffer()
{
	swapChain->Present(0, DXGI_PRESENT_ALLOW_TEARING);
}

void Window::bindRTV()
{
	ID3D11RenderTargetView* renderTargetViews[1] = { renderTargetView.Get() };
	deviceContext->OMSetRenderTargets(1, renderTargetViews, depthStencilView.Get());

	D3D11_VIEWPORT port = { 0,0,width,height ,0,1};

	deviceContext->RSSetViewports(1, &port);
}

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	createWindow(windowTitle, windowWidth, windowHeight);
}

//Separate to constructor to allow early exit
bool Window::createWindow(const std::string& windowTitle, int windowWidth, int windowHeight)
{
	
	if (!glfwInit())
	{
		std::cerr << "GLFW failed to initialize\n";
		return false;
	}

	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	width = windowWidth;
	height = windowHeight;

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), nullptr, nullptr);

	if (!window)
	{
		std::cerr << "GLFW failed to create window\n";
		return false;
	}

	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, Window::handleResize);

	HRESULT errorCode;

	//Create DXGI factory for creating other DXGI objects
	errorCode = CreateDXGIFactory1(IID_PPV_ARGS(&factory));
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create DXGIfactory\n";
		return false;
	}

	constexpr D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	//Create device and device context
	errorCode = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create device/device context\n";
		return false;
	}

	//Create swapchain for rendering
	DXGI_SWAP_CHAIN_DESC1 swapChainDescription
	{
		width,
		height,
		DXGI_FORMAT_B8G8R8A8_UNORM,
		false,
		{1,0},
		DXGI_USAGE_RENDER_TARGET_OUTPUT,
		2,
		DXGI_SCALING_STRETCH,
		DXGI_SWAP_EFFECT_FLIP_DISCARD,
		DXGI_ALPHA_MODE_IGNORE,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING
	};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullDesc{};
	fullDesc.Windowed = true;

	errorCode = factory->CreateSwapChainForHwnd(device.Get(), glfwGetWin32Window(window), &swapChainDescription, &fullDesc, nullptr, &swapChain);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create swapchain\n";
		return false;
	}

	errorCode = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to get backbuffer texture\n";
		return false;
	}

	//Create depth texture
	D3D11_TEXTURE2D_DESC depthTexDesc
	{
		width,
		height,
		1,
		1,
		DXGI_FORMAT_D32_FLOAT,
		{1,0},
		D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL,
		0,
		0
	};

	errorCode = device->CreateTexture2D(&depthTexDesc, 0, &depthBuffer);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth texture\n";
		return false;
	}

	//Create render target view
	errorCode = device->CreateRenderTargetView(backBuffer.Get(), 0, &renderTargetView);
	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create render target view\n";
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depthDesc{};
	depthDesc.DepthEnable = false;

	//deviceContext->

	//Create depth stencil view

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format=DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	errorCode = device->CreateDepthStencilView(depthBuffer.Get(), &depthStencilViewDesc, &depthStencilView);

	if (FAILED(errorCode))
	{
		std::cerr << "Failed to create depth stencil view\n";
		return false;
	}

	return true;
}

void Window::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Window::handleResize(GLFWwindow* window, int width, int height)
{
	static_cast<Window*>(glfwGetWindowUserPointer(window))->setSize(width, height);
}


Window::~Window()
{
}

