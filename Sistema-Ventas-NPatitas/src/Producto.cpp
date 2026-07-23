#include "Producto.h"

#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;

// ========== CONSTRUCTORES ==========

Producto::Producto() : precio(0.0), stock(0) {}

Producto::Producto(string codigo, string familia, string concepto, double precio, int stock)
    : codigo(move(codigo)),
      familia(sanitizar(familia)),    // Sanitiza para evitar '|' en el archivo
      concepto(sanitizar(concepto)),  // Sanitiza para evitar '|' en el archivo
      precio(precio),
      stock(stock) {}

// ========== GETTERS ==========

const string& Producto::getCodigo() const {
    return codigo;
}
const string& Producto::getFamilia() const {
    return familia;
}
const string& Producto::getConcepto() const {
    return concepto;
}

string Producto::getNombreCompleto() const {
    return familia + " - " + concepto;
}

double Producto::getPrecio() const {
    return precio;
}
int Producto::getStock() const {
    return stock;
}

// ========== SETTERS ==========

void Producto::setFamilia(const string& nuevaFamilia) {
    familia = sanitizar(nuevaFamilia);
}

void Producto::setConcepto(const string& nuevoConcepto) {
    concepto = sanitizar(nuevoConcepto);
}

void Producto::setPrecio(double nuevoPrecio) {
    precio = nuevoPrecio;
}

void Producto::setStock(int nuevoStock) {
    stock = nuevoStock;
}

// ========== MÉTODO DE NEGOCIO ==========

/**
 * Descuenta stock al realizar una venta
 * Complejidad: O(1)
 * Validación: cantidad > 0 y cantidad <= stock disponible
 */
bool Producto::descontarStock(int cantidad) {
    if (cantidad <= 0 || cantidad > stock) {
        return false;  // Evita stock negativo
    }
    stock -= cantidad;
    return true;
}

// ========== PERSISTENCIA ==========

/**
 * Serializa el producto a formato: CODIGO|FAMILIA|CONCEPTO|PRECIO|STOCK
 * Este formato es fácil de leer y parsear
 */
string Producto::serializar() const {
    ostringstream salida;
    salida << codigo << '|' << familia << '|' << concepto << '|' << precio << '|' << stock;
    return salida.str();
}

/**
 * Deserializa una línea de texto a un objeto Producto
 * Valida que haya exactamente 5 campos y que los valores sean válidos
 */
bool Producto::deserializar(const string& linea, Producto& producto) {
    stringstream entrada(linea);
    string codigoLeido, familiaLeida, conceptoLeido, precioTexto, stockTexto;

    // Extraer 5 campos usando '|' como separador
    if (!getline(entrada, codigoLeido, '|') || !getline(entrada, familiaLeida, '|') ||
        !getline(entrada, conceptoLeido, '|') || !getline(entrada, precioTexto, '|') ||
        !getline(entrada, stockTexto)) {
        return false;  // Formato incorrecto
    }

    try {
        double precioLeido = stod(precioTexto);
        int stockLeido = stoi(stockTexto);

        // Validar que los valores no sean negativos
        if (precioLeido < 0 || stockLeido < 0) {
            return false;
        }

        producto = Producto(codigoLeido, familiaLeida, conceptoLeido, precioLeido, stockLeido);
        return true;
    } catch (...) {
        return false;  // Error en conversión numérica
    }
}

// ========== SANITIZACIÓN ==========

/**
 * Sanitiza un texto eliminando caracteres que rompen el formato de serialización
 * Reemplaza '|' por '-' para no romper el separador
 */
string Producto::sanitizar(const string& texto) {
    string sanitizado = texto;
    replace(sanitizado.begin(), sanitizado.end(), '|', '-');
    return sanitizado;
}