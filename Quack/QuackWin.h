#pragma once

#include <windows.h>
#include <cassert>
#include <iostream>
#include <GL/glew.h>
#include <GL/GL.h>
#include "QuackInput.h"

#pragma comment (lib, "opengl32.lib")

#define WINDOW_CLASS_NAME "Quack"

class QuackWin {
public:
	int frameCount;
	QuackInput *input;

	QuackWin();
	QuackWin(HINSTANCE);
	~QuackWin();

	//************************************
	// Method:    CreatePFD
	// FullName:  QuackWin::CreatePFD
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: PIXELFORMATDESCRIPTOR * pPFD
	// Parameter: int colorBits
	// Parameter: int depthBits
	// Parameter: int stencilBits
	// Parameter: bool stereo
	//************************************
	void CreatePFD(int colorBits, int depthBits, int stencilBits);

	//************************************
	// Method:    CreateWindow
	// FullName:  QuackWin::CreateWindow
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: int width
	// Parameter: int height
	// Parameter: int colorBits
	//************************************
	bool B_CreateWindow(int width, int height, int colorBits);

	//************************************
	// Method:    EndFrame
	// FullName:  QuackWin::EndFrame
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: void
	//************************************
	void EndFrame(void);

	//************************************
	// Method:    Init
	// FullName:  QuackWin::Init
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: void
	// Description: Platform specfic OpenGL initialization. Loads OpenGL, inits,
	// creates the window, etc. If this call is successful, a functional OpenGL
	// subsystem has been established.
	//************************************
	void Init(void);

	//************************************
	// Method:    MakeContext
	// FullName:  QuackWin::MakeContext
	// Access:    public 
	// Returns:   int
	// Qualifier:
	//************************************
	int MakeContext();

	//************************************
	// Method:    StartOpenGL
	// FullName:  QuackWin::StartOpenGL
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: void
	//************************************
	void StartOpenGL(void);

	LONG WINAPI MainWndProc(HWND n_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LONG WINAPI SWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

protected:
	PIXELFORMATDESCRIPTOR bpfd;

	WNDPROC wndproc;

	HDC hDC;
	HGLRC hGLRC;
	HWND hWnd;

	HINSTANCE hinstOpenGL;

	bool pixelFormatSet;

	int desktopWidth, desktopHeight;

	bool classRegistered;
};

