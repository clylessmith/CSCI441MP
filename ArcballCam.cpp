//
// Created by Camden Lyles-Smith on 10/6/23.
//


#include <iostream>
#include "ArcballCam.h"

ArcballCam::ArcballCam(const GLfloat aspectRatio,
        const GLfloat fovy,
        const GLfloat nearClipPlane,
        const GLfloat farClipPlane
) : _fovy(fovy),
    _aspectRatio(aspectRatio),
    _nearClipPlane(nearClipPlane),
    _farClipPlane(farClipPlane)
{
    mProjectionMatrix = glm::perspective(_fovy, _aspectRatio, _nearClipPlane, _farClipPlane);
}

void ArcballCam::recomputeOrientation() {
    mCameraDirection.x = glm::sin(mCameraTheta) * glm::sin(mCameraPhi) * mCameraRadius;
    mCameraDirection.y = -glm::cos(mCameraPhi) * mCameraRadius;
    mCameraDirection.z = -glm::cos(mCameraTheta) * glm::sin(mCameraPhi) * mCameraRadius;
    

    _updateArcballCameraViewMatrix();
}

void ArcballCam::moveForward(GLfloat movementFactor) {
    mCameraRadius -= movementFactor;
    _clampRadius();
    recomputeOrientation();
}

void ArcballCam::moveBackward(GLfloat movementFactor) {
    mCameraRadius += movementFactor;
    _clampRadius();
    recomputeOrientation();
}

void ArcballCam::_updateArcballCameraViewMatrix() {
    setPosition(mCameraLookAtPoint + mCameraDirection);
    computeViewMatrix();
}

void ArcballCam::_clampRadius() {
    mCameraRadius = glm::clamp(mCameraRadius, _minRad, _maxRad);
}

