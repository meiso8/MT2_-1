#include"Particle.h"
#include"Camera.h"
#include"Enemy.h"

const int Particle::startFrame_ = 0;
const int Particle::endFrame_ = 30;

Particle::Particle() {
    Init();
}

Particle::~Particle() {
    delete camera_;
    delete enemy_;
}

void Particle::Init() {

    isShot_ = false;
    radius_ = enemy_->GetRadius();
    worldPos_ = { 0.0f };
    screenPos_ = { 0.0f };
    worldMatrix_ = { 0.0f };
    frame_ = 0;
}

void Particle::Update() {

    frame_++;

    if (frame_ % 2 == 0) {

        if (!isShot_) {

            isShot_ = true;
            worldPos_ = enemy_->GetPos();
        }
    }

    if (isShot_) {

        if (frame_ < endFrame_) {
            isShot_ = false;
            frame_ = startFrame_;
        }

    }

    worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0.0f, worldPos_);
    screenPos_ = camera_->TransformScreenPos(Vector2(0.0f, 0.0f), worldMatrix_);

}

void Particle::Draw() {

    Novice::DrawEllipse(
        static_cast<int>(screenPos_.x),
        static_cast<int>(screenPos_.y),
        static_cast<int>(radius_),
        static_cast<int>(radius_),
        0.0f,
        WHITE,
        kFillModeSolid
    );
}