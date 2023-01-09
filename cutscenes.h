class Cutscene {
	public:
		void render( SDL_Rect& camera );
		void handleEvent(SDL_Event& e, std::string s);
		void louis_hildegarde();
		int sceneID;
	private:
};
