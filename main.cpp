/*
 *  CSCI 441, Computer Graphics, Fall 2023
 *
 *  Project: a3.cpp
 *
 *  Description:
 *      This file contains the basic setup to work with GLSL shaders.
 *
 *  Author: Dr. Paone, Colorado School of Mines, 2023
 *
 */

#include "MPEngine.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

///*****************************************************************************
//
// Our main function
int main() {

    auto labEngine = new MPEngine();
    labEngine->initialize();
    if (labEngine->getError() == CSCI441::OpenGLEngine::OPENGL_ENGINE_ERROR_NO_ERROR) {
        labEngine->run();
    }
    labEngine->shutdown();
    delete labEngine;

	return EXIT_SUCCESS;
}
