#include "collision.cpp"
#include "cutscenes.cpp"
#include "menu.cpp"

const int LEVEL_WIDTH = 1290;
const int LEVEL_HEIGHT = 960;

bool loadMedia() {
	gTextbox.loadFromFile("resources/objects/textbox.png");
	return 1;
}
