#pragma once

#include "DirectXIncLib.h"

//�e�N�X�`���̎��
enum class TextureType {
    TEXTURE_TYPE_1D,
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_3D,
    TEXTURE_TYPE_CUBE
};

//�e�N�X�`���t�H�[�}�b�g
enum class TextureFormat {
    TEXTURE_FORMAT_RGBA8,
};

//�e�N�X�`���̎g�p���@
enum class TextureUsage {
    TEXTURE_USAGE_DEFAULT, //GPU�ɂ��ǂݏ���
    TEXTURE_USAGE_IMMUTABLE, //GPU�̓ǂݍ��݂̂݉\
    TEXTURE_USAGE_DYNAMIC, //GPU�̓ǂݍ��݂�CPU�̏������݂��\
    TEXTURE_USAGE_STAGING //GPU����CPU�ւ̃f�[�^�]�����T�|�[�g
};

//���\�[�X�̎g�p���@
enum class TextureBind {
    TEXTURE_BIND_SHADER_RESOURCE,
    TEXTURE_BIND_RENDER_TARGET
};

//cpu�A�N�Z�X����
enum class TextureCPUAccessFlag {
    CPU_ACCESS_NONE,
    CPU_ACCESS_WRITE,
    CPU_ACCESS_READ
};

//�e�N�X�`�����
enum class TextureFilter {
    TEXTURE_FILTER_POINT, //��ԂȂ�
    TEXTURE_FILTER_LINEAR, //���`���
    TEXTURE_FILTER_TRIANGLE, //�����\�A�d��
};

struct TextureDesc {
    //��
    unsigned width;
    //����
    unsigned height;
    //�[�x(2D�e�N�X�`���ł�0)
    unsigned depth;
    //�~�b�v�}�b�v�̍ŏ��̃��x�� ��{0
    unsigned firstMipLevel;
    //�~�b�v�}�b�v��
    unsigned mipLevels;
    //�e�N�X�`���̎g�p���@
    TextureUsage usage;
    //���\�[�X�̎g�p���@
    TextureBind bindFlags;
    //cpu�A�N�Z�X����
    TextureCPUAccessFlag cpuAccessFlags;
    //�I�v�V���� ��{0
    unsigned miscFlags;
    //�t�H�[�}�b�g
    TextureFormat format;
    //�e�N�X�`���̃t�B���^�����O
    TextureFilter filter;
    //�~�b�v�}�b�v�̃t�B���^�����O
    TextureFilter mipFilter;
    //�ǂݍ��ތ��摜���
    D3DX11_IMAGE_INFO* srcInfo;

    TextureDesc() :
        width(1),
        height(1),
        depth(0),
        firstMipLevel(0),
        mipLevels(1),
        usage(TextureUsage::TEXTURE_USAGE_DEFAULT),
        bindFlags(TextureBind::TEXTURE_BIND_SHADER_RESOURCE),
        cpuAccessFlags(TextureCPUAccessFlag::CPU_ACCESS_NONE),
        miscFlags(0),
        format(TextureFormat::TEXTURE_FORMAT_RGBA8),
        filter(TextureFilter::TEXTURE_FILTER_LINEAR),
        mipFilter(TextureFilter::TEXTURE_FILTER_LINEAR),
        srcInfo(0) {
    }
};