#pragma once

//���_�^�C�v
enum class VertexType {
    VERTEX_TYPE_FLOAT1,
    VERTEX_TYPE_FLOAT2,
    VERTEX_TYPE_FLOAT3,
    VERTEX_TYPE_FLOAT4,
    VERTEX_TYPE_BYTE4,
    VERTEX_TYPE_BYTE4N,
    VERTEX_TYPE_UBYTE4,
    VERTEX_TYPE_UBYTE4N,
    VERTEX_TYPE_SHORT2,
    VERTEX_TYPE_SHORT2N,
    VERTEX_TYPE_USHORT2,
    VERTEX_TYPE_USHORT2N,
    VERTEX_TYPE_SHORT4,
    VERTEX_TYPE_SHORT4N,
    VERTEX_TYPE_USHORT4,
    VERTEX_TYPE_USHORT4N,
    VERTEX_TYPE_INT1,
    VERTEX_TYPE_INT2,
    VERTEX_TYPE_INT3,
    VERTEX_TYPE_INT4,
    VERTEX_TYPE_UINT1,
    VERTEX_TYPE_UINT2,
    VERTEX_TYPE_UINT3,
    VERTEX_TYPE_UINT4
};

//���_���ۂ�
enum class SlotClass {
    SLOT_CLASS_VERTEX_DATA,
    SLOT_CLASS_INSTANCE_DATA
};

//���_�錾�f�B�X�N���v�^
struct InputElementDesc {
    //�Z�}���e�B�b�N LPCSTR
    const char* semantic;
    //�Z�}���e�B�b�N�C���f�b�N�X
    unsigned index;
    //���_�^�C�v
    VertexType type;
    //�X���b�g
    unsigned slot;
    //�I�t�Z�b�g
    unsigned offset;
    //���_���ۂ�
    SlotClass classification;
    //�X�g���[���ԍ�
    unsigned stream;
};

//���_�錾�̍ő�l
static const unsigned VERTEX_DECLARATION_MAX = 16;
