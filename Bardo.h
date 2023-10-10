#ifndef LAB05_BARDO_H
#define LAB05_BARDO_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class Bardo {
public:
    /// \desc creates the hero bardo
    /// \param shaderProgramHandle shader program handle that the plane should be drawn using
    /// \param mvpMtxUniformLocation uniform location for the full precomputed MVP matrix
    /// \param normalMtxUniformLocation uniform location for the precomputed Normal matrix
    /// \param materialColorUniformLocation uniform location for the material diffuse color
    Bardo(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation );

    /// \desc draws bardo for a given MVP matrix
    /// \param modelMtx existing model matrix to apply to plane
    /// \param viewMtx camera view matrix to apply to plane
    /// \param projMtx camera projection matrix to apply to plane
    /// \note internally uses the provided shader program and sets the necessary uniforms
    /// for the MVP and Normal Matrices as well as the material diffuse color
    void drawBardo(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans, float orbAngle, float orbHover );

    /// \desc moves bardo forward
    void moveForward(GLfloat theta);
    /// \desc moves bardo forward
    void moveBackward(GLfloat theta);

    void rotate(GLfloat theta);

private:
    /// \desc current angle of rotation for bardo
    GLfloat _bardoAngle;


    /// \desc handle of the shader program to use when drawing bardo
    GLuint _shaderProgramHandle;
    /// \desc stores the uniform locations needed for bardo information
    struct ShaderProgramUniformLocations {
        /// \desc location of the precomputed ModelViewProjection matrix
        GLint mvpMtx;
        /// \desc location of the precomputed Normal matrix
        GLint normalMtx;
        /// \desc location of the material diffuse color
        GLint materialColor;
    } _shaderProgramUniformLocations;

    /// \desc angle to rotate bardo
    GLfloat _rotatePlaneAngle;

    /// \desc color bardo's body
    glm::vec3 _colorBody;
    /// \desc amount to scale bardo's body by
    glm::vec3 _scaleBody;
    glm::vec3 _scaleBodyBottom;
    glm::vec3 _bottomBodyTrans;

    /// \desc color bardo's head
    glm::vec3 _colorHead;
    /// \desc amount to scale bardo's head by
    glm::vec3 _scaleHead;
    glm::vec3 _transHead;

    /// \desc color bardo's beard and hair
    glm::vec3 _colorBeard;
    glm::vec3 _scaleBeard;
    glm::vec3 _transBeard;
    glm::vec3 _scaleSideBeard;
    glm::vec3 _transSideBeard;

    glm::vec3 _scaleHatBottom;
    glm::vec3 _transHatBottom;
    glm::vec3 _hatMiddleColor;
    glm::vec3 _scaleHatMiddle;
    glm::vec3 _transHatMiddle;
    glm::vec3 _transHatTop;
    glm::vec3 _scaleHatTop;

    glm::vec3 _staffColor;
    glm::vec3 _scaleStaffBottom;
    glm::vec3 _transStaffBottom;
    glm::vec3 _scaleStaffMiddle;
    glm::vec3 _transStaffMiddle;
    glm::vec3 _scaleStaffTop;
    glm::vec3 _transStaffTop;

    glm::vec3 _transHand;
    glm::vec3 _scaleHand;

    glm::vec3 _orbColor;
    glm::vec3 _scaleOrb;
    glm::vec3 _transOrb;

    const GLfloat _PI = glm::pi<float>();
    const GLfloat _2PI = glm::two_pi<float>();
    const GLfloat _PI_OVER_2 = glm::half_pi<float>();

    /// \desc draws bardo's body
    /// \param modelMtx existing model matrix to apply
    /// \param viewMtx camera view matrix to apply
    /// \param projMtx camera projection matrix to apply
    void _drawBardoBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    /// \desc draws bardo's head
    /// \param modelMtx existing model matrix to apply
    /// \param viewMtx camera view matrix to apply
    /// \param projMtx camera projection matrix to apply
    void _drawHead( glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    /// \desc draws bardo's beard
    /// \param modelMtx existing model matrix to apply
    /// \param viewMtx camera view matrix to apply
    /// \param projMtx camera projection matrix to apply
    void _drawBeard(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    /// \desc draws bardo's hat
    /// \param modelMtx existing model matrix to apply
    /// \param viewMtx camera view matrix to apply
    /// \param projMtx camera projection matrix to apply
    void _drawHat(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans ) const;
    /// \desc draws bardo's staff
    /// \param modelMtx existing model matrix to apply
    /// \param viewMtx camera view matrix to apply
    /// \param projMtx camera projection matrix to apply
    void _drawStaff(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx, float idleTrans, float orbAngle, float orbHover ) const;


    /// \desc precomputes the matrix uniforms CPU-side and then sends them
    /// to the GPU to be used in the shader for each vertex.  It is more efficient
    /// to calculate these once and then use the resultant product in the shader.
    /// \param modelMtx model transformation matrix
    /// \param viewMtx camera view matrix
    /// \param projMtx camera projection matrix
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //LAB05_BARDO_H
