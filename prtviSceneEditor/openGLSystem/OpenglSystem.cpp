#include "OpenglSystem.h"
#include "../vendor/easylogging++.h"

bool OpenglSystem::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG(ERROR) << "OpenglSystem::initSDL() Failed to initialize SDL";
		return false;
	}
	return true;
}

SDL_Window* OpenglSystem::initWindow(int width, int height)
{
	SDL_Window* window = SDL_CreateWindow(
		"prtvi scene editor",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (!window)
	{
		LOG(ERROR) << "OpenglSystem::initWindow() Failed to initialize SDL_Window* window";
	}

	return window;
}

SDL_GLContext OpenglSystem::initContext(SDL_Window* window)
{
	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (!context)
	{
		LOG(ERROR) << "OpenglSystem::initContext() Failed to initialize SDL_GLContext context";
	}

	return context;
}

bool OpenglSystem::initGlew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err)
	{
		LOG(ERROR) << "OpenglSystem::initGlew() Failed to initialize GLEW";
		return false;
	}
	return true;
}

void OpenglSystem::initGlAttributes(unsigned int major, unsigned int minor)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void OpenglSystem::cleanUp(SDL_GLContext context, SDL_Window* window)
{
	LOG(INFO) << "OpenglSystem::cleanUp() deleting context, window and running SDL_QUIT()";
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void OpenglSystem::enableMouseCapture(bool state)
{
	state ? SDL_CaptureMouse(SDL_TRUE) : SDL_CaptureMouse(SDL_FALSE);
}

void OpenglSystem::enableMouseCursor(bool state)
{
	state ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
}

void OpenglSystem::enableDepthTest(bool state)
{
	state ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void OpenglSystem::setMouseToCenter(SDL_Window* window, unsigned int width, unsigned int height)
{
	SDL_WarpMouseInWindow(window, width / 2.0f, height / 2.0f);
}

void OpenglSystem::enableWireframe(bool state)
{
	state ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenglSystem::enableCulling(bool state)
{
	if (state == true)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		return;
	}

	glDisable(GL_CULL_FACE);
}
