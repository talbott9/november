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
int renderCharAlpha; 
bool charFade, charFadeSuccess;
bool charFadeOut, charFadeIn;
int complimentPoints;
bool switchlever;


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

std::ifstream hildegardelouis1("script/hildegarde_louis/s1");
std::ifstream hildegardelouis1_1("script/hildegarde_louis/s1-1");
std::ifstream hildegardelouis1_1_1("script/hildegarde_louis/s1-1-1");
std::ifstream hildegardelouis1_1_2("script/hildegarde_louis/s1-1-2");
std::ifstream hildegardelouis1_1_1_1("script/hildegarde_louis/s1-1-1-1");
std::ifstream hildegardelouis1_1_1_2("script/hildegarde_louis/s1-1-1-2");
std::ifstream hildegardelouis1_2("script/hildegarde_louis/s1-2");
std::ifstream hildegardelouis1_2_1("script/hildegarde_louis/s1-2-1");
std::ifstream hildegardelouis1_2_2("script/hildegarde_louis/s1-2-2");
std::string s;
int i;
char c;
std::string scriptLine[NUMBER_OF_LINES];

enum louis_hildegarde_scenes {louhil1, louhil1_1, louhil1_1_1, louhil1_1_2, louhil1_1_2_1, louhil1_1_2_2, louhil1_1_2_2_1, louhil1_1_2_2_1_1, louhil1_1_2_2_1_2, louhil1_1_2_2_2, louhil1_1_2_2_3};
louis_hildegarde_scenes louhil;
enum hildegarde_louis_scenes {hillou1, hillou1_1, hillou1_1_1, hillou1_1_2, hillou1_1_1_1, hillou1_1_1_2, hillou1_2, hillou1_2_1, hillou1_2_2};
hildegarde_louis_scenes hillou;

enum chars1 { louis1, longford1, lombard1, hildegarde1, margaret1, blanche1 };
enum chars2 { hildegarde2, margaret2, blanche2, louis2, longford2, lombard2 };
chars1 char1; chars2 char2;

enum detChar { louis_hildegarde, hildegarde_louis };

int determineChars() {
	switch(char1) {
		case louis1: 
			switch(char2) {
				     case hildegarde2: return louis_hildegarde; break;
			}
			break;
		case hildegarde1:
			switch(char2) {
				case louis2: return hildegarde_louis; break;
			}
			break;
	}
}

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
						charFade = 0; charFadeSuccess = 0; renderCharAlpha = 0;
					}
				} else {
					if(checkCollision(mouseBox, button1) || checkCollision(mouseBox, button2)) {
						if(selectedButton == 0) {
							bunki = 0;
						} else {
							bunki = 1;
						}
						freeText(&gText);
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
						charFade = 0; charFadeSuccess = 0; renderCharAlpha = 0;
					}
				} else {
					if(checkCollision(mouseBox, button1) || checkCollision(mouseBox, button2)) {
						if(selectedButton == 0) {
							bunki = 0;
						} else {
							bunki = 1;
						}
						freeText(&gText);
						trigger++;
					}
				}
				break;
		}
	}
}

