#include "triangle_rasterization.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::TriangleRasterization::TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file) : cg::Projections(width, height, obj_file)
{
}

cg::TriangleRasterization::~TriangleRasterization()
{
}

void cg::TriangleRasterization::DrawScene()
{
	Projections::DrawScene();
}

void cg::TriangleRasterization::DrawTriangle(cg::face face)
{
	float x_min = std::min(std::min(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float x_max = std::max(std::max(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_min = std::min(std::min(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);
	float y_max = std::max(std::max(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);

	bool ccw = false;
	float direction = ccw ? -1.f : 1.f;
	float area = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), face.vertexes[2].xy());

	for (float x = x_min; x <= x_max; x+=1.0f) {
		for (float y = y_min; y <= y_max; y+=1.0f) {
			float2 point{ x, y };
			
			float e0 = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), point);
			float e1 = direction * EdgeFunction(face.vertexes[1].xy(), face.vertexes[2].xy(), point);
			float e2 = direction * EdgeFunction(face.vertexes[2].xy(), face.vertexes[0].xy(), point);

			if (e0 >= 0 && e1 >= 0 && e2 >= 0) {
				float3 bary{ e0 / area, e1 / area, e2 / area };
				SetPixel(round(x), round(y), PixelShader(point, bary, face.primitive_id));
			}

		}
	}

	Projections::DrawTriangle(face);

}

cg::color cg::TriangleRasterization::PixelShader(float2 coords, float3 bary, float depth)
{
	//float3 inter_color = bary * 255;
	float cc = 512 - depth * 255;
	return color(round(cc), round(cc), round(cc));
	//return color(round(inter_color.x), round(inter_color.y), round(inter_color.z));

}

float cg::TriangleRasterization::EdgeFunction(float2 a, float2 b, float2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}


