#pragma once

#ifndef H_QUATERNION
#define H_QUATERNION
#include "Core.h"

class Quaternion {
public:
	float r; // real component.
	float i; // first complex component.
	float j; // second complex component.
	float k; // third complex component.

	Quaternion() : r(1), i(0), j(0), k(0) { };
	Quaternion(const float r, const float i, const float j, const float k) : r(r), i(i), j(j), k(k) { };

	void normalise() {
		float d = r * r + i * i + k * k; // squared magnitude of a quaternion

		if (d <= 0) {
			r = 1;
			return;
		}

		d = 1.0f / ()
	}
};

#endif // !H_QUATERNION
