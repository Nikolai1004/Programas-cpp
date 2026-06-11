/*
====================================================================
PROGRAMA: Gestion de Empleados - Empresa
AUTOR: Nikolai Jose Coica Iturri
FECHA: 11/06/2026
====================================================================
*/

#include <cstdlib>  // Para system() - limpiar pantalla
#include <ctime>    // Para time() - obtener fecha/hora
#include <fstream>  // Para ifstream (leer archivos) y ofstream (escribir archivos)
#include <iostream> // Para cout (salida) y cin (entrada)
#include <sstream>  // Para stringstream - convertir datos a string
#include <string>   // Para usar string (texto)
using namespace std;

// ==================== CLASE PADRE ====================
class Empleado
{
  protected: // "protected" = solo las clases HIJAS pueden acceder directamente
             // Una función NORMAL NO puede acceder (por eso necesitamos GET/SET)
    string nombre;
    string apellido;
    int edad;
    int añosEnEmpresa;

  public: // "public" = todos pueden acceder (GET y SET son públicos)
    // CONSTRUCTOR: se ejecuta automáticamente al crear un objeto
    Empleado(string _nombre = "", string _apellido = "", int _edad = 0, int _añosEnEmpresa = 0)
    {
        nombre = _nombre;
        apellido = _apellido;
        edad = _edad;
        añosEnEmpresa = _añosEnEmpresa;
    }

    // ========== METODOS GET ==========
    // "get" = obtener - devuelve el valor de un atributo
    string getNombre()
    {
        return nombre;
    } // Devuelve el nombre
    string getApellido()
    {
        return apellido;
    } // Devuelve el apellido
    int getEdad()
    {
        return edad;
    } // Devuelve la edad
    int getAñosEnEmpresa()
    {
        return añosEnEmpresa;
    } // Devuelve los años

    // ========== METODOS SET ==========
    // "set" = establecer - modifica el valor de un atributo
    void setNombre(string _nombre)
    {
        nombre = _nombre;
    } // Cambia el nombre
    void setApellido(string _apellido)
    {
        apellido = _apellido;
    } // Cambia el apellido
    void setEdad(int _edad)
    {
        edad = _edad;
    } // Cambia la edad
    void setAñosEnEmpresa(int _años)
    {
        añosEnEmpresa = _años;
    } // Cambia los años

    // "virtual" = palabra clave que PERMITE que las clases HIJAS SOBRESCRIBAN este método
    // Sin "virtual", la clase hija NO podría modificar este método
    virtual void mostrarDatos()
    {
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Edad: " << edad << " años" << endl;
        cout << "Tiempo en empresa: " << añosEnEmpresa << " años" << endl;
    }

    // "virtual" + "= 0" = MÉTODO VIRTUAL PURO
    // "= 0" significa que NO tiene implementación aquí
    // OBLIGA a la clase HIJA a implementar estos métodos (como un contrato)
    virtual double getSalario() = 0;              // La hija DEBE tener este método
    virtual int getHoras() = 0;                   // La hija DEBE tener este método
    virtual string getCargo() = 0;                // La hija DEBE tener este método
    virtual void calcularSalario() = 0;           // La hija DEBE tener este método
    virtual void setCargo(string _cargo) = 0;     // La hija DEBE tener este método
    virtual void setHoras(int _horas) = 0;        // La hija DEBE tener este método
    virtual void setSalario(double _salario) = 0; // La hija DEBE tener este método
};

// ==================== CLASE HIJA ====================
// ": public Empleado" = HERENCIA (EmpleadoEmpresa HEREDA de Empleado)
class EmpleadoEmpresa : public Empleado
{
  private:          // "private" = SOLO esta clase puede acceder (ni las funciones externas pueden)
    string cargo;   // operador, supervisor o gerente
    int horas;      // horas trabajadas
    double salario; // salario del empleado

  public:
    // CONSTRUCTOR VACIO (necesario para crear arreglos como: EmpleadoEmpresa empleados[10])
    // ": Empleado(...)" = llama al constructor de la clase PADRE primero
    EmpleadoEmpresa() : Empleado("", "", 0, 0)
    {
        cargo = "";
        horas = 0;
        salario = 0;
    }

