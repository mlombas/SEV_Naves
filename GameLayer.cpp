#include "GameLayer.h"

#include <iostream>

GameLayer::GameLayer(Game* game)
	: Layer(game)
{
	init();
}

void GameLayer::init() {
	player = new Player(50, 50, game);
}

void GameLayer::processControls() {
}

void GameLayer::update() {
	std::cout << "update GameLayer" << std::endl;
}

void GameLayer::draw() {
	player->draw();

	SDL_RenderPresent(game->renderer); // Renderiza
}
