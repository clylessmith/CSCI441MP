#include "Peanut.h"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

Peanut::Peanut( GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {

    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;

    _legAngle = 0.0f;
    _reverseDirection = false;

    _colorTorso = glm::vec3(0.749, 0.561, 0.165);
    _scaleTorso = glm::vec3( 0.5f, 1.5f, 1.0f );

    _colorHead = glm::vec3(0.922, 0.851, 0.698);
    _scaleHead = glm::vec3( 0.75f, 0.75f, 0.75f );

    _colorLeg = glm::vec3(0.612, 0.035, 0.18);
    _scaleLeg = glm::vec3(0.5, 1.5, 0.5);

    _scaleHat = glm::vec3(0.75f, 1.5f, 0.75f);
}

void Peanut::drawPeanut( glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    modelMtx = glm::scale(modelMtx, glm::vec3(30.0f,30.0f, 30.0f));
    _drawTorso(modelMtx, viewMtx, projMtx);
    _drawArm(true, modelMtx, viewMtx, projMtx);
    _drawArm(false, modelMtx, viewMtx, projMtx);
    _drawLeg(true, modelMtx, viewMtx, projMtx);
    _drawLeg(false, modelMtx, viewMtx, projMtx);
    _drawHead(modelMtx, viewMtx, projMtx);
    _drawHat(modelMtx, viewMtx, projMtx);
}


void Peanut::recomputeOrientation() {
    // compute direction vector based on spherical to cartesian conversion
    _charDirection.x =  glm::sin(_charTheta );
    _charDirection.z = -glm::cos(_charTheta );

    // and normalize this directional vector!
    _charDirection = glm::normalize(_charDirection );
}

void Peanut::moveForward() {
    _charPosition += _charDirection * 0.1f;
    if (_legAngle > _PI / 2.0f) {
        _legAngle = -_PI / 16.0f;
    }
    else if (_legAngle < -_PI / 2.0f) {
        _legAngle = _PI / 16.0f;
    }
    if (_legAngle > 0.0f) {
        _legAngle += _PI / 16.0f;
    }
    else {
        _legAngle -= _PI / 16.0f;
    }
}

void Peanut::moveBackward() {
    _charPosition -= _charDirection * 0.1f;
    if (_legAngle > _PI / 2.0f) {
        _legAngle = -_PI / 16.0f;
    }
    else if (_legAngle < -_PI / 2.0f) {
        _legAngle = _PI / 16.0f;
    }
    if (_legAngle > 0.0f) {
        _legAngle += _PI / 16.0f;
    }
    else {
        _legAngle -= _PI / 16.0f;
    }
}

void Peanut::rotate(const GLfloat theta) {
    _charTheta += theta;
    recomputeOrientation();
}


void Peanut::_drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::translate(modelMtx, glm::vec3(0.0f,0.34f,0.0f));
    modelMtx = glm::scale( modelMtx, _scaleHead );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorHead[0]);

    CSCI441::drawSolidCube(0.1f);
}

void Peanut::_drawArm(bool isLeftArm, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::rotate( modelMtx, (float)M_PI/2, CSCI441::Z_AXIS );

    if (isLeftArm)
        modelMtx = glm::translate(modelMtx, glm::vec3(0.275f,0.05f,0.075f));
    else
        modelMtx = glm::translate(modelMtx, glm::vec3(0.275f,0.05f,-0.075f));

    modelMtx = glm::scale( modelMtx, _scaleLeg );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorLeg[0]);

    CSCI441::drawSolidCube(0.1f);
}

void Peanut::_drawTorso(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::translate(modelMtx, glm::vec3(0.0f, 0.225f, 0.0f));
    modelMtx = glm::scale(modelMtx, _scaleTorso);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorTorso[0]);

    CSCI441::drawSolidCube( 0.1f);
}

void Peanut::_drawHat(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::rotate(modelMtx, _PI / 4.0f, CSCI441::Y_AXIS);
    modelMtx = glm::translate(modelMtx, glm::vec3(0.0f, 0.37f, 0.0f));
    modelMtx = glm::scale(modelMtx, _scaleHat);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorLeg[0]);

    CSCI441::drawSolidCone(0.1f, 0.1f, 1.0f, 4.0f);
}


void Peanut::_drawLeg(bool isLeftLeg, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    if (isLeftLeg) {
        modelMtx = glm::translate(modelMtx, glm::vec3(0.0f, 0.15f, 0.025f));
        modelMtx = glm::rotate(modelMtx, _legAngle - _PI_OVER_2, CSCI441::Z_AXIS);
        modelMtx = glm::translate(modelMtx, glm::vec3(0.0f, -0.075f, 0.0f));
    }
    else {
        modelMtx = glm::translate(modelMtx, glm::vec3(0.0f,0.15f,-0.025f));
        modelMtx = glm::rotate(modelMtx, _legAngle, CSCI441::Z_AXIS);
        modelMtx = glm::translate(modelMtx, glm::vec3(0.0f, -0.075f, 0.0f));
    }
    modelMtx = glm::scale( modelMtx, _scaleLeg );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorLeg[0]);

    CSCI441::drawSolidCube( 0.1f );
}

void Peanut::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}
