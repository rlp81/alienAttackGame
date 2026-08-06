# Alien Attack 2026

A modern, high-performance 2D space shooter built with C++ and SFML. This project showcases a robust entity management architecture ("Pixies") and a sophisticated swarm-based AI system.

## 🚀 Version 0.7.0 Highlights

Version 0.7.0 introduces significant gameplay and architectural improvements:
- **Integrated UI System**: Real-time scoring and floating text feedback.
- **Dynamic Swarm AI**: Enhanced leadership reassignment and random movement patterns.
- **Level Management**: New `LevelLoader` for state management and progression.
- **Smart Pointer Architecture**: Fully transitioned to `std::shared_ptr` and `std::weak_ptr` for safe, automated memory management.

## 🎮 Features

- **Advanced Swarm AI**: Enemies operate in intelligent groups. If a leader is destroyed, the swarm dynamically reassigns leadership to maintain formation and tactical cohesion.
- **Pixie Entity System**: A custom-built hierarchy for managing game objects. Features automated drawing, collision detection, and a unique ID-keyed map for efficient entity tracking.
- **Responsive Combat**: Smooth, vector-based player movement with 8-way directional rotation and RayCast-assisted enemy firing logic.
- **Visual Feedback**: Frame-based explosion animations (PNG with alpha transparency) and missile trails for a polished arcade feel.
- **Robust UI**: Dynamic scoring display using retro-styled fonts (Pixeloid/SuperPixel).

## ⌨️ Controls

| Action | Input |
| :--- | :--- |
| **Move** | `WASD` or `Arrow Keys` |
| **Fire Missile** | `Spacebar` |
| **Exit** | `Close Window` |

## 🏗️ Technical Architecture

### Class Hierarchy

The project uses a structured inheritance model centered around the `Pixie` base class:

- **Pixie**: The foundation for all drawable entities. Manages SFML Sprites, Textures, and global entity tracking via unique IDs.
    - **BackgroundPixie**: Handles scrolling and static backgrounds.
    - **MissilePixie**: Manages projectile physics, owner tracking, and collision impact.
    - **ExplosionPixie**: Handles temporary visual effects with frame-based animation.
    - **ShipPixie**: Base class for entities with combat stats (health, damage, ammo).
        - **PlayerPixie**: Processes user input and camera-relative movement.
        - **EnemyPixie**: Implements "Follow", "Orbit", and "Swarm" behaviors.

### Key Components

- **Swarm Controller**: Responsible for the complex behaviors of enemy groups. It manages collections of `EnemyPixie` IDs, orchestrates group organizational logic (e.g., maintaining formation, orbit patterns), and dynamically reassigns swarm leadership if the current leader is destroyed. This ensures a persistent and challenging enemy presence.
- **UI Controller**: Dedicated to managing all in-game user interface elements. This includes displaying the Heads-Up Display (HUD), tracking and presenting the player's score, and managing dynamic, disposable floating text elements (ee.g., score pop-ups) using various fonts.
- **RayCast Utility**: A critical helper for collision prediction and line-of-sight calculations. It provides efficient checks for enemies to prevent friendly fire, improve projectile accuracy, and inform tactical AI decisions, contributing to a more responsive combat system.
- **Level Loader**: Orchestrates the initialization and resetting of game states between levels or after game over. It's responsible for clearing entity registries, setting up initial enemy swarms, player positions, and ensuring a clean environment for each new game session.

### Core Game Loop and Interaction

The game operates on a continuous loop, managed by SFML's `RenderWindow`. Each frame involves the following critical steps:

1.  **Event Handling**: User inputs (keyboard, mouse) and window events (close, resize) are processed. Player commands are translated into actions (movement, firing).
2.  **Update Logic**:
    *   All active `Pixie` entities are updated based on their individual logic (e.g., movement, animation, AI).
    *   The `Swarm Controller` updates enemy group behaviors, leader assignments, and overall swarm tactical decisions.
    *   `MissilePixie` instances update their positions and check for collisions using the `RayCast Utility`.
    *   The `UI Controller` refreshes scores and manages the lifecycle of dynamic text elements.
    *   Collision detection is performed between relevant entities (e.g., player missiles vs. enemies, enemy missiles vs. player).
3.  **Rendering**:
    *   The screen is cleared.
    *   All drawable `Pixie` entities (backgrounds, ships, missiles, explosions, UI elements) are rendered to the screen in the appropriate order.
    *   The `RenderWindow` displays the newly drawn frame.

This loop ensures a dynamic and responsive gameplay experience, with clear separation of concerns among the various architectural components.

## 🛠️ Requirements & Setup

### Prerequisites
- **Compiler**: C++20 compliant compiler (MSVC 2022 recommended).
- **Library**: [SFML 3.0.2]([https://www.sfml-dev.org/](https://www.sfml-dev.org/download/sfml/3.0.2/)).
- **Platform**: Windows (Visual Studio solution provided).

### Downloading
1. Download the latest release.
2. Unzip the file.
3. Ensure that the assets/ directory is in the same directory as the executable.

### Building
1. Clone the repository.
2. Ensure SFML 3.0 is installed and your environment variables are configured.
3. Open `AlienAttack26.sln` in Visual Studio.
4. Verify that the project's **Include Directories** and **Library Directories** point to your SFML installation.
5. Build in **Debug** or **Release** mode for `x86`.

## 📝 Authors
- **Original Work**: Prof. Andy Harbert
- **Modifications**: Prof. Pat Smith (2021)
- **Architecture & Refactoring**: Cole Lehl (2026)

## Documentation Disclaimer
Most of the GitHub documentation (Commits and README) is generated by AI, because I cannot be bothered.
