enum chars1 { louis1, longford1, lombard1, hildegarde1, margaret1, phyllis1 };
enum chars2 { hildegarde2, margaret2, phyllis2, louis2, longford2, lombard2 };
chars1 char1; chars2 char2;

class Menu { 
	public:
		SDL_Rect startButton;
		SDL_Rect loadButton;
		SDL_Rect name1Button;
		SDL_Rect name2Button;
		void renderMenu();
		void handleEvent(SDL_Event& e);
};

LTexture gName1, gName2, gStart;
void Menu::renderMenu() {
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseBox.x = mouseX; mouseBox.y = mouseY; mouseBox.w = 5; mouseBox.h = 5;
	printf("%i/%i/%i\n", mouseX, mouseY, menuStep);
	background.bgID = 4;

	if(menuStep == 0) {
		startButton.x = 325; startButton.y = 420; startButton.w = 160; startButton.h = 65;
		loadButton.x = 535; loadButton.y = 420; loadButton.w = 170; loadButton.h = 70;
		name1Button.x = 90; name1Button.y = 445; name1Button.w = 190; name1Button.h = 45;
		name2Button.x = 90; name2Button.y = 505; name2Button.w = 190; name2Button.h = 45;

		std::string name1, name2;
		switch(char1) {
			case louis1: name1 = "Louis"; break;
			case longford1: name1 = "Longford"; break;
			case lombard1: name1 = "Lombard"; break;
			case hildegarde1: name1 = "Hildegarde"; break;
			case margaret1: name1 = "Margaret"; break;
			case phyllis1: name1 = "Phyllis"; break;
		}
		switch(char2) {
			case hildegarde2: name2 = "Hildegarde"; break;
			case margaret2: name2 = "Margaret"; break;
			case phyllis2: name2 = "Phyllis"; break;
			case louis2: name2 = "Louis"; break;
			case longford2: name2 = "Longford"; break;
			case lombard2: name2 = "Lombard"; break;
		}

		gName1.loadFromRenderedText(name1, Black, 0, gFancyFont);
		gName1.render(90, 450);
		gName2.loadFromRenderedText(name2, Black, 0, gFancyFont);
		gName2.render(90, 510);

		gStart.loadFromRenderedText("Start", Black, 0, gBigFancyFont);
		gStart.render(330, 425);
		gStart.loadFromRenderedText("Load", Black, 0, gBigFancyFont);
		gStart.render(540, 425);

		gMenuBG.render(0, 0);
		
		if(checkCollision(mouseBox, startButton)) {
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
			SDL_RenderFillRect(gRenderer, &startButton);
		} else if(checkCollision(mouseBox, loadButton)) {
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
			SDL_RenderFillRect(gRenderer, &loadButton);
		}/* else if(checkCollision(mouseBox, name1Button)) {
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
			SDL_RenderFillRect(gRenderer, &name1Button);
		} else if(checkCollision(mouseBox, name2Button)) {
			SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);	
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 100);
			SDL_RenderFillRect(gRenderer, &name2Button);
		}*/
	}
}

void Menu::handleEvent(SDL_Event& e) {
	if(e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState(&mouseX, &mouseY);
		mouseBox.x = mouseX; mouseBox.y = mouseY; mouseBox.w = 5; mouseBox.h = 5;
		switch(e.button.button) {
			case SDL_BUTTON_LEFT:
				if(menuStep == 0) {
					if(checkCollision(mouseBox, startButton)) {
						menuStep = 1;
					} else if(checkCollision(mouseBox, loadButton)) {
						menuStep = 2;
					} else if(checkCollision(mouseBox, name1Button)) {
						if(char1 == 5)
							char1 = static_cast<chars1>(0);
						else
							char1 = static_cast<chars1>(char1 + 1);				
					} else if(checkCollision(mouseBox, name2Button)) {
						if(char2 == 5)
							char2 = static_cast<chars2>(0);
						else
							char2 = static_cast<chars2>(char2 + 1);								
					}

				}
				break;
		}
	}
}

Menu menu;
