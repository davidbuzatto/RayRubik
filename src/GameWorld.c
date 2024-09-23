/**
 * @file GameWorld.h
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>

#include "GameWorld.h"
#include "ResourceManager.h"

#include "Cube.h"

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

const float CUBE_ROTATION_SPEED = 200.0f;

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld* createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    gw->cube = createCube( 
        (Vector3){ 0.0f, 0.0f, 0.0f },
        (Vector3){ 2.0f, 2.0f, 2.0f },
        (Vector3){ 0.0f, 0.0f, 0.0f },
        ORANGE
    );

    gw->camera = (Camera3D) {
        .position = { 0.0f, 10.0f, 20.0f },
        .fovy = 45.0f,
        .up = { 0.0f, 1.0f, 0.0f },
        .target = gw->cube.pos,
        .projection = CAMERA_PERSPECTIVE
    };

    return gw;

}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void inputAndUpdateGameWorld( GameWorld *gw ) {

    float delta = GetFrameTime();

    Cube *cube = &gw->cube;

    if ( IsKeyPressed( KEY_UP ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_X_CW );
    } else if ( IsKeyPressed( KEY_DOWN ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_X_ACW );
    } else if ( IsKeyPressed( KEY_LEFT ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_Y_CW );
    } else if ( IsKeyPressed( KEY_RIGHT ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_Y_ACW );
    } else if ( IsKeyPressed( KEY_PAGE_DOWN ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_Z_CW );
    } else if ( IsKeyPressed( KEY_DELETE ) ) {
        rotateCube( cube, CUBE_ROTATION_SPEED, CUBE_ROTATION_TYPE_Z_ACW );
    }

    updateCube( &gw->cube, delta );

}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    BeginMode3D( gw->camera );
    drawCube(& gw->cube );
    EndMode3D();

    EndDrawing();

}