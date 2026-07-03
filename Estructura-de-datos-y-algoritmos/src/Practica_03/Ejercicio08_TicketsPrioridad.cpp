#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Estructura para almacenar cada ticket
struct Ticket
{
    int codigo;
    string cliente;
    int prioridad; // 1=Alta, 2=Media, 3=Baja
};

// Funcion para comparar prioridad (menor numero = mayor prioridad)
struct CompararPrioridad
{
    bool operator()(Ticket const &t1, Ticket const &t2)
    {
        return t1.prioridad > t2.prioridad; // Prioridad mas alta primero
    }
};

int main()
{
    priority_queue<Ticket, vector<Ticket>, CompararPrioridad> cola;
    int codigo = 1000;
    int opcion;

    do
    {
        cout << "\n--- SISTEMA DE TICKETS ---" << endl;
        cout << "1. Crear ticket" << endl;
        cout << "2. Atender ticket" << endl;
        cout << "3. Mostrar orden de atencion" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            Ticket t;
            t.codigo = codigo++;
            cout << "Nombre del cliente: ";
            cin >> t.cliente;
            cout << "Prioridad (1=Alta, 2=Media, 3=Baja): ";
            cin >> t.prioridad;
            cola.push(t);
            cout << "Ticket #" << t.codigo << " creado." << endl;
            break;
        }

        case 2:
            if (!cola.empty())
            {
                Ticket t = cola.top();
                cola.pop();
                cout << "Atendiendo ticket #" << t.codigo
                     << " - " << t.cliente
                     << " (Prioridad: " << t.prioridad << ")" << endl;
            }
            else
            {
                cout << "No hay tickets en espera." << endl;
            }
            break;

        case 3:
        {
            if (!cola.empty())
            {
                priority_queue<Ticket, vector<Ticket>, CompararPrioridad> temp = cola;
                cout << "Orden de atencion:" << endl;
                int i = 1;
                while (!temp.empty())
                {
                    Ticket t = temp.top();
                    temp.pop();
                    cout << "  " << i++ << ". #" << t.codigo
                         << " - " << t.cliente
                         << " (Prio: " << t.prioridad << ")" << endl;
                }
            }
            else
            {
                cout << "No hay tickets pendientes." << endl;
            }
            break;
        }

        case 4:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    return 0;
}