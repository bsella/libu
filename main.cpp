#include "window.h"
#include "text.h"

u::Font f("../Lato-Regular.ttf", 20);

class TestWindow : public u::Window{
	bool in;
	void draw()override{
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
		text(&t, 12, 34);
	}
	void onMouseEnter(int,int)override{
		in=true;
		invalidate();
	}
	void onMouseLeave()override{
		in=false;
		invalidate();
	}
	u::Text t;
public:
	TestWindow():u::Window("test", 512,512), t("test", 255,255,0, &f){}
};

int main(){
	TestWindow window;

	while(!window.closing){
		window.handle();
	}
	return 0;
}