void charAnim(LTexture* gChar, LTexture* gCharFace) {
	if(charFade && !charFadeSuccess) {
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

//0 Louis: 0 neutral, 1 joy, 2 sad, 3 angry, 4 surprised, 5 special, 6 special2, 7 kaikou
//1 Hildegarde: 0 neutral, 1 joy, 2 impatient, 3 angry, 4 glare, 5 heigan
int baseLouisX = 0; int baseLouisY = 0;
LTexture gFace;
void renderCharacter(int characterID, int faceID, int specialID = 0, int modifyX = 0, int modifyY = 0) {
	int louisX = baseLouisX + modifyX;
	int louisY = baseLouisY + modifyY;
	switch(characterID) {
		case 0:	 switch(faceID) {
				case 0: gFace = gLouisNeutral; break;
				case 1: gFace = gLouisJoy; break;
				case 2: gFace = gLouisSad; break;
				case 3: gFace = gLouisAngry; break;
				case 4: gFace = gLouisSurprised; break;
				case 5: gFace = gLouisSpecial; break;
				case 6: gFace = gLouisSpecial2; break;
				case 7: gFace = gLouisKaikou; break;
			}
			charAnim(&gLouis, &gFace);
			if(specialID == 0)
				gLouis.render(louisX, louisY);
			else
				gLouisHilda.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
		case 1:	switch(faceID) {
				case 0: gFace = gHildegardeNeutral; break;
				case 1: gFace = gHildegardeJoy; break;
				case 2: gFace = gHildegardeImpatient; break;
				case 3: gFace = gHildegardeAngry; break;
				case 4: gFace = gHildegardeGlare; break;
				case 5: gFace = gHildegardeHeigan; break;
			}
			charAnim(&gHildegarde, &gFace);
			gHildegarde.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
		case 2:	switch(faceID) {
				case 0: gFace = gMargaretNeutral; break;
				case 1: gFace = gMargaretJoy; break;
				case 2: gFace = gMargaretSad; break;
				case 3: gFace = gMargaretAngry; break;
				case 4: gFace = gMargaretSurprised; break;
				case 5: gFace = gMargaretSpecial; break;
			}
			charAnim(&gMargaret, &gFace);
			gMargaret.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
		case 3:	switch(faceID) {
				case 0: gFace = gLongfordNeutral; break;
				case 1: gFace = gLongfordJoy; break;
				case 2: gFace = gLongfordDaring; break;
				case 3: gFace = gLongfordReflect; break;
			}
			charAnim(&gLongford, &gFace);
			gLongford.render(louisX, louisY);
			gFace.render(louisX, louisY);
			break;
		case 4:	switch(faceID) {
				case 0: gFace = gBlancheNeutral; break;
				case 1: gFace = gBlancheJoy; break;
				case 2: gFace = gBlancheSad; break;
				case 3: gFace = gBlanchePerturbed; break;
				case 4: gFace = gBlancheNeutral2; break;
			}
			charAnim(&gBlanche, &gFace);
			gBlanche.render(louisX, louisY);
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
				case 6: gLouisPortraitSpecial2.render(louisXP, louisYP); break;
				case 7: gLouisPortraitKaikou.render(louisXP, louisYP); break;
			}
			break;
		case 1: gHildegardePortrait.render(louisXP, louisYP);
			switch(faceID) {
				case 0: gHildegardePortraitNeutral.render(louisXP, louisYP); break;
				case 1: gHildegardePortraitJoy.render(louisXP, louisYP); break;
				case 2: gHildegardePortraitImpatient.render(louisXP, louisYP); break;
				case 3: gHildegardePortraitAngry.render(louisXP, louisYP); break;
				case 4: gHildegardePortraitGlare.render(louisXP, louisYP); break;
				case 5: gHildegardePortraitHeigan.render(louisXP, louisYP); break;
			}
			break;
	}	
}

void renderTextbox() {
	if(activeDialogue) 
		textbox.render(camera, "hi");
}

void charFadeOutThenIn() {
	if(!background.success) {
		background.changeBG = 1;
		charFadeOut = 1;
		charFade = 1;
		switchlever = 1;
	} else {
		if(switchlever) {
			charFadeSuccess = 0;
			switchlever = 0;
		}
		charFadeOut = 0;
		charFade = 1;
	}
}


void resetToMenu() {
	for(int i =0; i < NUMBER_OF_LINES; i++)
		scriptLine[i] = "";
	switch(determineChars()) {
		case louis_hildegarde:
			louishildegarde1.clear(); 
			louishildegarde1.seekg(0, std::ios::beg);
			louishildegarde1_1.clear(); 
			louishildegarde1_1.seekg(0, std::ios::beg);
			louishildegarde1_1_1.clear(); 
			louishildegarde1_1_1.seekg(0, std::ios::beg);
			louishildegarde1_1_2.clear(); 
			louishildegarde1_1_2.seekg(0, std::ios::beg);
			louishildegarde1_1_2_1.clear(); 
			louishildegarde1_1_2_2.seekg(0, std::ios::beg);
			louishildegarde1_1_2_2_1.clear(); 
			louishildegarde1_1_2_2_1_1.seekg(0, std::ios::beg);
			louishildegarde1_1_2_2_1_2.clear(); 
			louishildegarde1_1_2_2_2.seekg(0, std::ios::beg);
			louishildegarde1_1_2_2_3.clear(); 
			break;
	}
	trigger = 0; lineNumber = 0; freeText(&gText); menuStep = 0;
	louhil = louhil1; background.success = 0; charFadeSuccess = 0;
	activeDialogue = 0; freeAll();
}

void resetScene() {
	 freeText(&gText); trigger = 0; lineNumber = 0; promptSelect = 0;
	 background.success = 0; charFadeSuccess = 0;
}

#include "stickgame.cpp"

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
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
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
					 renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
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
				case 29: resetToMenu(); break;
			} break;
		case louhil1_1_2: 
			switch(trigger) {
				case 0: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 1: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 7); break;
				case 6: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 9: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 10: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 11: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 14: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 15: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 16: promptSelect = 1; renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 17: if(!bunki) {
						 louhil = louhil1_1_2_1; 
						 indexScript(louishildegarde1_1_2_1);
					 } else {
						 louhil = louhil1_1_2_2; 
						 indexScript(louishildegarde1_1_2_2);
					 }
					 freeText(&gText); trigger = 0; lineNumber = 0; promptSelect = 0;
					 renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
			} break;
		case louhil1_1_2_1: 
			switch(trigger) {
				case 0: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 3: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 9: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 10: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 11: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 14: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 15: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 17: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 18: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 19: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 20: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1;
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 21: renderTextbox(); renderPortrait(0, 0); break;
				case 22: resetToMenu(); break;
			} break;
		case louhil1_1_2_2: 
			switch(trigger) {
				case 0: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 4); break;
				case 7: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 9: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 10: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 3); break;
				case 11: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 13: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 14: promptSelect = 0; 
					 if(!switchlever) {
						 if(!bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 1;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 1;
						 }
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 15: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: promptSelect = 0;
					 if(switchlever) {
						 if(!bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 0;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 0;
						 }
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 17: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 18: promptSelect = 0;
					 if(!switchlever) {
						 if(!bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 1;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 1;
						 }
					 }
					 if(complimentPoints == 3)
						 renderCharacter(1, 1);
					 else
						 renderCharacter(1, 0);
					 renderTextbox(); renderPortrait(0, 0); break;
				case 19: if(complimentPoints == 3)
						 renderCharacter(1, 1);
					 else
						 renderCharacter(1, 0);
					 renderTextbox(); renderPortrait(0, 0); break;
				case 20: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 21: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 22: promptSelect = 0; 
					 if(switchlever) {
						 if(!bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 0;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 0;
						 }
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 23: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 24: promptSelect = 0; 
					 if(!switchlever) {
						 if(bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 1;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 1;
						 }
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
			      	case 25: promptSelect = 1; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
			     	case 26: promptSelect = 0; 
					 if(switchlever) {
						 if(!bunki) {
							 complimentPoints++; lineNumber++; freeText(&gText); switchlever = 0;
						 } else {
							 lineNumber++; freeText(&gText); switchlever = 0;
						 }
					 }
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0);
					 if(complimentPoints == 6) {
						 louhil = louhil1_1_2_2_1;
						 indexScript(louishildegarde1_1_2_2_1);
					 } else if(complimentPoints >= 3) {
						 louhil = louhil1_1_2_2_2;
						 indexScript(louishildegarde1_1_2_2_2);
					 } else {
						 louhil = louhil1_1_2_2_3;
						 indexScript(louishildegarde1_1_2_2_3);
					 }
					 resetScene(); break;
			} break;
		case louhil1_1_2_2_1: 
			switch(trigger) {
				case 0: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 4); break;
				case 5: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 9: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 10: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 11: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 14: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 15: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 16: if(!background.success)
						 background.changeBG = 1;
					 background.bgID = 2;
					 renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 17: background.success = 0; renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 18: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 20: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 21: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 22: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 23: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 24: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 25: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 26: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 27: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 28: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 29: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 30: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 31: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 3); break;
				case 32: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 33: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 6); break;
				case 34: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 6); break;
				case 35: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 36: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 37: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 38: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 39: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 40: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 41: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 42: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 43: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 44: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 45: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 46: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 47: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 48: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 49: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 50: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 4); break;
				case 51: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 52: promptSelect = 1; renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 53: if(!bunki) {
						 louhil = louhil1_1_2_2_1_1;
						 indexScript(louishildegarde1_1_2_2_1_1);
					 } else {
						 louhil = louhil1_1_2_2_1_2;
						 indexScript(louishildegarde1_1_2_2_1_2);
					 }
					 renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
			} break;
		case louhil1_1_2_2_1_1: 
			switch(trigger) {
				case 0: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 3: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1;
					 }
					renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 4: charFadeSuccess = 0; renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderTextbox(); break;
				case 8: renderTextbox(); break;
				case 9: renderTextbox(); break;
				case 10: resetToMenu(); break;
			} break;
		case louhil1_1_2_2_1_2: 
			switch(trigger) {
				case 0: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 7); break;
				case 5: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 4); break;
				case 6: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 9: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 10: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 11: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 12: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 13: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 7); break;
				case 14: if(!charFadeSuccess) {
						charFadeOut = 1;
						charFade = 1; 
					} renderCharacter(1, 5); renderTextbox(); renderPortrait(0, 7); break;
				case 15: renderTextbox(); renderPortrait(0, 1); break;
				case 16: resetToMenu(); break;
			} break;
		case louhil1_1_2_2_2: 
			switch(trigger) {
				case 0: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 0); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 7: if(!charFadeSuccess) {
						charFadeOut = 1;
						charFade = 1;
					} 
					renderCharacter(1, 1); renderTextbox(); renderPortrait(0, 0); break;
				case 8: charFadeSuccess = 0; renderTextbox(); renderPortrait(0, 0); break;
				case 9: resetToMenu(); break;
			} break;
		case louhil1_1_2_2_3: 
			switch(trigger) {
				case 0: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 1: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 2: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 3: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 4: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 5: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 6: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 7: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 8: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 9: renderCharacter(1, 3); renderTextbox(); renderPortrait(0, 0); break;
				case 10: resetToMenu(); break;
			} break;
	}
	if(activeDialogue) {
		drawDialogueText(scriptLine[lineNumber], &gText);
	}

	//printf("%b\n", promptSelect);
}

