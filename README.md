# Pacman (C++ / SFML)

<p align="center">
  <img src="Materials/logo32.png" alt="Pacman Logo" width="320"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg?logo=c%2B%2B" alt="C++"/>
  <img src="https://img.shields.io/badge/Library-SFML%202.x-green.svg?logo=sfml" alt="SFML"/>
  <img src="https://img.shields.io/badge/Architecture-OOP%20%2F%20A*--AI-orange.svg" alt="Architecture"/>
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6.svg?logo=windows" alt="Windows"/>
  <img src="https://img.shields.io/badge/License-GPLv3-red.svg" alt="GPLv3"/>
</p>

<p align="center">
  <a href="README.md"><b>Read in English</b></a> | <a href="README_RU.md"><b>Читать на русском</b></a>
</p>

This repository contains a complete, standalone desktop implementation of the classic arcade game Pacman written in **C++** using the **SFML** multimedia library. The project includes full source code, Visual Studio solution files, ready-to-run precompiled binaries with runtime dependencies, original hand-crafted sprite atlases, customizable maze definitions, and a persistent highscore system.

---

## Table of Contents

- [Repository Structure](#repository-structure)
- [Architecture & Application Logic](#architecture--application-logic)
- [Ghost Behavior & Artificial Intelligence](#ghost-behavior--artificial-intelligence)
- [Graphical Assets](#graphical-assets)
  - [Visual Themes](#visual-themes)
  - [Character Spritesheets](#character-spritesheets)
- [Gameplay & Controls](#gameplay--controls)
- [Level Map Format](#level-map-format)
- [How to Run and Build](#how-to-run-and-build)
  - [Instant Play](#instant-play-no-build-required)
  - [Build with Visual Studio](#build-with-visual-studio)
- [License](#license)

---

## Repository Structure

The repository provides everything required to inspect, build, modify, and run the game:

| Folder / File | Purpose |
| :--- | :--- |
| **`Headers/`** | C++ header files (`.h`): declarations for entities (Pacman, 4 ghosts, maze map, custom UI components, global settings). |
| **`Materials/`** | Graphical and audio assets: hand-drawn spritesheets, maze wall tiles, backgrounds, title logos, icon, and font. |
| **`Maps/`** | Plain-text maze files (`Map_Standart.txt`, `Map_Labyrinth.txt`, `Map_Loops.txt`, etc.). |
| **`Settings/`** | Configuration files: available level roster (`Maps.txt`), active themes (`LevelColors.txt`), and graphics settings (`Settings.txt`). |
| **`Highscores/`** | Persistent per-map leaderboard score files. |
| **`Main.cpp`**, **`*.cpp`** | Source files implementing core gameplay, game loop, ghost artificial intelligence, and user interface. |
| **`Pacman.sln`**, **`Pacman.vcxproj`** | Solution and project files for Microsoft Visual Studio. |
| **`Pacman.exe`** | Standalone precompiled game executable for Windows. |
| **`*.dll`** | Dynamic runtime libraries for SFML (`sfml-graphics`, `sfml-window`, `sfml-system`, `sfml-audio`, `sfml-network`) and OpenAL. |

---

## Architecture & Application Logic

The application coordinates its subsystems through a modular structure:

```mermaid
flowchart TD
    subgraph Core["1. Core & State Management"]
        GL["Global.h / Global.cpp (Global context, timers)"]
        M["Main.cpp (FSM: Menu / Game / Pause / Settings)"]
    end

    subgraph Entities["2. Game Entities & OOP"]
        P["Pacman (Sub-pixel movement, collisions, tunnels)"]
        G["Ghost (Base class: A*, bitfield state flags)"]
        G --> B["Blinky (Direct target intercept)"]
        G --> PK["Pinky (Lead vector +4 tiles)"]
        G --> I["Inky (Flanking vector via Blinky)"]
        G --> C["Clyde (Proximity trigger: retreat if distance &lt; 8)"]
    end

    subgraph MapSys["3. Procedural Maze Generation"]
        MP["Map.cpp (21x21 matrix parser)"]
        AT["Bitwise Wall Autotiling (Marching Squares, 16 states)"]
        MP --> AT
    end

    subgraph UISys["4. Custom GUI Engine over SFML"]
        A["Area (Mouse detection)"] --> R["Rectangle (Geometry)"]
        R --> BT["Button (Interactive FSM)"]
        T["Text (Typography)"] --> BT
    end

    M --> P
    M --> G
    M --> MP
    M --> A
```

### Core Logic Overview:
- **Game State Machine (FSM):** Manages transitions between the main menu, settings dialog, active gameplay session, pause overlay, game over, and victory screens.
- **Delta-Time Scaled Movement:** Movement velocities are scaled by frame duration (`_Settings::__ElapsedTime`), maintaining consistent game speed regardless of monitor refresh rate.
- **Continuous-Discrete Grid Projection:** Character positions move with sub-pixel floating-point smoothness, while collisions, dot consumption, and pathfinding queries project onto a discrete $21 \times 21$ tile matrix.
- **Lightweight Custom GUI:** Menus and buttons are constructed using an internal component hierarchy (`Area` -> `Rectangle` -> `Text` -> `Button`) that dispatches mouse events without external heavyweight dependencies.

---

## Ghost Behavior & Artificial Intelligence

The game implements canonical ghost behaviors with distinct targeting heuristics powered by the **A\*** (A-Star) pathfinding algorithm:

```
                              [ Pacman ]
                                  ▲
        ┌────────────────┬────────┴────────┬────────────────┐
        │ Direct Pursuit │ Ambush (+4 sq.) │ Flank Vector   │ Scatter / Flee
        │                │                 │                │ (if closer than 8 sq.)
        ▼                ▼                 ▼                ▼
   [ Blinky 🔴 ]    [ Pinky 🌸 ]      [ Inky 🔷 ]      [ Clyde 🟠 ]
```

| Ghost | Sprite | Target Cell Selection Logic |
| :--- | :---: | :--- |
| **Blinky** (Red) | <img src="Materials/Ghost32_Default.png" width="32" height="32" style="object-fit: cover; object-position: 0 0;" alt="Blinky"/> | **Direct Chaser:** Directly targets Pacman's current coordinate. The most relentless pursuer. In scatter phase, patrols the top-right corner. |
| **Pinky** (Pink) | <img src="Materials/Ghost32_Default.png" width="32" height="32" style="object-fit: cover; object-position: -32px 0;" alt="Pinky"/> | **Ambusher:** Targets 4 tiles ahead of Pacman's current heading direction to cut off escape corridors. |
| **Inky** (Cyan) | <img src="Materials/Ghost32_Default.png" width="32" height="32" style="object-fit: cover; object-position: -64px 0;" alt="Inky"/> | **Flanker:** Constructs a vector from Blinky's coordinates to the spot ahead of Pacman and doubles it to execute pincer maneuvers. |
| **Clyde** (Orange) | <img src="Materials/Ghost32_Default.png" width="32" height="32" style="object-fit: cover; object-position: -96px 0;" alt="Clyde"/> | **Proximity Trigger:** Pursues Pacman when distance $\ge 8$ tiles; retreats toward home corner when closing in closer than 8 tiles. |

### Ghost State Cycles:
- **Chase:** Active pursuit toward computed target coordinates along shortest navigable paths.
- **Scatter:** Timed periodic disengagement where ghosts return to loop around their home quadrant corners.
- **Frightened:** Triggered upon energizer consumption. The A\* pathfinder inverts node costs, routing ghosts away from Pacman at reduced speed.
- **Eaten:** Defeated ghost eyes chart an expedited A\* path directly back to the central spawn house to revive.

---

## Graphical Assets

All graphical resources (character animations, ghost states, death sequences, and maze structure blocks) were drawn by hand. The assets are stored in the `Materials/` folder as structured horizontal spritesheets.

### Visual Themes

Three visual styles are included and selectable from the game's settings menu:

| Theme | Maze Wall Tiles (`Map32_*.png`) | Ghost Spritesheet (`Ghost32_*.png`) | Description |
| :--- | :---: | :---: | :--- |
| **Default** | <img src="Materials/Map32_Default.png" width="170" alt="Map Default"/> | <img src="Materials/Ghost32_Default.png" width="170" alt="Ghost Default"/> | Classic arcade color scheme with blue maze walls and canonical ghost colors. |
| **Cyber** | <img src="Materials/Map32_Cyber.png" width="170" alt="Map Cyber"/> | <img src="Materials/Ghost32_Cyber.png" width="170" alt="Ghost Cyber"/> | High-tech neon theme with circuit-style walls and futuristic apparitions. |
| **Spooky** | <img src="Materials/Map32_Spooky.png" width="170" alt="Map Spooky"/> | <img src="Materials/Ghost32_Spooky.png" width="170" alt="Ghost Spooky"/> | Dark gothic Halloween theme with stone masonry and eerie spirits. |

All texture sheets are provided in three native resolution tiers: **16×16**, **32×32**, and **64×64** pixels (`Materials/*16.png`, `*32.png`, `*64.png`), allowing window scaling without pixel blur or distortion.

### Character Spritesheets

| Movement Sequence (`Pacman32.png`) | Death Sequence (`PacmanDeath32.png`) |
| :---: | :---: |
| <img src="Materials/Pacman32.png" width="180" alt="Pacman Walk"/> | <img src="Materials/PacmanDeath32.png" width="220" alt="Pacman Death"/> |

---

## Gameplay & Controls

- **Wall Autotiling:** Maze walls automatically resolve their visual shapes (corners, straight runs, T-junctions, crossways) based on neighbor analysis.
- **Seamless Tunnels:** Side tunnels project duplicate sprites across opposite boundaries to eliminate edge clipping.
- **Leaderboards:** Per-map persistent record tables saved to the `Highscores/` directory.

### Controls:
- **Movement:** `W`, `A`, `S`, `D` or Arrow Keys (`Up`, `Left`, `Down`, `Right`).
- **Pause:** `Escape`.
- **Menu Navigation:** Left Mouse Click.

---

## Level Map Format

Mazes are stored under `Maps/` as plain text matrices containing $21 \times 21$ values:

```text
1 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 1
1 4 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 4 1
...
```

- `0` — Ghost house door (permeable only to ghosts);
- `1` — Empty walkable corridor;
- `2` — Energizer (power pellet);
- `3` — Pellet (regular dot);
- `4` — Wall (dynamically styled by autotiling);
- `5` — Pacman starting position;
- `6..9` — Ghost spawn positions (Blinky, Pinky, Inky, Clyde).

To add a custom level, place `Maps/Map_CustomName.txt` in the folder and register its name in `Settings/Maps.txt`.

---

## How to Run and Build

### Instant Play (No Build Required)
The repository includes precompiled binaries and all required dependencies:
1. Clone the repository:
   ```powershell
   git clone https://github.com/MalenkiySolovey/Pacman.git
   ```
2. Double-click **`Pacman.exe`** in the root folder to launch the game.

### Build with Visual Studio
1. Open the solution file **`Pacman.sln`** in Microsoft Visual Studio (2019 or 2022).
2. Select configuration **`Release`** or **`Debug`** (platform **`x86`**).
3. Press `F5` or `Ctrl + Shift + B` to build and run. SFML headers and libraries are configured with relative project paths.

---

## License

This project is distributed under the **GNU General Public License v3.0 (GPLv3)**. For the full license text, see [LICENSE](LICENSE).
