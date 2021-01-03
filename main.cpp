/*
This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.
*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "libs/whitecat/GameObjects.hpp"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;





class Game{
    private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::shared_ptr<SDL_Surface> mainSurface;
	std::shared_ptr<SDL_Renderer> mainRenderer;
	std::string m_title;

	bool isLooping;

	int m_x;
	int m_y;
	int m_width;
	int m_height;

    void Initialize(){
        if (SDL_Init(SDL_INIT_VIDEO) < 0){
			throw "SDL could not initialize! SDL_Error: "+ std::string(SDL_GetError());
        }
    }

	void checkWindowIsNull(){
		if(window == NULL){
			throw "Window couldn't be created!" + std::string(SDL_GetError());
		}
	}

    public:
	GameObjectCollection gameObjects;


	/**
	 * @brief "Creates a Window for a game"zael1002
: y por que programas un juego? por gusto y ya me imagino
azael1002
: mejor en el Unreal Engine
azael1002
: o con el Roblox studio GlitchCat
azael1002
: y por que ahora strim por tuitch y no por fb?
azael1002
: el rectangulo y escenario lo haras en paint ?
	 * 
	 * @param title {string} of the window title
	 * @param p_x {int} X coordinate of the window in the screen 
	 * @param p_y {int} Y coordinate of the window in the screen
	 * @param windowFlag {SDL_WindowFlags} which flag to use to create the new window
	*/
    Game(std::string title, int p_x, int p_y, int p_width, int p_height, SDL_WindowFlags windowFlag):
		m_title(title),	m_x(p_x),
		m_y(p_y),		m_width(p_width),
		m_height(p_height),
		window(nullptr, SDL_DestroyWindow),

		isLooping(false),	mainRenderer(nullptr, SDL_DestroyRenderer){


		mainSurface = NULL;

		Initialize();

		window.reset(SDL_CreateWindow( m_title.c_str(), m_x, m_y, m_width, m_height, windowFlag));
		
		checkWindowIsNull();
		
		//mainRenderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED),&SDL_DestroyRenderer);
		mainSurface.reset(SDL_GetWindowSurface(window.get()), &SDL_FreeSurface);
		
	}

	~Game(){
		SDL_Quit();
	}
	



	void addGameObject(std::shared_ptr<GameObject_Abstract> gameObject){
		gameObjects.addGameObject(gameObject);
	}

	void run(){
		do{

			for(auto & gameObject: gameObjects.get()){
				gameObject->draw(mainSurface, mainRenderer);
			}
			SDL_FillRect(mainSurface.get(), NULL, SDL_MapRGB(mainSurface->format,25,25,25));
			
			SDL_UpdateWindowSurface(window.get());


			SDL_Delay(3000);
		
		}while(isLooping);
	}
};




class JumpingRectangle: public GameObject_Abstract{
	public:
	JumpingRectangle(int x, int y):GameObject_Abstract(x,y){
	}

	void draw(std::shared_ptr<SDL_Surface> surface, std::shared_ptr<SDL_Renderer> renderer) override{
		auto rectangle = std::make_shared<SDL_Rect>();

		SDL_RenderClear(renderer.get());
		
		rectangle->h = GameObject_Abstract::m_height;
		rectangle->w = GameObject_Abstract::m_width;
		rectangle->x = GameObject_Abstract::position.getX();
		rectangle->y = GameObject_Abstract::position.getY();

		SDL_SetRenderDrawColor(renderer.get(), 255,255,255,255);
		SDL_RenderDrawRect(renderer.get(), rectangle.get());

		SDL_SetRenderDrawColor(renderer.get(), 0,0,0,255);
		SDL_RenderPresent(renderer.get());
	}

};


int main( int argc, char* args[] )
{
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;

	std::shared_ptr<JumpingRectangle> rectangle = std::make_shared<JumpingRectangle>(WINDOW_WIDTH/2, WINDOW_WIDTH/2);

	Game game("Rectangulo que salta",100,100,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WindowFlags::SDL_WINDOW_OPENGL);
	
	game.addGameObject(rectangle);
	
	game.run();

	return 0;
}