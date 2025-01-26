#pragma once
#include "Vector2.h"
#include"Matrix3x3.h"
#include<Novice.h>

class Character {
protected:
    float radius_ = 0.0f;
    Matrix3x3 worldMatrix_ = { 0.0f }; //ワールド行列
    Vector2 worldPos_ = { 0.0f };      // ワールド座標
    Vector2 velocity_ = { 0.0f };      // 速度
    float repulsionFactor_ = 0.0f;     // 反発係数
    int graphHandle_ = Novice::LoadTexture("./NoviceResources/white1x1.png"); // グラフハンドル
    bool isHit_ = false;            // 衝突フラグ
    bool isAlive_ = true;           // 生存フラグ
    int reactionTimer_ = 120;       // リアクションタイマー
    unsigned int color_ = WHITE;    // 色
};
