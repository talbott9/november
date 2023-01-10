class Menu { 
	public:
		SDL_Rect startButton;
		SDL_Rect loadButton;
		SDL_Rect name1Button;
		SDL_Rect name2Button;
		void renderMenu();
		void handleEvent(SDL_Event& e);
};

