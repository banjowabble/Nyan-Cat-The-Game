#ifndef GAME__H_
#define GAME__H_

#include <iostream>>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "cat.h"
#include "enemy.h"


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
	LTexture gGameOverTexture;
	LTexture gIntroTexture;
	LTexture gTutorial1Texture;
	LTexture gTutorial2Texture;
	LTexture gTutorial3Texture;
	LTexture gTutorial4Texture;
	LTexture gScoreTexture;
	LTexture gShowScoreTexture;
	LTexture gLivesTexture;
	LTexture gShowLivesTexture;

	//button texutres
	LTexture gPlayTexture;
	LTexture gAltPlayTexture;
	LTexture gExitTexture;
	LTexture gAltExitTexture;

	//bg music
	Mix_Music* gMusic = NULL;
	Mix_Music* gLose = NULL;
	Mix_Chunk* gClick = NULL;
	Mix_Chunk* gEat = NULL;

	unsigned int lastTime = 0, currentTime;
	unsigned int rate = 1, realRate = 1, lives = 3, score = 0;

	int scrollingOffset = 0;
	int catframe = 0;

	const int WALKING_ANIMATION_FRAMES = 5;

	SDL_Rect gCatSpriteClips[5];

	Cat* cat = new Cat (SCREEN_WIDTH, SCREEN_HEIGHT);
	vector<Enemy*> enemies;

	bool init()
	{
		bool success = true;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

					if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
					{
						printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
						success = false;
					}
				}
			}
		}

		//generateEnemy();

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
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
		else
		{
			//Render text
			SDL_Color white = { 255, 255, 255 }, red = { 255, 0, 0 }, green = { 0, 255, 0 }, blue = { 0, 0, 255 };
			if (!gGameOverTexture.loadFromRenderedText("Game  over", white, gFont, gRenderer))
			{
				printf("Failed to render text texture!\n");
				success = false;
			}
			if (!gIntroTexture.loadFromRenderedText("The  adventure  of  Nyan  Cat", white, gFont, gRenderer))
			{
				printf("Failed to render intro texture!\n");
				success = false;
			}
			if (!gTutorial1Texture.loadFromRenderedText("In  this  game  you  control  Nyan  Cat  using  the  arrow  keys", white, gFont, gRenderer))
			{
				printf("Failed to render tutorial1 texture!\n");
				success = false;
			}
			if (!gTutorial2Texture.loadFromRenderedText("Collect  the  flying  Doge  loaves  heading  towards Cheems", white, gFont, gRenderer))
			{
				printf("Failed to render tutorial2 texture!\n");
				success = false;
			}
			if (!gTutorial3Texture.loadFromRenderedText("as  much  as  you  can  before  he  consumes  too  many !", white, gFont, gRenderer))
			{
				printf("Failed to render tutorial2 texture!\n");
				success = false;
			}
			if (!gTutorial4Texture.loadFromRenderedText("Press  any  key   to  continue", white, gFont, gRenderer))
			{
				printf("Failed to render tutorial2 texture!\n");
				success = false;
			}
			if (!gShowScoreTexture.loadFromRenderedText("Score ", white, gFont, gRenderer))
			{
				printf("Failed to render show score texture!\n");
				success = false;
			}
			if (!gShowLivesTexture.loadFromRenderedText("Lives ", white, gFont, gRenderer))
			{
				printf("Failed to render show lives texture!\n");
				success = false;
			}

		}

		gMusic = Mix_LoadMUS("resource/original.wav");
		if (gMusic == NULL)
		{
			printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gClick = Mix_LoadWAV("resource/click.wav");
		if (gClick == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gEat = Mix_LoadWAV("resource/eat.wav");
		if (gEat == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		gLose = Mix_LoadMUS("resource/game over.wav");
		if (gMusic == NULL)
		{
			printf("Failed to load game over music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
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
			for (int i = 0; i < 1000; i++)
			{
				Enemy* en1 = new Enemy(-71, rand() % (SCREEN_HEIGHT + 1));
				enemies.push_back(en1);
				Enemy* en2 = new Enemy(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT + 1));
				enemies.push_back(en2);
				Enemy* en3 = new Enemy(rand() % (SCREEN_WIDTH + 1), -50);
				enemies.push_back(en3);
				Enemy* en4 = new Enemy(rand() % (SCREEN_HEIGHT + 1), SCREEN_HEIGHT);
				enemies.push_back(en4);
			}
	}

	void move()
	{
		cat->move(SCREEN_WIDTH, SCREEN_HEIGHT);
		for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.begin() + rate; )
		{
			Enemy* enemy = *it;
			enemy->move(SCREEN_WIDTH, SCREEN_HEIGHT);

			if (enemy->touchCheems(SCREEN_WIDTH, SCREEN_HEIGHT) || enemy->touchCat(cat->mCollider))
			{
				Mix_PlayChannel(-1, gEat, 0);
				if (enemy->touchCheems(SCREEN_WIDTH, SCREEN_HEIGHT)) lives = lives - 1;
				else if (enemy->touchCat(cat->mCollider)) score = score + 1;
				it = enemies.erase(it);
				delete enemy;				
			}
			else ++it;
		}
	}

	void updateScoreAndLives()
	{
		SDL_Color white = { 255, 255, 255 };
		string scoreText = to_string(score);
		string livesText = to_string(lives);
		gScoreTexture.loadFromRenderedText(scoreText, white, gFont, gRenderer);
		gLivesTexture.loadFromRenderedText(livesText, white, gFont, gRenderer);
	}

	void restart(bool& quitMenu)
	{
		if (lives == 0) {
			lives = 3; rate = 1; score = 0;
			for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.begin() + realRate; ++it)
			{
				Enemy* enemy = *it;
				it = enemies.erase(it);
				delete enemy;
			}
			renderOver();
			Mix_PlayMusic(gMusic, -1);
			quitMenu = false;
		}
	}

	void updateSpawnRate()
	{
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 5000) {
			rate++; 
			realRate++;
			lastTime = currentTime;
		}
	}

	void render()
	{
		clearScreen();
		
		renderScrollingBG();

		gcheemsTexture.render(SCREEN_WIDTH / 2 - gcheemsTexture.getWidth() / 2, SCREEN_HEIGHT / 2 - gcheemsTexture.getHeight() / 2, gRenderer);

		gShowScoreTexture.render(830, 0, gRenderer, NULL);
		gScoreTexture.render(920, 0, gRenderer, NULL);

		gShowLivesTexture.render(20, 0, gRenderer, NULL);
		gLivesTexture.render(120, 0, gRenderer, NULL);

		SDL_Rect* currentCatClip = &gCatSpriteClips[catframe / WALKING_ANIMATION_FRAMES];
		cat->render(gcatTexture, gRenderer, currentCatClip, catframe, WALKING_ANIMATION_FRAMES);

		for (Enemy* en : enemies) en->render(gEnemyTexture, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

		SDL_RenderPresent(gRenderer);
		catframe++;
		if (catframe / 5 >= WALKING_ANIMATION_FRAMES)
		{
			catframe = 0;
		}
	}

	void renderIntro()
	{
		while (SDL_GetTicks() <= 2000)
		{
			renderScrollingBG();
			gIntroTexture.render((SCREEN_WIDTH - gIntroTexture.getWidth()) / 2, (SCREEN_HEIGHT - gIntroTexture.getHeight()) / 2, gRenderer, NULL);
			SDL_RenderPresent(gRenderer);
		}
		gIntroTexture.free();
	}

	void renderTutorial(SDL_Event& e, bool& quitTuto)
	{
		renderScrollingBG();
		gTutorial1Texture.render(SCREEN_WIDTH / 2 - gTutorial1Texture.getWidth() / 2, 150, gRenderer, NULL);
		gTutorial2Texture.render(SCREEN_WIDTH / 2 - gTutorial2Texture.getWidth() / 2, 200, gRenderer, NULL);
		gTutorial3Texture.render(SCREEN_WIDTH / 2 - gTutorial3Texture.getWidth() / 2, 250, gRenderer, NULL);
		gTutorial4Texture.render(SCREEN_WIDTH / 2 - gTutorial4Texture.getWidth() / 2, 420, gRenderer, NULL);
		SDL_RenderPresent(gRenderer);
		if (SDL_PollEvent(&e) != 0 &&
			(e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
		{
			quitTuto = true;
		}
	}

	void renderOver()
	{
		Mix_PlayMusic(gLose, 0);
		gGameOverTexture.render((SCREEN_WIDTH - gGameOverTexture.getWidth()) / 2, (SCREEN_HEIGHT - gGameOverTexture.getHeight()) / 2, gRenderer, NULL);
		gShowScoreTexture.render(420, 280, gRenderer, NULL);
		gScoreTexture.render(520, 280, gRenderer, NULL);
		SDL_RenderPresent(gRenderer);
		SDL_Delay(2000);
	}

	void close()
	{
		//free main stuff
		for (Enemy* en : enemies) { delete en; }
		gcatTexture.free();
		gEnemyTexture.free();
		gcheemsTexture.free();
		gBGTexture.free();
		gMenuTexture.free();
		
		//free text stuff
		gGameOverTexture.free();
		gIntroTexture.free();
		gTutorial1Texture.free();
		gTutorial2Texture.free();
		gTutorial3Texture.free();
		gTutorial4Texture.free();
		gScoreTexture.free();
		gShowScoreTexture.free();
		gLivesTexture.free();
		gShowLivesTexture.free();
		TTF_CloseFont(gFont);
		gFont = NULL;

		//free buttons
		gPlayTexture.free();
		gAltPlayTexture.free();
		gExitTexture.free();
		gAltExitTexture.free();

		//free music and sfx stuff
		Mix_FreeMusic(gMusic);
		gMusic = NULL;
		Mix_FreeChunk(gClick);
		Mix_FreeChunk(gEat);
		gClick = NULL;
		gEat = NULL;

		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

};

#endif