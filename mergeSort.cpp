#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void intercalar(
        char *array1,
        char *array2,
        size_t tamanho_array1,
        size_t tamanho_array2,
        char *aux,
        size_t tamanho_elemento,
        int (* comparador)(void *, void *)
) {
    int a = 0, b = 0, c = 0;
    while (a < tamanho_array1 || b < tamanho_array2) {
        int ain = a < tamanho_array1;
        int bin = b < tamanho_array2;
        char *e1 = ain ? &array1[a * tamanho_elemento] : NULL;
        char *e2 = bin ? &array2[b * tamanho_elemento] : NULL;
        char *e3 = &aux[c * tamanho_elemento];
        char *comp = (e2 == NULL || (e1 != NULL && comparador(e1, e2) <= 0)) ? e1 : e2;
        memcpy(e3, comp, tamanho_elemento);
        if (comp == e1) a++; else b++;
        c++;
    }
}

void mergesort_aux(
        char *array,
        char *aux,
        size_t tamanho_elemento,
        size_t tamanho_array,
        int (* comparador)(void *, void *)
) {
    if (tamanho_array < 2) return;
    int metade1 = tamanho_array / 2;
    int metade2 = tamanho_array - metade1;
    mergesort_aux(array, aux, tamanho_elemento, metade1, comparador);
    char *temp = &array[metade1 * tamanho_elemento];
    mergesort_aux(temp, aux, tamanho_elemento, metade2, comparador);
    intercalar(array, temp, metade1, metade2, aux, tamanho_elemento, comparador);
    memcpy(array, aux, tamanho_elemento * tamanho_array);
}

void mergesort(
        void *array,
        size_t tamanho_elemento,
        size_t tamanho_array,
        int (* comparador)(void *, void *)
) {
    void *aux = malloc(tamanho_elemento * tamanho_array);
    mergesort_aux((char *) array, (char *) aux, tamanho_elemento, tamanho_array, comparador);
    free(aux);
}

typedef struct {
    int a;
    int b;
    int c;
} XPTO;

void criar_vetor(XPTO *v, int n) {
    for (int i = 0; i < n; i++) {
        v[i].a = (i % 3) + 4;
        v[i].b = 100 - i % 5;
        v[i].c = i;
    }
}

void imprimir_vetor(XPTO *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("(a=%d b=%d c=%d) ", v[i].a, v[i].b, v[i].c);
    }
    printf("\n");
}

int por_a(void *p1, void *p2) {
    XPTO *pp1 = (XPTO *) p1;
    XPTO *pp2 = (XPTO *) p2;
    return pp1->a - pp2->a;
}

int por_b(void *p1, void *p2) {
    XPTO *pp1 = (XPTO *) p1;
    XPTO *pp2 = (XPTO *) p2;
    return pp1->b - pp2->b;
}

#define T 20

int main(int argc, char* argv[]) {
    XPTO v[T];
    criar_vetor(v, T);

    printf("Antes:\n");
    imprimir_vetor(v, T);

    printf("\nPor A:\n");
    mergesort(v, sizeof(XPTO), T, por_a);
    imprimir_vetor(v, T);

    criar_vetor(v, T);
    printf("\nPor B:\n");
    mergesort(v, sizeof(XPTO), T, por_b);
    imprimir_vetor(v, T);

    return 0;
}