#include "Transform2D.h"
#include "Actor.h"

Transform2D::Transform2D(Actor* owner) :
    mOwner(owner),
    mWorldTransform(Matrix4::identity),
    mPosition(Vector3::zero),
    mRotation(Quaternion::identity),
    mPivot(Vector2::zero),
    mScale(Vector2::one),
    mSize(Vector2::zero),
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
        mWorldTransform = Matrix4::createScale(Vector3(mSize, 1.f)); //テクスチャサイズに
        mWorldTransform *= Matrix4::createTranslation(-Vector3(mSize * 0.5f + mPivot, 0.f)); //中心 + ピボットを原点に
        mWorldTransform *= Matrix4::createScale(Vector3(getWorldScale(), 1.f));
        mWorldTransform *= Matrix4::createFromQuaternion(getWorldRotation());
        mWorldTransform *= Matrix4::createTranslation(Vector3(getWorldPosition(), mPosition.z));

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
    shouldRecomputeTransform();
}

Vector2 Transform2D::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

Vector2 Transform2D::getWorldPosition() const {
    auto root = mParent.lock();
    auto pos = mPosition;
    while (root) {
        pos += root->mPosition;
        root = root->mParent.lock();
    }
    return Vector2(pos.x, pos.y);
}

void Transform2D::translate(const Vector2& translation) {
    mPosition.x += translation.x;
    mPosition.y += translation.y;
    shouldRecomputeTransform();
}

void Transform2D::setPrimary(float z) {
    mPosition.z = z;
    shouldRecomputeTransform();
}

float Transform2D::getDepth() const {
    return mPosition.z;
}

void Transform2D::setRotation(float angle) {
    angle *= 0.5f;
    float sinAngle = Math::sin(angle);

    mRotation.z = sinAngle;
    mRotation.w = Math::cos(angle);

    shouldRecomputeTransform();
}

Quaternion Transform2D::getRotation() const {
    return mRotation;
}

Quaternion Transform2D::getWorldRotation() const {
    auto root = mParent.lock();
    auto rotation = mRotation;
    while (root) {
        rotation = Quaternion::concatenate(rotation, root->mRotation);
        root = root->mParent.lock();
    }
    return rotation;
}

void Transform2D::rotate(float angle) {
    angle *= 0.5f;
    float sinAngle = Math::sin(angle);

    Quaternion inc;
    inc.z = sinAngle;
    inc.w = Math::cos(angle);

    mRotation = Quaternion::concatenate(mRotation, inc);

    shouldRecomputeTransform();
}

void Transform2D::setPivot(const Vector2& pivot) {
    mPivot = pivot;
    shouldRecomputeTransform();
}

Vector2 Transform2D::getPivot() const {
    return mPivot;
}

void Transform2D::setScale(const Vector2& scale) {
    mScale = scale;
    shouldRecomputeTransform();
}

void Transform2D::setScale(float scale) {
    mScale.x = scale;
    mScale.y = scale;
    shouldRecomputeTransform();
}

Vector2 Transform2D::getScale() const {
    return mScale;
}

Vector2 Transform2D::getWorldScale() const {
    auto root = mParent.lock();
    auto scale = mScale;
    while (root) {
        scale.x *= root->mScale.x;
        scale.y *= root->mScale.y;
        root = root->mParent.lock();
    }
    return scale;
}

void Transform2D::setSize(const Vector2& size) {
    mSize = size;
    shouldRecomputeTransform();
}

Vector2 Transform2D::getSize() const {
    return mSize;
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
    auto root = mParent.lock();
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

void Transform2D::shouldRecomputeTransform() {
    mIsRecomputeTransform = true;

    if (mChildren.empty()) {
        return;
    }
    for (auto&& child : mChildren) {
        child->mIsRecomputeTransform = true;
    }
}
