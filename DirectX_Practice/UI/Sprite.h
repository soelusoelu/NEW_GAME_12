﻿#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class SpriteState {
    Active, //常に描画
    Once, //一回描画後削除
    Dead //描画せず削除
};

class Shader;
class Texture;

class Sprite {
public:
    Sprite(const char* fileName, const Vector2& size, float z);
    ~Sprite();
    Sprite(const Sprite& sprite);
    //SpriteManagerにて毎フレーム実行
    void update();
    Sprite* draw() const;
    //ピクセル単位で位置指定
    void setPosition(const Vector2& pos);
    //描画優先順位(0～1、0が手前)
    void setPrimary(float z);
    const Vector2 getPosition() const;
    const float getDepth() const;
    void translate(const Vector2& translation);
    //回転
    void setRotation(float angle);
    const Quaternion getRotation() const;
    void rotate(float angle);
    //倍率で拡縮
    void setScale(const Vector2& scale, bool isCenterShift = false);
    void setScale(float scale, bool isCenterShift = false);
    const Vector2 getScale() const;
    //色味、たぶん0～1
    void setColor(const Vector3& color);
    void setColor(float r, float g, float b);
    //不透明度(0～1、1が不透明, 0が透明)
    void setAlpha(float alpha);
    const Vector4 getColor() const;
    //切り取り範囲(left, top, right, bottom, 0～1)
    void setUV(float l, float t, float r, float b);
    const Vector4 getUV() const;
    //回転ピボット位置
    void setPivot(const Vector2& pivot);
    const Vector2 getPivot() const;
    //テクスチャサイズの取得(getterのみ)
    const Vector2 getTextureSize() const;
    //スクリーン表示上のサイズの取得
    const Vector2 getScreenTextureSize() const;
    //状態管理
    static void destroy(Sprite* sprite);
    static void destroy(std::shared_ptr<Sprite> sprite);
    const SpriteState getState() const;
    //World行列の取得
    const Matrix4 getWorld() const;
    //テクスチャの取得
    void setTexture(const char* fileName, const Vector2& size);
    const std::shared_ptr<Texture> texture() const;
    //シェーダーの取得
    std::shared_ptr<Shader> shader() const;
    //ファイル名の取得
    const char* fileName() const;
    //ワールド行列の変更フラグ
    bool getWorldUpdateFlag() const;
    void onceToDead();

private:
    void updateWorld();
    void centerShift(const Vector2& nextScale);

public:
    static bool mZSortFlag;

private:
    Vector2 mDefaultSize;
    Vector2 mCurrentSize;
    Vector3 mPosition;
    Quaternion mRotation;
    Vector2 mScale;
    Vector4 mColor;
    Vector4 mUV;
    Vector2 mPivot;
    Matrix4 mWorld;
    SpriteState mState;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Shader> mShader;
    const char* mFileName;
    bool mWorldUpdateFlag;
};

