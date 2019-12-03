#pragma once

#include <memory>

class Buffer;

struct VertexStreamDesc {
    //���_�o�b�t�@
    std::shared_ptr<Buffer> buffer;
    //�I�t�Z�b�g
    unsigned offset;
    //�X�g���C�h
    unsigned stride;

    VertexStreamDesc() :
        buffer(nullptr),
        offset(0),
        stride(0) {
    }
};
