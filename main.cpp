/*
This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.
*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <memory>
#include <vector>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Position{
	int m_x, m_y;

	public:
	Position():Position(0,0){}
	Position(int p_x, int p_y): m_x(p_x),m_y(p_y){
	}
};

class GameObject_Abstract{
	private:
	Position position;

	public:
	GameObject_Abstract():GameObject_Abstract(0,0){

	}
	GameObject_Abstract(int x, int y){
		position = Position(x,y);
	}

	virtual void process(){

	}
	virtual void draw(){

	}
};




class GameObjectCollection{
	std::vector<std::shared_ptr<GameObject_Abstract>> m_gameObjects;

	public:
	void addGameObject(std::shared_ptr<GameObject_Abstract> gameObject){
		m_gameObjects.push_back(gameObject);
	}
};

class Game{
    private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Surface> mainSurface;
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
	 * @brief "Creates a Window for a game"
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

		isLooping(false){


		mainSurface = NULL;

		Initialize();

		window.reset(SDL_CreateWindow( m_title.c_str(), m_x, m_y, m_width, m_height, windowFlag));
		
		checkWindowIsNull();
		

		mainSurface.reset(SDL_GetWindowSurface(window.get()));

	}

	~Game(){
		SDL_Quit();
	}
	




	void run(){
		do{
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


};


int main( int argc, char* args[] )
{
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;


	Game game("Rectangulo que salta",100,100,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WindowFlags::SDL_WINDOW_OPENGL);

	game.run();

	return 0;
}