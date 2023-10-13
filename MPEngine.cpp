#include "MPEngine.h"
#include "ArcballCam.h"

#include <CSCI441/objects.hpp>
#include <iostream>

//*************************************************************************************
//
// Helper Functions

#ifndef M_PI
#define M_PI 3.14159265f
#endif

/// \desc Simple helper function to return a random number between 0.0f and 1.0f.
GLfloat getRand() {
    return (GLfloat)rand() / (GLfloat)RAND_MAX;
}

//*************************************************************************************
//
// Public Interface

MPEngine::MPEngine()
         : CSCI441::OpenGLEngine(4, 1,
                                 640, 480,
                                 "A3: The Cabin in the Woods") {

    for(auto& _key : _keys) _key = GL_FALSE;

    _mousePosition = glm::vec2(MOUSE_UNINITIALIZED, MOUSE_UNINITIALIZED );
    _leftMouseButtonState = GLFW_RELEASE;
    _heroCoords = glm::vec3(0, 0, 0);
    _idleTrans = 0.01;
    _orbHover = 0.01;
    _currentHero = 1;
    _currentCamera = 4;
    _firstPerson = false;
}

MPEngine::~MPEngine() {
    delete _pArcballCam;
    delete _pFreeCam;
    delete _pFPCam;
}

void MPEngine::handleKeyEvent(GLint key, GLint action) {
    if(key != GLFW_KEY_UNKNOWN)
        _keys[key] = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));

    if(action == GLFW_PRESS) {
        switch( key ) {
            // quit!
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                setWindowShouldClose();
                break;

            default: break; // suppress CLion warning
        }
    }
}

void MPEngine::handleMouseButtonEvent(GLint button, GLint action) {
    // if the event is for the left mouse button
    if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        // update the left mouse button's state
        _leftMouseButtonState = action;
    }
}

void MPEngine::handleCursorPositionEvent(glm::vec2 currMousePosition) {
    // if mouse hasn't moved in the window, prevent camera from flipping out
    if(_mousePosition.x == MOUSE_UNINITIALIZED) {
        _mousePosition = currMousePosition;
    }

    // if the left mouse button is being held down while the mouse is moving
    if(_leftMouseButtonState == GLFW_PRESS) {

        if ( _keys[GLFW_KEY_LEFT_SHIFT]) {
            if (_currentCamera == 4) {
                float mouseChange = _mousePosition.y - currMousePosition.y ;
                if (mouseChange > 0) {
                    _pArcballCam->moveForward(mouseChange * 0.1f);
                }
                else if (mouseChange < 0) {
                    _pArcballCam->moveBackward(-mouseChange * 0.1f);
                }
            }

        }
        else {
            if (_currentCamera == 4) {
                // rotate the camera by the distance the mouse moved
                _pArcballCam->rotate(( currMousePosition.x  - _mousePosition.x ) * 0.005f,
                                     (_mousePosition.y - currMousePosition.y) * 0.005f );
            }
            else if (_currentCamera == 5) {
                // rotate the camera by the distance the mouse moved
                _pFreeCam->rotate((currMousePosition.x - _mousePosition.x) * 0.005f,
                                  (_mousePosition.y - currMousePosition.y) * 0.005f );
            }

        }

    }

    // update the mouse position
    _mousePosition = currMousePosition;
}

//*************************************************************************************
//
// Engine Setup

void MPEngine::mSetupGLFW() {
    CSCI441::OpenGLEngine::mSetupGLFW();

    // set our callbacks
    glfwSetKeyCallback(mpWindow, lab05_engine_keyboard_callback);
    glfwSetMouseButtonCallback(mpWindow, lab05_engine_mouse_button_callback);
    glfwSetCursorPosCallback(mpWindow, lab05_engine_cursor_callback);
}

void MPEngine::mSetupOpenGL() {
    glEnable( GL_DEPTH_TEST );					                        // enable depth testing
    glDepthFunc( GL_LESS );							                // use less than depth test

    glEnable(GL_BLEND);									            // enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	    // use one minus blending equation

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	        // clear the frame buffer to black
}

