#ifndef cat__H
#define cat__H

#include "Ltexture.h"
//#include "Game.h";

class Cat
{
public:

	const int cat_WIDTH = 50;
	const int cat_HEIGHT = 20;
	const int cat_VEL = 5;

	LTexture catTexture;

	Cat(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT);

	void handleEvent(SDL_Event& e);

	void move(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT);

	void render(LTexture& gcatTexture, SDL_Renderer* gRenderer, SDL_Rect* currentClip, int& frame, const int& WALKING_ANIMATION_FRAMES);

	int mPosX, mPosY;

	int mVelX, mVelY;

	SDL_Rect mCollider;
};

#endif
