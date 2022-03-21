#include "hzpch.h"
#include "WindowsWindow.h"


//#include "Hazel/Events/ApplicationEvent.h"
//#include "Hazel/Events/MouseEvent.h"
//#include "Hazel/Events/KeyEvent.h"


namespace Hazel {

	static uint8_t s_GLFWWindowCount = 0;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		//HZ_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		//HZ_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		//HZ_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{
			//HZ_PROFILE_SCOPE("glfwInit");
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			//HZ_PROFILE_SCOPE("glfwCreateWindow");
//#if defined(HZ_DEBUG)
//			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
//				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
//#endif
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}


		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);


	}

	void WindowsWindow::Shutdown()
	{
		//HZ_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		//HZ_PROFILE_FUNCTION();

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
		//m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//HZ_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}