#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>

//=================| Data Structures |============================
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>
//======================================================================

//==================| Engine Includes |=============================
#include "engine\Core\Log.h"
#include "Types.h"
//======================================================================


#ifdef PE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // PE_PLATFORM_WINDOWS
