#pragma once

#include "Matrix3x3.h"
#include"Vector2.h"
#include <math.h>
#include<assert.h>

//レンダリングパイプラインのヘッダー

//ワールド行列作成関数 平行移動
Matrix3x3 MakeTranslateMatrix(Vector2 rectCenter);

//アフィン行列作成関数
Matrix3x3 MakeAffineMatrix(Vector2 scale, float theta, Vector2 translate);

//ビュー行列作成関数 逆行列
Matrix3x3 Inverse(Matrix3x3 matrix);

//正射影行列作成関数
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

//ビューポート行列作成関数
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

//掛け算
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//ベクトル変換
Vector2 Transform(Vector2 pos, Matrix3x3 worldMatrix);