void MPEngine::mSetupShaders() {
    _lightingShaderProgram = new CSCI441::ShaderProgram("shaders/a3.v.glsl", "shaders/a3.f.glsl" );
    _lightingShaderUniformLocations.mvpMatrix      = _lightingShaderProgram->getUniformLocation("mvpMatrix");
    _lightingShaderUniformLocations.materialColor  = _lightingShaderProgram->getUniformLocation("materialColor");
    // assign uniforms
    _lightingShaderUniformLocations.lightColor = _lightingShaderProgram->getUniformLocation("lightColor");
    _lightingShaderUniformLocations.lightDirection = _lightingShaderProgram->getUniformLocation("lightDirection");
    _lightingShaderUniformLocations.normalMatrix = _lightingShaderProgram->getUniformLocation("normalMatrix");

    _lightingShaderAttributeLocations.vPos         = _lightingShaderProgram->getAttributeLocation("vPos");
    // assign attributes
    _lightingShaderAttributeLocations.vertexNormal = _lightingShaderProgram->getAttributeLocation("vNormal");

}

void MPEngine::mSetupBuffers() {
    // need to connect our 3D Object Library to our shader
    CSCI441::setVertexAttributeLocations( _lightingShaderAttributeLocations.vPos, _lightingShaderAttributeLocations.vertexNormal );

    // give bardo the normal matrix location
    _bardo = new Bardo(_lightingShaderProgram->getShaderProgramHandle(),
                       _lightingShaderUniformLocations.mvpMatrix,
                       _lightingShaderUniformLocations.normalMatrix,
                       _lightingShaderUniformLocations.materialColor);

    _peanut = new Peanut(_lightingShaderProgram->getShaderProgramHandle(),
                         _lightingShaderUniformLocations.mvpMatrix,
                         _lightingShaderUniformLocations.normalMatrix,
                         _lightingShaderUniformLocations.materialColor);
    
    _dorock = new Dorock(_lightingShaderProgram->getShaderProgramHandle(),
                         _lightingShaderUniformLocations.mvpMatrix,
                         _lightingShaderUniformLocations.normalMatrix,
                         _lightingShaderUniformLocations.materialColor);


    _createGroundBuffers();
    _generateEnvironment();
}

