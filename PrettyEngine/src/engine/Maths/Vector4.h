#pragma once

#include "engine\Core\Core.h"

#include "Vector3.h"

#include <ostream>

namespace PrettyEngine { 

	class Matrix4;
	

	class PE_API Vector4
	{
	public:
		float x, y, z, w;

		Vector4() = default;
		Vector4(float scalar);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector3& xyz, float w);

		Vector4& Add(const Vector4& other);
		Vector4& Subtract(const Vector4& other);
		Vector4& Multiply(const Vector4& other);
		Vector4& Divide(const Vector4& other);

		Vector4 Multiply(const Matrix4& transform) const;

		inline String Export() const { return String(std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " " + std::to_string(w)); }

		friend Vector4 operator+(Vector4 left, const Vector4& right);
		friend Vector4 operator-(Vector4 left, const Vector4& right);
		friend Vector4 operator*(Vector4 left, const Vector4& right);
		friend Vector4 operator/(Vector4 left, const Vector4& right);

		bool operator==(const Vector4& other);
		bool operator!=(const Vector4& other);

		Vector4& operator+=(const Vector4& other);
		Vector4& operator-=(const Vector4& other);
		Vector4& operator*=(const Vector4& other);
		Vector4& operator/=(const Vector4& other);

		float DotProduct(const Vector4& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vector4& vector);
	};

} 