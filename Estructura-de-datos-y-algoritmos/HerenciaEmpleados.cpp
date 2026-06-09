#include <iostream>
#include <string>

using namespace std;

// ==================== CLASE PADRE ====================
// Contiene SOLO: nombre, apellido y edad (como pide el enunciado)
class Empleado
{
  protected:
    string nombre;
    string apellido;
    int edad;

  public:
    // Constructor de la clase padre
    Empleado(string _nombre, string _apellido, int _edad)
    {
        nombre = _nombre;
        apellido = _apellido;
        edad = _edad;
    }

    // METODO PARA MOSTRAR DATOS (en la clase padre como pide el enunciado)
    void mostrarDatos()
    {
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Edad: " << edad << " años" << endl;
    }
};

// ==================== CLASE HIJA ====================
// Se llama EmpleadoEmpresa (nombre mas profesional)
// Aqui van: ocupacion, horas(40) y sueldo
// Aqui van los metodos: empleado por planta y empleado por hora
class EmpleadoEmpresa : public Empleado
{
  private:
    string ocupacion;
    int horas; // Siempre sera 40
    double sueldo;

  public:
    // Constructor de la clase hija
    EmpleadoEmpresa(string _nombre, string _apellido, int _edad, string _ocupacion)
        : Empleado(_nombre, _apellido, _edad)
    {
        ocupacion = _ocupacion;
        horas = 40; // Cantidad de horas siempre 40
        sueldo = 0;
    }

    // METODO PARA EMPLEADO POR HORA (operador)
    // Calcula el sueldo del operador: 40 horas * 50 soles = 2000 soles
    void empleadoPorHora()
    {
        if (ocupacion == "operador")
        {
            sueldo = horas * 50;
        }
    }

    // METODO PARA EMPLEADO DE PLANTA (supervisor y gerente)
    // Supervisor: 40 horas * 80 soles = 3200 soles
    // Gerente: 40 horas * 100 soles = 4000 soles
    void empleadoDePlanta()
    {
        if (ocupacion == "supervisor")
        {
            sueldo = horas * 80;
        }
        else if (ocupacion == "gerente")
        {
            sueldo = horas * 100;
        }
    }

    // Metodo para mostrar todos los datos (incluye los de la clase padre)
    void mostrarTodo()
    {
        mostrarDatos(); // Llama al metodo de la clase padre
        cout << "Ocupacion: " << ocupacion << endl;
        cout << "Horas: " << horas << endl;
        cout << "Sueldo: S/. " << sueldo << endl;
        cout << "------------------------" << endl;
    }
};

// ==================== PROGRAMA PRINCIPAL ====================
int main()
{
    // CREAR UN ARREGLO CON LOS 5 EMPLEADOS
    EmpleadoEmpresa empleados[5] = {
        EmpleadoEmpresa("Carlos", "Mendoza", 23, "operador"), // Por hora
        EmpleadoEmpresa("Ana", "Gomez", 28, "operador"),      // Por hora
        EmpleadoEmpresa("Luis", "Torres", 31, "operador"),    // Por hora
        EmpleadoEmpresa("Sofia", "Castro", 35, "supervisor"), // De planta
        EmpleadoEmpresa("Javier", "Lopez", 42, "gerente")     // De planta
    };

    // CALCULAR SUELDOS SEGUN EL TIPO DE EMPLEADO
    // Los 3 primeros son por hora (operadores)
    empleados[0].empleadoPorHora();
    empleados[1].empleadoPorHora();
    empleados[2].empleadoPorHora();

    // Los 2 ultimos son de planta (supervisor y gerente)
    empleados[3].empleadoDePlanta();
    empleados[4].empleadoDePlanta();

    // MOSTRAR TODOS LOS EMPLEADOS
    cout << "========== LISTA DE EMPLEADOS ==========" << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        empleados[i].mostrarTodo();
    }

    return 0;
}