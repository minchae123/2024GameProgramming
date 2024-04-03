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

	// Ŀ�ǵ� ť�� �׼��� ���ؼ� ����
	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	// D3D12_COMMAND_LIST_TYPE_DIRECT : GPU�� ���� �����Ѵ� ��ɾ� ���
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU�� �ϳ��� �ý��ۿ����� 0���� ����
	// nullptr�� �ʱ���·� ���� (�׸��� ����� nullptr�� ����)
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// Ŀ��帮��Ʈ������ Close ���¿� Open ���°� �����ϴµ�
	// Open ���¿����� Ŀ�ǵ带 �־��ְ�, Close ���¿����� �������� �����Ѵٴ� ����
	_cmdList->Close();

	// ��Ÿ���� ���� ? CPU�� GPU�� ����ȭ �������� ����
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));

	// ��Ƽ �����忡�� ����ȭ �Ҷ� �ַ� ����ϴ� ���
	// �̺�Ʈ �ڵ� ������ �����ؼ� ��ȣ��ó�� ����� �� �ִ�
	// fenceEvent : �������϶� �����ִٰ� �Ķ����� ���� ������ ��ٷȴٰ� ����ȭ�� ��Ű�� �뵵�� ���
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{
	// GPU���� ���ָ� �� ������ �ε����� ����
	_fenceValue++;

	// ��� ��⿭�� ���ο� �潺����Ʈ�� �����ϴ� ����� �߰�
	// GPU Ÿ�Ӷ��ο� �����Ƿ� GPU�� ���� �������Ҷ����� ���ο� �潺�� �������� �ʴ´�
	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	// GPU�� �� �潺 �������� ����� �Ϸ��Ҷ����� ��ٸ���
	if (_fence->GetCompletedValue() < _fenceValue)
	{
		// GPU�� ���� �潺�� �����ϸ� �̺�Ʈ�� �߻�(�Ķ��� ����)
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// GPU�� ���� �潺�� �����Ҷ����� ��ٷ���. �� �̺�Ʈ�� �����ϴϱ�
		// �� CPU�� ��ٸ��� �ִ� ��...
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	// ����ü�ΰ� �¹��� �۵��Ѵ�
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_PRESENT, // ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET); // ���� �����

	_cmdList->ResourceBarrier(1, &barrier);

	// ����Ʈ�� �����簢���� �����Ѵ�
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// �������� ���۸� �����Ѵ�
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _descHeap->GetBackBufferView();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetCurrentBackBufferResource().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, // ���� �����
		D3D12_RESOURCE_STATE_PRESENT); // ȭ�� ���

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close();

	// Ŀ�ǵ� ����Ʈ ����
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	// ȭ�鿡 ������
	_swapChain->Present();

	// ������ ����� �Ϸ��� ������ ��ٸ��� (����)
	WaitSync();

	_swapChain->SwapIndex();
}