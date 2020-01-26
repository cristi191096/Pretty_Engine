#include "pepch.h"
#include "DebugLayer3D.h"

#include "Platform\OpenGL\GLCore.h"

#include "Utilities\Files.h"

#include "engine\ECS\Components\Components.h"

#include "engine\Graphics\Cameras\EditorCamera.h"
#include "engine\Core\Scene3D.h"

#include <Box2D\Box2D.h>
#include <tinyxml2.h>
#include "Utilities\String.h"

#include "Utilities\AssetImporter.h"



namespace PrettyEngine {

	
	DebugLayer3D::DebugLayer3D() 
		: Layer("DebugLayer3D")
	{//Matrix4::Orthographic(-180.0f, 180.0f, -100.0f, 100.0f, -100.0f, 1000.0f)
		m_Scene = LevelManager::Import("src/game/res/Levels/level1.xml"); //new Scene3D(new EditorCamera(Vector3(0.0f, 0.0f, -50.0f),Matrix4::Perspective(60.0f, (float)1280 / (float) 720 , 1.0f, 1000.0f)));
	}

	DebugLayer3D::~DebugLayer3D()
	{
	}

	void DebugLayer3D::OnAttach()
	{

	//	//tinyxml2::XMLNode* node;
	//
	//	//=========================================================== Model Rendering Testing ==============================================================================
	//	object = new Entity();
	//	Transform* objTransform = object->GetComponent<Transform>();
	//	objTransform->position = Vector3(10.0f, 50.0f, 0.0f);
	//	objTransform->scale = Vector3(1.0f);
	//	
	//
	//	Material* someMat = new Material();
	//	
	//	someMat->SetSpecularColour(Vector3(0.0f, 1.0f, 0.0f));
	//	//someMat->SetEmissionColour(Vector3(1.0f, 0.0f, 0.0f));

	//	object->AddComponent(new ModelComponent(new Model("src/game/res/Models/ahsoka/AhsokaTest1.obj", someMat,  BufferUsage::STATIC, false)));
	//	object->AddComponent(new Rigidbody(0.00001f, 1.0f));

	//	objectRB = object->GetComponent<Rigidbody>();

	//	PE_CORE_TRACE( "The lower case char: {0}", ToLowerCase("VerY SurPriSed!"));
	//	

	//	ModelComponent* objModel = object->GetComponent<ModelComponent>();
	//	//objModel->model->SetMaterial
	//	 
	//	Entity* object1 = new Entity();
	//	objTransform = object1->GetComponent<Transform>();
	//	objTransform->position = Vector3(40.0f, 50.0f, 0.0f);
	//	objTransform->scale = Vector3(0.1f);
	//
	//	
	//	object1->AddComponent(new ModelComponent(new Model("src/game/res/Models/dice/dice.obj", BufferUsage::STATIC,true, false)));
	//	object1->AddComponent(new Rigidbody(1.0f, 0.3f));

	////=================================================================== Lighting Testing ======================================================================================

	//	dirlight = new Entity();
	//	Transform* dirLightTransform = dirlight->GetComponent<Transform>();
	//	dirLightTransform->rotation = Vector3(90, 0, 0);
	//	
	//	dirlight->AddComponent(new LightComponent( Light::Type::DIRECTIONAL, Vector3(1,1,1), Vector3(0.3,0.3,0.3), Vector3(1,1,1)/*, Optional colour, radius, intensity */));

	//	Entity* pointlight = new Entity();
	//	Transform* pointTransform = pointlight->GetComponent<Transform>();
	//	pointTransform->position = Vector3(20.0f, -25.0f, -25.0f);
	//	pointlight->AddComponent(new LightComponent( Light::Type::POINT, Vector3(1,1,1), Vector3(0.3,0.3,0.3), Vector3(1,1,1), 6.0f, 50.0f/*, Optional colour, radius, intensity */));

	////================================================================================================================================

	//	m_Scene->Add(object);
	//	m_Scene->Add(dirlight);
	//	//m_Scene->Add(pointlight);
	//	m_Scene->Add(object1);
	//
	//	 

	//	 m_Scene->Submit();
	//	 
	//	 //group->Submit(renderer);
	//	 
	//someMat->SetDiffuseColour(Vector3(1.0f, 1.0f, 1.0f));

		m_Scene->Submit();
		
	}

