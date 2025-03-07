/**
 * @file Window.h
 * @brief Definition of the Window class for managing application windows
 * @copyright Copyright (c) 2024 Cody Wall
 */

#pragma once

#include <string>
#include <functional>

// Forward declarations to avoid including GLFW in header
struct GLFWwindow;

namespace GameEngine {

/**
 * @class Window
 * @brief Manages a window using GLFW
 * 
 * This class handles window creation, destruction, and events.
 * It provides an abstraction over GLFW functionality.
 */
class Window {
public:
    /**
     * @brief Window configuration parameters
     */
    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;
        bool vsync;
        bool fullscreen;
        bool resizable;
        
        /**
         * @brief Constructor with default values
         */
        WindowProps(
            const std::string& title = "Game Engine",
            unsigned int width = 1280,
            unsigned int height = 720,
            bool vsync = true,
            bool fullscreen = false,
            bool resizable = true
        ) : title(title), width(width), height(height), 
            vsync(vsync), fullscreen(fullscreen), resizable(resizable) {}
    };
    
    /**
     * @brief Constructor
     * @param props Window properties
     */
    Window(const WindowProps& props = WindowProps());
    
    /**
     * @brief Destructor
     */
    ~Window();
    
    /**
     * @brief Deleted copy constructor
     */
    Window(const Window&) = delete;
    
    /**
     * @brief Deleted assignment operator
     */
    Window& operator=(const Window&) = delete;
    
    /**
     * @brief Initialize the window
     * @return true if initialization was successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Shutdown the window
     */
    void shutdown();
    
    /**
     * @brief Update the window (process events, swap buffers)
     */
    void update();
    
    /**
     * @brief Check if the window should close
     * @return true if the window should close, false otherwise
     */
    bool shouldClose() const;
    
    /**
     * @brief Get the native GLFW window handle
     * @return Pointer to the GLFW window
     */
    GLFWwindow* getNativeWindow() const { return m_window; }
    
    /**
     * @brief Get the window width
     * @return Window width in pixels
     */
    unsigned int getWidth() const { return m_data.width; }
    
    /**
     * @brief Get the window height
     * @return Window height in pixels
     */
    unsigned int getHeight() const { return m_data.height; }
    
    /**
     * @brief Set the window title
     * @param title New window title
     */
    void setTitle(const std::string& title);
    
    /**
     * @brief Set the VSync mode
     * @param enabled Whether VSync should be enabled
     */
    void setVSync(bool enabled);
    
    /**
     * @brief Check if VSync is enabled
     * @return true if VSync is enabled, false otherwise
     */
    bool isVSync() const { return m_data.vsync; }
    
    /**
     * @brief Set window resize callback
     * @param callback Function to call when window is resized
     */
    void setResizeCallback(const std::function<void(unsigned int, unsigned int)>& callback);
    
    /**
     * @brief Set window close callback
     * @param callback Function to call when window is closed
     */
    void setCloseCallback(const std::function<void()>& callback);
    
private:
    /**
     * @brief Internal data structure for window properties and callbacks
     */
    struct WindowData {
        std::string title;
        unsigned int width;
        unsigned int height;
        bool vsync;
        bool fullscreen;
        bool resizable;
        
        std::function<void(unsigned int, unsigned int)> resizeCallback;
        std::function<void()> closeCallback;
    };
    
    GLFWwindow* m_window;  ///< GLFW window handle
    WindowData m_data;     ///< Window data
    
    /**
     * @brief Set up GLFW callbacks
     */
    void setupCallbacks();
};

} // namespace GameEngine 