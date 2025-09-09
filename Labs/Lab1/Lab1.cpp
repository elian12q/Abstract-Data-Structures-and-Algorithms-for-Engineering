/*
- Abstract Data Structures and Algorithms for Engineering.
- Laboratory 1.
- Student: Elián Jiménez Quesada - C13983.
*/


#include <iostream>
#include <limits>
#include <cmath>
#include <string>
#include <cctype>  // For isdigit
#include <vector>

using namespace std;

// Function prototypes
void ejercicio1();
double get_coefficients(char coefficient);
int get_roots(double a, double b, double c, double* r1, double* r2);
void ejercicio2();
void moverJugador(int* posx, int* posy, char d);
void ejercicio3();
void calc_average(double* array, int size);
void find_max_min(double* array, int size);
void threshold(double* array, int size);
void print_celsius(double* array, int size);
void print_fahrenheit(double* array, int size);
void ejercicio4();
void add_task(vector<string>* v);
void see_task(vector<string>* v);
void done_task(vector<string>* v);
void menu();
bool check_natural_number(string input);

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

    double z; // Variable to store a, b or c
    string input_coefficient; // Input as string

    // While true to ask repeatedly
    while (true) {
        cout << "\nIngrese el coeficiente " << coefficient << ": ";
        cin >> input_coefficient;

        bool is_number = true; // To analyze all cases where the input is invalid
        bool point = false; // Decimal point allowed only once

        for (size_t i = 0; i < input_coefficient.size(); i++) { // Check the entire input

            char s = input_coefficient[i]; // Iterates throughout the string

            if (!isdigit(s)){ // If it is not a number:

                if (input_coefficient.size() == 1){ // And there is only one character, is_number = false
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
        z = stod(input_coefficient);
        break;
    }
    return z;
}

void ejercicio2(){
    // Variables for position with their pointers 
    int posX = 1; 
    int posY = 1;
    int* pointer3 = &posX;
    int* pointer4 = &posY;

    char next_pos; // It will be sent to the "moverJugador" function 
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
    switch (d){ // For each letter: n, e, o, s

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

void ejercicio3(){

    string temp_input; // Input as string
    int menu_temp;

    // Array, its pointer and the number of temperature values
    double temperaturas[] = {22.5, 24.1, 21.9, 25.3, 26.0, 19.8, 23.7, 28.1, 18.5, 22.5};
    double* pointer5 = temperaturas; // equivalent: double* pointer5 = &temperaturas[0] 
    size_t size_temp = sizeof(temperaturas) / sizeof(temperaturas[0]);

    cout << "\n--- Analizador de Temperaturas ---\n"
            "1. Calcular Promedio\n"
            "2. Encontrar Máximo y Mínimo\n"
            "3. Contar Superiores a Umbral\n"
            "4. Mostrar datos en Celsius\n"
            "5. Mostrar datos en Fahrenheit\n"
            "6. Salir";

    // While true to ask repeatedly
    while (true) {
        cout << "\nSeleccione una opción: ";

        cin >> temp_input;

        if (check_natural_number(temp_input)) { // If true, read the number as an integer
            // Convert to integer
            menu_temp = stoi(temp_input);

        } else { // If false, keep asking                      
            cout << "\nOpción inválida, debe ser un valor entre 1 y 6.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        }

        // Check the entered value
        switch (menu_temp) {
            case 1: 
                calc_average(pointer5, size_temp);
                break;
            case 2: 
                find_max_min(pointer5, size_temp);
                break;
            case 3:
                threshold(pointer5 ,size_temp);
                break;
            case 4:
                print_celsius(pointer5, size_temp);
                break;
            case 5:
                print_fahrenheit(pointer5, size_temp);
                break;
            case 6:
                cout << "\nSaliendo del programa.\n";
                return;
            default:
                cout << "\nOpción inválida, debe ser un valor entre 1 y 6.\n"
                        "Inténtelo nuevamente.\n";
        }
    }
}

void calc_average(double* array, int size){

    // Variable to do the sum
    double average = 0;

    // This loop iterates through the array
    for (int i = 0; i < size; i++){

        average += *(array + i); // It takes the values in the memory where the array is
    }

    // Divide by the size of the array
    average = average / size;
    cout << "La temperatura promedio es: " << average << " C\n";
}

void find_max_min(double* array, int size){
    float max = *array;
    float min = *array;

    // This loop iterates through the array
    for (int i = 0; i < size; i++){

        if (max < *(array + i)){ // If the current max value is less than the next value in the array, update the max value
            max = *(array + i);
        }

        else if (min > *(array + i)){ // If the current min value is greater than the next value in the array, update the min value
            min = *(array + i);
        }
    }
    cout << "La temperatura máxima es: " << max << " C\n"
         << "La temperatura mínima es: " << min << " C\n"; 
}

void threshold(double* array, int size){

    double threshold_value;
    int count = 0;
    string threshold_input; // Input as string

    while (true){
        cout << "\nIngrese el valor de umbral (en Celsius): ";
        cin >> threshold_input;

        bool is_number = true; // To analyze all cases where the input is invalid
        bool point = false; // Decimal point allowed only once

        for (size_t i = 0; i < threshold_input.size(); i++) { // Check the entire input

            char s = threshold_input[i]; // Iterates throughout the string

            if (!isdigit(s)){ // If it is not a number:

                if (threshold_input.size() == 1){ // And there is only one character, is_number = false
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
        threshold_value = stod(threshold_input);
        break;
    }

    // This loop iterates through the array
    for (int i = 0; i < size; i++){

        if (threshold_value < *(array + i)){ // If threshold value is less than the value in array, count = count + 1 
            count += 1;
        }
    }
    cout << "\nHay " << count << " lecturas de temperatura que superan el umbral de " << threshold_value << " C\n";
}

void print_celsius(double* array, int size){

    cout << "--- Temperaturas en Celsius ---\n";

    // This loop iterates through the array
    for (int i = 0; i < size; i++){

        if (i == (size - 1)){ // If it is the last position, don't print a comma
            cout << *(array + i) << " C\n";

        } else {
            cout << *(array + i) << " C, ";
        }
    }
    cout << "-------------------------------\n";
}

void print_fahrenheit(double* array, int size){

    cout << "--- Temperaturas en Fahrenheit ---\n";

    // This loop iterates through the array
    for (int i = 0; i < size; i++){

        if (i == (size - 1)){ // If is the last position, don't set a comma
            cout << ((*(array + i) * (9.0/5) ) + 32) << " F\n"; // Applying the formula: F = (C * (9/5)) + 32

        } else {
            cout << ((*(array + i) * (9.0/5) ) + 32) << " F, ";
        }
    }
    cout << "---------------------------------\n";
}

void ejercicio4(){

    string to_do_input; // Input as a string
    int menu_to_do;
    vector<string> tasks;

    cout << "\n--- Mi Lista de Tareas ---\n"
            "1. Agregar Tarea\n"
            "2. Ver Tareas\n"
            "3. Marcar Tarea como Completada\n"
            "4. Salir";

    // While true to ask repeatedly
    while (true) {
            cout << "\nOpción: ";

        cin >> to_do_input;

        if (check_natural_number(to_do_input)) { // If true, read the number as an integer
            // Convert to integer
            menu_to_do = stoi(to_do_input);

        } else { // If false, keep asking                      
            cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        }

        // Check the entered value
        switch (menu_to_do) {
            case 1: 
                add_task(&tasks);
                break;
            case 2:
                if ( (tasks.size()) == 0 ) { // If the vector is empty, there is nothing to show
                    cout << "\nLa lista de tareas está vacía.\n";
                    break;
                }
                see_task(&tasks);
                break;
            case 3:
                if ( (tasks.size()) == 0 ) { // If the vector is empty, there is nothing to complete
                    cout << "\nLa lista de tareas está vacía.\n";
                    break;
                }
                done_task(&tasks);
                break;
            case 4:
                cout << "\nHasta luego!\n";
                return;
            default:
                cout << "\nOpción inválida, debe ser un valor entre 1 y 4.\n"
                        "Inténtelo nuevamente.\n";
        }
    }
}

void add_task(vector<string>* v){

    string new_task;
    cout << "Ingrese la nueva tarea: ";

    getline(cin >> ws, new_task); // Save the entire string to "new_task"
    (*v).push_back(new_task); // Add new element to the vector
}

void see_task(vector<string>* v){

    cout << "--- TAREAS PENDIENTES ---\n";

    // This loop iterates through the vector and prints its elements
    for (size_t i = 0; i < (*v).size(); i++) {
        cout << (i+1) << ". " << (*v)[i] << "\n";
    }
    cout << "-------------------------\n";
}

void done_task(vector<string>* v){

    string task_num_input;
    int task_num;

    while (true) {
        cout << "Número de la tarea a completar: ";
        cin >> task_num_input;

        if (check_natural_number(task_num_input)) { // If true, read the number as an integer
            // Convert to integer
            task_num = stoi(task_num_input);
            break;

        } else { // If false, keep asking                      
            cout << "\nOpción inválida, debe ser un valor entero positivo.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        }

        if (task_num<=0){ // It has to be greater than 0
            cout << "\nOpción inválida, debe ser un valor entero positivo.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
        } 
    }

    if ( (task_num) > static_cast<int>((*v).size()) ){ // Checks if the vector has the number of tasks equal to the value of "num_task"
        cout << "\nLa lista no tiene una tarea número " << (task_num) << ".\n";
        return;
    }

    cout << "Tarea \"" << (*v)[task_num - 1] << "\" completada.\n";
    (*v).erase((*v).begin() + (task_num - 1)); // Erase from the vector, the value given for the user 
}

void menu() {

    string main_input; // Input as a string
    int menu_option;
    
    // While true to ask repeatedly
    while (true) {
        cout << "\n--------------------------Menú Laboratorio 1--------------------------\n"
             << "1. Ejercicio 1 \n"
             << "2. Ejercicio 2 \n"
             << "3. Ejercicio 3 \n"
             << "4. Ejercicio 4 \n"
             << "5. Salir \n"
             << "Ingrese la opción que desea ejecutar: ";

        cin >> main_input;
        
        if (check_natural_number(main_input)) { // If true, read the number as an integer
            // Convert to integer
            menu_option = stoi(main_input);

        } else { // If false, keep asking                      
            cout << "\nOpción inválida, debe ser un valor entre 1 y 5.\n"
                 << "Inténtelo nuevamente.\n";
            continue;
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
                ejercicio3();
                break;
            case 4:
                ejercicio4();
                break;
            case 5:
                cout << "\nSaliendo del programa...\n";
                return;
            default:
                cout << "\nOpción inválida, debe ser un valor entre 1 y 5.\n"
                     << "Inténtelo nuevamente.\n";
        }
    }
}

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
            return true; // If it is a natural number return true         
        }
}