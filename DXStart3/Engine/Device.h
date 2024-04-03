#pragma once

// �ϵ����� ���� �����ϱ� ���� �ʿ��� Ŭ����
// (-�׷��� ī��)

// DX�� �����ΰ� ?
// GPU�� �����ϰ� ���α׷����ϴ� �� ���̴� ������(�ο췹��) API�� �����̴�
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// COM �̶� (������Ʈ ������Ʈ ��)
	// COM(Ptr) DX�� ���� Ŭ������
	// DX������ COM �̶�?
	// DX�� ���α׷��� ����� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
	// Comptr�� ������ DX API�� �ս��� �� �� �ִ� ����Ʈ �����ͷ� ������ Ŭ������

	ComPtr<ID3D12Debug>            _debugController;
	ComPtr<IDXGIFactory>        _dxgi; // ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>        _device; // ���� ��ü ����

};

