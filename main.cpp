#include <iostream>
#include <string>
#include <fstream>
#include "super_string_tda.hpp"
#include "super_string_functions.cpp"


using namespace std;


int string_to_int(const char* str, int start, int length) {
    int result = 0;
    for (int i = start; i < start + length; ++i) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

void copiar_string(const char* origen, char* destino, int inicio) {
    int i = inicio;
    int j = 0;
    while (origen[i] != '\0') {
        destino[j++] = origen[i++];
    }
    destino[j] = '\0';
}

int main() {
    // Crear un objeto super_string
    super_string ss;

   /* // Insertar el string "Gato amarillo"
    ss.INSERTAR(0, "Hola");
    ss.MOSTRAR();
    ss.mostrar_altura();
    cout<< "\n" << ss.mostrar_largo()<<endl;
    ss.agregar('c');
    ss.MOSTRAR();
    cout<< "\n" << ss.mostrar_largo()<<endl;
    
    // Mostrar el super-string y la raíz actual
    ss.INSERTAR(1,"_nueva");
    ss.mostrar_altura();
     cout<< "\n" << ss.mostrar_largo()<<endl;
    cout << "Antes de recortar:" << endl;
    ss.MOSTRAR();
    ss.mostrar_raiz();
    ss.mostrar_altura();

    // Aplicar la función recortar
    ss.recortar();

    // Mostrar el super-string y la nueva raíz después de recortar
    cout << "\nDespués de recortar:" << endl;
    ss.MOSTRAR();
    ss.mostrar_raiz();
    ss.mostrar_altura();

    super_string a;
    super_string b;

    ss.separar(3,a,b);
    a.MOSTRAR();
    a.mostrar_altura();

    b.MOSTRAR();
    b.mostrar_altura();

    */

    ifstream archivo;
    archivo.open("pruebas/prueba_1.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    super_string s;
    char linea[256];

    while (archivo.getline(linea, 256)) {
        if (linea[0] == 'I' && linea[1] == 'N' && linea[2] == 'S' && 
            linea[3] == 'E' && linea[4] == 'R' && linea[5] == 'T' && 
            linea[6] == 'A' && linea[7] == 'R') {
            int i = 9;
            while (linea[i] >= '0' && linea[i] <= '9') ++i;
            int arg1 = string_to_int(linea, 9, i - 9);
            char texto[256];
            copiar_string(linea, texto, i + 1);
            s.INSERTAR(arg1, texto);
        } else if (linea[0] == 'M' && linea[1] == 'O' && linea[2] == 'S' && 
                   linea[3] == 'T' && linea[4] == 'R' && linea[5] == 'A' && linea[6] == 'R') {
            s.MOSTRAR();
        } else if (linea[0] == 'E' && linea[1] == 'L' && linea[2] == 'I' && 
                   linea[3] == 'M' && linea[4] == 'I' && linea[5] == 'N' && 
                   linea[6] == 'A' && linea[7] == 'R') {
            int i = 9;
            while (linea[i] >= '0' && linea[i] <= '9') ++i;
            int arg1 = string_to_int(linea, 9, i - 9);
            int j = i + 1;
            while (linea[j] >= '0' && linea[j] <= '9') ++j;
            int arg2 = string_to_int(linea, i + 1, j - i - 1);
            s.ELIMINAR(arg1, arg2);
        } else if (linea[0] == 'R' && linea[1] == 'E' && 
                   linea[2] == 'V' && linea[3] == 'E' && 
                   linea[4] == 'R' && linea[5] == 'S' && 
                   linea[6] == 'O') {
            int i = 8;
            while (linea[i] >= '0' && linea[i] <= '9') ++i;
            int arg1 = string_to_int(linea, 8, i - 8);
            int j = i + 1;
            while (linea[j] >= '0' && linea[j] <= '9') ++j;
            int arg2 = string_to_int(linea, i + 1, j - i - 1);
            s.REVERSO(arg1, arg2);
        } else if (linea[0] == 'R' && linea[1] == 'E' && 
                   linea[2] == 'C' && linea[3] == 'O' && 
                   linea[4] == 'R' && linea[5] == 'T' && 
                   linea[6] == 'A' && linea[7] == 'R') {
            s.RECORTAR(); // Utilizar el método RECORTAR
        } else if (linea[0] == 'F' && linea[1] == 'I' && linea[2] == 'N') {
            break;
        } else {
            cout << "Operación no reconocida: " << linea << endl;
        }
    }

    archivo.close(); 
    return 0; 
}