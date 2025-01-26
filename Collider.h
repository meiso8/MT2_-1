#pragma once
#include<math.h>
#include"Vector2.h"

bool CircleCollider(Vector2 pos1, Vector2 pos2, float radius1, float radius2) {

    return(sqrtf(powf(pos1.x - pos2.x, 2) + powf(pos1.y - pos2.y, 2)) <= radius1 + radius2) ? true : false;

}

