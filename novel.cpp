//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "level1.cpp"

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Novel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
                		if( TTF_Init() == -1 )
                		{
                			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    			success = false;
                		}
			}
		}
	}

	return success;
}

void close()
{
	freeAll();
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	srand(time(NULL));
	indexScript(louishildegarde1);
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		loadFont(25);
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			char1 = hildegarde1; char2 = louis2;
			while(!quit)
			{
				background.render(camera);
				
				if(menuStep == 1) {
					switch(determineChars()) {
						case louis_hildegarde:
							cutscene.louis_hildegarde(); break;
						case hildegarde_louis:
							cutscene.hildegarde_louis(); break;
					}
					if(promptSelect)
						renderButtons();
				} else {
					menu.renderMenu();
				}

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
						if(e.key.keysym.sym == SDLK_q)
							quit = true;
						if(e.key.keysym.sym == SDLK_a) {
							hillou = hillou1_1;
							indexScript(hildegardelouis1_1);				
						}
					}


					if(promptSelect)
						button.handleEvent(e);
					if(activeDialogue)
						cutscene.handleEvent(e, scriptLine[lineNumber]);
					if(menuStep != 1)
						menu.handleEvent(e);
				}

								
				SDL_RenderPresent( gRenderer );

			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

