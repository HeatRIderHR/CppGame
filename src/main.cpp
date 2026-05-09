#include <iostream>
#include "raylib.h"

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "My Game");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello World", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();
	return 0;
	
}