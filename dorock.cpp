
#include "dorock.h"

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



void Dorock::drawDorock(glm::mat4 viewMtx, glm::mat4 projMtx, glm::mat4 moveMtx, glm::mat4 rotMtx) const {


    // _pArcBall->setLookAtPoint(glm::vec3(dorockX, 10, dorockZ));
    // _pArcBall->recomputeOrientation();


    //DRAW BIG HEAD
    glm::mat4 tranMtx = glm::translate( glm::mat4(1.0), glm::vec3(0, 10, 0) );
    glm::mat4 scaleMtx = glm::scale( glm::mat4(1.0), glm::vec3(0.5f, 2.0f, 0.5f) );


    glm::mat4 TorModelMatrix =   moveMtx * tranMtx * rotMtx  * scaleMtx;

    _computeAndSendMatrixUniforms(TorModelMatrix, viewMtx, projMtx);

    glm::vec3 torColor(0.8f, 0.8f, 0.8f);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &torColor[0]);
    


    // CSCI441::drawSolidTorus(1.0, 2.0, 16.0, 16.0);

    CSCI441::drawSolidSphere(3.0, 16.0, 16.0);

    //DRAW BASE OF CHARACTER
    glm::mat4 tranMtx1 = glm::translate( glm::mat4(1.0), glm::vec3(0, -2, 0) );
    glm::mat4 scaleMtx1 = glm::scale( glm::mat4(1.0), glm::vec3(0.5f, 2.0f, 0.5f) );
    glm::mat4 rotMtx1 = glm::rotate(glm::mat4(1.0f), _dorockAngle, glm::vec3(0.0f, 0.1f, 0.0f));

    glm::mat4 baseModelmtx =  moveMtx * tranMtx1 * rotMtx * rotMtx1* scaleMtx1;

    _computeAndSendMatrixUniforms(baseModelmtx, viewMtx, projMtx);

    glm::vec3 baseColor(0.48,0.29,0.59);
    // _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, baseColor);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &baseColor[0]);


    CSCI441::drawSolidCube(8.0);

    //DRAW FACE OF CHARACTER
    glm::mat4 tranMtx2 = glm::translate( glm::mat4(1.0), glm::vec3(0, 13, 1.5) );
    glm::mat4 scaleMtx2 = glm::scale( glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f) );

    glm::mat4 baseModelmtx1 =  moveMtx * rotMtx  * tranMtx2 * scaleMtx2;

    _computeAndSendMatrixUniforms(baseModelmtx1, viewMtx, projMtx);

    glm::vec3 baseColor1(0.78f, 0.03f, 0.2f);
    // _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, baseColor1);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &baseColor1[0]);


    // CSCI441::drawSolidTorus(2.0, 4.0, 16, 16);
    CSCI441::drawSolidSphere(3.0, 16.0, 16.0);


    glm::mat4 tranMtx3 = glm::translate( glm::mat4(1.0), glm::vec3(1.0, 13, 1) );
    glm::mat4 scaleMtx3 = glm::scale( glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f) );

    glm::mat4 baseModelmtx2 =  moveMtx * rotMtx  * tranMtx3 * scaleMtx3;

    _computeAndSendMatrixUniforms(baseModelmtx2, viewMtx, projMtx);

    glm::vec3 baseColor2(0.78f, 0.03f, 0.2f);
    // _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, baseColor2);
    glProgramUniform3fv(_shaderProgramHandle, _shaderProgramUniformLocations.materialColor, 1, &baseColor2[0]);


    // CSCI441::drawSolidTorus(2.0, 4.0, 16, 16);
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
