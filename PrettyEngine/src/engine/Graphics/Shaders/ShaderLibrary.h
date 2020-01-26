#pragma once
#include "Shader.h"


namespace PrettyEngine {

	//TODO: Add PE_API for each shader when writing the editor
	PE_API Shader* defaultShader2D();
	PE_API Shader* flatColourShader();
	PE_API Shader* blinPhongShader();

}