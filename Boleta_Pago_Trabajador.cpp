/*
=========================================================
PROGRAMA: SISTEMA DE BOLETA DE PAGO (VERSIÓN FINAL)
AUTOR: Nikolai Coica
CURSO: Estructura de Datos y Algoritmos

LÓGICA DEFINITIVA:
- Hora normal:      S/ 120.00 por hora
- Hora extra:       S/ 130.00 por hora (se paga más)
- Hora faltada:     S/ 130.00 por hora (se descuenta igual que la extra)
- Horas por dia:    FIJO (8 horas)
- Dias trabajados:  FIJO (26 dias)
- Horas regulares:  8h x 26d = 208 horas
=========================================================
*/

#include <iomanip> // Para formatear la salida (setw, setprecision, fixed, left)
#include <iostream>
#include <limits> // Para obtener valores máximos/mínimos de tipos de datos (usado en limpiarBuffer)
#include <string>

using namespace std;

// ===============================
// CONSTANTES DEL SISTEMA (FIJAS)
// ===============================
const double PAGO_POR_HORA_NORMAL = 120.00;       // Pago por hora normal
const double PAGO_POR_HORA_EXTRA = 130.00;        // Pago por hora extra
const double DESCUENTO_POR_HORA_FALTADA = 130.00; // Descuento por hora faltada
const int HORAS_POR_DIA = 8;                      // FIJO - no se modifica
const int DIAS_MES = 26;                          // FIJO - no se modifica

// ===============================
// DESCUENTOS FIJOS
// ===============================
const double DESCUENTO_SEGURO = 120.00;
const double DESCUENTO_AFP = 150.00;

// ===============================
// BENEFICIOS FIJOS
// ===============================
const double BONO_PRODUCTIVIDAD = 500.00;
const double ASIGNACION_FAMILIAR = 1000.00;

// ===============================
// VARIABLES MODIFICABLES
// ===============================
int horasFaltadas = 0; // Horas que faltó el trabajador
int horasExtras = 0;   // Horas extras trabajadas
string trabajador;

// ===============================
// FUNCIÓN PARA LIMPIAR BUFFER
// ===============================
void limpiarBuffer()
{
    cin.clear(); // Resetea las banderas de error de cin
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n'); // Elimina todos los caracteres del buffer hasta el salto de línea
}

// ===============================
// FUNCIÓN PAUSAR - SOLO UN ENTER
// ===============================
void pausar()
{
    cout << "\n┌──────────────────────────────────────────┐\n";
    cout << "│    Presione Enter para continuar...      │\n";
    cout << "└──────────────────────────────────────────┘";
    cin.get();
}

// ===============================
// CABECERA DEL PROGRAMA
// ===============================
void mostrarCabecera()
{
    cout << "\n┌───────────────────────────────────────────────┐\n";
    cout << "│       BIENVENIDO AL SISTEMA NIKSOFT           │\n";
    cout << "│     Soluciones de Software Empresarial        │\n";
    cout << "└───────────────────────────────────────────────┘\n";
}

// ===============================
// MUESTRA EL MENÚ PRINCIPAL
// ===============================
void mostrarMenu()
{
    cout << "\n┌────────────────────────────────────────────────┐\n";
    cout << "│                 MENU PRINCIPAL                 │\n";
    cout << "├────────────────────────────────────────────────┤\n";
    cout << "│  1. Ver configuracion actual                   │\n";
    cout << "│  2. Registrar horas faltadas (inasistencias)   │\n";
    cout << "│  3. Registrar horas extras                     │\n";
    cout << "│  4. Ver calculos completos                     │\n";
    cout << "│  5. IMPRIMIR BOLETA COMPLETA                   │\n";
    cout << "│  6. Salir                                      │\n";
    cout << "└────────────────────────────────────────────────┘\n";
    cout << "Seleccione una opcion: ";
}

// ===============================
// CÁLCULOS CON LÓGICA CORREGIDA
// ===============================

// Total horas REGULARES (8h x 26d = 208h)
int horasRegulares()
{
    return HORAS_POR_DIA * DIAS_MES;
}

// Horas normales EFECTIVAS = horas regulares - horas faltadas
int horasNormalesEfectivas()
{
    return horasRegulares() - horasFaltadas;
}

// Salario por horas normales
double calcularSalarioHorasNormales()
{
    return horasNormalesEfectivas() * PAGO_POR_HORA_NORMAL;
}

