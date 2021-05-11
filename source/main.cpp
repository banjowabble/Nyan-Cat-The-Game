#include <iostream>
#include "Game.h"
#include "Ltexture.h"
#include "cat.h"
#include "utils.h"
#include "enemy.h"
#include "Menu.h"

//int main(int argc, char* args[])
//{
//	if 
//	{
//		printf("Failed to initialize!\n");
//	}
//	else
//	{
//		if (!loadMedia(gRenderer, gcatTexture, gCatSpriteClips, gExplosionSpriteClips, gBGTexture, gcheemsTexture, gEnemyTexture, gExplosionTexture))
//		{
//			printf("Failed to load media!\n");
//		}
//		else
//		{
//			bool quit = false;
//
//			SDL_Event e;
//
//			while (!quit)
//			{
//				while (SDL_PollEvent(&e) != 0)
//				{
//					if (e.type == SDL_QUIT)
//					{
//						quit = true;
//					}
//
//					cat.handleEvent(e);
//				}
//
//				cat.move(SCREEN_WIDTH, SCREEN_HEIGHT);
//				enemy.move(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//				clearScreen();
//
//				renderScrollingBG(scrollingOffset, gBGTexture, gRenderer);
//
//				gcheemsTexture.render(SCREEN_WIDTH/2 - gcheemsTexture.getWidth()/2, SCREEN_HEIGHT/2 - gcheemsTexture.getHeight()/2, gRenderer);
//
//				SDL_Rect* currentCatClip = &gCatSpriteClips[catframe / 5];
//				SDL_Rect* currentExClip = &gExplosionSpriteClips[exframe / 8];
//
//				cat.render(gcatTexture, gRenderer, currentCatClip, catframe, WALKING_ANIMATION_FRAMES);
//				enemy.render(gEnemyTexture, gExplosionTexture, gRenderer, currentExClip, exframe, SCREEN_WIDTH, SCREEN_HEIGHT, EXPLOSION_ANIMATION_FRAMES);
//
//				SDL_RenderPresent(gRenderer);
//				catframe++;
//				exframe++;
//				if (catframe / 5 >= WALKING_ANIMATION_FRAMES)
//				{
//					catframe = 0;
//				}
//
//				if (exframe / 8 >= EXPLOSION_ANIMATION_FRAMES)
//				{
//					exframe = 0;
//				}
//			}
//		}
//	}
//
//	close(gRenderer, gWindow, gcatTexture);
//
//	return 0;
//}

int main(int argc, char* args[])
{
    srand(time(0));
    Game game;
    
    if (!game.init()) cout << "Failed to initialize!\n";
    else
    {
        if (!game.loadMedia()) cout << "Failed to load media!\n";
        else
        {
            Menu menu(game.gPlayTexture, game.gExitTexture, game.gAltPlayTexture, game.gAltExitTexture, game.gMenuTexture);
            bool quit = false;
            bool quitMenu = false;
            int level = 1;
            SDL_Event e;
            while (SDL_GetTicks() <= 2000)game.renderIntro();
            while (!quit)
            { 
                //menu loop
                while (!quitMenu)
                {
                    while (SDL_PollEvent(&e) != 0)
                    {                     
                        if (e.type == SDL_QUIT)
                        {
                            quitMenu = true;
                            quit = true;
                        }
                        menu.handleButtons(e, quitMenu, quit);
                    }
                    game.renderScrollingBG();
                    menu.render(game.gRenderer); 
                }
                if (quit) break;
                //game loop
                /*while (level < 5)
                {*/
                    while (SDL_PollEvent(&e) != 0)
                    {
                        if (e.type == SDL_QUIT || game.gameover())
                        {
                            quit = true;
                        }
                        game.cat->handleEvent(e);
                    }
                    game.move();
                    game.render();
                //}
            }
            if (game.gameover()) game.renderOver();
        }
    }
    game.close();
    return 0;
}