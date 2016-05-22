#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<cstdio>
#include<stdint.h>

struct window {
  HDC hDC;
  HGLRC hRC;
  HWND hWnd;
  HINSTANCE hInstance;
  const char *classname;
  char title[99];
  int width, height, interval;
} W;

int run = 0;

LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  if (uMsg == WM_CLOSE) {
    run = 0;
    PostMessage (W.hWnd, WM_QUIT, 0, 0);
  }
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int glinit(int width, int height) {
	glViewport(0, 0, (GLsizei)(width), (GLsizei)(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)(width)/(GLfloat)(height), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0, 0.0, 0.0, 0.5);						// Black Background
	glClearDepth(1.0);										// Depth Buffer Setup
	glDepthFunc(GL_LEQUAL);									// The Type Of Depth Testing (Less Or Equal)
	glEnable(GL_DEPTH_TEST);									// Enable Depth Testing
	glShadeModel(GL_SMOOTH);									// Select Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// Set Perspective Calculations To Most Accurate

	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// Set Texture Max Filter
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// Set Texture Min Filter

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For S To Sphere Mapping
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);		// Set The Texture Generation Mode For T To Sphere Mapping
}


int init_window(int w, int h, int interval) {
  static int init = 0;
  if (init) return 0;
  init = 1;
  W.classname = "video";
  strcpy(W.title, W.classname);
  W.width = w;
  W.height = h;
  W.interval = interval;

  WNDCLASSEX winclass;
	ZeroMemory(&winclass, sizeof(WNDCLASSEX));
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winclass.lpfnWndProc = (WNDPROC)WindowProc;
	winclass.hInstance = W.hInstance;
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  winclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
	winclass.lpszClassName = W.classname;
	if (RegisterClassEx (&winclass) == 0) {
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}

  DWORD style = WS_OVERLAPPEDWINDOW, extstyle = WS_EX_APPWINDOW;
  W.hWnd = CreateWindowEx(extstyle, W.classname, W.title, style,
   0, 0, W.width+8, W.height+32, HWND_DESKTOP, NULL, W.hInstance, NULL);
  W.hDC = GetDC(W.hWnd);

  PIXELFORMATDESCRIPTOR pfd;
  ZeroMemory(&pfd, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  int iFormat = ChoosePixelFormat(W.hDC, &pfd);
  SetPixelFormat(W.hDC, iFormat, &pfd);

  W.hRC = wglCreateContext(W.hDC);
  wglMakeCurrent(W.hDC, W.hRC);

  ShowWindow(W.hWnd, SW_NORMAL);
  run = 1;
  glinit(W.width, W.height);
}

void draw(uint8_t data[]) {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W.width, W.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 11.0f,  8.3f, -20.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-11.0f,  8.3f, -20.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-11.0f, -8.3f, -20.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 11.0f, -8.3f, -20.0f);
	glEnd();
  MSG msg;
  SwapBuffers(W.hDC);
  PeekMessage(&msg, W.hWnd, 0, 0, PM_REMOVE);
  DispatchMessage(&msg);
  if (msg.message == WM_QUIT || msg.message == WM_CLOSE) run = 0;
  Sleep(W.interval-3);
  PeekMessage(&msg, W.hWnd, 0, 0, PM_REMOVE);
  DispatchMessage(&msg);
  if (msg.message == WM_QUIT || msg.message == WM_CLOSE) run = 0;
}

int dec_main(const char name[]);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  W.hInstance = hInstance;

  run = 1;
  dec_main(lpCmdLine);

  MSG msg;
  while (run) {
    WaitMessage();
    PeekMessage(&msg, W.hWnd, 0, 0, PM_REMOVE);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT || msg.message == WM_CLOSE) break;
  }
  return 0;
}
