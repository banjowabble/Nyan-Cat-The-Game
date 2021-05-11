#ifndef GAME__H_
#define GAME__H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "cat.h"
#include "enemy.h"
//#include "Button.h"

using namespace std;

class Game
{
public:
	const int SCREEN_WIDTH = 960;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* gWindow = NULL;

	SDL_Renderer* gRenderer = NULL;

	TTF_Font* gFont = NULL;

	//main textures
	LTexture gcatTexture;
	LTexture gBGTexture;
	LTexture gcheemsTexture;
	LTexture gEnemyTexture;
	LTexture gMenuTexture;

	//text textures
	LTexture gTextTexture;
	LTexture gIntroTexture;

	//button texutres
	LTexture gPlayTexture;
	LTexture gAltPlayTexture;
	LTexture gExitTexture;
	LTexture gAltExitTexture;

	int scrollingOffset = 0;
	int catframe = 0;

	const int WALKING_ANIMATION_FRAMES = 5;

	SDL_Rect gCatSpriteClips[5];

	Cat* cat = new Cat (gcatTexture, SCREEN_WIDTH, SCREEN_HEIGHT);
	vector<Enemy*> enemies;

	bool init()
	{
		bool success = true;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning: Linear texture filtering not enabled!");
			}

			gWindow = SDL_CreateWindow("Nyan Cat The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}

					if (TTF_Init() == -1)
					{
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}
				}
			}
		}

		generateEnemy();

		return success;
	}

	void clearScreen()
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
	}

	bool loadMedia()
	{
		bool success = true;

		if (!gcatTexture.loadFromFile("resource/nyan cat.png", gRenderer))
		{
			printf("Failed to load cat texture!\n");
			success = false;
		}
		else
		{
			gCatSpriteClips[0].x = 0;
			gCatSpriteClips[0].y = 0;
			gCatSpriteClips[0].w = 52;
			gCatSpriteClips[0].h = 20;

			gCatSpriteClips[1].x = 61;
			gCatSpriteClips[1].y = 0;
			gCatSpriteClips[1].w = 52;
			gCatSpriteClips[1].h = 20;

			gCatSpriteClips[2].x = 121;
			gCatSpriteClips[2].y = 0;
			gCatSpriteClips[2].w = 52;
			gCatSpriteClips[2].h = 20;

			gCatSpriteClips[3].x = 184;
			gCatSpriteClips[3].y = 0;
			gCatSpriteClips[3].w = 52;
			gCatSpriteClips[3].h = 20;

			gCatSpriteClips[4].x = 242;
			gCatSpriteClips[4].y = 0;
			gCatSpriteClips[4].w = 52;
			gCatSpriteClips[4].h = 20;
		}

		if (!gEnemyTexture.loadFromFile("resource/doge loaf pixel.png", gRenderer))
		{
			printf("Failed to load enemy texture!\n");
			success = false;
		}

		if (!gBGTexture.loadFromFile("resource/bgspace2.png", gRenderer))
		{
			printf("Failed to load background texture!\n");
			success = false;
		}

		if (!gcheemsTexture.loadFromFile("resource/cheems pixel.png", gRenderer))
		{
			printf("Failed to load cheems texture!\n");
			success = false;
		}

		if (!gMenuTexture.loadFromFile("resource/nyan cat logo.png", gRenderer))
		{
			printf("Failed to load menu texture!\n");
			success = false;
		}
		if (!gPlayTexture.loadFromFile("resource/play1.png", gRenderer))
		{
			printf("Failed to load play texture!\n");
			success = false;
		}
		if (!gAltPlayTexture.loadFromFile("resource/play2.png", gRenderer))
		{
			printf("Failed to load play texture!\n");
			success = false;
		}

		if (!gExitTexture.loadFromFile("resource/quit1.png", gRenderer))
		{
			printf("Failed to load exit texture!\n");
			success = false;
		}
		if (!gAltExitTexture.loadFromFile("resource/quit2.png", gRenderer))
		{
			printf("Failed to load exit texture!\n");
			success = false;
		}

		gFont = TTF_OpenFont("resource/ARCADECLASSIC.ttf", 28);
		if (gFont == NULL)
		{
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
		else
		{
			//Render text
			SDL_Color white = { 255, 255, 255 }, red = { 255, 0, 0 }, green = { 0, 255, 0 }, blue = { 0, 0, 255 };
			if (!gTextTexture.loadFromRenderedText("Game  over", white, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			if (!gIntroTexture.loadFromRenderedText("The  adventure  of  Nyan  Cat", white, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			/*if (!gPlayTexture.loadFromRenderedText("PLAY", white, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			if (!gAltPlayTexture.loadFromRenderedText("PLAY", blue, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			if (!gExitTexture.loadFromRenderedText("EXIT", white, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			if (!gAltExitTexture.loadFromRenderedText("EXIT", red, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}*/
		}

		return success;
	}

	void renderScrollingBG()
	{
		--scrollingOffset;
		if (scrollingOffset < -gBGTexture.getWidth())
		{
			scrollingOffset = 0;
		}

		gBGTexture.render(scrollingOffset, 0, gRenderer);
		gBGTexture.render(scrollingOffset + gBGTexture.getWidth(), 0, gRenderer);
	}

	void generateEnemy()
	{
			Enemy* en1 = new Enemy(gEnemyTexture, rand() % (SCREEN_WIDTH / 2 + 1), rand() % (SCREEN_HEIGHT / 2 + 1));
			enemies.push_back(en1);
			Enemy* en2 = new Enemy(gEnemyTexture, rand() % (SCREEN_WIDTH - SCREEN_WIDTH / 2 + 1) + SCREEN_WIDTH / 2, rand() % (SCREEN_HEIGHT + 1));
			enemies.push_back(en2);
			Enemy* en3 = new Enemy(gEnemyTexture, rand() % (SCREEN_WIDTH - SCREEN_WIDTH / 2 + 1) + SCREEN_WIDTH / 2, rand() % (SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 1) + SCREEN_HEIGHT / 2);
			enemies.push_back(en3);
			Enemy* en4 = new Enemy(gEnemyTexture, rand() % (SCREEN_WIDTH / 2 + 1), rand() % (SCREEN_HEIGHT - SCREEN_HEIGHT / 2 + 1) + SCREEN_HEIGHT / 2);
			enemies.push_back(en4);	
			/*Enemy* en1 = new Enemy(gEnemyTexture, 0, 0);
			enemies.push_back(en1);*/
	}

	void move()
	{
		cat->move(SCREEN_WIDTH, SCREEN_HEIGHT);
		for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); )
		{
			Enemy* enemy = *it;
			enemy->move(SCREEN_WIDTH, SCREEN_HEIGHT);

			if (enemy->touchCheems(SCREEN_WIDTH, SCREEN_HEIGHT) || enemy -> touchCat(cat->mCollider))
			{
				it = enemies.erase(it);
				delete enemy;
			}
			else ++it;
		}
	}

	bool gameover()
	{
		return enemies.empty();
	}

	void render()
	{
		clearScreen();
		
		renderScrollingBG();

		gcheemsTexture.render(SCREEN_WIDTH / 2 - gcheemsTexture.getWidth() / 2, SCREEN_HEIGHT / 2 - gcheemsTexture.getHeight() / 2, gRenderer);

		SDL_Rect* currentCatClip = &gCatSpriteClips[catframe / WALKING_ANIMATION_FRAMES];
		cat->render(gcatTexture, gRenderer, currentCatClip, catframe, WALKING_ANIMATION_FRAMES);

		for (Enemy* en : enemies) en->render(gEnemyTexture, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
		/*for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		{
			Enemy* enemy = *it;
			enemy->render(gEnemyTexture, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			cout << "Rendered an enemy";
		}*/

		SDL_RenderPresent(gRenderer);
		catframe++;
		if (catframe / 5 >= WALKING_ANIMATION_FRAMES)
		{
			catframe = 0;
		}
	}

	void renderIntro()
	{
		renderScrollingBG();
		gIntroTexture.render((SCREEN_WIDTH - gIntroTexture.getWidth()) / 2, (SCREEN_HEIGHT - gIntroTexture.getHeight()) / 2, gRenderer, NULL);
		SDL_RenderPresent(gRenderer);
	}

	void renderOver()
	{
		gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTextTexture.getHeight()) / 2, gRenderer, NULL);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(2000);
	}

	void close()
	{

		for (Enemy* en : enemies) { delete en; }
		gcatTexture.free();
		gEnemyTexture.free();
		gcheemsTexture.free();

		gTextTexture.free();
		TTF_CloseFont(gFont);
		gFont = NULL;

		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

};

#endif