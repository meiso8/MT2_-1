#pragma once
#include"WVPVp.h"

//レンダリングパイプラインのヘッダー

//ワールド行列作成関数 平行移動
Matrix3x3 MakeTranslateMatrix(Vector2 rectCenter) {

    Matrix3x3 result = {};

    result.m[0][0] = 1.0f;
    result.m[1][0] = 0.0f;
    result.m[2][0] = rectCenter.x;

    result.m[0][1] = 0.0f;
    result.m[1][1] = 1.0f;
    result.m[2][1] = rectCenter.y;

    result.m[0][2] = 0.0f;
    result.m[1][2] = 0.0f;
    result.m[2][2] = 1.0f;

    return (result);
};

//アフィン行列作成関数
Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate) {
    Matrix3x3 result = {};

    result.m[0][0] = scale.x * cosf(theta);
    result.m[1][0] = scale.y * -sinf(theta);
    result.m[2][0] = translate.x;

    result.m[0][1] = scale.x * sinf(theta);
    result.m[1][1] = scale.y * cosf(theta);
    result.m[2][1] = translate.y;

    result.m[0][2] = 0.0f;
    result.m[1][2] = 0.0f;
    result.m[2][2] = 1.0f;

    return (result);
};

//ビュー行列作成関数 逆行列
Matrix3x3 Inverse(Matrix3x3 matrix) {

    float determinant = matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
        matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
        matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
        matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
        matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
        matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

    Matrix3x3 result;

    result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) /
        determinant;
    result.m[0][1] = (-1.0f * (matrix.m[0][1] * matrix.m[2][2] -
        matrix.m[0][2] * matrix.m[2][1])) /
        determinant;
    result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) /
        determinant;

    result.m[1][0] = (-1.0f * (matrix.m[1][0] * matrix.m[2][2] -
        matrix.m[1][2] * matrix.m[2][0])) /
        determinant;
    result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) /
        determinant;
    result.m[1][2] = (-1.0f * (matrix.m[0][0] * matrix.m[1][2] -
        matrix.m[0][2] * matrix.m[1][0])) /
        determinant;

    result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) /
        determinant;
    result.m[2][1] = (-1.0f * (matrix.m[0][0] * matrix.m[2][1] -
        matrix.m[0][1] * matrix.m[2][0])) /
        determinant;
    result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) /
        determinant;

    return result;
};

//正射影行列作成関数
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {

    //正規かデバイス座標系
    //NDC

    //引数は左上と右下の座標でカメラ空間上での座標である
    Matrix3x3 result = {};
    result.m[0][0] = 2.0f / (right - left);
    result.m[1][0] = 0.0f;
    result.m[2][0] = (left + right) / (left - right);

    result.m[0][1] = 0.0f;
    result.m[1][1] = 2.0f / (top - bottom);
    result.m[2][1] = (top + bottom) / (bottom - top);

    result.m[0][2] = 0.0f;
    result.m[1][2] = 0.0f;
    result.m[2][2] = 1.0f;

    return result;

}

//ビューポート行列作成関数
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
    //引数はスクリーン空間上でNDCがどこにどこの大きさで見えるかというのを指定する。

    //ビューポート変換
    Matrix3x3 result = {};
    result.m[0][0] = width / 2.0f;
    result.m[1][0] = 0.0f;
    result.m[2][0] = left + (width / 2.0f);

    result.m[0][1] = 0.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][1] = top + (height / 2.0f);

    result.m[0][2] = 0.0f;
    result.m[1][2] = 0.0f;
    result.m[2][2] = 1.0f;

    return result;
}

//掛け算
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
    Matrix3x3 result = {};
    result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] +
        matrix1.m[0][1] * matrix2.m[1][0] +
        matrix1.m[0][2] * matrix2.m[2][0];

    result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] +
        matrix1.m[0][1] * matrix2.m[1][1] +
        matrix1.m[0][2] * matrix2.m[2][1];

    result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] +
        matrix1.m[0][1] * matrix2.m[1][2] +
        matrix1.m[0][2] * matrix2.m[2][2];

    result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] +
        matrix1.m[1][1] * matrix2.m[1][0] +
        matrix1.m[1][2] * matrix2.m[2][0];

    result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] +
        matrix1.m[1][1] * matrix2.m[1][1] +
        matrix1.m[1][2] * matrix2.m[2][1];

    result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] +
        matrix1.m[1][1] * matrix2.m[1][2] +
        matrix1.m[1][2] * matrix2.m[2][2];

    result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] +
        matrix1.m[2][1] * matrix2.m[1][0] +
        matrix1.m[2][2] * matrix2.m[2][0];

    result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] +
        matrix1.m[2][1] * matrix2.m[1][1] +
        matrix1.m[2][2] * matrix2.m[2][1];

    result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] +
        matrix1.m[2][1] * matrix2.m[1][2] +
        matrix1.m[2][2] * matrix2.m[2][2];

    return (result);
};

//ベクトル変換
Vector2 Transform(Vector2 pos, Matrix3x3 worldMatrix) {
    Vector2 result = {};
    result.x = pos.x * worldMatrix.m[0][0] + pos.y * worldMatrix.m[1][0] +
        1.0f * worldMatrix.m[2][0];

    result.y = pos.x * worldMatrix.m[0][1] + pos.y * worldMatrix.m[1][1] +
        1.0f * worldMatrix.m[2][1];

    float w = pos.x * worldMatrix.m[0][2] + pos.y * worldMatrix.m[1][2] +
        1.0f * worldMatrix.m[2][2];

    assert(w != 0.0f); // 0だったらプログラムを終了する
    result.x /= w;
    result.y /= w;

    return (result);
};
