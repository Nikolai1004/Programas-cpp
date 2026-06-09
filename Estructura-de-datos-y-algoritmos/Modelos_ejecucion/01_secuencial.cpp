#include <iostream>
using namespace std;

/*
Modelo: Secuencial
Descripcion:
Las instrucciones se ejecutan en orden, una después de otra,
sin uso de hilos ni ejecución simultánea.
*/

int main() {
    
    int n1, n2, n3;
    double promedio;

    cout << "=== MODELO SECUENCIAL ===\n";

    // Entrada de datos (flujo lineal)
    cout << "\nPaso 1: Ingresar nota 1: ";
    cin >> n1;

    cout << "Paso 2: Ingresar nota 2: ";
    cin >> n2;

    cout << "Paso 3: Ingresar nota 3: ";
    cin >> n3;

    // Procesamiento (depende de los datos ingresados)
    cout << "\nPaso 4: Calculando promedio...\n";
    promedio = (n1 + n2 + n3) / 3.0;

    // Salida de resultado
    cout << "Paso 5: Mostrando resultado...\n";
    cout << "El promedio es: " << promedio << endl;

    cout << "\nFin del programa (ejecucion secuencial)\n";

    return 0;
}