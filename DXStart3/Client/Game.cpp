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

	Vec3 pos = Vec3(1, 1, 1);


	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
	//GEngine->Render();
	GEngine->RenderBegin();


	GEngine->RenderEnd();
}
