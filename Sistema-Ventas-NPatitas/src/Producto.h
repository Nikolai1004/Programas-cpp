#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

using namespace std;

/**
 * @brief Clase Producto - Representa un artículo en el inventario
 *
 * Tema: Tipos de Datos Abstractos (TDA) - Unidad 2
 *
 * Atributos:
 * - codigo: Identificador único (ej: S00001)
 * - familia: Grupo al que pertenece (ej: Sustrato)
 * - concepto: Presentación o variante (ej: Premium bolsa x 1kg)
 * - precio: Precio de venta en soles
 * - stock: Cantidad disponible en inventario
 */
class Producto {
   private:
    string codigo;
    string familia;
    string concepto;
    double precio;
    int stock;

   public:
    // Constructores
    Producto();  // Constructor por defecto (necesario para deserializar)
    Producto(string codigo, string familia, string concepto, double precio, int stock);

    // Getters (solo lectura)
    const string& getCodigo() const;
    const string& getFamilia() const;
    const string& getConcepto() const;
    string getNombreCompleto() const;  // Retorna "Familia - Concepto"
    double getPrecio() const;
    int getStock() const;

    // Setters (para editar productos)
    void setFamilia(const string& nuevaFamilia);
    void setConcepto(const string& nuevoConcepto);
    void setPrecio(double nuevoPrecio);
    void setStock(int nuevoStock);

    // Método de negocio: descuenta stock con validación
    bool descontarStock(int cantidad);

    // Persistencia: Serialización y Deserialización (Unidad 3)
    string serializar() const;
    static bool deserializar(const string& linea, Producto& producto);

    // Sanitiza texto para evitar que el carácter '|' rompa el formato
    static string sanitizar(const string& texto);
};

#endif