void Cutscene::hildegarde_louis() {
	switch(hillou) {
		case hillou1:
			switch(trigger) {
				case 0: if(!background.success) {
						gBackground = gCoastBG;
						background.changeBG = 1;
					} else {
						activeDialogue = 1; renderTextbox();
					}	
					background.bgID = 2;  renderPortrait(1, 0);
					break;
				case 1: background.success = 0; renderTextbox(); renderPortrait(1, 0); break;
				case 2: if(!background.success) {
						background.changeBG = 1;
					}
					background.bgID = 1; renderTextbox(); renderPortrait(1, 0); break;
				case 3: background.success = 0; renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderTextbox(); renderPortrait(1, 0); break;
				case 5: if(!charFadeSuccess) {
						charFadeIn = 1;
						charFade = 1; 
					}
					renderCharacter(0, 1); renderTextbox();  renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 1); renderTextbox();  renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 7); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 7); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 12: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 13: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0);
					 promptSelect = 1; break;
				case 17: if(!bunki) {
						 hillou = hillou1_1;
						 indexScript(hildegardelouis1_1);
					 } else {
						 hillou = hillou1_2;
						 indexScript(hildegardelouis1_2);
					 }
					 renderCharacter(0, 4); renderTextbox(); renderPortrait(1, 0); resetScene(); break;
			} break;
		case hillou1_1: 
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 12: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 13: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); trigger++; break;
				case 17: charFadeOutThenIn();
					 background.bgID = 5; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 18: renderCharAlpha = 255; charFade = 0; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 19: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 20: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 21: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 22: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 23: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 24: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 25: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 26: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 27: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 28: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 29: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 30: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 31: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				default: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0);
					 stickGame(); break;
			} break;
		case hillou1_1_1: 
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 3: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 1); break;
				case 4: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 12: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 13: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0);break;
				case 17: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 18: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 19: if(!background.success)
						 background.changeBG = 1;
					 charFadeOut = 1;
					 charFade = 1;
					 background.bgID = 5;
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 20: renderTextbox(); renderPortrait(1, 0); break;
				case 21: renderTextbox(); renderPortrait(1, 0); break;
				case 22: renderTextbox(); renderPortrait(1, 0); break;
				case 23: renderTextbox(); renderPortrait(1, 0); break;
				case 24: renderTextbox(); renderPortrait(1, 0); break;
				case 25: renderTextbox(); renderPortrait(1, 0); break;
				case 26: renderTextbox(); renderPortrait(1, 0); break;
				case 27: renderTextbox(); renderPortrait(1, 0); break;
				case 28: renderTextbox(); renderPortrait(1, 0); break;
				case 29: renderTextbox(); renderPortrait(1, 0); break;
				case 30: renderTextbox(); renderPortrait(1, 0); break;
				case 31: renderTextbox(); renderPortrait(1, 0); break;
				case 32: renderTextbox(); renderPortrait(1, 0); break;
				case 33: if(!background.success) {
						 background.changeBG = 1;
					 } else {
						 charFadeOut = 0;
						 charFade = 1;
					 }
					 background.bgID = 2;
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 34: renderCharAlpha = 255; charFade = 0; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 35: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 36: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 37: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 38: promptSelect = 1; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 39: if(!bunki) {
						 hillou = hillou1_1_1_1;
						 indexScript(hildegardelouis1_1_1_1);
					 } else {
						 hillou = hillou1_1_1_2;
						 indexScript(hildegardelouis1_1_1_2);
					 }
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(0, 0); loadMargaret(); loadBlanche(); loadLongford(); resetScene(); break;		
			} break;
		case hillou1_1_1_1: 
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: charFadeOut = 1;
					charFade = 1;
					if(!background.success)
						background.changeBG = 1;
					background.bgID = 1;
					renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4:	charFadeOut = 0;
					charFade = 1;
					renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 12: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 13: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1; 
					 }
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: if(!charFadeSuccess) {
						 charFadeOut = 0;
						 charFade = 1;
					 }
					 renderCharacter(0, 6, 1); renderTextbox(); renderPortrait(1, 1); break;
				case 17: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 1); break;
				case 18: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 1); break;
				case 19: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 20: renderCharacter(0, 4, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 21: if(!charFadeSuccess) {
						  charFadeIn = 1;
						  charFade = 1;
					  }
					 renderCharacter(0, 0, 1, -200); renderCharacter(2, 4, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 22: renderCharacter(0, 0, 1, -200); renderCharacter(2, 4, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 23: renderCharacter(0, 0, 1, -200); renderCharacter(2, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 24: renderCharacter(0, 5, 1, -200); renderCharacter(2, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 25: renderCharacter(0, 0, 1, -200); renderCharacter(2, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 26: renderCharacter(0, 0, 1, -200); renderCharacter(2, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 27: renderCharacter(0, 0, 1, -200); renderCharacter(2, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 28: renderCharacter(0, 6, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 29: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 30: renderCharacter(0, 7, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 31: renderCharacter(0, 6, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 32: renderCharacter(0, 6, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 33: renderCharacter(0, 0, 1, -200); renderCharacter(4, 1, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 34: renderCharacter(0, 0, 1, -200); renderCharacter(4, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 35: renderCharacter(0, 0, 1, -200); renderCharacter(4, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 36: renderCharacter(0, 0, 1, -200); renderCharacter(4, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 37: renderCharacter(0, 0, 1, -200); renderCharacter(4, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 38: renderCharacter(0, 0, 1, -200); renderCharacter(4, 4, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 39: renderCharacter(0, 0, 1, -200); renderCharacter(4, 4, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 40: renderCharacter(0, 0, 1, -200); renderCharacter(4, 4, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 41: renderCharacter(0, 0, 1, -200); renderCharacter(4, 3, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 42: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 43: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 44: renderCharacter(0, 3, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 45: renderCharacter(0, 3, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 46: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 47: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 48: renderCharacter(0, 0, 1, -200); renderTextbox(); renderPortrait(1, 0); break;
				case 49: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 50: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 51: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 52: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 53: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 54: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 55: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 56: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 57: renderCharacter(0, 0, 1, -200); renderCharacter(3, 1, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 58: renderCharacter(0, 6, 1, -200); renderCharacter(3, 1, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 59: renderCharacter(0, 6, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 60: renderCharacter(0, 0, 1, -200); renderCharacter(3, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 61: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1;
						 renderCharacter(0, 0, 1, -200); 
						 renderCharacter(3, 0, 0, 200);
						 switchlever = 1;
					 } else if(switchlever) {
						 switchlever = 0;
						 charFadeIn = 1;
						 charFade = 1;
					 } else {
						 renderCharacter(0, 0, 1);
					 }
					 renderTextbox(); renderPortrait(1, 0); break;
				case 62: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 63: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 64: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 65: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 66: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 67: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 68: renderCharacter(0, 0, 1); renderTextbox(); renderPortrait(1, 0); break;
				case 69: if(!background.success) {
						 charFadeOut = 1;
						 charFade = 1;
						 background.changeBG = 1;
						 background.bgID = 5;
						 switchlever = 1;
					 } else if(switchlever) {
						 switchlever = 0;
						 charFadeIn = 1;
						 charFade = 1;
					 }
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 70: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 71: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 72: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 73: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 74: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 75: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 76: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 77: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 78: if(!background.success) {
						 charFadeOut = 1;
						 charFade = 1;
						 background.changeBG = 1;
						 background.bgID = 2;
						 switchlever = 1;
					 } else if(switchlever) {
						 switchlever = 0;
						 charFadeIn = 1;
						 charFade = 1;
					 }
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 79: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 80: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 81: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 82: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 83: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 84: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 85: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 86: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 87: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 88: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 1); break;
				case 89: resetToMenu();
			} break;
		case hillou1_1_1_2:
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11: if(!charFadeSuccess) {
						 charFadeOut = 1;
						 charFade = 1;
					 }
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 12: resetToMenu(); break;
			} break;
		case hillou1_1_2:
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 3); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: resetToMenu(); break;
			} break;
		case hillou1_2:
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: promptSelect = 1; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0);
					if(!bunki) {
						hillou = hillou1_2_1;
					        indexScript(hildegardelouis1_2_1);
					} else {
						hillou = hillou1_2_2;
						indexScript(hildegardelouis1_2_2);
					}
					 renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); resetScene();
					 break;
			} break;
		case hillou1_2_1:
			switch(trigger) {
				case 0: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 2: if(!background.success) {
						background.changeBG = 1;
					}
					background.bgID = 6;
					renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 5: renderCharacter(0, 6); renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 4); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 10: if(!background.success) {
						 background.changeBG = 1;
					 }
					background.bgID = 4; renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 11:renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 12: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 13: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 17: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 18: resetToMenu(); break;
				case 19: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 20: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 21: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 22: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 23: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 24: resetToMenu(); break;
			} break;
		case hillou1_2_2:
			switch(trigger) {
				case 0: gStoreBG.loadFromFile("resources/bg/thestore.png"); gInsideStoreBG.loadFromFile("resources/bg/insidestore.png"); renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 1: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 2: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 3: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 4: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 1); break;
				case 5: if(!background.success) {
						background.changeBG = 1;
						renderCharacter(0, 0);
					} else {
						if(!charFadeSuccess) {
							charFadeIn = 1;
							charFade = 1;
						}
						renderCharacter(0, 6, 0, 200);
					}
					background.bgID = 7;
					renderTextbox(); renderPortrait(1, 0); break;
				case 6: renderCharacter(0, 6, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 7: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 8: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 9: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 10: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 11: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 0); break;
				case 12: renderCharacter(0, 0, 0, 200); renderTextbox(); renderPortrait(1, 1); break;
				case 13: if(!background.success) {
						 background.changeBG = 1;
						 renderCharacter(0, 0, 0, 200);
					 } else {
						if(!charFadeSuccess) {
							charFadeIn = 1;
							charFade = 1;
						}
						renderCharacter(0, 0);
					}
					 background.bgID = 8; renderTextbox(); renderPortrait(1, 0); break;
				case 14: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 15: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 16: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 17: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 18: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 19: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 20: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 21: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 22: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 23: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 24: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 25: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 26: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 27: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 28: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 29: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 30: renderCharacter(0, 0); renderTextbox(); renderPortrait(1, 0); break;
				case 31: resetToMenu(); break;
			} break;
	}
	if(activeDialogue) {
		drawDialogueText(scriptLine[lineNumber], &gText);
	}

	//printf("%b\n", promptSelect);
}
