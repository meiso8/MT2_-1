#pragma once
#include"Character.h"
#include"Bullet.h"
#include"Camera.h"

class Player :public Character {
private:
    int score_;
    Vector2 scale_ = { 1.0f,1.0f };
    float theta_ = 0.0f;
    Vector2 leftTop_;
    Vector2 rightTop_;
    Vector2 leftBottom_;
    Vector2 rightBottom_;
    Vector2 screenLeftTop_;
    Vector2 screenRightTop_;
    Vector2 screenLeftBottom_;
    Vector2 screenRightBottom_;
public:
    Bullet* bullet_[bulletMax];

public:
    Player();
    ~Player();
    void Init();
    void Transform(Camera* camera);
    void Update(char* keys, float& gravity, Vector2& linePos);
    void Draw();
    void DrawScore();

    int& GetScore() { return score_; };
    Vector2 GetPos() { return worldPos_; };
};

