#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
    stack<string> historial;
    string pagina;
    int opcion;

    do
    {
        cout << "\n--- NAVEGADOR WEB ---" << endl;
        cout << "1. Visitar pagina" << endl;
        cout << "2. Retroceder" << endl;
        cout << "3. Mostrar pagina actual" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Ingrese URL: ";
            cin >> pagina;
            historial.push(pagina);
            cout << "Visitando: " << pagina << endl;
            break;

        case 2:
            if (!historial.empty())
            {
                cout << "Retrocediendo de: " << historial.top() << endl;
                historial.pop();
                if (!historial.empty())
                {
                    cout << "Pagina actual: " << historial.top() << endl;
                }
                else
                {
                    cout << "No hay paginas en el historial." << endl;
                }
            }
            else
            {
                cout << "No hay paginas para retroceder." << endl;
            }
            break;

        case 3:
            if (!historial.empty())
            {
                cout << "Pagina actual: " << historial.top() << endl;
            }
            else
            {
                cout << "No hay paginas visitadas." << endl;
            }
            break;

        case 4:
            cout << "Saliendo del navegador..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    return 0;
}