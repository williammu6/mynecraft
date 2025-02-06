# Mynecraft - A C++ Minecraft "Clone"

![mynecraft](screenshots/mynecraft2.png)

## Introduction

The goal of this project is to learn more about "modern" C++ and OpenGL, while creating a basic Minecraft-inspired game.

## Features

- Proceduraly generated world
- Player movement
- Destroying blocks within a certain range from the player
- Placing blocks
- Basic lighting

## Getting Started

### Requirements

To build and run Mynecraft, you need the following

- C++17 or later compiler
- CMake (version 3.10 or higher)
- OpenGL

_I've only tested it on Mac_

### Building

1. Clone the repository

```sh
git clone https://github.com/williammu6/mynecraft.git --recursive
cd mynecraft
```

2. Create a build directory

```sh 
mkdir build
cd build
```


3. Build
```sh
cmake .. -B.
make
```

### Running

```sh
./Mynecraft <seed>
```
