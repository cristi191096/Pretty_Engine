#pragma once

#include "engine\Core\Core.h"

#include "Vector3.h"

namespace PrettyEngine { 

	class PE_API Vector2
	{
	public:
		float x, y;

		Vector2();
		Vector2(float scalar);
		Vector2(float x, float y);
		Vector2(const Vector3& Vectortor);

		Vector2& Add(const Vector2& other);
		Vector2& Subtract(const Vector2& other);
		Vector2& Multiply(const Vector2& other);
		Vector2& Divide(const Vector2& other);

		Vector2& Add(float value);
		Vector2& Subtract(float value);
		Vector2& Multiply(float value);
		Vector2& Divide(float value);

		inline String Export() const { return String(std::to_string(x) + " " + std::to_string(y)); }

		friend Vector2 operator+(Vector2 left, const Vector2& right);
		friend Vector2 operator-(Vector2 left, const Vector2& right);
		friend Vector2 operator*(Vector2 left, const Vector2& right);
		friend Vector2 operator/(Vector2 left, const Vector2& right);

		friend Vector2 operator+(Vector2 left, float value);
		friend Vector2 operator-(Vector2 left, float value);
		friend Vector2 operator*(Vector2 left, float value);
		friend Vector2 operator/(Vector2 left, float value);

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);

		Vector2& operator+=(float value);
		Vector2& operator-=(float value);
		Vector2& operator*=(float value);
		Vector2& operator/=(float value);

		bool operator<(const Vector2& other) const;
		bool operator<=(const Vector2& other) const;
		bool operator>(const Vector2& other) const;
		bool operator>=(const Vector2& other) const;

		float Magnitude() const;
		Vector2 Normalise() const;
		float Distance(const Vector2& other) const;
		float DotProduct(const Vector2& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& Vectortor);
	};

} 