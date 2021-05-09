#pragma once
#include "Vector3D.h"

class Texture
{
public:
	virtual Vector3D value(float u, float v, const Vector3D& p) const = 0;
};

class solid_color : public Texture
{
public:
	Vector3D color_value;
public:
	solid_color();
	solid_color(Vector3D c) : color_value(c) {}

	solid_color(float red, float green, float blue) : solid_color(Vector3D(red, green, blue)) {}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		return color_value;
	}
};

class check_texture : public Texture
{
public:
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;

public:
	check_texture() {};

	check_texture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) : even(_even), odd(_odd) {}
	check_texture(Vector3D c1, Vector3D c2) : even(std::make_shared<solid_color>(c1)), odd(std::make_shared<solid_color>(c2)) {}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
		if (sines < 0)
			return odd->value(u, v, p);
		else
			return even->value(u, v, p);
	}
};

