/*
- Abstract Data Structures and Algorithms for Engineering.
- Laboratory 1.
- Student: Elián Jiménez Quesada - C13983.
*/


#include <iostream>
#include <limits>

using namespace std;

// Function prototypes
void menu();

// Main
int main () {

    // Call the menu function
    menu ();

    return 0; 
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
                cout << "Bienvenido al ejercicio 1\n"; return;
            case 2: 
                cout << "Bienvenido al ejercicio 2\n"; return;
            case 3:
                cout << "Bienvenido al ejercicio 3\n"; return;
            case 4:
                cout << "\nSaliendo del programa... \n";
                return;
            default:
                cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                        "Inténtelo nuevamente.\n";
        }
    }
    
}