#include "shader.hpp"

Shader::Shader(std::string vertex_path, std::string fragment_path) {
    vertex_shader = compile(vertex_path, GL_VERTEX_SHADER);
    fragment_shader = compile(fragment_path, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);
    
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked) {
        std::cout << "error linking program" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLuint Shader::compile(std::string path, GLenum shader_type) {
    const char* shader_code = read_file(path);

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (!status) {
        std::cout << "error compiling shader" << std::endl;
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
        exit(EXIT_FAILURE);
    }

    return shader;
}

const char* Shader::read_file(std::string path) {
    std::string code;
    std::ifstream shader_file;

    shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(path);
        std::stringstream shader_stream;

        shader_stream << shader_file.rdbuf();		

        shader_file.close();

        code = shader_stream.str();		
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* codec = code.c_str();

    return codec;
}

void Shader::use() {
    std::cout << "using shader" << std::endl;
    glUseProgram(program);
}
