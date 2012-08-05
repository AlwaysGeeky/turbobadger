// ================================================================================
// == This file is a part of TinkerBell UI Toolkit. (C) 2011-2012, Emil Seger�s  ==
// ==                   See tinkerbell.h for more information.                   ==
// ================================================================================

#include "tinkerbell/src/tb_bitmap_fragment.h"

namespace tinkerbell {

// Remove image formats we don't use to limit binary size.
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_HDR
#define STBI_NO_JPG
#define STBI_NO_BMP
#define STBI_NO_GIF
#define STBI_NO_PSD
#define STBI_NO_PIC
#define STBI_NO_TGA

// Include stb image - Tiny portable and reasonable fast image loader from http://nothings.org/
// Should not be used for content not distributed with your app (May not be secure and doesn't
// support all formats fully)
#include "stb_image.c"

class STBI_Loader : public TBImageLoader
{
public:
	int width, height;
	unsigned char *data;

	STBI_Loader() : width(0), height(0), data(nullptr) {}
	~STBI_Loader() { stbi_image_free(data); }

	virtual int Width() { return width; }
	virtual int Height() { return height; }
	virtual uint32 *Data() { return (uint32*)data; }
};

TBImageLoader *TBImageLoader::CreateFromFile(const char *filename)
{
	int w, h, comp;
	if (unsigned char *data = stbi_load(filename, &w, &h, &comp, 4))
	{
		if (STBI_Loader *img = new STBI_Loader())
		{
			img->width = w;
			img->height = h;
			img->data = data;
			return img;
		}
		else
			stbi_image_free(data);
	}
	return nullptr;
}

}; // namespace tinkerbell
