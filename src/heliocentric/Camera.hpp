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

class Camera {
	mat4 cameraToClip, worldToCamera, worldToCameraRot;
	// Perspective data
	float frustumScale, zNear, zFar;
	// Orientation data
	vec3 position;
	float fPan, fTilt, fRoll;
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
	void setPosition(vec3 position);
	vec3 getPosition();
	void move(vec3 translation);
	void moveRelative(vec3 translation);
	void move(float x, float y, float z);
	void moveRelative(float x, float y, float z);
	// Orientation functions
	void resetOrientation();
	void pan(float angle);
	void tilt(float angle);
	void roll(float angle);
};

#endif	/* CAMERA_HPP */

