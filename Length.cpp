#include"Length.h"

float Length(Vector2 direction) {

    return sqrtf(powf(direction.x, 2.0f) + powf(direction.y, 2.0f));

}