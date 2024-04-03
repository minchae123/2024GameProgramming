#include "pch.h"
#include "Device.h"

void Device::Init()
{
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController));
	_debugController->EnableDebugLayer();
#endif

	// DGXI (DirectX Graphics Infrastructure)
	// Direct3D와 함께 쓰이는 API
	// - 전체화면 모드 전환
	// - 지원되는 디스플레이 모드 열거 등등
	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgi));

	// 디스플레이 어댑터(그래픽 카드)를 나타내는 객체
	// nullptr로 지정하면 시스템 기본 디스플레이 어댑터
	// D3D_FEATURE_LEVEL_11_0 : 응용 프로그램이 요구하는 최소 가능 수준(옛날 그래픽 카드를 걸러낼 수 있음)
	// riid : 디바이스의 COM ID
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
}