    // CONSTRUCTOR COMPLETO
    EmpleadoEmpresa(string _nombre, string _apellido, int _edad, int _añosEnEmpresa, string _cargo, int _horas)
        : Empleado(_nombre, _apellido, _edad, _añosEnEmpresa) // Primero llama al constructor del padre
    {
        cargo = _cargo;
        horas = _horas;
        salario = 0;
    }

    // "override" = palabra clave que indica que este método REEMPLAZA a un método "virtual" del padre
    // Es como decir: "Oye compilador, este método ya existe en el padre, pero yo lo voy a cambiar"
    string getCargo() override
    {
        return cargo;
    } // Obtiene el cargo
    int getHoras() override
    {
        return horas;
    } // Obtiene las horas
    double getSalario() override
    {
        return salario;
    } // Obtiene el salario

    // "override" = este método reemplaza al método virtual del padre
    void setCargo(string _cargo) override
    {
        cargo = _cargo;
    } // Cambia el cargo
    void setHoras(int _horas) override
    {
        horas = _horas;
    } // Cambia las horas
    void setSalario(double _salario) override
    {
        salario = _salario;
    } // Cambia el salario

    // "override" = este método reemplaza al método virtual puro del padre
    void calcularSalario() override
    {
        if (cargo == "operador")
            salario = horas * 50; // 50 soles por hora (salario semanal)
        else if (cargo == "supervisor")
            salario = horas * 80; // 80 soles por hora (salario semanal)
        else if (cargo == "gerente")
            salario = horas * 100; // 100 soles por hora (salario semanal)
        else
            salario = 0;
    }

    // "override" = este método reemplaza al método virtual del padre
    void mostrarDatos() override
    {
        // "::" = operador de resolución de ámbito
        // Significa: "llama al método mostrarDatos() de la clase PADRE (Empleado)"
        Empleado::mostrarDatos();

        // Luego muestra los datos específicos de la clase HIJA
        cout << "Cargo: " << cargo << endl;
        cout << "Horas trabajadas a la semana: " << horas << endl;
        cout << "Salario semanal: S/. " << salario << endl;
        cout << "------------------------" << endl;
    }
};

// ==================== VARIABLES GLOBALES ====================
EmpleadoEmpresa empleados[10]; // Arreglo para 10 empleados
int cantidad = 0;              // Cuántos empleados se cargaron

// ==================== FUNCIONES ====================
// Las funciones evitan repetir código y organizan el programa

// LIMPIAR PANTALLA
void limpiarPantalla()
{
#ifdef _WIN32      // "Si está definido Windows"
    system("cls"); // Limpia pantalla en Windows
#else              // Sino (Linux/Mac/WSL)
    system("clear"); // Limpia pantalla en Linux/Mac/WSL
#endif
}

// PAUSAR - Espera que el usuario presione Enter
void pausar()
{
    cout << "\nPresiona Enter para continuar...";
    cin.clear();             // "clear()" = limpia el estado de error del cin
    cin.ignore(10000, '\n'); // "ignore()" = descarta la entrada incorrecta
    cin.get();               // "get()" = espera que el usuario presione Enter
}

// LEER OPCIÓN VALIDADA - Evita que el programa se bloquee con letras
int leerOpcion()
{
    int valor;
    cin >> valor; // Intenta leer un número

    if (cin.fail()) // "fail()" = detecta si NO es un número
    {
        cin.clear();             // Limpia el error
        cin.ignore(10000, '\n'); // Descarta la entrada incorrecta
        return -1;               // Retorna -1 para indicar error
    }
    return valor; // Retorna el número válido
}

// OBTENER FECHA Y HORA ACTUAL
string obtenerFechaHora()
{
    time_t ahora = time(nullptr);               // "time_t" = tipo para almacenar tiempo
    struct tm *tiempoLocal = localtime(&ahora); // "struct tm" = estructura de fecha/hora

    stringstream ss;                           // "stringstream" = convierte datos a string
    ss << (tiempoLocal->tm_year + 1900) << "-" // Año (tm_year = años desde 1900)
       << (tiempoLocal->tm_mon + 1) << "-"     // Mes (tm_mon = 0-11, por eso +1)
       << tiempoLocal->tm_mday << "_"          // Día
       << tiempoLocal->tm_hour << "-"          // Hora
       << tiempoLocal->tm_min << "-"           // Minuto
       << tiempoLocal->tm_sec;                 // Segundo
    return ss.str();                           // "str()" = convierte stringstream a string
}

