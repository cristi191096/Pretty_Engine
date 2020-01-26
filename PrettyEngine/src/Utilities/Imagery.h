#pragma once

#include "Types.h"

#ifdef LoadImage		// Who on Earth named this macro ??
#undef LoadImage
#endif

namespace PrettyEngine {

	byte* LoadImage(const char* filename, int* width = nullptr, int* height = nullptr, int* bits = nullptr, bool flipY = false);
	byte* LoadImage(const String& filename, int* width = nullptr, int* height = nullptr, int* bits = nullptr, bool flipY = false);

	void FreeImageData(byte* pixelData);

}
