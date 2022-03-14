#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) 
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	int a = 4;
	HZ_INFO("Hello! a = {0}", a);

	std::cout << "Hazel Engine running..." << std::endl;
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
