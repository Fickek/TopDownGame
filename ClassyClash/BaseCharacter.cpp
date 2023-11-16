#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{


}

void BaseCharacter::undoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCharacterCollision()
{
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		width * scale,
		height * scale
	};
}

void BaseCharacter::tick(float deltaTime)
{
	worldPosLastFrame = worldPos;

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