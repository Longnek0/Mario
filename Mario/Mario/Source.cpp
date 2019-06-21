#include <iostream>
#include <SDL.h>
#include "Constants.h"
#include <SDL_image.h>

/********************************************************************
Nguyen Huu Hung Long
15/6/2019
Source Code
Dung Quen Break
*********************************************************************/

//Global variable
SDL_Window* g_Window;
SDL_Renderer * g_Renderer;
SDL_Texture* g_Texture;
//Funtions prototype
bool Init();
bool Update();
void Render();
int angle = 0;
int rect_x;
//int rect_y;
//Funtion declaration

void CloseSDL()
{
	if (g_Texture != nullptr)
		SDL_DestroyTexture(g_Texture);
	g_Texture = nullptr;
	if (g_Renderer != nullptr)
		SDL_DestroyRenderer(g_Renderer);
	g_Renderer = nullptr;
	if (g_Window != nullptr)	
		SDL_DestroyWindow(g_Window);
	g_Window = nullptr;

	SDL_Quit();
}
bool Init()
{
	bool success = false;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
		printf("Error%s\n", SDL_GetError());
	}
	SDL_Window*g_Window = SDL_CreateWindow("Mario",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_FULLSCREEN);
	if (g_Window != nullptr)
	{
		g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED);
		
		if (g_Renderer != nullptr)
		{
			int flag = IMG_INIT_PNG|IMG_INIT_JPG;
			if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & flag )
			{
				
				SDL_Surface* pSurface = IMG_Load("Images/Quocanh.jpg");
				if (pSurface != nullptr)
				{
					g_Texture = SDL_CreateTextureFromSurface(g_Renderer, pSurface);
					if (g_Texture != nullptr)
					{
						success = true;
					}
					else
					{
						success = false;
						printf("Error%s\n", SDL_GetError());
					}
				}
				else
				{
					success = false;
					printf("Could Not Init Surface%s\n", SDL_GetError());
				}
				if (pSurface != nullptr)
				{
					SDL_FreeSurface(pSurface);
					pSurface = nullptr;
				}
				success = true;
			}
			else
			{
				success = false;
				printf("Could Not Init PNG%s\n", IMG_GetError());
			}
			success = true;
		}
		else
		{
			success = false;
			printf("Could not create renderer %s\n", SDL_GetError);
		}
		
		success = true;
	}
	else
	{
		success = false;
		printf("Could not create window%s\n", SDL_GetError);
	}
	return success;
}
bool Update()
{
	bool success = false;
	//handle event
	SDL_Event e;

	//Get event
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		
		if (e.button.clicks>1)
		{
			success = true;
		}
		break;
		case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
			case SDLK_q:
			success = true;
			break;
			case SDLK_UP:
			angle += 15;
			break;
			case SDLK_DOWN:
			angle -= 15;
			break;
			case SDLK_RIGHT:
			rect_x += 10;
			break;
			case SDLK_LEFT:
			rect_x -= 10;
			break;
		default:
			break;
		}		
		break;
	case SDL_QUIT:
		success = true;
		break;
	default:
		break;
	}
	
	return success;
}
void Render()
{
	SDL_SetRenderDrawColor(g_Renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_Renderer);
	
	SDL_Rect rect = { rect_x , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	SDL_RenderCopyEx(g_Renderer, g_Texture, nullptr, &rect, angle , nullptr, SDL_FLIP_NONE);
	
	SDL_RenderPresent(g_Renderer);
	
}


int main(int argc, char *argv[])
{
	bool isQuit = false;
	if (!Init())
	{
	
	}
	else
	{
		while(!isQuit)
		{
			Render();
			isQuit =Update();
		}		
	}
	
	CloseSDL();
	system("pause");
	return 0;
}