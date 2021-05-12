#include "cat.h"

Cat::Cat(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{
    mPosX = rand() % ((SCREEN_WIDTH - cat_WIDTH) + 1);
    mPosY = rand() % ((SCREEN_HEIGHT - cat_HEIGHT) + 1);

    mVelX = 0;
    mVelY = 0;

    mCollider.w = cat_WIDTH;
    mCollider.h = cat_HEIGHT;
}

void Cat::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: mVelY -= cat_VEL; break;
        case SDLK_DOWN: mVelY += cat_VEL; break;
        case SDLK_LEFT: mVelX -= cat_VEL; break;
        case SDLK_RIGHT: mVelX += cat_VEL; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP: mVelY += cat_VEL; break;
        case SDLK_DOWN: mVelY -= cat_VEL; break;
        case SDLK_LEFT: mVelX += cat_VEL; break;
        case SDLK_RIGHT: mVelX -= cat_VEL; break;
        }
    }
}

void Cat::move(const int& SCREEN_WIDTH, const int& SCREEN_HEIGHT)
{
    mPosX += mVelX;
    mCollider.x = mPosX;

    if ((mPosX < 0) || (mPosX + cat_WIDTH > SCREEN_WIDTH))
    {
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    mPosY += mVelY;
    mCollider.y = mPosY;

    if ((mPosY < 0) || (mPosY + cat_HEIGHT > SCREEN_HEIGHT))
    {
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Cat::render(LTexture& gcatTexture, SDL_Renderer* gRenderer, SDL_Rect* currentClip, int& frame, const int& WALKING_ANIMATION_FRAMES)
{

    gcatTexture.render(mPosX, mPosY, gRenderer, currentClip);
}