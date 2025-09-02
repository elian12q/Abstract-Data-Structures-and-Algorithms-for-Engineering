/*
- Abstract Data Structures and Algorithms for Engineering.
- Laboratory 1.
- Student: Elián Jiménez Quesada - C13983.
*/


#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

// Function prototypes
void menu();
void ejercicio1();
double get_coefficients(char coefficient);
int get_roots(double a, double b, double c, double* r1, double* r2);

// Main
int main () {

    // Call the menu function
    menu ();

    return 0; 
}

void ejercicio1() {
    cout << "\n--------------------------Ejercicio 1--------------------------\n";
    int discriminant;
    double root1, root2; // Two variables for the roots

    // A pointer for each root
    double* pointer1 = &root1;
    double* pointer2 = &root2;

    // Get coefficients by giving the specific letter to make almost the same print
    double a = get_coefficients('a');
    double b = get_coefficients('b');
    double c = get_coefficients('c');

    // Summary
    cout << "\nLos coeficientes ingresados son: a=" << a << ", b=" << b << ", c=" << c << "\n";

    // Get roots by giving coefficients and the addresses of variables 
    discriminant = get_roots(a, b, c, pointer1, pointer2);

    // Here both the variable and the pointer are used to print the result
    if (discriminant == 0) {
        cout << "\nLa ecuación tiene una única raíz real:\n" 
        "Raíz = "<< *pointer1 << "\n";
    } else if (discriminant > 0) {
        cout << "\nLa ecuación tiene dos raices reales:\n"
        "Raíz 1 = "<< root1 << "\n" 
        "Raíz 2 = "<< *pointer2 << "\n";
    } else {
        cout << "\nEl discriminante es negativo. No existen soluciones reales. \n";
    }
}

int get_roots(double a, double b, double c, double* r1, double* r2){

    // Calculate discriminant
    int d = (b*b) - ((4*a)*c);
    
    // Calculate roots using the given formula, the value in memory is changed using the pointers
    if (d==0){
        *r1 = (-b + (sqrt((b*b)-((4*a)*c)))) / (2*a); // One root
    } else if (d>0){
        *r1 = (-b + (sqrt((b*b)-((4*a)*c)))) / (2*a); // Two roots
        *r2 = (-b - (sqrt((b*b)-((4*a)*c)))) / (2*a);
    } // else does nothing

    return d;
}

double get_coefficients(char coefficient){

    double z; // Random letter to print a, b or c

    // While true to ask repeatedly
    while (true) {
        cout << "\nIngrese el coeficiente " << coefficient << ": ";
        cin >> z;

        // Check if the input is a number:
        if (std::cin.fail()) {
            std::cout << "\nOpción inválida, debe ser un número real.\n"
                         "Inténtelo nuevamente.\n";
            std::cin.clear();                                    // Clear the buffer error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line to avoid an infinite loop of errors
            continue;
        }
        return z;
    }
}

void menu() {

    int menu_option;

    // While true to ask repeatedly
    while (true) {
        cout << "\n--------------------------Menú Laboratorio 1-------------------------- \n"
            "1. Ejercicio 1 \n"
            "2. Ejercicio 2 \n"
            "3. Ejercicio 3 \n"
            "4. Salir \n"
            "Ingrese la opción que desea ejecutar: ";

        cin  >> menu_option;

        // Check if the input is a number:
        if (std::cin.fail()) {
            std::cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                         "Inténtelo nuevamente.\n";
            std::cin.clear();                                    // Clear the buffer error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the line to avoid an infinite loop of errors
            continue;                                            // Jump to the next iteration
        }

        // Check the entered value
        switch (menu_option) {
            case 1: 
                ejercicio1();
                break;
            case 2: 
                cout << "Bienvenido al ejercicio 2\n"; 
                return;
            case 3:
                cout << "Bienvenido al ejercicio 3\n"; 
                return;
            case 4:
                cout << "\nSaliendo del programa... \n";
                return;
            default:
                cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                        "Inténtelo nuevamente.\n";
        }
    }
    
}