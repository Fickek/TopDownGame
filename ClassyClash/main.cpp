#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{

	const int windowWidth{ 384 };
	const int windowHeight{ 384 };

	InitWindow(windowWidth, windowHeight, "Top Down");

	// texture map
	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPosition{ 0.0, 0.0 };
	const float mapScale{ 4.f };

	Character knight{ windowWidth, windowHeight };

	Prop props[2]
	{
		Prop {Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
		Prop {Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}
	};

	Enemy goblin
	{
		Vector2{800.f, 300.f}, 
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png")
	};

	Enemy slime
	{
		Vector2{500.f, 700.f},
		LoadTexture("characters/slime_idle_spritesheet.png"),
		LoadTexture("characters/slime_run_spritesheet.png")
	};

	Enemy* enemies[]
	{
		&goblin,
		&slime
	};

	for(auto enemy : enemies) 
	{
		enemy->setTarget(&knight);
	}

	SetTargetFPS(60);

	while(!WindowShouldClose()) 
	{
		BeginDrawing();
		ClearBackground(WHITE);

		mapPosition = Vector2Scale(knight.getWorldPos(), -1.f);

		// draw the map
		DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);
	
		// draw the props
		for(auto prop : props)
		{
			prop.Render(knight.getWorldPos());
		}

		if(!knight.getAlive()) // character is not alive
		{
			DrawText("GAME OVER", 55.f, 45.f, 40, RED);
			EndDrawing();
			continue;
		}
		else // character is alive
		{
			std::string knightHealth{ "Health: " };
			knightHealth.append(std::to_string(knight.getHealth()), 0, 5);

			DrawText(knightHealth.c_str(), 55.f, 45.f, 40, RED);
		}

		knight.tick(GetFrameTime());

		for(auto enemy : enemies) 
		{
			enemy->tick(GetFrameTime());
		}

		// check map bounds
		if(knight.getWorldPos().x < 0.f ||
			knight.getWorldPos().y < 0.f ||
			knight.getWorldPos().x + windowWidth > map.width * mapScale ||
			knight.getWorldPos().y + windowHeight > map.height * mapScale
			)
		{
			knight.undoMovement();
		}
		// check prop collisions
		for (auto prop : props)
		{
			if(CheckCollisionRecs(prop.getCollisionRect(knight.getWorldPos()), knight.getCharacterCollision())) 
			{
				knight.undoMovement();
			}
		}

		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{

			for(auto enemy : enemies) 
			{
				if (CheckCollisionRecs(enemy->getCharacterCollision(), knight.getWeaponCollisionRec()))
				{
					enemy->setAlive(false);
				}
			}
	
		}
		
		EndDrawing();
	}

	CloseWindow();

	return 0;
}