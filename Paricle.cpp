#include"Particle.h"
#include"Enemy.h"
#include"CommonHeader.h"

int Particle::coolTime_ = 0;

Particle::Particle() {

    worldPos_ = { 0.0f };
    screenPos_ = { 0.0f };
    worldMatrix_ = { 0.0f };
    radius_ = 0.0f;
}

void Particle::Init(float& radius, Vector2& pos) {

    radius_ = radius;
    worldPos_ = pos;
    coolTime_ = 10;
}

void Particle::Update(float& radius, Vector2& pos) {

    if (coolTime_ > 0) {
        coolTime_--;
    } else {
        Init(radius, pos);
    }

}

void Particle::Transform(Camera* camera) {

    worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0.0f, worldPos_);
    screenPos_ = camera->TransformScreenPos(Vector2(0.0f, 0.0f), worldMatrix_);

}

void Particle::Draw() {

    Novice::DrawEllipse(
        static_cast<int>(screenPos_.x),
        static_cast<int>(screenPos_.y),
        static_cast<int>(radius_),
        static_cast<int>(radius_),
        0.0f,
        GREEN - 160,
        kFillModeSolid
    );

}