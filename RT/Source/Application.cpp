#include <iostream>

#include "Application.h"
#include "DebugUtilty.h"
#include "Renderer.h"
#include "Materials.h"

Applciation::Applciation(uint32_t windowWidth, uint32_t windowHeight, const std::string& name)
	: m_WindowHeight(windowHeight), m_WindowWidth(windowWidth), m_AppName(name)
{
	//================================== INT WINDOW ==========================//

	
	ASSERT_L(glfwInit(), " can't initalize GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_AppName.c_str(), NULL, NULL);
	ASSERT_L(m_Window, " can't create window");
	
	glfwMakeContextCurrent(m_Window);
	ASSERT_L(glewInit() == GLEW_OK, " unable to initalize GLEW");

	glfwSwapInterval(1);	 // 1/0 | enable/disable vsync

	
	//================================== Init ImGui ================================== //

	//set up IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	m_ImGuiIO = &ImGui::GetIO(); (void)m_ImGuiIO;
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	m_ImGuiIO->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	//set style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 1.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init(m_GlslVersion);


	//Crete target Texture
	m_TargetTexture = new Texture2D(1, 1); 

	m_IsRunning = true;

}

Applciation::~Applciation()
{
}

void Applciation::Start()
{
	std::cout << "App is starting" << std::endl;
	
	Material mat1;
	mat1.allbedo = mu::vec3(0.7803921568627451, 0.06666666666666667, 0.6431372549019608);
	mat1.materialType = Material::MaterialType::Diffues;

	Material mat2;
	mat2.allbedo = mu::vec3(0, 0.3254901960784314, 0.5843137254901961);
	mat2.materialType = Material::MaterialType::Diffues;

	Material metalic1;
	metalic1.allbedo = mu::vec3(1, 1, 1);
	metalic1.fuzzines = 0.5f;
	metalic1.materialType = Material::MaterialType::Metalic;

	Material metalic2;
	metalic2.allbedo = mu::vec3(0.541176470588, 0.23921568627450981, 0.4823529411764706);
	metalic2.fuzzines = 0.0f;
	metalic2.materialType = Material::MaterialType::Metalic;


	m_Scean.M_Shapes.push_back(Shape(0, 0, -1.5, 0.5,mat1));
	m_Scean.M_Shapes.push_back(Shape(1.75, 0, -2, 0.5, metalic1));
	m_Scean.M_Shapes.push_back(Shape(-1.75, 0, -2, 0.5, metalic2));
	m_Scean.M_Shapes.push_back(Shape(0, -100.5, -1, 100,mat2));

}

void Applciation::PerFrame()
{
	/* Poll for and process events */
	glfwPollEvents();

	//================================== Render GUI ================================== //
	
	//Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ------------------------------ GUI CODE HERE ---------------------//
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); //Enable docking UI

	//Vwie port Panel 
	ImGui::Begin("Vwie port");
	{
		ImVec2 viwieSize = ImGui::GetContentRegionMax();

		//Resiaze taraget texture aftet resizing viwie port
		if ((static_cast<int>(viwieSize.x) != static_cast<int>(m_ViwiePortSize.x) || static_cast<int>(viwieSize.y) != static_cast<int>(m_ViwiePortSize.y)) && !m_ImGuiIO->MouseDown[0])
		{
			delete m_TargetTexture;
			m_TargetTexture = new Texture2D(static_cast<int>(viwieSize.x), static_cast<int>(viwieSize.y));
			m_ViwiePortSize.x = viwieSize.x;
			m_ViwiePortSize.y = viwieSize.y;
		}

		m_TargetTexture->Bind();
		ImGui::Image((void*)(intptr_t)(m_TargetTexture->GetID()), ImVec2(static_cast<float>(viwieSize.x), static_cast<float>(viwieSize.y - 8.0)), ImVec2(0.f, 0.f), ImVec2(1.f, 1.f)); //Draw target texture
		m_TargetTexture->Unbind();
	}
	ImGui::End();

	//Property Panle 
	ImGui::Begin("MENU");
	{
		ImVec2 viwieSize = ImGui::GetContentRegionMax();

		if (ImGui::Button("Trace",ImVec2(viwieSize.x, 30)))
		{
			Rendere::Trace(m_TargetTexture, m_Scean, 5,50); //TODO: 10, 100 are temporary values
			m_TargetTexture->Update();
		}

		if (ImGui::Button("Corect gamma", ImVec2(viwieSize.x, 30)))
		{
			Rendere::AlphaCorrect(m_TargetTexture);
			m_TargetTexture->Update();
		}


		if (ImGui::CollapsingHeader("Background"))
		{
			float uppColor[3]{static_cast<float>(m_Scean.M_ColorUp.x),    static_cast<float>(m_Scean.M_ColorUp.y),   static_cast<float>(m_Scean.M_ColorUp.z)};
			float dowColor[3]{static_cast<float>(m_Scean.M_ColorDown.x),  static_cast<float>(m_Scean.M_ColorDown.y), static_cast<float>(m_Scean.M_ColorDown.z)};

			ImGui::ColorEdit3("Up   color", uppColor);
			ImGui::ColorEdit3("Down color", dowColor);

			m_Scean.M_ColorUp = mu::vec3(uppColor[0], uppColor[1], uppColor[2]);
			m_Scean.M_ColorDown = mu::vec3(dowColor[0], dowColor[1], dowColor[2]);
		}

		if (ImGui::CollapsingHeader("Renderer setings")) 
		{
			ImGui::DragInt("Max depth", &m_MaxDepth, 1, 1, 10000);
			ImGui::DragInt("Samples per pixel", &m_SamplesPerPixel, 1, 1, 10000);
		}
	}
	ImGui::End();

	// -------------------------------------------------------------------//
	

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	if (m_ImGuiIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	


	glfwSwapBuffers(m_Window);

}


