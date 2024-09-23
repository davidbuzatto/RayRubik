#pragma once

#include "raylib/raylib.h"

typedef enum CubeRotationType {
    CUBE_ROTATION_TYPE_X_ACW,
    CUBE_ROTATION_TYPE_X_CW,
    CUBE_ROTATION_TYPE_Y_ACW,
    CUBE_ROTATION_TYPE_Y_CW,
    CUBE_ROTATION_TYPE_Z_ACW,
    CUBE_ROTATION_TYPE_Z_CW
} CubeRotationType;

typedef struct Cube {

    Vector3 pos;
    Vector3 dim;

    Vector3 rotationAxis;
    Vector3 rotationAngles;
    Vector3 rotationVel;

    int startRotationAngle;
    
    bool rotating;
    bool rotatingX;
    bool rotatingY;
    bool rotatingZ;

    Model model;
    Color color;

} Cube;

Cube createCube( Vector3 pos, Vector3 dim, Vector3 rotationAngles, Color color );
void rotateCube( Cube *cube, float rotationSpeed, CubeRotationType rotationType );
void updateCube( Cube *cube, float delta );
void drawCube( Cube *cube );