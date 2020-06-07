#pragma once
#include <vector>
class SDL_Surface;
class SDL_Renderer;

namespace u{
	class Widget{
	public:
		Widget(unsigned int w, unsigned int h, int x=0, int y=0);
		virtual ~Widget();
	
		void addWidget(Widget*, int, int);
		void invalidate();

		void setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)const;
		void clear()const;
		void line(int x1, int y1, int x2, int y2)const;
		void rect(int x, int y, int w, int h)const;
		void frect(int x, int y, int w, int h)const;
		void dot(int x, int y)const;

	protected:
		struct{
			int x; int y;
			int w; int h;
		} _rect;
		SDL_Renderer* _renderer;
		static unsigned int mouseMask;
		bool valid=false;
		virtual void draw()const;
		void redraw();

		virtual void onMouseEnter(int x, int y);
		virtual void onMouseLeave();
		virtual void onMouseMove(int x, int y);
		virtual void onMouseDown(int x, int y, int button);
		virtual void onMouseUp(int x, int y, int button);

	private:
		bool cursorInside;
		Widget* parent=nullptr;
		std::vector<Widget*> widgets;
		bool inside(int, int)const;
		void updateRenderer();
	};
}
