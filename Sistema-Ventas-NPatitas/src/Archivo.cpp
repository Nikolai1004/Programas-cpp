#include "Archivo.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief Localiza la raíz del proyecto automáticamente
 *
 * Tema: Gestión de recursos del sistema (Unidad 1)
 * Busca la carpeta data/ o src/ desde la ubicación actual
 */
namespace {
filesystem::path localizarRaizProyecto() {
    filesystem::path actual = filesystem::current_path();
    if (filesystem::exists(actual / "src") || filesystem::exists(actual / "data"))
        return actual;
    if (actual.filename() == "bin" && filesystem::exists(actual.parent_path() / "data"))
        return actual.parent_path();
    return actual;
}
}  // namespace

// ========== CONSTRUCTOR ==========

Archivo::Archivo() {
    auto raiz = localizarRaizProyecto();
    directorioDatos = raiz / "data";

    // ========== CARPETA PRINCIPAL DE DATOS ==========
    directorioDatabase = directorioDatos / "database";

    // ========== CARPETAS DE BASE DE DATOS ==========
    directorioProductos = directorioDatabase / "productos";
    directorioVentas = directorioDatabase / "ventas";

    // ========== CARPETAS DE REPORTES ==========
    directorioReportes = directorioDatos / "reportes";
    directorioReporteVentas = directorioReportes / "ventas";
    directorioReporteInventario = directorioReportes / "inventario";
    directorioReporteStockBajo = directorioReportes / "stock_bajo";
    directorioReporteHistorial = directorioReportes / "historial";

    archivoProductos = directorioProductos / "productos.txt";
    archivoVentas = directorioVentas / "ventas.txt";

    // ========== CREAR TODAS LAS CARPETAS ==========
    error_code error;
    filesystem::create_directories(directorioDatabase, error);
    filesystem::create_directories(directorioProductos, error);
    filesystem::create_directories(directorioVentas, error);
    filesystem::create_directories(directorioReportes, error);
    filesystem::create_directories(directorioReporteVentas, error);
    filesystem::create_directories(directorioReporteInventario, error);
    filesystem::create_directories(directorioReporteStockBajo, error);
    filesystem::create_directories(directorioReporteHistorial, error);

    // ========== CREAR ARCHIVOS SI NO EXISTEN ==========
    if (!filesystem::exists(archivoProductos))
        ofstream(archivoProductos);
    if (!filesystem::exists(archivoVentas))
        ofstream(archivoVentas);
}

// ========== MÉTODOS PARA RUTAS DE REPORTES ==========

/**
 * Obtiene la ruta completa para un reporte de ventas
 */
string Archivo::getRutaReporteVentas(const string& nombreArchivo) const {
    return (directorioReporteVentas / nombreArchivo).string();
}

/**
 * Obtiene la ruta completa para un reporte de inventario
 */
string Archivo::getRutaReporteInventario(const string& nombreArchivo) const {
    return (directorioReporteInventario / nombreArchivo).string();
}

/**
 * Obtiene la ruta completa para un reporte de stock bajo
 */
string Archivo::getRutaReporteStockBajo(const string& nombreArchivo) const {
    return (directorioReporteStockBajo / nombreArchivo).string();
}

/**
 * Obtiene la ruta completa para un reporte historial de ventas
 */
string Archivo::getRutaReporteHistorial(const string& nombreArchivo) const {
    return (directorioReporteHistorial / nombreArchivo).string();
}

// ========== OPERACIONES CON PRODUCTOS ==========

/**
 * Carga productos desde el archivo
 * Complejidad: O(n) - Recorre todas las líneas
 */
vector<Producto> Archivo::cargarProductos() const {
    vector<Producto> productos;
    ifstream entrada(archivoProductos);
    string linea;
    while (getline(entrada, linea)) {
        if (linea.empty())
            continue;
        Producto producto;
        if (Producto::deserializar(linea, producto)) {
            productos.push_back(producto);
        }
    }
    return productos;
}

/**
 * Guarda productos con backup automático
 * Complejidad: O(n) - Recorre todos los productos
 */
bool Archivo::guardarProductos(const vector<Producto>& productos) const {
    // Crear backup antes de sobrescribir (seguridad)
    if (filesystem::exists(archivoProductos)) {
        try {
            filesystem::copy_file(archivoProductos, directorioProductos / "productos.txt.bak",
                                  filesystem::copy_options::overwrite_existing);
        } catch (...) {
        }
    }

    // Guardar productos
    ofstream salida(archivoProductos, ios::trunc);
    if (!salida.is_open())
        return false;
    salida << fixed << setprecision(2);
    for (const auto& p : productos) {
        salida << p.serializar() << '\n';
    }
    return true;
}

// ========== OPERACIONES CON VENTAS ==========

/**
 * Guarda una venta en formato:
 * VENTA|ID|FECHA|HORA|TOTAL
 * DETALLE|COD|NOMBRE|CANT|PRECIO|SUBTOTAL
 * FIN_VENTA
 */
bool Archivo::guardarVenta(const Venta& venta) const {
    // ========== BACKUP DE VENTAS ==========
    // Se crea una copia de seguridad antes de guardar cada venta
    if (filesystem::exists(archivoVentas)) {
        try {
            filesystem::copy_file(archivoVentas, directorioVentas / "ventas.txt.bak",
                                  filesystem::copy_options::overwrite_existing);
        } catch (...) {
        }
    }

    ofstream salida(archivoVentas, ios::app);
    if (!salida.is_open())
        return false;

    salida << fixed << setprecision(2);
    salida << "VENTA|" << venta.getId() << '|' << venta.getFecha() << '|' << venta.getHora() << '|'
           << venta.calcularTotal() << '\n';

    for (const auto& d : venta.getDetalles()) {
        salida << "DETALLE|" << d.getCodigoProducto() << '|' << d.getNombreProducto() << '|'
               << d.getCantidad() << '|' << d.getPrecioUnitario() << '|' << d.calcularSubtotal()
               << '\n';
    }
    salida << "FIN_VENTA\n";
    return true;
}

/**
 * Carga resumen de ventas (solo cabeceras)
 * Complejidad: O(n) - Recorre todas las líneas
 */
vector<ResumenVenta> Archivo::cargarResumenVentas() const {
    vector<ResumenVenta> ventas;
    ifstream entrada(archivoVentas);
    string linea;
    while (getline(entrada, linea)) {
        if (linea.rfind("VENTA|", 0) != 0)
            continue;
        stringstream ss(linea);
        string tipo, id, fecha, hora, totalTexto;
        if (getline(ss, tipo, '|') && getline(ss, id, '|') && getline(ss, fecha, '|') &&
            getline(ss, hora, '|') && getline(ss, totalTexto)) {
            try {
                ventas.push_back({id, fecha, hora, stod(totalTexto)});
            } catch (...) {
            }
        }
    }
    return ventas;
}

/**
 * Genera ID secuencial sin duplicados
 * Lee el último ID del archivo para evitar duplicados al eliminar registros
 * Complejidad: O(n) - Lee todas las ventas para encontrar el último ID
 */
string Archivo::generarSiguienteIdVenta() const {
    auto ventas = cargarResumenVentas();
    if (ventas.empty())
        return "V000001";
    int maxNum = 0;
    for (const auto& v : ventas) {
        try {
            int num = stoi(v.id.substr(1));
            if (num > maxNum)
                maxNum = num;
        } catch (...) {
        }
    }
    ostringstream id;
    id << 'V' << setw(6) << setfill('0') << (maxNum + 1);
    return id.str();
}