# Alien Attack 2026

A modern 2D space shooter prototype built with C++ and SFML. This project features a robust entity management system ("Pixies") and a sophisticated swarm-based AI for enemy behaviors.

## 🚀 Features

- **Dynamic Swarm AI**: Enemies operate in groups with a designated leader. If the leader is destroyed, the swarm dynamically reassigns leadership to maintain cohesion.
- **Pixie Entity System**: A custom-built hierarchy for managing game objects, including automated drawing, collision detection, and lifecycle management via shared pointers.
- **Responsive Controls**: Smooth, vector-based movement with 8-way directional rotation.
- **Visual Effects**: Frame-based explosion animations triggered upon entity destruction.
- **Collision Logic**: Integrated projectile and entity collision systems with optimized bounding box checks.

## 🎮 Controls

| Action | Input |
| :--- | :--- |
| **Move** | `WASD` or `Arrow Keys` |
| **Fire Missile** | `Spacebar` |
| **Exit** | `Close Window` |

## 🏗️ Technical Architecture

### Class Hierarchy

The project uses a structured inheritance model centered around the `Pixie` base class:

- **Pixie**: The foundation for all drawable entities. Manages SFML Sprites, Textures, and global entity tracking.
    - **BackgroundPixie**: Handles scrolling or static backgrounds.
    - **MissilePixie**: Manages projectile movement and collision impact.
    - **ExplosionPixie**: Handles temporary visual effects and animation frames.
    - **ShipPixie**: Base class for entities with combat stats (health, damage, ammo).
        - **PlayerPixie**: Processes user input and camera-relative movement.
        - **EnemyPixie**: Implements "Follow" and "Orbit" behaviors relative to a target or swarm leader.

### Key Components

- **Swarm Controller**: Manages a collection of `EnemyPixie` IDs. It handles the organizational logic of the group, ensuring enemies orbit correctly and follow the leader.
- **Game Engine (SFML)**: Utilizes SFML 3.x for hardware-accelerated rendering and modern C++ event handling.
- **Object Management**: Uses `std::shared_ptr` and a static registry within the `Pixie` class to prevent memory leaks and simplify global operations like `drawAll()`.

## 🛠️ Requirements & Setup

### Prerequisites
- **Compiler**: C++20 compliant compiler (e.g., MSVC 2022, GCC 11+, Clang 13+).
- **Library**: [SFML 3.0](https://www.sfml-dev.org/) or higher.
- **Platform**: Windows (Visual Studio solution provided).

### Building
1. Clone the repository.
2. Ensure SFML 3.0 is installed and its environment variables are configured.
3. Open `AlienAttack26.sln` in Visual Studio.
4. Ensure the include and library directories point to your SFML installation.
5. Build in **Debug** or **Release** mode for `x64`.

## 📝 Authors
- **Original Work**: Prof. Andy Harbert
- **Modifications**: Prof. Pat Smith (2021)
- **Architecture & Refactoring**: Cole Lehl (2026)
