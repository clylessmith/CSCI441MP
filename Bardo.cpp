#include "Bardo.h"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>
#include <iostream>

Bardo::Bardo(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {
    _bardoAngle = 0.0f;

    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;

    _rotatePlaneAngle = _PI / 2.0f;

    //info for body
    _colorBody = glm::vec3 (0.38, 0.61, 0.96);
    _scaleBody = glm::vec3( 25.0f, 25.0f, 25.0f );
    _scaleBodyBottom = glm::vec3( 1.4f, 0.5f, 2.0f );
    _bottomBodyTrans = glm::vec3(0.0f, -0.05f, 0.025f);

    //info for head
    _colorHead = glm::vec3(0.95, 0.85, 0.74 );
    _scaleHead = glm::vec3(15.0f, 18.0f, 15.0f );
    _transHead = glm::vec3(0.0f, 0.15f, 0.0f);

    //info for beard
    _colorBeard = glm::vec3(0.78, 0.78, 0.78 );
    _scaleBeard = glm::vec3(17.0f, 6.0f, 19.0f);
    _transBeard = glm::vec3(0.0f, 0.18f, -0.01f);
    _scaleSideBeard = glm::vec3(1.0f, 3.7f, 0.4f);
    _transSideBeard = glm::vec3(0.0f, 0.073f, 0.2f);

    //info for hat
    _hatMiddleColor = glm::vec3( 0.17, 0.46, 1.0 );
    _scaleHatBottom = glm::vec3(48.0f, 13.0f, 48.0f );
    _transHatBottom = glm::vec3(0.0f, 0.38f, 0.01f );

    _scaleHatMiddle = glm::vec3(0.9f, 0.9f, 0.9f);
    _transHatMiddle = glm::vec3(0.0f, 0.05f, 0.0f);

    _scaleHatTop = glm::vec3(1.0f, 5.0f, 1.0f);
    _transHatTop = glm::vec3(0.0f, 0.01f, 0.0f);

    _staffColor = glm::vec3(0.63f, 0.32f, 0.18f);
    _scaleStaffBottom = glm::vec3(5.0f, 80.0f, 5.0f);
    _transStaffBottom = glm::vec3(0.5f, 0.04f, -0.5f);
    _scaleStaffMiddle = glm::vec3(1.0f, 0.4f, 1.0f);
    _transStaffMiddle = glm::vec3(0.0f, 0.15f, 0.05f);
    _scaleStaffTop = glm::vec3(1.0f, 0.2f, 4.0f);
    _transStaffTop = glm::vec3(0.0f, 0.195f, -0.05f);

    _transHand = glm::vec3(0.0f, -1.2f, 0.05f);
    _scaleHand = glm::vec3(1.4f, 1.0f, 0.6f);

    _orbColor = glm::vec3(0.85f, 0.61f, 1.0f);
    _scaleOrb = glm::vec3(2.0f, 1.8f, 0.8f);
    _transOrb = glm::vec3(0.0f, 0.53f, -0.06f);


}

void Bardo::drawBardo(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans, float orbAngle, float orbHover ) {
    modelMtx = glm::rotate( modelMtx, -_rotatePlaneAngle, CSCI441::Y_AXIS );
    modelMtx = glm::translate(modelMtx, glm::vec3(
                                                  glm::cos(_bardoAngle),
                                                  0.2,
                                                  glm::sin(_bardoAngle)));
    _drawBardoBody(modelMtx, viewMtx, projMtx);        // Bardo's body
    _drawHead(modelMtx, viewMtx, projMtx);
    _drawBeard(modelMtx, viewMtx, projMtx);        // Bardo's beard and hair
    _drawHat(modelMtx, viewMtx, projMtx, idleTrans);   // Bardo's hat
    _drawStaff(modelMtx, viewMtx, projMtx, idleTrans * 0.5, orbAngle, orbHover);   // Bardo's magic staff
}

void Bardo::moveForward(GLfloat thetaIn, GLfloat worldSize, glm::vec2 moveSpeed) {
    if(_bardoAngle > _2PI ) _bardoAngle -= _2PI;
    // _bardoAngle += thetaIn;
    
    float xMove = coords[0] + glm::cos(_bardoAngle) * moveSpeed.x;
    float zMove = coords[2] - glm::sin(_bardoAngle) * moveSpeed.x;

    if (xMove <= -worldSize || xMove >= worldSize) {
        xMove = coords[0];
    }
    if (zMove <= -worldSize || zMove >= worldSize) {
        zMove = coords[2];
    }
    coords = glm::vec3(xMove,
                            coords[1],
                            zMove);
}

void Bardo::moveBackward(GLfloat thetaIn, GLfloat worldSize, glm::vec2 moveSpeed) {
    if(_bardoAngle < 0.0f ) _bardoAngle += _2PI;
    // _bardoAngle += thetaIn;

    float xMove = coords[0] - glm::cos(_bardoAngle) * moveSpeed.x;
    float zMove = coords[2] + glm::sin(_bardoAngle) * moveSpeed.x;

    if (xMove <= -worldSize || xMove >= worldSize) {
        xMove = coords[0];
    }
    if (zMove <= -worldSize || zMove >= worldSize) {
        zMove = coords[2];
    }
    coords = glm::vec3(xMove,
                            coords[1],
                            zMove);
}

void Bardo::rotate(GLfloat thetaIn) {
    _bardoAngle += thetaIn;
}

void Bardo::_drawBardoBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    glm::mat4 modelMtx1 = glm::scale( modelMtx, _scaleBody );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorBody[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::mat4 modelMtx2 = glm::scale( modelMtx1, _scaleBodyBottom );
    modelMtx2 = glm::translate(modelMtx2, _bottomBodyTrans);

    _computeAndSendMatrixUniforms(modelMtx2, viewMtx, projMtx);

    CSCI441::drawSolidCube(0.1f);
}

void Bardo::_drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::scale(modelMtx, _scaleHead );
    modelMtx = glm::translate(modelMtx, _transHead);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorHead[0]);

    CSCI441::drawSolidCube(0.2f);
}

