#include "pepch.h"
#include "DebugLayer2D.h"

#include "Platform\OpenGL\GLCore.h"

#include "Utilities\Files.h"



#include "engine\Graphics\Cameras\EditorCamera.h"
#include "engine\Core\Scene2D.h"



namespace PrettyEngine {

	
	DebugLayer2D::DebugLayer2D() 
		: Layer("DebugLayer2D")
	{
		//m_Scene = new Scene2D(new EditorCamera(Vector3(0.2f, 2.6f, 9.6f),Matrix4::Orthographic(-180.0f, 180.0f, -100.0f, 100.0f, -100.0f, 1000.0f)));
		m_Scene = new Scene2D(new EditorCamera(Vector3(0.2f, 2.6f, 9.6f),Matrix4::Perspective(60.0f, 1280/720, 1.0f, 1000.0f)));
	}

	DebugLayer2D::~DebugLayer2D()
	{
	}

	void DebugLayer2D::OnAttach()
	{

		 Group* group = new Group(Matrix4::Translate(Vector3(0, 0.1f, 0)));
		 
		 Sprite* object = new Sprite(0, 0, 20, 20, Vector4(0, 0, 1, 1));
		 Sprite* object1 = new Sprite( -50, -100, Texture2D::CreateFromFile("..PrettyEngine/src/game/res/Textures/pixel.png"));
		 Sprite* object3 = new Sprite(-150, -100, Texture2D::CreateFromFile("..PrettyEngine/src/game/res/Textures/grad.png"));
		 Sprite* object2 = new Sprite(0, -0.1, 20, 5, Vector4(0.8, 0.75, 0.05, 1));

		

		 //group->Add(object);
		 //group->Add(object1);
		 
		// Renderer::SetViewport(0, 0, 500, 500);

		// m_Scene->Add(object);
		// m_Scene->Add(object1);
		// m_Scene->Add(object2);
		// m_Scene->Add(object3);
		 
		 

		
		 
		 //group->Submit(renderer);
		 
	
		
	}

	void DebugLayer2D::OnDetach()
	{
	}

	void DebugLayer2D::OnUpdate()
	{
		m_Scene->BeginScene();
		m_Scene->DrawLine(Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.5f), 0.1f);
		m_Scene->DrawRect(Vector2(0.0f, 0.0f), Vector2(3.0f, 3.0f));
		m_Scene->Submit();
		m_Scene->EndScene();
		m_Scene->RenderScene();

	}

	void DebugLayer2D::OnEvent(Event & ev)
	{
		/*
		EventHandler handler(ev);
		handler.Handle<MouseButtonPressedEvent>(BIND_EVENT_FN(DebugLayer2D::OnMouseButtonPressedEvent));
		handler.Handle<MouseButtonReleasedEvent>(BIND_EVENT_FN(DebugLayer2D::OnMouseButtonReleasedEvent));
		handler.Handle<MouseMovedEvent>(BIND_EVENT_FN(DebugLayer2D::OnMouseMovedEvent));
		handler.Handle<MouseScrolledEvent>(BIND_EVENT_FN(DebugLayer2D::OnMouseScrolledEvent));
		handler.Handle<KeyPressedEvent>(BIND_EVENT_FN(DebugLayer2D::OnKeyPressedEvent));
		handler.Handle<KeyTypedEvent>(BIND_EVENT_FN(DebugLayer2D::OnKeyTypedEvent));
		handler.Handle<KeyReleasedEvent>(BIND_EVENT_FN(DebugLayer2D::OnKeyReleasedEvent));
		handler.Handle<WindowResizeEvent>(BIND_EVENT_FN(DebugLayer2D::OnWindowResizeEvent));
		handler.Handle<WindowCloseEvent>(BIND_EVENT_FN(DebugLayer2D::OnWindowCloseEvent));
		*/
	}

#if 0
	bool DebugLayer2D::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
	{
		/*ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
	*/
		return false;
	}

	bool DebugLayer2D::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
	{
		/*ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;*/

		return false;
	}

	bool DebugLayer2D::OnMouseMovedEvent(MouseMovedEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool DebugLayer2D::OnMouseScrolledEvent(MouseScrolledEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.MouseWheelH += e.GetXOffset();
		//io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool DebugLayer2D::OnKeyPressedEvent(KeyPressedEvent & e)
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

	bool DebugLayer2D::OnKeyTypedEvent(KeyTypedEvent & e)
	{
		
		//ImGuiIO& io = ImGui::GetIO();
		//int keycode = e.GetKeyCode();
		//if (keycode > 0 && keycode < 0x10000)
		//	io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool DebugLayer2D::OnKeyReleasedEvent(KeyReleasedEvent & e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool DebugLayer2D::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		//ImGuiIO& io = ImGui::GetIO();
		//io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		//io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		//glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

	bool DebugLayer2D::OnWindowCloseEvent(WindowCloseEvent & e)
	{
		//ImGui::CloseCurrentPopup();
		//TODO: Find how to close ImGUI windows

		return false;
	}
#endif
}