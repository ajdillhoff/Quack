#pragma once

#include "BShared.h"
#include <fstream>
#include <windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

#define SHADER_PATH "Shaders/"

enum BroShaderType {
	VERTEX,
	FRAGMENT,
	//GEOMETRY,
	//TESS_CONTROL,
	//TESS_EVALUATION
};

class BroShader {
private:
	int Handle;
	int VertexHandle;
	int FragmentHandle;

	bool Linked;

	int GetUniformLocation(const char * name);

	// File Operations
	bool FileExists(const char & fileName);

	//************************************
	// Method:    GetFileLength
	// FullName:  BroShader::GetFileLength
	// Access:    private 
	// Returns:   unsigned long
	// Qualifier:
	// Parameter: ifstream & file
	//************************************
	unsigned long GetFileLength(ifstream& file);

	//************************************
	// Method:    LoadFile
	// FullName:  BroShader::LoadFile
	// Access:    private 
	// Returns:   int
	// Qualifier:
	// Parameter: char * fileName
	// Parameter: char * source
	// Parameter: unsigned long * length
	//************************************
	int LoadFile(const char * fileName, char *& source, unsigned long * length);
public:
	BroShader();
	~BroShader();

	//************************************
	// Method:    BindAttribLocation
	// FullName:  BroShader::BindAttribLocation
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: GLuint
	// Parameter: const char *
	// Description: Wrapper around glBindAttribLocation
	//************************************
	void BindAttribLocation(GLuint, const char *);

	//************************************
	// Method:    BindFragDataLocation
	// FullName:  BroShader::BindFragDataLocation
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: GLuint
	// Parameter: const char *
	// Description: Wrapper around glBindFragDataLocation
	//************************************
	void BindFragDataLocation(GLuint, const char *);

	//************************************
	// Method:    Compile
	// FullName:  BroShader::Compile
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Compile();

	//************************************
	// Method:    GetHandle
	// FullName:  BroShader::GetHandle
	// Access:    public 
	// Returns:   int
	// Qualifier:
	//************************************
	int GetHandle();

	//************************************
	// Method:    IsLinked
	// FullName:  BroShader::IsLinked
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool IsLinked();

	//************************************
	// Method:    Link
	// FullName:  BroShader::Link
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	//************************************
	bool Link();

	//************************************
	// Method:    LoadFromFile
	// FullName:  BroShader::LoadFromFile
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char *
	//************************************
	void LoadFromFile(GLuint, const char *);

	//************************************
	// Method:    SetUniform
	// FullName:  BroShader::SetUniform
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: const char *
	// Parameter: type *
	// TODO: Possible to template this?
	//************************************
	void SetUniform(const char *, glm::mat4);
	void SetUniform(const char *, float);
	void SetUniform(const char *, int);
	void SetUniform(const char *, bool);

	//************************************
	// Method:    Use
	// FullName:  BroShader::Use
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void Use();
};

