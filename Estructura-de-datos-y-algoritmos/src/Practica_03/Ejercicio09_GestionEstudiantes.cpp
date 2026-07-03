#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Clase Estudiante
class Estudiante
{
  private:
    string codigo;
    string nombre;
    int edad;
    string carrera;

  public:
    // Constructor por defecto
    Estudiante()
    {
    }

    // Constructor con parametros
    Estudiante(string c, string n, int e, string car)
    {
        codigo = c;
        nombre = n;
        edad = e;
        carrera = car;
    }

    // Metodos para establecer valores (setters)
    void setCodigo(string c)
    {
        codigo = c;
    }
    void setNombre(string n)
    {
        nombre = n;
    }
    void setEdad(int e)
    {
        edad = e;
    }
    void setCarrera(string c)
    {
        carrera = c;
    }

    // Metodos para obtener valores (getters)
    string getCodigo()
    {
        return codigo;
    }
    string getNombre()
    {
        return nombre;
    }
    int getEdad()
    {
        return edad;
    }
    string getCarrera()
    {
        return carrera;
    }

    // Metodo para mostrar los datos del estudiante
    void mostrar()
    {
        cout << "  Codigo: " << codigo << endl;
        cout << "  Nombre: " << nombre << endl;
        cout << "  Edad: " << edad << endl;
        cout << "  Carrera: " << carrera << endl;
        cout << "  --------------------" << endl;
    }
};

int main()
{
    vector<Estudiante> estudiantes; // Vector para almacenar objetos Estudiante
    int opcion;

    do
    {
        cout << "\n--- GESTION DE ESTUDIANTES ---" << endl;
        cout << "1. Registrar estudiante" << endl;
        cout << "2. Mostrar todos los estudiantes" << endl;
        cout << "3. Buscar estudiante por codigo" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            string codigo, nombre, carrera;
            int edad;

            cout << "Codigo: ";
            cin >> codigo;
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Edad: ";
            cin >> edad;
            cout << "Carrera: ";
            cin.ignore();
            getline(cin, carrera);

            // Crear objeto Estudiante y agregarlo al vector
            Estudiante e(codigo, nombre, edad, carrera);
            estudiantes.push_back(e);
            cout << "Estudiante registrado." << endl;
            break;
        }

        case 2:
            if (!estudiantes.empty())
            {
                cout << "\n--- LISTA DE ESTUDIANTES (" << estudiantes.size() << ") ---" << endl;
                for (int i = 0; i < estudiantes.size(); i++)
                {
                    cout << "Estudiante #" << i + 1 << endl;
                    estudiantes[i].mostrar(); // Llamar al metodo mostrar
                }
            }
            else
            {
                cout << "No hay estudiantes registrados." << endl;
            }
            break;

        case 3:
        {
            string cod;
            cout << "Ingrese codigo a buscar: ";
            cin >> cod;
            bool encontrado = false;
            for (int i = 0; i < estudiantes.size(); i++)
            {
                if (estudiantes[i].getCodigo() == cod)
                {
                    cout << "\n--- ESTUDIANTE ENCONTRADO ---" << endl;
                    estudiantes[i].mostrar();
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                cout << "Estudiante no encontrado." << endl;
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