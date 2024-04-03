#include "pch.h"
#include "Device.h"

void Device::Init()
{
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController));
	_debugController->EnableDebugLayer();
#endif

	// DGXI (DirectX Graphics Infrastructure)
	// Direct3D�� �Բ� ���̴� API
	// - ��üȭ�� ��� ��ȯ
	// - �����Ǵ� ���÷��� ��� ���� ���
	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgi));

	// ���÷��� �����(�׷��� ī��)�� ��Ÿ���� ��ü
	// nullptr�� �����ϸ� �ý��� �⺻ ���÷��� �����
	// D3D_FEATURE_LEVEL_11_0 : ���� ���α׷��� �䱸�ϴ� �ּ� ���� ����(���� �׷��� ī�带 �ɷ��� �� ����)
	// riid : ����̽��� COM ID
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
}