// LEER EMPLEADOS DESDE ARCHIVO
// Esta función NO es una clase hija, por eso USA SET (no puede acceder directamente)
bool leerEmpleadosDesdeArchivo(string nombreArchivo)
{
    ifstream archivo(nombreArchivo); // "ifstream" = Input File Stream (para LEER archivos)

    if (!archivo.is_open()) // "is_open()" = verifica si se pudo abrir
    {
        cout << "\n❌ ERROR: No se pudo abrir '" << nombreArchivo << "'" << endl;
        return false;
    }

    int contador = 0;
    string nombre, apellido, cargo;
    int edad, años, horas;

    while (archivo >> nombre >> apellido >> edad >> años >> cargo >> horas && contador < 10)
    {
        // USAMOS SET porque esta función NO es una clase hija
        empleados[contador].setNombre(nombre);
        empleados[contador].setApellido(apellido);
        empleados[contador].setEdad(edad);
        empleados[contador].setAñosEnEmpresa(años);
        empleados[contador].setCargo(cargo);
        empleados[contador].setHoras(horas);
        empleados[contador].setSalario(0);
        contador++;
    }

    archivo.close(); // "close()" = cierra el archivo
    archivo.close();

    if (contador == 0)
    {
        cout << "\n❌ ERROR: Archivo vacío" << endl;
        return false;
    }

    cout << "\n📖 Se leyeron " << contador << " empleados" << endl;
    cantidad = contador;
    return true;
}

// CALCULAR SALARIOS DE TODOS
void calcularSalarios()
{
    for (int i = 0; i < cantidad; i++)
    {
        empleados[i].calcularSalario(); // Cada empleado calcula su propio salario
    }
}

// MOSTRAR TODOS LOS EMPLEADOS
void mostrarTodosLosEmpleados()
{
    cout << "\n========== LISTA COMPLETA DE EMPLEADOS ==========\n" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        empleados[i].mostrarDatos();
    }
}

// MOSTRAR EMPLEADO CON MAYOR SALARIO (usa GET)
void mostrarEmpleadoMayorSalario()
{
    if (cantidad == 0)
        return;

    int indiceMayor = 0;
    for (int i = 1; i < cantidad; i++)
    {
        if (empleados[i].getSalario() > empleados[indiceMayor].getSalario())
        {
            indiceMayor = i;
        }
    }

    cout << "\n========== EMPLEADO CON MAYOR SALARIO SEMANAL ==========\n" << endl;
    empleados[indiceMayor].mostrarDatos();
}

// MOSTRAR EMPLEADOS CON MAYOR TIEMPO (usa GET)
void mostrarEmpleadosMayorTiempo()
{
    if (cantidad == 0)
        return;

    int mayorTiempo = empleados[0].getAñosEnEmpresa();
    for (int i = 1; i < cantidad; i++)
    {
        if (empleados[i].getAñosEnEmpresa() > mayorTiempo)
        {
            mayorTiempo = empleados[i].getAñosEnEmpresa();
        }
    }

    cout << "\n========== EMPLEADOS CON MAYOR TIEMPO EN LA EMPRESA ==========" << endl;
    cout << "(Tiempo maximo: " << mayorTiempo << " años)\n" << endl;

    for (int i = 0; i < cantidad; i++)
    {
        if (empleados[i].getAñosEnEmpresa() == mayorTiempo)
        {
            empleados[i].mostrarDatos();
        }
    }
}

