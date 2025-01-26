#include"Enemy.h"
#include"Length.h"
#include"Normalize.h"
#include"CommonHeader.h"
#include"Particle.h"

int Enemy::frame_ = 0;

bool Enemy::isHitLineY(float& lineY) {
    return (worldPos_.y <= radius_ + lineY) ? true : false;
}

bool Enemy::isHitLineX(float& lineX) {
    return (worldPos_.x <= radius_ + lineX) ? true : false;
}

Enemy::Enemy() {
    isAlive_ = false;
    Init();

    for (int i = 0; i < PARTICLE_MAX; ++i) {
        particle[i] = new Particle();
    }
}

Enemy::~Enemy() {

    for (int i = 0; i < PARTICLE_MAX; ++i) {
        delete particle[i];
    }

}

void Enemy::Init() {

    //エネミーのコンストラクタ

    //見た目が大きいほどあんこは重いものとし、重いほど反発係数を低くする
    radius_ = 8.0f * (rand() % 4 + 1.0f); // 半径
    mass_ = radius_ / 8.0f;//質量

    repulsionFactor_ = 1.0f / mass_;  // 反発係数

    worldPos_.x = 1280.0f; // ワールド座標x
    worldPos_.y =
        rand() % (720 - static_cast<int>(radius_ * 2.0f - 64.0f)) +
        64.0f + radius_;                // ワールド座標y
    screenPos_.x = { 0.0f }; // スクリーン座標x

    velocity_.x = -16.0f * mass_;  // 初速度
    velocity_.y = -16.0f * (rand() % 8 + 1.0f);// 初速度

    isHit_ = false;                   // 衝突フラグ
    isAlive_ = true;
    color_ = 0xFFFFFFFF;              // 白
    reactionTimer_ = 30;              // リアクションタイマー
    isFrictionX_ = false;
}

void Enemy::Update(bool& isMoon, Vector2& linePos, int& score, const Vector2& kGravity, float& miu) {

    if (isAlive_) {

        if (!isMoon) {
            //空気抵抗は速度に対して比例して逆方法に発生する
            airResistance_ = { k_ * -velocity_.x,k_ * -velocity_.y };

            //加速度とはa=F/mであるから、空気抵抗による加速度は
            airResistanceAcceleration_.x = airResistance_.x / mass_;
            airResistanceAcceleration_.y = airResistance_.y / mass_;

            //まず現時点での加速度を求める
            acceleration_.x = (kGravity.x + airResistanceAcceleration_.x);
            acceleration_.y = (kGravity.y + airResistanceAcceleration_.y);
        }

        if (isFrictionX_) {

            //動摩擦力N　μ*||kg*m/s2|| の大きさを求める
            magnitude_ = miu * Length(Vector2(mass_ * kGravity.x, mass_ * kGravity.y));

            //box.velocity.xを利用して摩擦力の動く向きを求める
            direction_.x = -Normalize(velocity_.x);

            //動摩擦力を求める
            frictionForce_.x = magnitude_ * direction_.x;

            //動摩擦力によって発生する加速度を求めるma = Fより、a = F/m
            acceleration_.x = frictionForce_.x / mass_;

            //摩擦による加速度が今回の速度の増分より大きければ符号が変わり、逆方向へと進ませてしまう。実際そんなことはありえないので計算して0になるように補正
            if (fabs(acceleration_.x / FRAME) > fabs(velocity_.x)) {
                acceleration_.x = velocity_.x * FRAME;
            }

        }


        if (isHitLineY(linePos.y)) {

            // 地面についたら座標を固定する
            worldPos_.y = radius_ + linePos.y;
            velocity_.y *= -repulsionFactor_; // 速度に反発係数を掛ける

            isFrictionX_ = true;
        }

        velocity_.y += acceleration_.y / FRAME;
        worldPos_.y += velocity_.y; // y軸方向に移動する

        //後の加速度や速度の扱いはボールと同じ
        velocity_.x += acceleration_.x / FRAME;
        worldPos_.x += velocity_.x / FRAME; // x軸方向に移動する

        //if (fabs(velocity_.x) > 0.01f || fabs(velocity_.y) > 0.01f) {
//    //動いているかどうかの判定

//}


        // -----------------------------------
        // スコアの処理
        // -----------------------------------

        if (isHitLineX(linePos.x)) {
            // 線を超えたら実行される処理
            isAlive_ = false; // 生存フラグを偽にする
            score -= 10;              // スコアを減らす
        }

        if (isHit_) {
            isAlive_ = false; // 生存フラグを偽にする
            color_ = GREEN - 128;
            score += 10; // スコアを増やす
        }



    } else {

        // -----------------------------------
        // リアクションタイマー
        // -----------------------------------

        if (reactionTimer_ >= 0) {
            reactionTimer_--;
        } else {

            Init();
        }

    }

    // -----------------------------------
    // パーティクルの処理
    // -----------------------------------

    for (int i = 0; i < PARTICLE_MAX; ++i) {
        particle[i]->Update(radius_, worldPos_);
    }

}

void Enemy::Transform(Camera* camera) {

    worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0.0f, worldPos_);
    screenPos_ = camera->TransformScreenPos(Vector2(0.0f, 0.0f), worldMatrix_);


    for (int i = 0; i < PARTICLE_MAX; ++i) {
        particle[i]->Transform(camera);
    }
}

void Enemy::Draw() {


    if (isAlive_) {

        for (int i = 0; i < PARTICLE_MAX; ++i) {
            particle[i]->Draw();
        }

    }

    if (reactionTimer_ % 2 == 0) {
        Novice::DrawEllipse(static_cast<int>(screenPos_.x),
            static_cast<int>(screenPos_.y),
            static_cast<int>(radius_),
            static_cast<int>(radius_), 0.0f,
            color_, kFillModeSolid);
    }


#ifdef _DEBUG

    ImGui::Begin("enemy");
    ImGui::Text("isHit_ %d", isHit_);
    ImGui::SliderFloat("pos_.x", &worldPos_.x, 0.0f, 1280.0f);
    ImGui::SliderFloat("velocity_.y", &velocity_.y, -120.0f, 120.0f);
    ImGui::SliderFloat("repulsionFactor_.y", &repulsionFactor_, 0.0f, 0.8f);
    ImGui::SliderFloat("mass_", &mass_, 0.0f, 10.0f);
    ImGui::Text("isFrictionX_ %d", isFrictionX_);

    ImGui::End();

#endif // _DEBUG

}

