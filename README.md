# Cub3D

## Overview
Cub3D is a **3D game** built using **C** and **minilibX (MLX)**. It features a simple first-person perspective, utilizing **raycasting** for rendering walls and simulating depth perception.

## Features
- **Raycasting engine** for 3D visualization
- **Player movement and collision detection**
- **Wall rendering with different colors for each face**
- **Mini-map representation**
- **Keyboard controls for navigation**

## Requirements
- A Linux-based operating system
- GCC compiler
- Make utility
- MinilibX (MLX42)
- Libft and GNL libraries

## Installation (if You have mlx in your machine)
Clone the repository:
```sh
git clone https://github.com/usm4/cub3d.git
cd cub3d
```

## Compilation
Use the provided **Makefile** to compile the project:
```sh
make
```
This generates an executable named **cub3d**.

## Usage
Run the game with:
```sh
./cub3d [map.cub]
```
Example:
```sh
./cub3d big_map.cub
```

## Makefile Commands
| Command        | Description                                  |
|---------------|----------------------------------------------|
| `make`        | Compiles the game                           |
| `make clean`  | Removes compiled executables and objects    |
| `make re`     | Cleans and recompiles the project           |

## Raycasting Algorithm Overview
Cub3D uses **raycasting** to determine visible walls and simulate a 3D environment.

1. **Cast a ray for each column of pixels on the screen**
2. **Check horizontal and vertical intersections with walls**
3. **Find the closest intersection and calculate the correct wall height**
4. **Render the walls with perspective scaling**
5. **Apply textures (if implemented)**

### DDA Algorithm (Digital Differential Analyzer)
1. Compute differences `dx` and `dy` between start and end points.
2. Determine the number of steps needed based on the larger difference.
3. Increment x and y values proportionally in each step to draw a line.

## Controls
| Key            | Action            |
|---------------|------------------|
| `W`           | Move forward     |
| `S`           | Move backward    |
| `A`           | Strafe left      |
| `D`           | Strafe right     |
| `Arrow Left`  | Rotate left      |
| `Arrow Right` | Rotate right     |
| `ESC`         | Quit the game    |

## Contributing
Feel free to fork the repository and submit pull requests!

---
**Author:** Oussama Redoine (USM4)

