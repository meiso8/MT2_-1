#pragma once
#include "Character.h"
#include"Camera.h"
#define ENEMY_MAX 10

class Particle;

class Enemy :public Character {
private:
    Vector2 screenPos_ = { 0.0f };     // スクリーン座標
    float mass_ = { 1.0f };               //質量
    float magnitude_ = { 0.0f };          //動摩擦力
    Vector2 frictionForce_ = { 0.0f };    //摩擦力
    Vector2 acceleration_ = { 0.0f };     //加速度
    Vector2 airResistance_ = { 0.0f };//空気抵抗
    Vector2 airResistanceAcceleration_ = { 0.0f };//空気抵抗による加速度
    Vector2 direction_ = { 0.0f };        //方向
    bool isFrictionX_ = false;//摩擦フラグ
    bool isAir_ = true;//空気アリ
    static int frame_;
    float k_ = 0.6f;//空気抵抗係数
    Particle* particle[5];
public:

    Enemy();
    ~Enemy();
    void Init();

    void Update(bool& isMoon, Vector2& linePos, int& score, const Vector2& kGravity, float& miu);
    void Transform(Camera* camera);
    void Draw();

    bool isHitLineY(float& lineY);
    bool isHitLineX(float& lineX);

    Vector2 GetPos() { return worldPos_; };
    float GetRadius() { return radius_; };

    bool GetIsAlive() { return isAlive_; };
    void SetIsAlive(bool isAlive) { isAlive_ = isAlive; };

    bool GetIsHit() { return isHit_; };
    void SetIsHit(bool isHit) { isHit_ = isHit; };

};

