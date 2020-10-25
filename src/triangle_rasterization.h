#pragma once


#include "projections.h"

namespace cg
{


	class TriangleRasterization : public Projections
	{
	public:
		TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file);
		virtual ~TriangleRasterization();

		virtual void DrawScene();

	protected:
		void DrawTriangle(face face);
		color PixelShader(float2 coords, float3 bary, float depth);

		float EdgeFunction(float2 a, float2 b, float2 c);
	};

}
