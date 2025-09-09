/*
- Abstract Data Structures and Algorithms for Engineering.
- Assignment 1.
- Student: Elián Jiménez Quesada - C13983.
*/


#include <iostream>
#include <tuple>   // To return more than one value from function
#include <cmath>   // To use sin, cos and fabs()
#include <iomanip> // To specify decimals

#define epsilon 1e-7 // For the case of Convergence by Tolerance

using namespace std;

// Function prototypes
bool check_natural_number(string input);
double get_value(string message);
void metodoBiseccion();
void metodoNewton();
int choose_function();
tuple<double, double, double> calc_function_B(double a, double b, double c, int num_function);
tuple<double, double> calc_function_NR(double xn, int num_function);

// Main
int main () {

    string main_input; // Input as string
        int menu_option;
        
        // While true to ask repeatedly
        while (true) {
            cout << "\n*** Calculadora de Raíces Numéricas ***\n"
                 << "Seleccione el método:\n"
                 << "1. Método de Bisección \n"
                 << "2. Método de Newton-Raphson \n"
                 << "Opción: ";

            cin >> main_input;
            
            if (check_natural_number(main_input)) {   // If true, read the number as an integer
                // Convert to integer
                menu_option = stoi(main_input);

            } else {                            // If false, keep asking                      
                cout << "\nOpción inválida, debe ser un valor entre 1 y 2.\n"
                     << "Inténtelo nuevamente.\n";
                continue;
            }

            // Validate the entered value
            switch (menu_option) {
                case 1:
                    metodoBiseccion();
                    break;
                case 2:
                    metodoNewton();
                    break;
                default:
                    cout << "\nOpción inválida, debe ser un valor entre 1 y 2.\n"
                         << "Inténtelo nuevamente.\n";
            }
        }
}

void metodoBiseccion(){

    double a, b, c; 
    
    // Messages to recycle functions
    string message_B_a = "Ingrese el valor de a: ";
    string message_B_b = "Ingrese el valor de b: ";

    cout << "\nHa seleccionado Bisección.\n";

    // The user has to choose the function to work with
    int function = choose_function();

    // Bisection cannot be applied to f(x) = -sin(x) - 1 because f(x) ≤ 0 (no sign change)
    if (function == 4){
        cout << "\nNo se puede aplicar bisección porque f(x) <= 0 y no hay cambio de signo en ningún intervalo.\n";
        return;
    }

    cout << "\nPara el método de Bisección se necesita un intervalo [a, b]\n";

    // While true to keep asking until a valid interval has been entered
    while (true) {

        // "get_value" checks if the interval is a real number
        a = get_value(message_B_a); 
        b = get_value(message_B_b);

        // b must be greater than a, to have a valid interval. Otherwise, ask again
        if (a > b){
            cout << "\nEl intervalo elegido no es válido. b debe ser mayor que a\n ";
            continue; 
        }

        // Compute midpoint c = (a+b)/2
        c = (a + b)/2;

        // Compute f(a), f(b), and f(c) for the selected function by the user
        auto [f_a, f_b, f_c] = calc_function_B(a, b, c, function);

        // To make possible the method, it must be true that: f(a) * f(b) < 0
        if ((f_a * f_b) < 0){ // If f(a) * f(b) < 0 stop asking 
            break; // Otherwise, request a new interval
        } else {
            cout << "\nEl intervalo elegido no es válido para este método. Se necesita que f(a) * f(b) < 0\n"
                 << "Elija un nuevo intervalo.\n";
        }
    }

    cout << endl; // Added spacing just for aesthetics

    // Iteration Limit (Safety Net). It will only make 100 iterations
    for (int i = 0; i < 100; i++){

        // Update f(a), f(b) and f(c), according to the chosen function by the user
        auto [f_a, f_b, f_c] = calc_function_B(a, b, c, function);

        // Print the current iteration
        cout << "Iteración " << (i+1) <<": c = " << fixed << setprecision(6) << c <<"\n"; // It will use six decimals

        // Convergence by Tolerance. Stop if f(c) is close to zero
        if (fabs(f_c) <= epsilon){
            cout << "Convergencia alcanzada.\n";
            break;

        }  else { // While it is not close to zero, update a or c and keep the condition f(a) * f(b) < 0
            if ( ((f_c < 0) && (f_a < 0)) || ((f_c >= 0) && (f_a >= 0)) ){
                a = c; // If a and c have the same sign, a = c

            } else if ( ((f_c < 0) && (f_b < 0)) || ((f_c >= 0) && (f_b >= 0)) ){
                b = c; // If b and c have the same sign, b = c
            }

        // Update the c value
        c = (a + b)/2;
        }
    }

    // Print the final answer when a stop condition occurs
    cout << "\nLa raíz es aproximadamente: " << fixed << setprecision(6) << c << endl;
}

void metodoNewton(){

    string message_NR = "Ingrese la estimación inicial x0: ";
    double xn;

    cout << "Ha seleccionado Newton-Raphson.\n";
    
    // The user has to choose the function to work with
    int function = choose_function();

    // "get_value" checks if x0 is a real number
    xn = get_value(message_NR); 

    for (int i = 0; i < 100; i++){

        // Compute f(xn) and f'(xn) for the selected function by the user
        auto [f_xn, df_xn] = calc_function_NR(xn, function);

        if (fabs(f_xn) <= epsilon){
            cout << "Convergencia alcanzada.\n";
            break;

        } else {
            xn = xn - (f_xn/df_xn);
            // Print the current iteration
            cout << "Iteración " << (i+1) <<": x = " << fixed << setprecision(6) << xn <<"\n"; // It will use six decimals
        }
    }

    // Print the final answer when a stop condition occurs
    cout << "\nLa raíz es aproximadamente: " << fixed << setprecision(6) << xn << endl;
}

