#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
using namespace std;

double calcularPi(double lanzamientos){
    srand(time(0));
    double contPuntos = 0;
    double ans = 0.0;
    int a = -1;
    int b = 1;
    for (int i = 0; i < lanzamientos; i++){
        double x1 = a + (static_cast<double>(rand()) / RAND_MAX) * (b - a); // ->[-1,1]
        double y1 = a + (static_cast<double>(rand()) / RAND_MAX) * (b - a); // ->[-1,1]
        if(x1*x1 + y1*y1 <= 1){ //El radio del circulo es igual a 1
            contPuntos++;
        }
    }
    ans = 4 * (contPuntos/lanzamientos);
    return ans;
}


int main(int argc, char* argv[]) {
    time_t inicio = time(NULL);
    clock_t start = clock();
    int num = atoi(argv[1]);
    double res = calcularPi(num);
    clock_t end = clock();
    time_t fin = time(NULL);
    cout << "La aproximacion es: " << res << endl;
    cout << "Tiempo CPU: " << end - start << endl;
    cout << "Wall-clock time: " << fin - inicio << endl;
}