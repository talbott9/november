const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;
TTF_Font* gBattleFont = NULL;

SDL_Color White = {255, 255, 255};
SDL_Color Grey = {200, 200, 255};
SDL_Color Blue1 = {0, 105, 255};
SDL_Color Black = {0, 0, 0};

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor, int wrapBoundary, TTF_Font* gFont);

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

		SDL_Rect getBox();
	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;

		SDL_Rect mBox;
};

LTexture gBackground, gForeground;
LTexture gMenuBG, gComputerBG, gStreet1BG, gStreet2BG, gLivingRoomBG, gCoastBG, gClassroomBG, gLakeBG;

LTexture gTextbox, gArrow;

LTexture gLouis, gLouisNeutral, gLouisJoy, gLouisSad, gLouisAngry, gLouisSurprised, gLouisSpecial, gLouisSpecial2, gLouisKaikou;
LTexture gHildegarde, gHildegardeNeutral, gHildegardeJoy, gHildegardeImpatient, gHildegardeAngry, gHildegardeGlare, gHildegardeHeigan;
LTexture gMargaret, gMargaretNeutral, gMargaretJoy, gMargaretSad, gMargaretAngry, gMargaretSurprised, gMargaretSpecial;


LTexture gMargaretPortrait, gMargaretPortraitNeutral, gMargaretPortraitJoy, gMargaretPortraitSad, gMargaretPortraitAngry, gMargaretPortraitSurprised, gMargaretPortraitSpecial;
LTexture gHildegardePortrait, gHildegardePortraitNeutral, gHildegardePortraitJoy, gHildegardePortraitImpatient, gHildegardePortraitAngry, gHildegardePortraitGlare, gHildegardePortraitHeigan;
LTexture gLouisPortrait, gLouisPortraitNeutral, gLouisPortraitJoy, gLouisPortraitSad, gLouisPortraitAngry, gLouisPortraitSurprised, gLouisPortraitSpecial, gLouisPortraitSpecial2, gLouisPortraitKaikou;

void loadHildegarde() {
	gHildegarde.loadFromFile("resources/char/hildegarde/hildegarde.png"); 
	gHildegardeNeutral.loadFromFile("resources/char/hildegarde/hildegardeneutral.png");
       	gHildegardeJoy.loadFromFile("resources/char/hildegarde/hildegardejoy.png");
       	gHildegardeImpatient.loadFromFile("resources/char/hildegarde/hildegardeimpatient.png");
       	gHildegardeAngry.loadFromFile("resources/char/hildegarde/hildegardeangry.png");
       	gHildegardeGlare.loadFromFile("resources/char/hildegarde/hildegardeglare.png");
       	gHildegardeHeigan.loadFromFile("resources/char/hildegarde/hildegardeheigan.png");

}

void loadHildegardePortrait() {
	gHildegardePortrait.loadFromFile("resources/char/hildegarde/hildegardeportrait.png"); 
	gHildegardePortraitNeutral.loadFromFile("resources/char/hildegarde/hildegardeportraitneutral.png");
       	gHildegardePortraitJoy.loadFromFile("resources/char/hildegarde/hildegardeportraitjoy.png");
       	gHildegardePortraitImpatient.loadFromFile("resources/char/hildegarde/hildegardeportraitimpatient.png");
       	gHildegardePortraitAngry.loadFromFile("resources/char/hildegarde/hildegardeportraitangry.png");
       	gHildegardePortraitGlare.loadFromFile("resources/char/hildegarde/hildegardeportraitglare.png");
       	gHildegardePortraitHeigan.loadFromFile("resources/char/hildegarde/hildegardeportraitheigan.png");

}

void loadLouis() {
	gLouis.loadFromFile("resources/char/louis/louis.png"); 
	gLouisNeutral.loadFromFile("resources/char/louis/louisneutral.png");
      	gLouisJoy.loadFromFile("resources/char/louis/louisjoy.png");  
       	gLouisSad.loadFromFile("resources/char/louis/louissad.png");  
       	gLouisAngry.loadFromFile("resources/char/louis/louisangry.png");  
       	gLouisSurprised.loadFromFile("resources/char/louis/louissurprised.png");   
	gLouisSpecial.loadFromFile("resources/char/louis/louisspecial.png");  
       	gLouisSpecial2.loadFromFile("resources/char/louis/louisspecial2.png");  
       	gLouisKaikou.loadFromFile("resources/char/louis/louiskaikou.png");  

}

void loadLouisPortrait() {
	gLouisPortrait.loadFromFile("resources/char/louis/louisportrait.png"); 
	gLouisPortraitNeutral.loadFromFile("resources/char/louis/louisportraitneutral.png");
      	gLouisPortraitJoy.loadFromFile("resources/char/louis/louisportraitjoy.png");  
       	gLouisPortraitSad.loadFromFile("resources/char/louis/louisportraitsad.png");  
       	gLouisPortraitAngry.loadFromFile("resources/char/louis/louisportraitangry.png");  
       	gLouisPortraitSurprised.loadFromFile("resources/char/louis/louisportraitsurprised.png");   
	gLouisPortraitSpecial.loadFromFile("resources/char/louis/louisportraitspecial.png");  
       	gLouisPortraitSpecial2.loadFromFile("resources/char/louis/louisportraitspecial2.png");  
       	gLouisPortraitKaikou.loadFromFile("resources/char/louis/louisportraitkaikou.png");  

}

void freeAll() {
	//Free loaded images
	gStreet1BG.free(); gStreet2BG.free(); gComputerBG.free(); gLivingRoomBG.free();
	gTextbox.free();
	gArrow.free();
	gHildegardeJoy.free();
	gMenuBG.free();
	gCoastBG.free();
	gLouisPortrait.free(); gLouisPortraitNeutral.free(); gLouisPortraitJoy.free(); gLouisPortraitSad.free(); gLouisPortraitAngry.free();  
       	gLouisPortraitSurprised.free();   
	gLouisPortraitSpecial.free();  
       	gLouisPortraitSpecial2.free();  
       	gLouisPortraitKaikou.free(); 
	gHildegarde.free(); gHildegardeNeutral.free(); gHildegardeJoy.free(); gHildegardeImpatient.free(); gHildegardeAngry.free(); gHildegardeGlare.free(); gHildegardeHeigan.free();
	gHildegardePortrait.free(); gHildegardePortraitNeutral.free(); gHildegardePortraitJoy.free(); gHildegardePortraitImpatient.free(); gHildegardePortraitAngry.free(); gHildegardePortraitGlare.free(); gHildegardePortraitHeigan.free();
}
