#pragma once
#include"Vector2.h"
#include"Matrix3x3.h"
#include"Camera.h"

#define PARTICLE_MAX 5

class Particle {
private:
    float radius_;
    Vector2 worldPos_;
    Vector2 screenPos_;
    Matrix3x3 worldMatrix_;
    static int coolTime_;
public:
    Particle();
    void Init(float& radius, Vector2& pos);
    void Update(float& radius, Vector2& pos);
    void Transform(Camera* camera);
    void Draw();
};