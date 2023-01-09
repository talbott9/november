#include "collision.cpp"
#include "cutscenes.cpp"
#include "menu.cpp"

const int LEVEL_WIDTH = 1290;
const int LEVEL_HEIGHT = 960;

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if( !gTextbox.loadFromFile( "resources/objects/textbox.png" ) )
	{
		printf("Failed to load object!\n");
		success = false;
	}
	if(!gComputerBG.loadFromFile("resources/bg/computer.png"))
		success = false;
	if(!gStreet1BG.loadFromFile("resources/bg/streetinautumn1.png"))
		success = false;
	if(!gStreet2BG.loadFromFile("resources/bg/streetinautumn2.png"))
		success = false;
	if(!gLivingRoomBG.loadFromFile("resources/bg/livingroom.png"))
		success = false;
	if(!gMenuBG.loadFromFile("resources/bg/menu.png"))
		success = false;
	if(!gCoastBG.loadFromFile("resources/bg/coast.png"))
		success = false;

	if(!gLouisPortrait.loadFromFile("resources/char/louis/louisportrait.png"))
		success = false;
	if(!gLouisPortraitNeutral.loadFromFile("resources/char/louis/louisportraitneutral.png"))
		success = false;
	if(!gLouisPortraitJoy.loadFromFile("resources/char/louis/louisportraitjoy.png"))
		success = false;
	if(!gLouisPortraitSad.loadFromFile("resources/char/louis/louisportraitsad.png"))
		success = false;
	if(!gLouisPortraitAngry.loadFromFile("resources/char/louis/louisportraitangry.png"))
		success = false;
	if(!gLouisPortraitSurprised.loadFromFile("resources/char/louis/louisportraitsurprised.png"))
		success = false;
	if(!gLouisPortraitSpecial.loadFromFile("resources/char/louis/louisportraitspecial.png"))
		success = false;
	if(!gLouisPortraitSpecial2.loadFromFile("resources/char/louis/louisportraitspecial2.png"))
		success = false;
	 if(!gLouis.loadFromFile("resources/char/louis/louis.png"))
		 success = false;
	 if(!gLouisJoy.loadFromFile("resources/char/louis/louisjoy.png"))
		 success = false;
	 if(!gLouisNeutral.loadFromFile("resources/char/louis/louisneutral.png"))
		 success = false;
	 if(!gLouisAngry.loadFromFile("resources/char/louis/louisangry.png"))
		 success = false;
	 if(!gLouisSurprised.loadFromFile("resources/char/louis/louissurprised.png"))
		 success = false;
	 if(!gLouisSpecial.loadFromFile("resources/char/louis/louisspecial.png"))
		 success = false;
	 if(!gLouisSpecial2.loadFromFile("resources/char/louis/louisspecial2.png"))
		 success = false;
	 if(!gLouisSad.loadFromFile("resources/char/louis/louissad.png"))
		 success = false;

	 /*
	if(!gMargaretPortrait.loadFromFile("resources/char/margaret/margaretportrait.png"))
		success = false;
	if(!gMargaretPortraitNeutral.loadFromFile("resources/char/margaret/margaretportraitneutral.png"))
		success = false;
	if(!gMargaretPortraitJoy.loadFromFile("resources/char/margaret/margaretportraitjoy.png"))
		success = false;
	if(!gMargaretPortraitSad.loadFromFile("resources/char/margaret/margaretportraitsad.png"))
		success = false;
	if(!gMargaretPortraitAngry.loadFromFile("resources/char/margaret/margaretportraitangry.png"))
		success = false;
	if(!gMargaretPortraitSurprised.loadFromFile("resources/char/margaret/margaretportraitsurprised.png"))
		success = false;
	if(!gMargaretPortraitSpecial.loadFromFile("resources/char/margaret/margaretportraitspecial.png"))
		success = false;*/
	 if(!gMargaret.loadFromFile("resources/char/margaret/margaret.png"))
		 success = false;
	 if(!gMargaretJoy.loadFromFile("resources/char/margaret/margaretjoy.png"))
		 success = false;
	 if(!gMargaretNeutral.loadFromFile("resources/char/margaret/margaretneutral.png"))
		 success = false;
	 if(!gMargaretAngry.loadFromFile("resources/char/margaret/margaretangry.png"))
		 success = false;
	 if(!gMargaretSurprised.loadFromFile("resources/char/margaret/margaretsurprised.png"))
		 success = false;
	 if(!gMargaretSpecial.loadFromFile("resources/char/margaret/margaretspecial.png"))
		 success = false;
	 if(!gMargaretSad.loadFromFile("resources/char/margaret/margaretsad.png"))
		 success = false;

	 /*
	if(!gHildegardePortrait.loadFromFile("resources/char/hildegarde/hildegardeportrait.png"))
		success = false;
	if(!gHildegardePortraitNeutral.loadFromFile("resources/char/hildegarde/hildegardeportraitneutral.png"))
		success = false;
	if(!gHildegardePortraitJoy.loadFromFile("resources/char/hildegarde/hildegardeportraitjoy.png"))
		success = false;
	if(!gHildegardePortraitAngry.loadFromFile("resources/char/hildegarde/hildegardeportraitangry.png"))
		success = false;
	if(!gHildegardePortraitImpatient.loadFromFile("resources/char/hildegarde/hildegardeportraitimpatient.png"))
		success = false;
	if(!gHildegardePortraitGlare.loadFromFile("resources/char/hildegarde/hildegardeportraitglare.png"))
		success = false;*/
	 if(!gHildegarde.loadFromFile("resources/char/hildegarde/hildegarde.png"))
		 success = false;
	 if(!gHildegardeJoy.loadFromFile("resources/char/hildegarde/hildegardejoy.png"))
		 success = false;
	 if(!gHildegardeNeutral.loadFromFile("resources/char/hildegarde/hildegardeneutral.png"))
		 success = false;
	 if(!gHildegardeAngry.loadFromFile("resources/char/hildegarde/hildegardeangry.png"))
		 success = false;
	 if(!gHildegardeGlare.loadFromFile("resources/char/hildegarde/hildegardeglare.png"))
		 success = false;
	 if(!gHildegardeImpatient.loadFromFile("resources/char/hildegarde/hildegardeimpatient.png"))
		 success = false;
	 if(!gHildegardeJoy.loadFromFile("resources/char/hildegarde/hildegardejoy.png"))
		 success = false;

	TTF_Font* gFont = TTF_OpenFont("resources/fonts/font1.ttf", 20);

	if(gFont == NULL || gFancyFont == NULL) {
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	else
	{
	}


	return success;
}

