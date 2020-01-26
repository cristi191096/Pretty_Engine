#include "pepch.h"
#include "ModelComponent.h"

namespace PrettyEngine {
	ModelComponent::ModelComponent(Model * m)
		: model(m)
	{
	}
	ModelComponent::~ModelComponent()
	{
		delete model;
	}
	void ModelComponent::Init()
	{
		
	}
}