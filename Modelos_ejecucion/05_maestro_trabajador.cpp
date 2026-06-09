#include <iostream>
#include <thread>
#include <vector>
using namespace std;

/*
Modelo: Maestro-Trabajador
Descripcion:
El hilo principal (maestro) divide el trabajo en partes
y asigna cada una a diferentes hilos (trabajadores).
Luego, recopila y combina los resultados parciales.
*/

// Funcion que ejecutan los trabajadores
void trabajador(int id, int inicio, int fin, int &resultado) {
    resultado = 0;

    for (int i = inicio; i <= fin; i++) {
        resultado += i;
    }

    cout << "Trabajador " << id << " proceso rango [" 
         << inicio << "-" << fin << "]\n";
}

int main() {

    cout << "=== MODELO MAESTRO-TRABAJADOR ===\n";

    int r1 = 0, r2 = 0, r3 = 0;
    int total = 0;

    cout << "\nEl maestro divide el trabajo en 3 partes.\n" << endl;

    // El maestro crea trabajadores asignando tareas específicas
    thread t1(trabajador, 1, 1, 30, ref(r1));
    thread t2(trabajador, 2, 31, 60, ref(r2));
    thread t3(trabajador, 3, 61, 100, ref(r3));

    // Sincronizacion: espera a que todos los trabajadores terminen
    t1.join();
    t2.join();
    t3.join();

    // Integracion de resultados parciales
    total = r1 + r2 + r3;

    cout << "\nResultados parciales:\n";
    cout << "Trabajador 1: " << r1 << endl;
    cout << "Trabajador 2: " << r2 << endl;
    cout << "Trabajador 3: " << r3 << endl;

    cout << "\nResultado total: " << total << endl;

    cout << "\nFin del programa maestro-trabajador." << endl;

    return 0;
}