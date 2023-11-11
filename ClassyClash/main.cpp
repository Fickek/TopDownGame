#include "raylib.h"

int main() 
{
	const int windowWidth{ 384 };
	const int windowHeight{ 384 };

	InitWindow(windowWidth, windowHeight, "Top Down");

	Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");
	

	SetTargetFPS(60);

	while(!WindowShouldClose()) 
	{
		
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 mapPosition{ 0, 0 };
		DrawTextureEx(worldMap, mapPosition, 0.0, 4.0, WHITE);

		EndDrawing();
	}

	CloseWindow();

}