#pragma once
#include "PrettyEngine.h"

using namespace PrettyEngine;

//#pragma region Game Layers
//
//class GameLayer : public Layer
//{
//
//};
//
//class EnvironmentLayer : public Layer
//{
//
//};
//
//class MenuLayer : public Layer
//{
//
//};
//
//
//
//#pragma endregion Engine layers used within the game. Layers are containers for objects that are rendered differently. e.g. Animated Objects Layer, Static Objects Layer, GUI Layer


class GameApplication : public Application
{
public:						
	GameApplication(RenderAPI api); 

	~GameApplication();

	

};
