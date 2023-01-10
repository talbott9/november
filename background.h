class Background { 
	public:
		Background();
		void render(SDL_Rect& camera);
		SDL_Rect background;
		SDL_Rect getBox();
		bool changeBG, success;
		int bgID;
	private:
		int backgroundTicks;
};
