# version 330 core

in vec3 textureDir; // direction vector representing a 3D texture coordinate
uniform samplerCube cubemap; // cubemap texture sampler

void main() {             
    FragColor = texture(cubemap, textureDir);
} 
