#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture) : 
	worldPos(pos), 
	texture(idle_texture),
	idle(idle_texture),
	run(run_texture)
{
	width = texture.width / maxFrames;
	height = texture.height;
}

void Enemy::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;

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

void Enemy::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle Enemy::getCharacterCollision()
{
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}
