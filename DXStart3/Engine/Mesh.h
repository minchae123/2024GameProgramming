#pragma once

// 버텍스 -> 폴리곤 -> 메시

// 1 버텍스란 ? 
// 하나의 점으로 표현된다
// 3D 공간상에서의 가장 기본이 되는 단위이다
// 버텍스에서는 위치, 색상, 법선... n개의 다양한 정보를 담고 있다
// 2D에서는 POINT라고 하는데 (위치값 X,Y)

// 2 폴리곤이란?
// 최소의 면 단위
// 선과 선들이 모여서 최초로 면이 되는데 이게 삼각형이다 !! ㄴㅇㄱ
// 버텍스 3개가 모이면 하나의 면 단위를 이루는 폴리곤이 완성된다

// 3 메시 Mesh란 ?
// 폴리곤들이 모이면 최소한의 3차원 공간을 만든다
// 폴리곤들이 모여서 나온 하나의 물체 덩어리
//

class Mesh
{
public:
    void Init(vector<Vertex>& vec);
    void Render();

private:
    ComPtr<ID3D12Resource>        _vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW    _vertexBufferView = {};
    uint32 _vertexCount = 0;
};