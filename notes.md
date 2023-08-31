## Refactor

1. One method that knows how to draw a _voxel_
2. One method that receives a texture and draws things correctly


## RENDERER

Knows know to draw stuff

Receives a shader and a texture

Draw any object?

## MESH

Receives a bunch of cube faces (vertices and indices) and draws everything
Calls renderer with the correct shaders and textures

### Meshes

1. World
    - Uses general block shader with lighting
    - Uses atlas texture

2. Water
    - Uses water shader, deals with all transparent stuff, water movement?
    - Use water texture from atlas is OK




