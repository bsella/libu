#pragma once
#include "widget.h"

class SDL_Window;

namespace u{
	class Window: public Widget{
	public:
		Window(const char*, unsigned int w, unsigned int h);
		virtual ~Window()override;

		bool closing=false;
		void handle();
		void present()const;

	protected:
		SDL_Window* window=nullptr;

		bool in;
	private:
		virtual void onClose();
		//virtual void onResize();
		void onMouseEnter(int,int)override;
		void onMouseLeave()override;
		void draw()const override;
	};
}
