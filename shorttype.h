#ifndef SHORTTYPES_H
#define SHORTTYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

typedef struct {
	float x, y;
} v2;
typedef struct {
	int x, y;
} v2i;

typedef struct {
	float x, y, z;
} v3;
typedef struct {
	int x, y, z;
} v3i;


#ifdef SHORTTYPES
int clampi(int in, int min, int max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}
float clampf(float in, float min, float max) {
	if (in > max) return max;
	if (in < min) return min;
	return in;
}


v2 v2_norm(v2 v) {
	float h = (v.x > v.y) ? v.x : v.y;
	return (v2) {
		v.x/h,
		v.y/h
	};
}

v2 v2_rot(v2 v, float a) {
	float sa = sin(a);
	float ca = cos(a);
	return (v2) {
		v.x * ca - v.y * sa,
		v.x * sa + v.y * ca
	};
}

v3 v3_norm(v3 v) {
	float h = (v.x > v.y) ? v.x : v.y;
	if (h < v.z) h = v.z;
	return (v3) {
		v.x/h,
		v.y/h,
		v.z/h
	};
}

// v2 v2_rot(v2 v, float a) {
	// float sa = sin(a);
	// float ca = cos(a);
	// return (v2) {
		// v.x * ca - v.y * sa,
		// v.x * sin + v.y * ca
	// };
// }
#else
int clampi(int in, int min, int max);
float clampf(float in, float min, float max);

v2 v2_norm(v2 v);
v2 v2_rot(v2 v, float a);
v3 v3_norm(v3 v);

#endif

#endif
