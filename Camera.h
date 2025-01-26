#pragma once
#include"WVPVp.h"

class Camera {
private:
    Vector2 pos_;
    Vector2 startPos_;
    Vector2 scale_;
    float theta_;
    Matrix3x3 worldMatrix_;
    Matrix3x3 viewMatrix_;
    Matrix3x3 orthoMatrix_;
    Matrix3x3 viewportMatrix_;
    Matrix3x3 wvpVpMatrix_;
public:
    Camera(const float& kWinWidth, const float& kWinHeight);
    void Init();
    void SetPos(Vector2 pos) { pos_ = pos; };
    void SetPosY(float posY) { pos_.y = posY; };
    void SetScale(Vector2 scale) { scale_ = scale; };

    Vector2 TransformScreenPos(Vector2 localTop, Matrix3x3 worldMatrix);
};


