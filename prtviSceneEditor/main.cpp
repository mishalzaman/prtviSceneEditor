#include <GL/glew.h>
#include <sdl/SDL.h>
#include "openGLSystem/OpenglSystem.h"
#include "vendor/easylogging++.h"
#include "Editor.h"
#include "MngrProgram.h"
#include "MngrTexture.h"
#include "LdrModelObj.h"

INITIALIZE_EASYLOGGINGPP

const unsigned int ERROR_SDL = 1;
const unsigned int ERROR_WINDOW = 2;
const unsigned int ERROR_CONTEXT = 3;
const unsigned int ERROR_GLEW = 4;
const unsigned int SUCCESS_SHUTDOWN = 0;

SDL_Window* window;
SDL_GLContext context;

unsigned int width = 1280;
unsigned int height = 720;

const std::string LOGFILE = "development.log";

unsigned int shutDownSceneEditor(SDL_Window* window, SDL_GLContext context, unsigned int returnCode);

int main(int argc, char *argv[])
{
	/*===================================================
	Logging system configuration
	====================================================*/

	el::Configurations defaultConf;
	defaultConf.set(el::Level::Error, el::ConfigurationType::Enabled, "true");
	defaultConf.setGlobally(el::ConfigurationType::ToStandardOutput, "true");
	defaultConf.setGlobally(el::ConfigurationType::Filename, LOGFILE);
	defaultConf.setGlobally(el::ConfigurationType::ToFile, "true");

	el::Loggers::reconfigureLogger("default", defaultConf);
	el::Loggers::setDefaultConfigurations(defaultConf, true);

	/*===================================================
	OpengGL / SDL / Glew initialization
	====================================================*/

	if (!OpenglSystem::initSDL())
	{
		return shutDownSceneEditor(window, context, ERROR_SDL);
	}

	window = OpenglSystem::initWindow(width, height);
	if (!window)
	{
		return shutDownSceneEditor(window, context, ERROR_WINDOW);
	}

	context = OpenglSystem::initContext(window);
	if (!context)
	{
		return shutDownSceneEditor(window, context, ERROR_CONTEXT);
	}

	if (!OpenglSystem::initGlew())
	{
		return shutDownSceneEditor(window, context, ERROR_GLEW);
	}
	OpenglSystem::initGlAttributes(3, 3);
	OpenglSystem::enableMouseCursor(true);
	OpenglSystem::enableMouseCapture(true);
	OpenglSystem::setMouseToCenter(window, width, height);
	OpenglSystem::enableDepthTest(true);

	/*===================================================
	Initialize scene subsystems
	====================================================*/

	const char* sceneFilename = "scenes/scene1.prtvi";

	Editor editor = Editor{ width, height };
	editor.load(sceneFilename);

	MngrProgram mngrProgram = MngrProgram{ sceneFilename };
	mngrProgram.load();

	MngrTexture mngrTexture = MngrTexture{ sceneFilename };
	mngrTexture.load();

	LdrModelObj ldrModelObj = LdrModelObj{ "assets/crate.obj" };

	/*===================================================
	Main scene Loop
	====================================================*/

	LOG(INFO) << "Main() Begin program loop";
	while (!editor.quit)
	{
		editor.quit = true;
	}

	/*===================================================
	Shut down
	====================================================*/
	return shutDownSceneEditor(window, context, SUCCESS_SHUTDOWN);
}

unsigned int shutDownSceneEditor(SDL_Window * window, SDL_GLContext context, unsigned int returnCode)
{
	LOG(INFO) << "shutDownSceneEditor() shutting down prtvi scene editor";
	el::Loggers::flushAll();
	OpenglSystem::cleanUp(context, window);

	return returnCode;
}
