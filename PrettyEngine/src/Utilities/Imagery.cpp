#include "pepch.h"
#include "Imagery.h"
#include "Image/stb_image.h"

namespace PrettyEngine {

	
	byte* LoadImage(const char * filename, int* width, int * height, int * bits, bool flipY)
	{
		stbi_set_flip_vertically_on_load(flipY);


		return stbi_load(filename, width, height, bits, 4);
	}



	byte* LoadImage(const String& filename, int * width, int * height, int * bits, bool flipY)
	{
		return LoadImage(filename.c_str(), width, height, bits, flipY);
	}
	void FreeImageData(byte * pixelData)
	{
		stbi_image_free(pixelData);
	}
}