/* 
 * File:   GameInterface.hpp
 * Author: Ale Strooisma
 *
 * Created on June 7, 2015, 7:53 PM
 */

#ifndef GAMEINTERFACE_HPP
#define	GAMEINTERFACE_HPP

#include <glm/mat4x4.hpp>

class Game3D;

/**
 * This interface provides access to the game loop. An instance of this interface
 * must be passed to the `Game3D` constructor.
 */
class GameInterface {
public:
	virtual ~GameInterface() {};
	/**
	 * This method can be used to get a way to access the `Game3D` object. It is 
	 * called before the game loop starts and before `init` is called.
	 * 
     * @param game the `Game3D` object running this game
     */
	virtual void setGame(Game3D* game) = 0;
	/**
	 * This method is called just before the game loop starts, but after the 
	 * OpenGL context is initialized.
	 * Immediately after this function terminates, the window is made visible 
	 * and the game loop starts.
     */
	virtual void init() = 0;
	/**
	 * This function is called each iteration of the game loop and should be 
	 * implemented to update the game state.
	 * 
     * @param dt the time since the last update call, in seconds
     */
	virtual void update(double dt) = 0;
	/**
	 * This function is called each iteration of the game loop and should be 
	 * implemented to render the elements in the 3D space.
	 * 
	 * The base matrix passed to this function contains the world-to-camera 
	 * transformation, so the model-to-camera matrix that must be passed to the 
	 * shaders/renderer has to be calculated by multiplying the base matrix with
	 * the model-to-world matrix.
	 * 
     * @param base the base matrix from which the model-to-camera matrix should 
	 * be calculated
     */
	virtual void renderWorld(glm::mat4 base) = 0;
	/**
	 * This function is called each iteration of the game loop and should be 
	 * implemented to render the GUI overlay.
	 * 
	 * In contrast to `renderWorld`, the matrix passed to this function does not 
	 * include the world-to-camera transformation, so elements rendered in this 
	 * function will be rendered with an orthogonal projection. In addition, 
	 * elements rendered in this function will always be rendered over elements 
	 * rendered in `renderWorld`.
	 * 
     * @param base the base matrix from which the model-to-camera matrix should 
	 * be calculated
     */
	virtual void renderHUD(glm::mat4 base) = 0;
	/**
	 * This function is called whenever the game loop ends, be it in a normal or
	 * exceptional way, so it should be used to clean up resources created in 
	 * the `init` function.
     */
	virtual void shutdown() = 0;
	/**
	 * Implement this function to return `true` whenever the program should stop 
	 * running. This is checked before each iteration of the game loop.
     * @return `true` if the program should stop
     */
	virtual bool shouldStop() = 0;
	/**
	 * Every iteration, just before rendering this function is called to account
	 * for effects of a window resize.
	 * Most likely this can be left empty, because the engine handles resizing.
	 * One exception is when extra cameras are defined. In that case you need to
	 * call `yourCamera.updateAspect(width, height)` here.
	 * 
     * @param width the new window width
     * @param height the new window height
     */
	virtual void windowResized(int width, int height) = 0;
	/**
	 * @brief This function is called whenever the user tries to close the 
	 * window. The window will only actually close if this function returns true.
	 * 
	 * Note that this is not called when the window closes because shouldStop
	 * returns true.
	 * 
     * @return 
     */
	virtual bool windowClosed() = 0;
};

#endif	/* GAMEINTERFACE_HPP */

