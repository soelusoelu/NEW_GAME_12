#include "Transform2D.h"

Transform2D::Transform2D() :
    mWorldTransform(Matrix4::identity),
    mPosition(Vector3::zero),
    mRotation(Quaternion::identity),
    mDefaultPivot(Vector2::zero),
    mPivot(Vector2::zero),
    mScale(Vector2::one),
    mIsRecomputeTransform(true) {
}

Transform2D::~Transform2D() = default;

bool Transform2D::computeWorldTransform() {
    if (mIsRecomputeTransform) {
        mIsRecomputeTransform = false;

        mWorldTransform = Matrix4::createScale(Vector3(mScale, 1.f));
        mWorldTransform *= Matrix4::createTranslation(-Vector3(mPivot, 0.f));
        mWorldTransform *= Matrix4::createFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::createTranslation(mPosition + Vector3(mPivot, 0.f));

        return true;
    }
    return false;
}

Matrix4 Transform2D::getWorldTransform() const {
    return mWorldTransform;
}

void Transform2D::setPosition(const Vector2 & pos) {
    mPosition.x = pos.x;
    mPosition.y = pos.y;
    mIsRecomputeTransform = true;
}

Vector2 Transform2D::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

void Transform2D::translate(const Vector2 & translation) {
    mPosition.x += translation.x;
    mPosition.y += translation.y;
    mIsRecomputeTransform = true;
}

void Transform2D::setPrimary(float z) {
    mPosition.z = z;
    mIsRecomputeTransform = true;
}

float Transform2D::getDepth() const {
    return mPosition.z;
}

void Transform2D::setRotation(float angle) {
    angle *= 0.5f;
    float sinAngle = Math::sin(angle);

    mRotation.z = sinAngle;
    mRotation.w = Math::cos(angle);

    mIsRecomputeTransform = true;
}

Quaternion Transform2D::getRotation() const {
    return mRotation;
}

void Transform2D::rotate(float angle) {
    angle *= 0.5f;
    float sinAngle = Math::sin(angle);

    Quaternion inc;
    inc.z = sinAngle;
    inc.w = Math::cos(angle);

    mRotation = Quaternion::concatenate(mRotation, inc);

    mIsRecomputeTransform = true;
}

void Transform2D::setPivot(const Vector2 & pivot) {
    mDefaultPivot = pivot;
    mPivot = pivot;
    mIsRecomputeTransform = true;
}

Vector2 Transform2D::getPivot() const {
    return mPivot;
}

void Transform2D::setScale(const Vector2 & scale, bool isComputePivot) {
    if (isComputePivot) {
        mPivot = mDefaultPivot * scale;
    }

    mScale = scale;
    mIsRecomputeTransform = true;
}

void Transform2D::setScale(float scale, bool isComputePivot) {
    if (isComputePivot) {
        mPivot = mDefaultPivot * scale;
    }

    mScale.x = scale;
    mScale.y = scale;
    mIsRecomputeTransform = true;
}

void Transform2D::setScale(const Vector2 & scale, const Vector2INT & size) {
    auto s = (mScale - scale) / 2.f;
    auto translation = Vector2(size.x * s.x, size.y * s.y);
    translate(translation);

    mPivot = mDefaultPivot * scale;

    mScale = scale;

    mIsRecomputeTransform = true;
}

void Transform2D::setScale(float scale, const Vector2INT & size) {
    auto sX = (mScale.x - scale) / 2.f;
    auto sY = (mScale.y - scale) / 2.f;
    auto translation = Vector2(size.x * sX, size.y * sY);
    translate(translation);

    mPivot = mDefaultPivot * scale;

    mScale.x = scale;
    mScale.y = scale;

    mIsRecomputeTransform = true;
}

Vector2 Transform2D::getScale() const {
    return mScale;
}

Vector2 Transform2D::getCenter() const {
    return Vector2(mPosition.x, mPosition.y) + mPivot;
}
