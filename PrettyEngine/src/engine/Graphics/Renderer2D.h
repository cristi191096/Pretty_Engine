#pragma once

#include "Buffers\VertexBuffer.h"
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexArray.h"
#include "engine\Maths\maths.h"

#include "engine\Graphics\Shaders\Shader.h"



namespace PrettyEngine {

#define RENDERER_MAX_TEXTURES	32 - 1		//TEXTURE0 is not used ( for safety)

	class Renderable2D;
	class Texture;
	class Camera;
	struct VertexData;

	class Renderer2D
	{
	public:
		Renderer2D(Camera* camera);
		~Renderer2D();

		void Push(const Matrix4& matrix, bool override = false);
		void Pop();

		void Begin();
		void Submit(const Renderable2D* renderable);
		void End();
		void Flush();

		void SetCamera(Camera* camera);
	

		// Drawing Functions
		void DrawLine(float x0, float y0, float x1, float y1, uint color = 0xffffffff, float thickness = 0.1f);
		void DrawLine(const Vector2& start, const Vector2& end, uint color = 0xffffffff, float thickness = 0.1f);
		void DrawLine(const Vector2& start, const Vector2& end, const Vector4& color = Vector4(1.0f, 1.0f, 1.0f, 1.0f), float thickness = 0.02f);
		void DrawRect(float x, float y, float width, float height, uint color = 0xffffffff, float thickness = 0.1f);
		void DrawRect(const Vector2& position, const Vector2& size, uint color = 0xffffffff, float thickness = 0.1f);
		

	//	static Renderer2D* Create();

	private:
		std::vector<Matrix4> m_TransformationStack;
		const Matrix4* m_TransformationBack;

		//Vertex stuff
		VertexData* m_Buffer;
		Shader* m_Shader;
		VertexArray* m_VAO;
		VertexBuffer* m_VBO;
		IndexBuffer* m_IBO;

		uint m_IndexCount;
		//========================

		//Textures
		std::vector<Texture*> m_Textures;
		int m_TextureIDs[RENDERER_MAX_TEXTURES];
		//========================

		Camera* m_Camera;	//TODO: Change the use of Camera with ShaderResources/ShaderUniformTypes


	private:
		void Init();
		float SubmitTexture(Texture* texture);
		void SetProjection();
		void SetView();
	};
}