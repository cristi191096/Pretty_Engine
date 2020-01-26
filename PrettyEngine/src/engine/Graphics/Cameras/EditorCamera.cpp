#include "pepch.h"
#include "EditorCamera.h"

#include "engine\Events\Input.h"
#include "engine\Events\Event.h"

namespace PrettyEngine {
	EditorCamera::EditorCamera(const Vector3 & position, const Matrix4 & projectionMatrix)
		: Camera(projectionMatrix)
	{
		m_Position = position;

		// Default values
		m_PanSpeed = 0.0015f;
		m_RotationSpeed = 0.002f;
		m_ZoomSpeed = 0.2f;

		
		m_Rotation = Vector3(90.0f, 90.0f, 0.0f);

		m_ViewMatrix = Matrix4::Translate(m_Position);// *Matrix4::Rotate(50, Vector3::ZAxis());//Matrix4::Identity();

		m_FocalPoint = Vector3::Zero();
		m_Distance = m_Position.Distance(m_FocalPoint);

		m_Yaw = 0;//3.0f * PI / 4.0f;
		m_Pitch = 0;// -3.0f * PI / 4.0f;
	}
	EditorCamera::EditorCamera(const Matrix4& projectionMatrix)
		: Camera(projectionMatrix)
	{
		// Default values
		m_PanSpeed = 0.0015f;
		m_RotationSpeed = 0.002f;
		m_ZoomSpeed = 0.2f;

		m_Position = Vector3(0.0f, 0.0f, 10.0f);
		m_Rotation = Vector3(90.0f, 0.0f, 0.0f);

		m_ViewMatrix = Matrix4::Translate(m_Position);// *Matrix4::Rotate(50, Vector3::ZAxis());//Matrix4::Identity();

		m_FocalPoint = Vector3::Zero();
		m_Distance = m_Position.Distance(m_FocalPoint);

		m_Yaw = 3.0f * PI / 4.0f;
		m_Pitch = PI / 4.0f;
	}

	EditorCamera::~EditorCamera()
	{
	}
	void EditorCamera::Focus()
	{
	}
	void EditorCamera::Update()
	{
		//if (Input::IsModOn(Internal::mod::Alt | Internal::mod::Control))	// Doesn't work Input::IsModOn(Internal::mod::Alt & Internal::mod::Contorl)
		//	PE_CORE_TRACE("ALT and CONTROL Pressed!");
	
		if (Input::IsModOn(Internal::mod::Alt))		//Hardcoded default keys.	TODO: Make it customisable. And add mods
		{
			//TODO: Move this on the Event system
			
			const Vector2& mouse = Input::GetMousePosition();
			Vector2 delta = mouse - m_InitialMousePosition;
			m_InitialMousePosition = mouse;
			
			if (Input::GetMouseButtonDown(Mouse::Left))
				MouseRotate(delta);
			else if (Input::GetMouseButtonDown(Mouse::Middle))
				MousePan(delta);

			
		}
		
		//Keep these in the Update.
		m_Position = CalculatePosition();
		

		Quaternion orientation = GetOrientation();
		m_Rotation = orientation.ToEulerAngles() * (180.0f / PI);

		m_ViewMatrix = Matrix4::Translate(Vector3(0, 0, 1)) * Matrix4::Rotate(orientation.Conjugate()) * Matrix4::Translate(-m_Position);
		
	
	}

	void EditorCamera::OnEvent(Event & ev)
	{
		EventHandler handler(ev);
		handler.Handle<MouseScrolledEvent>(BIND_EVENT_FN(EditorCamera::OnScroll));
	}

	Vector3 EditorCamera::CalculatePosition()
	{
		return m_FocalPoint - GetForwardDirection() * m_Distance;																								
	}																																							        
																																								                                                                                                                                                              
	void EditorCamera::MousePan(const Vector2 & delta)																											                                                 
	{																																							
																																								
		m_FocalPoint += -GetRightDirection() * delta.x * m_PanSpeed * m_Distance;																				
		m_FocalPoint += GetUpDirection() * delta.y * m_PanSpeed * m_Distance;																					
	}																																							
	void EditorCamera::MouseRotate(const Vector2 & delta)																										
	{																																							
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;																									
		m_Yaw += yawSign * delta.x * m_RotationSpeed;
		m_Pitch += delta.y * m_RotationSpeed;
	}
	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * m_ZoomSpeed;
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}
	bool EditorCamera::OnScroll(MouseScrolledEvent & ev)
	{
		
		MouseZoom(ev.GetYOffset() * 10);		//Some hardcoded multiplier. TODO: Add a zoom level system depending on the FocalPoint
		PE_CORE_TRACE("YOffset: {0}", ev.GetYOffset()); 
		return true;
	}
}