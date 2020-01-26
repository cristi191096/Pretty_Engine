#pragma once
#include "Component.h"
#include "engine\Graphics\Model.h"

namespace PrettyEngine {

	class ModelComponent : public Component
	{

	public:
		Model* model;

	
		ModelComponent(Model* m);
		~ModelComponent();

		virtual ComponentType GetType() const override { return GetStaticType(); }

		static ComponentType GetStaticType() {
			static ComponentType type = ComponentType::Model;
			return type;
		}

		virtual void Init() override;

	};
}