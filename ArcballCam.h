//
// Created by Camden Lyles-Smith on 10/6/23.
//

#ifndef LAB05_ARCBALLCAM_H
#define LAB05_ARCBALLCAM_H

#include <CSCI441/Camera.hpp>

class ArcballCam : public CSCI441::Camera {
public:
    explicit ArcballCam(GLfloat aspectRatio = 1.0f, GLfloat fovy = 45.0f, GLfloat nearClipPlane = 0.001f, GLfloat farClipPlane = 1000.0f);
    void recomputeOrientation() final;

    void moveForward(GLfloat movementFactor) final;
    void moveBackward(GLfloat movementFactor) final;
private:
    void _updateArcballCameraViewMatrix();
    void _clampRadius();
    GLfloat _minRad = 10.0f;
    GLfloat _maxRad = 100.0f;
    GLfloat _fovy;
    GLfloat _aspectRatio;
    GLfloat _nearClipPlane;
    GLfloat _farClipPlane;
};

#endif //LAB05_ARCBALLCAM_H
