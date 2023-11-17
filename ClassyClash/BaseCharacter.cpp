#include "BaseCharacter.h"
#include "raymath.h"

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
		getScreenPos().x,
		getScreenPos().y,
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

	if (Vector2Length(velocity) != 0.0)
	{
		// set worldPos = worldPos + velocity
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));

		// set velocity knight
		velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;

		// set animation knight
		texture = run;
	}
	else
	{
		// set animation knight
		texture = idle;
	}

	velocity = {};

	// draw the character
	Rectangle source{ frame * width, .0f, width * rightLeft, height };
	Rectangle dest{ getScreenPos().x, getScreenPos().y, scale * width, scale * height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);

}