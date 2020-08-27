#include <stdio.h>
#include <stdlib.h>

#define N 2

typedef struct{
  char * titulo;
  int paginas;
}libro;

typedef struct{
    int valor;
}numero;

typedef void (*opcion_t) (int);

void series(int);
void bibliotecas(int);
void forward(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *));
    void bidirectional(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *));
void imprimirNumero(void *e, size_t i, void *arr, size_t len, void *ctx);
void imprimirLibro(void *e, size_t i, void *arr, size_t len, void *ctx);
/*Funciones génericas 
void recorre();

void forward();
void bidirectional();*/

int main(int argc, const char * argv[]) {
    
    
     opcion_t * menu = (opcion_t *) malloc( N * sizeof(opcion_t));
    
    *menu = series;
    *(menu+1) = bibliotecas;
    
     printf("--- Opciones --- \n1-Numeros\n2-Libros\nEscoge tu opcion: ");
    
    int opcion;
    
    scanf("%d", &opcion);
    
    (*(menu+opcion-1))(opcion);
    
    free(menu);
    
    return 0;
}

void series(int opcion){
    
    numero * serie;
    numero * aux;
    
    int cantidad = 0;
    
    printf(" ¿ Cuantos numeros quieres guardar ? : ");
    scanf("%d", &cantidad);

    int len = sizeof(numero) * cantidad;
    serie = (numero *) malloc(len);
    
    numero * final = serie + cantidad;
    
    for (aux = serie; aux < final; ++aux) {
        
       
        printf(" Ingrese el valor del numero: ");
        scanf("%d", &aux->valor);
        
    }
    
    printf("\n\n---Serie de numeros ---\n\n");
    forward(serie, sizeof(numero), cantidad, &serie, imprimirNumero);
}

void imprimirNumero(void *e, size_t i, void *arr, size_t len, void *ctx) {
    numero * n = (numero *)e;
    printf("%d\n", n->valor);
}

void bibliotecas(int opcion)
{
    libro * biblioteca;
    libro * aux;
    
    int cantidad = 0;
    
    printf(" ¿ Cuantos libros quieres guardar? : ");
    scanf("%d", &cantidad);
    
    biblioteca = (libro *) malloc(sizeof(libro) * cantidad);
    
    libro * final = biblioteca + cantidad;
    
    for (aux = biblioteca; aux < final; ++aux) {
        
        aux->titulo = (char * ) malloc(sizeof(char) * 25);
        
        printf("Entre el titulo del libro: ");
        scanf("%s", aux->titulo);

        
        printf("Entre el numero de paginas del libro: ");
        scanf("%d", &aux->paginas);
        
    }

    /*printf("\n\n--- Listado de libros ---\n\n");*/
    for (aux = biblioteca; aux < final; ++aux) {
        printf("%25s \t %4d \n",
               aux->titulo,
               aux->paginas);
           }
               printf("\n\n---Serie  ---\n\n");
    bidirectional(biblioteca, sizeof(libro), cantidad, &biblioteca, imprimirLibro);
}

void imprimirLibro(void *e, size_t i, void *arr, size_t len, void *ctx) {
    libro * t = (libro *)e;
    libro * p = (libro *)e;
    printf("%s\t %d \n", t->titulo,p->paginas);
   /* printf("%d\n", p->paginas); */
}

void forward(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *))
{
    if (len < 1)
        return;

    if (len == 1) {
        iter(arr, 0, arr, len, ctx);
        return;
    }

    size_t i;
    numero *data = (numero *) arr;
    for (i = 0; i < len; i++){
        iter(data + i, i, arr, len, ctx);
    }
    /*for (i = 0; i < len; i++){
        iter((data + len - 1) - i, i, arr, len, ctx);
    }*/
}

void bidirectional(void *arr, size_t size, size_t len, void *ctx,
    void (*iter)(void *, size_t, void *, size_t, void *))
{
    if (len < 1)
        return;

    if (len == 1) {
        iter(arr, 0, arr, len, ctx);
        return;
    }

    size_t i;
    libro *data = (libro *) arr;
    for (i = 0; i < len; i++){
        iter(data + i, i, arr, len, ctx);
    }
    for (i = 0; i < len; i++){
        iter((data + len - 1) - i, i, arr, len, ctx);
    }
}
