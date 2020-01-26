#include "pepch.h"
#include "GameApplication.h"
#include "GameLayer.h"

/*
		Should do the following : 
			- push GameLayer, EnvironmentLayer, MenuLayer (GUI)
			- Match. I mean sync the editor layers within the Game Logic. E.g. Open Menu -> Level Editor Option.
*/
GameApplication::GameApplication(RenderAPI api) : Application(api)
{
		//Push Layers here

	PushLayer(new GameLayer());

}

GameApplication::~GameApplication()
{
	// Pop Layers and deallocate other chuncks of memory
}



int main(int argc, char** argv)
{
	PrettyEngine::Log::Init();
	GameApplication* game = new GameApplication(RenderAPI::OPENGL);
	game->Run();
	delete game;
}