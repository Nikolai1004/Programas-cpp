#include "Menu.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include "Venta.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// ============================================================
// CONSTRUCTOR - CON SELECCIÓN DE ROL Y SEGURIDAD
// ============================================================

Menu::Menu() : productos(archivo.cargarProductos()), esAdmin(false) {
    mostrarPantallaInicio();

    // ========== SELECCIÓN DE ROL ==========
    int opcionRol = 0;
    do {
        cout << "\n--- SELECCIONE SU ROL ---\n";
        cout << "1. Administrador\n";
        cout << "2. Vendedor\n";
        cout << "------------------------\n";
        opcionRol = leerEntero("Seleccione una opcion: ", 1, 2);
    } while (opcionRol != 1 && opcionRol != 2);

    if (opcionRol == 1) {
        // ========== 3 INTENTOS PARA LA CLAVE ==========
        int intentos = 3;
        bool claveCorrecta = false;
        while (intentos > 0 && !claveCorrecta) {
            string clave = leerClaveConAsteriscos("Ingrese la clave de administrador: ");
            if (clave == "Niko100") {
                claveCorrecta = true;
                esAdmin = true;
                cout << "\n✅ Acceso de administrador concedido.\n";
            } else {
                intentos--;
                if (intentos > 0) {
                    cout << "\n❌ Clave incorrecta. Intentos restantes: " << intentos << "\n";
                }
            }
        }

        if (!claveCorrecta) {
            cout << "\n❌ Ha superado el numero maximo de intentos.\n";
            cout << "El sistema se cerrara.\n";
            exit(0);
        }
    } else {
        cout << "\n✅ Acceso como vendedor.\n";
    }

    pausar();
    actualizarIndices();
}

// ============================================================
// PANTALLA DE INICIO
// ============================================================

void Menu::mostrarPantallaInicio() const {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &tiempo);
#else
    localtime_r(&tiempo, &local);
#endif
    ostringstream fecha, hora;
    fecha << put_time(&local, "%Y-%m-%d");
    hora << put_time(&local, "%H:%M:%S");

    cout << "\n";
    cout << "================================================================================\n";
    cout << "            🐾  SISTEMA DE GESTIÓN DE VENTAS - N' PATITAS  🐾\n";
    cout << "                         FARMACIA VETERINARIA\n";
    cout << "================================================================================\n";
    cout << "\n";
    cout << "    🐶  🐱  🐮  🐷  🐑  🐔  🐴  🐰  🐟  🐝  🐾  🦜\n";
    cout << "\n";
    cout << "    \"Comprometidos con cada pata, cada vida, cada historia.\"\n";
    cout << "\n";
    cout << "    📅 Fecha: " << fecha.str() << "                    ⏰ Hora: " << hora.str()
         << "\n";
    cout << "    💻 Versión: 1.0                         🏥 N' Patitas\n";
    cout << "\n";
    cout << "================================================================================\n";
    cout << "    Presione ENTER para acceder al sistema...\n";
    cout << "================================================================================\n";
    cout << "\n";
    cin.get();
}

// ============================================================
// MENÚ PRINCIPAL
// ============================================================

void Menu::mostrarEncabezado() const {
    cout << "\n============================================================\n";
    cout << "             SISTEMA DE VENTAS - " << NOMBRE_EMPRESA << "\n";
    cout << "============================================================\n";
}

void Menu::mostrarMenuPrincipal() const {
    mostrarEncabezado();
    if (esAdmin) {
        cout << "1. Registrar producto\n";
        cout << "2. Registrar venta\n";
        cout << "3. Ver ventas\n";
        cout << "4. Generar reportes en archivos\n";
        cout << "5. Gestionar productos (editar/eliminar)\n";
        cout << "6. Salir\n";
    } else {
        cout << "1. Registrar venta\n";
        cout << "2. Ver ventas del dia\n";
        cout << "3. Salir\n";
    }
    cout << "------------------------------------------------------------\n";
}

void Menu::iniciar() {
    int opcion = 0;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        mostrarMenuPrincipal();
        if (esAdmin) {
            opcion = leerEntero("Seleccione una opcion: ", 1, 6);
            switch (opcion) {
                case 1:
                    registrarProducto();
                    break;
                case 2:
                    registrarVenta();
                    break;
                case 3:
                    verVentas();
                    break;
                case 4:
                    generarReportes();
                    break;
                case 5:
                    gestionarProductos();
                    break;
                case 6:
                    cout << "\nSistema finalizado correctamente.\n";
                    break;
            }
        } else {
            opcion = leerEntero("Seleccione una opcion: ", 1, 3);
            switch (opcion) {
                case 1:
                    registrarVenta();
                    break;
                case 2:
                    consultarVentasDelDia();
                    break;
                case 3:
                    cout << "\nSistema finalizado correctamente.\n";
                    break;
            }
        }
    } while (opcion != (esAdmin ? 6 : 3));
}

