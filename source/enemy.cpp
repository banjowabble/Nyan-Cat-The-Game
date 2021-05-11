#include "enemy.h"

Enemy::Enemy(LTexture gEnemyTexture, int getX, int getY)
{
    mPosX = getX;
    mPosY = getY;

    mVelX = 1;
    mVelY = 1;

    enemyTexture = gEnemyTexture;

    mCollider.w = enemy_WIDTH;
    mCollider.h = enemy_HEIGHT;
}

void Enemy::move(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{

    if (mPosX + enemy_WIDTH < SCREEN_WIDTH/2)
    {
        mPosX += mVelX;
		mCollider.x = mPosX;
    }
    else if (mPosX + enemy_WIDTH > SCREEN_WIDTH / 2)
    {
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    if (mPosY + enemy_HEIGHT < SCREEN_HEIGHT/2)
    {
        mPosY += mVelY;
		mCollider.y = mPosY;
    }
    else if (mPosY + enemy_HEIGHT > SCREEN_HEIGHT / 2)
    {
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
}

void Enemy::render(LTexture& gEnemyTexture, SDL_Renderer* gRenderer, const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{
    gEnemyTexture.render(mPosX, mPosY, gRenderer);
}

bool Enemy::touchCheems(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if (mPosX + enemy_WIDTH == SCREEN_WIDTH / 2 && mPosY + enemy_HEIGHT == SCREEN_HEIGHT / 2)
    {
        return true;
    }
    else return false;
}

bool Enemy::touchCat(SDL_Rect otherRect)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = mCollider.x;
	rightA = mCollider.x + mCollider.w;
	topA = mCollider.y;
	bottomA = mCollider.y + mCollider.h;

	//Calculate the sides of rect B
	leftB = otherRect.x;
	rightB = otherRect.x + otherRect.w;
	topB = otherRect.y;
	bottomB = otherRect.y + otherRect.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}