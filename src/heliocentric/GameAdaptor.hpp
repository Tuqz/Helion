/* 
 * File:   GameAdaptor.hpp
 * Author: Ale Strooisma
 *
 * Created on July 31, 2015, 7:34 PM
 */

#ifndef GAMEADAPTOR_HPP
#define	GAMEADAPTOR_HPP

#include "GameInterface.hpp"

/**
 * An implementation of GameInterface that has an empty implementation of all 
 * methods. `shouldStop` always returns `true` and `windowClosed` always returns
 * `true`. Additionally a pointer to a `Game3D`-type is provided as a member 
 * variable, including a getter and setter, the latter of which is required.
 */
class GameAdaptor : public GameInterface {
protected:
	Game3D* game;
public:
	GameAdaptor();
	GameAdaptor(const GameAdaptor& orig) = delete;
	virtual ~GameAdaptor();
	virtual void init();
	virtual void update(double dt);
	virtual void renderHUD(glm::mat4 base);
	virtual void renderWorld(glm::mat4 base);
	virtual void shutdown();
	virtual bool shouldStop();
	virtual void windowResized(int width, int height);
	virtual bool windowClosed();
	virtual Game3D* getGame() const {
		return game;
	}
	virtual void setGame(Game3D* game) {
		this->game = game;
	}
};

#endif	/* GAMEADAPTOR_HPP */

