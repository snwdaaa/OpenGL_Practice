#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// vertex shader의 정의와 컴파일
// vertex shader의 정의는 코드 상단에 const char*으로
const char* vertexShaderSource =
	"#version 330 core\n"	// OpenGL 버전(3.3) & core-profile 모드 사용 명시
	"layout (location = 0) in vec3 aPos;\n" // 정점 데이터를 aPos라는 3차원 벡터 데이터 타입의 변수에 담음
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	// vertex shader의 출력을 담을 gl_Position 변수
	"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit(); // glfw 라이브러리 초기화
	// OpenGL 3.3 이상만 지원
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core-profile 모드

	// glfw window 생성
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 사이즈 변경 콜백 함수

	// glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		return -1;
	}

	// graphics pipeline
	
	// vertex shader 컴파일
	// 쉐이더 오브젝트를 저장할 unsigned int형의 변수를 만든다.
	unsigned int vertexShader;
	// 쉐이더 오브젝트를 만든 후 변수에 저장한다.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// vertex shader의 코드를 가져온다.
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // glShaderSource(컴파일 할 쉐이더 오브젝트, vertex shader GLSL 코드의 string 수, vertex shader의 GLSL 코드, NULL)
	// vertex shader를 컴파일 한다.
	glCompileShader(vertexShader);
	// glCompileShader 호출 후 vertex shader 컴파일 오류 확인
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// 컴파일 실패
	if (!success)
	{	// 에러 메시지 출력
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	// 삼각형의 정점
	// 정규화 장치 좌표(Normalized Device Coordinates, NDC)로 표현함
	// x, y, z는 각각 0.0 ~ 1.0 사이의 값을 가짐
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO); // 버퍼를 만든 후 유니크 ID를 부여(1)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 버퍼의 타입을 정점 버퍼(vertex buffer)로 설정
	// glBufferData(데이터를 복사할 버퍼의 타입, 버퍼에 저장할 데이터의 크기(바이트), 저장할 데이터, 그래픽카드의 데이터 처리 방식)
	// 이전에 정의한 정점 데이터를 버퍼 메모리(정점 버퍼)로 복사함
	// 그래픽 카드 데이터 처리 방식 => GL_STREAM_DRAW(한 번 설정되고 GPU가 가능한 적게 사용), GL_STATIC_DRAW(한 번 설정되고 자주 쓰임), 
	// GL_DYNAMIC_DRAW(자주 바뀌고 자주 사용됨) -> 자료의 종류에 따라 적절하게 설정해야 함
	// 삼각형의 정점의 경우는 바뀌지 않고 자주 사용되므로 GL_STATIC_DRAW가 적절함
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// -----------------

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// 입력 감지
		processInput(window);

		// 색 변경
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// buffer swap
		glfwSwapBuffers(window);
		// 이벤트 감지
		glfwPollEvents();
	}
}

// window 사이즈 변경 시 호출할 콜백 함수
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// viewport의 크기를 새로운 window에 맞춤
	glViewport(0, 0, width, height);
}

// ESC 클릭하면 종료
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}