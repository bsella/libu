#pragma once
#include "widget.h"

class SDL_Window;

namespace u{
	class Window: public Widget{

		//virtual void onResize();
		virtual void onClose();
		static unsigned int instanceCount;

	public:
		Window(const char*, unsigned int w, unsigned int h);
		virtual ~Window()override;

		bool closing=false;
		void handle();
		void present()const;

	protected:
		SDL_Window* window=nullptr;

	};
}
