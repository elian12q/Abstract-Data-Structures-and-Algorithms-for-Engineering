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
void ejercicio2();
void moverJugador(int* posx, int* posy, char d);

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

void ejercicio2(){
    // Variables for position with their pointers 
    int posX = 1; 
    int posY = 1;
    int* pointer3 = &posX;
    int* pointer4 = &posY;

    char next_pos; // It will be send to "moverJugador" function 
    string input_pos; // To receive strings or chars

    // While true keeps the game until player types "salir"
    while (true){
        cout << "\nEstás en la habitación [" << posX << "," << posY << "].\n";
        cin >> input_pos;   

        if ((input_pos == "norte") || (input_pos == "n")){ // "n" or "norte" are valid
            next_pos = 'n';
            moverJugador(pointer3, pointer4, next_pos);

        } else if ((input_pos == "este") || (input_pos == "e")){ // "e" or "este" are valid
            next_pos = 'e';
            moverJugador(pointer3, pointer4, next_pos);

        } else if ((input_pos == "oeste") || (input_pos == "o")){ // "o" or "oeste" are valid
            next_pos = 'o';
            moverJugador(pointer3, pointer4, next_pos);

        } else if ((input_pos == "sur") || (input_pos == "s")){ // "s" or "sur" are valid
            next_pos = 's';
            moverJugador(pointer3, pointer4, next_pos);

        } else if (input_pos == "salir"){ // To kill the game 
            cout << "\nGracias por jugar.\n";
            return;

        } else { // For invalid inputs
            cout << "Opción inválida.\n";
        }
    } 
}

void moverJugador(int* posx, int* posy, char d){
    switch (d) // For each letter: n, e, o, s
    {
    case 'n':
        if (*posx == 0) { // The limit for north 
            cout << "No puedes ir en esa dirección, hay una pared.\n";
        } else {
            cout << "Te mueves al norte.\n";
            *posx -=1; // Change the value in memory
        }
        break;

    case 'e':
        if (*posy == 2) { // The limit for east
            cout << "No puedes ir en esa dirección, hay una pared.\n";
        } else {
            cout << "Te mueves al este.\n";
            *posy +=1; // Change the value in memory
        }
        break;

    case 'o':
        if (*posy == 0) { // The limit for west
            cout << "No puedes ir en esa dirección, hay una pared.\n";
        } else {
            cout << "Te mueves al oeste.\n";
            *posy -=1; // Change the value in memory
        }
        break;

    case 's':
        if (*posx == 2) { // The limit for south
            cout << "No puedes ir en esa dirección, hay una pared.\n";
        } else {
            cout << "Te mueves al sur.\n";
            *posx +=1; // Change the value in memory
        }
        break;
    } // There isn't default because d can only be n, e, o, s
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
                ejercicio2();
                break;
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