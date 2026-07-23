#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Clase DetalleVenta - Representa una línea de venta
 *
 * Tema: Estructuras de datos anidadas (Unidad 2)
 * Relación: Un DetalleVenta pertenece a una Venta (composición)
 */
class DetalleVenta {
   private:
    string codigoProducto;  // Código del producto vendido
    string nombreProducto;  // Nombre completo (se copia para historial)
    int cantidad;           // Cantidad vendida
    double precioUnitario;  // Precio al momento de la venta

   public:
    DetalleVenta(string codigoProducto, string nombreProducto, int cantidad, double precioUnitario);

    // Getters
    const string& getCodigoProducto() const;
    const string& getNombreProducto() const;
    int getCantidad() const;
    double getPrecioUnitario() const;

    // Calcula el subtotal: cantidad × precio unitario
    double calcularSubtotal() const;
};

/**
 * @brief Clase Venta - Representa una transacción completa
 *
 * Tema: Estructuras de datos compuestas (Unidad 2)
 * Relación: Contiene múltiples DetalleVenta (composición)
 */
class Venta {
   private:
    string id;                      // Identificador único (V000001)
    string fecha;                   // Fecha de la venta
    string hora;                    // Hora de la venta
    vector<DetalleVenta> detalles;  // Lista de productos vendidos

   public:
    Venta(string id, string fecha, string hora);

    // Getters
    const string& getId() const;
    const string& getFecha() const;
    const string& getHora() const;
    const vector<DetalleVenta>& getDetalles() const;

    // Agrega un producto a la venta
    void agregarDetalle(const DetalleVenta& detalle);

    // Calcula el total sumando todos los subtotales
    double calcularTotal() const;

    // Genera una NOTA DE VENTA INTERNA formateada
    string generarComprobante(const string& nombreEmpresa) const;
};

#endif