#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {

	std::cout << "Hazel Engine running..." << std::endl;
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
