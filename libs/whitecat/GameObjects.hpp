#ifndef GAMEOBJECTS_HPP_
#define GAMEOBJECTS_HPP_

#include <vector>
#include <memory>
#include <iostream>
#include <SDL2/SDL.h>

class GameObjectCollection{
	std::vector<std::shared_ptr<GameObject_Abstract>> m_gameObjects;

	public:
	void addGameObject(std::shared_ptr<GameObject_Abstract> gameObject){
		m_gameObjects.push_back(gameObject);
	}

	std::vector<std::shared_ptr<GameObject_Abstract>> get(){
		return m_gameObjects;
	}
};


class Position{
	int m_x, m_y;

	public:
	Position():Position(0,0){}
	Position(int p_x, int p_y): m_x(p_x),m_y(p_y){
	}

	int getX(){ return m_x;}
	int getY(){ return m_y;}
};




class GameObject_Abstract{
	private:
	protected:
	int m_width, m_height;

	public:
	Position position;


	GameObject_Abstract():GameObject_Abstract(0,0){

	}
	GameObject_Abstract(int x, int y):
	GameObject_Abstract(x, y, 50, 50){

	}
	
	GameObject_Abstract(int x, int y, int p_width, int p_height):
	m_width(p_width), m_height(p_height){
		position = Position(x,y);
	}

	virtual void process(){

	}
	virtual void draw(std::shared_ptr<SDL_Surface>, std::shared_ptr<SDL_Renderer>)=0;
};

#endif