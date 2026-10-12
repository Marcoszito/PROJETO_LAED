#include <stdlib.h>
#include "raylib.h"
#include "entidade.h"

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600

int main(void) {
    InitWindow(LARGURA_JANELA, ALTURA_JANELA, "Reuso do Modulo Entidade");
    SetTargetFPS(60);

    Entidade *jogador = entidadeCriar(ENTIDADE_JOGADOR, (Vector2){ 200.0f, 300.0f });
    Entidade *inimigo = entidadeCriar(ENTIDADE_INIMIGO, (Vector2){ 300.0f, 300.0f });
    Entidade *item    = entidadeCriar(ENTIDADE_ITEM,    (Vector2){ 400.0f, 300.0f });

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            entidadeDesenhar(jogador);
            entidadeDesenhar(inimigo);
            entidadeDesenhar(item);

            DrawText("Demonstracao de reuso do modulo", 150, 50, 20, DARKGRAY);
            DrawText("Pressione ESC para sair", 10, ALTURA_JANELA - 25, 16, GRAY);
        EndDrawing();
    }
    free(jogador);
    free(inimigo);
    free(item);

    CloseWindow();
    return 0;
}