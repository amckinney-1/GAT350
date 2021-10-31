#include "Plane.h"

bool Plane::Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit)
{
	float denominator = dot(r.direction, normal);

	if (denominator == 0) return false;
	if (abs(denominator) < glm::epsilon<float>()) return false;

	float t = dot(center - r.origin, normal) / denominator;

	if (t < 0) return false;
	if (t >= tMin && t <= tMax)
	{
		hit.t = t;
		hit.point = r.pointAt(t);
		hit.normal = normal;
		hit.material = material.get();

		return true;
	}

	return false;
}
