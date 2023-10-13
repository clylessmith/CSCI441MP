
#include "Dorock.h"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>
#include <iostream>




Dorock::Dorock(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {
    _dorockAngle = 0.0f;

    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;

    _rotatePlaneAngle = _PI / 2.0f;

}



void Dorock::drawDorock(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {

    drawHead(modelMtx, viewMtx, projMtx);
    drawBase(modelMtx, viewMtx, projMtx);
    drawFace(modelMtx, viewMtx, projMtx);

}

void Dorock::drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const{
    //DRAW BIG HEAD
    modelMtx = glm::translate( modelMtx, glm::vec3(0, 10, 0) );
    modelMtx = glm::scale( modelMtx, glm::vec3(0.5f, 2.0f, 0.5f) );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glm::vec3 headColor(0.8f, 0.8f, 0.8f);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &headColor[0]);
    
    CSCI441::drawSolidSphere(3.0, 16.0, 16.0);

}

void Dorock::drawBase(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const{

    //DRAW BASE OF CHARACTER
    modelMtx = glm::translate( modelMtx, glm::vec3(0, -2, 0) );
    modelMtx = glm::scale( modelMtx, glm::vec3(0.5f, 2.0f, 0.5f) );
    modelMtx = glm::rotate( modelMtx, baseRotation, glm::vec3(0.0f, 0.1f, 0.0f));

    // glm::mat4 baseModelmtx =  moveMtx * tranMtx1 * rotMtx * rotMtx1* scaleMtx1;

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glm::vec3 baseColor(0.48,0.29,0.59);
    // _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, baseColor);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &baseColor[0]);

    CSCI441::drawSolidCube(8.0);
}


void Dorock::drawFace(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const{

    glm::mat4 leftEyeModelMtx = modelMtx;

    //DRAW FACE OF CHARACTER
    leftEyeModelMtx = glm::translate( leftEyeModelMtx, glm::vec3(0, 13, 1.5) );
    leftEyeModelMtx = glm::scale( leftEyeModelMtx, glm::vec3(0.1f, 0.1f, 0.1f) );

    _computeAndSendMatrixUniforms(leftEyeModelMtx, viewMtx, projMtx);

    glm::vec3 leftEyeColor(0.78f, 0.03f, 0.2f);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &leftEyeColor[0]);

    CSCI441::drawSolidSphere(3.0, 16.0, 16.0);

    modelMtx = glm::translate( modelMtx, glm::vec3(1.0, 13, 1) );
    modelMtx = glm::scale( modelMtx, glm::vec3(0.1f, 0.1f, 0.1f) );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glm::vec3 rightEyeColor(0.78f, 0.03f, 0.2f);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &rightEyeColor[0]);

    CSCI441::drawSolidSphere(3.0, 16.0, 16.0);
}

void Dorock::moveForward(GLfloat worldSize){

    if(dorockX > -worldSize && dorockX < worldSize ){
        dorockX += 3 * sin(_dorockAngle);
    }
    else{
        dorockX *= 0.9;
    }

    if(dorockZ > -worldSize && dorockZ < worldSize){
        dorockZ += 3 * cos(_dorockAngle);
    }
    else{
        dorockZ *= 0.9;
    }
}

void Dorock::rotate(const GLfloat theta) {
    _dorockAngle = theta;

}

void Dorock::moveBackward(GLfloat worldSize){
    if(dorockX > -worldSize && dorockX < worldSize ){
        dorockX -= 3 * sin(_dorockAngle);
    }
    else{
        dorockX *= 0.9;
    }

    if(dorockZ > -worldSize && dorockZ < worldSize){
        dorockZ -= 3 * cos(_dorockAngle);
    }
    else{
        dorockZ *= 0.9;
    }
}

void Dorock::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}
