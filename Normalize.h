#pragma once

float Normalize(float length) {

    if (length != 0.0f) {
        return length / length;
    }

    return 0.0f;

}