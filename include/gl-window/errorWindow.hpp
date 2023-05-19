#ifndef ERRORWINDOW_HPP
#define ERRORWINDOW_HPP

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>

void error_window(std::string error_message, bool &show_error);

#endif