void MPEngine::_createGroundBuffers() {
    // expand our struct
    struct Vertex {
        GLfloat x, y, z;
        GLfloat normalX, normalY, normalZ;

    };

    // add normal data
    Vertex groundQuad[4] = {
            {-1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
            { 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
            {-1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f},
            { 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f}
    };

    GLushort indices[4] = {0,1,2,3};

    _numGroundPoints = 4;

    glGenVertexArrays(1, &_groundVAO);
    glBindVertexArray(_groundVAO);

    GLuint vbods[2];       // 0 - VBO, 1 - IBO
    glGenBuffers(2, vbods);
    glBindBuffer(GL_ARRAY_BUFFER, vbods[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundQuad), groundQuad, GL_STATIC_DRAW);

    glEnableVertexAttribArray(_lightingShaderAttributeLocations.vPos);
    glVertexAttribPointer(_lightingShaderAttributeLocations.vPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // hook up vertex normal attribute
    glEnableVertexAttribArray(_lightingShaderAttributeLocations.vertexNormal);
    glVertexAttribPointer(_lightingShaderAttributeLocations.vertexNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GLfloat) * 3));


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbods[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MPEngine::_generateEnvironment() {
    //******************************************************************
    // parameters to make up our grid size and spacing, feel free to
    // play around with this
    const GLfloat GRID_WIDTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_LENGTH = WORLD_SIZE * 1.8f;
    const GLfloat GRID_SPACING_WIDTH = 1.0f;
    const GLfloat GRID_SPACING_LENGTH = 1.0f;
    // precomputed parameters based on above
    const GLfloat LEFT_END_POINT = -GRID_WIDTH / 2.0f - 5.0f;
    const GLfloat RIGHT_END_POINT = GRID_WIDTH / 2.0f + 5.0f;
    const GLfloat BOTTOM_END_POINT = -GRID_LENGTH / 2.0f - 5.0f;
    const GLfloat TOP_END_POINT = GRID_LENGTH / 2.0f + 5.0f;
    //******************************************************************

    srand( time(0) );                                                   // seed our RNG


    // psych! everything's on a grid.
    for(int i = LEFT_END_POINT; i < RIGHT_END_POINT; i += GRID_SPACING_WIDTH) {
        for(int j = BOTTOM_END_POINT; j < TOP_END_POINT; j += GRID_SPACING_LENGTH) {
            // don't just draw a building ANYWHERE.
            if( i % 2 && j % 2 && getRand() < 0.0025f ) {
                // translate to spot
                glm::mat4 transToSpotMtx = glm::translate( glm::mat4(1.0), glm::vec3(i, 0.0f, j) );

                // compute random height
                GLdouble height = powf(getRand(), 2.5)*25 + 20;

                // scale to building size
                glm::mat4 scaleToHeightMtx = glm::scale( glm::mat4(1.0), glm::vec3(1, height, 1) );

                // translate up to grid
                glm::mat4 transToHeight = glm::translate( glm::mat4(1.0), glm::vec3(0, height/2.0f, 0) );

                // compute full model matrix
                glm::mat4 modelMatrix = transToHeight * scaleToHeightMtx * transToSpotMtx;

                // compute random color
                glm::vec3 color( 0.36, 0.26, 0.2 );
                // store building properties
                BuildingData currentBuilding = {modelMatrix, color, height};
                _buildings.emplace_back( currentBuilding );
            }
        }
    }
}

void MPEngine::mSetupScene() {

    _pArcballCam = new ArcballCam();
    _pArcballCam->setTheta(M_PI / 3.5f );
    _pArcballCam->setPhi(2*M_PI / 4.0f );
    _pArcballCam->setRadius(25.0f);
    _pArcballCam->setLookAtPoint(glm::vec3(_heroCoords[0], 4, _heroCoords[2]));
    _pArcballCam->recomputeOrientation();

    _cameraSpeed = glm::vec2(0.25f, 0.02f);

    _pFreeCam= new CSCI441::FreeCam();
    _pFreeCam->setPosition(glm::vec3(60.0f, 40.0f, 30.0f) );
    _pFreeCam->setTheta(-M_PI / 3.0f );
    _pFreeCam->setPhi(M_PI / 2.8f );
    _pFreeCam->recomputeOrientation();
    _cameraSpeed = glm::vec2(0.25f, 0.02f);

    _pFPCam = new CSCI441::FreeCam();
    _pFPCam->setPosition(glm::vec3(_heroCoords[0], 4, _heroCoords[2])
                            + glm::vec3(2*cos(_heroTheta),4,2*sin(_heroTheta)));
    _pFPCam->setTheta(_heroTheta);
    _pFPCam->setPhi(M_PI_2);
    _pFPCam->recomputeOrientation();

//    _pFPCam = new ArcballCam();
//    _pFPCam->setTheta( _heroTheta );
//    _pFPCam->setPhi(M_PI / 2.0f );
//    _pFPCam->setRadius(0.0f);
//    _pFPCam->setPosition(_pFPCam->getPosition()+glm::vec3(cos(_heroTheta),0,sin(_heroTheta)));
//    _pFPCam->setLookAtPoint(glm::vec3(_heroCoords[0], 4, _heroCoords[2]));
//    _pFPCam->recomputeOrientation();

    _cameraSpeed = glm::vec2(0.25f, 0.02f);

    // set lighting uniforms
    glm::vec3 lightDirection = glm::vec3(-1,-1,-1);
    glm::vec3 lightColor = glm::vec3(1.0f,1.0f,1.0f);

    glProgramUniform3fv(
            _lightingShaderProgram->getShaderProgramHandle(),
            _lightingShaderUniformLocations.lightDirection,
            1,
            &lightDirection[0]
            );

    glProgramUniform3fv(
            _lightingShaderProgram->getShaderProgramHandle(),
            _lightingShaderUniformLocations.lightColor,
            1,
            &lightColor[0]
    );

}

//*************************************************************************************
//
// Engine Cleanup

void MPEngine::mCleanupShaders() {
    fprintf( stdout, "[INFO]: ...deleting Shaders.\n" );
    delete _lightingShaderProgram;
}

void MPEngine::mCleanupBuffers() {
    fprintf( stdout, "[INFO]: ...deleting VAOs....\n" );
    CSCI441::deleteObjectVAOs();
    glDeleteVertexArrays( 1, &_groundVAO );

    fprintf( stdout, "[INFO]: ...deleting VBOs....\n" );
    CSCI441::deleteObjectVBOs();

    fprintf( stdout, "[INFO]: ...deleting models..\n" );
    delete _bardo;
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!

void MPEngine::_renderScene(glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // use our lighting shader program
    _lightingShaderProgram->useProgram();

    //// BEGIN DRAWING THE GROUND PLANE ////
    // draw the ground plane
    glm::mat4 groundModelMtx = glm::scale( glm::mat4(1.0f), glm::vec3(WORLD_SIZE, 1.0f, WORLD_SIZE));
    _computeAndSendMatrixUniforms(groundModelMtx, viewMtx, projMtx);

    glm::vec3 groundColor(0.301f, 0.70f, 0.301f);

    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, groundColor);

    glBindVertexArray(_groundVAO);
    glDrawElements(GL_TRIANGLE_STRIP, _numGroundPoints, GL_UNSIGNED_SHORT, (void*)0);
    //// END DRAWING THE GROUND PLANE ////

    //// BEGIN DRAWING THE BUILDINGS ////
    for( const BuildingData& currentBuilding : _buildings ) {

        _drawTree(currentBuilding, viewMtx, projMtx);
    }
    //// END DRAWING THE BUILDINGS ////

    //// BEGIN DRAWING BARDO ////
    glm::mat4 modelMtx(1.0f);
    // draw bardo at known coords
    modelMtx = glm::translate(modelMtx, glm::vec3(_bardo->coords[0], 1, _bardo->coords[2]) );
    // rotate bardo when drawn
    modelMtx = glm::rotate(modelMtx, _bardo->_bardoAngle, CSCI441::Y_AXIS );
    // draw our plane now
    _bardo->drawBardo(modelMtx, viewMtx, projMtx, _idleTrans, _orbAngle, _orbHover);

    glm::mat4 modelMtx1(1.0f);
    // draw peanut at known coords
    modelMtx1 = glm::translate(modelMtx1, glm::vec3(_peanut->getPosition()[0], 1, _peanut->getPosition()[2]) );
    // rotate peanut when drawn
    modelMtx1 = glm::rotate(modelMtx1, _peanut->getTheta(), CSCI441::Y_AXIS );
    _peanut->drawPeanut(modelMtx1, viewMtx, projMtx);
    //// END DRAWING BARDO ////

    ////BEGIN DRAWING DOROCK////
    glm::mat4 modelMtx2(1.0f);

    modelMtx2 = glm::translate(modelMtx2, glm::vec3(_dorock->dorockX, 1, _dorock->dorockZ) );
    modelMtx2 = glm::rotate(modelMtx2, _dorock->_dorockAngle, CSCI441::Y_AXIS );


    _dorock->drawDorock(modelMtx2, viewMtx, projMtx);

    ////END DRAWING DOROCK////

}

void MPEngine::_updateScene() {

    //animation for dorock
    _dorock->baseRotation += 0.1;

    // animation for Bardo
    if (_framesPassedOrb == 4) {
        _framesPassedOrb = 0;
        if (_orbAngle > glm::two_pi<float>()) {
            _orbAngle -= glm::two_pi<float>();
        }
        _orbAngle += 0.05f;
    }
    else {
        _framesPassedOrb++;
    }
    if (_framesPassedHover == 64) {
        _framesPassedHover = 0;
        _orbHover *= -1;
    }
    else {
        _framesPassedHover++;
    }

    // turn hero right
    if( _keys[GLFW_KEY_D] ) {
        _heroTheta -= _cameraSpeed.y;

        switch (_currentHero) {
            case 1:
                _bardo->rotate(_heroTheta);
                break;
            case 2:
                _peanut->rotate(_heroTheta);
                break;
            case 3:
               _dorock->rotate(_heroTheta);
                break;
            
            default:
                break;
        }
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
        _pFPCam->setTheta(-_heroTheta + M_PI_2);
        _pFPCam->setPosition(_heroCoords + glm::vec3(2*cos(-_heroTheta),4,2*sin(-_heroTheta)));
        _pFPCam->recomputeOrientation();
    }
    // turn hero left
    if( _keys[GLFW_KEY_A] ) {
        _heroTheta += _cameraSpeed.y;

        switch (_currentHero) {
            case 1:
                _bardo->rotate(_heroTheta);
                break;
            case 2:
                _peanut->rotate(_heroTheta);
                break;
            case 3:
                _dorock->rotate(_heroTheta);
                break;
            default:
                break;
        }
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
        _pFPCam->setTheta(-_heroTheta + M_PI_2);
        _pFPCam->setPosition(_heroCoords + glm::vec3(2*cos(-_heroTheta),4,2*sin(-_heroTheta)));
        _pFPCam->recomputeOrientation();
    }
    // move hero forward
    if( _keys[GLFW_KEY_W]) {
        switch (_currentHero) {
            case 1:
                if (_framesPassed == 28) {
                    _framesPassed = 0;
                    _idleTrans *= -1;
                }
                else {
                    _framesPassed++;
                }
                _bardo->moveForward(_heroTheta, WORLD_SIZE, _cameraSpeed);
                _heroCoords = _bardo->coords;
                break;
            case 2:
                _peanut->moveForward();
                _heroCoords = _peanut->getPosition();
                break;
            case 3:
                _dorock->moveForward(WORLD_SIZE);
                _heroCoords = glm::vec3(_dorock->dorockX, 8, _dorock->dorockZ);
            default:
                break;
        }

        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
        _pFPCam->setPosition(_heroCoords + glm::vec3(2*cos(-_heroTheta),4,2*sin(-_heroTheta)));
        _pFPCam->recomputeOrientation();
    }

    // move hero backward
    if( _keys[GLFW_KEY_S] ) {
        switch (_currentHero) {
            case 1:
                if (_framesPassed == 28) {
                    _framesPassed = 0;
                    _idleTrans *= -1;
                }
                else {
                    _framesPassed++;
                }
                _bardo->moveBackward(_heroTheta, WORLD_SIZE, _cameraSpeed);
                _heroCoords = _bardo->coords;
                break;
            case 2:
                _peanut->moveBackward();
                _heroCoords = _peanut->getPosition();
                break;
            case 3:
                _dorock->moveBackward(WORLD_SIZE);
                _heroCoords = glm::vec3(_dorock->dorockX, 8, _dorock->dorockZ);
                break;
            default:
                break;
        }
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
        _pFPCam->setPosition(_heroCoords + glm::vec3(2*cos(-_heroTheta),4,2*sin(-_heroTheta)));
        _pFPCam->recomputeOrientation();
    }


    // turn camera right
    if( _keys[GLFW_KEY_RIGHT] ) {
        _pFreeCam->rotate(_cameraSpeed.y, 0.0f);
    }
    // turn camera left
    if(_keys[GLFW_KEY_LEFT] ) {
        _pFreeCam->rotate(-_cameraSpeed.y, 0.0f);
    }
    // pitch camera up
    if(  _keys[GLFW_KEY_UP] ) {
        _pFreeCam->rotate(0.0f, _cameraSpeed.y);
    }
    // pitch camera down
    if( _keys[GLFW_KEY_DOWN] ) {
        _pFreeCam->rotate(0.0f, -_cameraSpeed.y);
    }
    if( _keys[GLFW_KEY_SPACE] ) {
        // go backward if shift held down
        if( _keys[GLFW_KEY_RIGHT_SHIFT] ) {
            _pFreeCam->moveBackward(_cameraSpeed.x * 2.5);
        }
            // go forward
        else {
            _pFreeCam->moveForward(_cameraSpeed.x * 2.5);
        }
    }


    // select camera and hero
    if (_keys[GLFW_KEY_1]) {
        _currentHero = 1;
        _currentCamera = 4;
        _heroCoords = _bardo->coords;
        _heroTheta = _bardo->_bardoAngle;
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
    }
    if (_keys[GLFW_KEY_2]) {
        _currentHero = 2;
        _currentCamera = 4;
        _heroCoords = _peanut->getPosition();
        _heroTheta = _peanut->getTheta();
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
    }
    if (_keys[GLFW_KEY_3]) {
        _currentHero = 3;
        _currentCamera = 4;
        _heroCoords = glm::vec3(_dorock->dorockX, 8, _dorock->dorockZ);
        _heroTheta = _dorock->_dorockAngle;
        _pArcballCam->setLookAtPoint(_heroCoords);
        _pArcballCam->recomputeOrientation();
    }
    if (_keys[GLFW_KEY_4]) {
        _currentCamera = 4;
    }
    if (_keys[GLFW_KEY_5]) {
        _currentCamera = 5;
    }
    if (_keys[GLFW_KEY_6]) {
        _firstPerson = true;
    }


}

void MPEngine::run() {
    //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
    //	until the user decides to close the window and quit the program.  Without a loop, the
    //	window will display once and then the program exits.
    while( !glfwWindowShouldClose(mpWindow) ) {	        // check if the window was instructed to be closed
        glDrawBuffer( GL_BACK );				        // work with our back frame buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// clear the current color contents and depth buffer in the window

        // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
        // when using a Retina display the actual window can be larger than the requested window.  Therefore,
        // query what the actual size of the window we are rendering to is.
        GLint framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize( mpWindow, &framebufferWidth, &framebufferHeight );

        // update the viewport - tell OpenGL we want to render to the whole window
        glViewport( 0, 0, framebufferWidth, framebufferHeight );

        // draw everything to the window
        switch (_currentCamera) {
            case 4:
                _renderScene(_pArcballCam->getViewMatrix(), _pArcballCam->getProjectionMatrix());
                break;
            case 5:
                _renderScene(_pFreeCam->getViewMatrix(), _pFreeCam->getProjectionMatrix());
                break;
        }

        if (_firstPerson) {
            glViewport(0, 0, framebufferWidth / 4, framebufferHeight / 4);
            _renderScene(_pFPCam->getViewMatrix(), _pFPCam->getProjectionMatrix());
        }
        _updateScene();

        glfwSwapBuffers(mpWindow);                       // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();				                // check for any events and signal to redraw screen
    }
}

//*************************************************************************************
//
// Private Helper FUnctions

void MPEngine::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.mvpMatrix, mvpMtx);

    // compute and send the normal matrix
    glm::mat3 normalMtx = glm::mat3(glm::transpose(glm::inverse(modelMtx)));
    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.normalMatrix, normalMtx);

}

