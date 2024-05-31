#pragma once

#include <DirectXMath.h> 

class Window;

class Input
{
public:
	static Input* InitializeInput();
	static Input* Instance() { return instance; }

	void update();

	//Key is currently pressed down
	bool getKeyDown(int key);
	//Key was pressed down this frame
	bool getKeyPressed(int key);
	//Key was released this frame
	bool getKeyReleased(int key);

	void enableCentredCursor() { cursorCentred = true; }
	void disableCentreCursor() { cursorCentred = false; }

	DirectX::XMFLOAT2 getMousePosition() { return mousePosition; }
protected:
	Input();
	~Input();

	static Input* instance;

	bool* keyStatesCurrent;
	bool* keyStatesPrev;

	DirectX::XMFLOAT2 mousePosition;
	bool cursorCentred;

	Window* window;
};