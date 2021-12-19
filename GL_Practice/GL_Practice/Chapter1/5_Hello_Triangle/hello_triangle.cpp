#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// vertex shader�� ���ǿ� ������
// vertex shader�� ���Ǵ� �ڵ� ��ܿ� const char*����
const char* vertexShaderSource =
	"#version 330 core\n"	// OpenGL ����(3.3) & core-profile ��� ��� ���
	"layout (location = 0) in vec3 aPos;\n" // ���� �����͸� aPos��� 3���� ���� ������ Ÿ���� ������ ����
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	// vertex shader�� ����� ���� gl_Position ����
	"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit(); // glfw ���̺귯�� �ʱ�ȭ
	// OpenGL 3.3 �̻� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core-profile ���

	// glfw window ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ������ ���� �ݹ� �Լ�

	// glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}

	// graphics pipeline
	
	// vertex shader ������
	// ���̴� ������Ʈ�� ������ unsigned int���� ������ �����.
	unsigned int vertexShader;
	// ���̴� ������Ʈ�� ���� �� ������ �����Ѵ�.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// vertex shader�� �ڵ带 �����´�.
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // glShaderSource(������ �� ���̴� ������Ʈ, vertex shader GLSL �ڵ��� string ��, vertex shader�� GLSL �ڵ�, NULL)
	// vertex shader�� ������ �Ѵ�.
	glCompileShader(vertexShader);
	// glCompileShader ȣ�� �� vertex shader ������ ���� Ȯ��
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// ������ ����
	if (!success)
	{	// ���� �޽��� ���
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	// �ﰢ���� ����
	// ����ȭ ��ġ ��ǥ(Normalized Device Coordinates, NDC)�� ǥ����
	// x, y, z�� ���� 0.0 ~ 1.0 ������ ���� ����
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO); // ���۸� ���� �� ����ũ ID�� �ο�(1)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // ������ Ÿ���� ���� ����(vertex buffer)�� ����
	// glBufferData(�����͸� ������ ������ Ÿ��, ���ۿ� ������ �������� ũ��(����Ʈ), ������ ������, �׷���ī���� ������ ó�� ���)
	// ������ ������ ���� �����͸� ���� �޸�(���� ����)�� ������
	// �׷��� ī�� ������ ó�� ��� => GL_STREAM_DRAW(�� �� �����ǰ� GPU�� ������ ���� ���), GL_STATIC_DRAW(�� �� �����ǰ� ���� ����), 
	// GL_DYNAMIC_DRAW(���� �ٲ�� ���� ����) -> �ڷ��� ������ ���� �����ϰ� �����ؾ� ��
	// �ﰢ���� ������ ���� �ٲ��� �ʰ� ���� ���ǹǷ� GL_STATIC_DRAW�� ������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// -----------------

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// �Է� ����
		processInput(window);

		// �� ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// buffer swap
		glfwSwapBuffers(window);
		// �̺�Ʈ ����
		glfwPollEvents();
	}
}

// window ������ ���� �� ȣ���� �ݹ� �Լ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// viewport�� ũ�⸦ ���ο� window�� ����
	glViewport(0, 0, width, height);
}

// ESC Ŭ���ϸ� ����
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}