#include "renderer.cpp"
#include "button.cpp"
#include <SDL_ttf.h>
#include "cutscenes.h"
#include "background.cpp"
#include <fstream>

Cutscene cutscene;

bool interactValue = 1;
bool saveGame = 0;
int trigger, lineNumber;
std::string dialogueText = "";
bool bunki; //controls branching after choices
int menuStep; // controls menu

const int NUMBER_OF_LINES = 100;
std::ifstream louishildegarde1("script/louis_hildegarde/s1");
std::ifstream louishildegarde1_1("script/louis_hildegarde/s1-1");
std::ifstream louishildegarde1_1_1("script/louis_hildegarde/s1-1-1");
std::ifstream louishildegarde1_1_2("script/louis_hildegarde/s1-1-2");
std::ifstream louishildegarde1_1_2_1("script/louis_hildegarde/s1-1-2-1");
std::ifstream louishildegarde1_1_2_2("script/louis_hildegarde/s1-1-2-2");
std::ifstream louishildegarde1_1_2_2_1("script/louis_hildegarde/s1-1-2-2-1");
std::ifstream louishildegarde1_1_2_2_1_1("script/louis_hildegarde/s1-1-2-2-1-1");
std::ifstream louishildegarde1_1_2_2_1_2("script/louis_hildegarde/s1-1-2-2-1-2");
std::ifstream louishildegarde1_1_2_2_2("script/louis_hildegarde/s1-1-2-2-2");
std::ifstream louishildegarde1_1_2_2_3("script/louis_hildegarde/s1-1-2-2-3");
std::string s;
int i;
char c;
std::string scriptLine[NUMBER_OF_LINES];

enum louishilscenes {louhil1, louhil1_1, louhil1_1_1, louhil1_1_2, louhil1_1_2_1, louhil1_1_2_2, louhil1_1_2_2_1, louhil1_1_2_2_1_1, louhil1_1_2_2_2, louhil1_1_2_2_3};
louishilscenes louhil;

void indexScript(std::ifstream& script) {
	while(script.get(c)) {
		if(isdigit(c)) {
				scriptLine[i] = s; i++;
				s = "";
	//	} else if(c == '\\') {
	//		s += "\n           ";
	//		std::cout << &c << std::endl;
		} else {
				s += c;
			}
	}
	i = 0;
}

void Cutscene::handleEvent(SDL_Event& e, std::string s) {
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_z:
				if(!promptSelect) {
					if(charCount < s.size()) {
						doNotType = 1;
					} else {
						doNotType = 0;
						freeText(&gText);
						trigger++; lineNumber++; background.success = 0;
					}
				} else {
					if(checkCollision(mouseBox, button1) || checkCollision(mouseBox, button2)) {
						if(selectedButton == 0) {
							bunki = 0;
						} else {
							bunki = 1;
						}
						trigger++;
					}
				}
				break;
		}
	}
	if(e.type == SDL_MOUSEBUTTONDOWN) {
		switch(e.button.button) {
			case SDL_BUTTON_LEFT:
				if(!promptSelect) {
					if(charCount < s.size()) {
						doNotType = 1;
					} else {
						doNotType = 0;
						freeText(&gText);
						trigger++; lineNumber++; background.success = 0;
					}
				} else {
					if(checkCollision(mouseBox, button1) || checkCollision(mouseBox, button2)) {
						if(selectedButton == 0) {
							bunki = 0;
						} else {
							bunki = 1;
						}
						trigger++;
					}
				}
				break;
		}
	}
}

int renderCharAlpha; 
bool charFade, charFadeSuccess;
bool charFadeOut;
void charAnim(LTexture* gChar, LTexture* gCharFace) {
	if(charFade) {
		charFadeSuccess = 0;
		renderCharAlpha += 15;
		gChar->setBlendMode(SDL_BLENDMODE_BLEND);
		gCharFace->setBlendMode(SDL_BLENDMODE_BLEND);
		if(!charFadeOut) {
			gChar->setAlpha(renderCharAlpha);
			gCharFace->setAlpha(renderCharAlpha);
		} else {
			gChar->setAlpha(255 - renderCharAlpha);
			gCharFace->setAlpha(255 - renderCharAlpha);
		}
		if(renderCharAlpha == 255) {
			charFade = 0; charFadeSuccess = 1;
			renderCharAlpha = 0;
		}
	}
}

//0 Louis: 0 neutral, 1 joy, 2 sad, 3 angry, 4 surprised, 5 special
//1 Hildegarde: 0 neutral, 1 joy, 2 impatient, 3 angry, 4 glare
int louisX = 0; int louisY = 0;
LTexture gFace;
void renderCharacter(int characterID, int faceID) {
	switch(characterID) {
		case 0:	switch(faceID) {
				case 0: gFace = gLouisNeutral; break;
				case 1: gFace = gLouisJoy; break;
				case 2: gFace = gLouisSad; break;
				case 3: gFace = gLouisAngry; break;
				case 4: gFace = gLouisSurprised; break;
				case 5: gFace = gLouisSpecial; break;
			}
			charAnim(&gLouis, &gFace);
			gLouis.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
		case 1:	switch(faceID) {
				case 0: gFace = gHildegardeNeutral; break;
				case 1: gFace = gHildegardeJoy; break;
				case 2: gFace = gHildegardeImpatient; break;
				case 3: gFace = gHildegardeAngry; break;
				case 4: gFace = gHildegardeGlare; break;
			}
			charAnim(&gHildegarde, &gFace);
			gHildegarde.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
	}	
}	

