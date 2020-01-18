#pragma once

#include "../Utility/Math.h"
#include <memory>
#include <list>

class Actor;

class Transform2D : public std::enable_shared_from_this<Transform2D> {
public:
    Transform2D(Actor* owner);
    ~Transform2D();

    //アタッチ元のアクターを返す
    Actor* getOwner() const;

    //ワールド行列更新
    bool computeWorldTransform();
    Matrix4 getWorldTransform() const;

    //ピクセル単位で位置指定
    void setPosition(const Vector2& pos);
    Vector2 getPosition() const;
    Vector2 getWorldPosition() const;
    void translate(const Vector2& translation);

    //描画優先順位
    void setPrimary(float z);
    float getDepth() const;

    //回転
    void setRotation(float angle);
    Quaternion getRotation() const;
    Quaternion getWorldRotation() const;
    void rotate(float angle);

    //回転ピボット位置
    void setPivot(const Vector2& pivot);
    Vector2 getPivot() const;

    //倍率で拡縮
    void setScale(const Vector2& scale);
    void setScale(float scale);
    Vector2 getScale() const;
    Vector2 getWorldScale() const;
    
    //親子関係
    void addChild(std::shared_ptr<Transform2D> child);
    void removeChild(std::shared_ptr<Transform2D> child);
    void removeChild(const char* tag);
    std::shared_ptr<Transform2D> getChild(const char* tag) const;
    std::shared_ptr<Transform2D> parent() const;
    std::shared_ptr<Transform2D> root() const;
    size_t getChildCount() const;

private:
    void setParent(std::shared_ptr<Transform2D> parent);
    void shouldRecomputeTransform();

private:
    Actor* mOwner;
    Matrix4 mWorldTransform;
    Vector3 mPosition;
    Quaternion mRotation;
    Vector2 mDefaultPivot;
    Vector2 mPivot;
    Vector2 mScale;
    std::weak_ptr<Transform2D> mParent;
    std::list<std::shared_ptr<Transform2D>> mChildren;
    bool mIsRecomputeTransform;
};

