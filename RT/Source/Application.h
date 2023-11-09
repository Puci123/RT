#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<string>

#include "ImGUI/imgui_impl_opengl3.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_internal.h"

#include "Texture2D.h"
#include "Scean.h"

class Applciation
{
	public:
		Applciation(uint32_t windowWidth, uint32_t windowHeight, const std::string& name);
		~Applciation();

		void Start();
		void PerFrame();

		inline bool IsRuning() const { return  !glfwWindowShouldClose(m_Window) && m_IsRunning;}

	private:

		GLFWwindow* m_Window;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;

		ImGuiIO* m_ImGuiIO;
		const char* m_GlslVersion = "#version 130"; // for ImGUI

		std::string m_AppName;

		Texture2D* m_TargetTexture;
		Scean m_Scean;

		mu::vec2 m_ViwiePortSize;

		bool m_IsRunning;

};

