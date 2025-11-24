#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "PongClasses.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main() 
{
	// Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("Pong", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	// Initialize the font
	TTF_Font* scoreFont = TTF_OpenFont("DejavuSansMono.ttf", 40);

	SDL_Color scoreColor = { 255, 255, 255, 255 };

	// Create the player score text fields
	PlayerScore playerOneScoreText(Vec2(WINDOW_WIDTH / 4, 20), renderer, scoreFont, scoreColor);

	PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer, scoreFont, scoreColor);

	// Create the ball
	Ball ball(
		Vec2((WINDOW_WIDTH / 2.0f) - (BALL_WIDTH / 2.0f), (WINDOW_HEIGHT / 2.0f) - (BALL_WIDTH / 2.0f)));

	// Create the paddles
	Paddle paddleOne(
		Vec2(50.0f, (WINDOW_HEIGHT / 2.0f) - (PADDLE_HEIGHT / 2.0f)));

	Paddle paddleTwo(
		Vec2(WINDOW_WIDTH - 50.0f, (WINDOW_HEIGHT / 2.0F) - (PADDLE_HEIGHT / 2.0F)));

	// Game logic
	{
		bool running = true;

		// Continue looping and processing events until user exits
		while (running) 
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_EVENT_KEY_DOWN)
				{
					if (event.key.key == SDLK_ESCAPE)
					{
						running = false;
					}
				}
			}
			// Clear the window to black
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);

			// Set the draw color to be white
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			
			// Draw the net
			for (int y = 0; y < WINDOW_HEIGHT; ++y)
			{
				if (y % 5 == 0)
				{
					SDL_RenderPoint(renderer, WINDOW_WIDTH / 2, y);
				}
			}
			
			// Draw the ball
			ball.Draw(renderer);

			// Draw the paddles
			paddleOne.Draw(renderer);
			paddleTwo.Draw(renderer);

			// Display the scores
			playerOneScoreText.Draw();
			playerTwoScoreText.Draw();

			// Present the backbuffer
			SDL_RenderPresent(renderer);
		}
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(scoreFont);
	TTF_Quit();
	SDL_Quit();
	
	return 0;
}
