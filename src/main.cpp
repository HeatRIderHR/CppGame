#include <iostream>
#include "raylib.h"

#include <imgui.h>
#include <rlImGui.h>


int main()
{
	// Seting up window raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "My Game");
	
	// ImGui Setup
	rlImGuiSetup(true);
	ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

	// Variable for shape position
	const Vector2 poly = {100, 100};
	
	while (!WindowShouldClose())
	{
		// Clear window
		BeginDrawing();
		ClearBackground(BLACK);

		rlImGuiBegin();

		// Docking things
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
		
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
		static bool box[1] = {true};
		ImGui::Checkbox("CheckBox", &box[0]);
		static int radio[1] = {false};
		ImGui::RadioButton("RadioButton", &radio[0]);
		static int intput = 1;
		ImGui::InputInt("Intput", &intput, 1, 100);
		static float dragFloat[3] = { 10, 50, 40};
		ImGui::DragFloat3("DragFloat", dragFloat, 1.0, 1.0, 50.0);
		if (ImGui::CollapsingHeader("Colors"))
		{
			static float colorEdit[3] = { 0 , 0, 0};
			ImGui::ColorEdit3("ColorEdit", colorEdit);
			static float colorPick[4] = { 0, 0, 0, 0 };
			ImGui::ColorPicker4("ColorPick", colorPick);
		}
		ImGui::TreeNode("Tree");
		
		static float progBar = 0.5;
		ImGui::ProgressBar(progBar);
		ImGui::End();

		ImGui::Begin("Futher Tests");
		ImGui::Text("Speed");
		ImGui::SameLine();
		ImGui::TextDisabled("(?)");
		
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Controls how fast the player moves.");
			ImGui::EndTooltip();
		}
		    static char buffer[128] = "";
     
  		ImGuiInputTextFlags flags =
        ImGuiInputTextFlags_CharsNoBlank |        // no spaces
        ImGuiInputTextFlags_EnterReturnsTrue |    // return true on Enter
        ImGuiInputTextFlags_AutoSelectAll;        // select all text when focused
     
		if (ImGui::InputText("Player Name", buffer, sizeof(buffer), flags))
		{
			std::cout << "Confirmed name: " << buffer << "\n";
		}
		ImGui::End();
		// Drawing shapes 
		DrawRectangle(50, 50, 100, 100, {255, 0, 0, 255});
		DrawPoly(poly, 8, 30, spin, {0, 255, 0, 255});

		// End drawing
		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
	CloseWindow();
	return 0;
	
}