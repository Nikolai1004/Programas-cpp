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
        cout << "\n--- REGISTRO DE CLIENTES ---" << endl;
        cout << "1. Registrar cliente" << endl;
        cout << "2. Atender cliente" << endl;
        cout << "3. Mostrar clientes pendientes" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Nombre del cliente: ";
            cin >> nombre;
            clientes.push(nombre); // Agregar cliente a la cola
            cout << "Cliente registrado." << endl;
            break;

        case 2:
            if (!clientes.empty())
            {
                cout << "Atendiendo a: " << clientes.front() << endl; // Mostrar primero
                clientes.pop();                                       // Eliminar cliente atendido
            }
            else
            {
                cout << "No hay clientes en espera." << endl;
            }
            break;

        case 3:
            if (!clientes.empty())
            {
                cout << "Clientes pendientes (" << clientes.size() << "):" << endl;
                queue<string> temp = clientes; // Copia para no perder datos
                int i = 1;
                while (!temp.empty())
                {
                    cout << "  " << i << ". " << temp.front() << endl;
                    temp.pop(); // Eliminar de la copia
                    i++;
                }
            }
            else
            {
                cout << "No hay clientes pendientes." << endl;
            }
            break;

        case 4:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4); // Repetir hasta que elija salir

    return 0;
}