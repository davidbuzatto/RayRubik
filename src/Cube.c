#include <math.h>

#include "Cube.h"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

Cube createCube( Vector3 pos, Vector3 dim, Vector3 rotationAngles, Color color ) {

    Mesh mesh = GenMeshCube( dim.x, dim.y, dim.z );
    Model model = LoadModelFromMesh( mesh );

    Cube cube = {
        .pos = pos,
        .dim = { 2.0f, 2.0f, 2.0f },
        .rotationAxis = { 0.0f, 1.0f, 0.0f },
        .rotationAngles = rotationAngles,
        .rotationVel = { 0.0f, 0.0f, 0.0f },
        .startRotationAngle = 0,
        .rotating = false,
        .model = model,
        .color = color
    };

    return cube;

}

void rotateCube( Cube *cube, float rotationSpeed, CubeRotationType rotationType ) {

    if ( !cube->rotating ) {

        cube->rotationVel = (Vector3) { 0 };

        switch ( rotationType ) {
            case CUBE_ROTATION_TYPE_X_CW:
                cube->rotationAxis = (Vector3) { 1.0f, 0.0f, 0.0f };
                cube->rotationVel.x = -rotationSpeed;
                break;
            case CUBE_ROTATION_TYPE_X_ACW:
                cube->rotationAxis = (Vector3) { 1.0f, 0.0f, 0.0f };
                cube->rotationVel.x = rotationSpeed;
                break;
            case CUBE_ROTATION_TYPE_Y_CW:
                cube->rotationAxis = (Vector3) { 0.0f, 1.0f, 0.0f };
                cube->rotationVel.y = -rotationSpeed;
                break;
            case CUBE_ROTATION_TYPE_Y_ACW:
                cube->rotationAxis = (Vector3) { 0.0f, 1.0f, 0.0f };
                cube->rotationVel.y = rotationSpeed;
                break;
            case CUBE_ROTATION_TYPE_Z_CW:
                cube->rotationAxis = (Vector3) { 0.0f, 0.0f, 1.0f };
                cube->rotationVel.z = -rotationSpeed;
                break;
            case CUBE_ROTATION_TYPE_Z_ACW:
                cube->rotationAxis = (Vector3) { 0.0f, 0.0f, 1.0f };
                cube->rotationVel.z = rotationSpeed;
                break;
        }

        cube->startRotationAngle = 0.0f;
        cube->rotating = true;

    }

}

void updateCube( Cube *cube, float delta ) {

    if ( cube->rotating ) {

        float rotationAmountX = cube->rotationVel.x * delta;
        float rotationAmountY = cube->rotationVel.y * delta;
        float rotationAmountZ = cube->rotationVel.z * delta;

        cube->rotationAngles.x += DEG2RAD * rotationAmountX;
        cube->rotationAngles.y += DEG2RAD * rotationAmountY;
        cube->rotationAngles.z += DEG2RAD * rotationAmountZ;

        cube->startRotationAngle += fabs( rotationAmountX ) + fabs( rotationAmountY ) + fabs( rotationAmountZ );

        if ( cube->startRotationAngle >= 90.0f ) {
            cube->rotationAngles.x = (float) ( (int) cube->rotationAngles.x );
            cube->rotationAngles.y = (float) ( (int) cube->rotationAngles.y );
            cube->rotationAngles.z = (float) ( (int) cube->rotationAngles.z );
            cube->rotating = false;
        }

    }

}

void drawCube( Cube *cube ) {

    //cube->model.
    cube->model.transform = MatrixRotateXYZ( cube->rotationAngles );

    DrawModel( 
        cube->model, 
        cube->pos,
        1.0f,
        cube->color
    );

    DrawModelWires( 
        cube->model, 
        cube->pos,
        1.0f,
        BLACK
    );

    /*DrawModelEx( 
        cube->model, 
        cube->pos, 
        cube->rotationAxis, 
        (float) cube->rotationAngle, 
        (Vector3){ 1.0f, 1.0f, 1.0f },
        cube->color
    );

    DrawModelWiresEx( 
        cube->model, 
        cube->pos, 
        cube->rotationAxis, 
        (float) cube->rotationAngle, 
        (Vector3){ 1.0f, 1.0f, 1.0f },
        BLACK
    );*/

}