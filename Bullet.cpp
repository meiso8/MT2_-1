#include"Bullet.h"
#include<Novice.h>
#include"CommonHeader.h"

int Bullet::coolTimer_ = 60;
bool Bullet::isCountDownTimer_ = false;

Bullet::Bullet() {

    radius_ = 8.0f;          // 半径

    Init();
}

void Bullet::Init() {

    worldPos_ = { -radius_,-radius_ };
    screenPos_ = { 0.0f };
    velocity_ = { 16.0f,0.0f };      // 速度
    repulsionFactor_ = 0.8f; // 反発係数
    isShot_ = false;
    isCountDownTimer_ = false;
    worldMatrix_ = { 0.0f };
}

bool Bullet::isHitLineY(float& lineY) const {
    return (worldPos_.y <= radius_ + lineY) ? true : false;
}

bool Bullet::isHitLineX(float& lineX) const {
    return (worldPos_.x <= radius_ + lineX) ? true : false;
}

void Bullet::Update(float& gravity, Vector2& linePos) {

    if (isShot_) {

        // -----------------------------------
        // 弾の発射フラグが真だったら
        // -----------------------------------

        velocity_.y +=
            gravity / FRAME; // 重力加速度を増加させる

        worldPos_.x += velocity_.x; // x軸方向に移動する
        worldPos_.y += velocity_.y; // y軸方向に移動する

        // -----------------------------------
        // 弾の跳ね返り処理
        // -----------------------------------

        if (worldPos_.y >= 720.0f - radius_) {
            worldPos_.y = 720.0f - radius_; // 地面についたら座標を固定する
            velocity_.y *= -repulsionFactor_; // 速度に反発係数を掛ける
        }

        if (isHitLineY(linePos.y)) {
            worldPos_.y = linePos.y + radius_; // 壁についたら座標を固定する
            velocity_.y *=
                -repulsionFactor_; // 速度に反発係数を掛ける
        }

        if (worldPos_.x >= 1280.0f - radius_) {
            isShot_ = false; // 画面外に出たら発射フラグを偽に
        }

    } else {

        // -----------------------------------
        // 弾の発射フラグが偽だったら向きを設定する
        // -----------------------------------

        velocity_.y++; // y速度を動かす

        if (fabs(velocity_.y) > 8.0f) {
            velocity_.y *= -1.0f; // 速度を反転する
        }
    }

}

void Bullet::CoolTimer(Vector2 playerPos) {

    if (!isCountDownTimer_) {
        //カウントダウンしていないとき
        isCountDownTimer_ = true;
    }

    if (isCountDownTimer_) {

        // クールタイムの計算
        if (coolTimer_ > 0) {
            // クールタイムが0より大きかったら
            coolTimer_--; // クールタイムを減らす
        } else {
            // それ以外だったら
            coolTimer_ = 60; // クールタイムを元に戻す
            isCountDownTimer_ = false;
        }

        if (coolTimer_ <= 0) {

            // クールタイムが0以下の時
            if (!isShot_) {
                // 弾が撃たれていなかったら

                // 自機の位置に持ってくる
                worldPos_.x = playerPos.x;
                worldPos_.y = playerPos.y;

                isShot_ = true; // 発射する
            }
        }

    }

}

void Bullet::Transform(Camera* camera) {

    worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0.0f, worldPos_);
    screenPos_ = camera->TransformScreenPos(Vector2(0.0f, 0.0f), worldMatrix_);
}

void Bullet::Draw() {

    if (isShot_) {

        Novice::DrawEllipse(
            static_cast<int>(screenPos_.x - radius_),
            static_cast<int>(screenPos_.y - radius_),
            static_cast<int>(radius_),
            static_cast<int>(radius_), 0.0f, 0xFF0000FF,
            kFillModeSolid);
    }

#ifdef _DEBUG

    ImGui::Begin("bullet");

    ImGui::Text("isShot_ %d", isShot_);
    ImGui::Text("isCountDownTimer_ %d", isCountDownTimer_);
    ImGui::End();

#endif // _DEBUG

}
