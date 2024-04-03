#pragma once

// 서명을 담당하는 녀석
// 어떤 버퍼를 사용하겠다

class RootSignature
{
public:
    void Init(ComPtr<ID3D12Device> device);

    ComPtr<ID3D12RootSignature>    GetSignature() { return _signature; }

private:
    ComPtr<ID3D12RootSignature>    _signature;
};

