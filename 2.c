#include <stdio.h>
#include <stdlib.h>

int main(){
    int l,c;
    printf("Quantas linhas na matriz?");
    scanf("%d",&l);
    printf("Quantas colunas na matriz?");
    scanf("%d",&c);
    int **matriz = (int**)malloc(l*(sizeof(int*)));
    for(int x = 0;x < l;x++){
        matriz[x] = malloc(c*sizeof(int));
        if(matriz[x] == NULL){
            printf("Acabou a memória");
            exit(1);
        }
    }
    for(int x = 0;x<l;x++){
        for(int y = 0;y < c;y++){
            printf("Digite o elemento [%d][%d]:",x,y);
            scanf("%d",&matriz[c*x+y]);
        }
    }
    printf("\n---Matriz normal---\n");
    for(int x = 0;x<l;x++){
        for(int y = 0;y < c;y++){
            printf("Elemento[%d][%d]:%d\n",x,y,matriz[x*c+y]);
        }
    }
    printf("\n---Matriz transposta---\n");
    for(int x = 0;x<c;x++){
        for(int y = 0;y < l;y++){
            printf("Elemento[%d][%d]:%d\n",x,y,matriz[y*c+x]);
        }
    }
    return 0;
}