#include "Scene.h"
#include "QuackBackend.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Camera *camera = new Camera();

	RefDef *rd = new RefDef(camera);

	// TODO: This is temporary, only for testing.
	QuackInput *input = new QuackInput(camera);

	// Init the window and context
	QuackWin *bgl = new QuackWin(hInstance);
	bgl->Init();
	bgl->input = input;

	// Init the backend renderer
	QuackBackend *backend = new QuackBackend(bgl);

	Renderer *re = new Renderer(backend);

	Scene *sc = new Scene(re);

	Entity *ent = new Entity();
	ent->GenerateSquareEntity();

	// main loop
	while (1) {
		MSG msg;

		// pump the message loop
		// TODO: this should go in the event manager (when we build it)
		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		sc->ToggleNewFrame();

		ent->Rotate(0.01, glm::vec3(1, 0, 0));
		ent->Rotate(0.03, glm::vec3(0, 1, 0));

		sc->AddEntityToScene(ent);

		sc->RenderScene(rd);
	}
}