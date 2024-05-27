#include <iostream>
#include <string>

using namespace std;

class super_string {

private:

    struct nodo {
        nodo *left = nullptr, *right = nullptr;
        int index;
        char c;
        nodo(int index, char c) : index(index), c(c) {}
        nodo() : index(0), c('\0') {}
    };

    int height = 0; // Altura del árbol
    int length = 0; // Largo del super-string
    nodo* root = nullptr; // Raíz del super-string

    // Función auxiliar para calcular la altura del árbol
    int calcular_altura_arbol(nodo* node) {
        if (node == nullptr) {
            return -1; // Un nodo nulo tiene altura -1
        } else {
            // Recursivamente calculamos la altura de los subárboles izquierdo y derecho
            int altura_izquierda = calcular_altura_arbol(node->left);
            int altura_derecha = calcular_altura_arbol(node->right);

            // La altura del árbol es la máxima altura de los subárboles más 1
            return 1 + max(altura_izquierda, altura_derecha);
        }
    }

    // Función auxiliar para realizar el recorrido inorder y obtener el super-string
    void inorder(nodo* node, string& result) {
        if (node != nullptr) {
            inorder(node->left, result);
            result += node->c;
            inorder(node->right, result);
        }
    }

    // Función auxiliar para actualizar la altura del árbol
    void actualizar_altura() {
        height = calcular_altura_arbol(root);
    }

public:
    super_string() {}

    // Método para insertar el super-string S en la posición l del super-string actual
    void insertar(int l, const string& S) {
        if (l < 0 || l > length) {
            cout << "Posición de inserción inválida." << endl;
            return;
        }

        // Recorremos los caracteres de S e insertamos cada uno como un nodo del árbol
        for (int i = 0; i < S.size(); ++i) {
            nodo* newNode = new nodo(l + i, S[i]);

            // Si el árbol está vacío, el nuevo nodo será la raíz
            if (root == nullptr) {
                root = newNode;
            } else {
                // Buscamos la posición de inserción para el nuevo nodo
                nodo* current = root;
                nodo* parent = nullptr;
                while (current != nullptr) {
                    parent = current;
                    if (newNode->index < current->index) {
                        current = current->left;
                    } else {
                        current = current->right;
                    }
                }

                // Insertamos el nuevo nodo como hijo izquierdo o derecho del nodo padre
                if (newNode->index < parent->index) {
                    parent->left = newNode;
                } else {
                    parent->right = newNode;
                }
            }

            length++;
        }

        // Actualizar la altura después de la inserción
        actualizar_altura();
    }

    // Método para mostrar el super-string actual
    void mostrar() {
        // Creamos una cadena vacía para almacenar el super-string
        string result;

        // Llamamos a una función auxiliar para realizar un recorrido inorder y obtener el super-string
        inorder(root, result);

        // Mostrar el super-string actual
        cout << "Super-string actual: " << result << endl;
    }

    // Método para mostrar la altura del árbol actual que representa el super-string
    void mostrar_altura() {
        // Mostramos la altura del árbol
        cout << "Altura del árbol actual: " << height << endl;
    }

    // Método para convertir el árbol a string realizando un recorrido inorder
    /*El método stringizar garantiza una complejidad de O(n) debido a que recorre el árbol in-order una vez, visitando cada nodo exactamente una vez.*/
    string stringizar() {
        string result;
        inorder(root, result);
        return result;
    }

    // Implementación de otros métodos aquí...
    void agregar(char c) {
        // Implementación del método agregar
    }

    void juntar(super_string &s) {
        // Implementación del método juntar
    }

    void separar(int i, super_string &a, super_string &b) {
        // Implementación del método separar
    }

    void reverso() {
        // Implementación del método reverso
    }

    int recortar() {
        // Implementación del método recortar
        return height;
    }

    void limpiar() {
        // Implementación del método limpiar
    }
};

int main() {
    super_string s;
    s.insertar(0, "Hola");
    s.mostrar();
    s.mostrar_altura(); // Mostrar altura del árbol
    cout << "Stringizar: " << s.stringizar() << endl; // Mostrar super-string usando stringizar
    return 0;
}
