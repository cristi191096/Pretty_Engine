// dear imgui: Platform Binding for Windows (standard windows API for 32 and 64 bits applications)
// This needs to be used along with a Renderer (e.g. DirectX11, OpenGL3, Vulkan..)

// Implemented features:
//  [X] Platform: Clipboard support (for Win32 this is actually part of core imgui)
//  [X] Platform: Mouse cursor shape and visibility. Disable with 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange'.
//  [X] Platform: Keyboard arrays indexed using VK_* Virtual Key Codes, e.g. ImGui::IsKeyPressed(VK_SPACE).
//  [X] Platform: Multi-viewport support (multiple windows). Enable with 'io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable'.
// Missing features:
//  [ ] Platform: Gamepad support (best leaving it to user application to fill io.NavInputs[] with gamepad inputs from their source of choice).

#pragma once

IMGUI_IMPL_API bool     ImGui_ImplWin32_Init(void* hwnd);
IMGUI_IMPL_API void     ImGui_ImplWin32_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplWin32_NewFrame();

// DPI-related helpers (which run and compile without requiring 8.1 or 10, neither Windows version, neither associated SDK)
IMGUI_API void        ImGui_ImplWin32_EnableDpiAwareness();
IMGUI_API float       ImGui_ImplWin32_GetDpiScaleForHwnd(void* hwnd);       // HWND hwnd
IMGUI_API float       ImGui_ImplWin32_GetDpiScaleForMonitor(void* monitor); // HMONITOR monitor
IMGUI_API float       ImGui_ImplWin32_GetDpiScaleForRect(int x1, int y1, int x2, int y2);

// Handler for Win32 messages, update mouse/keyboard data.
// You may or not need this for your implementation, but it can serve as reference for handling inputs.
// Intentionally commented out to avoid dragging dependencies on <windows.h> types. You can COPY this line into your .cpp code instead.
/*
IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
*/
