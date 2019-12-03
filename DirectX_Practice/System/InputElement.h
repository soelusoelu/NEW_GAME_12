#pragma once

#include "InputElementDesc.h"
#include "VertexStreamDesc.h"
#include "DirectXIncLib.h"
#include <vector>
#include <memory>

class InputElement {
public:
    InputElement(const InputElementDesc* desc, unsigned numElements, ID3D10Blob* compile);
    ~InputElement();
    //�f�B�X�N���v�^�̗v�f����Ԃ�
    size_t size() const;
    //�f�B�X�N���v�^�̎擾
    const InputElementDesc& desc(unsigned index) const;
    //���_���C�A�E�g�̎擾
    ID3D11InputLayout* layout() const;

    //���_�o�b�t�@�X�g���[���̐ݒ�
    void setVertexStream(const VertexStreamDesc* streams, unsigned start = 0);
    //���_�o�b�t�@�X�g���[���̃��Z�b�g
    void resetVertexStream();

private:
    //���_�o�b�t�@�̐ݒ�
    //void setVertexBuffer(const Element& element, const VertexStreamDesc& stream, unsigned start);
    //�f�B�X�N���v�^��ϊ�
    //static Element toElement(const InputElementDesc& desc);
    static D3D11_INPUT_ELEMENT_DESC toElement(const InputElementDesc& desc);
    //���_�^�C�v��ϊ�
    static const DXGI_FORMAT& toVertexFormat(VertexType type);
    static const D3D11_INPUT_CLASSIFICATION toClassification(SlotClass classification);

private:
    //�f�B�X�N���v�^�z��
    std::vector<InputElementDesc> mDesc;
    //���_�錾�z��
    D3D11_INPUT_ELEMENT_DESC* mElements;
    //�R���p�C���ς݃V�F�[�_�[�R�[�h
    ID3D10Blob* mCompiledShader;
    //���_���C�A�E�g
    ID3D11InputLayout* mInputLayout;
};

