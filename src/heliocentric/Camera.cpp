/* 
 * File:   Camera.cpp
 * Author: Ale Strooisma
 * 
 * Created on June 11, 2015, 7:39 PM
 */

#define GLM_FORCE_RADIANS
#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : Camera(0.001f, 100, 1) {
}

Camera::Camera(float zNear, float zFar, float frustumScale) : worldToCamera(), cameraToClip(0.0f), orientation(), position() {
	setRanges(zNear, zFar);
	setFrustumScale(frustumScale);
	cameraToClip[2][3] = -1;
	dirChanged = true;
	posChanged = true;
}

Camera::~Camera() {
}

mat4 Camera::getWorldToClipMatrix() {
	return getCameraToClipMatrix() * getWorldToCameraMatrix();
}

mat4 Camera::getCameraToClipMatrix() {
	return cameraToClip;
}

mat4 Camera::getWorldToCameraMatrix() {
	if (posChanged || dirChanged) {
		if (dirChanged) {
			worldToCameraRot = glm::mat4_cast(orientation);
		}
		worldToCamera = translate(worldToCameraRot, -getPosition());
		posChanged = false;
		dirChanged = false;
	}
	return worldToCamera;
}

void Camera::setRanges(float zNear, float zFar) {
	this->zNear = zNear;
	this->zFar = zFar;
	cameraToClip[2][2] = (zFar + zNear) / (zNear - zFar);
	cameraToClip[3][2] = (2 * zFar * zNear) / (zNear - zFar);
}

float Camera::getZNear() {
	return zNear;
}

float Camera::getZFar() {
	return zFar;
}

void Camera::setFOV(float fov) {
	const float degToRad = 3.14159f / 180.0f;
    setFrustumScale(1.0f / tan(fov * degToRad / 2.0f));
}

void Camera::setFrustumScale(float frustumScale) {
	this->frustumScale = frustumScale;
}

float Camera::getFrustumScale() {
	return frustumScale;
}

void Camera::updateAspect(int width, int height) {
	cameraToClip[0][0] = frustumScale * ((float) height / (float) width);
	cameraToClip[1][1] = frustumScale;
}

vec3 Camera::getPosition() {
	return position;
}