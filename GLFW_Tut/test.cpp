#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* Shader src code */
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

/**
 * @FUNCTION:	Window resize callback 
 * @PARAMS:	GLFW window to resize, width and height 
 * @RETS:	VOID 
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

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
	/* ======== GLFW Init and Config ======== */
	if(!glfwInit())
	{
		std::cout << "Error initing GLFW\n";
		return 1;
	}
	
	/* Using OpenGL 3.3 and using the core */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	/* Set parameters for GLFWWindow state machine */
	GLFWwindow* window = glfwCreateWindow(800, 600, "My first GLFW Window!", NULL, NULL);
	
	if(!window)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	/* Make window */
	glfwMakeContextCurrent(window);

	/* Resize window callback for when user resizes the window */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

	/* ======== GLAD Work ======== */
	/* Locate drivers */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{	
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	/* Basically says how much of the window we created is for rendering stuff using OpenGL */
	glViewport(0, 0, 800, 600);
	

	/* ======== BUILD AND COMPILE SHADER PROGRAM USING SHADER SRC CODE ======== */
	
	/* Debugging setup */
	int success {1};
	char log[512];

	/* Vertex Shader */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	/* Check for errors */
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::VERTEXT::COMPILATION_FAILED\n" << log << std::endl;
	}

	/* Fragment Shader */
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* Check for errors */
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
	}
	
	/* Create shader program */
	unsigned int myFirstShaderProgram = glCreateProgram();

	/* Link the shaders to the shader program */
	glAttachShader(myFirstShaderProgram, vertexShader);
	glAttachShader(myFirstShaderProgram, fragmentShader);
	glLinkProgram(myFirstShaderProgram);
	/* Check for errors */
	glGetProgramiv(myFirstShaderProgram, GL_LINK_STATUS, &success);

	if(!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
	}
	
	/* Now that the shaders are compiled and linked, free them */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* ======== VERTEX DATA SET UP ======== */

	/* Verticies for a triangle that are normalized */
	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	/* ======== VERTEX BUFFER AND ARRAY SET UP ======== */
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);

	/* Now bind VAO so it can track what we are doing! */
	glBindVertexArray(VAO);

	/* Bind and set up vertex buffer */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	/* Render loop */
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		/* Set color of window */
		/* State Setting function */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		/* Actually apply color */
		/* State using function */
		glClear(GL_COLOR_BUFFER_BIT);
	
		/* Tell OpenGL what shader program to use */
		glUseProgram(myFirstShaderProgram);

		/* Bind the VAO with vertex data that we want to draw */
		glBindVertexArray(VAO);

		/* Draw GL_TRIANGLES with out VAO data */
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* GLFW Swap Buffers */
		glfwSwapBuffers(window);

		/* Poll KB/M events */
		glfwPollEvents();    
	}

	/* Clean up */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(myFirstShaderProgram);
	glfwTerminate();
}
