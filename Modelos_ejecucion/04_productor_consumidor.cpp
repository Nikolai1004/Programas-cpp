#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

/*
Modelo: Productor-Consumidor
Descripcion:
Un hilo (productor) genera datos y los coloca en una cola compartida.
Otro hilo (consumidor) extrae y procesa esos datos de forma coordinada.
*/

queue<int> buffer;
mutex mtx;
condition_variable cv;
bool produccionTerminada = false;

// Hilo productor: genera datos y los agrega al buffer
void productor() {
    for (int i = 1; i <= 5; i++) {
        unique_lock<mutex> lock(mtx);

        buffer.push(i);
        cout << "Productor genero el dato: " << i << endl;

        lock.unlock();
        cv.notify_one(); // Notifica al consumidor que hay datos

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // Indica que ya no se generaran mas datos
    unique_lock<mutex> lock(mtx);
    produccionTerminada = true;
    lock.unlock();
    cv.notify_one();
}

// Hilo consumidor: espera datos y los procesa
void consumidor() {
    while (true) {
        unique_lock<mutex> lock(mtx);

        // Espera hasta que haya datos o termine la produccion
        cv.wait(lock, [] {
            return !buffer.empty() || produccionTerminada;
        });

        if (!buffer.empty()) {
            int dato = buffer.front();
            buffer.pop();

            cout << "Consumidor proceso el dato: " << dato << endl;
        } 
        else if (produccionTerminada) {
            break; // Finaliza si no hay mas datos
        }

        lock.unlock();
    }
}

int main() {

    cout << "=== MODELO PRODUCTOR-CONSUMIDOR ===" << endl;
    cout << "\nEl productor genera datos y el consumidor los procesa.\n" << endl;

    // Creacion de hilos
    thread hiloProductor(productor);
    thread hiloConsumidor(consumidor);

    // Sincronizacion de finalizacion
    hiloProductor.join();
    hiloConsumidor.join();

    cout << "\nFin del programa productor-consumidor." << endl;

    return 0;
}S