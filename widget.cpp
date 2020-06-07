#include "widget.h"
#include <SDL2/SDL.h>

namespace u{
	Widget::Widget(unsigned int w, unsigned int h, int x, int y){
		_rect.x= x;
		_rect.y= y;
		_rect.w= w;
		_rect.h= h;
	}
	Widget::~Widget(){}

	void Widget::invalidate(){
		valid= false;
		for(auto widget: widgets)
			widget->invalidate();
	}

	void Widget::updateRenderer(){
		if(parent) _renderer= parent->_renderer;
		else _renderer= nullptr;
		for(auto widget: widgets){
			widget->updateRenderer();
		}
	}

	void Widget::addWidget(Widget* child, int x, int y){
		child->parent= this;
		widgets.push_back(child);
		child->_rect.x= _rect.x+x;
		child->_rect.y= _rect.y+y;
		child->updateRenderer();
		invalidate();
	}
	void Widget::setColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)const{
		SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	}
	static struct{
		int x, y;
		int w, h;
	}r;
	void Widget::clear()const{
		SDL_RenderFillRect(_renderer, reinterpret_cast<const SDL_Rect*>(&_rect));
	}
	void Widget::dot(int x, int y)const{
		SDL_RenderDrawPoint(_renderer, x, y);
	}
	void Widget::line(int x1, int y1, int x2, int y2)const{
		SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	}
	void Widget::rect(int x, int y, int w, int h)const{
		r= {x,y,w,h};
		SDL_RenderDrawRect(_renderer, reinterpret_cast<const SDL_Rect*>(&r));
	}
	void Widget::frect(int x, int y, int w, int h)const{
		r= {x,y,w,h};
		SDL_RenderFillRect(_renderer, reinterpret_cast<const SDL_Rect*>(&r));
	}
	void Widget::draw()const{}
	void Widget::redraw(){
		if(valid) return;
		draw();
		for(auto widget : widgets)
			widget->redraw();
		valid= true;
	}
	bool Widget::inside(int x, int y)const{
		return x >= _rect.x && x < _rect.x+_rect.w && y >= _rect.y && y < _rect.y+_rect.h;
	}

	unsigned int Widget::mouseMask= 0;

	void Widget::onMouseEnter(int x, int y){
		cursorInside= true;
		for(auto widget : widgets)
			if(widget->inside(x,y))
				widget->onMouseEnter(x, y);
	}
	void Widget::onMouseLeave(){
		cursorInside= false;
		for(auto widget : widgets)
			if(widget->cursorInside)
				widget->onMouseLeave();
	}
	void Widget::onMouseMove(int x, int y){
		for(auto widget: widgets)
			if(widget->inside(x, y)){
				if(widget->cursorInside)
					widget->onMouseMove(x, y);
				else
					widget->onMouseEnter(x, y);
			}else if(widget->cursorInside)
				widget->onMouseLeave();
	}
	void Widget::onMouseDown(int x, int y, int button){
		mouseMask|= 1 << button;
		for(auto widget: widgets)
			if(widget->cursorInside)
				widget->onMouseDown(x, y, button);
	}
	void Widget::onMouseUp(int x, int y, int button){
		mouseMask&= ~(1 << button);
		for(auto widget: widgets)
			if(widget->cursorInside)
				widget->onMouseUp(x, y, button);
	}
}
