#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main()
{
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
	
	/* Make window */
	glfwMakeContextCurrent(window);

	/* Locate drivers */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{	
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}    

	/* Basically says how much of the window we created is for rendering stuff using OpenGL */
	glViewport(0, 0, 800, 600);
	
	/* Resize window callback for when user resizes the window */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

	/* Render loop */
	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	/* Clean up */
	glfwTerminate();
}
