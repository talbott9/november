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

LTexture gTextbox;

LTexture gLouis, gLouisNeutral, gLouisJoy, gLouisSad, gLouisAngry, gLouisSurprised, gLouisSpecial, gLouisSpecial2;
LTexture gHildegarde, gHildegardeNeutral, gHildegardeJoy, gHildegardeImpatient, gHildegardeAngry, gHildegardeGlare;
LTexture gMargaret, gMargaretNeutral, gMargaretJoy, gMargaretSad, gMargaretAngry, gMargaretSurprised, gMargaretSpecial;


LTexture gMargaretPortrait, gMargaretPortraitNeutral, gMargaretPortraitJoy, gMargaretPortraitSad, gMargaretPortraitAngry, gMargaretPortraitSurprised, gMargaretPortraitSpecial;
LTexture gHildegardePortrait, gHildegardePortraitNeutral, gHildegardePortraitJoy, gHildegardePortraitImpatient, gHildegardePortraitAngry, gHildegardePortraitGlare;
LTexture gLouisPortrait, gLouisPortraitNeutral, gLouisPortraitJoy, gLouisPortraitSad, gLouisPortraitAngry, gLouisPortraitSurprised, gLouisPortraitSpecial, gLouisPortraitSpecial2;