// Salario por horas extras
double calcularSalarioHorasExtras()
{
    return horasExtras * PAGO_POR_HORA_EXTRA;
}

// Descuento por horas faltadas
double calcularDescuentoHorasFaltadas()
{
    return horasFaltadas * DESCUENTO_POR_HORA_FALTADA;
}

// Salario bruto total = salario normal + salario extras
double calcularSalarioBruto()
{
    return calcularSalarioHorasNormales() + calcularSalarioHorasExtras();
}

// Total descuentos = seguro + AFP + horas faltadas
double calcularTotalDescuentos()
{
    return DESCUENTO_SEGURO + DESCUENTO_AFP + calcularDescuentoHorasFaltadas();
}

double calcularBeneficios()
{
    return BONO_PRODUCTIVIDAD + ASIGNACION_FAMILIAR;
}

double calcularSueldoNeto()
{
    return calcularSalarioBruto() + calcularBeneficios() - calcularTotalDescuentos();
}

// ===============================
// MOSTRAR CONFIGURACIÓN ACTUAL
// ===============================
void mostrarConfiguracion()
{
    cout << fixed << setprecision(2);
    cout << "\n┌───────────────────────────────────────────────────┐\n";
    cout << "│               CONFIGURACION ACTUAL                │\n";
    cout << "├───────────────────────────────────────────────────┤\n";
    cout << "│ Trabajador:                  " << setw(21) << left << trabajador
         << "│\n"; // setw(21): reserva 21 espacios de ancho para el campo y left: alinea el texto a la izquierda dentro
                   // de esos 21 espacios
    cout << "│ Horas por dia (fijo):        " << setw(21) << HORAS_POR_DIA << "│\n";
    cout << "│ Dias trabajados (fijo):      " << setw(21) << DIAS_MES << "│\n";
    cout << "│ Horas regulares:             " << setw(21) << horasRegulares() << "│\n";
    cout << "│ Pago hora normal:         S/ " << setw(21) << PAGO_POR_HORA_NORMAL << "│\n";
    cout << "│ Pago hora extra:          S/ " << setw(21) << PAGO_POR_HORA_EXTRA << "│\n";
    cout << "│ Descuento hora faltada:   S/ " << setw(21) << DESCUENTO_POR_HORA_FALTADA << "│\n";
    cout << "│ Horas faltadas:              " << setw(21) << horasFaltadas << "│\n";
    cout << "│ Horas extras:                " << setw(21) << horasExtras << "│\n";
    cout << "│ Horas normales efectivas:    " << setw(21) << horasNormalesEfectivas() << "│\n";
    cout << "└───────────────────────────────────────────────────┘\n";
}

