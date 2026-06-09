#include <iostream>
#include <string>

using namespace std;

// ==================== CLASE PADRE ====================
class Empleado
{
  protected:
    string nombre;
    string apellido;
    int edad;

  public:
    Empleado(string _nombre, string _apellido, int _edad)
    {
        nombre = _nombre;
        apellido = _apellido;
        edad = _edad;
    }

    // ------------------------------------------------------------
    // METODO VIRTUAL
    // ------------------------------------------------------------
    // La palabra "virtual" permite que las clases hijas puedan
    // SOBREESCRIBIR (cambiar el comportamiento) de este metodo.
    // Sin "virtual", la clase padre no permitiria que la hija
    // modifique este metodo.
    // ------------------------------------------------------------
    virtual void mostrarDatos()
    {
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Edad: " << edad << " años" << endl;
    }
};

// ==================== CLASE HIJA ====================
class EmpleadoEmpresa : public Empleado
{
  private:
    string ocupacion;
    int horas; // Siempre sera 40
    double sueldo;

  public:
    EmpleadoEmpresa(string _nombre, string _apellido, int _edad, string _ocupacion)
        : Empleado(_nombre, _apellido, _edad)
    {
        ocupacion = _ocupacion;
        horas = 40;
        sueldo = 0;
    }

    void empleadoPorHora()
    {
        if (ocupacion == "operador")
        {
            sueldo = horas * 50;
        }
    }

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

    // ------------------------------------------------------------
    // SOBREESCRIBIENDO EL METODO DE LA CLASE PADRE (OVERRIDE)
    // ------------------------------------------------------------
    // La palabra "override" indica que este metodo ESTA REEMPLAZANDO
    // al metodo "mostrarDatos()" de la clase padre.
    //
    // ¿POR QUE ES NECESARIO?
    // Porque la clase padre NO puede acceder a los atributos de la hija
    // (ocupacion, horas, sueldo). Entonces la hija debe "sobrescribir"
    // el metodo para poder mostrar SUS propios datos.
    //
    // ¿QUE SIGNIFICA "override"?
    // Es una palabra que C++ usa para decir: "Oye, este metodo ya existe
    // en la clase padre, pero yo lo voy a cambiar (sobrescribir) para
    // que haga algo diferente".
    // ------------------------------------------------------------
    void mostrarDatos() override
    {
        // Llamamos al metodo de la clase padre para mostrar
        // nombre, apellido y edad (asi no repetimos codigo)
        Empleado::mostrarDatos();

        // Ahora mostramos los datos que SOLO tiene la clase hija
        cout << "Ocupacion: " << ocupacion << endl;
        cout << "Horas laboradas: " << horas << endl;
        cout << "Sueldo: S/. " << sueldo << endl;
        cout << "------------------------" << endl;
    }
};

// ==================== PROGRAMA PRINCIPAL ====================
int main()
{
    // Creamos un arreglo con los 5 empleados
    // 3 operadores (por hora) y 2 de planta (supervisor y gerente)
    EmpleadoEmpresa empleados[5] = {
        EmpleadoEmpresa("Carlos", "Mendoza", 23, "operador"), EmpleadoEmpresa("Ana", "Gomez", 28, "operador"),
        EmpleadoEmpresa("Luis", "Torres", 31, "operador"), EmpleadoEmpresa("Sofia", "Castro", 35, "supervisor"),
        EmpleadoEmpresa("Javier", "Lopez", 42, "gerente")};

    // Calculamos los sueldos segun el tipo de empleado
    empleados[0].empleadoPorHora();
    empleados[1].empleadoPorHora();
    empleados[2].empleadoPorHora();
    empleados[3].empleadoDePlanta();
    empleados[4].empleadoDePlanta();

    // Mostramos todos los empleados
    // NOTA: Aunque SOLO llamamos a "mostrarDatos()", gracias al OVERRIDE
    // se ejecuta la version de la clase hija, NO la de la clase padre.
    cout << "========== LISTA DE EMPLEADOS ==========" << endl << endl;

    for (int i = 0; i < 5; i++)
    {
        empleados[i].mostrarDatos(); // Aqui se usa el metodo con override
    }

    return 0;
}
