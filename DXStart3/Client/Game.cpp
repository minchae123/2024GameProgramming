#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& wInfo)
{
	GEngine->Init(wInfo);

	// 삼각형 그리기 테스트 코드
	// 버텍스 세개 만들고
	// 메시 초기화
	// 쉐이더 파일 읽어옴

	vector<Vertex> vec(3);
	vec[0].pos = Vec3(0.f, 0.5f, 0.5f);
	vec[0].color = Vec4(1, 0, 0, 1);

	vec[1].pos = Vec3(0.5f, -0.5f, 0.5f);
	vec[1].color = Vec4(0, 1, 0, 1);

	vec[2].pos = Vec3(-0.5f, -0.5f, 0.5f);
	vec[2].color = Vec4(0, 0, 1, 1);

	mesh->Init(vec);
	shader->Init(L"..\\Resources\\Shader\\default.hlsli");


	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
	//GEngine->Render();
	GEngine->RenderBegin();

	shader->Update();
	mesh->Render();

	GEngine->RenderEnd();
}