// ===============================
// MOSTRAR CÁLCULOS COMPLETOS
// ===============================
void mostrarCalculos()
{
    double salarioNormal = calcularSalarioHorasNormales();
    double salarioExtra = calcularSalarioHorasExtras();
    double salarioBruto = calcularSalarioBruto();
    double descuentoFaltas = calcularDescuentoHorasFaltadas();
    double descuentosFijos = DESCUENTO_SEGURO + DESCUENTO_AFP;
    double totalDescuentos = calcularTotalDescuentos();
    double beneficios = calcularBeneficios();
    double sueldoNeto = calcularSueldoNeto();
    int horasReg = horasRegulares();
    int horasNormalesEfect = horasNormalesEfectivas();

    cout << fixed << setprecision(2);
    cout << "\n┌──────────────────────────────────────────────────┐\n";
    cout << "│                CALCULOS DETALLADOS               │\n";
    cout << "├──────────────────────────────────────────────────┤\n";
    cout << "│                                                  │\n";
    cout << "│ 1. HORAS DEL MES:                                │\n";
    cout << "│    Horas regulares:       " << setw(23) << (to_string(horasReg) + "h") << "│\n";
    cout << "│    Horas faltadas:        " << setw(23) << (to_string(horasFaltadas) + "h") << "│\n";
    cout << "│    Horas normales:        " << setw(23) << (to_string(horasNormalesEfect) + "h") << "│\n";
    cout << "│    Horas extras:          " << setw(23) << (to_string(horasExtras) + "h") << "│\n";
    cout << "│                                                  │\n";
    cout << "│ 2. VALORES POR HORA:                             │\n";
    cout << "│    Hora normal:           S/ " << setw(20) << PAGO_POR_HORA_NORMAL << "│\n";
    cout << "│    Hora extra:            S/ " << setw(20) << PAGO_POR_HORA_EXTRA << "│\n";
    cout << "│    Hora faltada:          S/ " << setw(20) << DESCUENTO_POR_HORA_FALTADA << "│\n";
    cout << "│                                                  │\n";
    cout << "│ 3. SALARIO BRUTO:                                │\n";
    cout << "│    Horas normales:        S/ " << setw(20) << salarioNormal << "│\n";
    cout << "│    Horas extras:          S/ " << setw(20) << salarioExtra << "│\n";
    cout << "│    TOTAL BRUTO:           S/ " << setw(20) << salarioBruto << "│\n";
    cout << "│                                                  │\n";
    cout << "│ 4. DESCUENTOS:                                   │\n";
    cout << "│    Por horas faltadas:    S/ " << setw(20) << descuentoFaltas << "│\n";
    cout << "│    Seguro:                S/ " << setw(20) << DESCUENTO_SEGURO << "│\n";
    cout << "│    AFP:                   S/ " << setw(20) << DESCUENTO_AFP << "│\n";
    cout << "│    TOTAL DESCUENTOS:      S/ " << setw(20) << totalDescuentos << "│\n";
    cout << "│                                                  │\n";
    cout << "│ 5. BENEFICIOS:                                   │\n";
    cout << "│    Bono productividad:    S/ " << setw(20) << BONO_PRODUCTIVIDAD << "│\n";
    cout << "│    Asignacion familiar:   S/ " << setw(20) << ASIGNACION_FAMILIAR << "│\n";
    cout << "│    TOTAL BENEFICIOS:      S/ " << setw(20) << beneficios << "│\n";
    cout << "│                                                  │\n";
    cout << "│ 6. SUELDO NETO:           S/ " << setw(20) << sueldoNeto << "│\n";
    cout << "└──────────────────────────────────────────────────┘\n";
}

// ===============================
// REGISTRAR HORAS FALTADAS
// ===============================
void registrarHorasFaltadas()
{
    cout << "\n┌─────────────────────────────────────────────┐\n";
    cout << "│          REGISTRAR HORAS FALTADAS           │\n";
    cout << "├─────────────────────────────────────────────┤\n";
    cout << "│ Horas faltadas actuales:      " << setw(14) << horasFaltadas << "│\n";
    cout << "│ Descuento por hora:        S/ " << setw(14) << DESCUENTO_POR_HORA_FALTADA << "│\n";
    cout << "└─────────────────────────────────────────────┘\n";
    cout << "Ingrese total de horas faltadas en el mes: ";
    cin >> horasFaltadas;
    limpiarBuffer();

    if (horasFaltadas < 0)
    {
        cout << "\n❌ Valor invalido. Usando 0 horas faltadas." << endl;
        horasFaltadas = 0;
    }
    else if (horasFaltadas > horasRegulares())
    {
        cout << "\n❌ No puede faltar mas de " << horasRegulares() << " horas." << endl;
        cout << "   Usando valor maximo: " << horasRegulares() << endl;
        horasFaltadas = horasRegulares();
    }
    else
    {
        double descuento = horasFaltadas * DESCUENTO_POR_HORA_FALTADA;
        cout << "\n✅ Horas faltadas registradas: " << horasFaltadas << " horas" << endl;
        cout << "   Descuento total por faltas: S/ " << fixed << setprecision(2) << descuento << endl;
    }
}

// ===============================
// REGISTRAR HORAS EXTRAS
// ===============================
void registrarHorasExtras()
{
    cout << "\n┌────────────────────────────────────────────┐\n";
    cout << "│           REGISTRAR HORAS EXTRAS           │\n";
    cout << "├────────────────────────────────────────────┤\n";
    cout << "│ Horas extras actuales:    " << setw(17) << horasExtras << "│\n";
    cout << "│ Pago por hora extra:   S/ " << setw(17) << PAGO_POR_HORA_EXTRA << "│\n";
    cout << "└────────────────────────────────────────────┘\n";
    cout << "Ingrese total de horas extras en el mes: ";
    cin >> horasExtras;
    limpiarBuffer();

    if (horasExtras < 0)
    {
        cout << "\n❌ Valor invalido. Usando 0 horas extras." << endl;
        horasExtras = 0;
    }
    else
    {
        double pago = horasExtras * PAGO_POR_HORA_EXTRA;
        cout << "\n✅ Horas extras registradas: " << horasExtras << " horas" << endl;
        cout << "   Pago por horas extras: S/ " << fixed << setprecision(2) << pago
             << endl; // fixed evita notación científica, setprecision(2) muestra 2 decimales (importante para valores
                      // monetarios)
    }
}

