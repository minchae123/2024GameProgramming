#pragma once
/*
*���� ü��(=��ȯ �罽)
*[���� ����]
* - ���� ���� ���� �ִ� ��Ȳ�� ����
* - � �������� ��� ���ϰ� ��� ������� �����ִ�?
* - GPU�� ������ ���� �ϰ� �ϰ��� �Ѱ��� �� ������?
* - ������� �޾Ƽ� ȭ�鿡 �׷��ش�
*
*  [���� �����]�� ��� �޾Ƶѱ�?
* - �Ϲ� ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź�� �غ���
* - Ư�� ���̸� ���� �ǳ��ְ� �� ������� �ش� ���̿� �޴´�
* - �������� �츮 ȭ�鿡 Ư�� ����(���� �����)�� ������ش�
*
* �ٵ� ȭ�鿡 ���� ������� ����ϴ� ���߿�, ���� ȭ�鵵 ���ָ� �ðܳ���
* ���� ȭ�� ������� �̹� ȭ�鿡 �����
*
* Ư�����̴� 2�� ����
* 0 �ϳ��� ���� ȭ���� �׷��ְ�
* 1 ���ָ� �ñ�� �뵵
*
* (= ���� ���۸�)
*/

class SwapChain
{
public:
    void Init(const WindowInfo& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

    void Present();
    void SwapIndex();

    ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
    ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _renderTargets[index]; }

    uint32 GetCurrentBackBufferIndex() { return _backBufferIndex; }
    ComPtr<ID3D12Resource> GetCurrentBackBufferResource() { return _renderTargets[_backBufferIndex]; }

private:
    ComPtr<IDXGISwapChain>    _swapChain;
    ComPtr<ID3D12Resource>    _renderTargets[SWAP_CHAIN_BUFFER_COUNT];
    uint32                    _backBufferIndex = 0;
};

