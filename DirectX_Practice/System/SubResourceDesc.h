#pragma once

struct SubResourceDesc {
    //�������f�[�^�ւ̃|�C���^
    const void* data;
    //�e�N�X�`���݂̂Ŏg�p
    //�e�N�X�`����1�s�̐擪���玟�̍s�܂ł̋���
    unsigned pitch;
    //3D�e�N�X�`���݂̂Ŏg�p
    //����[�����x���̊J�n���玟�̐[���܂ł̋���
    unsigned slicePitch;

    SubResourceDesc() :
        data(nullptr),
        pitch(0),
        slicePitch(0) {
    }
};

struct MappedSubResourceDesc {
    //�f�[�^�ւ̃|�C���^
    void* data;
    //�f�[�^�̍s�s�b�`
    unsigned rowPitch;
    //�f�[�^�̐[���s�b�`
    unsigned depthPitch;

    MappedSubResourceDesc() :
        data(nullptr),
        rowPitch(0),
        depthPitch(0) {
    }
};
