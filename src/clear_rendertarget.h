#pragma once

#include <string>
#include <vector>

namespace cg
{

	struct color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;

		color()
		{
			r = 0;
			g = 0;
			b = 0;
		}

		color(unsigned char in_r, unsigned char in_g, unsigned char in_b)
		{
			r = in_r;
			g = in_g;
			b = in_b;
		}
	};


	class ClearRenderTarget
	{
	public:
		ClearRenderTarget(unsigned width, unsigned height);
		virtual ~ClearRenderTarget();

		void Clear();
		void Save(std::string filename) const;

	protected:
		void SetPixel(unsigned x, unsigned y, color color);

		unsigned height;
		unsigned width;

		std::vector<color> frame_buffer;
	};


}

