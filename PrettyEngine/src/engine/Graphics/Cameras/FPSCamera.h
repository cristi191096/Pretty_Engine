#pragma once
#include "Camera.h"

namespace PrettyEngine {

	class FPSCamera : public Camera
	{
	public:
		FPSCamera(const Matrix4& projectionMatrix);
		~FPSCamera();

	private:

	};

}