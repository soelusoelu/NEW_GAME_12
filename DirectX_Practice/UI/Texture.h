#pragma once

#include "../System/DirectXIncLib.h"
#include "../Utility/Math.h"
#include <list>
#include <memory>

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
class Shader;
class Sprite;

class Texture {
public:
    Texture();
    ~Texture();
    void create(const char* fileName);
    void createVertexLayout(ID3D10Blob* compiledShader);
    static void end();
    static void drawAll(std::list<std::shared_ptr<Sprite>>* sprites);
    ID3D11ShaderResourceView* texture() const;

private:
    void createVertexBuffer();
    void createIndexBuffer();
    void createSampler();
    void createTexture(const char* fileName);

private:
    static ID3D11SamplerState* mSampleLinear;
    static std::shared_ptr<Buffer> mVertexBuffer;
    static std::shared_ptr<Buffer> mIndexBuffer;
    std::shared_ptr<InputElement> mVertexLayout;
    ID3D11ShaderResourceView* mTexture;
};

