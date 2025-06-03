#version 330 core 
out vec4 FragColor; /* Because color is a 4 unit Vector (RGBA) with A being the opacity */

void main()
{
	/* Hard coding a color */
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}

