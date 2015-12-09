#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GL_3
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    // specify GL 3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        cout << "Window could not be created" << endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float vertices[] = {
         1.0f,  1.0f, // Vertex 1 (X, Y)
         1.0f, -1.0f, // Vertex 2 (X, Y)
        -1.0f, -1.0f, // Vertex 3 (X, Y)
        -1.0f,  1.0f  // Vertex 4 (X, Y)
    };

    GLuint vbo;
    glGenBuffers(1, &vbo); // gen 1 buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // static draw = upload vertex data once, draw many times
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLchar* shaderVec =
    "#version 150 core\n"
    "in vec2 position;"
    "void main() {"
    "   gl_Position = vec4(position, 0.0, 1.0);"
    "}";
    
    const GLchar* shaderFrag =
    "#version 150 core\n"
    "uniform vec2 viewportXY;"
    "out vec4 outColor;"
    "void main() {"
    "   outColor = vec4(gl_FragCoord.xy / viewportXY, 1.0, 1.0);"
    "}";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderVec, NULL);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
        cout << "GL ERROR IN VERTEX SHADER" << endl;
        char logBuf[1024];
        glGetShaderInfoLog( vertexShader, sizeof(logBuf), NULL, (GLchar*)logBuf ); 
        cout << (char*)logBuf << endl;
        cout << glGetString(GL_VERSION) << endl;
        cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
        return -1;
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderFrag, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
        cout << "GL ERROR IN FRAG SHADER" << endl;
        return -1;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // needs to be done before enable vertex attrib pointer because compliance
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    GLint sizeUniform = glGetUniformLocation(shaderProgram, "viewportXY");
    //glUniform3f(sizeUniform, 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glUniform2f(sizeUniform, width, height);

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width/(float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();     
    return 0;
}
