#include "pepch.h"
#include "StaticCamera.h"

namespace PrettyEngine {

	StaticCamera::StaticCamera(const Matrix4& projectionMatrix)
		: Camera(projectionMatrix)
	{
	}

	StaticCamera::~StaticCamera()
	{
	}
}