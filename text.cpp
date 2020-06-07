#include "text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace u{
	unsigned int Font::instanceCount=0;
	Font::Font(const char* path, int size){
		if(instanceCount==0){
			TTF_Init();
		}
		font= TTF_OpenFont(path, size);
		instanceCount++;
	}
	Font::~Font(){
		TTF_CloseFont(font);
		instanceCount--;
		if(instanceCount==0){
			TTF_Quit();
		}
	}

	Text::Text(const char* text, unsigned char r, unsigned char g, unsigned char b, Font* font){
		surface= TTF_RenderText_Solid(font->font, text, {r,g,b,255});
	}
	Text::~Text(){
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
	void Text::draw(SDL_Renderer* renderer, int x, int y){
		if(renderer!=lastRenderer){
			if(lastRenderer){
				SDL_DestroyTexture(texture);
			}
			texture= SDL_CreateTextureFromSurface(renderer, surface);
			SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
			lastRenderer=renderer;
		}
		rect.x= x;
		rect.y= y;
		SDL_RenderCopy(renderer, texture, nullptr, reinterpret_cast<SDL_Rect*>(&rect));
	}
}
