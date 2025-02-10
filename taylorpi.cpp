#include <iostream>
#include <cstdlib>
using namespace std;

double aproximarPiSerie(int upper_bound){
    double ans = 0.0;
    for (int i = 0; i < upper_bound; i++){
        if (i % 2 == 0){
            ans += 1.0 / (2*i + 1);
        }else {
            ans -= 1.0 / (2*i + 1);
        }
    }
    ans = 4.0 * ans;
    return ans;
}

double aproximarPiFraccion(int upper_bound){
    double ans = 0.0;
    if (upper_bound == 0){
        ans = 4;
    } else{
        for (int i = upper_bound; i > 0; i--){
            int num = (2*(i-1) + 1) * (2*(i-1) + 1);
            ans = num / (2 + ans);
        }
        ans = 4.0 / (1 + ans);
    }
    return ans;
}

int main(int argc, char* argv[]){
    int num = atoi(argv[1]);
    double res1 = aproximarPiSerie(num);
    double res2 = aproximarPiFraccion(num);
    cout << "El resultado con Serie es: " << res1 << endl;
    cout << "El resultado con Fraccion es: " << res2 << endl;

}