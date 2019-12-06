#pragma once

//�o�b�t�@�^�C�v
enum class BufferType {
    BUFFER_TYPE_VERTEX, //���_�o�b�t�@
    BUFFER_TYPE_INDEX, //�C���f�b�N�X�o�b�t�@
    BUFFER_TYPE_CONSTANT_BUFFER,
    BUFFER_TYPE_SHADER_RESOURCE,
    BUFFER_TYPE_STREAM_OUTPUT,
    BUFFER_TYPE_RENDER_TARGET,
    BUFFER_TYPE_DEPTH_STENCIL,
    BUFFER_TYPE_UNORDERED_ACCESS,
    //BUFFER_TYPE_DECODER,
    //BUFFER_TYPE_VIDEO_ENCODER
};

enum class BufferUsage {
    BUFFER_USAGE_DEFAULT, //GPU�ɂ��ǂݏ���
    BUFFER_USAGE_IMMUTABLE, //GPU�̓ǂݍ��݂̂݉\
    BUFFER_USAGE_DYNAMIC, //GPU�̓ǂݍ��݂�CPU�̏������݂��\
    BUFFER_USAGE_STAGING //GPU����CPU�ւ̃f�[�^�]�����T�|�[�g
};

enum class BufferCPUAccessFlag {
    CPU_ACCESS_NONE,
    CPU_ACCESS_WRITE,
    CPU_ACCESS_READ
};

struct BufferDesc {
    //�f�[�^�̃o�C�g��
    unsigned size;
    //�o�b�t�@�̎g�p���@
    BufferUsage usage;
    //�o�b�t�@�^�C�v(BindFlags)
    BufferType type;
    //cpu�A�N�Z�X����
    BufferCPUAccessFlag cpuAccessFlags;
    //�I�v�V���� ��{0
    unsigned miscFlags;
    //�R���s���[�g�V�F�[�_���g���Ȃ� ��{0
    unsigned structureByteStride;

    //�R���X�g���N�^
    BufferDesc() :
        size(0),
        usage(BufferUsage::BUFFER_USAGE_DEFAULT),
        type(BufferType::BUFFER_TYPE_VERTEX),
        cpuAccessFlags(BufferCPUAccessFlag::CPU_ACCESS_NONE),
        miscFlags(0),
        structureByteStride(0) {
    }
};