// ===============================
// IMPRIMIR BOLETA COMPLETA
// ===============================
void imprimirBoleta()
{
    double salarioNormal = calcularSalarioHorasNormales();
    double salarioExtra = calcularSalarioHorasExtras();
    double salarioBruto = calcularSalarioBruto();
    double descuentoFaltas = calcularDescuentoHorasFaltadas();
    double totalDescuentos = calcularTotalDescuentos();
    double beneficios = calcularBeneficios();
    double sueldoNeto = calcularSueldoNeto();
    int horasReg = horasRegulares();
    int horasNormalesEfect = horasNormalesEfectivas();

    cout << fixed << setprecision(2);

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                  BOLETA ELECTRONICA DE PAGO                                ║\n";
    cout << "║                             GRUPO CORPORATIVO TINGO MARIA S.A.C.                           ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ DATOS DEL TRABAJADOR                                                                       ║\n";
    cout << "║ ┌────────────────────────────────────────────────────────────────────┐                     ║\n";
    cout << "║ │ Nombre:       " << setw(40) << left << trabajador << "             │                     ║\n";
    cout << "║ │ Periodo:      " << setw(53) << left << "Mensual - Mayo 2026" << "│                     ║\n";
    cout << "║ └────────────────────────────────────────────────────────────────────┘                     ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ DETALLE DE HORAS TRABAJADAS                                                                ║\n";
    cout << "║ ┌───────────────────────────────────────────────────────────────────────┐                  ║\n";
    cout << "║ │ Horas por dia (fijo):                " << setw(33) << HORAS_POR_DIA << "│                  ║\n";
    cout << "║ │ Dias trabajados (fijo):              " << setw(33) << DIAS_MES << "│                  ║\n";
    cout << "║ │ Horas regulares:                     " << setw(33) << horasReg << "│                  ║\n";
    cout << "║ │ Horas faltadas:                      " << setw(33) << horasFaltadas << "│                  ║\n";
    cout << "║ │ Horas normales efectivas:            " << setw(33) << horasNormalesEfect << "│                  ║\n";
    cout << "║ │ Horas extras:                        " << setw(33) << horasExtras << "│                  ║\n";
    cout << "║ │ Pago hora normal:                 S/ " << setw(33) << PAGO_POR_HORA_NORMAL << "│                  ║\n";
    cout << "║ │ Pago hora extra:                  S/ " << setw(33) << PAGO_POR_HORA_EXTRA << "│                  ║\n";
    cout << "║ │ Descuento hora faltada:           S/ " << setw(33) << DESCUENTO_POR_HORA_FALTADA
         << "│                  ║\n";
    cout << "║ └───────────────────────────────────────────────────────────────────────┘                  ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ INGRESOS                                                                                   ║\n";
    cout << "║ ┌──────────────────────────────────────────────────────────────────────────────────────┐   ║\n";
    cout << "║ │ Salario por horas normales:        S/ " << setw(35) << salarioNormal << "            │   ║\n";
    cout << "║ │ Salario por horas extras:          S/ " << setw(34) << salarioExtra << "             │   ║\n";
    cout << "║ │ BENEFICIOS:                                                                          │   ║\n";
    cout << "║ │   Bono productividad:              S/ " << setw(41) << BONO_PRODUCTIVIDAD << "      │   ║\n";
    cout << "║ │   Asignacion familiar:             S/ " << setw(42) << ASIGNACION_FAMILIAR << "     │   ║\n";
    cout << "║ │   Total beneficios:                S/ " << setw(33) << beneficios << "              │   ║\n";
    cout << "║ ├──────────────────────────────────────────────────────────────────────────────────────┤   ║\n";
    cout << "║ │ TOTAL INGRESOS:                    S/ " << setw(46) << (salarioBruto + beneficios) << " │   ║\n";
    cout << "║ └──────────────────────────────────────────────────────────────────────────────────────┘   ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ DESCUENTOS                                                                                 ║\n";
    cout << "║ ┌─────────────────────────────────────────────────────────────────────────────┐            ║\n";
    cout << "║ │ Por horas faltadas:              S/ " << setw(38) << descuentoFaltas << "  │            ║\n";
    cout << "║ │ Seguro:                          S/ " << setw(38) << DESCUENTO_SEGURO << "  │            ║\n";
    cout << "║ │ AFP:                             S/ " << setw(35) << DESCUENTO_AFP << "     │            ║\n";
    cout << "║ │ Total descuentos:                S/ " << setw(32) << totalDescuentos << "        │            ║\n";
    cout << "║ └─────────────────────────────────────────────────────────────────────────────┘            ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║ ┌────────────────────────────────────────────────────────────┐                             ║\n";
    cout << "║ │                   SUELDO NETO A PAGAR                      │                             ║\n";
    cout << "║ │                                                            │                             ║\n";
    cout << "║ │                   S/ " << setw(32) << sueldoNeto << "      │                             ║\n";
    cout << "║ └────────────────────────────────────────────────────────────┘                             ║\n";
    cout << "╠════════════════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << "║                               FIRMA DEL EMPLEADOR                                          ║\n";
    cout << "║                             _________________________                                      ║\n";
    cout << "╚════════════════════════════════════════════════════════════════════════════════════════════╝\n";
}

