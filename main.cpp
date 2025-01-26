#include <Novice.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Vector2.h"
#include"Player.h"
#include"Enemy.h"
#include"Collider.h"
#include"Bullet.h"
#include"Camera.h"
#include"CommonHeader.h"

// ===================================
// 定数の宣言
// ===================================

const char kWindowTitle[] = "LC1A_25_ヨシダトモカ_MT2_評価課題1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, WIN_WIDTH, WIN_HEIGHT);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // ---------------------------------
    // 乱数の初期化
    // ---------------------------------

    srand(static_cast<unsigned int>(time(nullptr)));

    // ===================================　
    // インスタンスの生成
    // ===================================

    Player* player = new Player();

    Enemy* enemy[ENEMY_MAX];

    for (int i = 0; i < ENEMY_MAX; ++i) {
        enemy[i] = new Enemy();
    }

    Camera* camera = new Camera(WIN_WIDTH, WIN_HEIGHT);

    // ===================================
    // シーンで使う列挙と変数の宣言
    // ===================================

    enum Scene { TITLE, GAME, END };

    int scene = TITLE;  // タイトルで初期化

    Vector2 selectButton = { 600.0f, 328.0f };

    bool isMoon = false; // 月モード

    //重力加速度1は1m
    Vector2 gravity = { 0.0f,-9.8f };

    float miu = 0.4f;//動摩擦係数

    // -----------------------------------
    // 防衛ライン
    // -----------------------------------

    //ワールド座標
    Vector2 linePos = { 64.0f, 64.0f };

    // -----------------------------------
    // ゲームタイマー
    // -----------------------------------

    int gameTimer = 0;

    int frame = 0;

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        switch (scene) {
        case TITLE:

            if (keys[DIK_W] && !preKeys[DIK_W]) {
                selectButton.y = 328;
                isMoon = false; // 月モード
            }

            if (keys[DIK_S] && !preKeys[DIK_S]) {
                selectButton.y = 344;
                isMoon = true; // 地球モード
            }

            if (isMoon) {
                gravity.y = -9.8f / 6.0f;
            } else {
                gravity.y = -9.8f;
            }

            // 更新処理
            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
                // ENTERキーを押した瞬間
                scene = GAME; // ゲームシーンに
            }

            // 描画処理
            Novice::DrawBox(static_cast<int>(selectButton.x),
                static_cast<int>(selectButton.y), 128, 16, 0.0f,
                0x000000FF, kFillModeSolid); // ホバーエフェクト

            Novice::ScreenPrintf(600, 328,
                "EARTH"); // 地球
            Novice::ScreenPrintf(600, 344,
                "MOON"); // 月
            Novice::ScreenPrintf(600, 360,
                "PRESS SPACE"); // スペースキーを押すとゲームが始まる

            break;
        case GAME:

            ///
            /// ↓更新処理ここから
            ///

#pragma region // 更新処理

            // ===================================
            // 自機の更新処理
            // ===================================

            player->Update(keys, gravity.y, linePos);

            // ===================================
            // 敵の更新処理
            // ===================================

            if (frame % 10 == 0) {

                for (int i = 0; i < ENEMY_MAX; ++i) {

                    if (!enemy[i]->GetIsAlive()) {

                        enemy[i]->SetIsAlive(true);

                    }

                }
            }

            for (int i = 0; i < ENEMY_MAX; ++i) {
                enemy[i]->Update(isMoon, linePos, player->GetScore(), gravity, miu);
            }

            // ===================================
            // 当たり判定
            // ===================================

            for (int i = 0; i < ENEMY_MAX; i++) {

                if (enemy[i]->GetIsAlive()) {

                    for (int j = 0; j < bulletMax; j++) {

                        if (player->bullet_[j]->GetIsShot()) {

                            if (CircleCollider(enemy[i]->GetPos(), player->bullet_[j]->GetPos(), enemy[i]->GetRadius(), player->bullet_[j]->GetRadius())) {

                                enemy[i]->SetIsHit(true);

                                player->bullet_[j]->SetIsShot(false);
                                player->bullet_[j]->SeyVelocityY(0.0f);
                            }

                        }

                    }

                }

            }

            // ===================================
            // ゲームタイマーの処理
            // ===================================

            if (frame < FRAME) {
                frame++;
            } else {
                frame = 0;
                gameTimer++;
            }

            if (gameTimer == 60) {
                scene = END;
            }

            // ===================================
            // 座標変換処理
            // ===================================

            player->Transform(camera);

            for (int i = 0; i < ENEMY_MAX; ++i) {
                enemy[i]->Transform(camera);
            }

#pragma endregion

            ///
            /// ↑更新処理ここまで
            ///

            ///
            /// ↓描画処理ここから
            ///

#pragma region // 描画処理

            // ===================================
            // 背景の描画処理
            // ===================================

            if (player->GetScore() < 0) {
                Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);
            } else {
                Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x404040FF, kFillModeSolid);
            }

            // ===================================
            // 防衛ラインの描画処理
            // ===================================

            //レンダリングパイプラインで描画してない
            Novice::DrawLine(static_cast<int>(linePos.x), 0,
                static_cast<int>(linePos.x), static_cast<int>(WIN_HEIGHT), WHITE);

            Novice::DrawLine(static_cast<int>(linePos.x), static_cast<int>((linePos.y * -1.0f) + WIN_HEIGHT),
                static_cast<int>(WIN_WIDTH), static_cast<int>((linePos.y * -1.0f) + WIN_HEIGHT), WHITE);

            // ===================================
            // 敵機の描画処理
            // ===================================

            for (int i = 0; i < ENEMY_MAX; ++i) {
                enemy[i]->Draw();
            }

            // ===================================
            // 自機の描画処理
            // ===================================

            player->Draw();

            // ===================================
            // ゲームタイマーの描画処理
            // ===================================

            Novice::ScreenPrintf(0, 0, "gameTimer:%d", gameTimer);

            ImGui::SliderFloat("miu", &miu, 0.0f, 1.0f);
            ImGui::Text("isMoon %d", isMoon);

            if (ImGui::Button("isMoon")) {
                if (isMoon) {
                    isMoon = false;
                } else {
                    isMoon = true;
                }
            }

#pragma endregion

            ///
            /// ↑描画処理ここまで
            ///

            break;
        case END:

            if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {

                player->Init();
                for (int i = 0; i < ENEMY_MAX; ++i) {
                    enemy[i]->Init();
                }

                gameTimer = 0;

                scene = TITLE;
            }

            // 描画処理
            Novice::ScreenPrintf(600, 344, "Score:%d", player->GetScore()); // スコア

            Novice::ScreenPrintf(620, 360,
                "END"); // エンド

            break;
        }

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    delete player;

    for (int i = 0; i < ENEMY_MAX; ++i) {
        delete enemy[i];
    }

    delete camera;

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
