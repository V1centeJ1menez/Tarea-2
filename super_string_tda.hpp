#include <string>
#pragma once

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
        int calcular_altura_arbol(nodo* node);

        // Función auxiliar para realizar el recorrido inorder y obtener el super-string
        void inorder(nodo* node, std::string& result); 

        void inorder_count(nodo* node, int& count);

        // Función auxiliar para actualizar la altura del árbol
        void actualizar_altura();
        // Función auxiliar para encontrar el índice mayor en el árbol
        int encontrar_mayor_indice(nodo* node);

        // Función auxiliar para insertar un nodo en el árbol
        void insertar_nodo(nodo*& root, nodo* newNode);

        // Función auxiliar para recorrer el árbol y separar los nodos
        void separar_nodos(nodo* node, int i, super_string& a, super_string& b); 

        nodo* eliminar_nodos_en_rango(nodo* node, int l, int r);

        void construir_reverso(nodo* originalNode, nodo*& newRoot);

        void construir_reverso_intervalo(nodo* originalNode, nodo*& newRoot, int l, int r);

        void inorder_recortar(nodo* node, nodo**& nodes, int& index);

        nodo* construir_arbol_balanceado(nodo** nodes, int start, int end);

        nodo* rotar_derecha(nodo* node);

        nodo* rotar_izquierda(nodo* node);

        nodo* reequilibrar(nodo* node);

        void mover_indices(nodo* node, int start, int amount) ;

    public:

        super_string();

        void mostrar_raiz();

        // Método para insertar el super-string S en la posición l del super-string actual
        void INSERTAR(int l, const std::string& S);
      
        // Método para agregar un carácter en la última posición del super-string
        void agregar(char c); // Insertar un caracter en la última posición

        // Método para mostrar el super-string actual
        void MOSTRAR(); 

        // Método para mostrar la altura del árbol actual que representa el super-string
        void mostrar_altura();

        /*La complejidad del método stringizar debe ser O(n) donde n es la cantidad de nodos.*/
        //Debe retornar un string en vez de un super-tring
        std::string stringizar(); // Debe ser O(n)

         // En la izquierda esta el super_string a y en la derecha el super_string b
        /* Esto le permitirá separar la posición i-esima del super-string devolviendo dos super-strings, uno desde
        el intervalo [0,i) y otro desde el intervalo [i, n). El segundo super-string puede estar vacio*/
        void separar(int i, super_string &a, super_string &b);

        // Método para mostrar la longitud del super-string
        int mostrar_largo();

        // Método para obtener el carácter en la posición i del super-string
        char obtener(int i);

        // Esto le permitirá, dado dos super-strings, obtener un nuevo super-string concatenando el primero con el segundo
        void juntar(super_string &s);

        /*El metodo llamado reverso debe preservar la altura del árbol, es decir, si el árbol tenía
        altura 5, la aplicación de la funcion no debe cambiar dicha altura.
        Dado un super-string debe revertir los índices. Es decir, si un super-string se lee como "ABCD", el reverso del mismo string es "DCBA"*/
        void reverso(); // No debe cambiar la altura del árbol

        void REVERSO(int l, int r);

        /* El metodo recortar apela a la creatividad. Es posible que, comparando su tarea con la de
        sus pares, encuentren que su funciones recortar obtengan distintas alturas. En este sentido
        basta con que dichas alturas sean a lo más O(log n), donde n es la cantidad de nodos.
        Deben explicar, comentando el código de la función, porqué creen que el método cumple
        con esa complejidad.
        
        El super-string puede estar representado de una forma que el camino más
        largo desde la raíz del arbol de busqueda binaria a algún nodo tome una cantidad de O(n)
        pasos. La función recortar debe permitir pasar esta operación a O(logn) pasos siempre y
        cuando no se ha insertado ningún nodo desde ese entonces.
        Un ejemplo de un árbol que toma O(n) pasos para encontrar un nodo se da cuando se
        intenta crear un árbol de busqueda binaria insertando los siguientes valores en orden:
        1,2,3,4,5 y 6
        Se asegura que para cualquier lista de nodos existe una disposición donde el camino desde
        la raíz hasta el nodo más lejano es O(logn).
        Es importante remarcar que la operación no debe realizar cambios en los nodos, estos
        deben ser los mismos previos a la operación. Los cambios deben realizarse en términos de
        la estructura del árbol.*/

        int recortar(); // Retorna this->height después de recortar

        void RECORTAR(); // Tiene que recortar el árbol y luego mostrar la altura por pantalla

        void borrar_nodos(nodo* node);

        void limpiar(); // Se deben borrar todos los nodos del super-string

        void ELIMINAR(int l, int r);
};