// ===============================
// PROGRAMA PRINCIPAL
// ===============================
int main()
{
    int opcion;

    mostrarCabecera();

    cout << "\n┌────────────────────────────────────────┐\n";
    cout << "│       INGRESO DE DATOS PERSONALES      │\n";
    cout << "└────────────────────────────────────────┘\n";
    cout << "Ingrese nombre del trabajador: ";
    getline(cin, trabajador);

    cout << "\n┌──────────────────────────────────────────────────────┐\n";
    cout << "│                  VALORES POR DEFECTO                 │\n";
    cout << "├──────────────────────────────────────────────────────┤\n";
    cout << "│ Horas por dia (FIJO):            " << left << setw(20) << HORAS_POR_DIA << "│\n";
    cout << "│ Dias trabajados (FIJO):          " << setw(15) << DIAS_MES << "     │\n";
    cout << "│ Horas regulares (FIJO):          " << setw(20) << horasRegulares() << "│\n";
    cout << "│ Pago por hora NORMAL:         S/ " << setw(20) << PAGO_POR_HORA_NORMAL << "│\n";
    cout << "│ Pago por hora EXTRA:          S/ " << setw(20) << PAGO_POR_HORA_EXTRA << "│\n";
    cout << "│ Descuento por hora FALTADA:   S/ " << setw(20) << DESCUENTO_POR_HORA_FALTADA << "│\n";
    cout << "└──────────────────────────────────────────────────────┘\n";

    // MOSTRAR MENSAJE Y ESPERAR UN SOLO ENTER
    cout << "\n✅ Sistema listo. Puede registrar faltas, extras o generar boleta.\n";
    cout << "\n┌────────────────────────────────────────┐\n";
    cout << "│    Presione Enter para continuar...    │\n";
    cout << "└────────────────────────────────────────┘";
    cin.get();

    do
    {
        mostrarMenu();
        cin >> opcion;
        limpiarBuffer(); // Elimina residuos del buffer (como saltos de línea) para evitar que lecturas posteriores se
                         // salten o fallen

        switch (opcion)
        {
        case 1:
            mostrarConfiguracion();
            pausar(); // Detiene la ejecución hasta que el usuario presione Enter, permitiendo ver los resultados antes
                      // de continuar
            break;

        case 2:
            registrarHorasFaltadas();
            pausar();
            break;

        case 3:
            registrarHorasExtras();
            pausar();
            break;

        case 4:
            mostrarCalculos();
            pausar();
            break;

        case 5:
            imprimirBoleta();
            cout << "\n✅ BOLETA GENERADA EXITOSAMENTE\n";
            pausar();
            break;

        case 6:
            cout << "\n┌──────────────────────────────────────────┐\n";
            cout << "│    GRACIAS POR UTILIZAR EL SISTEMA       │\n";
            cout << "│           © NikSoft - 2026               │\n";
            cout << "└──────────────────────────────────────────┘\n";
            break;

        default:
            cout << "\n❌ Opcion invalida. Intente nuevamente.\n";
            pausar();
        }

    } while (opcion != 6); // Repite el menú hasta que el usuario seleccione la opción 6 (Salir)

    return 0;
}