// ============================================================
// LEER CLAVE CON ASTERISCOS (SEGURIDAD - TIEMPO REAL)
// ============================================================

string Menu::leerClaveConAsteriscos(const string& mensaje) {
    string clave;
    char ch;
    cout << mensaje;
    cout.flush();

#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modo;
    GetConsoleMode(hStdin, &modo);
    SetConsoleMode(hStdin, modo & ~ENABLE_ECHO_INPUT);
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

    while (true) {
        ch = cin.get();
        if (ch == '\n' || ch == '\r') {
            break;
        } else if (ch == '\b' || ch == 127) {
            if (!clave.empty()) {
                clave.pop_back();
                cout << "\b \b";
                cout.flush();
            }
        } else if (ch >= 32 && ch <= 126) {
            clave.push_back(ch);
            cout << '*';
            cout.flush();
        }
    }
    cout << '\n';

#ifdef _WIN32
    SetConsoleMode(hStdin, modo);
#else
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return clave;
}

// ============================================================
// GENERAR CÓDIGO DE PRODUCTO
// ============================================================

string Menu::generarCodigoProducto(const string& familia) {
    char letra = toupper(familia[0]);
    int contador = 0;
    for (const auto& p : productos) {
        if (!p.getCodigo().empty() && p.getCodigo()[0] == letra) {
            contador++;
        }
    }
    ostringstream codigo;
    codigo << letra << setw(5) << setfill('0') << (contador + 1);
    return codigo.str();
}

// ============================================================
// REGISTRAR PRODUCTO
// ============================================================

void Menu::registrarProducto() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    cout << "REGISTRO DE PRODUCTO\n";
    cout << "------------------------------------------------------------\n";
    cout << "EJEMPLOS:\n";
    cout << "  Familia: Sustrato | Concepto: Premium bolsa x 1kg\n";
    cout << "  Familia: Vigantol ADE | Concepto: Fco x 25ml\n";
    cout << "------------------------------------------------------------\n";

    string familia = leerTextoNoVacio("Familia: ");
    string concepto = leerTextoNoVacio("Concepto: ");
    double precio = leerDouble("Precio (S/): ", 0.01);
    int stock = leerEntero("Stock inicial: ", 0, 1000000);

    string codigo = generarCodigoProducto(familia);

    cout << "\n--- Resumen del producto ---\n";
    cout << "Codigo   : " << codigo << " (generado automaticamente)\n";
    cout << "Familia  : " << familia << '\n';
    cout << "Concepto : " << concepto << '\n';
    cout << "Precio   : S/ " << fixed << setprecision(2) << precio << '\n';
    cout << "Stock    : " << stock << '\n';
    cout << "----------------------------\n";

    productos.emplace_back(codigo, familia, concepto, precio, stock);

    if (!archivo.guardarProductos(productos)) {
        productos.pop_back();
        cout << "\nError: no se pudo guardar el producto.\n";
    } else {
        actualizarIndices();
        cout << "\nProducto registrado correctamente.\n";
    }
    pausar();
}

// ============================================================
// SELECCIONAR PRODUCTO POR FAMILIA (PARA VENTAS)
// ============================================================

