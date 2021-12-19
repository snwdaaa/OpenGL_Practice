#include <iostream>

// glad, GLFW include
// glad를 GLFW보다 먼저 include 해야하는 것에 주의
// glad.h가 OpenGL의 header들을 포함하고 있기 때문
// 그러므로 OpenGL을 사용하는 헤더 파일들을 include 하기 전에 glad를 먼저 include 해야 함
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// 함수 프로토타입
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	glfwInit(); // GLFW 라이브러리를 초기화.

	// glfwWindowHint(a, b): GLFW를 설정 함
	// a: 설정하고 싶은 옵션. GLFW_라는 접두사가 붙은 enum 옵션들을 이용.
	// b: 옵션 a를 설정하고 싶은 정수 값.

	// GLFW_CONTEXT_VERSION_MAJOR, GLFW_CONTEXT_VERSION_MINOR 두 개를 모두 3으로 설정
	// => 사용자의 OpenGL 버전이 3.3 이상이 아니면 오류를 발생하게 함.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// OpenGL을 core-profile mode로 동작시키기 위해
	// GLFW_OPENGL_PROFILE을 GLFW_OPENGL_CORE_PROFILE로 설정
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// window 오브젝트 만들기
	// window 오브젝트 -> 보여지는 모든 데이터를 담고 있음
	// glfwCreateWindow 함수로 window를 만든 후 GLFWwindow 타입의 포인터 변수에 저장
	// glfwCreateWindow(가로, 세로, 타이틀, GLFWmonitor* monitor, GLFWwindow* share) -> GLFWwindow 타입의 오브젝트 반환
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	// window가 NULL 값이면 glfwTerminate 함수 호출 후 종료
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// window의 크기가 바뀔 때 두 번째 인자로 주어진 콜백 함수를 호출
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OpenGL 관련 함수가 호출되기 전에 GLAD 초기화하기
	// GLAD가 OpenGL의 모든 함수 포인터들을 관리
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 프로그램이 꺼지지 않게 loop를 돌려줘야 함 => render loop
	// 이 render loop 한 번을 수행하면 1 프레임
	// glfwWindowShouldClose: 인자로 입력된 window가 GLFW에게 종료 명령을 받았는지 매 loop iteration마다 확인함
	// 종료 명령을 받으면 true, 아니면 false 반환
	while (!glfwWindowShouldClose(window))
	{
		// 입력 확인
		processInput(window);

		// rendering commands
		// 매 frame마다 rendering 관련 commands 실행
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT); // color buffer를 clear

		// front buffer와 back buffer를 바꿈
		glfwSwapBuffers(window);
		// glfwPollEvents 함수는 이벤트 호출(키보드 입력 등), window 상태 업데이트,
		// callback 함수 호출 등의 이벤트를 체크
		glfwPollEvents();
	}

	// 종료 전에 GLFW에서 할당했던 모든 리소스 해제
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	// glfwGetKey 함수: 두 번째 인자로 받은 키의 입력 여부를 반환.
	// 입력되지 않았으면 glfwGetKey 함수는 GLFW_RELEASE를 반환
	// ESC 키를 누르고 있으면 창을 닫는다.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// glfwSetWindowShouldClose 함수: window의 WindowShouldClose 속성의 값을 변경
		glfwSetWindowShouldClose(window, true);
	}
}

// window 사이즈가 바뀔 때 viewport 사이즈도 그에 맞게 바꿔야 함
// window 사이즈가 바뀔 때마다 호출됨
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// OpenGL이 window의 사이즈를 알고 있어야 데이터를 상대적으로
	// 어디에 표시할지 알게 됨
	// => glViewport 함수 사용
	// glViewport(모니터 왼쪽 위 x 좌표, 모니터 왼쪽 위 y 좌표, width, height)
	glViewport(0, 0, width, height);
}