#include "QuackShader.h"


QuackShader::QuackShader() {
	Handle = glCreateProgram();
	VertexHandle = -1;
	FragmentHandle = -1;

	const char *DefaultVertexShader = "Shaders/LightingVertex.shader";
	const char *DefaultFragmentShader = "Shaders/DefaultFragment.shader";

	// Use Defaults
	LoadFromFile(VERTEX, DefaultVertexShader);
	LoadFromFile(FRAGMENT, DefaultFragmentShader);
}


QuackShader::~QuackShader() {
}

//************************************
// Method:    BindAttribLocation
// FullName:  QuackShader::BindAttribLocation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: GLuint
// Parameter: const char *
// Description: Wrapper around glBindAttribLocation
//************************************
void QuackShader::BindAttribLocation(GLuint location, const char * name) {

}

//************************************
// Method:    BindFragDataLocation
// FullName:  QuackShader::BindFragDataLocation
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: GLuint
// Parameter: const char *
// Description: Wrapper around glBindFragDataLocation
//************************************
void QuackShader::BindFragDataLocation(GLuint location, const char * name) {

}

//************************************
// Method:    Compile
// FullName:  QuackShader::Compile
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void QuackShader::Compile() {
	if (VertexHandle != -1) {
		glCompileShader(VertexHandle);
	}

	if (FragmentHandle != -1) {
		glCompileShader(FragmentHandle);
	}

	// Perform some sort of error checking
}

//************************************
// Method:    GetFileLength
// FullName:  QuackShader::GetFileLength
// Access:    private 
// Returns:   unsigned long
// Qualifier:
// Parameter: ifstream & file
//************************************
unsigned long QuackShader::GetFileLength(ifstream& file) {
	if (!file.good()) {
		return 0;
	}

	unsigned long pos = file.tellg();
	file.seekg(0, ios::end);
	unsigned long len = file.tellg();
	file.seekg(ios::beg);

	return len;
}

//************************************
// Method:    GetHandle
// FullName:  QuackShader::GetHandle
// Access:    public 
// Returns:   int
// Qualifier:
//************************************
int QuackShader::GetHandle() {
	return Handle;
}

//************************************
// Method:    IsLinked
// FullName:  QuackShader::IsLinked
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool QuackShader::IsLinked() {
	return Linked;
}

//************************************
// Method:    Link
// FullName:  QuackShader::Link
// Access:    public 
// Returns:   bool
// Qualifier:
//************************************
bool QuackShader::Link() {
	// TODO: Add error checking
	glLinkProgram(Handle);
	GLint linkInt;
	glGetProgramiv(Handle, GL_LINK_STATUS, &linkInt);

	if (linkInt) {
		Linked = true;
	} else {
		// link error nooooo
	}

	return false;
}

//************************************
// Method:    LoadFile
// FullName:  QuackShader::LoadFile
// Access:    private 
// Returns:   int
// Qualifier:
// Parameter: char * fileName
// Parameter: char * source
// Parameter: unsigned long * length
//************************************
int QuackShader::LoadFile(const char * fileName, char *& source, unsigned long * length) {
	ifstream file;
	unsigned int i = 0;

	file.open(fileName, ios::in);
	if (!file) {
		return -1; // unable to open
	}

	*length = GetFileLength(file);

	if (length == 0) {
		return -2; // empty
	}

	source = new char[*length + 1];
	if (!source) {
		return -3; // unable to alloc
	}

	source[*length] = 0;
	while (file.good()) {
		source[i] = file.get();
		if (!file.eof()) {
			i++;
		}
	}

	source[i] = 0; // 0-terminated
	
	file.close();

	return 0;
}

//************************************
// Method:    LoadFromFile
// FullName:  QuackShader::LoadFromFile
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char *
//************************************
void QuackShader::LoadFromFile(GLuint type, const char * fileName) {
	// Get the contents of the file and do some error checking
	char * data = 0;
	int result;
	unsigned long length = 0;

	// Load the file
	result = LoadFile(fileName, data, &length);

	if (result != 0) {
		// darn something bad happened
	}

	switch (type) {
	case VERTEX:
		VertexHandle = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexHandle, 1, &data, NULL);
		glAttachShader(Handle, VertexHandle);

		delete data;
		break;
	case FRAGMENT:
		FragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentHandle, 1, &data, NULL);
		glAttachShader(Handle, FragmentHandle);

		delete data;
		break;
	default:
		// error
		break;
	}
}

//************************************
// Method:    SetUniform
// FullName:  QuackShader::SetUniform
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char *
// Parameter: type *
//************************************
void QuackShader::SetUniform(const char * name, glm::mat4 mat) {
	GLuint uniformLocation = glGetUniformLocation(Handle, name);
	if (uniformLocation == -1) {
		// Unable to find uniform
	}

	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

//************************************
// Method:    Use
// FullName:  QuackShader::Use
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void QuackShader::Use() {
	// TODO: Add error checking

	glUseProgram(Handle);
}
