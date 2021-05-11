#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


image_texture::image_texture(const char* filename)
{
	auto components_per_pixel = bytes_per_pixel;

	data = stbi_load(filename, &width, &height, &components_per_pixel, components_per_pixel);

	if (!data)
	{
		std::cerr << "Error: could not load texture texture image file " << filename << ".\n";
		width = height = 0;
	}

	bytes_per_scanline = bytes_per_pixel * width;
}