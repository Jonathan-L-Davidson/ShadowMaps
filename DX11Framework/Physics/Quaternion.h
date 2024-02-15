#ifndef H_QUATERNION
#define H_QUATERNION

#include "DirectXMath.h"
#include "Core.h"
#include "Vector3.h"

namespace Physics {

	class Quaternion {
	public:
		real r; // real component.
		real i; // first complex component.
		real j; // second complex component.
		real k; // third complex component.

		Quaternion() : r(1), i(0), j(0), k(0) { };
		Quaternion(const real r, const real i, const real j, const real k) : r(r), i(i), j(j), k(k) { };
		Quaternion(const DirectX::XMFLOAT4 xmFloat) : r(xmFloat.w), i(xmFloat.x), j(xmFloat.y), k(xmFloat.z) { };
		Quaternion(const Vector3 vec3) : r(1), i(vec3.x), j(vec3.y), k(vec3.z) { };

		void normalise() {
			real d = r * r + i * i + k * k; // squared magnitude of a quaternion

			if (d <= 0) {
				r = 1;
				return;
			}

			// Casts the value into the appropriate datatype it needs to be, e.g: Double or float
			d = static_cast<real>(1.0) / (real)sqrt(d);
			r *= d;
			i *= d;
			j *= d;
			k *= d;
		};

		void operator *=(const Quaternion& multiplier) {
			Quaternion q = *this;

			// ...matrix math, yay.
			
			// Following the wikipedia page
			// i = (r * i) + (i * r) + (j * k) - (k * j);
			//  
			// j = (r * j) + (j * r) + (k * i) - (i * k);
			//
			// k = (r * k) + (k * r) + (i * j) - (j * i);
			// 
			// r = (r * r) - (i * i) - (j * j) - (k * k);

			i = (q.r * multiplier.i) +  (q.i * multiplier.r) + (q.j * multiplier.k) - (q.k * multiplier.j);
			j = (q.r * multiplier.j) + (q.j * multiplier.r) + (q.k * multiplier.i) - (q.i * multiplier.k);
			k = (q.r * multiplier.k) + (q.k * multiplier.r) + (q.i * multiplier.j) - (q.j * multiplier.i);
			r = (q.r * multiplier.r) - (q.i * multiplier.i) - (q.j * multiplier.j) - (q.k * multiplier.k);

			//i = q.i * multiplier.r + q.j * multiplier.k - q.k * multiplier.j + q.r * multiplier.i;
			//j = -q.i * multiplier.k + q.j * multiplier.r + q.k * multiplier.i + q.r * multiplier.j;
			//k = q.i * multiplier.j - q.j * multiplier.i + q.k * multiplier.r + q.r * multiplier.k;
			//r = -q.i * multiplier.i - q.j * multiplier.j - q.k * multiplier.k + q.r * multiplier.r;

		}

		void operator +=(const Quaternion& add) {
			r += add.r;
			i += add.i;
			j += add.j;
			k += add.k;
		}

		void operator +=(const Vector3& add) {
			i += add.x;
			j += add.y;
			k += add.z;
		}

		Quaternion operator +(const Quaternion& add) {
			return Quaternion(r + add.r, i + add.i, j + add.j, k + add.k);
		}

		Quaternion operator +(const Vector3& add) {
			return Quaternion(r, i + add.x, j + add.y, i + add.z);
		}



		void AddScaledVector(const Vector3& vec, float scale = 1.0f) {
			Quaternion q(0, vec.x * scale, vec.y * scale, vec.z * scale);
			q *= *this;
			r += q.r * static_cast<real>(0.5);
			i += q.i * static_cast<real>(0.5);
			j += q.j * static_cast<real>(0.5);
			k += q.k * static_cast<real>(0.5);
		}