bool Menu::seleccionarProductoPorFamilia(Producto& productoSeleccionado) {
    string busqueda = leerTextoNoVacio("Ingrese parte de la familia del producto: ");

    string busquedaLower = busqueda;
    transform(busquedaLower.begin(), busquedaLower.end(), busquedaLower.begin(), ::tolower);

    vector<Producto> resultados;
    for (const auto& p : productos) {
        string fam = p.getFamilia();
        transform(fam.begin(), fam.end(), fam.begin(), ::tolower);
        if (fam.find(busquedaLower) != string::npos) {
            resultados.push_back(p);
        }
    }

    if (resultados.empty()) {
        cout << "\nNo se encontraron productos con '" << busqueda << "'.\n";
        return false;
    }

    cout << "\n--- Productos encontrados ---\n";
    cout << left << setw(8) << "CODIGO" << setw(35) << "FAMILIA" << setw(30) << "CONCEPTO" << right
         << setw(10) << "PRECIO" << setw(10) << "STOCK" << '\n';
    cout << "--------------------------------------------------------------------------------------"
            "--\n";
    cout << fixed << setprecision(2);

    for (const auto& p : resultados) {
        string fam = p.getFamilia();
        string con = p.getConcepto();
        if (fam.size() > 34)
            fam = fam.substr(0, 34);
        if (con.size() > 29)
            con = con.substr(0, 29);
        cout << left << setw(8) << p.getCodigo() << setw(35) << fam << setw(30) << con << right
             << setw(10) << p.getPrecio() << setw(10) << p.getStock() << '\n';
    }
    cout << "--------------------------------------------------------------------------------------"
            "--\n";

    string codigo =
        normalizarCodigo(leerTextoNoVacio("\nIngrese el codigo del producto a vender: "));

    auto it = indiceProductos.find(codigo);
    if (it == indiceProductos.end()) {
        cout << "Producto no encontrado.\n";
        return false;
    }

    productoSeleccionado = productos[it->second];
    return true;
}

// ============================================================
// REGISTRAR VENTA
// ============================================================

void Menu::registrarVenta() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    cout << "REGISTRO DE VENTA\n";
    cout << "------------------------------------------------------------\n";
    cout << "Busque el producto por familia y luego seleccione el concepto.\n";
    cout << "------------------------------------------------------------\n";

    if (productos.empty()) {
        cout << "Debe registrar productos antes de realizar una venta.\n";
        pausar();
        return;
    }

    Venta venta(archivo.generarSiguienteIdVenta(), fechaActual(), horaActual());
    vector<Producto> productosActualizados = productos;

    char continuar = 'S';
    while (continuar == 'S') {
        Producto producto;
        if (!seleccionarProductoPorFamilia(producto)) {
            continuar = leerSiNo("Desea intentar de nuevo? (S/N): ");
            continue;
        }

        int indice = -1;
        for (size_t i = 0; i < productosActualizados.size(); ++i) {
            if (productosActualizados[i].getCodigo() == producto.getCodigo()) {
                indice = i;
                break;
            }
        }

        if (indice == -1) {
            cout << "Error: Producto no encontrado en el inventario.\n";
            continuar = leerSiNo("Desea intentar de nuevo? (S/N): ");
            continue;
        }

        Producto& p = productosActualizados[indice];
        cout << fixed << setprecision(2);
        cout << "\nProducto: " << p.getNombreCompleto() << '\n';
        cout << "Precio  : S/ " << p.getPrecio() << '\n';
        cout << "Stock   : " << p.getStock() << '\n';

        if (p.getStock() <= 0) {
            cout << "El producto no tiene stock disponible.\n";
            continuar = leerSiNo("Desea agregar otro producto? (S/N): ");
            continue;
        }

        int cantidad = leerEntero("Cantidad: ", 1, p.getStock());
        p.descontarStock(cantidad);
        venta.agregarDetalle(
            DetalleVenta(p.getCodigo(), p.getNombreCompleto(), cantidad, p.getPrecio()));

        cout << "Subtotal agregado: S/ " << cantidad * p.getPrecio() << '\n';
        continuar = leerSiNo("Desea agregar otro producto? (S/N): ");
    }

    if (venta.getDetalles().empty()) {
        cout << "\nLa venta fue cancelada porque no se agregaron productos.\n";
        pausar();
        return;
    }

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    cout << "║                    NOTA DE VENTA INTERNA                        ║\n";
    cout << "║                    " << NOMBRE_EMPRESA << "\n";
    cout << "╠══════════════════════════════════════════════════════════════════╣\n";
    cout << venta.generarComprobante(NOMBRE_EMPRESA);
    cout << "╚══════════════════════════════════════════════════════════════════╝\n";

    char confirmar = leerSiNo("\nConfirmar y guardar la venta? (S/N): ");

    if (confirmar == 'N') {
        cout << "\nVenta cancelada. No se modifico el stock.\n";
        pausar();
        return;
    }

    if (!archivo.guardarVenta(venta)) {
        cout << "\nError: No se pudo guardar la venta.\n";
        cout << "La venta ha sido cancelada. El stock NO se ha modificado.\n";
        pausar();
        return;
    }

    if (!archivo.guardarProductos(productosActualizados)) {
        cout << "\n¡ERROR CRÍTICO! El stock se descontó pero no se guardó.\n";
        cout << "Advertencia: Debes revisar manualmente los archivos.\n";

        string backupPath = "data/database/productos/productos.txt.bak";
        if (filesystem::exists(backupPath)) {
            try {
                filesystem::copy_file(backupPath, "data/database/productos/productos.txt",
                                      filesystem::copy_options::overwrite_existing);
                cout << "Se restauró el stock desde el backup.\n";
            } catch (...) {
                cout << "No se pudo restaurar el backup. Revisa manualmente.\n";
            }
        }
        pausar();
        return;
    }

    productos = move(productosActualizados);
    actualizarIndices();
    cout << "\n✅ Venta registrada correctamente con codigo " << venta.getId() << ".\n";
    cout << "📄 Nota de Venta Interna generada correctamente.\n";
    pausar();
}

