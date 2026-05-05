#include <iostream>
#include <thread>
using namespace std;

/*
Modelo: Paralelo
Descripcion:
El programa divide una tarea grande en dos partes.
Cada hilo calcula una parte de la suma y luego el hilo principal
combina los resultados parciales.
*/

// Funcion que suma un rango de numeros asignado a un hilo
void sumarRango(int inicio, int fin, int &resultado) {
    resultado = 0;

    for (int i = inicio; i <= fin; i++) {
        resultado += i;
    }
}

int main() {

    cout << "=== MODELO DE EJECUCION PARALELO ===" << endl;

    int resultado1 = 0;
    int resultado2 = 0;
    int sumaTotal = 0;

    cout << "\nEl trabajo se divide en dos partes." << endl;
    cout << "Hilo 1 suma del 1 al 50." << endl;
    cout << "Hilo 2 suma del 51 al 100.\n" << endl;

    // Creacion de hilos para ejecutar partes independientes del trabajo
    thread hilo1(sumarRango, 1, 50, ref(resultado1));
    thread hilo2(sumarRango, 51, 100, ref(resultado2));

    // El hilo principal espera a que ambos hilos terminen
    hilo1.join();
    hilo2.join();

    // Integracion de resultados parciales
    sumaTotal = resultado1 + resultado2;

    cout << "Resultado del hilo 1: " << resultado1 << endl;
    cout << "Resultado del hilo 2: " << resultado2 << endl;
    cout << "Suma total del 1 al 100: " << sumaTotal << endl;

    cout << "\nFin del programa paralelo." << endl;

    return 0;
}