#include "Venta.h"

#include <iomanip>
#include <sstream>
#include <utility>

using namespace std;

// ========== DETALLEVENTA ==========

DetalleVenta::DetalleVenta(string codigoProducto, string nombreProducto, int cantidad,
                           double precioUnitario)
    : codigoProducto(move(codigoProducto)),
      nombreProducto(move(nombreProducto)),
      cantidad(cantidad),
      precioUnitario(precioUnitario) {}

const string& DetalleVenta::getCodigoProducto() const {
    return codigoProducto;
}
const string& DetalleVenta::getNombreProducto() const {
    return nombreProducto;
}
int DetalleVenta::getCantidad() const {
    return cantidad;
}
double DetalleVenta::getPrecioUnitario() const {
    return precioUnitario;
}

double DetalleVenta::calcularSubtotal() const {
    return cantidad * precioUnitario;
}

// ========== VENTA ==========

Venta::Venta(string id, string fecha, string hora)
    : id(move(id)), fecha(move(fecha)), hora(move(hora)) {}

const string& Venta::getId() const {
    return id;
}
const string& Venta::getFecha() const {
    return fecha;
}
const string& Venta::getHora() const {
    return hora;
}
const vector<DetalleVenta>& Venta::getDetalles() const {
    return detalles;
}

void Venta::agregarDetalle(const DetalleVenta& detalle) {
    detalles.push_back(detalle);
}

/**
 * Calcula el total de la venta
 * Complejidad: O(n) - Recorre todos los detalles
 */
double Venta::calcularTotal() const {
    double total = 0.0;
    for (const auto& detalle : detalles) {
        total += detalle.calcularSubtotal();
    }
    return total;
}

/**
 * Genera una NOTA DE VENTA INTERNA formateada con tabla de productos
 * Complejidad: O(n) - Recorre todos los detalles para formatear
 */
string Venta::generarComprobante(const string& nombreEmpresa) const {
    ostringstream salida;
    salida << "\n============================================================\n";
    salida << "                    " << nombreEmpresa << "\n";
    salida << "                 NOTA DE VENTA INTERNA\n";  // Título del comprobante
    salida << "============================================================\n";
    salida << "Venta: " << id << "\n";
    salida << "Fecha: " << fecha << "    Hora: " << hora << "\n";
    salida << "------------------------------------------------------------\n";
    salida << left << setw(40) << "Producto" << right << setw(7) << "Cant." << setw(12)
           << "P. Unit." << setw(13) << "Subtotal" << '\n';
    salida << "------------------------------------------------------------\n";

    salida << fixed << setprecision(2);
    for (const auto& detalle : detalles) {
        string nombre = detalle.getNombreProducto();
        salida << left << setw(40) << nombre << right << setw(7) << detalle.getCantidad()
               << setw(12) << detalle.getPrecioUnitario() << setw(13) << detalle.calcularSubtotal()
               << '\n';
    }

    salida << "------------------------------------------------------------\n";
    salida << right << setw(59) << "TOTAL: S/ " << setw(10) << calcularTotal() << '\n';
    salida << "============================================================\n";
    salida << "Documento de control interno - No valido como comprobante tributario\n";
    salida << "============================================================\n";
    return salida.str();
}