// ============================================================
// CONSULTAR VENTAS DEL DÍA
// ============================================================

void Menu::consultarVentasDelDia() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    string hoy = fechaActual();
    cout << "REPORTE DE VENTAS DEL " << hoy << '\n';
    cout << "------------------------------------------------------------\n";

    auto ventas = archivo.cargarResumenVentas();
    int cantidad = 0;
    double total = 0.0;

    cout << left << setw(12) << "VENTA" << setw(12) << "HORA" << right << setw(14) << "TOTAL (S/)"
         << '\n';
    cout << "--------------------------------------\n";
    cout << fixed << setprecision(2);

    for (const auto& v : ventas) {
        if (v.fecha == hoy) {
            cout << left << setw(12) << v.id << setw(12) << v.hora << right << setw(14) << v.total
                 << '\n';
            ++cantidad;
            total += v.total;
        }
    }

    if (cantidad == 0) {
        cout << "No se registraron ventas en la fecha actual.\n";
    }

    cout << "--------------------------------------\n";
    cout << "Cantidad de ventas: " << cantidad << '\n';
    cout << "Total vendido      : S/ " << total << '\n';
    pausar();
}

// ============================================================
// CONSULTAR VENTAS POR FECHA
// ============================================================

void Menu::consultarVentasPorFecha() const {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    cout << "CONSULTAR VENTAS POR FECHA\n";
    cout << "------------------------------------------------------------\n";
    cout << "Formato de fecha: AAAA-MM-DD (ej: 2026-07-22)\n";
    cout << "------------------------------------------------------------\n";

    string fechaInicio = leerTextoNoVacio("Fecha de inicio: ");
    string fechaFin = leerTextoNoVacio("Fecha de termino: ");

    auto ventas = archivo.cargarResumenVentas();
    int cantidad = 0;
    double total = 0.0;

    cout << "\n--- VENTAS DEL " << fechaInicio << " AL " << fechaFin << " ---\n";
    cout << left << setw(12) << "VENTA" << setw(12) << "FECHA" << setw(12) << "HORA" << right
         << setw(14) << "TOTAL (S/)" << '\n';
    cout << "----------------------------------------------------------------\n";
    cout << fixed << setprecision(2);

    for (const auto& v : ventas) {
        if (v.fecha >= fechaInicio && v.fecha <= fechaFin) {
            cout << left << setw(12) << v.id << setw(12) << v.fecha << setw(12) << v.hora << right
                 << setw(14) << v.total << '\n';
            ++cantidad;
            total += v.total;
        }
    }

    if (cantidad == 0) {
        cout << "No se encontraron ventas en el rango de fechas.\n";
    }

    cout << "----------------------------------------------------------------\n";
    cout << "Cantidad de ventas: " << cantidad << '\n';
    cout << "Total vendido      : S/ " << total << '\n';
    pausar();
}

// ============================================================
// VER VENTAS (SUBMENÚ)
// ============================================================

void Menu::verVentas() const {
    int opcion = 0;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        mostrarEncabezado();
        cout << "VER VENTAS\n";
        cout << "------------------------------------------------------------\n";
        cout << "1. Ventas del dia\n";
        cout << "2. Ventas por rango de fechas\n";
        cout << "3. Volver al menu principal\n";
        cout << "------------------------------------------------------------\n";

        opcion = leerEntero("Seleccione una opcion: ", 1, 3);
        switch (opcion) {
            case 1:
                consultarVentasDelDia();
                break;
            case 2:
                consultarVentasPorFecha();
                break;
            case 3:
                return;
        }
    } while (opcion != 3);
}

// ============================================================
// GESTIONAR PRODUCTOS (SUBMENÚ)
// ============================================================

