#ifndef SHORTTYPE_H
#define SHORTTYPE_H

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
} vec2_t;
typedef struct {
	int x, y;
} vec2i_t;

typedef struct {
	float x, y, z;
} vec3_t;
typedef struct {
	int x, y, z;
} vec3i_t;


#ifdef SHORTTYPE
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


vec2_t vec2_t_norm(vec2_t v) {
	float h = (v.x > v.y) ? v.x : v.y;
	return (vec2_t) {
		v.x/h,
		v.y/h
	};
}

vec2_t vec2_t_rot(vec2_t v, float a) {
	float sa = sin(a);
	float ca = cos(a);
	return (vec2_t) {
		v.x * ca - v.y * sa,
		v.x * sa + v.y * ca
	};
}

float lerpf(float in, float target, float factor) {
	return in * (1.0f - factor) + (target * factor);
}

// vec3_t vec3_t_norm(vec3_t v) {
	// float h = (v.x > v.y) ? v.x : v.y;
	// if (h < v.z) h = v.z;
	// return (vec3_t) {
		// v.x/h,
		// v.y/h,
		// v.z/h
	// };
// }

// vec2_t vec2_t_rot(vec2_t v, float a) {
	// float sa = sin(a);
	// float ca = cos(a);
	// return (vec2_t) {
		// v.x * ca - v.y * sa,
		// v.x * sin + v.y * ca
	// };
// }
#else
int clampi(int in, int min, int max);
float clampf(float in, float min, float max);
float lerpf(float in, float target, float factor);

vec2_t vec2_t_norm(vec2_t v);
vec2_t vec2_t_rot(vec2_t v, float a);
vec3_t vec3_t_norm(vec3_t v);

#endif

#endif
