#include <iostream>
#include <string>
#include "super_string_tda.hpp"

using namespace std;

//---- METODOS TDA-SUPER STRINGS ----//

/*Privados*/

int super_string::calcular_altura_arbol(nodo* node){

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

void super_string::inorder(nodo* node,string& result){

    if (node != nullptr) {
        inorder(node->left, result);
        result += node->c;
        inorder(node->right, result);
    }
}

void super_string::actualizar_altura(){ this->height = calcular_altura_arbol(root); }

int super_string::encontrar_mayor_indice(nodo* node){

    while (node->right != nullptr) {
            node = node->right;
        }
    return node->index;
}

void super_string::insertar_nodo(nodo*& root, nodo* newNode){

    if (root == nullptr) {
        root = newNode;
    } else {
        if (newNode->index < root->index) {
            insertar_nodo(root->left, newNode);
        } else {
            insertar_nodo(root->right, newNode);
        }
    }
}

void super_string::separar_nodos(nodo* node, int i, super_string& a, super_string& b){
    if (node != nullptr) {
            separar_nodos(node->left, i, a, b);

            nodo* newNode = new nodo(node->index, node->c);
            if (node->index < i) {
                insertar_nodo(a.root, newNode);
                a.length++;
            } else {
                insertar_nodo(b.root, newNode);
                b.length++;
            }

            separar_nodos(node->right, i, a, b);
        }
}

void super_string::borrar_nodos(nodo* node){
    if (node != nullptr) {
        // Llamamos recursivamente para los subárboles izquierdo y derecho
        borrar_nodos(node->left);
        borrar_nodos(node->right);

        // Borramos el nodo actual
        delete node;
    }
}

 // Función auxiliar para eliminar nodos en un rango
super_string::nodo* super_string::eliminar_nodos_en_rango(nodo* node, int l, int r) {
    if (node == nullptr) return nullptr;

    // Primero recorremos el subárbol izquierdo y derecho
    node->left = eliminar_nodos_en_rango(node->left, l, r);
    node->right = eliminar_nodos_en_rango(node->right, l, r);

    // Si el índice del nodo está en el rango [l, r], eliminamos el nodo
    if (node->index >= l && node->index <= r) {
        nodo* temp = nullptr;
        if (node->left == nullptr) {
            temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            temp = node->left;
            delete node;
            return temp;
        } else {
            // Nodo con dos hijos: obtenemos el sucesor en el inorder (el más pequeño en el subárbol derecho)
            nodo* sucesor = node->right;
            while (sucesor->left != nullptr) {
                sucesor = sucesor->left;
            }

            // Copiamos el contenido del sucesor al nodo actual
            node->index = sucesor->index;
            node->c = sucesor->c;

            // Eliminamos el sucesor
            node->right = eliminar_nodos_en_rango(node->right, sucesor->index, sucesor->index);
        }
    }
    return node;
}

void super_string::construir_reverso(nodo* originalNode, nodo*& newRoot) {
    if (originalNode != nullptr) {
        // Recorremos el árbol en orden inverso: derecha, raíz, izquierda
        construir_reverso(originalNode->right, newRoot);

        // Creamos un nuevo nodo con el índice y el carácter invertidos
        nodo* newNode = new nodo(length - originalNode->index - 1, originalNode->c);
        
        // Insertamos el nuevo nodo en el árbol invertido
        insertar_nodo(newRoot, newNode);

        // Llamamos recursivamente para el subárbol izquierdo
        construir_reverso(originalNode->left, newRoot);
    }
}

void super_string::construir_reverso_intervalo(nodo* originalNode, nodo*& newRoot, int l, int r) {
    if (originalNode != nullptr) {
        // Recorremos el árbol en orden inverso: derecha, raíz, izquierda
        construir_reverso_intervalo(originalNode->right, newRoot, l, r);

        // Si el índice del nodo está en el rango [l, r], invertimos su posición
        if (originalNode->index >= l && originalNode->index <= r) {
            nodo* newNode = new nodo(originalNode->index, originalNode->c);
            newNode->index = r - (originalNode->index - l);
            insertar_nodo(newRoot, newNode);
        } else {
            // Si el nodo no está en el rango, lo copiamos tal cual al nuevo árbol
            nodo* newNode = new nodo(originalNode->index, originalNode->c);
            insertar_nodo(newRoot, newNode);
        }

        // Llamamos recursivamente para el subárbol izquierdo
        construir_reverso_intervalo(originalNode->left, newRoot, l, r);
    }
}

// Función auxiliar para realizar un recorrido inorder y obtener los nodos del árbol en un array
void super_string::inorder_recortar(nodo* node, nodo**& nodes, int& index) {
    if (node != nullptr) {
        inorder_recortar(node->left, nodes, index);
        nodes[index++] = node;
        inorder_recortar(node->right, nodes, index);
    }
}

// Función auxiliar para construir un árbol AVL balanceado a partir de un array de nodos

// Función auxiliar para construir un árbol balanceado a partir de un array de nodos
super_string::nodo* super_string::construir_arbol_balanceado(nodo** nodes, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    // Encontrar el punto medio del rango y crear un nodo con él
    int mid = (start + end) / 2;
    nodo* newNode = new nodo(nodes[mid]->index, nodes[mid]->c);

    // Construir recursivamente el subárbol izquierdo y derecho
    newNode->left = construir_arbol_balanceado(nodes, start, mid - 1);
    newNode->right = construir_arbol_balanceado(nodes, mid + 1, end);

    return newNode;
}

// Método para realizar una rotación a la derecha
super_string::nodo* super_string::rotar_derecha(nodo* node) {
    nodo* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

// Método para realizar una rotación a la izquierda
super_string::nodo* super_string::rotar_izquierda(nodo* node) {
    nodo* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

// Método para reequilibrar un subárbol
super_string::nodo* super_string::reequilibrar(nodo* node) {
    // Calculamos la altura de los subárboles izquierdo y derecho
    int altura_izquierda = calcular_altura_arbol(node->left);
    int altura_derecha = calcular_altura_arbol(node->right);

    // Si el subárbol izquierdo es más alto, aplicamos rotaciones a la derecha
    if (altura_izquierda - altura_derecha > 1) {
        // Aplicamos rotación a la derecha si es necesario
        if (calcular_altura_arbol(node->left->left) < calcular_altura_arbol(node->left->right)) {
            node->left = rotar_izquierda(node->left);
        }
        // Realizamos la rotación a la derecha
        node = rotar_derecha(node);
    }
    // Si el subárbol derecho es más alto, aplicamos rotaciones a la izquierda
    else if (altura_derecha - altura_izquierda > 1) {
        // Aplicamos rotación a la izquierda si es necesario
        if (calcular_altura_arbol(node->right->right) < calcular_altura_arbol(node->right->left)) {
            node->right = rotar_derecha(node->right);
        }
        // Realizamos la rotación a la izquierda
        node = rotar_izquierda(node);
    }
    return node;
}

void super_string::mover_indices(nodo* node, int start, int amount) {
    if (node == nullptr) {
        return;
    }

    // Si el índice del nodo es mayor o igual al índice de inicio, lo movemos
    if (node->index >= start) {
        node->index += amount;
    }

    // Llamamos recursivamente para los hijos izquierdo y derecho
    mover_indices(node->left, start, amount);
    mover_indices(node->right, start, amount);
}



/*Publicos*/

super_string::super_string(){}

void super_string::mostrar_raiz() {
    if (root != nullptr) {
        cout << "La raíz del árbol es: (" << root->index << ", '" << root->c << "')" << endl;
    } else {
        cout << "El árbol está vacío." << endl;
    }
}

void super_string::INSERTAR(int l, const string& S) {
    if (l < 0 || l > length) {
        cout << "Posición de inserción inválida." << endl;
        return;
    }

    // Primero, ajustamos los índices de los nodos existentes en el árbol para hacer espacio
    mover_indices(root, l, S.size());

    // Luego, recorremos los caracteres de S e insertamos cada uno como un nodo del árbol
    for (std::string::size_type i = 0; i < S.size(); ++i) {
        nodo* newNode = new nodo(l + i, S[i]);
        insertar_nodo(root, newNode);
    }

    // Actualizamos la longitud y la altura después de la inserción
    length += S.size();
    actualizar_altura();
}


void super_string::agregar(char c){

    int nuevo_indice = length;
        nodo* newNode = new nodo(nuevo_indice, c);

        if (root == nullptr) {
            root = newNode;
        } else {
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

            if (newNode->index < parent->index) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }

        length++;
        actualizar_altura();

}

void super_string::MOSTRAR() {
    // Verificar si el árbol está vacío
    if (root == nullptr) {
        cout << "El árbol está vacío." << endl;
        return;
    }

    // Creamos una cadena vacía para almacenar el super-string
    string result;

    // Llamamos a una función auxiliar para realizar un recorrido inorder y obtener el super-string
    inorder(root, result);

    // Mostrar el super-string actual
    cout << "Super-string actual: " << result << endl;
}

void super_string::mostrar_altura(){

    // Mostramos la altura del árbol
    cout << "Altura del árbol actual: " << height << endl;
}

string super_string::stringizar(){
    string result;
    inorder(root, result);
    return result;
}

void super_string::separar(int i, super_string &a, super_string &b){
    separar_nodos(root, i, a, b);
    a.actualizar_altura();
    b.actualizar_altura();
};

int super_string::mostrar_largo(){
    return length;
}

char super_string::obtener(int i) {
    // Buscamos el nodo con índice i en el árbol
    nodo* current = root;
    while (current != nullptr) {
        if (i == current->index) {
            return current->c; // Retornamos el carácter del nodo encontrado
        } else if (i < current->index) {
            current = current->left; // Buscamos en el subárbol izquierdo
        } else {
            current = current->right; // Buscamos en el subárbol derecho
        }
    }
    
    return '\0'; // Si no se encuentra el nodo, retornamos un carácter nulo
}

void super_string::juntar(super_string &s){
    // Obtenemos el índice mayor en el árbol actual
    int max_index = encontrar_mayor_indice(root);

    // Insertamos el super-string s en el árbol
     for (int i = 0; i < s.length; ++i) {
            char c = s.obtener(i); // Obtenemos el carácter en la posición i de s
            nodo* newNode = new nodo(max_index + i + 1, c); // Creamos un nuevo nodo con el índice adecuado
            insertar_nodo(root, newNode); // Insertamos el nuevo nodo en el árbol actual
            length++; // Incrementamos la longitud del super-string
        }

        // Actualizamos la altura del árbol
        actualizar_altura();

}

void super_string::reverso() {
    // Creamos un nuevo árbol para almacenar el super-string invertido
    nodo* newRoot = nullptr;
    // Construimos el árbol invertido recursivamente
    construir_reverso(root, newRoot);
    // Asignamos el nuevo árbol invertido como el árbol actual
    root = newRoot;
}

void super_string::REVERSO(int l, int r) {
    if (l < 0 || r >= length || l >= r) {
        cout << "Índices de reverso inválidos." << endl;
        return;
    }
    
    // Creamos un nuevo árbol para almacenar el super-string invertido
    nodo* newRoot = nullptr;
    // Construimos el árbol con reverso dentro del intervalo
    construir_reverso_intervalo(root, newRoot, l, r);
    // Asignamos el nuevo árbol invertido como el árbol actual
    root = newRoot;
}


// Método para recortar el árbol y reequilibrarlo
int super_string::recortar() {
    // Paso 1: Obtener los nodos del árbol en orden
    nodo** nodes = new nodo*[length];
    int index = 0;
    inorder_recortar(root, nodes, index);

    // Paso 2: Construir un nuevo árbol balanceado a partir de los nodos
    root = construir_arbol_balanceado(nodes, 0, length - 1);

    // Paso 3: Reequilibrar el árbol
    root = reequilibrar(root);

    // Actualizar la altura del árbol después del recorte
    actualizar_altura();

    // Liberar memoria asignada a nodos auxiliares
    delete[] nodes;

    // Devolver la altura del árbol
    return this->height;
}

// Método para ejecutar la operación RECORTAR y mostrar la altura del árbol
void super_string::RECORTAR() {
    // Ejecutar el método recortar() para balancear el árbol
    int new_height = recortar();

    // Mostrar la nueva altura del árbol después de recortar
    std::cout << new_height << std::endl;
}

void super_string::limpiar(){
    borrar_nodos(root);
    root = nullptr;
    length = 0;
    height = 0;
}

void super_string::ELIMINAR(int l, int r) {
    // Verificar si los índices son válidos y si r no es menor que l
    if (l < 0 || r >= length || l > r) {
        cout << "Índices de eliminación inválidos." << endl;
        return;
    }

    // Eliminar los nodos en el rango [l, r]
    root = eliminar_nodos_en_rango(root, l, r);

    // Actualizar la longitud y la altura del árbol después de la eliminación
    length -= (r - l + 1);
    actualizar_altura();
}