void Menu::gestionarProductos() {
    int opcion = 0;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        mostrarEncabezado();
        cout << "GESTION DE PRODUCTOS\n";
        cout << "------------------------------------------------------------\n";
        cout << "1. Editar producto\n";
        cout << "2. Eliminar producto\n";
        cout << "3. Volver al menu principal\n";
        cout << "------------------------------------------------------------\n";

        opcion = leerEntero("Seleccione una opcion: ", 1, 3);
        switch (opcion) {
            case 1:
                editarProducto();
                break;
            case 2:
                eliminarProducto();
                break;
            case 3:
                return;
        }
    } while (opcion != 3);
}

// ============================================================
// EDITAR PRODUCTO
// ============================================================

void Menu::editarProducto() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    cout << "EDITAR PRODUCTO\n";
    cout << "------------------------------------------------------------\n";

    string codigo = normalizarCodigo(leerTextoNoVacio("Ingrese el codigo del producto a editar: "));

    int indice = buscarIndiceProducto(codigo);
    if (indice == -1) {
        cout << "\nProducto no encontrado.\n";
        pausar();
        return;
    }

    Producto& p = productos[indice];
    cout << "\n--- Datos actuales del producto ---\n";
    cout << "Codigo   : " << p.getCodigo() << '\n';
    cout << "Familia  : " << p.getFamilia() << '\n';
    cout << "Concepto : " << p.getConcepto() << '\n';
    cout << "Precio   : S/ " << fixed << setprecision(2) << p.getPrecio() << '\n';
    cout << "Stock    : " << p.getStock() << '\n';
    cout << "--------------------------------------\n";

    cout << "\nDeje en blanco para no modificar.\n";
    string nuevaFamilia = leerTextoOpcional("Nueva familia: ");
    string nuevoConcepto = leerTextoOpcional("Nuevo concepto: ");
    double nuevoPrecio = leerDoubleOpcional("Nuevo precio (S/): ");
    int nuevoStock = leerEnteroOpcional("Nuevo stock: ");

    if (!nuevaFamilia.empty())
        p.setFamilia(nuevaFamilia);
    if (!nuevoConcepto.empty())
        p.setConcepto(nuevoConcepto);
    if (nuevoPrecio >= 0)
        p.setPrecio(nuevoPrecio);
    if (nuevoStock >= 0)
        p.setStock(nuevoStock);

    if (!archivo.guardarProductos(productos)) {
        cout << "\nError: no se pudo guardar los cambios.\n";
    } else {
        actualizarIndices();
        cout << "\nProducto actualizado correctamente.\n";
    }
    pausar();
}

// ============================================================
// ELIMINAR PRODUCTO
// ============================================================

void Menu::eliminarProducto() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    mostrarEncabezado();
    cout << "ELIMINAR PRODUCTO\n";
    cout << "------------------------------------------------------------\n";

    string codigo =
        normalizarCodigo(leerTextoNoVacio("Ingrese el codigo del producto a eliminar: "));

    int indice = buscarIndiceProducto(codigo);
    if (indice == -1) {
        cout << "\nProducto no encontrado.\n";
        pausar();
        return;
    }

    const Producto& p = productos[indice];
    cout << "\n--- Producto a eliminar ---\n";
    cout << "Codigo   : " << p.getCodigo() << '\n';
    cout << "Familia  : " << p.getFamilia() << '\n';
    cout << "Concepto : " << p.getConcepto() << '\n';
    cout << "Precio   : S/ " << fixed << setprecision(2) << p.getPrecio() << '\n';
    cout << "Stock    : " << p.getStock() << '\n';
    cout << "----------------------------\n";

    char confirmar = leerSiNo("\n¿Esta seguro de eliminar este producto? (S/N): ");

    if (confirmar == 'N') {
        cout << "\nEliminacion cancelada.\n";
        pausar();
        return;
    }

    productos.erase(productos.begin() + indice);

    if (!archivo.guardarProductos(productos)) {
        cout << "\nError: no se pudo eliminar el producto.\n";
    } else {
        actualizarIndices();
        cout << "\nProducto eliminado correctamente.\n";
    }
    pausar();
}

// ============================================================
// REPORTES EN ARCHIVOS .TXT CON ORGANIZACIÓN POR CARPETAS
// ============================================================

