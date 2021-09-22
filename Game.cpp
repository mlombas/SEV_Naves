#include "Game.h"
#include "GameLayer.h"

#include <iostream>
#include <string>

constexpr int MIN_TIME_PER_FRAME = 1000 / 30;

Game::Game() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error SDL_Init" << SDL_GetError() << std::endl;
	}
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) 
	{
		std::cout << "Error Window y Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(window, "Juego de Navecitas");
	// Escalado de imágenes de calidad 
	// https://wiki.libsdl.org/SDL_HINT_RENDER_SCALE_QUALITY
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	gameLayer = new GameLayer(this);

	loopActive = true; // bucle activo
	loop();
}

void Game::scale(){
	scaledToMax = !scaledToMax;

	if (scaledToMax) {
		SDL_DisplayMode PCdisplay;
		SDL_GetCurrentDisplayMode(0, &PCdisplay);
		float scaleX = (float)PCdisplay.w / (float)WIDTH;
		float scaleY = (float)PCdisplay.h / (float)HEIGHT;
		// Necesitamos la menor de las 2 escalas para no deformar el juego
		scaleLower = scaleX; 
		if (scaleY < scaleX) {
			scaleLower = scaleY;
		}
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, WIDTH * scaleLower, HEIGHT * scaleLower);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, scaleLower, scaleLower);
	}
	else { // Escala Original
		scaleLower = 1;
		// Cambiar dimensiones ventana
		SDL_SetWindowSize(window, WIDTH, HEIGHT);
		// Cambiar escala del render
		SDL_RenderSetScale(renderer, 1, 1);
	}

}

void Game::loop() 
{
	int initTick; // ms de inicio loop
	int endTick; // ms de fin de loop
	int differenceTick; // fin - inicio
	while (loopActive) 
	{
		initTick = SDL_GetTicks();

		gameLayer->processControls();
		gameLayer->update();
		gameLayer->draw();

		endTick = SDL_GetTicks();
		differenceTick = endTick - initTick;

		if (differenceTick < MIN_TIME_PER_FRAME) 
		{
			SDL_Delay(MIN_TIME_PER_FRAME - differenceTick);
		}
	}
}
