#ifndef __GL_INIT_HPP__
#define __GL_INIT_HPP__
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
// Will drag system OpenGL headers
#include <GLFW/glfw3.h>
#include <globalVars.hpp>
#include <gl-window/mainWindow.hpp>
#include <gl-window/errorWindow.hpp>
#include <gl-window/informationWindow.hpp>
#include <gl-window/transactionWindow.hpp>
#include <gl-window/libraryWindow.hpp>
#include <gl-window/blockchainWindow.hpp>
#include <gl-window/stateVars.hpp>
#include <cryptography/Login.hpp>
#include <blockchain/Utils.hpp>
#include <library.hpp>

inline void glfw_error_callback(int error, const char *description);
void spaceSection(int n);
void separatorSection(int n);

void initGLwindow();

#endif // __GL_INIT_HPP__