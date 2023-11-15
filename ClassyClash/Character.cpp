#include "Character.h"
#include "raymath.h"



Character::Character(int winWidth, int winHeight)
{
	width = texture.width / maxFrames;
	height = texture.height;

	screenPos =
	{
		static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width),
		static_cast<float>(winHeight) / 2.0f - scale * (0.5f * height)
	};

}

void Character::tick(float deltaTime)
{

	worldPosLastFrame = worldPos;

	Vector2 direction{};
	if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
	if (IsKeyDown(KEY_D)) direction.x += 1.0f;
	if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
	if (IsKeyDown(KEY_S)) direction.y += 1.0f;

	if (Vector2Length(direction) != 0.0)
	{
		// set worldPos = worldPos + direction
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

		// set direction knight
		direction.x < 0.f ? rightleft = -1.f : rightleft = 1.f;

		// set animation knight
		texture = run;
	}
	else
	{
		// set animation knight
		texture = idle;
	}

	// update animation frame
	runnningTime += deltaTime;
	if (runnningTime >= updateTime)
	{
		runnningTime = 0.f;
		frame++;
		if (frame > maxFrames) frame = 0;
	}

	// draw the character
	Rectangle source{ frame * width, .0f, width * rightleft, height };
	Rectangle dest{ screenPos.x, screenPos.y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

void Character::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle Character::getCharacterCollision()
{
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}
