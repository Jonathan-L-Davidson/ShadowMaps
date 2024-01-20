#pragma once
#include "Core.h"

/// IM AT PAGE 35 GO TO PAGE 35 DO NOT CONTINUE THIS UNTIL I COMPLETE CHAPTER 2

#ifndef VECTOR3_H
#define VECTOR3_H

namespace Physics {

	// I do not like this implementation, it's from: https://web.archive.org/web/20100330183043/http://nlindblad.org/2007/04/04/write-your-own-square-root-function
	// TODO: import maths or just make a better sqrt function.
	

	class Vector3
	{
	public:
		real x, y, z; // X Y and Z for the vector.

	private:
		long : 32; // 4 word alignment making it safe for constant buffers and other byte-sensitive code
		// Typical C++ ... - Mike Acton (2008)

	public:
		Vector3() = default;
		Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}

		void Invert() {
			x = -x;
			y = -y;
			z = -z;
		}

		real Magnitude() {
			// this is a square root function merged into the magnitude as I'm having header file problems.
			real val = (x * x + y * y + z * z);
			real root = val / 2; // divide value in half.
			for (int i = 0; i < 10; i++) {
				root = (root + val / root) / 2;
			}
			return root;
		}

		real SquareMagnitude() const {
			return x * x + y * y + z * z;
		}

		void Normalise() {
			real length = Magnitude();
			if (length > 0) {
				(*this) *= ((real)1) / length; // v = v * (1.0f / length)
			}
		}

		/////
		/// Multiplication
		/////

		// Creates a multiplication operator for Vector3
		void operator*=(const real value) {
			x *= value;
			y *= value;
			z *= value;
		}

		// Returns a vector3 with multiplied values.
		Vector3 operator*(const real value) const {
			return Vector3(x * value, y * value, z * value);
		}

		/////
		/// Division
		/////

		Vector3 operator/(const real value) const {
			return Vector3(x / value, y / value, z / value);
		}

		/////
		/// Addition
		/////

		void operator+=(const Vector3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}

		Vector3 operator+(const Vector3& v) const {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		/////
		/// Subtraction
		/////

		void operator-=(const Vector3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		Vector3 operator-(const Vector3& v) const {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}


		/// <summary>
		/// Performs an additional and a multiplication to a vector.
		/// E.G: vec.AddScaledVector(Vector3(10.0f, 5.0f, 5.0f), 3.0f) simply translates to: vec += Vector3(30.0f, 15.0f, 15.0f)
		/// </summary>
		/// <param name="vector">Vector to add</param>
		/// <param name="scale">Scale</param>
		void AddScaledVector(const Vector3& vector, real scale) {
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}
		/////
		/// Products
		/////

		Vector3 ComponentProduct(const Vector3& vector) const {
			return Vector3(x * vector.x, y * vector.y, z * vector.z);
		}

		/// <summary>
		/// Does a component product however applies it to itself.
		/// </summary>
		/// <param name="vector"></param>
		void ComponentProductUpdate(const Vector3& vector) {
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}

		/// <summary>
		/// Gets the Scalar product from a vector. See 2.1.7 (page 31) of Game Physics engine development
		/// </summary>
		/// <param name="vector"></param>
		/// <returns>Scalar product</returns>
		real ScalarProduct(const Vector3& vector) const {
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/// <summary>
		/// See ScalarProduct.
		/// </summary>
		real DotProduct(const Vector3& vector) const {
			return ScalarProduct(vector);
		}

		/// <summary>
		/// Returns a scalar product/dot product.
		/// </summary>
		/// <param name="vector"></param>
		/// <returns></returns>
		real operator*(const Vector3& vector) const {
			return x * vector.x + y * vector.y + z * vector.z;
		}

		/// <summary>
		/// Cross product! Returns a vector3 instead of a dot product, the length gets smaller the closer it is
		/// to being a 90 degree angle.
		/// </summary>
		/// <param name="vector"></param>
		/// <returns></returns>
		Vector3 VectorProduct(const Vector3& vector) const {
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}

		/// <summary>
		/// See VectorProduct
		/// </summary>
		/// <param name="vector"></param>
		/// <returns></returns>
		Vector3 CrossProduct(const Vector3& vector) const {
			return VectorProduct(vector);
		}

		/// <summary>
		/// Performs a Cross product
		/// </summary>
		/// <param name="vector"></param>
		void operator%=(const Vector3& vector) {
			*this = CrossProduct(vector);
		}

		/// <summary>
		/// Returns a cross product
		/// </summary>
		/// <param name="vector"></param>
		/// <returns>Vector3 Cross Product</returns>
		Vector3 operator%(const Vector3& vector) const {
			return Vector3(y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}

	};
}

#endif

