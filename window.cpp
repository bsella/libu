#include "window.h"
#include <SDL2/SDL.h>

namespace u{
	Window::Window(const char* title, unsigned int w, unsigned int h): Widget(w,h){
		SDL_Init(SDL_INIT_VIDEO);
		if(!window)
			window= SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
		_renderer= SDL_CreateRenderer(window, -1, 0);
	}
	//Window::Window():Window("", 640, 400){}
	Window::~Window(){
		SDL_DestroyWindow(window);
	}

	void Window::onMouseEnter(int, int){
		in=true;
		invalidate();
	}
	void Window::onMouseLeave(){
		in=false;
		invalidate();
	}
	void Window::present()const{
		SDL_RenderPresent(_renderer);
	}
	void Window::draw()const{
		if(in)
			setColor(255,0,0,255);
		else
			setColor(0,255,0,255);
		clear();
		setColor(0,0,255,255);
		line(0,_rect.h,_rect.w,0);
		line(0,0,_rect.w,_rect.h);
		setColor(255,255, 0,255);
		dot(100, 200);
	}
	
	void Window::handle(){
		if(!valid){
			redraw();
			present();
		}
        SDL_Event event;
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