int louisXP = 5; int louisYP = 445;
void renderPortrait(int characterID, int faceID) {
	switch(characterID) {
		case 0: gLouisPortrait.render(louisXP, louisYP);
			switch(faceID) {
				case 0: gLouisPortraitNeutral.render(louisXP, louisYP); break;
				case 1: gLouisPortraitJoy.render(louisXP, louisYP); break;
				case 2: gLouisPortraitSad.render(louisXP, louisYP); break;
				case 3: gLouisPortraitAngry.render(louisXP, louisYP); break;
				case 4: gLouisPortraitSurprised.render(louisXP, louisYP); break;
				case 5: gLouisPortraitSpecial.render(louisXP, louisYP); break;
			}
			break;
	}	
}

void renderTextbox() {
	if(activeDialogue) 
		textbox.render(camera, "hi");
}

void Cutscene::louis_hildegarde() {
	switch(louhil) {
		case louhil1:
			switch(trigger) {
				case 0: if(!background.success) {
						gBackground = gCoastBG;
						background.changeBG = 1;
					} else {
						activeDialogue = 1; renderTextbox();
					}	
					background.bgID = 0; 
					renderPortrait(0, 0);
					break;
				case 1: if(!background.success)
						background.changeBG = 1;
					background.bgID = 1; renderTextbox(); renderPortrait(0,0); break;
				case 4: background.success = 0;
					if(!charFadeSuccess) {
						charFadeOut = 0;
						charFade = 1;
					}
					renderCharacter(1, 0); renderTextbox(); renderPortrait(0,0); break;
				case 5: charFadeSuccess = 0; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 1); break;
				case 6: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 4); break;
				case 7: renderCharacter(1, 0); renderTextbox();  renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 0); renderTextbox();  renderPortrait(0, 3); break;
				case 9: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 10: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 11: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 12: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 14: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 15: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: freeText(&gText); trigger = 0; louhil = louhil1_1; indexScript(louishildegarde1_1); lineNumber = 0;
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0);
				default: renderTextbox(); renderPortrait(0, 0); break;
			} break;
		case louhil1_1: 
			switch(trigger) {
				case 0: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 1); break;
				case 1: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 4); break;
				case 2: renderCharacter(1, 0); renderTextbox();  renderPortrait(0, 4); break;
				case 3: if(!background.success)
						background.changeBG = 1;
					background.bgID = 3;
					renderCharacter(1, 0); renderTextbox();  renderPortrait(0, 4); break;
				case 4: background.success = 0;
					renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 5: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 5); break;
				case 7: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 5); break;
				case 8: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 9: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 10: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 11: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 14: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 15: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 17: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 18: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 19: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 20: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 21: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 22: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 23: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 24: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 25: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 26: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 5); break;
				case 27: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 5); break;
				case 28: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 5); break;
				case 29: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 5); break;
				case 30: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 31: promptSelect = 1; renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 32: if(!bunki) {
						 louhil = louhil1_1_1; 
						 indexScript(louishildegarde1_1_1);
					 } else {
						 louhil = louhil1_1_2; 
						 indexScript(louishildegarde1_1_2);
					 }
					 freeText(&gText); trigger = 0; lineNumber = 0; promptSelect = 0;
					 renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3);
			} break;
		case louhil1_1_1: 
			switch(trigger) {
				case 0: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 1: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 2: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 3: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 4: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 6: if(!background.success)
						 background.changeBG = 1;
					 background.bgID = 1;
					renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 7: background.success = 0; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 8: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 9: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 10: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 11: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 12: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 13: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 14: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 15: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 17: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 18: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 19: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 20: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 21: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1;
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 22: renderTextbox(); renderPortrait(0, 0); break;
				case 23: charFadeSuccess = 0; charFadeOut = 0;
					 if(!background.success)
						 background.changeBG = 1;
					 background.bgID = 3;
					 renderTextbox(); renderPortrait(0, 0); break;
				case 24: background.success = 0; renderTextbox(); renderPortrait(0, 0); break;
				case 25: renderTextbox(); renderPortrait(0, 0); break;
				case 26: renderTextbox(); renderPortrait(0, 0); break;
				case 27: renderTextbox(); renderPortrait(0, 0); break;
				case 28: renderTextbox(); renderPortrait(0, 0); break;
			} break;

	}
	if(activeDialogue) {
		drawDialogueText(scriptLine[lineNumber], &gText);
	}

	//printf("%b\n", promptSelect);
}