int choose_function(){
    string func_input; // Validate the entered value
    int num_function; // To return the function as an ID

    // Functions as strings
    string funcP1 = "f(x) = x^3 - x - 2";
    string funcP2 = "f(x) = 3x^2 - 1";
    string funcT1 = "f(x) = cos(x) - x";
    string funcT2 = "f(x) = -sen(x) - 1";

    cout << "\nFunciones disponibles: \n"
         << "1. " << funcP1 << "\n"
         << "2. " << funcP2 << "\n"
         << "3. " << funcT1 << "\n"
         << "4. " << funcT2 << "\n";

    // While true to ask repeatedly 
    while (true){
        cout << "\nElija una función para encontrar una raíz: ";

        cin >> func_input;

        if (check_natural_number(func_input)) {   // If true, read the number as an integer
            // Convert to integer
            num_function = stoi(func_input);

        } else {                            // If false, keep asking                      
            cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        }

        // Print the chosen function and return a specific number representing a function:
        // 1 as f(x) = x^3 - x - 2
        // 2 as f(x) = 3x^2 - 1
        // 3 as f(x) = cos(x) - x
        // 4 as f(x) = -sin(x) - 1
        switch (num_function) {
        case 1:
            cout << "Ha elegido " << funcP1 << "\n";
            return num_function;

        case 2:
            cout << "Ha elegido " << funcP2 << "\n";
            return num_function;
        
        case 3:
            cout << "Ha elegido " << funcT1 << "\n";
            return num_function;

        case 4:
            cout << "Ha elegido " << funcT2 << "\n";
            return num_function;
        
        default:
            cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n" // If it is not a number between 1 to 4, ask again
                 << "Inténtelo nuevamente.\n";
            break;
        }
    }

}

// Calculates the value of f(xn) and f'(xn) according to the chosen function by the user
tuple<double, double> calc_function_NR(double xn, int num_function){

    double fxn; 
    double df_xn;

    switch (num_function){
        
    case 1: // f(x) = x^3 - x - 2 and f'(x) = 3x^2 - 1
        fxn = (xn*xn*xn) - xn - 2;
        df_xn = (3*(xn*xn)) - 1;
        break;
    
    case 2: // f(x) = 3x^2 - 1 and f'(x) = 6x
        fxn = (3*(xn*xn)) - 1;
        df_xn = 6*xn;
        break;

    case 3: // f(x) = cos(x) - x and f'(x) = -sin(x) - 1
        fxn = cos(xn) - xn;
        df_xn = -sin(xn) - 1;
        break;

    case 4: // f(x) = -sin(x) - 1 and f'(x) = -cos(x)
        fxn = -sin(xn) - 1;
        df_xn = -cos(xn);
        break;
    }
    return {fxn, df_xn};
}

// Calculates the value of f(a), f(b) and f(c), according to the chosen function by the user
tuple<double, double, double> calc_function_B(double a, double b, double c, int num_function){

    double fx_a; 
    double fx_b;
    double fx_c;

    switch (num_function){
        
    case 1: // f(x) = x^3 - x - 2
        fx_a = (a*a*a) - a - 2;
        fx_b = (b*b*b) - b - 2;
        fx_c = (c*c*c) - c - 2;
        break;
    
    case 2: // f(x) = 3x^2 - 1
        fx_a = (3*(a*a)) - 1;
        fx_b = (3*(b*b)) - 1;
        fx_c = (3*(c*c)) - 1;
        break;

    case 3: // f(x) = cos(x) - x
        fx_a = cos(a) - a;
        fx_b = cos(b) - b;
        fx_c = cos(c) - c;
        break;

    case 4: // f(x) = -sin(x) - 1
        fx_a = -sin(a) - 1;
        fx_b = -sin(b) - 1;
        fx_c = -sin(c) - 1;
        break;
    }
    return {fx_a, fx_b, fx_c};
}

// Request real numbers
double get_value(string message){

    double z; // Variable to store a, b or x0
    string input_value; // Input as string

    // While true to ask repeatedly
    while (true) {
        cout << "\n" << message; // Message according to the required value
        cin >> input_value;

        bool is_number = true; // To analyze all cases where the input is invalid
        bool point = false; // Decimal point allowed only once

        for (size_t i = 0; i < input_value.size(); i++) { // Check the entire input

            char s = input_value[i]; // Iterates throughout the string

            if (!isdigit(s)){ // If it is not a number:

                if (input_value.size() == 1){ // And there is only one character, is_number = false
                    is_number = false;
                    break;        
                }

                if (i == 0 && (s == '+' || s == '-')){ // But the first character is minus or plus, continue with the next iteration
                    continue;
                }
                
                if (s == '.' && (point)) { // And it is the second point in the string, is_number = false
                    is_number = false; 
                    break; 
                } else if (s == '.' && (!point)){ // And it is the first point in the string, continue with the next iteration
                    point = true;
                    continue;
                }
            
                is_number = false; // If none of the above conditions are met, is_number = false
                break;
            }
        }

        if (!is_number) {
            cout << "\nOpción inválida, debe ser un número real.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        }

        // Convert to float
        z = stod(input_value);
        break;
    }
    return z; // Return the number as a double
}

// Check if an input is a natural number
bool check_natural_number(string input){

        // Check if the input is a valid number:
        bool is_natural_number = true;
        for (char c : input) { // Check the entire input
            if (!isdigit(c)) { // If it is not a single digit, it will show an error
                is_natural_number = false;
                break;
            }
        }

        if (!is_natural_number) { // If it is not a natural number return false
            return false;
        } else {
            return true;   // If it is a natural number return true         
        }
}