		void rotateByVector(const Vector3& vec) {
			Quaternion q(0, vec.x, vec.y, vec.z);
			(*this) *= q;
		}


	};

	
	// I'm just copying this from our provided sample as this looks insane

/**
* Inline function that creates a transform matrix from a
* position and orientation.
*/
	static inline void CalculateTransformMatrixColumnMajor(DirectX::XMMATRIX& transformMatrix,
		const Vector3& position,
		const Quaternion& orientation)
	{
		transformMatrix.r[0] = DirectX::XMVectorSetX(transformMatrix.r[0], 1 - 2 * orientation.j * orientation.j - 2 * orientation.k * orientation.k);
		transformMatrix.r[0] = DirectX::XMVectorSetY(transformMatrix.r[0], 2 * orientation.i * orientation.j -
			2 * orientation.r * orientation.k);
		transformMatrix.r[0] = DirectX::XMVectorSetZ(transformMatrix.r[0], 2 * orientation.i * orientation.k +
			2 * orientation.r * orientation.j);
		transformMatrix.r[0] = DirectX::XMVectorSetW(transformMatrix.r[0], 0.0f);

		transformMatrix.r[1] = DirectX::XMVectorSetX(transformMatrix.r[1], 2 * orientation.i * orientation.j +
			2 * orientation.r * orientation.k);
		transformMatrix.r[1] = DirectX::XMVectorSetY(transformMatrix.r[1], 1 - 2 * orientation.i * orientation.i -
			2 * orientation.k * orientation.k);
		transformMatrix.r[1] = DirectX::XMVectorSetZ(transformMatrix.r[1], 2 * orientation.j * orientation.k -
			2 * orientation.r * orientation.i);
		transformMatrix.r[1] = DirectX::XMVectorSetW(transformMatrix.r[1], 0.0f);

		transformMatrix.r[2] = DirectX::XMVectorSetX(transformMatrix.r[2], 2 * orientation.i * orientation.k -
			2 * orientation.r * orientation.j);
		transformMatrix.r[2] = DirectX::XMVectorSetY(transformMatrix.r[2], 2 * orientation.j * orientation.k +
			2 * orientation.r * orientation.i);
		transformMatrix.r[2] = DirectX::XMVectorSetZ(transformMatrix.r[2], 1 - 2 * orientation.i * orientation.i -
			2 * orientation.j * orientation.j);
		transformMatrix.r[2] = DirectX::XMVectorSetW(transformMatrix.r[2], 0.0f);

		transformMatrix.r[3] = DirectX::XMVectorSetX(transformMatrix.r[3], position.x);
		transformMatrix.r[3] = DirectX::XMVectorSetY(transformMatrix.r[3], position.y);
		transformMatrix.r[3] = DirectX::XMVectorSetZ(transformMatrix.r[3], position.z);
		transformMatrix.r[3] = DirectX::XMVectorSetW(transformMatrix.r[3], 1.0f);
	}

	static inline void CalculateTransformMatrixRowMajor(DirectX::XMMATRIX& transformMatrix,
		const Vector3& position,
		const Quaternion& orientation)
	{
		transformMatrix.r[0] = DirectX::XMVectorSetX(transformMatrix.r[0], 1 - 2 * orientation.j * orientation.j - 2 * orientation.k * orientation.k);
		transformMatrix.r[0] = DirectX::XMVectorSetY(transformMatrix.r[0], 2 * orientation.i * orientation.j - 2 * orientation.r * orientation.k);
		transformMatrix.r[0] = DirectX::XMVectorSetZ(transformMatrix.r[0], 2 * orientation.i * orientation.k + 2 * orientation.r * orientation.j);
		transformMatrix.r[0] = DirectX::XMVectorSetW(transformMatrix.r[0], 0.0f);

		transformMatrix.r[1] = DirectX::XMVectorSetX(transformMatrix.r[1], 2 * orientation.i * orientation.j + 2 * orientation.r * orientation.k);
		transformMatrix.r[1] = DirectX::XMVectorSetY(transformMatrix.r[1], 1 - 2 * orientation.i * orientation.i - 2 * orientation.k * orientation.k);
		transformMatrix.r[1] = DirectX::XMVectorSetZ(transformMatrix.r[1], 2 * orientation.j * orientation.k - 2 * orientation.r * orientation.i);
		transformMatrix.r[1] = DirectX::XMVectorSetW(transformMatrix.r[1], 0.0f);

		transformMatrix.r[2] = DirectX::XMVectorSetX(transformMatrix.r[2], 2 * orientation.i * orientation.k - 2 * orientation.r * orientation.j);
		transformMatrix.r[2] = DirectX::XMVectorSetY(transformMatrix.r[2], 2 * orientation.j * orientation.k + 2 * orientation.r * orientation.i);
		transformMatrix.r[2] = DirectX::XMVectorSetZ(transformMatrix.r[2], 1 - 2 * orientation.i * orientation.i - 2 * orientation.j * orientation.j);
		transformMatrix.r[2] = DirectX::XMVectorSetW(transformMatrix.r[2], 0.0f);

		transformMatrix.r[3] = DirectX::XMVectorSetX(transformMatrix.r[3], position.x);
		transformMatrix.r[3] = DirectX::XMVectorSetY(transformMatrix.r[3], position.y);
		transformMatrix.r[3] = DirectX::XMVectorSetZ(transformMatrix.r[3], position.z);
		transformMatrix.r[3] = DirectX::XMVectorSetW(transformMatrix.r[3], 1.0f);

		transformMatrix = XMMatrixTranspose(transformMatrix);
	}
}

#endif// !H_QUATERNION
