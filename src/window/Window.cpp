#include <window/Window.h>

// Include IO stream
#include <iostream>

// Include ImGui
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// Include stb
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Include settings
#include "settings.h"

Window::Window(const char* title)
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
	window = glfwCreateWindow(Settings::window_width, Settings::window_height, title, NULL, NULL);
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

	glfwSwapInterval(Settings::enable_vsync);

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
	Settings::imgui_style(NULL);

	// Load Roboto Font:
	io.Fonts->AddFontFromFileTTF((CMAKE_SOURCE_DIR "/lib/imgui-1.89.4/misc/fonts/Roboto-Medium.ttf"), Settings::font_size);

	// Window Icon
	GLFWimage icon;
	icon.pixels = stbi_load(CMAKE_SOURCE_DIR "/images/icon.png", &icon.width, &icon.height, NULL, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(icon.pixels);

}

Window::~Window(void)
{
	std::cout << "Destroy ImGui context." << std::endl;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	std::cout << "Destroy Window" << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::start(void)
{
	while (!glfwWindowShouldClose(window))
	{
		// start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Resets viewport
		glViewport(0, 0, get_width(), get_height());

		// Clears the image
		glClear(GL_COLOR_BUFFER_BIT);
		const Vec4f bg_color = Settings::background_color;
		glClearColor(bg_color.x, bg_color.y, bg_color.z, bg_color.w);

		// Calls the update method
		this->update();

		// Render the GUI and draw it to the screen:
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swaps the buffers
		glfwSwapBuffers(window);

		// Polls the GLFW input events
		glfwPollEvents();
	}

}

void Window::update(void)
{
	ImGui::ShowDemoWindow();
}

int Window::get_width(void) const
{
	int width;
	glfwGetFramebufferSize(window, &width, NULL);
	return width;
}

int Window::get_height(void) const
{
	int height;
	glfwGetFramebufferSize(window, NULL, &height);
	return height;
}