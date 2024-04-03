#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
    _vertexCount = static_cast<uint32>(vec.size());
    uint32 bufferSize = _vertexCount * sizeof(Vertex);

    D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    DEVICE->CreateCommittedResource(
        &heapProperty,
        D3D12_HEAP_FLAG_NONE,
        &desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&_vertexBuffer));

    // _vertexBuffer은 GPU의 공간을 가리키고 있다
    // GPU 의 메모리에 정점데이터를 복사해주는 과정이다

    void* vertexDataBuffer = nullptr;
    CD3DX12_RANGE readRange(0, 0);
    _vertexBuffer->Map(0, &readRange, &vertexDataBuffer); // 포인터상의 주소공간을 만들고 연결
    ::memcpy(vertexDataBuffer, &vec[0], bufferSize); // 버퍼 사이즈만큼 메모리 카피
    _vertexBuffer->Unmap(0, nullptr);

    // Initialize the vertex buffer view.
    _vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
    _vertexBufferView.StrideInBytes = sizeof(Vertex);
    _vertexBufferView.SizeInBytes = bufferSize;
}

void Mesh::Render()
{
    CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView);

    // 루트 시그니처 서명에 관련된 코드를 넣어줘야함
    // 디폴트로 서명하면 가장 기본적인 메시만 그려줄 수 있다

    CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}
