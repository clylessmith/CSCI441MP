#ifndef LAB05_DOROCK_H
#define LAB05_DOROCK_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

class Dorock {
public:
    /// \desc creates the hero dorock
    /// \param shaderProgramHandle shader program handle that the plane should be drawn using
    /// \param mvpMtxUniformLocation uniform location for the full precomputed MVP matrix
    /// \param normalMtxUniformLocation uniform location for the precomputed Normal matrix
    /// \param materialColorUniformLocation uniform location for the material diffuse color
    Dorock(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation );

    /// \desc draws dorock for a given MVP matrix
    /// \param modelMtx existing model matrix to apply to plane
    /// \param viewMtx camera view matrix to apply to plane
    /// \param projMtx camera projection matrix to apply to plane
    /// \note internally uses the provided shader program and sets the necessary uniforms
    /// for the MVP and Normal Matrices as well as the material diffuse color
    void drawDorock(glm::mat4 viewMtx, glm::mat4 projMtx, glm::mat4 moveMtx);

    /// \desc moves dorock forward
    // void moveForward(GLfloat theta, GLfloat worldSize, glm::vec2 moveSpeed);
    void moveForward(GLfloat worldSize);

    /// \desc moves dorock forward
    // void moveBackward(GLfloat theta, GLfloat worldSize, glm::vec2 moveSpeed);
    void moveBackward(GLfloat worldSize);


    void rotate(GLfloat theta);

    glm::vec3 coords = {0.0f, 0.0f, 0.0f};
    /// \desc current angle of rotation for dorock
    GLfloat _dorockAngle = 0.0f;

private:

    GLint dorockX;
    GLint dorockZ;

    GLfloat heroOrientation;
    GLfloat dorockTurnAngle;

    GLfloat baseRotation;

    GLfloat _rotatePlaneAngle;

    /// \desc handle of the shader program to use when drawing dorock
    GLuint _shaderProgramHandle;
    /// \desc stores the uniform locations needed for dorock information
    struct ShaderProgramUniformLocations {
        /// \desc location of the precomputed ModelViewProjection matrix
        GLint mvpMtx;
        /// \desc location of the precomputed Normal matrix
        GLint normalMtx;
        /// \desc location of the material diffuse color
        GLint materialColor;
    } _shaderProgramUniformLocations;

    const GLfloat _PI = glm::pi<float>();
    const GLfloat _2PI = glm::two_pi<float>();
    const GLfloat _PI_OVER_2 = glm::half_pi<float>();


    /// \desc precomputes the matrix uniforms CPU-side and then sends them
    /// to the GPU to be used in the shader for each vertex.  It is more efficient
    /// to calculate these once and then use the resultant product in the shader.
    /// \param modelMtx model transformation matrix
    /// \param viewMtx camera view matrix
    /// \param projMtx camera projection matrix
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //LAB05_BARDO_H
