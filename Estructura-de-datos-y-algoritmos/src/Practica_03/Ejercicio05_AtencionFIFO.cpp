#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main()
{
    queue<string> cola;
    string nombre;

    cout << "Registre 10 personas para atencion:" << endl;

    // Registrar 10 personas
    for (int i = 0; i < 10; i++)
    {
        cout << "Persona " << i + 1 << ": ";
        cin >> nombre;
        cola.push(nombre);
    }

    cout << "\n--- Atendiendo personas (FIFO) ---" << endl;

    // Atender en orden de llegada
    int turno = 1;
    while (!cola.empty())
    {
        cout << "Atendiendo #" << turno << ": " << cola.front() << endl;
        cola.pop();
        turno++;
    }

    return 0;
}