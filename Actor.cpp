#include "Actor.h"

Actor::Actor(std::string filename, float x, float y, int width, int height, Game* game)
{
	this->game = game;

	SDL_Surface* surface = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	// lo que mide el fichero
	this->fileWidth = width;
	this->fileHeight = height;

	// posición
	this->x = x;
	this->y = y;

	// lo que va a medir en el juego
	this->width = width;
	this->height = height;
}

void Actor::draw()
{
	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width;
	source.h = fileHeight; // texture.height;

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - width / 2;
	destination.y = y - height / 2;
	destination.w = width;
	destination.h = height;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer, 
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}