#pragma once
#include"Vector2.h"
#include"Matrix3x3.h"

class Camera;
class Enemy;

class Particle {
private:
    bool isShot_ = false;
    float radius_;
    Vector2 worldPos_;
    Vector2 screenPos_;
    Matrix3x3 worldMatrix_;
    static int frame_;
    static const int startFrame_;
    static const int endFrame_;
    Camera* camera_;
    Enemy* enemy_;
public:
    Particle();
    ~Particle();
    void Init();
    void Update();
    void Draw();
};