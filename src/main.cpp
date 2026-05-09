#include <iostream>
#include "raylib.h"

#include <imgui.h>
#include <rlImGui.h>


int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "My Game");
	
	rlImGuiSetup(true);
	ImGuiIO &io = ImGui::GetIO();
	io.FontGlobalScale = 2;

	Vector2 poly = {100, 100};
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		rlImGuiBegin();
		ImGui::Begin("test");
		ImGui::Text("Hi");
		if (ImGui::Button("Button"))
		{
			std::cout << "Button" << std::endl;
		}
		if (ImGui::Button("Button2"))
		{
			std::cout << "Button2" << std::endl;
		}
		ImGui::End();

		ImGui::Begin("slide");
		ImGui::Text("hello");
		ImGui::Separator();
		ImGui::NewLine();
		static float spin = 0;
		ImGui::SliderFloat("slider", &spin, 0, 360);
		ImGui::End();
		
		DrawRectangle(50, 50, 100, 100, {255, 0, 0, 255});
		DrawPoly(poly, 8, 30, spin, {0, 255, 0, 255});

		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
	
}