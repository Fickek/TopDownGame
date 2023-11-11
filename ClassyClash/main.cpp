#include "raylib.h"
#include "raymath.h"

int main() 
{
	const int windowWidth{ 384 };
	const int windowHeight{ 384 };

	InitWindow(windowWidth, windowHeight, "Top Down");

	// texture map
	Texture2D worldMap = LoadTexture("nature_tileset/WorldMap.png");

	// texture character
	Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
	Vector2 knightPos
	{
		(float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
		(float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)
	};
	


	Vector2 mapPosition{ 0, 0 };
	float speed = 10.0;

	SetTargetFPS(60);

	while(!WindowShouldClose()) 
	{
		
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 direction{};
		if(IsKeyDown(KEY_A)) direction.x -= 1.0;
		if(IsKeyDown(KEY_D)) direction.x += 1.0;
		if(IsKeyDown(KEY_W)) direction.y -= 1.0;
		if(IsKeyDown(KEY_S)) direction.y += 1.0;

		if(Vector2Length(direction) != 0.0)
		{
			// set mapPos = mapPos - direction
			mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), speed));
	
		}

		// draw the map
		DrawTextureEx(worldMap, mapPosition, 0.0, 4.0, WHITE);

		// draw the character
		Rectangle source{ .0f,.0f, (float)knight.width / 6.f, (float)knight.height };
		Rectangle dest{ knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.f, 4.0f * (float)knight.height };
		DrawTexturePro(knight, source, dest, Vector2{}, .0f, WHITE);


		EndDrawing();
	}

	CloseWindow();

}