void MPEngine::_drawTree(MPEngine::BuildingData building, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    _computeAndSendMatrixUniforms(building.modelMatrix, viewMtx, projMtx);

    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, building.color);

    CSCI441::drawSolidCube(1.0);

    glm::mat4 modelMtx1 = modelMtx1 = glm::translate(modelMtx1, glm::vec3(0, building.treeHeight * 0.005, 0));;
    modelMtx1 = glm::scale(building.modelMatrix, glm::vec3(4.0f, building.treeHeight * 0.3, 4.0f));


    glm::vec3 leafColor = glm::vec3(0.02f, 0.22f, 0.02f);

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.materialColor, leafColor);

    CSCI441::drawSolidCone( 2.25f, 0.2f, 16, 16 );


}

//*************************************************************************************
//
// Callbacks

void lab05_engine_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the key and action through to the engine
    engine->handleKeyEvent(key, action);
}

void lab05_engine_cursor_callback(GLFWwindow *window, double x, double y ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the cursor position through to the engine
    engine->handleCursorPositionEvent(glm::vec2(x, y));
}

void lab05_engine_mouse_button_callback(GLFWwindow *window, int button, int action, int mods ) {
    auto engine = (MPEngine*) glfwGetWindowUserPointer(window);

    // pass the mouse button and action through to the engine
    engine->handleMouseButtonEvent(button, action);
}
