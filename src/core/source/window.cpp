/**
 * @file window.cpp
 * @brief Implementation of the Window class for managing application windows
 * @copyright Copyright (c) 2024 Cody Wall
 */

#include "../header/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace GameEngine {

// Custom data structure for GLFW callbacks
struct WindowCallbackData {
    unsigned int width;
    unsigned int height;
    std::function<void(unsigned int, unsigned int)> resizeCallback;
    std::function<void()> closeCallback;
};

// Static callback functions for GLFW
static void glfwErrorCallback(int error, const char* description) {
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowCallbackData* data = static_cast<WindowCallbackData*>(glfwGetWindowUserPointer(window));
    data->width = width;
    data->height = height;
    
    if (data->resizeCallback) {
        data->resizeCallback(width, height);
    }
}

static void glfwWindowCloseCallback(GLFWwindow* window) {
    WindowCallbackData* data = static_cast<WindowCallbackData*>(glfwGetWindowUserPointer(window));
    
    if (data->closeCallback) {
        data->closeCallback();
    }
}

Window::Window(const WindowProps& props) 
    : m_window(nullptr) {
    m_data.title = props.title;
    m_data.width = props.width;
    m_data.height = props.height;
    m_data.vsync = props.vsync;
    m_data.fullscreen = props.fullscreen;
    m_data.resizable = props.resizable;
}

Window::~Window() {
    shutdown();
}

bool Window::initialize() {
    glfwInit();
    
    glfwSetErrorCallback(glfwErrorCallback);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    
    glfwMakeContextCurrent(m_window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    
    setVSync(m_data.vsync);
    
    setupCallbacks();
    
    return true;
}

void Window::shutdown() {
    if (m_window) {
        // Clean up the callback data
        WindowCallbackData* callbackData = static_cast<WindowCallbackData*>(glfwGetWindowUserPointer(m_window));
        if (callbackData) {
            delete callbackData;
        }
        
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
    glfwTerminate();
}

void Window::update() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::setTitle(const std::string& title) {
    m_data.title = title;
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::setVSync(bool enabled) {
    m_data.vsync = enabled;
    glfwSwapInterval(enabled ? 1 : 0);
}

void Window::setResizeCallback(const std::function<void(unsigned int, unsigned int)>& callback) {
    m_data.resizeCallback = callback;
    
    // Update the callback in the WindowCallbackData if it exists
    if (m_window) {
        WindowCallbackData* callbackData = static_cast<WindowCallbackData*>(glfwGetWindowUserPointer(m_window));
        if (callbackData) {
            callbackData->resizeCallback = callback;
        }
    }
}

void Window::setCloseCallback(const std::function<void()>& callback) {
    m_data.closeCallback = callback;
    
    // Update the callback in the WindowCallbackData if it exists
    if (m_window) {
        WindowCallbackData* callbackData = static_cast<WindowCallbackData*>(glfwGetWindowUserPointer(m_window));
        if (callbackData) {
            callbackData->closeCallback = callback;
        }
    }
}

void Window::setupCallbacks() {
    // Create a WindowCallbackData instance for callbacks
    WindowCallbackData* callbackData = new WindowCallbackData();
    callbackData->width = m_data.width;
    callbackData->height = m_data.height;
    callbackData->resizeCallback = m_data.resizeCallback;
    callbackData->closeCallback = m_data.closeCallback;
    
    // Set the window user pointer to our callback data
    glfwSetWindowUserPointer(m_window, callbackData);
    
    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_window, glfwWindowSizeCallback);
    glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
}

} // namespace GameEngine