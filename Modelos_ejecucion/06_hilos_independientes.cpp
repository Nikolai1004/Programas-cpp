#include <iostream>
#include <thread>
using namespace std;

/*
Modelo: Hilos Independientes
Descripcion:
Cada hilo ejecuta una tarea propia sin compartir datos
ni depender de otros hilos.
*/

// Hilo 1
void tarea1() {
    for (int i = 1; i <= 5; i++) {
        cout << "Hilo 1 ejecutando paso " << i << endl;
    }
}

// Hilo 2
void tarea2() {
    for (int i = 1; i <= 5; i++) {
        cout << "Hilo 2 procesando paso " << i << endl;
    }
}

// Hilo 3
void tarea3() {
    for (int i = 1; i <= 5; i++) {
        cout << "Hilo 3 trabajando paso " << i << endl;
    }
}

int main() {

    cout << "=== MODELO DE HILOS INDEPENDIENTES ===\n";

    // Creación de hilos sin relación entre sí
    thread h1(tarea1);
    thread h2(tarea2);
    thread h3(tarea3);

    // Sincronización: esperar a que todos terminen
    h1.join();
    h2.join();
    h3.join();

    cout << "\nTodos los hilos terminaron." << endl;
    cout << "Fin del programa." << endl;

    return 0;
}