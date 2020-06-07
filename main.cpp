#include "window.h"

int main(){
	u::Window window("test", 512,512);

	while(!window.closing){
		window.handle();
	}
	return 0;
}
