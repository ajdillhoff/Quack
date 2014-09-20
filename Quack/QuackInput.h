#ifndef QUACK_INPUT_H
#define QUACK_INPUT_H

// TODO: This is temporary only for testing
#include "Camera.h"

class QuackInput {
public:
	Camera *camera;

	QuackInput();
	QuackInput(Camera*);
	~QuackInput();
	
	//************************************
	// Method:    HandleKeyPress
	// FullName:  QuackInput::handleKeyPress
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: char key
	//************************************
	void HandleKeyPress(char key);
};

#endif