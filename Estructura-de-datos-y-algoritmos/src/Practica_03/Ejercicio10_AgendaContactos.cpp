#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Clase Contacto
class Contacto
{
  private:
    string nombre;
    string telefono;
    string email;

  public:
    // Constructor por defecto
    Contacto()
    {
    }

    // Constructor con parametros
    Contacto(string n, string t, string e)
    {
        nombre = n;
        telefono = t;
        email = e;
    }

    // Metodos para establecer valores (setters)
    void setNombre(string n)
    {
        nombre = n;
    }
    void setTelefono(string t)
    {
        telefono = t;
    }
    void setEmail(string e)
    {
        email = e;
    }

    // Metodos para obtener valores (getters)
    string getNombre()
    {
        return nombre;
    }
    string getTelefono()
    {
        return telefono;
    }
    string getEmail()
    {
        return email;
    }

    // Metodo para mostrar los datos del contacto
    void mostrar()
    {
        cout << "  Nombre: " << nombre << endl;
        cout << "  Telefono: " << telefono << endl;
        cout << "  Email: " << email << endl;
        cout << "  --------------------" << endl;
    }
};

int main()
{
    vector<Contacto> agenda; // Vector para almacenar objetos Contacto
    int opcion;

    do
    {
        cout << "\n--- AGENDA DE CONTACTOS ---" << endl;
        cout << "1. Agregar contacto" << endl;
        cout << "2. Buscar por nombre" << endl;
        cout << "3. Eliminar contacto" << endl;
        cout << "4. Mostrar todos los contactos" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string nombre, telefono, email;

            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Telefono: ";
            getline(cin, telefono);
            cout << "Email: ";
            getline(cin, email);

            // Crear objeto Contacto y agregarlo al vector
            Contacto c(nombre, telefono, email);
            agenda.push_back(c);
            cout << "Contacto agregado." << endl;
            break;
        }

        case 2:
        {
            string nom;
            cout << "Nombre a buscar: ";
            cin.ignore();
            getline(cin, nom);

            bool encontrado = false;
            for (int i = 0; i < agenda.size(); i++)
            {
                if (agenda[i].getNombre() == nom)
                {
                    cout << "\n--- CONTACTO ENCONTRADO ---" << endl;
                    agenda[i].mostrar();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                cout << "Contacto no encontrado." << endl;
            }
            break;
        }

        case 3:
        {
            string nom;
            cout << "Nombre a eliminar: ";
            cin.ignore();
            getline(cin, nom);

            bool eliminado = false;
            for (int i = 0; i < agenda.size(); i++)
            {
                if (agenda[i].getNombre() == nom)
                {
                    agenda.erase(agenda.begin() + i); // Eliminar del vector
                    cout << "Contacto eliminado." << endl;
                    eliminado = true;
                    break;
                }
            }
            if (!eliminado)
            {
                cout << "Contacto no encontrado." << endl;
            }
            break;
        }

        case 4:
            if (!agenda.empty())
            {
                cout << "\n--- LISTA DE CONTACTOS (" << agenda.size() << ") ---" << endl;
                for (int i = 0; i < agenda.size(); i++)
                {
                    cout << "Contacto #" << i + 1 << endl;
                    agenda[i].mostrar();
                }
            }
            else
            {
                cout << "No hay contactos registrados." << endl;
            }
            break;

        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 5);

    return 0;
}