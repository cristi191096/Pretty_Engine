#pragma once
#include "Camera.h"

namespace PrettyEngine {

	class StaticCamera : public Camera
	{
	public:
		StaticCamera();			// Default Constructor		TODO: Add default orthografic matrix
		StaticCamera(const Matrix4& projectionMatrix);
		~StaticCamera();

	private:

	};

	
}
