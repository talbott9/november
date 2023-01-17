#include "background.h"

Background::Background() {
	background.x = 0; background.y = 0;
	background.w = 800; background.h = 600;
}

SDL_Rect Background::getBox() {
	return background;
}

void Background::render(SDL_Rect& camera) {
	//printf("%i, %b\n", bgID, changeBG);
	switch(bgID) {
		case 0: gForeground = gComputerBG; break;
		case 1: gForeground = gStreet1BG; break;
		case 2: gForeground = gStreet2BG; break;
		case 3: gForeground = gLivingRoomBG; break;
		case 4: gForeground = gCoastBG; break;
		case 5: gForeground = gClassroomBG; break;
		case 6: gForeground = gLakeBG; break;
		case 7: gForeground = gStoreBG; break;
		case 8: gForeground = gInsideStoreBG; break;
	}

	if(changeBG) {
		activeDialogue = 0;
		success = 0;
		gBackground.render(background.x, background.y);
		backgroundTicks += 5;
		gForeground.setBlendMode(SDL_BLENDMODE_BLEND);
		gForeground.setAlpha(backgroundTicks);
		if(backgroundTicks == 255) {
			gForeground.setAlpha(255);
			backgroundTicks = 0;
			changeBG = 0;
			success = 1;
			gBackground = gForeground;
			textbox.transition = 1;
			activeDialogue = 1;
		}
	}
	gForeground.render(background.x, background.y);
}

Background background;
