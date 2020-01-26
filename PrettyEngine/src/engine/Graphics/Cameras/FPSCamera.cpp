#include "pepch.h"
#include "FPSCamera.h"

namespace PrettyEngine {

	FPSCamera::FPSCamera(const Matrix4& projectionMatrix)
		: Camera(projectionMatrix)
	{
	}

	FPSCamera::~FPSCamera()
	{
	}
}