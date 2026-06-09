#include <iostream>
#include <thread>
using namespace std;

/*
Modelo: Concurrente
Descripcion:
El programa utiliza dos hilos que ejecutan tareas de manera independiente.
Ambos hilos avanzan dentro del mismo periodo de tiempo, lo que permite
observar un comportamiento concurrente en la ejecución.
*/

// Función 1 (se ejecuta en un hilo)
void tarea1() {
    for (int i = 1; i <= 5; i++) {
        cout << "Tarea 1 - Paso " << i << endl;
    }
}

// Función 2 (se ejecuta en otro hilo)
void tarea2() {
    for (int i = 1; i <= 5; i++) {
        cout << "Tarea 2 - Paso " << i << endl;
    }
}

int main() {

    cout << "=== MODELO CONCURRENTE ===\n";

    // Creación de hilos secundarios
    thread hilo1(tarea1);
    thread hilo2(tarea2);

    /*
    Sincronización:
    El hilo principal espera a que ambos hilos terminen
    antes de finalizar el programa.
    */
    hilo1.join();
    hilo2.join();

    cout << "Fin del programa concurrente\n";

    return 0;
}