#include <iostream>
using namespace std;

int main() {
    char operacion;
    double num1, num2, resultado;
    
    cout << "=== CALCULADORA BASICA ===" << endl;
    cout << "Operaciones disponibles: + (suma), - (resta), * (multiplicacion), / (division)" << endl;
    cout << "Ingrese la operacion (ejemplo: 5 + 3): ";
    
    cin >> num1 >> operacion >> num2;
    
    switch(operacion) {
        case '+':
            resultado = num1 + num2;
            cout << num1 << " + " << num2 << " = " << resultado << endl;
            break;
            
        case '-':
            resultado = num1 - num2;
            cout << num1 << " - " << num2 << " = " << resultado << endl;
            break;
            
        case '*':
            resultado = num1 * num2;
            cout << num1 << " * " << num2 << " = " << resultado << endl;
            break;
            
        case '/':
            if(num2 != 0) {
                resultado = num1 / num2;
                cout << num1 << " / " << num2 << " = " << resultado << endl;
            } else {
                cout << "Error: No se puede dividir entre cero!" << endl;
            }
            break;
            
        default:
            cout << "Error: Operacion no valida!" << endl;
            break;
    }
    
    return 0;
}