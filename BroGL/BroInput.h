#ifndef BRO_INPUT_H
#define BRO_INPUT_H

// TODO: This is temporary only for testing
#include "Camera.h"

class Input {
public:
	Camera *camera;

	Input();
	Input(Camera*);
	~Input();
	
	//************************************
	// Method:    HandleKeyPress
	// FullName:  Input::handleKeyPress
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: char key
	//************************************
	void HandleKeyPress(char key);
};

#endif