﻿#pragma once

#include "../System/DirectXIncLib.h"
#include "../System/TextureDesc.h"
#include "../Utility/Math.h"
#include <memory>
#include <vector>

//頂点の構造体
struct TextureVertex {
    Vector3 mPos; //位置
    Vector2 mTex; //テクスチャ座標
};

struct TextureShaderConstantBuffer {
    Matrix4 mWorld;
    Matrix4 mProjection;
    Vector4 mColor;
    Vector4 mUV;
};

class Buffer;
class InputElement;
class Sprite;
class Renderer;

class Texture {
public:
    Texture(std::shared_ptr<Renderer> renderer, const char* fileName);
    ~Texture();
    static void end();
    void createInputLayout(std::shared_ptr<Renderer> renderer, ID3D10Blob* compiledShader);
    static void drawAll(std::vector<std::shared_ptr<Sprite>> sprites, std::shared_ptr<Renderer> renderer, const Vector2& cameraPosition);
    ID3D11ShaderResourceView* texture() const;
    const TextureDesc& desc() const;
    std::shared_ptr<InputElement> getVertexlayout() const;
    ID3D11SamplerState* getSampler() const;

private:
    void createVertexBuffer(std::shared_ptr<Renderer> renderer);
    void createIndexBuffer(std::shared_ptr<Renderer> renderer);
    void createTexture(std::shared_ptr<Renderer> renderer, const char* fileName);
    void createSampler(std::shared_ptr<Renderer> renderer);
    //各種変換
    D3DX11_IMAGE_LOAD_INFO toImageLoadInfo(const TextureDesc& desc) const;
    D3D11_USAGE toUsage(TextureUsage usage) const;
    unsigned toBind(TextureBind bind) const;
    unsigned toCPUAccess(TextureCPUAccessFlag flag) const;
    DXGI_FORMAT toFormat(TextureFormat format) const;
    unsigned toFilter(TextureFilter filter) const;

private:
    std::shared_ptr<InputElement> mVertexLayout;
    ID3D11ShaderResourceView* mTexture;
    ID3D11SamplerState* mSampleLinear;
    TextureDesc mDesc;

    static Buffer* mVertexBuffer;
    static Buffer* mIndexBuffer;
};

