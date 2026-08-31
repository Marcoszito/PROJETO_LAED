#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA  600
#define TAM_CELULA     40
#define LIMITE_BOLA    50

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float   raio;
    Color   cor;
} Bola;

int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int **)malloc(linhas * sizeof(int *));
    if (matriz == NULL) return NULL;

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void desenharMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Color cor = (matriz[i][j] == 1) ? (Color){50, 80, 120, 255}
                                            : (Color){15, 30, 55, 255};
            DrawRectangle(j * TAM_CELULA, i * TAM_CELULA,
                          TAM_CELULA - 2, TAM_CELULA - 2, cor);
        }
    }
}

Bola *criarBolas(int quantidade) {
    Bola *bolas = (Bola *)malloc(quantidade * sizeof(Bola));
    if (bolas == NULL) return NULL;

    for (int i = 0; i < quantidade; i++) {
        Bola *b = (bolas + i);
        b->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50),
                            (float)GetRandomValue(50, ALTURA_JANELA - 50) };
        b->vel = (Vector2){ (float)GetRandomValue(-4, 4),
                            (float)GetRandomValue(-4, 4) };
        b->raio = (float)GetRandomValue(10, 25);
        b->cor  = (Color){ GetRandomValue(100, 255), GetRandomValue(100, 255),
                           GetRandomValue(100, 255), 255 };
    }
    return bolas;
}

void atualizarBola(Bola *b, int**matriz, int linhas, int colunas) {
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    if (b->pos.x - b->raio < 0 || b->pos.x + b->raio > LARGURA_JANELA)
        b->vel.x *= -1;
    if (b->pos.y - b->raio < 0 || b->pos.y + b->raio > ALTURA_JANELA)
        b->vel.y *= -1;
    
    int coluna = (int)(b->pos.x / TAM_CELULA), linha = (int)(b->pos.y / TAM_CELULA);
    if(linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas){
        matriz[linha][coluna] = 1;
}
}

int main(void) {
    srand((unsigned int)time(NULL));

    InitWindow(LARGURA_JANELA, ALTURA_JANELA,
               "Ponteiros e Alocacao Dinamica - raylib");
    SetTargetFPS(60);

    int linhas   = ALTURA_JANELA / TAM_CELULA;
    int colunas  = LARGURA_JANELA / TAM_CELULA;
    int **grade  = criarMatriz(linhas, colunas);

    int quantidadeBolas = 12;
    Bola *bolas = criarBolas(quantidadeBolas);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE) && quantidadeBolas < LIMITE_BOLA) {
            quantidadeBolas++;
            Bola *tempor = (Bola *)realloc(bolas, quantidadeBolas * sizeof(Bola));
            
            if (tempor != NULL) {
                bolas = tempor;
                Bola *b = &bolas[quantidadeBolas - 1];
                b->pos = (Vector2){ (float)GetRandomValue(50, LARGURA_JANELA - 50),
                                    (float)GetRandomValue(50, ALTURA_JANELA - 50) };
                b->vel = (Vector2){ (float)GetRandomValue(-4, 4),
                                    (float)GetRandomValue(-4, 4) };
                b->raio = (float)GetRandomValue(10, 25);
                b->cor  = (Color){ GetRandomValue(100, 255), GetRandomValue(100, 255),
                                   GetRandomValue(100, 255), 255 };
            } else {
                quantidadeBolas--;
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE) && quantidadeBolas > 0) {
            quantidadeBolas--;
            
            if (quantidadeBolas == 0) {
                free(bolas);
                bolas = NULL;
            } else {
                Bola *tempor = (Bola *)realloc(bolas, quantidadeBolas * sizeof(Bola));
                if (tempor != NULL) {
                    bolas = tempor;
                }
            }
        }
        for (int i = 0; i < quantidadeBolas; i++) {
            atualizarBola((bolas + i), grade, linhas, colunas);
        }
        int celulasVisitadas = 0;
        for (int i = 0; i < linhas;i++){
            for(int j = 0; j < colunas;j++){
                if(grade[i][j] == 1){
                    celulasVisitadas++;
}
}
}
        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenharMatriz(grade, linhas, colunas);

        for (int i = 0; i < quantidadeBolas; i++){
            DrawCircleV(bolas[i].pos, bolas[i].raio, bolas[i].cor);
        }
        DrawText("Matriz (int**) e vetor de structs (Bola*) alocados com malloc",10, 10, 18, WHITE);
        DrawText("Pressione ESC para sair", 10, ALTURA_JANELA - 25, 16, WHITE);
        DrawText(TextFormat("Bolas: %d", quantidadeBolas), 10, 25, 18, WHITE);
        DrawText(TextFormat("Visitadas: %d / %d", celulasVisitadas, linhas * colunas), 10, 40, 18, RED);
        EndDrawing();
    }
    if (bolas != NULL) {
        free(bolas);
    }
    liberarMatriz(grade, linhas);
    CloseWindow();
    return 0;
}