#include "pch.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& wInfo)
{
	GEngine->Init(wInfo);

	// �ﰢ�� �׸��� �׽�Ʈ �ڵ�
	// ���ؽ� ���� �����
	// �޽� �ʱ�ȭ
	// ���̴� ���� �о��

	Vec3 pos = Vec3(1, 1, 1);


	GEngine->GetCmdQueue()->WaitSync();
}

void Game::Update()
{
	//GEngine->Render();
	GEngine->RenderBegin();


	GEngine->RenderEnd();
}
