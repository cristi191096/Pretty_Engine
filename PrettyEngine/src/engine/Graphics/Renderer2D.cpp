#include "pepch.h"
#include "Renderer2D.h"
#include "engine\Core\Context.h"
#include "Renderable2D.h"

#include "Renderer.h"
#include "Cameras\Camera.h"

#include "engine\Graphics\Shaders\ShaderLibrary.h"



namespace PrettyEngine {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6




	Renderer2D::Renderer2D(Camera* camera)
		: m_IndexCount(0)
	{
		SetCamera(camera);
		Init();
	}

	Renderer2D::~Renderer2D()
	{
	}

	void Renderer2D::Push(const Matrix4 & matrix, bool override)
	{
		if (override)
			m_TransformationStack.push_back(matrix);
		else
			m_TransformationStack.push_back(*m_TransformationBack * matrix);

		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::Pop()
	{
		if (m_TransformationStack.size() > 1)
			m_TransformationStack.pop_back();

		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::SetCamera(Camera* camera)
	{
		m_Camera = camera;
	}

	void Renderer2D::DrawLine(float x0, float y0, float x1, float y1, uint color, float thickness)
	{
		const std::vector<Vector2>& uv = Renderable2D::GetDefaultUVs();
		float ts = 0.0f;
	

		Vector2 normal = Vector2(y1 - y0, -(x1 - x0)).Normalise() * thickness;

		Vector3 vertex = *m_TransformationBack * Vector3(x0 + normal.x, y0 + normal.y, 0.0f);
		m_Buffer->position = vertex;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * Vector3(x1 + normal.x, y1 + normal.y, 0.0f);
		m_Buffer->position = vertex;
		m_Buffer->uv = uv[1];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * Vector3(x1 - normal.x, y1 - normal.y, 0.0f);
		m_Buffer->position = vertex;
		m_Buffer->uv = uv[2];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		vertex = *m_TransformationBack * Vector3(x0 - normal.x, y0 - normal.y, 0.0f);
		m_Buffer->position = vertex;
		m_Buffer->uv = uv[3];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void Renderer2D::DrawLine(const Vector2 & start, const Vector2 & end, uint color, float thickness)
	{
		DrawLine(start.x, start.y, end.x, end.y, color, thickness);
	}

	void Renderer2D::DrawLine(const Vector2 & start, const Vector2 & end, const Vector4 & color, float thickness)
	{
		uint col = (uint)(color.w * 255.0f) << 24 | (uint)(color.z * 255.0f) << 16 | (uint)(color.y * 255.0f) << 8 | (uint)(color.x * 255.0f);

		DrawLine(start.x, start.y, end.x, end.y, col, thickness);
	}

	void Renderer2D::DrawRect(float x, float y, float width, float height, uint color, float thickness)
	{
		DrawLine(x, y, x + width, y, color, thickness);
		DrawLine(x + width, y, x + width, y + height, color, thickness);
		DrawLine(x + width, y + height, x, y + height, color, thickness);
		DrawLine(x, y + height, x, y, color, thickness);
	}

	void Renderer2D::DrawRect(const Vector2 & position, const Vector2 & size, uint color, float thickness)
	{
		DrawRect(position.x, position.y, size.x, size.y, color, thickness);
	}

	void Renderer2D::SetProjection()
	{
		m_Shader->SetUniformMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());
	}

	void Renderer2D::SetView()
	{
	//	PE_CORE_TRACE("View: {0}, {1}, {2}, {3}", m_Camera->GetViewMatrix().rows[0], m_Camera->GetViewMatrix().rows[1], m_Camera->GetViewMatrix().rows[2], m_Camera->GetViewMatrix().rows[3]);
		m_Shader->SetUniformMat4("u_ViewMatrix",m_Camera->GetViewMatrix());
	}


	void Renderer2D::Init()
	{
		m_TransformationStack.push_back(Matrix4::Identity());
		m_TransformationBack = &m_TransformationStack.back();

		m_Shader = defaultShader2D();

		for (uint i = 0; i <= RENDERER_MAX_TEXTURES; i++)
			m_TextureIDs[i] = i;

		m_Shader->Bind();
		
		SetProjection();
		//SetPV(Matrix4::Orthographic(-180.0f, 180.0f, -100.0f, 100.0f, -1.0f, 10.0f));
		m_Shader->SetUniform1iv("textures", m_TextureIDs, RENDERER_MAX_TEXTURES);
		//m_Shader->SetUniform1i("textures", 0);
		

		m_VAO = VertexArray::Create();
		m_VBO = VertexBuffer::Create(BufferUsage::DYNAMIC);
		m_VBO->Bind();
		m_VAO->Bind();
		m_VBO->Resize(RENDERER_BUFFER_SIZE);

		m_VBO->SetLayout(m_Shader->GetLayout());
		m_VAO->PushBuffer(m_VBO);

		uint* indices = new uint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = IndexBuffer::Create(indices, RENDERER_INDICES_SIZE);

		m_VAO->Unbind();
	}

	float Renderer2D::SubmitTexture(Texture * texture)
	{
		float result = 0.0f;
		bool found = false;
		for (uint i = 0; i < m_Textures.size(); i++)
		{
			if (m_Textures[i] == texture)
			{
				result = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_Textures.size() >= RENDERER_MAX_TEXTURES)
			{
				End();
				Flush();
				Begin();
			}
			m_Textures.push_back(texture);
			result = (float)(m_Textures.size());
		}
		return result;
	}

	void Renderer2D::Begin()
	{
		//TODO: set a ifdef for calling submit in start or update
		//m_IndexCount = 0;	//If submit is called one time.
		//m_Textures.clear(); //If submit is called one time.
		m_VAO->Bind();
		m_Buffer = m_VAO->GetBuffer()->GetPointer<VertexData>();
	}

	void Renderer2D::Submit(const Renderable2D* renderable)
	{
		if (!renderable->IsVisible())
			return;

		const Vector3& position = renderable->GetPosition();
		const Vector2& size = renderable->GetSize();
		const uint color = renderable->GetColor();
		//const Vector4& color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		const std::vector<Vector2>& uvs = renderable->GetUVs();
		const Texture* texture = renderable->GetTexture();

		float textureSlot = 0.0f;
		if (texture)
			textureSlot = SubmitTexture(renderable->GetTexture());

		
		//BufferLayout layout;
		//layout.Push<Vector3>("position");
		//layout.Push<Vector4>("color");
		
		
		

		m_Buffer->position = *m_TransformationBack * position;
		m_Buffer->uv = uvs[0];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * Vector3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uvs[1];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * Vector3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uvs[2];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->position = *m_TransformationBack * Vector3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uvs[3];
		m_Buffer->tid = textureSlot;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;

		
	}

	void Renderer2D::End()
	{
		m_VAO->GetBuffer()->ReleasePointer();
		m_VAO->Unbind();
	}

	void Renderer2D::Flush()
	{
		//Renderer::SetDepthTesting(false);

		m_Shader->Bind();

		SetView();

		for (uint i = 0; i < m_Textures.size(); i++)
			m_Textures[i]->Bind(i);

		m_VAO->Bind();
		m_IBO->Bind();
		m_VAO->Draw(m_IndexCount);
		m_IBO->Unbind();
		m_VAO->Unbind();

		for (uint i = 0; i < m_Textures.size(); i++)
			m_Textures[i]->Unbind(i);

		m_Shader->Unbind();
		//Renderer::SetDepthTesting(true);
#if 1	//If submit is called once per frame do this
		m_IndexCount = 0;
		m_Textures.clear();
#endif
		
	}




}