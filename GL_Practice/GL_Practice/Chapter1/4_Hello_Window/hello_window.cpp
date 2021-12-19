#include <iostream>

// glad, GLFW include
// glad�� GLFW���� ���� include �ؾ��ϴ� �Ϳ� ����
// glad.h�� OpenGL�� header���� �����ϰ� �ֱ� ����
// �׷��Ƿ� OpenGL�� ����ϴ� ��� ���ϵ��� include �ϱ� ���� glad�� ���� include �ؾ� ��
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// �Լ� ������Ÿ��
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit(); // GLFW ���̺귯���� �ʱ�ȭ.

	// glfwWindowHint(a, b): GLFW�� ���� ��
	// a: �����ϰ� ���� �ɼ�. GLFW_��� ���λ簡 ���� enum �ɼǵ��� �̿�.
	// b: �ɼ� a�� �����ϰ� ���� ���� ��.

	// GLFW_CONTEXT_VERSION_MAJOR, GLFW_CONTEXT_VERSION_MINOR �� ���� ��� 3���� ����
	// => ������� OpenGL ������ 3.3 �̻��� �ƴϸ� ������ �߻��ϰ� ��.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// OpenGL�� core-profile mode�� ���۽�Ű�� ����
	// GLFW_OPENGL_PROFILE�� GLFW_OPENGL_CORE_PROFILE�� ����
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// window ������Ʈ �����
	// window ������Ʈ -> �������� ��� �����͸� ��� ����
	// glfwCreateWindow �Լ��� window�� ���� �� GLFWwindow Ÿ���� ������ ������ ����
	// glfwCreateWindow(����, ����, Ÿ��Ʋ, GLFWmonitor* monitor, GLFWwindow* share) -> GLFWwindow Ÿ���� ������Ʈ ��ȯ
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	// window�� NULL ���̸� glfwTerminate �Լ� ȣ�� �� ����
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// window�� ũ�Ⱑ �ٲ� �� �� ��° ���ڷ� �־��� �ݹ� �Լ��� ȣ��
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OpenGL ���� �Լ��� ȣ��Ǳ� ���� GLAD �ʱ�ȭ�ϱ�
	// GLAD�� OpenGL�� ��� �Լ� �����͵��� ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ���α׷��� ������ �ʰ� loop�� ������� �� => render loop
	// �� render loop �� ���� �����ϸ� 1 ������
	// glfwWindowShouldClose: ���ڷ� �Էµ� window�� GLFW���� ���� ����� �޾Ҵ��� �� loop iteration���� Ȯ����
	// ���� ����� ������ true, �ƴϸ� false ��ȯ
	while (!glfwWindowShouldClose(window))
	{
		// �Է� Ȯ��
		processInput(window);

		// rendering commands
		// �� frame���� rendering ���� commands ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // color buffer�� clear

		// front buffer�� back buffer�� �ٲ�
		glfwSwapBuffers(window);
		// glfwPollEvents �Լ��� �̺�Ʈ ȣ��(Ű���� �Է� ��), window ���� ������Ʈ,
		// callback �Լ� ȣ�� ���� �̺�Ʈ�� üũ
		glfwPollEvents();
	}

	// ���� ���� GLFW���� �Ҵ��ߴ� ��� ���ҽ� ����
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	// glfwGetKey �Լ�: �� ��° ���ڷ� ���� Ű�� �Է� ���θ� ��ȯ.
	// �Էµ��� �ʾ����� glfwGetKey �Լ��� GLFW_RELEASE�� ��ȯ
	// ESC Ű�� ������ ������ â�� �ݴ´�.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// glfwSetWindowShouldClose �Լ�: window�� WindowShouldClose �Ӽ��� ���� ����
		glfwSetWindowShouldClose(window, true);
	}
}

// window ����� �ٲ� �� viewport ����� �׿� �°� �ٲ�� ��
// window ����� �ٲ� ������ ȣ���
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// OpenGL�� window�� ����� �˰� �־�� �����͸� ���������
	// ��� ǥ������ �˰� ��
	// => glViewport �Լ� ���
	// glViewport(����� ���� �� x ��ǥ, ����� ���� �� y ��ǥ, width, height)
	glViewport(0, 0, width, height);
}