// ORDENAR Y MOSTRAR POR CARGO (Gerente > Supervisor > Operador)
void ordenarYMostrarPorCargo()
{
    // Algoritmo de ordenamiento BURBUJA
    for (int i = 0; i < cantidad - 1; i++)
    {
        for (int j = 0; j < cantidad - i - 1; j++)
        {
            // Operador ternario: (condición) ? (si verdadero) : (si falso)
            int prioridad1 = (empleados[j].getCargo() == "gerente")      ? 3
                             : (empleados[j].getCargo() == "supervisor") ? 2
                                                                         : 1;
            int prioridad2 = (empleados[j + 1].getCargo() == "gerente")      ? 3
                             : (empleados[j + 1].getCargo() == "supervisor") ? 2
                                                                             : 1;

            if (prioridad1 < prioridad2)
            {
                EmpleadoEmpresa temp = empleados[j];
                empleados[j] = empleados[j + 1];
                empleados[j + 1] = temp;
            }
        }
    }

    cout << "\n========== EMPLEADOS ORDENADOS POR CARGO ==========" << endl;
    cout << "(Orden: Gerente > Supervisor > Operador)\n" << endl;

    for (int i = 0; i < cantidad; i++)
    {
        cout << empleados[i].getCargo() << ": " << empleados[i].getNombre() << " " << empleados[i].getApellido()
             << " - S/. " << empleados[i].getSalario() << " semanales" << endl;
    }
    cout << "\n✅ Arreglo ordenado permanentemente." << endl;
}

