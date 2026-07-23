#ifndef MENU_H
#define MENU_H

#include <string>
#include <unordered_map>
#include <vector>

#include "Archivo.h"
#include "Producto.h"

using namespace std;

/**
 * @brief Clase Menu - Controla la interfaz de usuario del sistema
 *
 * Tema: Estructuras de control (Unidad 2)
 * Tema: Tablas de Dispersión para búsqueda O(1) (Unidad 3)
 *
 * Responsabilidades:
 * - Interactuar con el usuario mediante consola
 * - Orquestar las operaciones del sistema
 * - Mantener tabla hash para búsqueda rápida de productos
 * - Control de acceso con roles (Administrador/Vendedor)
 */
class Menu {
   private:
    // Constantes
    static constexpr const char* NOMBRE_EMPRESA = "N' PATITAS";

    // Atributos
    Archivo archivo;                                ///< Manejador de persistencia
    vector<Producto> productos;                     ///< Inventario en memoria
    unordered_map<string, size_t> indiceProductos;  ///< Tabla hash: código → índice
    bool esAdmin;                                   ///< true = administrador, false = vendedor

    // ========== MÉTODOS PRIVADOS ==========

    // Menú y navegación
    void mostrarPantallaInicio() const;
    void mostrarEncabezado() const;
    void mostrarMenuPrincipal() const;

    // Operaciones del sistema
    void registrarProducto();
    void registrarVenta();
    void consultarVentasDelDia() const;
    void consultarVentasPorFecha() const;
    void verVentas() const;

    // Reportes en archivos TXT
    void generarReportes();
    void generarReporteVentasDia();
    void generarReporteInventario();
    void generarReporteStockBajo();
    void generarReporteHistorialVentas();
    string obtenerFechaHoraParaArchivo();

    // Gestión de productos
    void gestionarProductos();
    void editarProducto();
    void eliminarProducto();

    /**
     * @brief Genera un código de producto automáticamente
     *
     * Toma la primera letra de la familia (en mayúscula) y genera
     * un número correlativo de 5 dígitos.
     *
     * Ejemplo: Sustrato → S00001, S00002, ...
     *          Vigantol ADE → V00001, V00002, ...
     */
    string generarCodigoProducto(const string& familia);

    /**
     * @brief Permite seleccionar un producto buscando por familia
     *
     * @param productoSeleccionado Referencia donde se almacenará el producto elegido
     * @return true si se seleccionó un producto, false si no
     */
    bool seleccionarProductoPorFamilia(Producto& productoSeleccionado);

    /**
     * @brief Actualiza la tabla hash de índices
     * Debe llamarse después de cualquier modificación en el vector productos
     * @complexity O(n) - Recorre todos los productos
     */
    void actualizarIndices();

    /**
     * @brief Busca un producto por código (usa tabla hash)
     * @param codigo Código del producto a buscar
     * @return Índice en el vector, -1 si no existe
     * @complexity O(1) promedio
     */
    int buscarIndiceProducto(const string& codigo) const;

    // ========== MÉTODOS DE VALIDACIÓN Y SEGURIDAD ==========

    static string leerTextoNoVacio(const string& mensaje);
    static string leerTextoOpcional(const string& mensaje);
    static int leerEntero(const string& mensaje, int minimo, int maximo);
    static int leerEnteroOpcional(const string& mensaje);
    static double leerDouble(const string& mensaje, double minimo);
    static double leerDoubleOpcional(const string& mensaje);
    static char leerSiNo(const string& mensaje);
    static string normalizarCodigo(string codigo);
    static string fechaActual();
    static string horaActual();
    static void pausar();

    /**
     * @brief Lee una clave ocultando caracteres con asteriscos (seguridad)
     *
     * @param mensaje Mensaje a mostrar al usuario
     * @return Clave ingresada por el usuario
     */
    static string leerClaveConAsteriscos(const string& mensaje);

   public:
    /** Constructor - Carga productos, selecciona rol y construye la tabla hash */
    Menu();

    /** Inicia el bucle principal del sistema */
    void iniciar();
};

#endif