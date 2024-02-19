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

// Borrowed straight from minwindef.h, didn't want to pull the whole library:
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