// GENERAR REPORTE COMPLETO (con fecha y hora en el nombre)
void generarReporteCompleto()
{
    string fechaHora = obtenerFechaHora();
    string nombreArchivo = "Reporte_Empleados_" + fechaHora + ".txt";

    ofstream archivo(nombreArchivo); // "ofstream" = Output File Stream (para ESCRIBIR archivos)

    if (!archivo.is_open())
    {
        cout << "❌ Error: No se pudo crear el archivo" << endl;
        return;
    }

    // ===== ESCRIBIR REPORTE =====
    archivo << "============================================================" << endl;
    archivo << "              REPORTE COMPLETO DE EMPLEADOS" << endl;
    archivo << "============================================================" << endl;
    archivo << "Fecha y hora: " << fechaHora << endl;
    archivo << "Total de empleados: " << cantidad << endl << endl;

    // 1. Lista completa (usa GET)
    archivo << "========== 1. LISTA COMPLETA ==========" << endl << endl;
    for (int i = 0; i < cantidad; i++)
    {
        archivo << "Empleado #" << i + 1 << endl;
        archivo << "  Nombre: " << empleados[i].getNombre() << " " << empleados[i].getApellido() << endl;
        archivo << "  Edad: " << empleados[i].getEdad() << " años" << endl;
        archivo << "  Tiempo: " << empleados[i].getAñosEnEmpresa() << " años" << endl;
        archivo << "  Cargo: " << empleados[i].getCargo() << endl;
        archivo << "  Horas: " << empleados[i].getHoras() << endl;
        archivo << "  Salario semanal: S/. " << empleados[i].getSalario() << endl;
        archivo << "  ----------------------------------------" << endl;
    }

    // 2. Mayor salario (usa GET)
    int idxMayor = 0;
    for (int i = 1; i < cantidad; i++)
        if (empleados[i].getSalario() > empleados[idxMayor].getSalario())
            idxMayor = i;

    archivo << endl << "========== 2. EMPLEADO CON MAYOR SALARIO ==========" << endl << endl;
    archivo << "  Nombre: " << empleados[idxMayor].getNombre() << " " << empleados[idxMayor].getApellido() << endl;
    archivo << "  Salario semanal: S/. " << empleados[idxMayor].getSalario() << endl;

    // 3. Mayor tiempo (usa GET)
    int mayorTiempo = empleados[0].getAñosEnEmpresa();
    for (int i = 1; i < cantidad; i++)
        if (empleados[i].getAñosEnEmpresa() > mayorTiempo)
            mayorTiempo = empleados[i].getAñosEnEmpresa();

    archivo << endl << "========== 3. EMPLEADO CON MAYOR TIEMPO ==========" << endl;
    archivo << "(Tiempo laborando: " << mayorTiempo << " años)" << endl << endl;
    for (int i = 0; i < cantidad; i++)
        if (empleados[i].getAñosEnEmpresa() == mayorTiempo)
            archivo << "  " << empleados[i].getNombre() << " " << empleados[i].getApellido() << " - "
                    << empleados[i].getCargo() << endl;

    // 4. Ordenados por cargo (copia temporal)
    EmpleadoEmpresa temp[10];
    for (int i = 0; i < cantidad; i++)
        temp[i] = empleados[i];
    for (int i = 0; i < cantidad - 1; i++)
        for (int j = 0; j < cantidad - i - 1; j++)
        {
            int p1 = (temp[j].getCargo() == "gerente") ? 3 : (temp[j].getCargo() == "supervisor") ? 2 : 1;
            int p2 = (temp[j + 1].getCargo() == "gerente") ? 3 : (temp[j + 1].getCargo() == "supervisor") ? 2 : 1;
            if (p1 < p2)
            {
                EmpleadoEmpresa aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }

    archivo << endl << "========== 4. ORDENADOS POR CARGO ==========" << endl;
    archivo << "(Gerente > Supervisor > Operador)" << endl << endl;
    for (int i = 0; i < cantidad; i++)
        archivo << "  " << temp[i].getCargo() << ": " << temp[i].getNombre() << " " << temp[i].getApellido()
                << " - S/. " << temp[i].getSalario() << " semanales" << endl;

    archivo << endl << "============================================================" << endl;
    archivo << "              FIN DEL REPORTE" << endl;
    archivo << "============================================================" << endl;
    archivo.close(); // Cierra el archivo

    cout << "\n✅ REPORTE guardado: '" << nombreArchivo << "'" << endl;
}

// MOSTRAR MENÚ
void mostrarMenu()
{
    cout << "\n========================================" << endl;
    cout << "        MENU DE OPCIONES" << endl;
    cout << "========================================" << endl;
    cout << "  1. Mostrar todos los empleados" << endl;
    cout << "  2. Mostrar empleado con mayor salario" << endl;
    cout << "  3. Mostrar empleados con mayor tiempo" << endl;
    cout << "  4. Ordenar y mostrar por cargo" << endl;
    cout << "  5. Guardar reporte completo (nuevo archivo)" << endl;
    cout << "  6. Salir" << endl;
    cout << "========================================" << endl;
    cout << "  Elija una opcion (1-6): ";
}

// ==================== PROGRAMA PRINCIPAL ====================
int main()
{
    int opcion;
    bool salir = false; // "bool" = tipo booleano (true o false)

    cout << "========================================" << endl;
    cout << "     GESTION DE EMPLEADOS - EMPRESA" << endl;
    cout << "========================================" << endl;

    // Intentar leer el archivo
    if (!leerEmpleadosDesdeArchivo("Empleados.txt"))
    {
        cout << "\n⚠️ Crea el archivo 'Empleados.txt' con el formato:" << endl;
        cout << "   nombre apellido edad años cargo horas" << endl;
        return 1; // "return 1" = el programa termina con error
    }

    calcularSalarios();
    cout << "\n✅ Salarios semanales calculados." << endl;

    while (!salir) // Mientras "salir" sea false, el bucle se repite
    {
        mostrarMenu();
        opcion = leerOpcion();

        if (opcion == -1) // Si el usuario ingresó una letra
        {
            cout << "❌ Opcion invalida. Elija 1-6." << endl;
            pausar();
            limpiarPantalla();
            continue; // "continue" = vuelve al inicio del bucle
        }

        switch (opcion) // "switch" = evalúa la opción
        {
        case 1:
            limpiarPantalla();
            mostrarTodosLosEmpleados();
            pausar();
            limpiarPantalla();
            break; // "break" = sale del switch
        case 2:
            limpiarPantalla();
            mostrarEmpleadoMayorSalario();
            pausar();
            limpiarPantalla();
            break;
        case 3:
            limpiarPantalla();
            mostrarEmpleadosMayorTiempo();
            pausar();
            limpiarPantalla();
            break;
        case 4:
            limpiarPantalla();
            ordenarYMostrarPorCargo();
            pausar();
            limpiarPantalla();
            break;
        case 5:
            limpiarPantalla();
            cout << "\n========== GENERANDO REPORTE ==========" << endl;
            generarReporteCompleto();
            pausar();
            limpiarPantalla();
            break;
        case 6:
            limpiarPantalla();
            cout << "========================================" << endl;
            cout << "     ¡GRACIAS POR USAR EL PROGRAMA!" << endl;
            cout << "========================================" << endl;
            salir = true; // Cambia a true para terminar el bucle
            break;
        default: // "default" = si ninguna opción coincide
            limpiarPantalla();
            cout << "❌ Opcion invalida. Elija 1-6." << endl;
            pausar();
            limpiarPantalla();
            break;
        }
    }
    return 0; // "return 0" = el programa termina correctamente
}