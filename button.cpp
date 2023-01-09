#include "button.h"

LTexture gText;
LTexture gArrow;
LTexture gYes;
LTexture gNo;

Button button;

TTF_Font* gFancyFont = TTF_OpenFont("resources/fonts/Basic Roman-BoldItalic.ttf", 40);
TTF_Font* gBigFancyFont = TTF_OpenFont("resources/fonts/Basic Roman-BoldItalic.ttf", 75);

SDL_Rect mouseBox;
SDL_Rect button1;
SDL_Rect button2;

int selectedButton; 
int mouseX, mouseY;
bool activeDialogue;
bool promptSelect = 0;

int charCount = 0;
std::string textWritten = "";
std::string battleTextWritten = "";
bool doNotType = 0;
int textX = 160; 
int textY = 475;
int wrpBnd = 650;
int drawTicks;
void drawDialogueText(std::string s, LTexture* gText) {
	//drawTicks++;
	if(!doNotType) {
		if(charCount < s.size()) {
			if(s[charCount] != '\\') {
				textWritten += s[charCount]; charCount++;
			} else {
				textWritten += "\n           "; charCount++;
			}
		}
			gText->loadFromRenderedText(textWritten, White, wrpBnd, gFont);
			if(!promptSelect)
				gText->render(textX, textY);
			else
				gText->render(textX, textY - 10);	
	} else {
		while(charCount < s.size()) {
			if(s[charCount] != '\\') {
				textWritten += s[charCount]; charCount++;
			} else {
				textWritten += "\n           "; charCount++;
			}
		}
		gText->loadFromRenderedText(textWritten, White, wrpBnd, gFont);
		gText->render(textX, textY);
	}
}

void loadFont(int size) {
	gFont= TTF_OpenFont("resources/fonts/font1.ttf", size);
	gFancyFont = TTF_OpenFont("resources/fonts/Basic Roman-BoldItalic.ttf", 40);
	gBigFancyFont = TTF_OpenFont("resources/fonts/Basic Roman-BoldItalic.ttf", 70);
}

void freeText(LTexture* gText) {
	charCount = 0;
	gText->free();
	textWritten = "";
	battleTextWritten = "";
}

void resetChars() {
	textWritten = "";	
}

void renderButtons() {
	button1.x = textX + 65; button1.y = textY + 12; button1.w = 400; button1.h = 30;
	button2.x = textX + 65; button2.y = textY + 68; button2.w = 400; button2.h = 30;
	mouseBox.x = mouseX; mouseBox.y = mouseY; mouseBox.w = 5; mouseBox.h = 5;
	if(checkCollision(mouseBox, button1)) {
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
		SDL_RenderFillRect(gRenderer, &button1);
		selectedButton = 0;
	} else if (checkCollision(mouseBox, button2)) {
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
		SDL_RenderFillRect(gRenderer, &button2);
		selectedButton = 1;
	}
}


Button::Button() {
	mBox.x = 50;
	mBox.y = 50;
	mBox.w = 30;
	mBox.h = 30;
}

SDL_Rect Button::getBox() {
	return mBox;
}

void Button::handleEvent( SDL_Event& e )
{
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        	switch(e.key.keysym.sym) {
	    		case SDLK_UP: selectedButton = 0;
				      SDL_WarpMouseInWindow(gWindow, button1.x + button1.w - 50, button1.y + 5);
				      break;
	    		case SDLK_DOWN: selectedButton = 1;
					SDL_WarpMouseInWindow(gWindow, button2.x + button2.w - 50, button2.y + 5);
				       	break;
		}
	}

	SDL_GetMouseState(&mouseX, &mouseY);
	//printf("%i/%i\n", mouseX, mouseY);
	
}

void Button::render(std::string text1, std::string text2, SDL_Rect& camera, Textbox* textbox, int selectedDirection) {
	gYes.loadFromRenderedText(text1, White, 0, gFont);
	gYes.render(textbox->getWidth() / 3, 
			textbox->getY() / 2 + textbox->getHeight() + 125);

	gNo.loadFromRenderedText(text2, White, 0, gFont);
	gNo.render(textbox->getWidth() - textbox->getWidth() / 3, 
			textbox->getY() / 2 + textbox->getHeight() + 125);
}

void Textbox::render(SDL_Rect& camera, std::string string) {
	if(transition) {
		alphaTicks += 10;
		gTextbox.setBlendMode(SDL_BLENDMODE_BLEND);
		gTextbox.setAlpha(alphaTicks);
		if(alphaTicks == 200) {
			transition = 0;
			alphaTicks = 0;
		}
	} else {
		gTextbox.setBlendMode(SDL_BLENDMODE_BLEND);
		gTextbox.setAlpha(200);
	}
	gTextbox.render(0, 0);
}
