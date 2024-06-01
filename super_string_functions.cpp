#include <iostream>
#include <string>
#include <cctype>
#include "super_string_tda.hpp"

using namespace std;

//---- METODOS TDA-SUPER STRINGS ----//

/*Privados*/

/*****
* int calcular_altura_arbol******
* Funcion que calcula la altura de un arbol de manera recursiva, calcula la altura del sub-arbol derecho y del sub-arbol izquierdo
* la altura del arbol es la altura del sub-arbol mayor mas 1, en caso de ser un arbol nulo, la altura es -1.
******
* Input:
* Puntero tipo nodo node : Puntero al nodo desde donde se calcula la altura.
* .......
******
* Returns:
* int, Retorna la altura maxima de los sub-arboles mas 1, que corresponde a la altura total del arbol.
*****/

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

/*****
* void inorder******
* Visita de manera recursiva los nodos de una arbol y almacena los caracteres en el string 'result', la visita a los nodos es 
* de manera 'in-order' esto asegura que el orden de la funcion sea de O(n), ya que visita cada nodo una vez.
******
* Input:
* Puntero tipo nodo node : Puntero hacia el nodo donde se incia la funcion.
* string result: String pasado por referencia donde se almacenaran los valores de los caracteres del arbol.
* .......
******
* Returns:
* void, Al ser una funcion del tipo voi no retorna nada, solo modifica el string pasado por referencia y almacena los caracteres
* del arbol.
*****/

void super_string::inorder(nodo* node,string& result){

    if (node != nullptr) {
        inorder(node->left, result);
        result += node->c;
        inorder(node->right, result);
    }
}

/*****
* void actualizar_altura******
* Actualiza la altura del arbol mediante la funcion calcular_altura_arbol.
******
* Input:
* No recibe parametros de entrada
* .......
******
* Returns:
* void, al ser una funcion del tipo void no retorna nada, solamente actualiza la altura del arbol.
*****/

void super_string::actualizar_altura(){ this->height = calcular_altura_arbol(root); }

/*****
* int encontrar_mayor_indice******
* Encuentra el mayor nodo del arbol binario recorriendo el arbol hacia la derecha de manera recursiva.
******
* Input:
* puntero tipo nodo node : Puntero hacia el nodo desde donde empieza la funcion.
* .......
******
* Returns:
* int, Retorna el indice del mayor nodo en el arbol.
*****/
int super_string::encontrar_mayor_indice(nodo* node){

    while (node->right != nullptr) {
            node = node->right;
        }
    return node->index;
}
/*****
* void insertar_nodo******
* Inserta un nuevo nodo al arbol evaluando de manera recursiva el valor del nodo nuevo en comparacion con los otros nodos. Si es menor
* el valor inserta hacia la izquierda, si es mayor el valor inserta hacia la derecha.
******
* Input:
* Puntero tipo nodo root : Puntero hacia la raiz del arbol 
* Puntero tipo nodo newNode : Puntero hacia el nuevo nodo que se insertara.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, solo inserta un nuevo nodo en el arbol, y si el arbol esta vacio
* inserta el nodo como root.
*****/
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
/*****
* void separar_nodos******
* Recorre el artbol de manera recursiva para separarlo en dos subarboles 'a' y 'b' con respecto al indice entregado 'i'
******
* Input:
* Puntero tipo nodo node: un puntero al nodo actual del arbol que se esta procesando.
* int i: indice entregado para separar los subarboles respecto a este mismo.
* super_string a: referencia a un super string 'a' donde se insertan los nodos con indice menor a 'i'.
* super_string b: referencia a un super string 'b' donde se insertan los nodos con indice mayor a 'i'.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void,  no retorna nada, solo modifica los super_strings 'a' y 'b' con los valores dados.
*****/
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

/*****
* void borrar_nodos******
* La funcion se encarga de borrar los sub-arboles de manera recursiva hasta que solamente queda el nodo raiz 
* y despues lo eliminan.
******
* Input:
* Puntero tipo nodo node : Puntero hacia el nodo del arbol donde empieza la funcion.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, solamente actualiza los valores del arbol, dejandolo vacio. 
*****/

void super_string::borrar_nodos(nodo* node){
    if (node != nullptr) {
        // Llamamos recursivamente para los subárboles izquierdo y derecho
        borrar_nodos(node->left);
        borrar_nodos(node->right);

        // Borramos el nodo actual
        delete node;
    }
}
/*****
* super_string::nodo* eliminar_nodos_en_rango******
* Elimina los nodos que se encuentren entre el rango de los rangos de indices entregados. el int 'l' es el rango inferior y el }
* int 'r' es el rango superior
******
* Input:
* Puntero tipo nodo node : Un puntero al nodo actual en el árbol binario. Es el nodo desde el cual comenzará el proceso de eliminación.
* int l : El limite inferior del rango de indices de los nodos por eliminar.
* int r : El limite superiro del rango de indices de los nodos por eliminar.
* .......
******
* Returns:
* Puntero de tipo nodo, Un puntero a la nueva raiz del sub arbol modificado despues de la funcion.
*****/

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

