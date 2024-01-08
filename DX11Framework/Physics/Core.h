#pragma once

#ifdef DIRECTX_MATH_VERSION
#define USING_DIRECTX
#endif

namespace Physics {
#ifdef USE_DOUBLE
	typedef double real;
#else
	typedef float real;
#endif
}