void Menu::generarReportes() {
    int opcion = 0;
    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        mostrarEncabezado();
        cout << "GENERADOR DE REPORTES\n";
        cout << "------------------------------------------------------------\n";
        cout << "1. Reporte de ventas del dia\n";
        cout << "2. Reporte de inventario completo\n";
        cout << "3. Reporte de productos con stock bajo (< 5 unidades)\n";
        cout << "4. Reporte historial de ventas\n";
        cout << "5. Volver al menu principal\n";
        cout << "------------------------------------------------------------\n";

        opcion = leerEntero("Seleccione una opcion: ", 1, 5);
        switch (opcion) {
            case 1:
                generarReporteVentasDia();
                break;
            case 2:
                generarReporteInventario();
                break;
            case 3:
                generarReporteStockBajo();
                break;
            case 4:
                generarReporteHistorialVentas();
                break;
            case 5:
                return;
        }
    } while (opcion != 5);
}

// ============================================================
// REPORTE DE VENTAS DEL DÍA
// ============================================================

void Menu::generarReporteVentasDia() {
    string hoy = fechaActual();
    string nombreArchivo = "Reporte_Ventas_" + hoy + ".txt";
    string rutaCompleta = archivo.getRutaReporteVentas(nombreArchivo);
    auto ventas = archivo.cargarResumenVentas();

    ofstream archivoReporte(rutaCompleta);
    if (!archivoReporte.is_open()) {
        cout << "\nError: No se pudo crear el archivo.\n";
        return;
    }

    archivoReporte << "============================================================\n";
    archivoReporte << "             REPORTE DE VENTAS DEL " << hoy << "\n";
    archivoReporte << "============================================================\n";
    archivoReporte << "VENTA\t\tHORA\t\tTOTAL (S/)\n";
    archivoReporte << "--------------------------------------\n";
    archivoReporte << fixed << setprecision(2);

    int cantidad = 0;
    double total = 0.0;
    for (const auto& v : ventas) {
        if (v.fecha == hoy) {
            archivoReporte << v.id << "\t\t" << v.hora << "\t\t" << v.total << '\n';
            ++cantidad;
            total += v.total;
        }
    }

    if (cantidad == 0)
        archivoReporte << "No se registraron ventas en la fecha actual.\n";
    archivoReporte << "--------------------------------------\n";
    archivoReporte << "Cantidad de ventas: " << cantidad << '\n';
    archivoReporte << "Total vendido      : S/ " << total << '\n';
    archivoReporte << "============================================================\n";
    archivoReporte << "Documento generado por Sistema de Ventas N' PATITAS\n";
    archivoReporte << "============================================================\n";
    archivoReporte.close();

    cout << "\nReporte generado correctamente en: " << rutaCompleta << "\n";
    pausar();
}

// ============================================================
// REPORTE DE INVENTARIO - COLUMNAS ALINEADAS
// ============================================================

void Menu::generarReporteInventario() {
    string nombreArchivo = "Reporte_Inventario_" + obtenerFechaHoraParaArchivo() + ".txt";
    string rutaCompleta = archivo.getRutaReporteInventario(nombreArchivo);
    ofstream archivoReporte(rutaCompleta);
    if (!archivoReporte.is_open()) {
        cout << "\nError: No se pudo crear el archivo.\n";
        return;
    }

    archivoReporte << "============================================================\n";
    archivoReporte << "             REPORTE DE INVENTARIO\n";
    archivoReporte << "============================================================\n";
    archivoReporte << "Fecha: " << fechaActual() << "  Hora: " << horaActual() << "\n";
    archivoReporte << "------------------------------------------------------------\n";

    archivoReporte << left << setw(10) << "CODIGO" << setw(35) << "FAMILIA" << setw(40)
                   << "CONCEPTO" << right << setw(10) << "PRECIO" << setw(10) << "STOCK" << '\n';
    archivoReporte << "----------------------------------------------------------------------------"
                      "------------\n";
    archivoReporte << fixed << setprecision(2);

    for (const auto& p : productos) {
        string fam = p.getFamilia();
        string con = p.getConcepto();
        if (fam.size() > 34)
            fam = fam.substr(0, 34);
        if (con.size() > 39)
            con = con.substr(0, 39);

        archivoReporte << left << setw(10) << p.getCodigo() << setw(35) << fam << setw(40) << con
                       << right << setw(10) << p.getPrecio() << setw(10) << p.getStock() << '\n';
    }

    archivoReporte << "----------------------------------------------------------------------------"
                      "------------\n";
    archivoReporte << "Total de productos: " << productos.size() << '\n';
    archivoReporte << "============================================================\n";
    archivoReporte.close();

    cout << "\nReporte generado correctamente en: " << rutaCompleta << "\n";
    pausar();
}

