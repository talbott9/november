novel: novel.cpp renderer.h renderer.cpp level1.cpp cutscenes.cpp cutscenes.h button.h button.cpp collision.cpp text.h background.h background.cpp menu.h menu.cpp stickgame.cpp
	g++ novel.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o novel