void Bardo::_drawBeard(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::scale(modelMtx, _scaleBeard);
    modelMtx = glm::translate( modelMtx, _transBeard);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorBeard[0]);

    CSCI441::drawSolidCube(0.2f);

    modelMtx = glm::scale(modelMtx, _scaleSideBeard);
    modelMtx = glm::translate( modelMtx, _transSideBeard);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    CSCI441::drawSolidCube(0.2f);
}

void Bardo::_drawHat(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans ) const {
    glm::vec3 _transHatBottomAnimate = glm::vec3(_transHatBottom[0], _transHatBottom[1] + idleTrans, _transHatBottom[2]);

    modelMtx = glm::scale(modelMtx, _scaleHatBottom);
    modelMtx = glm::translate(modelMtx, _transHatBottomAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorBody[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::vec3 _transHatMiddleAnimate = glm::vec3(_transHatMiddle[0], _transHatMiddle[1] + idleTrans, _transHatMiddle[2]);

    modelMtx = glm::scale(modelMtx, _scaleHatMiddle);
    modelMtx = glm::translate(modelMtx, _transHatMiddleAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_hatMiddleColor[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::vec3 _transHatTopAnimate = glm::vec3(_transHatTop[0], _transHatTop[1] + idleTrans/10, _transHatTop[2]);

    modelMtx = glm::scale(modelMtx, _scaleHatTop);
    modelMtx = glm::translate(modelMtx, _transHatTopAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorBody[0]);

    CSCI441::drawSolidCone( 0.05f, 0.1f, 16, 16 );
}

void Bardo::_drawStaff(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans, float orbAngle, float orbHover) const {
    glm::vec3 _transStaffBottomAnimate = glm::vec3(_transStaffBottom[0], _transStaffBottom[1] + idleTrans * 0.5, _transStaffBottom[2]);

    modelMtx = glm::scale(modelMtx, _scaleStaffBottom);
    modelMtx = glm::translate(modelMtx, _transStaffBottomAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_staffColor[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::vec3 _transStaffMiddleAnimate = glm::vec3(_transStaffMiddle[0], _transStaffMiddle[1] + idleTrans * 0.5, _transStaffMiddle[2]);

    modelMtx = glm::scale(modelMtx, _scaleStaffMiddle);
    modelMtx = glm::translate(modelMtx, _transStaffMiddleAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_staffColor[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::vec3 _transStaffTopAnimate = glm::vec3(_transStaffTop[0], _transStaffTop[1] + idleTrans * 0.5, _transStaffTop[2]);

    modelMtx = glm::scale(modelMtx, _scaleStaffTop);
    modelMtx = glm::translate(modelMtx, _transStaffTopAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_staffColor[0]);

    CSCI441::drawSolidCube( 0.1f );

    glm::vec3 _transHandAnimate = glm::vec3(_transHand[0], _transHand[1] + idleTrans * 0.5, _transHand[2]);

    modelMtx = glm::scale(modelMtx, _scaleHand);
    modelMtx = glm::translate(modelMtx, _transHandAnimate);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_colorHead[0]);

    CSCI441::drawSolidCube( 0.1f );


    glm::vec3 _transOrbAnimate = glm::vec3(_transOrb[0], _transOrb[1] + idleTrans * 0.5 + orbHover * 0.5, _transOrb[2]);

    modelMtx = glm::scale(modelMtx, _scaleOrb);
    modelMtx = glm::translate(modelMtx, _transOrbAnimate);
    modelMtx = glm::rotate(modelMtx, -0.5f, CSCI441::X_AXIS);
    modelMtx = glm::rotate(modelMtx, orbAngle, CSCI441::Y_AXIS);

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &_orbColor[0]);

    CSCI441::drawSolidCube( 0.1f );
}

void Bardo::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}




