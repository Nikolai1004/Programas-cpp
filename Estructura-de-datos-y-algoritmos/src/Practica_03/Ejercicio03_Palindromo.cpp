#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
    stack<char> pila;
    string palabra, invertida = "";

    cout << "Ingrese una palabra: ";
    cin >> palabra;

    // Guardar cada caracter en la pila
    for (int i = 0; i < palabra.length(); i++)
    {
        pila.push(palabra[i]);
    }

    // Construir la palabra invertida
    while (!pila.empty())
    {
        invertida += pila.top();
        pila.pop();
    }

    // Verificar si es palindromo
    if (palabra == invertida)
    {
        cout << "La palabra \"" << palabra << "\" SI es un palindromo." << endl;
    }
    else
    {
        cout << "La palabra \"" << palabra << "\" NO es un palindromo." << endl;
    }

    return 0;
}