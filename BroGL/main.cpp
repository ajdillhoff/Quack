#include "Scene.h"
#include "BroGLBackend.h"

//int main(int argc, char **argv) {
//	//BroGLWin *bgl = new BroGLWin();
//
//	return 0;
//}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Init the window and context
	BroGLWin *bgl = new BroGLWin(hInstance);
	bgl->Init();

	// Init the backend renderer
	BroGLBackend *backend = new BroGLBackend(bgl);

	Renderer *re = new Renderer(backend);

	Camera *camera = new Camera();

	RefDef *rd = new RefDef(camera); 

	Scene *sc = new Scene(re);

	Entity *ent = new Entity();
	ent->GenerateTestEntity();

	// main loop
	while (1) {
		sc->ToggleNewFrame();

		sc->AddEntityToScene(ent);

		sc->RenderScene(rd);
	}
}