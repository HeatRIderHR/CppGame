#include <iostream>
#include "raylib.h"

int main()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "My Game");
	Vector2 poly = {100, 100};
	float spin = 0;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		spin += 0.1;
		DrawRectangle(50, 50, 100, 100, {255, 0, 0, 255});
		DrawPoly(poly, 8, 30, spin, {0, 255, 0, 255});

		EndDrawing();
	}

	CloseWindow();
	return 0;
	
}