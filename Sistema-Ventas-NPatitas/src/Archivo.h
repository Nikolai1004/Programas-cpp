#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <filesystem>
#include <string>
#include <vector>

#include "Producto.h"
#include "Venta.h"

using namespace std;

/**
 * @brief Estructura ResumenVenta - DTO para reportes ligeros
 *
 * Tema: Estructuras de datos (Unidad 2)
 * Propósito: Cargar solo los datos necesarios para reportes
 */
struct ResumenVenta {
    string id;
    string fecha;
    string hora;
    double total;
};

/**
 * @brief Clase Archivo - Gestiona la persistencia de datos
 *
 * Tema: Persistencia y Serialización (Unidad 3)
 * Responsabilidades:
 * - Leer/escribir productos desde/hacia productos.txt
 * - Leer/escribir ventas desde/hacia ventas.txt
 * - Backup automático antes de sobrescribir
 * - Generación de IDs secuenciales sin duplicados
 * - Organización de reportes en carpetas específicas
 *
 * ESTRUCTURA DE CARPETAS:
 * data/
 *   database/
 *     productos/
 *       productos.txt
 *       productos.txt.bak
 *     ventas/
 *       ventas.txt
 *       ventas.txt.bak
 *   reportes/
 *     ventas/
 *       Reporte_Ventas_*.txt
 *     inventario/
 *       Reporte_Inventario_*.txt
 *     stock_bajo/
 *       Reporte_Stock_Bajo_*.txt
 *     historial/
 *       Historial_Ventas_*.txt
 */
class Archivo {
   private:
    filesystem::path directorioDatos;
    filesystem::path directorioDatabase;  // Carpeta principal de datos
    filesystem::path directorioProductos;
    filesystem::path directorioVentas;
    filesystem::path directorioReportes;

    // Subcarpetas de reportes
    filesystem::path directorioReporteVentas;
    filesystem::path directorioReporteInventario;
    filesystem::path directorioReporteStockBajo;
    filesystem::path directorioReporteHistorial;

    filesystem::path archivoProductos;
    filesystem::path archivoVentas;

   public:
    Archivo();

    // ========== OPERACIONES CON PRODUCTOS ==========
    vector<Producto> cargarProductos() const;
    bool guardarProductos(const vector<Producto>& productos) const;

    // ========== OPERACIONES CON VENTAS ==========
    bool guardarVenta(const Venta& venta) const;
    vector<ResumenVenta> cargarResumenVentas() const;
    string generarSiguienteIdVenta() const;

    // ========== MÉTODOS PARA RUTAS DE REPORTES ==========
    string getRutaReporteVentas(const string& nombreArchivo) const;
    string getRutaReporteInventario(const string& nombreArchivo) const;
    string getRutaReporteStockBajo(const string& nombreArchivo) const;
    string getRutaReporteHistorial(const string& nombreArchivo) const;
};

#endif