#include "Scene.h"
#include "BroGLBackend.h"

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
	ent->GenerateSquareEntity();

	// main loop
	while (1) {
		sc->ToggleNewFrame();

		//ent->Rotate(0.01, glm::vec3(1, 0, 0));
		ent->Rotate(0.03, glm::vec3(0, 1, 0));

		sc->AddEntityToScene(ent);

		sc->RenderScene(rd);
	}
}