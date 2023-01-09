#include <cstdio>
#include <iostream>

class Textbox {
	public:
		Textbox();
		bool showTextbox;
		bool getTextValue();
		void handleEvent(SDL_Event& e);
		void render(SDL_Rect& camera, std::string string);
		SDL_Rect getBox();
		int getX();
		int getY();
		int getWidth();
		int getHeight();
		bool transition;
		int alphaTicks;
		bool success;
	private:
		SDL_Rect mBox;
};

Textbox textbox;
Textbox battleActionBox;
