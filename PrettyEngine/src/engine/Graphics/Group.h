#pragma once

#include "Renderable2D.h"


namespace PrettyEngine {

	class PE_API Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		Matrix4 m_TransformationMatrix;
	public:
		Group(const Matrix4& transform);
		~Group();
		void Add(Renderable2D* renderable);
		void Submit(Renderer2D* renderer) const override;

		Matrix4& GetTransformRef() { return m_TransformationMatrix; }

	};


}