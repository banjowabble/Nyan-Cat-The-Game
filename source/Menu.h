#ifndef MENU_H_
#define MENU_H_
#include "Ltexture.h"
#include "Game.h"

class Menu
{
public:

	LTexture PlayButton;
	LTexture altPlayButton;
	LTexture ExitButton;
	LTexture altExitButton;
	LTexture menuTexture;

	bool hoverPlay = false;
	bool hoverExit = false;

	int x1 = 580, y1 = 100;
	int x2 = 580, y2 = 300;

	const int width = 222;
	const int height = 108;

	Menu(LTexture& gPlayTexture, LTexture& gExitTexture, LTexture& gAltPlayButton, LTexture& gAltExitButton, LTexture& gMenuTexture)
	{
		PlayButton = gPlayTexture;
		altPlayButton = gAltPlayButton;
		ExitButton = gExitTexture;
		altExitButton = gAltExitButton;
		menuTexture = gMenuTexture;
	}

	void handlePlayButton(Mix_Chunk* gClick, SDL_Event& e, bool& quitMenu, bool& quit)
	{
		if (PlayButton.isInside(x1, y1, e)) 
		{
			hoverPlay = true;
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, gClick, 0);
				quitMenu = true;
			}
		}
		else hoverPlay = false;
	}

	void handleExitButton(Mix_Chunk *gClick, SDL_Event& e, bool& quitMenu, bool& quit)
	{
		if (ExitButton.isInside(x2, y2, e))
		{
			hoverExit = true;
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Mix_PlayChannel(-1, gClick, 0);
				quitMenu = true;
				quit = true;
			}
		}
		else hoverExit = false;
	}

	void handleButtons(Mix_Chunk* gClick, SDL_Event& e, bool& quitMenu, bool& quit)
	{
		handlePlayButton(gClick, e, quitMenu, quit);
		handleExitButton(gClick, e, quitMenu, quit);
	}

	void render(SDL_Renderer* gRenderer)
	{
		menuTexture.render(0, 150, gRenderer, NULL);

		if (hoverPlay == false) PlayButton.render(x1, y1, gRenderer, NULL);
		else altPlayButton.render(x1, y1, gRenderer, NULL);
		if (hoverExit == false) ExitButton.render(x2, y2, gRenderer, NULL);
		else altExitButton.render(x2, y2, gRenderer, NULL);
		SDL_RenderPresent(gRenderer);
	}
};
#endif

