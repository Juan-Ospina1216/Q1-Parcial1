#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <math.h>
#define _USE_MATH_DEFINES

using namespace std;

void*montecarlo(void*id);
double n;
int cant_hilos;
long long suma_total = 0;
pthread_mutex_t mutex;

int main(int argc, char*argv[]){
    time_t inicio = time(NULL);
    clock_t start = clock();
    cant_hilos = atoi(argv[1]);
    n = atoi(argv[2]);

    srand(time(0));
    pthread_t hilos[cant_hilos];  //Arreglo de hilos
    int hilos_id[cant_hilos];  //Arreglo con los id
    pthread_mutex_init(&mutex, NULL);  //Mutex para evitar conflictos al acceder a variable suma_total
    for(int i = 0; i < cant_hilos; i++){
        hilos_id[i] = i;
        pthread_create(&hilos[i], NULL, montecarlo, &hilos_id[i]);
    }
    for(int j = 0; j < cant_hilos; j++){
        pthread_join(hilos[j], NULL);
    }
    pthread_mutex_destroy(&mutex);
    time_t fin = time(NULL);
    clock_t end = clock();
    double aprox_pi = (suma_total / n) * 4;
    cout << "Aproximacion de pi: " << aprox_pi << endl;
    //cout << "Tiempo en CPU: " << end - start << endl;
    //cout << "Wall-clock time: " << fin - inicio << endl;
    cout << "Error relativo: " << fabs(aprox_pi - M_PI) / M_PI * 100 << "%" << endl;
    return 0;
}

void*montecarlo(void*id){
    int rango = *(int*) id;
    int local_m = n / cant_hilos;
    int inicio = rango * local_m;
    int fin = inicio + local_m;  //Asignar rango para cada hilo
    int a = -1, b = 1;
    double en_circulo = 0;
    for(int i = 0; i < n; i++){
        double x = a + (static_cast<double>(rand())/RAND_MAX) * (b-a);  //Generar numero aleatorio en [-1,1]
        double y = a + (static_cast<double>(rand())/RAND_MAX) * (b-a);
        double distancia = (x*x) + (y*y);  //distancia desde el origen
        if(distancia <= 1.0){ //Radio del circulo
            en_circulo ++;
        }
    }
    pthread_mutex_lock(&mutex);  //Mutex para bloquear la variable
    suma_total += en_circulo;
    pthread_mutex_unlock(&mutex);
    return NULL;
}