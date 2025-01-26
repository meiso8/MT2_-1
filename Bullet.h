#pragma once
#include "Vector2.h"
#include"Matrix3x3.h"
#include"Camera.h"

const int bulletMax = 10;

class Bullet {
private:
    static int coolTimer_;           // 弾のクールタイマー
    static bool isCountDownTimer_;   //カウントダウンフラグ
    float radius_;                   // 半径
    Matrix3x3 worldMatrix_;          // ワールド行列
    Vector2 worldPos_;               // ワールド座標
    Vector2 screenPos_;              // スクリーン座標
    Vector2 velocity_;               // 速度
    float repulsionFactor_;          // 反発係数
    bool isShot_;                    // 発射フラグ
public:
    Bullet();
    void Init();
    void Transform(Camera* camera);
    void Update(float& gravity, Vector2& linePos);
    void CoolTimer(Vector2 playerPos);
    bool isHitLineY(float& lineY);
    bool isHitLineX(float& lineX);

    void Draw();

    void SetIsShot(bool isShot) { isShot_ = isShot; };
    void SeyVelocityY(float velY) { velocity_.y = velY; };

    Vector2 GetPos() { return worldPos_; };
    float GetRadius() { return radius_; };
    bool GetIsShot() { return isShot_; };
};
