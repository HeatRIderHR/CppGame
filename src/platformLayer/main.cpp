#include <iostream>
#include "raylib.h"

#include <imgui.h>
#include <rlImGui.h>

#include <gameMain.h>

int main()
{

	#if PRODUCTION_BUILD == 1
		SetTraceLogCallLevel(LOG_NONE);
	#endif

	// Seting up window raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "My Game");
	SetExitKey(KEY_NULL);
	SetTargetFPS(240);
	
	// ImGui Setup
	rlImGuiSetup(true);
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;
	
	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{
		// Clear window
		BeginDrawing();
		rlImGuiBegin();
		if (!updateGame())
		{
			CloseWindow();
		}

		rlImGuiEnd();
		EndDrawing();
	}

	
	CloseWindow();
	closeGame();

	return 0;
	
}