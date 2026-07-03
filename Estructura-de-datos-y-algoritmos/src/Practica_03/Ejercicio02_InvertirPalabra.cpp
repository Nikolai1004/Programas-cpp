#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
    stack<char> pila; // Pila para almacenar caracteres
    string palabra;

    cout << "Ingrese una palabra: ";
    cin >> palabra;

    // Guardar cada caracter en la pila
    for (int i = 0; i < palabra.length(); i++)
    {
        pila.push(palabra[i]);
    }

    // Mostrar la palabra invertida
    cout << "Palabra invertida: ";
    while (!pila.empty())
    {
        cout << pila.top(); // Mostrar el caracter de la cima
        pila.pop();         // Eliminar el caracter mostrado
    }
    cout << endl;

    return 0;
}