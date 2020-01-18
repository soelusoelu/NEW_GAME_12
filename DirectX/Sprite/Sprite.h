﻿#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class SpriteState {
    ACTIVE,
    NON_ACTIVE,
    DEAD
};

class Transform2D;
class SpriteManager;
class Shader;
class Texture;
class Renderer;

class Sprite {
public:
    Sprite(std::shared_ptr<Renderer> renderer, const char* fileName, float z);
    Sprite(std::shared_ptr<Renderer> renderer, const char* fileName, float z, std::shared_ptr<Transform2D> transform);
    ~Sprite();
    Sprite(const Sprite& sprite);
    //SpriteManagerにて毎フレーム実行
    void update();
    //描画
    void draw(const Matrix4& proj);
    //自身のコピーを作成
    std::shared_ptr<Sprite> copy() const;
    //Transform
    std::shared_ptr<Transform2D> transform() const;
    //色味、たぶん0～1
    void setColor(const Vector3& color);
    void setColor(float r, float g, float b);
    //不透明度(0～1、1が不透明, 0が透明)
    void setAlpha(float alpha);
    Vector4 getColor() const;
    //切り取り範囲(left, top, right, bottom, 0～1)
    void setUV(float l, float t, float r, float b);
    Vector4 getUV() const;
    //テクスチャサイズの取得
    Vector2 getTextureSize() const;
    //状態管理
    static void destroy(Sprite* sprite);
    static void destroy(std::shared_ptr<Sprite> sprite);
    void setActive(bool value);
    bool getActive() const;
    SpriteState getState() const;
    void setUI();
    bool isUI() const;
    //テクスチャの取得
    std::shared_ptr<Texture> texture() const;
    //シェーダーの取得
    std::shared_ptr<Shader> shader() const;
    //ファイル名の取得
    const char* fileName() const;

    //SpriteManagerの登録
    static void setSpriteManager(SpriteManager* manager);

public:
    static bool ZSortFlag;

private:
    std::shared_ptr<Renderer> mRenderer;
    std::shared_ptr<Transform2D> mTransform;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Shader> mShader;
    Vector2 mTextureSize;
    Vector4 mColor;
    Vector4 mUV;
    SpriteState mState;
    bool mIsUI;
    const char* mFileName;

    static SpriteManager* mSpriteManager;
};

