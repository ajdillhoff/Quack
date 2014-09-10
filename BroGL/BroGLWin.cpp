#include "BroGLWin.h"


BroGLWin::BroGLWin() {
}

BroGLWin::BroGLWin(HINSTANCE hInstance) {
	wndproc = SWndProc;
	hinstOpenGL = hInstance;
	pixelFormatSet = false;
	frameCount = 0;
}

BroGLWin::~BroGLWin() {
}

void BroGLWin::CreatePFD(int colorBits, int depthBits, int stencilBits) {
	PIXELFORMATDESCRIPTOR p = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,															// version number
		PFD_DRAW_TO_WINDOW |						// support window
		PFD_SUPPORT_OPENGL |						// support OpenGL
		PFD_DOUBLEBUFFER,								// double buffered
		PFD_TYPE_RGBA,									// RGBA type
		32,															// 32-bit color depth
		0, 0, 0, 0, 0, 0,								// color bits ignored
		0,															// no alpha buffer
		0,															// shift bit ignored
		0,															// no accumulation buffer
		0, 0, 0, 0, 										// accum bits ignored
		24,															// 24-bit z-buffer	
		8,															// 8-bit stencil buffer
		0,															// no auxiliary buffer
		PFD_MAIN_PLANE,									// main layer
		0,															// reserved
		0, 0, 0													// layer masks ignored
	};

	bpfd = p;

	bpfd.cColorBits = colorBits;
	bpfd.cDepthBits = depthBits;
	bpfd.cStencilBits = stencilBits;
}

//************************************
// Method:    CreateWindow
// FullName:  BroGLWin::CreateWindow
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: int width
// Parameter: int height
// Parameter: int colorBits
//************************************
bool BroGLWin::B_CreateWindow(int width, int height, int colorBits) {
	if (!classRegistered) {
		WNDCLASS wc;

		memset(&wc, 0, sizeof(wc));

		wc.style = 0;
		wc.lpfnWndProc = (WNDPROC)wndproc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hinstOpenGL;
		//wc.hIcon = LoadIcon(hinstOpenGL, MAKEINTRESOURCE(IDI_ICON1));
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		wc.lpszMenuName = 0;
		wc.lpszClassName = WINDOW_CLASS_NAME;

		if (!RegisterClass(&wc)) {
			// TODO: Add safe error here
			// unable to register class
		}
		classRegistered = true;
	}

	// create HWND
	if (!hWnd) {
		hWnd = CreateWindowEx(
			WS_EX_TOPMOST,
			WINDOW_CLASS_NAME,
			"BroGL",
			WS_VISIBLE | WS_OVERLAPPEDWINDOW,
			0,
			0,
			width,
			height,
			NULL,
			NULL,
			hinstOpenGL,
			this
			);

		if (!hWnd) {
			// error creating the window
		}

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);
	}

	if (!(hDC = GetDC(hWnd))) {
		ShowWindow(hWnd, SW_HIDE);
		DestroyWindow(hWnd);
		hWnd = NULL;
		return false;
	}

	// Create OpenGL Context
	if (!MakeContext()) {
		ShowWindow(hWnd, SW_HIDE);
		DestroyWindow(hWnd);
		hWnd = NULL;

		return false;
	}

	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	return true;
}

//************************************
// Method:    EndFrame
// FullName:  BroGLWin::EndFrame
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void BroGLWin::EndFrame(void) {
	frameCount++;
	SwapBuffers(hDC);
}

//************************************
// Method:    Init
// FullName:  BroGLWin::Init
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
// Description: Platform specfic OpenGL initialization. Loads OpenGL, inits,
// creates the window, etc. If this call is successful, a functional OpenGL
// subsystem has been established.
//************************************
void BroGLWin::Init(void) {
	// init opengl
	StartOpenGL();

	// other init functions
	glewInit();
}

//************************************
// Method:    MakeContext
// FullName:  BroGLWin::MakeContext
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int BroGLWin::MakeContext() {
	int pixelformat;

	// is the pixelformat already set?
	if (!pixelFormatSet) {
		// Set it up!
		CreatePFD(32, 24, 8);

		if ((pixelformat = ChoosePixelFormat(hDC, &bpfd)) == 0) {
			return 0;
		}

		if (!SetPixelFormat(hDC, pixelformat, &bpfd)) {
			return 0;
		}

		pixelFormatSet = true;
	}

	// Create a context and make it current
	if (!hGLRC) {
		// create context and check for failure
		if ((hGLRC = wglCreateContext(hDC)) == 0) {
			// FAILED TO CREATE CONTEXT
			return 0;
		}

		// make context current
		if (!wglMakeCurrent(hDC, hGLRC)) {
			wglDeleteContext(hGLRC);
			hGLRC = NULL;
			return 0;
		}
	}

	return 1;
}

//************************************
// Method:    StartOpenGL
// FullName:  BroGLWin::StartOpenGL
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void BroGLWin::StartOpenGL(void) {
	// Load OpenGL

	hDC = GetDC(GetDesktopWindow());
	desktopWidth = GetDeviceCaps(hDC, HORZRES);
	desktopHeight = GetDeviceCaps(hDC, VERTRES);
	ReleaseDC(GetDesktopWindow(), hDC);

	// Create the window
	if (!B_CreateWindow(1680, 1050, 24)) {

		// some sort of error checking
	}
}

LONG WINAPI BroGLWin::MainWndProc(HWND n_hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
									LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
									void * lpCreateParam = cs->lpCreateParams;
									BroGLWin *win = reinterpret_cast<BroGLWin *>(lpCreateParam);
									assert(win == this);
									return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Static wndproc created in order to pass a function pointer
LONG WINAPI BroGLWin::SWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	BroGLWin *bgl;

	if (msg == WM_NCCREATE) {
		LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lp);
		void * lpCreateParam = cs->lpCreateParams;
		bgl = reinterpret_cast<BroGLWin *>(lpCreateParam);
		bgl->hWnd = hwnd;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(bgl));
		return DefWindowProc(hwnd, msg, wp, lp);
	}
	LONG_PTR userData = GetWindowLongPtr(hwnd, GWL_USERDATA);
	bgl = reinterpret_cast<BroGLWin *>(userData);
	if (bgl) {
		return bgl->MainWndProc(hwnd, msg, wp, lp);
	} else {
		return DefWindowProc(hwnd, msg, wp, lp);
	}
}
