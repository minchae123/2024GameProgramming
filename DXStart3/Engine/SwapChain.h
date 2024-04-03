#pragma once
/*
*스왑 체인(=교환 사슬)
*[외주 과정]
* - 현재 게임 세상에 있는 상황을 묘사
* - 어떤 공식으로 어떻게 상세하게 적어서 계산할지 던져주니?
* - GPU가 열심히 일을 하게 일감을 넘겨줄 수 있을까?
* - 결과물을 받아서 화면에 그려준다
*
*  [외주 결과물]을 어디서 받아둘까?
* - 일반 종이(Buffer)에 그려서 건내달라고 부탁을 해보자
* - 특수 종이를 만들어서 건내주고 이 결과물을 해당 종이에 받는다
* - 마지막에 우리 화면에 특수 종이(외주 결과물)를 출력해준다
*
* 근데 화면에 현재 결과물을 출력하는 도중에, 다음 화면도 외주를 맡겨놔야
* 현재 화면 결과물은 이미 화면에 출력중
*
* 특수종이는 2개 만들어서
* 0 하나는 현재 화면을 그려주고
* 1 외주를 맡기는 용도
*
* (= 더블 버퍼링)
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

