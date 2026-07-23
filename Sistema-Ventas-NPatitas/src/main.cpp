#include <exception>
#include <iostream>

#include "Menu.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

/**
 * @brief Punto de entrada principal del sistema
 *
 * Tema: Estructuras de control y manejo de excepciones (Unidad 1 y 2)
 *
 * Configura UTF-8 en Windows para mostrar correctamente caracteres especiales
 * y maneja excepciones globales del sistema.
 */
int main() {
#ifdef _WIN32
    // Configurar codificación UTF-8 (ñ, tildes, S/)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    try {
        Menu menu;
        menu.iniciar();
    } catch (const exception& error) {
        cerr << "Error inesperado: " << error.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "Error inesperado no identificado.\n";
        return 1;
    }

    return 0;
}