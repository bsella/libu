#include "window.h"
#include <SDL2/SDL.h>

namespace u{
	unsigned int Window::instanceCount=0;
	Window::Window(const char* title, unsigned int w, unsigned int h): Widget(w,h){
		if(instanceCount==0){
			SDL_Init(SDL_INIT_VIDEO);
		}
		if(!window)
			window= SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		_renderer= SDL_CreateRenderer(window, -1, 0);
		instanceCount++;
	}
	Window::~Window(){
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(_renderer);
		instanceCount--;
		if(instanceCount==0){
			SDL_Quit();
		}
	}

	void Window::present()const{
		SDL_RenderPresent(_renderer);
	}
	
	void Window::handle(){
		if(!valid){
			redraw();
			present();
		}
        static SDL_Event event;
		static int x, y;
        while( SDL_PollEvent( &event ) ){
            switch( event.type ){
                case SDL_KEYUP:
                    if( event.key.keysym.sym == SDLK_ESCAPE ){
						onClose();
						return;
					}
                    break;
				case SDL_WINDOWEVENT:
					switch(event.window.event){
						case SDL_WINDOWEVENT_CLOSE:
							onClose();
							return;
						case SDL_WINDOWEVENT_ENTER:
							SDL_GetMouseState(&x,&y);
							onMouseEnter(x, y);
							return;
						case SDL_WINDOWEVENT_LEAVE:
							onMouseLeave();
							return;
					}
					break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x,&y);
					onMouseMove(x, y);
					return;
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&x,&y);
					onMouseDown(x, y, event.button.button);
					return;
				case SDL_MOUSEBUTTONUP:
					SDL_GetMouseState(&x,&y);
					onMouseUp(x, y, event.button.button);
					return;
            }
        }
        SDL_Delay( 1 );
	}

	void Window::onClose(){
		closing=true;
	}
}
