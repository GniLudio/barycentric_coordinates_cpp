#include <window/Window.h>

// Include IO stream
#include <iostream>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Window::Window(char* title, int width, int height, float fontSize, ImGuiStyleFunction imGuiStyle)
{
	// sets GLFW error callback
	glfwSetErrorCallback([](int error, const char* description)
	{
		std::fprintf(stderr, "GLFW Error (%d): %s", error, description);
		exit(EXIT_FAILURE);
	});

	// initializes GLFW
	if (!glfwInit())
	{
		std::cerr << "Couldn't initialize GLFW." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "GLFW initialized" << std::endl;

	// Decide GL+GLSL versions:
	const char* glsl_version = "#version 330 core";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// creates the GLFW window
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window)
	{
		std::cerr << "Couldn't create window. (" << title << ")" << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}
	std::cout << "Window created." << std::endl;

	// sets input callback
	glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int, int action, int) {
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(w, GLFW_TRUE);
	});

	// sets the OpenGL context
	glfwMakeContextCurrent(window);

	// sets the swap interval
	glfwSwapInterval(1);

	// intializes GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Couldn't initialize GLAD" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	std::cout << "GLAD initialized." << std::endl;

	// setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	std::cout << "IMGui context created." << std::endl;

	// Setup Platform/Renderer backends:
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup ImGui style.
	imGuiStyle(NULL);

	// Load Roboto Font:
	io.Fonts->AddFontFromFileTTF((CMAKE_SOURCE_DIR "/lib/imgui-1.89.4/misc/fonts/Roboto-Medium.ttf"), fontSize);

	// Window Icon
	GLFWimage images[1];
	images[0].pixels = stbi_load(CMAKE_SOURCE_DIR"/images/icon.png", &images[0].width, &images[0].height, NULL, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);
}

Window::~Window()
{
	std::cout << "Destroy ImGui context." << std::endl;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	std::cout << "Destroy Window" << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::Start()
{
	while (!glfwWindowShouldClose(window))
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Resets viewport
		glViewport(0, 0, getWidth(), getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		// Calls the Update method
		this->Update();

		// Render the GUI and draw it to the screen:
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swaps the buffers
		glfwSwapBuffers(window);

		// Polls the GLFW input events
		glfwPollEvents();
	}

}

void Window::Update()
{
	ImGui::ShowDemoWindow();
}

int Window::getWidth(void) const
{
	int width;
	glfwGetFramebufferSize(window, &width, NULL);
	return width;
}

int Window::getHeight(void) const
{
	int height;
	glfwGetFramebufferSize(window, NULL, &height);
	return height;
}