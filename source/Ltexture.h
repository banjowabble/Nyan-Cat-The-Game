#ifndef LTEXTURE__H
#define LTEXTURE__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class LTexture
{
public:

	LTexture();


	~LTexture();


	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);


	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer);


	void free();


	void setAlpha(Uint8 alpha);


	void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);


	int getWidth();
	int getHeight();

	bool isInside(int x, int y, SDL_Event& e)
	{
		if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
		{
			int mouseX, mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);

			bool inside = true;
			if (mouseX < x)
			{
				inside = false;
			}
			else if (mouseX > x + mWidth)
			{
				inside = false;
			}
			else if (mouseY < y)
			{
				inside = false;
			}
			else if (mouseY > y + mHeight)
			{
				inside = false;
			}
			return inside;
		}
		return false;
	}


private:

	SDL_Texture* mTexture;


	int mWidth;
	int mHeight;
};

#endif