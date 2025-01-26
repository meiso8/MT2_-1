#include"Camera.h"

Camera::Camera(const float& kWinWidth, const float& kWinHeight) {

    startPos_ = { kWinWidth / 2.0f,kWinHeight / 2.0f };

    pos_ = startPos_;
    scale_ = { 1.0f,1.0f };
    theta_ = 0.0f;
    worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
    viewMatrix_ = Inverse(worldMatrix_);
    orthoMatrix_ = MakeOrthographicMatrix(-(kWinWidth / 2.0f), (kWinHeight / 2.0f), (kWinWidth / 2.0f), -(kWinHeight / 2.0f));
    viewportMatrix_ = MakeViewportMatrix(0.0f, 0.0f, kWinWidth, kWinHeight);
    wvpVpMatrix_ = { 0.0f };
}

void Camera::Init() {
    pos_ = startPos_;
    scale_ = { 1.0f,1.0f };
    theta_ = 0.0f;
}

Vector2 Camera::TransformScreenPos(Vector2 localPos, Matrix3x3 worldMatrix) {

    worldMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
    viewMatrix_ = Inverse(worldMatrix_);

    //全ての行列の積を求めローカル空間上の矩形をスクリーン空間に変換する
    wvpVpMatrix_ = Multiply(Multiply(Multiply(worldMatrix, viewMatrix_), orthoMatrix_), viewportMatrix_);
    //座標を返す
    return Transform(localPos, wvpVpMatrix_);
}

