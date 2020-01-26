#include "pepch.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"

namespace PrettyEngine {

	Rigidbody::Rigidbody(const float& density, const float& drag, BodyType type)
		: m_Type(type), m_Density(density), m_Drag(drag)
	{
	
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Init()
	{
		m_Transform = entity->GetComponent<Transform>();
		PE_CORE_ASSERT(m_Transform, "Transform couldn't be found. Returned NULL!");	
		m_ModelComp = entity->GetComponent<ModelComponent>();
		PE_CORE_ASSERT(m_ModelComp, "Model couldn't be found. Returned NULL!");	

		
		m_Body.Init(m_Transform, m_Density, m_Drag, m_ModelComp->model->GetBoundingBox().min, m_ModelComp->model->GetBoundingBox().max, m_Type);


		//m_Body.Init(m_Transform, m_Type);

		//mass = m_Body.GetMass();
		//density = m_Body.GetDensity();
		//drag = m_Body.GetFriction();
		//*m_Transform->position = Vector3(GetPosition(), m_Transform->position->z);

		m_Transform->SetRigidbody(this);
	}
}