/*****
* void contruir_reverso******
* Recorre un arbol de manera inversa, es decir, derecha -> raiz -> izquierda, y construye un arbol con los indices invertidos. 
* Recorre cada sub-arbol de manera recursiva.
******
* Input:
* Puntero de tipo nodo originalNode : El nodo actual del arbol original que se esta procesando.
* Puntero de tipo nodo newRoot : La raiz del nuevo arbol invertido.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, el nuevo arbol se forma modificando el parametro 'newRoot' pasado por 
* referencia.
*****/

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

/*****
* void contruir_reverso_intervalo******
* Construye un arbol binario a partir de una arbol original, invirtiendo los indices de los nodos que estan dentro
* de lo rangos 'l' y 'r' 
******
* Input:
* Puntero tipo nodo originalNode : El nodo actual del arbol original que se esta procesando.
* Puntero tipo nodo newRoot : La raiz del nuevo arbol, se actualiza recursivamente para contruir el nuevo arbol.
* int l : EL limite inferior del rango de indices que deben ser invertidos
* int r : El limite superior del rango de indices que deben ser invertidos.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, el nuevo arbol se ontruye modificando el parametro 'newRoot'.
*****/

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

/*****
* void inorder_recortar******
* Realiza un recorrido inorden del arbol binario y almacena los punteros a los nodos en el arreglo 'nodes', 
* incrementa el 'index' cada vez que se almacena un nodo.
******
* Input:
* Puntero tipo nodo node : El nodo actual del arbol que se esta procesando.
* Puntero tipo nodo nodes : Un arreglo que almacenara los punteros a los nodos en el orden inorder.
* Referencia a entero index : Un indice que se incrementa cada vez que se almacena un puntero a un nodo en el arreglo.
* .......
******
* Returns:
* vopid, Al ser una funcion del tipo void no retorna nada, actualiza los valores almacenados en el arreglo 'nodes' e incrementa
* el valor de 'index'.
*****/

void super_string::inorder_recortar(nodo* node, nodo**& nodes, int& index) {
    if (node != nullptr) {
        inorder_recortar(node->left, nodes, index);
        nodes[index++] = node;
        inorder_recortar(node->right, nodes, index);
    }
}

/*****
* super_string::nodo* contruir_arbol_balanceado******
* El proposito de la funcion es construir un arbol binario balanceado a partir de un arreglo de nodos ordenados
******
* Input:
* Puntero tipo nodo nodes : Un puntero al arreglo de punteros a nodos, contiene los nodos ordenados que se usan para 
* contruir el arbol balanceado.
* int start : El indice de incio del rango del arreglo que se utilizara para construir el arbol.
* int end : El indice de fin del rango del arreglo que se utilizara para construir el arbol.
* .......
******
* Returns:
* Puntero a nodo, El nodo representa la raiz del nuevo arbol balanceado construido por la funcion.
*****/


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

/*****
* super_string::nodo* rotar_derecha******
* Metodo que permite realizar una rotacion de los nodos hacia la derecha para mantener el arbol balanceado.
******
* Input:
* Puntero de tipo nodo node : Un puntero al nodo que se rotara hacia la derecha
* .......
******
* Returns:
* Puntero a nodo, Este puntero representa la nueva raiz del subarbol despues de la rotacion
*****/

