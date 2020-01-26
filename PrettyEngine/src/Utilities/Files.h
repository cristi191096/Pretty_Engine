#pragma once
#include "engine\Core\Core.h"

namespace PrettyEngine {

	class PE_API FileSystem {

	public:
		static byte* ReadFile(const String& path);
		static String ReadTextFile(const String& path);

		static bool WriteFile();
		static bool WriteTextFile();
	};
}
