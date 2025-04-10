Yuki Hanif Arsan (5223600061)
Ibrahim Ar-Rafii (5223600066)

Pacman Game Project

Overview
This project is a console-based implementation of the classic Pacman game, written in C++. The game features Pacman navigating a map to collect pellets while avoiding ghosts. The ghosts exhibit different behaviors based on their state, and the game includes difficulty settings, random ghost spawning, and visual enhancements like colored ghost states. The project demonstrates the use of several design patterns: State, Factory, and Decorator.

Project Structure
The project is organized into include and src directories, with a main entry point in main.cpp.

include/: Header files (.h) for all classes.
src/: Source files (.cpp) for class implementations.
main.cpp: Entry point of the game, handling initialization, user input, and game loop.

File Breakdown
Map.h / Map.cpp: Defines the game map, including display and tile management.
Pacman.h / Pacman.cpp: Manages Pacman’s movement and power-up state.
Ghost.h / Ghost.cpp: Represents a ghost with state-based behavior.
GhostState.h: Abstract base class for ghost states.
ChaseState.h / ChaseState.cpp: State where ghosts chase Pacman.
WanderState.h / WanderState.cpp: State where ghosts wander randomly.
FrightenedState.h / FrightenedState.cpp: State where ghosts flee from Pacman.
ReturnState.h / ReturnState.cpp: State where ghosts return to the ghost house after being caught.
ColoredFrightenedState.h / ColoredFrightenedState.cpp: Decorator for FrightenedState to add color.
GhostFactory.h / GhostFactory.cpp: Factory for creating ghosts.
Utils.h: Utility functions (e.g., gotoxy for console positioning).
main.cpp: Game initialization and loop.

Classes and Their Roles
- Map: Manages the game map (23x39 grid).
Methods: ShowMap, redrawMap (for periodic clearing), isWalkable, getTile, setTile.
Displays the map and handles tile interactions.
- Pacman: Represents the player character.
Attributes: Position (x, y), power-up state.
Methods: draw, startMoving, stopMoving, isPoweredUp.
Moves via a separate thread, responding to user input.
- Ghost: Represents a ghost with state-based behavior.
Attributes: Position (x, y), unique icon (B, P, I, C), current state (GhostState*).
Methods: draw, startMoving, stopMoving, setState, getIcon.
Uses a state machine to switch behaviors, running in a separate thread.

State Pattern Classes
The State Pattern is used to manage ghost behaviors dynamically.

- GhostState (Abstract Base):
Defines the interface for all states.
Methods: update (pure virtual), getIcon (virtual).
Protected constructor sets the state’s icon.
- ChaseState:
Ghosts chase Pacman directly.
Icon: Uses the ghost’s original icon (B, P, I, C).
Behavior: Moves toward Pacman’s position if the path is walkable.
- WanderState:
Ghosts move randomly until Pacman is within 5 tiles, then switch to ChaseState.
Icon: Uses the ghost’s original icon.
Behavior: Picks a random direction, moves if walkable.
- FrightenedState:
Ghosts flee randomly when Pacman eats a power pellet.
Icon: F.
Behavior: Moves in a random direction.
ReturnState:
Ghosts return to the ghost house (position 12,18) after being caught, wait 2 seconds, then switch to WanderState.
Icon: R.
Behavior: Moves to (12,18), waits, then transitions.

Factory Pattern
- GhostFactory:
Creates ghosts dynamically based on difficulty.
Method: createRandomGhost(int x).
Behavior: Randomly assigns an icon (B, P, I, C) and spawns ghosts at specified x positions (y=11).
Used in main.cpp to spawn 1-4 ghosts based on difficulty (1-4).

Decorator Pattern
- ColoredFrightenedState:
Decorates FrightenedState to display the F icon in blue.
Attributes: Wraps a FrightenedState*, manages console color via HANDLE.
Behavior: Sets the console color to blue on creation, resets to white on destruction, delegates update and getIcon to the wrapped state.
Applied in Ghost::moveLoop when transitioning to FrightenedState.

Design Patterns Used
1. State Pattern
Purpose: Allows ghosts to change behavior dynamically (chasing, wandering, fleeing, returning).
Implementation:
GhostState is the abstract base class.
Concrete states (ChaseState, WanderState, FrightenedState, ReturnState) implement specific behaviors.
Ghost holds a currentState pointer, switching states based on game events (e.g., power-up, collision).
Benefit: Encapsulates state-specific behavior, making it easy to add new states.
2. Factory Pattern
Purpose: Dynamically creates ghosts with random types and positions based on difficulty.
Implementation:
GhostFactory::createRandomGhost generates ghosts with random icons (B, P, I, C).
Used in main.cpp to spawn 1-4 ghosts, with positions starting at x=16 and incrementing by difficulty.
Benefit: Centralizes ghost creation, supports extensibility (e.g., adding new ghost types).
3. Decorator Pattern
Purpose: Enhances FrightenedState by adding a colored icon (blue F) without modifying the original state.
Implementation:
ColoredFrightenedState wraps FrightenedState, setting the console color to blue.
Applied in Ghost::moveLoop when transitioning to FrightenedState.
Benefit: Adds visual feedback (color) transparently, allowing further decorations (e.g., blinking) in the future.

Game Features
Difficulty Settings: User inputs a difficulty (1-4), determining the number of ghosts spawned.
Random Ghost Types: Ghosts are randomly assigned icons (B, P, I, C).
Dynamic Positions: Ghosts spawn at y=11, with x starting at 16 and incrementing by difficulty.
State-Based Behavior:
Ghosts wander or chase Pacman normally.
Turn to F (blue) when Pacman eats a pellet.
Turn to R when caught, return to the ghost house, then resume normal behavior.
Map Clearing: A background thread redraws the map every 2 seconds to clear artifacts from ghost movement.

How to Run
Prerequisites:
Windows OS (for console color and positioning).
C++ compiler (e.g., g++ with MinGW for Windows).

Gameplay:
Enter a difficulty (1-4).
Use arrow keys to move Pacman.
Collect pellets (O) to power up, making ghosts frightened (blue F).
Collide with frightened ghosts to send them back to the ghost house (R).

Future Improvements
Per-Ghost Coloring: Set colors individually in Ghost::draw() for more visual distinction.
Scoring System: Add points for collecting pellets and catching ghosts.
Game Over Conditions: Implement win/lose states (e.g., all pellets collected or Pacman caught).
Additional States: Add new ghost behaviors (e.g., ambush, patrol).
Cross-Platform Support: Replace Windows-specific console functions with a portable library (e.g., ncurses).