	void DebugLayer3D::OnDetach()
	{
	}

	void DebugLayer3D::OnUpdate()
	{
		//Transform* tr = (Transform*)object->GetComponent("Transform");
		//tr->rotation += Vector3(0.0f, 1.0f, 0.0f);
		//LightComponent* lTransform = (LightComponent*)dirlight->GetComponent("Light");
		//lTransform->rotation += Vector3(0, -10.0f, 0);
		//lTransform->light->m_Direction += Vector3(0, -10.0f, 0);

		m_Scene->RenderScene();

	}

	void DebugLayer3D::OnEvent(Event & ev)
	{
		m_Scene->OnEvent(ev);

		
		//EventHandler handler(ev);
		//handler.Handle<JumpEvent>(BIND_EVENT_FN(DebugLayer3D::OnJump));
		//handler.Handle<MoveEvent>(BIND_EVENT_FN(DebugLayer3D::OnMove));
		/*handler.Handle<MouseButtonPressedEvent>(BIND_EVENT_FN(DebugLayer3D::OnMouseButtonPressedEvent));
		handler.Handle<MouseButtonReleasedEvent>(BIND_EVENT_FN(DebugLayer3D::OnMouseButtonReleasedEvent));
		handler.Handle<MouseMovedEvent>(BIND_EVENT_FN(DebugLayer3D::OnMouseMovedEvent));
		handler.Handle<MouseScrolledEvent>(BIND_EVENT_FN(DebugLayer3D::OnMouseScrolledEvent));
		handler.Handle<KeyPressedEvent>(BIND_EVENT_FN(DebugLayer3D::OnKeyPressedEvent));
		handler.Handle<KeyTypedEvent>(BIND_EVENT_FN(DebugLayer3D::OnKeyTypedEvent));
		handler.Handle<KeyReleasedEvent>(BIND_EVENT_FN(DebugLayer3D::OnKeyReleasedEvent));
		handler.Handle<WindowResizeEvent>(BIND_EVENT_FN(DebugLayer3D::OnWindowResizeEvent));
		handler.Handle<WindowCloseEvent>(BIND_EVENT_FN(DebugLayer3D::OnWindowCloseEvent));
		*/
	}

	bool DebugLayer3D::OnJump(JumpEvent& e)
	{
		Vector2* vec = objectRB->GetVelocity();
		//objectRB->ApplyForce(Vector2(0, 0.1f),/*vec */ vec , true);
		//objectRB->SetLinearVeclocity(Vector2(0, 20));
		objectRB->ApplyForce(Vector2(0.0f, 10.0f));
		PE_CORE_TRACE("JUMPED");

		return true;
	}

	bool DebugLayer3D::OnMove(MoveEvent& e)
	{
		if (e.GetDirection() == 1) 
		{
			objectRB->SetLinearVeclocity(Vector2(20, 0));

		}
		if (e.GetDirection() == -1) 
		{
			objectRB->SetLinearVeclocity(Vector2(-20, 0));
		//	PE_CORE_TRACE("MOVED LEFT");
		}
		return true;
	}

#if 0
	bool DebugLayer3D::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
	{
		/*ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
	*/
		return false;
	}

	bool DebugLayer3D::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
	{
		/*ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;*/

		return false;
	}

	bool DebugLayer3D::OnMouseMovedEvent(MouseMovedEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool DebugLayer3D::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.MouseWheelH += e.GetXOffset();
		//io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool DebugLayer3D::OnKeyPressedEvent(KeyPressedEvent & e)
	{

		//ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = true;
		//
		//io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		//io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		//io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		//io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool DebugLayer3D::OnKeyTypedEvent(KeyTypedEvent & e)
	{
		
		//ImGuiIO& io = ImGui::GetIO();
		//int keycode = e.GetKeyCode();
		//if (keycode > 0 && keycode < 0x10000)
		//	io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool DebugLayer3D::OnKeyReleasedEvent(KeyReleasedEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool DebugLayer3D::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		//io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		//glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool DebugLayer3D::OnWindowCloseEvent(WindowCloseEvent & e)
	{
		//ImGui::CloseCurrentPopup();
		//TODO: Find how to close ImGUI windows

		return false;
	}
#endif
}