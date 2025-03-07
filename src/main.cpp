/**
 * @file main.cpp
 * @brief Entry point for the Game Engine
 * @copyright Copyright (c) 2024 Cody Wall
 */

#include <iostream>
#include "core/header/Engine.h"

int main() {
    std::cout << "Starting Game Engine..." << std::endl;
    
    // Create and run the engine
    GameEngine::Engine engine;
    engine.run();
    
    std::cout << "Game Engine terminated successfully" << std::endl;
    
    return 0;
} 