// ============================================================
// REPORTE DE STOCK BAJO
// ============================================================

void Menu::generarReporteStockBajo() {
    string nombreArchivo = "Reporte_Stock_Bajo_" + obtenerFechaHoraParaArchivo() + ".txt";
    string rutaCompleta = archivo.getRutaReporteStockBajo(nombreArchivo);
    ofstream archivoReporte(rutaCompleta);
    if (!archivoReporte.is_open()) {
        cout << "\nError: No se pudo crear el archivo.\n";
        return;
    }

    archivoReporte << "============================================================\n";
    archivoReporte << "       PRODUCTOS CON STOCK BAJO (< 5 unidades)\n";
    archivoReporte << "============================================================\n";
    archivoReporte << "Fecha: " << fechaActual() << "  Hora: " << horaActual() << "\n";
    archivoReporte << "------------------------------------------------------------\n";

    bool hay = false;
    for (const auto& p : productos) {
        if (p.getStock() < 5) {
            hay = true;
            archivoReporte << "Codigo  : " << p.getCodigo() << "\n";
            archivoReporte << "Familia : " << p.getFamilia() << "\n";
            archivoReporte << "Concepto: " << p.getConcepto() << "\n";
            archivoReporte << "Stock   : " << p.getStock() << " unidades\n";
            archivoReporte << "------------------------------------------------------------\n";
        }
    }

    if (!hay)
        archivoReporte << "No hay productos con stock "
                          "bajo.\n------------------------------------------------------------\n";
    archivoReporte << "============================================================\n";
    archivoReporte.close();

    cout << "\nReporte generado correctamente en: " << rutaCompleta << "\n";
    pausar();
}

// ============================================================
// REPORTE DE HISTORIAL DE VENTAS POR RANGO DE FECHAS
// ============================================================

void Menu::generarReporteHistorialVentas() {
    cout << "------------------------------------------------------------\n";
    cout << "Formato de fecha: AAAA-MM-DD (ej: 2026-07-20)\n";
    cout << "------------------------------------------------------------\n";

    string fechaInicio = leerTextoNoVacio("Fecha de inicio: ");
    string fechaFin = leerTextoNoVacio("Fecha de fin: ");

    if (fechaInicio.empty() || fechaFin.empty()) {
        cout << "\nError: Las fechas no pueden estar vacias.\n";
        pausar();
        return;
    }

    string nombreArchivo = "Reporte_Ventas_" + fechaInicio + "_a_" + fechaFin + ".txt";
    string rutaCompleta = archivo.getRutaReporteHistorial(nombreArchivo);
    auto ventas = archivo.cargarResumenVentas();

    ofstream archivoReporte(rutaCompleta);
    if (!archivoReporte.is_open()) {
        cout << "\nError: No se pudo crear el archivo.\n";
        return;
    }

    archivoReporte << "============================================================\n";
    archivoReporte << "       REPORTE DE VENTAS DEL " << fechaInicio << " AL " << fechaFin << "\n";
    archivoReporte << "============================================================\n";
    archivoReporte << "Fecha de generacion: " << fechaActual() << "  Hora: " << horaActual()
                   << "\n";
    archivoReporte << "------------------------------------------------------------\n";
    archivoReporte << "VENTA\t\tFECHA\t\tHORA\t\tTOTAL (S/)\n";
    archivoReporte << "------------------------------------------------------------\n";
    archivoReporte << fixed << setprecision(2);

    int cantidad = 0;
    double totalGeneral = 0.0;

    for (const auto& v : ventas) {
        if (v.fecha >= fechaInicio && v.fecha <= fechaFin) {
            archivoReporte << v.id << "\t\t" << v.fecha << "\t" << v.hora << "\t\t" << v.total
                           << '\n';
            ++cantidad;
            totalGeneral += v.total;
        }
    }

    if (cantidad == 0) {
        archivoReporte << "No se encontraron ventas en el rango de fechas.\n";
    }

    archivoReporte << "------------------------------------------------------------\n";
    archivoReporte << "Cantidad de ventas: " << cantidad << "\n";
    archivoReporte << "Total vendido      : S/ " << totalGeneral << "\n";
    archivoReporte << "============================================================\n";
    archivoReporte << "Documento generado por Sistema de Ventas N' PATITAS\n";
    archivoReporte << "============================================================\n";
    archivoReporte.close();

    cout << "\nReporte generado correctamente en: " << rutaCompleta << "\n";
    pausar();
}

