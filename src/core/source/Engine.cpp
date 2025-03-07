/**
 * @file Engine.cpp
 * @brief Implementation of the main Engine class
 * @copyright Copyright (c) 2024 Cody Wall
 */

#include "core/header/Engine.h"
#include "core/header/Window.h"
#include <iostream>

namespace GameEngine {

Engine::Engine() : m_isRunning(false), m_window(nullptr) {
    std::cout << "Engine created" << std::endl;
}

Engine::~Engine() {
    shutdown();
    std::cout << "Engine destroyed" << std::endl;
}

bool Engine::initialize() {
    // Create window
    m_window = std::make_unique<Window>(Window::WindowProps("Game Engine", 1280, 720));
    if (!m_window->initialize()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return false;
    }
    
    // Set window callbacks
    m_window->setResizeCallback([](unsigned int width, unsigned int height) {
        std::cout << "Window resized: " << width << "x" << height << std::endl;
        // TODO: Handle window resize (update viewport, etc.)
    });
    
    m_window->setCloseCallback([this]() {
        std::cout << "Window close requested" << std::endl;
        m_isRunning = false;
    });
    
    std::cout << "Engine initialized" << std::endl;
    m_isRunning = true;
    return true;
}

void Engine::shutdown() {
    if (m_window) {
        m_window->shutdown();
        m_window.reset();
    }
    
    std::cout << "Engine shutdown" << std::endl;
    m_isRunning = false;
}

void Engine::run() {
    if (!m_isRunning) {
        if (!initialize()) {
            std::cerr << "Failed to initialize engine" << std::endl;
            return;
        }
    }

    std::cout << "Engine running" << std::endl;
    
    // Main game loop
    while (m_isRunning) {
        // Process window events
        m_window->update();
        
        // Check if window should close
        if (m_window->shouldClose()) {
            m_isRunning = false;
        }
        
        // TODO: Update game state
        
        // TODO: Render frame
    }
    
    shutdown();
}

bool Engine::isRunning() const {
    return m_isRunning;
}

} // namespace GameEngine 