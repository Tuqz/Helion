/* 
 * File:   Camera.hpp
 * Author: Ale Strooisma
 *
 * Created on June 11, 2015, 7:39 PM
 */

#ifndef CAMERA_HPP
#define	CAMERA_HPP

#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

using namespace glm;

/**
 * A camera object for defining the perspective from which the world should be 
 * rendered. The viewpoint (position of the camera) and viewing direction 
 * (orientation of the camera) can be controlled, as well as properties of the 
 * perspective projection such as the FOV and aspect ration, but also the near 
 * and far rendering limits.
 * 
 * Note that camera space is defined such that for the viewer, the positive x-
 * axis points to the right, the positive y-axis point up, and the *negative* 
 * z-axis points into the screen.
 */
class Camera {
	mat4 cameraToClip, worldToCamera, worldToCameraRot;
	// Perspective data
	float frustumScale, zNear, zFar;
	// Orientation data
	vec3 position;
	quat orientation;
	bool dirChanged, posChanged;
public:
	Camera();
	Camera(const Camera& orig);
	virtual ~Camera();
	Camera(float zNear, float zFar, float frustumScale);
	
	// Matrix getters
	mat4 getWorldToClipMatrix();
	mat4 getCameraToClipMatrix();
	mat4 getWorldToCameraMatrix();
	
	// Perspective functions
	void setRanges(float zNear, float zFar);
	float getZNear();
	float getZFar();
	void setFOV(float fov);
	void setFrustumScale(float frustumScale);
	float getFrustumScale();
	void updateAspect(int width, int height);
	
	// Position functions
	/**
	 * Set the world-space position of the camera.
	 * 
     * @param position the new camera position
     */
	void setPosition(vec3 position);
	/**
	 * Returns the camera's world-space position.
	 * 
     * @return the camera position
     */
	vec3 getPosition();
	/**
	 * Move the camera as described by the given vector, in world space.
	 * In other words, this movement is independent of the orientation of the 
	 * camera.
	 * 
     * @param translation how far and in what direction the camera should move
     */
	void move(vec3 translation);
	/**
	 * Move the camera as described by the given vector, in camera space.
	 * So `moveRelative(vec3(a,b,c))` moves the camera `a` to the right, `b` to 
	 * upwards and `c` backwards.
	 * 
     * @param translation how far and in what direction the camera should move
     */
	void moveRelative(vec3 translation);
	/**
	 * Move the camera as described by the given vector components, in world 
	 * space.
	 * In other words, this movement is independent of the orientation of the 
	 * camera. 
	 * This call is identical to `move(vec3(x,y,z))`.
	 * 
     * @param x how far the camera should move along the world x-axis
     * @param y how far the camera should move along the world y-axis
     * @param z how far the camera should move along the world z-axis
     */
	void move(float x, float y, float z);
	/**
	 * Move the camera as described by the given vector components, in camera 
	 * space.
	 * So `moveRelative(a,b,c)` moves the camera `a` to the right, `b` to 
	 * upwards and `c` backwards. This is identical to 
	 * `moveRelative(vec3(a,b,c))`.
	 * 
     * @param x how far the camera should move along the camera x-axis
     * @param y how far the camera should move along the camera y-axis
     * @param z how far the camera should move along the camera z-axis
     */
	void moveRelative(float x, float y, float z);
	
	// Orientation functions
	/**
	 * Makes the camera point down the negative z-axis.
     */
	void resetOrientation();
	/**
	 * Rotate the camera over the positive y-axis, which means a negative angle 
	 * turns the camera left, and a positive angle turns the camera right.
	 * 
     * @param angle how far the camera should be rotated in radians
     */
	void pan(float angle);
	/**
	 * Rotate the camera over the negative x-axis, which means a negative angle 
	 * turns the camera down, and a positive angle turns the camera up.
	 * 
     * @param angle how far the camera should be rotated in radians
     */
	void tilt(float angle);
	/**
	 * Rotate the camera over the positive z-axis.
	 * 
     * @param angle how far the camera should be rotated in radians
     */
	void roll(float angle);
};

#endif	/* CAMERA_HPP */

