#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> pila; // Pila para almacenar los numeros
    int num;

    cout << "Ingrese numeros (escriba -1 para terminar):" << endl;

    // Bucle para ingresar numeros
    while (true)
    {
        cout << "Numero: ";
        cin >> num;

        // Condicion de salida
        if (num == -1)
        {
            break;
        }

        pila.push(num); // Agregar el numero a la pila
    }

    // Mostrar resultados
    cout << "\n--- Resultados ---" << endl;
    cout << "Cantidad de elementos en la pila: " << pila.size() << endl;

    // Verificar si hay elementos antes de mostrar el ultimo
    if (!pila.empty())
    {
        cout << "Ultimo elemento ingresado: " << pila.top() << endl;
    }
    else
    {
        cout << "No se ingresaron elementos." << endl;
    }

    return 0;
}