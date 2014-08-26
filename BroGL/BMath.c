#include "BShared.h"

vec3	vec3_origin = { 0, 0, 0 };
vec3	axisDefault[3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };

//************************************
// Method:    AnglesToAxis
// FullName:  AnglesToAxis
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const vec3 angles
// Parameter: vec3 axis[3]
// Description: AnglesToAxis implementation from Quake-III-Engine source code.
//************************************
void AnglesToAxis(const vec3 angles, vec3 axis[3]) {
	vec3	right;

	// angle vectors returns "right" instead of "y axis"
	AngleVectors(angles, axis[0], right, axis[2]);
	VectorSubtract(vec3_origin, right, axis[1]);
}

//************************************
// Method:    AngleVectors
// FullName:  AngleVectors
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const vec3 angles
// Parameter: vec3 forward
// Parameter: vec3 right
// Parameter: vec3 up
// Description: AngleVectors implementation from Quake-III-Engine source code.
//************************************
void AngleVectors(const vec3 angles, vec3 forward, vec3 right, vec3 up) {
	float		angle;
	static float		sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward) {
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right) {
		right[0] = (-1 * sr*sp*cy + -1 * cr*-sy);
		right[1] = (-1 * sr*sp*sy + -1 * cr*cy);
		right[2] = -1 * sr*cp;
	}
	if (up) {
		up[0] = (cr*sp*cy + -sr*-sy);
		up[1] = (cr*sp*sy + -sr*cy);
		up[2] = cr*cp;
	}
}
