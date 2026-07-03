#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main()
{
    queue<string> clientes; // Cola para almacenar clientes en espera
    string nombre;
    int opcion;

    do
    {
        cout << "\n--- BANCO - SISTEMA DE TURNOS ---" << endl;
        cout << "1. Agregar cliente" << endl;
        cout << "2. Atender cliente" << endl;
        cout << "3. Mostrar siguiente cliente" << endl;
        cout << "4. Mostrar cantidad de clientes" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Nombre del cliente: ";
            cin >> nombre;
            clientes.push(nombre); // Agregar cliente a la cola
            cout << "Cliente agregado. Turno #" << clientes.size() << endl;
            break;

        case 2:
            if (!clientes.empty())
            {
                cout << "Atendiendo a: " << clientes.front() << endl;
                clientes.pop(); // Eliminar cliente atendido
                cout << "Clientes restantes: " << clientes.size() << endl;
            }
            else
            {
                cout << "No hay clientes en espera." << endl;
            }
            break;

        case 3:
            if (!clientes.empty())
            {
                cout << "Siguiente cliente: " << clientes.front() << endl; // Ver proximo sin eliminar
            }
            else
            {
                cout << "No hay clientes en espera." << endl;
            }
            break;

        case 4:
            cout << "Clientes en cola: " << clientes.size() << endl; // Mostrar cantidad
            break;

        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5); // Repetir hasta que elija salir

    return 0;
}