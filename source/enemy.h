#ifndef enemy__H
#define enemy__H

#include "Ltexture.h"

class Enemy
{
public:

	const int enemy_WIDTH = 71;
	const int enemy_HEIGHT = 50;

	Enemy(LTexture gEnemyTexture, int getX, int getY);

	void move(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT);

	void render(LTexture& gEnemyTexture, SDL_Renderer* gRenderer, const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT);

	bool touchCheems(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

	bool touchCat(SDL_Rect otherRect);

	int mPosX, mPosY;

	int mVelX, mVelY;

	LTexture enemyTexture;

	SDL_Rect mCollider;
};

#endif