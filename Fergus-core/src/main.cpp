#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <algorithm>    // std::min



#include "graphics\window.h"
#include "graphics\camera.h"
#include "graphics\renderers\renderer3d.h"
#include "graphics\models\rawmodel.h"
#include "graphics\shader.h"
#include "graphics\models\modeltexture.h"
#include "graphics\models\texturedmodel.h"
#include "graphics\entities\entity.h"
#include "graphics\models\model.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//TODO: load shader in Mesh::draw



// Breakpoints that should ALWAYS trigger (EVEN IN RELEASE BUILDS) [x86]!
#ifdef _MSC_VER
# define eTB_CriticalBreakPoint() if (IsDebuggerPresent ()) __debugbreak ();
#else
# define eTB_CriticalBreakPoint() asm (" int $3");
#endif

void
ETB_GL_ERROR_CALLBACK(GLenum        source,
	GLenum        type,
	GLuint        id,
	GLenum        severity,
	GLsizei       length,
	const GLchar* message,
	GLvoid*       userParam);

int main()
{
	Window window(960.0f, 540.0, "Lex ist lustig!");

	//pfuscherei
	if (glDebugMessageControlARB != NULL) {
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
		glDebugMessageCallbackARB((GLDEBUGPROCARB)ETB_GL_ERROR_CALLBACK, NULL);
		
	}


	Camera camera(glm::vec3(0, 0, 0), window);

	Renderer3D renderer;
	

	GLfloat vertices [] = {
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,0.5f,0,

		-0.5f,0.5f,1,
		-0.5f,-0.5f,1,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		0.5f,0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1,
		0.5f,0.5f,1,

		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		-0.5f,-0.5f,1,
		-0.5f,0.5f,1,

		-0.5f,0.5f,1,
		-0.5f,0.5f,0,
		0.5f,0.5f,0,
		0.5f,0.5f,1,

		-0.5f,-0.5f,1,
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0.5f,-0.5f,1

	};

	GLfloat textureCoords [] = {

		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0

	};

	GLushort indices [] = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

	};

	//RawModel model(vertices, 12 * 6, indices, 12 * 3, textureCoords, 23 * 2);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	//ModelTexture modelTexture("res/textures/basic2.png");
	//TexturedModel texturedModel(&model, &modelTexture);

	//Entity entity(&texturedModel, glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), 1);
	
	Model suit("res/models/teapot.obj");
	

	while (!window.closed())
	{
		window.clear();
		
		camera.update();

		shader.enable();

		// view/projection transformations
		
		glm::mat4 projection = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();
		shader.setUniformMat4("pr_matrix", projection);
		shader.setUniformMat4("vw_matrix", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0, -0.1, 0));
		model = glm::scale(model, glm::vec3(0.002, 0.002, 0.002));
		model = glm::rotate(model, 100.f, glm::vec3(0, 1, 0));

		shader.setUniformMat4("ml_matrix", model);
		
		suit.draw(&shader);


		//entity.rotate(glm::vec3(0.01f, 0.01f, 0.0f));

		//renderer.render(&entity, &shader, &camera);

		window.update();
	}
	return 0;
}


const char*
ETB_GL_DEBUG_SOURCE_STR(GLenum source)
{
	static const char* sources[] = {
		"API",   "Window System", "Shader Compiler", "Third Party", "Application",
		"Other", "Unknown"
	};

	int str_idx =
		std::min(source - GL_DEBUG_SOURCE_API,
			sizeof(sources) / sizeof(const char *));

	return sources[str_idx];
}

const char*
ETB_GL_DEBUG_TYPE_STR(GLenum type)
{
	static const char* types[] = {
		"Error",       "Deprecated Behavior", "Undefined Behavior", "Portability",
		"Performance", "Other",               "Unknown"
	};

	int str_idx =
		std::min(type - GL_DEBUG_TYPE_ERROR,
			sizeof(types) / sizeof(const char *));

	return types[str_idx];
}

const char*
ETB_GL_DEBUG_SEVERITY_STR(GLenum severity)
{
	static const char* severities[] = {
		"High", "Medium", "Low", "Unknown" };
	return "peter rendl";
}



void
ETB_GL_ERROR_CALLBACK(GLenum        source,
	GLenum        type,
	GLuint        id,
	GLenum        severity,
	GLsizei       length,
	const GLchar* message,
	GLvoid*       userParam)
{
	printf("OpenGL Error:\n");
	printf("=============\n");

	printf(" Object ID: ");
	printf("%d\n", id);

	printf(" Severity:  ");
	printf(ETB_GL_DEBUG_SEVERITY_STR(severity));

	printf(" Type:      ");
	printf("%s\n", ETB_GL_DEBUG_TYPE_STR(type));

	printf(" Source:    ");
	printf("%s\n", ETB_GL_DEBUG_SOURCE_STR(source));

	printf(" Message:   ");
	printf("%s\n\n", message);

	// Force the console to flush its contents before executing a breakpoint
	//eTB_FlushConsole();

	// Trigger a breakpoint in gDEBugger...
	glFinish();

	// Trigger a breakpoint in traditional debuggers...
	//eTB_CriticalBreakPoint();
}
