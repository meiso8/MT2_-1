#include"Player.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"CommonHeader.h"

Player::Player() {

    for (int i = 0; i < bulletMax; ++i) {
        bullet_[i] = new Bullet;
    }

    Init();
}

Player::~Player() {

    for (int i = 0; i < bulletMax; ++i) {
        delete bullet_[i];
    }

}

void Player::Init() {

    // 半径
    radius_ = 16.0f;
    //四頂点
    leftTop_ = { -radius_,radius_ };
    rightTop_ = { radius_,radius_ };
    leftBottom_ = { -radius_,-radius_ };
    rightBottom_ = { radius_,-radius_ };

    // ワールド座標
    worldPos_ = { 96.0f,360.0f };
    //拡縮
    scale_ = { 1.0f,1.0f };
    //回転
    theta_ = 0.0f;
    // 速度
    velocity_ = { 0.0f,16.0f };

    color_ = RED;
    score_ = 0;

    for (int i = 0; i < bulletMax; ++i) {
        bullet_[i]->Init();
    }

}

void Player::Update(char* keys, float& gravity, Vector2& linePos) {

    // ===================================
    // 自機の更新処理
    // ===================================

#pragma region // 自機の更新処理

      // 自機の移動
    if (keys[DIK_W]) {

        if (worldPos_.y < 720.0f - velocity_.y - radius_) {
            worldPos_.y += velocity_.y;
        }

    }

    if (keys[DIK_S]) {

        if (worldPos_.y > velocity_.y + radius_) {
            worldPos_.y -= velocity_.y;
        }
    }
#pragma endregion

    // ===================================
    // 弾の更新処理
    // ===================================

#pragma region // 弾の更新処理

    if (keys[DIK_SPACE]) {
        //  スペースキーが押されている間
        for (int i = 0; i < bulletMax; i++) {
            bullet_[i]->CoolTimer(worldPos_);
        }

        theta_ -= 2.0f * static_cast<float>(M_PI) / FRAME;
    } else {
        theta_ += static_cast<float>(M_PI) / FRAME;
    }

    for (int i = 0; i < bulletMax; i++) {
        bullet_[i]->Update(gravity, linePos);
    }

#pragma endregion
}

void Player::Transform(Camera* camera) {

    worldMatrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);

    screenLeftTop_ = camera->TransformScreenPos(leftTop_, worldMatrix_);
    screenRightTop_ = camera->TransformScreenPos(rightTop_, worldMatrix_);
    screenLeftBottom_ = camera->TransformScreenPos(leftBottom_, worldMatrix_);
    screenRightBottom_ = camera->TransformScreenPos(rightBottom_, worldMatrix_);

    for (int i = 0; i < bulletMax; i++) {
        bullet_[i]->Transform(camera);
    }

}

void Player::Draw() {

    Novice::DrawQuad(
        static_cast<int>(screenLeftTop_.x),
        static_cast<int>(screenLeftTop_.y),
        static_cast<int>(screenRightTop_.x),
        static_cast<int>(screenRightTop_.y),
        static_cast<int>(screenLeftBottom_.x),
        static_cast<int>(screenLeftBottom_.y),
        static_cast<int>(screenRightBottom_.x),
        static_cast<int>(screenRightBottom_.y),
        0,
        0,
        1,
        1,
        graphHandle_,
        color_);

    for (int i = 0; i < bulletMax; i++) {
        bullet_[i]->Draw();
    }

    DrawScore();
}

void Player::DrawScore() {

    Novice::ScreenPrintf(
        static_cast<int>(screenLeftTop_.x),
        static_cast<int>(screenLeftTop_.y - 24.0f),
        "Score:%d", score_);
}
