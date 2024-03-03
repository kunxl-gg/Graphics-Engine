#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <includes/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "./utils/shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void frambuffer_size_callback(GLFWwindow* window, int widht, int height) {
    glViewport(0, 0, widht, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float objectX = 0.0f;
float objectY = 0.0f;

void moveSpaceShip(GLFWwindow* window) {
    // Check if the 'A' key is pressed
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        objectX -= 0.01f;
    }
    // Check if the 'D' key is pressed
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        objectX += 0.01f;
    }
    // Check if the 'W' key is pressed
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        objectY += 0.01f;
    }
    // Check if the 'S' key is pressed
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        objectY -= 0.01f;
    }
}

int loadTexture() {
    // Creating a texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load("/Users/kunaltiwari/Desktop/Projects/game/assets/spaceship.png", &width, &height, &nrChannels, 0);

    // Check if data is loaded
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    return texture;

}

int main() {
    // Initialise GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    // Creata a window object in using GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if(!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
   }
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL 
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set the viewport size
    glViewport(0, 0, 800, 600); // We are actually defining default viewport

    // Accont for keyboard input
    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);

    // creating shaders
    Shader ourShader("/Users/kunaltiwari/Desktop/Projects/game/src/shaders/vertex.glsl", "/Users/kunaltiwari/Desktop/Projects/game/src/shaders/fragment.glsl");

    // Set up vertex data (a single line)
    float vertices[] = {
        -0.1f, -0.173f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 
         0.1f, -0.173f, 0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.0f,  0.173f, 0.0f,  0.0f, 0.0f, 1.0f,   0.5f, 1.0f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  
   
    // Load the texture
    int texture = loadTexture();

    while(!glfwWindowShouldClose(window)) {
        // clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Handling Keyboard input
        processInput(window);
        moveSpaceShip(window);

        ourShader.use();
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        
        // creting the model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(objectX, objectY, 0.0f));
        ourShader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        // Rendering commands here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
