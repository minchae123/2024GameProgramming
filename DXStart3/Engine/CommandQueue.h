#pragma once

// 명령어들의 집합소
// GPU에게 일을 시키기 위한 명세서를 기록해 놓은 공간
// 외주를 요쳥할 때 하나씩 요청하면 비효율적
// 그래서 "외주 목록"에 일감을 쌓아놨다가 한방에 요청

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain, shared_ptr<DescriptorHeap> descHeap);
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() { return    _cmdList; }

private:
	// CommandQueue는 DX12d에 처음 등장
	ComPtr<ID3D12CommandQueue>            _cmdQueue;
	ComPtr<ID3D12CommandAllocator>        _cmdAlloc;
	ComPtr<ID3D12GraphicsCommandList>    _cmdList;

	// Fence란 울타리
	// CPU와 GPU 사이의 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>                    _fence;
	uint32                                _fenceValue = 0;
	HANDLE                                _fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>        _swapChain;
	shared_ptr<DescriptorHeap>    _descHeap;
};