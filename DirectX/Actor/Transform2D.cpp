#include "Transform2D.h"
#include "Actor.h"

Transform2D::Transform2D(Actor* owner) :
    mOwner(owner),
    mWorldTransform(Matrix4::identity),
    mPosition(Vector3::zero),
    mRotation(Quaternion::identity),
    mDefaultPivot(Vector2::zero),
    mPivot(Vector2::zero),
    mScale(Vector2::one),
    mParent(),
    mChildren(0),
    mIsRecomputeTransform(true) {
}

Transform2D::~Transform2D() {
    for (auto&& child : mChildren) {
        Actor::destroy(child->mOwner);
    }
}

Actor* Transform2D::getOwner() const {
    return mOwner;
}

bool Transform2D::computeWorldTransform() {
    if (mIsRecomputeTransform) {
        if (auto p = mParent.lock()) {
            mWorldTransform = Matrix4::createScale(Vector3(mScale * p->mScale, 1.f));
            mWorldTransform *= Matrix4::createTranslation(-Vector3(mPivot, 0.f));
            mWorldTransform *= Matrix4::createFromQuaternion(Quaternion::concatenate(mRotation, p->mRotation));
            mWorldTransform *= Matrix4::createTranslation(mPosition + Vector3(p->mPosition.x, p->mPosition.y, 0.f) + Vector3(mPivot, 0.f));

            //相対移動(途中)
            //mWorldTransform = Matrix4::createTranslation(-Vector3(mPivot, 0.f));
            //mWorldTransform *= Matrix4::createScale(Vector3(mScale, 1.f));
            //mWorldTransform *= Matrix4::createFromQuaternion(mRotation);
            //mWorldTransform *= Matrix4::createTranslation(mPosition);
            //mWorldTransform *= p->mWorldTransform;
            //mWorldTransform.m[3][2] = mPosition.z;
        } else {
            mWorldTransform = Matrix4::createTranslation(-Vector3(mDefaultPivot, 0.f));
            mWorldTransform *= Matrix4::createScale(Vector3(mScale, 1.f));
            mWorldTransform *= Matrix4::createFromQuaternion(mRotation);
            mWorldTransform *= Matrix4::createTranslation(mPosition);
        }

        mIsRecomputeTransform = false;

        return true;
    }
    return false;
}

Matrix4 Transform2D::getWorldTransform() const {
    return mWorldTransform;
}

void Transform2D::setPosition(const Vector2& pos) {
    mPosition.x = pos.x;
    mPosition.y = pos.y;
    recomputeTransform();
}

Vector2 Transform2D::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

void Transform2D::translate(const Vector2& translation) {
    mPosition.x += translation.x;
    mPosition.y += translation.y;
    recomputeTransform();
}

void Transform2D::setPrimary(float z) {
    mPosition.z = z;
    recomputeTransform();
}

float Transform2D::getDepth() const {
    return mPosition.z;
}

void Transform2D::setRotation(float angle) {
    angle *= 0.5f;
    float sinAngle = Math::sin(angle);

    mRotation.z = sinAngle;
    mRotation.w = Math::cos(angle);

    recomputeTransform();
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

    recomputeTransform();
}

void Transform2D::setPivot(const Vector2& pivot) {
    mDefaultPivot = pivot;
    mPivot = pivot;
    recomputeTransform();
}

Vector2 Transform2D::getPivot() const {
    return mPivot;
}

void Transform2D::setScale(const Vector2& scale) {
    mScale = scale;
    mPivot = mDefaultPivot * scale;
    recomputeTransform();
}

void Transform2D::setScale(float scale) {
    mScale.x = scale;
    mScale.y = scale;
    mPivot = mDefaultPivot * scale;
    recomputeTransform();
}

Vector2 Transform2D::getScale() const {
    return mScale;
}

void Transform2D::addChild(std::shared_ptr<Transform2D> child) {
    mChildren.emplace_back(child);
    child->setParent(shared_from_this());
}

void Transform2D::removeChild(std::shared_ptr<Transform2D> child) {
    removeChild(child->mOwner->tag());
}

void Transform2D::removeChild(const char* tag) {
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
        if ((*itr)->mOwner->tag() == tag) {
            Actor::destroy((*itr)->mOwner);
            mChildren.erase(itr);
            return;
        }
    }
}

std::shared_ptr<Transform2D> Transform2D::getChild(const char* tag) const {
    std::shared_ptr<Transform2D> child = nullptr;
    for (const auto& c : mChildren) {
        if (c->mOwner->tag() == tag) {
            child = c;
        }
    }
    return child;
}

std::shared_ptr<Transform2D> Transform2D::parent() const {
    return mParent.lock();
}

std::shared_ptr<Transform2D> Transform2D::root() const {
    std::shared_ptr<Transform2D> root = mParent.lock();
    while (root) {
        auto p = root->mParent.lock();
        if (!p) {
            break;
        }
        root = p;
    }
    return root;
}

size_t Transform2D::getChildCount() const {
    return mChildren.size();
}

void Transform2D::setParent(std::shared_ptr<Transform2D> parent) {
    mParent = parent;
}

void Transform2D::recomputeTransform() {
    mIsRecomputeTransform = true;

    if (mChildren.empty()) {
        return;
    }
    for (auto&& child : mChildren) {
        child->mIsRecomputeTransform = true;
    }
}