super_string::nodo* super_string::rotar_derecha(nodo* node) {
    nodo* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

/*****
* super_string::nodo* rotar_izquierda******
* Metodo que permite realizar una rotacion de los nodos hacia la izquierda para mantener el arbol balanceado.
******
* Input:
* Puntero de tipo nodo node : Un puntero al nodo que se rotara hacia la izquierda.
* .......
******
* Returns:
* Puntero a nodo, Este puntero representa la nueva raiz del subarbol despues de la rotacion
*****/

super_string::nodo* super_string::rotar_izquierda(nodo* node) {
    nodo* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

/*****
* super_string::nodo* reequilibrar******
* Funcion que ajusta las alturas de los subarboles para mantener el balanceo de un arbol AVL, aplicando
* rotaciones cuando es necesario.
******
* Input:
* Puntero tipo nodo node : Un puntero al nodo que se va a equilibrar.
* .......
******
* Returns:
* super_string::nodo, Retorna un puntero a un nodo que representa la nueva raiz del subarbol depsues del reequilibrio.
*****/

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

/*****
* void mover_indices******
* Funcion que se aplica a los nodos de un arbol para ajustar sus indices, sumando un valor a los nodos que de indice mayor o igual que el valor dado.
******
* Input:
* Puntero tipo nodo node : Puntero al nodo actual que esta siendo procesado.
* int start : El indice a partir del cual los nodos deben ser movidos.
* int amount : La cantidad que se sumara a los indices de los nodos que cumplen con la condicion.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, solo modifica los indices de los nodos.
*****/

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

/*****
* void mostrar_raiz******
* Muestra la raiz del arbol orignal por pantalla, si el arbol se encuentra vacio muestr un mensaje de aviso.
******
* Input:
* No recibe parametros de entrada.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada, solo muestra por pantalla el contenido de la raiz del arbol.
*****/

void super_string::mostrar_raiz() {
    if (root != nullptr) {
        cout << "La raíz del árbol es: (" << root->index << ", '" << root->c << "')" << endl;
    } else {
        cout << "El árbol está vacío." << endl;
    }
}
/*****
* void Insertar******
* Inserta los caracteres de un string dado como nuevos nodos en el arbol
******
* Input:
* int l : indice de posicion en el cual se inserta el string dado.
* string S : string que se inserta en el arbol desde la posicion l
* .......
******
* Returns:
* void, Al ser una funcion del tipo void, no retorna nada, solo actualiza los valores de longitud y altura del arbol despues de la insercion.
*****/
void super_string::INSERTAR(int l, const string& S) {
    if (l < 0 || l > length) {
        cout << "Posición de inserción inválida." << endl;
        return;
    }
    int count_char_invalido = 0;
    // Primero, ajustamos los índices de los nodos existentes en el árbol para hacer espacio
    mover_indices(root, l, S.size());

    // Luego, recorremos los caracteres de S e insertamos cada uno como un nodo del árbol
    for (std::string::size_type i = 0; i < S.size(); ++i) {
        char c = S[i];
        if (isalpha(c)|| c ==' '|| c =='_'){
            nodo* newNode = new nodo(l + i, S[i]);
            insertar_nodo(root, newNode);
        } else{
            count_char_invalido ++;
        }
    }

    // Actualizamos la longitud y la altura después de la inserción
    length += (S.size() - count_char_invalido);
    actualizar_altura();
}

/*****
* void agregar******
* Agrega un caracter dado como nuevo nodo al final del arbol.
******
* Input:
* char c : Caracter que se inserta al final del super string.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void, no retorna nada, solo actualiza los valores de longitud y altura del arbol.
*****/

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

/*****
* void MOSTRAR******
* Muestra por pantalla el super string, si este esta vacio  muestra un mensaje de aviso.
******
* Input:
* No recibe parametro de entrada.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, muestra por pantalla el super_string actual.
*****/

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

/*****
* void mostrar_altura******
* Muestra la altura del arbol por pantalla.
******
* Input:
* No recibe parametros de entrada.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, muestra por pantalla la altura del arbol.
*****/

void super_string::mostrar_altura(){
    cout << "Altura del árbol actual: " << height << endl;
}

/*****
* string stringizar******
* Toma el super_string y lo convierte en un string normal, hace un recorrido del arbol en inorder para extraer los caracteres de cada nodo.
******
* Input:
* No recibe parametros de entrada.
* .......
******
* Returns:
* string, Retorna el string obtenido al recorrer el arbol en inorden.
*****
* Comentarios:
* Nos aseguramos de que la complejidad de este metodo es de orden 𝑂(𝑛) ya que hacemos un recorrido inorder para recorrer el arbol del super_string
* y transformarlo en string. El recorrido inorder solamente visita los nodos una vez respetando asi el orden 𝑂(𝑛) donde n es el numero de nodos.
*******/

string super_string::stringizar(){
    string result;
    inorder(root, result);
    return result;
}

/*****
* void separar******
* Utiliza la funcion separar_nodos para separar un super_string en dos super_strings 'a' y 'b', los separa segun el indice i entregado.
* en el sub-arbol 'a' quedan los nodos inferiores a i y en el sub-arbol 'b' quedan los nodos superiores a i.
******
* Input:
* int i : Indice con el cual se separan los dos super_strings.
* super_string a : Super_string donde se almacenan los nodos menores a i.
* super_  // Mostramos la altura del árbolstring b : Super_string donde se almacenan los nodos mayores a i.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, modifica los dos super_string entregados 'a' y 'b' y actualiza sus alturas.
*****/

void super_string::separar(int i, super_string &a, super_string &b){
    separar_nodos(root, i, a, b);
    a.actualizar_altura();
    b.actualizar_altura();
}

/*****
* int mostrar_largo******
* Muestra por pantalla el largo del arbol.
******
* Input:
* No recibe parametros de entrada
* .......
******
* Returns:
* int, Retorna el entero correspondiente al largo del arbol.
*****/

int super_string::mostrar_largo(){
    return length;
}

/*****
* char obtener******
* Buscamos el caravter correspondiente al indice i dentro del arbol y lo retornamos como caracter.
******
* Input:
* int i : Indice i correspondiente al caracter que se desea obtener del arbol.
* .......
******
* Returns:
* char, Caracter correspondiente con el indice i, si el nodo no se encuentra, se retorna un nodo nulo.
*****/

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

/*****
* void juntar******
* Junta un super_string dado con un arbol ya existente, modifica los indices de los nuevos nodos para que sean los adecuados.
* Finalmente actuliza la altura del arbol e incrementa la longitud del super_string
******
* Input:
* super_string s : super_String que se anexara con el arbol general.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada. Modifica los parametros del arbol a medida que se anexa el super_string.
*****/

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

/*****
* void reverso******
* Utiliza la funcion construir_reverso para recorrer el arbol de manera inversa y almacena los datos invertidos. Al final asigna el nuevo
* arbol invertido como el arbol actual. 
******
* Input:
* No recibe parametros de entrada.
* .......
******
* Returns:
* void, AL ser una funcion de tipo void no retorna nada, crea un arbol invertido y despues lo asigna como el arbol actual.
*****
* Comentarios:
* La funcion no modifica la altura del arbol porque el proceso de construccion del arbol invertido preserva 
* la profundidad de los nodos. Solamente intercambia los subarboles izquierdo y derecho de cada nodo, lo que 
* no afecta la longitud de los caminos desde la raiz hasta cualquier hoja.
*******/

void super_string::reverso() {
    // Creamos un nuevo árbol para almacenar el super-string invertido
    nodo* newRoot = nullptr;
    // Construimos el árbol invertido recursivamente
    construir_reverso(root, newRoot);
    // Asignamos el nuevo árbol invertido como el árbol actual
    root = newRoot;
}

/*****
* void REVERSO******
* La funcion invierte los elementos de un arbol dentro de un intervalo de indices especificos.
******
* Input:
* int 'l' : El indice inicial del intervalo para la operacion de reverso.
* int 'r' : El indice final del intervalo para la operacion de reverso.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, solo invierte los elementos dentro del intervalo dado
*****/

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

/*****
* int recortar******
* Se almacenan los nodos en un arreglo dinamico con la funcion inorder_recortar. Se utiliza la 
* funcion contruir_arbol_balanceado para crear un arbol nuevo y balanceado con el arreglo de nodos.
* Se actualiza la altura del nuevo arbol desde la raiz y se retorna esta misma.
******
* Input:
* No tiene parametros de entrada, modifica parametros de la clase super_string.
* .......
******
* Returns:
* int, Retorna la altura del arbol despues de haber sido recortado y balanceado.
*****
* Comentarios:
* La funcion transforma el arbol original en un arbol balanceado utilizando una lista de nodos ordenados
* y un proceso de construccion recursivo. Debido a que un arbol balanceado tiene altura 𝑂(log 𝑛), se puede concluir
* que despues de ejecutar la funcion, la altura del arbol será, a lo más, 𝑂(log 𝑛).
*
*****/

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

/*****
* void RECORTAR******
* Esta funcion utiliza la funcion recortar para obtener la nueva altura de un arbol recortado
* Muestra por pantalla la nueva altura del arbol
******
* Input:
* No recibe parametros de entrada.
* .......
******
* Returns:
* void, Al ser una funcion del tipo void no retorna nada. Recorta el arbol original y muestra por pantalla la nueva altura.
*****/


void super_string::RECORTAR() {
    // Ejecutar el método recortar() para balancear el árbol
    int new_height = recortar();

    // Mostrar la nueva altura del árbol después de recortar
    std::cout << new_height << std::endl;
}

/*****
* void limpiar******
* Reinicia el arbol completo borrando los nodos con la funcion borrar_nodos y reinicia la raiz como nullptr
******
* Input:
* No recibe parametros de entrada solo modifica el arbol original.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, solo reinicia los parametros del arbol original.
*****/

void super_string::limpiar(){
    borrar_nodos(root);
    root = nullptr;
    length = 0;
    height = 0;
}

/*****
* void ELIMINAR******
* Elimina los nodos que se encuentren entre el rango dado, utilizando la funcion eliminar_nodos_en_rango. 
* Finalmente actualiza la altura del arbol.
******
* Input:
* int l : Indice inferior desde donde se eliminan los nodos
* int r : Indice superior desde donde se eliminan los nodos.
* .......
******
* Returns:
* void, Al ser una funcion de tipo void no retorna nada, solamente modifica los nodos del arbol original.
*****/

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