// ============================================================
// OBTENER FECHA Y HORA PARA NOMBRE DE ARCHIVO
// ============================================================

string Menu::obtenerFechaHoraParaArchivo() {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &tiempo);
#else
    localtime_r(&tiempo, &local);
#endif
    ostringstream salida;
    salida << put_time(&local, "%Y-%m-%d_%H-%M-%S");
    return salida.str();
}

// ============================================================
// MÉTODOS DE TABLA HASH
// ============================================================

int Menu::buscarIndiceProducto(const string& codigo) const {
    auto it = indiceProductos.find(codigo);
    if (it != indiceProductos.end())
        return static_cast<int>(it->second);
    return -1;
}

void Menu::actualizarIndices() {
    indiceProductos.clear();
    for (size_t i = 0; i < productos.size(); ++i) {
        indiceProductos[productos[i].getCodigo()] = i;
    }
}

// ============================================================
// MÉTODOS DE VALIDACIÓN Y UTILIDAD
// ============================================================

string Menu::leerTextoNoVacio(const string& mensaje) {
    while (true) {
        cout << mensaje;
        string texto;
        getline(cin, texto);
        auto inicio = texto.find_first_not_of(" \t\r\n");
        auto fin = texto.find_last_not_of(" \t\r\n");
        if (inicio != string::npos) {
            return texto.substr(inicio, fin - inicio + 1);
        }
        cout << "Entrada invalida. El campo no puede estar vacio.\n";
    }
}

string Menu::leerTextoOpcional(const string& mensaje) {
    cout << mensaje;
    string texto;
    getline(cin, texto);
    auto inicio = texto.find_first_not_of(" \t\r\n");
    auto fin = texto.find_last_not_of(" \t\r\n");
    if (inicio != string::npos) {
        return texto.substr(inicio, fin - inicio + 1);
    }
    return "";
}

int Menu::leerEntero(const string& mensaje, int minimo, int maximo) {
    while (true) {
        cout << mensaje;
        int valor;
        if (cin >> valor && valor >= minimo && valor <= maximo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada invalida. Ingrese un entero entre " << minimo << " y " << maximo << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int Menu::leerEnteroOpcional(const string& mensaje) {
    cout << mensaje;
    string entrada;
    getline(cin, entrada);
    if (entrada.empty())
        return -1;
    try {
        return stoi(entrada);
    } catch (...) {
        return -1;
    }
}

double Menu::leerDouble(const string& mensaje, double minimo) {
    while (true) {
        cout << mensaje;
        double valor;
        if (cin >> valor && valor >= minimo) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
        cout << "Entrada invalida. Ingrese un numero mayor o igual que " << minimo << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double Menu::leerDoubleOpcional(const string& mensaje) {
    cout << mensaje;
    string entrada;
    getline(cin, entrada);
    if (entrada.empty())
        return -1;
    try {
        return stod(entrada);
    } catch (...) {
        return -1;
    }
}

char Menu::leerSiNo(const string& mensaje) {
    while (true) {
        cout << mensaje;
        char respuesta;
        cin >> respuesta;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        respuesta = static_cast<char>(toupper(static_cast<unsigned char>(respuesta)));
        if (respuesta == 'S' || respuesta == 'N')
            return respuesta;
        cout << "Respuesta invalida. Ingrese S o N.\n";
    }
}

string Menu::normalizarCodigo(string codigo) {
    codigo.erase(
        remove_if(codigo.begin(), codigo.end(), [](unsigned char c) { return isspace(c) != 0; }),
        codigo.end());
    transform(codigo.begin(), codigo.end(), codigo.begin(),
              [](unsigned char c) { return static_cast<char>(toupper(c)); });
    return codigo;
}

string Menu::fechaActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &tiempo);
#else
    localtime_r(&tiempo, &local);
#endif
    ostringstream salida;
    salida << put_time(&local, "%Y-%m-%d");
    return salida.str();
}

string Menu::horaActual() {
    auto ahora = chrono::system_clock::now();
    time_t tiempo = chrono::system_clock::to_time_t(ahora);
    tm local{};
#ifdef _WIN32
    localtime_s(&local, &tiempo);
#else
    localtime_r(&tiempo, &local);
#endif
    ostringstream salida;
    salida << put_time(&local, "%H:%M:%S");
    return salida.str();
}

void Menu::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}