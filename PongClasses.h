#pragma once
#include <cstring> // for strlen

class Vec2
{
public:
	Vec2()
		: x(0.0f), y(0.0f)
	{}

	Vec2( float x, float y )
		: x(x), y(y)
	{}

	Vec2 operator+(Vec2 const& rhs)
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2& operator+=(Vec2 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vec2 operator*(float rhs)
	{
		return Vec2(x * rhs, y * rhs);
	}

	float x, y;
};

static constexpr int BALL_WIDTH = 15;
static constexpr int BALL_HEIGHT = 15;

class Ball
{
public:
	Ball(Vec2 position)
		: position(position)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = BALL_WIDTH;
		rect.h = BALL_HEIGHT;
	}

	void Draw(SDL_Renderer* renderer)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);

		SDL_RenderFillRect(renderer, &rect);
	}

	Vec2 position;
	SDL_FRect rect{};
};

static constexpr int PADDLE_WIDTH = 20;
static constexpr int PADDLE_HEIGHT = 100;

class Paddle
{
public:
	Paddle(Vec2 position)
		: position(position)
	{
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = PADDLE_WIDTH;
		rect.h = PADDLE_HEIGHT;
	}

	void Draw(SDL_Renderer* renderer)
	{
		rect.y = static_cast<int>(position.y);

		SDL_RenderFillRect(renderer, &rect);
	}

	Vec2 position;
	SDL_FRect rect{};
};

class PlayerScore
{
public:
	PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) :renderer(renderer), font(font), color(color)
	{
		
		surface = TTF_RenderText_Solid(font, "0", strlen("0"), SDL_Color{ 255,255,255,255 });
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		float width, height;
		SDL_GetTextureSize(texture, &width, &height);

		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = width;
		rect.h = height;
	}

	~PlayerScore()
	{
		SDL_DestroySurface(surface);
		SDL_DestroyTexture(texture);
	}

	void Draw()
	{
		SDL_RenderTexture(renderer, texture, nullptr, &rect);
	}

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface{};
	SDL_Texture* texture{};
	SDL_FRect rect{};

};