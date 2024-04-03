#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"

CommandQueue::~CommandQueue()
{
	::CloseHandle(_fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain, shared_ptr<DescriptorHeap> descHeap)
{
	_swapChain = swapChain;
	_descHeap = descHeap;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	// 커맨드 큐를 항수를 통해서 생성
	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	// D3D12_COMMAND_LIST_TYPE_DIRECT : GPU가 직접 실행한느 명령어 목록
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU가 하나인 시스템에서는 0으로 지정
	// nullptr은 초기상태로 지정 (그리기 명령은 nullptr로 지정)
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// 커멘드리스트에서는 Close 상태와 Open 상태가 존재하는데
	// Open 상태에서는 커맨드를 넣어주고, Close 상태에서는 다음에는 제출한다는 개념
	_cmdList->Close();

	// 울타리는 뭐냐 ? CPU와 GPU의 동기화 수단으로 쓰임
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));

	// 멀티 스레드에서 동기화 할때 주로 사용하는 방법
	// 이벤트 핸들 변수를 선언해서 신호등처럼 사용할 수 있다
	// fenceEvent : 빨간불일땐 멈춰있다가 파란불이 켜질 때까지 기다렸다가 동기화를 시키는 용도로 사용
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	// GPU에게 외주를 줄 때마다 인덱스를 증가
	_fenceValue++;

	// 명령 대기열에 새로운 펜스포인트를 설정하는 명령을 추가
	// GPU 타임라인에 있으므로 GPU가 일을 마무리할때까지 새로운 펜스가 설정되지 않는다
	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	// GPU가 이 펜스 지점까지 명령을 완료할때까지 기다린다
	if (_fence->GetCompletedValue() < _fenceValue)
	{
		// GPU가 현재 펜스에 도달하면 이벤트를 발생(파란불 켜짐)
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// GPU가 현재 펜스에 도달할때까지 기다려라. 곧 이벤트가 시작하니까
		// 즉 CPU가 기다리고 있는 중...
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	// 스왑체인과 맞물려 작동한다
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // 화면 출력
		D3D12_RESOURCE_STATE_RENDER_TARGET); // 외주 결과물

	_cmdList->ResourceBarrier(1, &barrier);

	// 뷰포트와 가위사각형을 설정한다
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// 렌더링할 버퍼를 지정한다
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _descHeap->GetBackBufferView();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // 외주 결과물
		D3D12_RESOURCE_STATE_PRESENT); // 화면 출력

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close();

	// 커맨드 리스트 수행
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	// 화면에 보여줌
	_swapChain->Present();

	// 프레임 명령을 완료할 때까지 기다린다 (무한)
	WaitSync();

	_swapChain->SwapIndex();
}