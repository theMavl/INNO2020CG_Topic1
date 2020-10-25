#include "depth_buffer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::ZCulling::ZCulling(unsigned short width, unsigned short height, std::string obj_file) : TriangleRasterization(width, height, obj_file)
{
	depth_buffer.reserve(static_cast<size_t>(width * height));
}

cg::ZCulling::~ZCulling()
{
	ClearRenderTarget::~ClearRenderTarget();
	depth_buffer.clear();
}

void cg::ZCulling::DrawScene()
{
   // throw std::runtime_error("Not implemented yet");
	TriangleRasterization::DrawScene();
}

void cg::ZCulling::Clear()
{
	ClearRenderTarget::Clear();
	depth_buffer.clear();
	depth_buffer.resize(static_cast<size_t>(width * height), 1.0f);
}

void cg::ZCulling::DrawTriangle(face face)
{
	float x_min = std::min(std::min(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float x_max = std::max(std::max(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_min = std::min(std::min(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);
	float y_max = std::max(std::max(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);

	bool ccw = false;
	float direction = ccw ? -1.f : 1.f;
	float area = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), face.vertexes[2].xy());

	for (float x = x_min; x <= x_max; x += 1.0f) {
		for (float y = y_min; y <= y_max; y += 1.0f) {
			float2 point{ x, y };

			float e0 = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), point);
			float e1 = direction * EdgeFunction(face.vertexes[1].xy(), face.vertexes[2].xy(), point);
			float e2 = direction * EdgeFunction(face.vertexes[2].xy(), face.vertexes[0].xy(), point);

			if (e0 >= 0 && e1 >= 0 && e2 >= 0) {
				float3 bary{ e1 / area, e2 / area, e0 / area };
				float z = 1.0f - (bary.x * face.vertexes[0].z + bary.y * face.vertexes[1].z + bary.z * face.vertexes[2].z);
				SetPixel(round(x), round(y), PixelShader(point, bary, z), z);
			}

		}
	}

	//Projections::DrawTriangle(face);
}

void cg::ZCulling::SetPixel(unsigned short x, unsigned short y, color color, float z)
{
	if (x < width && y < height && depth_buffer[y * width + x] > z) {
		frame_buffer[y * width + x] = color;
		depth_buffer[y * width + x] = z;
	}
}


