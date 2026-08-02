#include "raylib.h"
#include <math.h>


bool CheckCollisionRecsLine(Rectangle coordinate, float linea);


typedef struct Quadrato {
  
    float     massa;         
    float     velocita;      
    Rectangle coordinate;
                             
} Quadrato;              

int main () {

    const int screenWidth  = 800;
    const int screenHeight = 450;

    InitWindow (screenWidth, screenHeight, "finestra principale");

    int collisioni = 0;

    Quadrato quadrato1 = {
        .massa = 1,
        .coordinate = { .x = screenWidth/4*2 - 120, .y = 200, .width = 100, .height = 100 }
    };

    Quadrato quadrato2 = {
        .massa = 100,
        .velocita = -2,
        .coordinate = { .x = screenWidth/4*3 - 40, .y = 100, .width = 200, .height = 200 }
    };
    

    Vector2 inizio_linea_x = { quadrato1.coordinate.x - 230, 300 };
    Vector2 fine_linea_x   = { quadrato2.coordinate.x + 300, 300 };

    Vector2 inizio_linea_y = { quadrato1.coordinate.x - 230, 100 };
    Vector2 fine_linea_y   = { quadrato1.coordinate.x - 230, 300 };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        bool collisione_quadrato = CheckCollisionRecs(quadrato1.coordinate, quadrato2.coordinate);
        bool collisione_linea    = CheckCollisionRecsLine(quadrato1.coordinate, quadrato1.coordinate.y - 150);
       
        if (collisione_linea) {
            quadrato1.velocita = quadrato1.velocita * (-1);
            ++collisioni;
        }

        else if (collisione_quadrato) {
            
            float v1 = quadrato1.velocita;
            float v2 = quadrato2.velocita;

            float m1 = quadrato1.massa;
            float m2 = quadrato2.massa;
            
            quadrato1.velocita = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
            quadrato2.velocita = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);

            ++collisioni;
        }

        quadrato1.coordinate.x += quadrato1.velocita;
        quadrato2.coordinate.x += quadrato2.velocita;

        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            DrawRectangleRec     (quadrato1.coordinate, DARKGRAY);
            DrawRectangleLinesEx (quadrato1.coordinate, 2, BLACK);

            DrawRectangleRec     (quadrato2.coordinate, DARKGRAY);        
            DrawRectangleLinesEx (quadrato2.coordinate, 2, BLACK);

            DrawLineEx(inizio_linea_x, fine_linea_x, 5, BLACK); 
            DrawLineEx(inizio_linea_y, fine_linea_y, 5, BLACK);

            DrawText(TextFormat("Peso del primo quadrato: %.0f", quadrato1.massa), 20 , 30 , 10, BLACK);
            DrawText(TextFormat("Peso del secondo quadrato: %.0f", quadrato2.massa), 20, 40, 10, BLACK);
            DrawText(TextFormat("Collisioni: %d", collisioni), 20, 50, 10, BLACK);
            DrawText(TextFormat("Velocita cubo 1: %.2f", quadrato1.velocita), 20, 60, 10, BLACK);
            DrawText(TextFormat("Velocita cubo 2: %.2f", quadrato2.velocita), 20, 70, 10, BLACK);
           
        EndDrawing();
    }  

    CloseWindow();

    return 0;
}



bool CheckCollisionRecsLine (Rectangle coordinate, float linea) {
        
    if (coordinate.x <= linea) return true;

    return false;
}


