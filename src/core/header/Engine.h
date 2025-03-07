/**
 * @file Engine.h
 * @brief Definition of the main Engine class
 * @copyright Copyright (c) 2024 Cody Wall
 */

#pragma once

#include <memory>

namespace GameEngine {
    class Window;

/**
 * @class Engine
 * @brief Main engine class that manages the game loop and subsystems
 */
class Engine {
public:
    /**
     * @brief Constructor
     */
    Engine();
    
    /**
     * @brief Destructor
     */
    ~Engine();
    
    /**
     * @brief Initialize the engine and all subsystems
     * @return true if initialization was successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Shutdown the engine and all subsystems
     */
    void shutdown();
    
    /**
     * @brief Run the main game loop
     */
    void run();
    
    /**
     * @brief Check if the engine is currently running
     * @return true if the engine is running, false otherwise
     */
    bool isRunning() const;
    
private:
    bool m_isRunning; ///< Flag indicating if the engine is running
    std::unique_ptr<Window> m_window; ///< Main application window
};

} // namespace GameEngine 