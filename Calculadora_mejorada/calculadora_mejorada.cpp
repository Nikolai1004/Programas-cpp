#include <iostream>
using namespace std;

int main() {
    char operacion;
    double num1, num2, resultado;
    bool continuar = true;
    
    while(continuar) {
        cout << "\n=== CALCULADORA BASICA ===" << endl;
        cout << "1. Suma (+)" << endl;
        cout << "2. Resta (-)" << endl;
        cout << "3. Multiplicacion (*)" << endl;
        cout << "4. Division (/)" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> operacion;
        
        if(operacion == '5') {
            cout << "¡Hasta luego!" << endl;
            continuar = false;
            break;
        }
        
        if(operacion >= '1' && operacion <= '4') {
            cout << "Ingrese el primer numero: ";
            cin >> num1;
            cout << "Ingrese el segundo numero: ";
            cin >> num2;
            
            switch(operacion) {
                case '1':
                    resultado = num1 + num2;
                    cout << num1 << " + " << num2 << " = " << resultado << endl;
                    break;
                case '2':
                    resultado = num1 - num2;
                    cout << num1 << " - " << num2 << " = " << resultado << endl;
                    break;
                case '3':
                    resultado = num1 * num2;
                    cout << num1 << " * " << num2 << " = " << resultado << endl;
                    break;
                case '4':
                    if(num2 != 0) {
                        resultado = num1 / num2;
                        cout << num1 << " / " << num2 << " = " << resultado << endl;
                    } else {
                        cout << "Error: No se puede dividir entre cero!" << endl;
                    }
                    break;
            }
        } else {
            cout << "Opcion no valida!" << endl;
        }
    }
    
    return 0;
}