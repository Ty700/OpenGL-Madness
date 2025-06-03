#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "shaders/shaders.h"

/**
 * @FUNCTION:	Determines if user wants to close window 
 * @PARAMS:	GLFWWindow ptr | Window to close 
 * @RETURNS:	VOID
 */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
	const int glfwWidth = 800; /* px */
	const int glfwHeight = 600; /* px */

	/* GLFW */
	if(!glfwInit())
	{	
		std::cout << "Error: GLFW INIT()" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(glfwWidth, glfwHeight, "Rectangle BRRRRRRRRRR", NULL, NULL);
	
	if(!window)
	{
		std::cout << "Error: GLFW WINDOW CREATE" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	/* GLAD */
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: GLAD FIND PROC" << std::endl;
		return -1;
	}
	
	glViewport(0,0, glfwWidth, glfwHeight);

	/* Shader src(s) */
	std::string vertexSrc = loadShaderSource("vertex_shader.glsl");
	std::string fragmentSrc = loadShaderSource("fragment_shader.glsl");
	
	const char* vertexShaderSrc = vertexSrc.c_str();
	const char* fragmentShaderSrc = fragmentSrc.c_str();

	/* Debugging */
	int success{1};
	char log[512];

	/* Vertex Shader */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShader);

	/* Vertex Shader Error Checking */
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
  		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "ERROR: VERTEX SHADER COMPILATION" << std::endl;
		std::cout << log << std::endl;
		return -1;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShader);
	
	/* Fragment Shader Error Checking */
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
  		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "ERROR: FRAGMENT SHADER COMPILATION" << std::endl;
		std::cout << log << std::endl;
		return -1;
	}
	
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	/* Fragment Shader Error Checking */
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if(!success)
	{
  		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR: SHADER PROGRAM LINKING" << std::endl;
		std::cout << log << std::endl;
		return -1;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* Vertex Set up */
	float vertices[] = {
		0.5f, 0.5f, 0.0f, 	/* Top Right */
		0.5f, -0.5f, 0.0f,	/* Bottom Right */
		-0.5f, -0.5f, 0.0f, 	/* Bottom Left */
		-0.5f, 0.5f, 0.0f,	/* Top Left */
	};
	
	/* Used by EBO */
	unsigned indicies[] = {
		0, 1, 3, 
		1, 2, 3, 
	};

	/* Create object */
	unsigned int EBO, VAO, VBO;
	
	/* Generate buffers on GPU */
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	
	/* VAO is recording our recipe for rectangle now */
	glBindVertexArray(VAO);
	
	/* Bind vertex buffer and place data in it */ 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	/* Bind EBO and place data in it */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	
	/* Descripe data to OpenGL */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	/* Unbind */
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		
		/* Bind to the VAO in shaderProgram */
		glBindVertexArray(VAO);
	
		/* Draw via the EBO and not VBO */
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}
