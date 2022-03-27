#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// to be define in client
	Application* CreateApplication();

}

