#pragma once

// 하드웨어와 직접 소통하기 위해 필요한 클래스
// (-그래픽 카드)

// DX란 무엇인가 ?
// GPU를 제어하고 프로그래밍하는 데 쓰이는 저수준(로우레벨) API의 모음이다
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM 이란 (컴포넌트 오브젝트 모델)
	// COM(Ptr) DX의 헬퍼 클래스다
	// DX에서의 COM 이란?
	// DX의 프로그래밍 언어의 독립성과 하위 호환성을 가능하게 하는 기술
	// Comptr은 일종의 DX API를 손쉽게 쓸 수 있는 스마트 포인터로 정의한 클래스다

	ComPtr<ID3D12Debug>            _debugController;
	ComPtr<IDXGIFactory>        _dxgi; // 화면 관련 기능들
	ComPtr<ID3D12Device>        _device; // 각종 객체 생성

};

