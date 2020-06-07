#pragma once

#include <SDL2/SDL_ttf.h>

class SDL_Surface;
class SDL_Texture;
class SDL_Renderer;

namespace u{
	class Font{
		TTF_Font* font;
		static unsigned int instanceCount;
	public:
		Font(const char* path, int size);
		~Font();

		friend class Text;
	};

	class Text{
		SDL_Surface* surface;
		SDL_Texture* texture=nullptr;
		struct{
			int x; int y;
			int w; int h;
		} rect;
		SDL_Renderer* lastRenderer= nullptr;
	public:
		Text(const char* text, unsigned char r, unsigned char g, unsigned char b, Font* font);
		~Text();

		void draw(SDL_Renderer*, int x, int y);
	};
}
