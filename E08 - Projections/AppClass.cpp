#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Machi Dimps - mrd6635@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//allocate the primitive
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateTorus(3.0f, 2.0f, 6, 6, C_RED);

	//allocate the primitive
	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateTorus(3.0f, 2.0f, 8, 8, C_GREEN);

	m_pMesh3 = new MyMesh();
	m_pMesh3->GenerateCone(0.5f, 1.0f, 6, C_BLUE);

	//create a new camera
	m_pCamera = new MyCamera();

	//projection used
	m_uProjection = 1;
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//calculate view and projection
	switch (m_uProjection)
	{
	default:
	case 1:
		m_pCamera->ResetCamera();
		break;
	case 2:
		m_pCamera->ResetCamera();
		m_pCamera->SetPerspective(false);
		//m_pCamera->SetPosition(vector3(0.0f, 0.0f, 20.0f));
		//m_pCamera->SetTarget(AXIS_Y);
		//m_pCamera->SetUpward(vector3(1.0f, 0.0f, 0.0f));
		break;
	case 3:
		m_pCamera->ResetCamera();
		m_pCamera->SetPosition(vector3(30.0f, 0.0f, 0.0f));
		m_pCamera->SetTarget(AXIS_X);
		m_pCamera->SetUp(vector3(0.0f, 0.0f, -1.0f));
		break;
	case 4:
		m_pCamera->ResetCamera();
		//m_pCamera->SetPerspective(false);
		m_pCamera->SetPosition(vector3(0.0f, 0.0f, -14.5f));
		break;
	case 5:
		m_pCamera->ResetCamera();
		m_pCamera->SetPerspective(false);
		m_pCamera->SetPosition(vector3(0.0f, 0.0f, -10.0f));
		break;
	case 6:
		m_pCamera->ResetCamera();
		//m_pCamera->SetPerspective(false);
		m_pCamera->SetPosition(vector3(0.0f, 0.0f, -14.0f));
		m_pCamera->SetNearFar(vector2(0.001f,10.0f));
		break;
	case 7:
		m_pCamera->ResetCamera();
		m_pCamera->SetUp(vector3(0.0f, -1.0f, 0.0f));
		break;
	}

	m_pCamera->CalculateProjectionMatrix();
	m_pCamera->CalculateViewMatrix();

	matrix4 m4Projection = m_pCamera->GetProjectionMatrix();
	matrix4 m4View = m_pCamera->GetViewMatrix();


	//draw the primitive
	m_pMesh1->Render(m4Projection, m4View, glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X));
	m_pMesh2->Render(m4Projection, m4View, glm::translate(IDENTITY_M4, vector3(0.0f, 0.0f, -5.0f)) * glm::rotate(IDENTITY_M4, 1.5708f, AXIS_X));
	m_pMesh3->Render(m4Projection, m4View, glm::translate(vector3(0.0f, 0.0f, -10.0f)));

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release GUI
	ShutdownGUI();
}