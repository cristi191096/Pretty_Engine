#pragma once

#include "engine\Core\Core.h"

namespace PrettyEngine {

	class Vector2;
	class Vector4;
	class Matrix4;

	class PE_API Vector3
	{
	public:

		float x, y, z;

		
		Vector3();
		Vector3(float scalar);
		Vector3(float x, float y, float z);
		Vector3(const Vector2& other);
		Vector3(const Vector2& other, float z);
		Vector3(float x, float y);
		Vector3(const Vector4& other);
		~Vector3();

		//Vector calculations
		Vector3 CrossProduct(const Vector3&) const;
		float DotProduct(const Vector3&) const;
		float Magnitude() const;
		Vector3 Normalise() const;
		float Distance(const Vector3& other) const;
		Vector3 Absolute();

		//void Reflect(Vector3&);
		//void Rotate(float);
		
		//Constants
		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Left();
		static Vector3 Right();
		static Vector3 Zero();

		static Vector3 XAxis();
		static Vector3 YAxis();
		static Vector3 ZAxis();

		//Standard calculations (used for overloads)
		Vector3& Add(const Vector3& other);
		Vector3& Subtract(const Vector3& other);
		Vector3& Multiply(const Vector3& other);
		Vector3& Divide(const Vector3& other);

		Vector3& Add(float other);
		Vector3& Subtract(float other);
		Vector3& Multiply(float other);
		Vector3& Divide(float other);

		Vector3 Multiply(const Matrix4& transform) const;

		inline String Export() const { return String(std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z)); }
		
		//Operator overloads
		friend Vector3 operator+(Vector3 left, const Vector3& right);
		friend Vector3 operator-(Vector3 left, const Vector3& right);
		friend Vector3 operator*(Vector3 left, const Vector3& right);
		friend Vector3 operator/(Vector3 left, const Vector3& right);

		friend Vector3 operator+(Vector3 left, float right);
		friend Vector3 operator-(Vector3 left, float right);
		friend Vector3 operator*(Vector3 left, float right);
		friend Vector3 operator/(Vector3 left, float right);

		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);

		Vector3& operator+=(float other);
		Vector3& operator-=(float other);
		Vector3& operator*=(float other);
		Vector3& operator/=(float other);

		bool operator<(const Vector3& other) const;
		bool operator<=(const Vector3& other) const;
		bool operator>(const Vector3& other) const;
		bool operator>=(const Vector3& other) const;

		friend Vector3 operator-(const Vector3& vector);
		
		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);  //For printing vectors
	};

}