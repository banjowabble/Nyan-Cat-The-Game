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

	bool isInside(int x, int y, SDL_Event& e);


private:

	SDL_Texture* mTexture;


	int mWidth;
	int mHeight;
};

#endif