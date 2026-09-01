#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Digite o tamanho do vetor:");
    scanf("%d",&n);
    float *vetor = (float*)malloc(sizeof(float)*n);
    for(int x = 0;x<n;x++){
        printf("Digite o %d° elemento do vetor:",x+1);
        scanf("%f",(vetor+x));
    }
    printf("--- VETOR NA ORDEM INVERSA ---");
    for(int y = n-1; y>=0;y--){
        printf("\n%.2f\n",vetor[y]);
    }
    return 0;
}