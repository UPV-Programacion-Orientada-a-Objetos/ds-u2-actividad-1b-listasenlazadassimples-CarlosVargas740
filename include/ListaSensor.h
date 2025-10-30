/**
 * @file ListaSensor.h
 * @brief Lista enlazada genérica para almacenar lecturas de sensores
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef LISTA_SENSOR_H
#define LISTA_SENSOR_H

#include <iostream>

/**
 * @struct Nodo
 * @brief Nodo de lista enlazada genérico
 * @tparam T Tipo de dato a almacenar
 */
template <typename T>
struct Nodo {
    T dato;         ///< Dato almacenado
    Nodo* siguiente; ///< Puntero al siguiente nodo
    
    /**
     * @brief Constructor
     * @param valor Valor a almacenar
     */
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @class ListaSensor
 * @brief Lista enlazada genérica con gestión manual de memoria
 * @tparam T Tipo de dato a almacenar (int, float, etc.)
 * 
 * Implementa la Regla de Tres (constructor copia, operador=, destructor)
 * para gestión correcta de memoria dinámica.
 */
template <typename T>
class ListaSensor {
private:
    Nodo<T>* cabeza;  ///< Puntero al primer nodo
    int cantidad;     ///< Número de elementos
    
    /**
     * @brief Libera toda la memoria de la lista
     */
    void liberar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        cabeza = nullptr;
        cantidad = 0;
    }
    
    /**
     * @brief Copia profunda de otra lista
     * @param otra Lista a copiar
     */
    void copiar(const ListaSensor& otra) {
        if (otra.cabeza == nullptr) {
            cabeza = nullptr;
            cantidad = 0;
            return;
        }
        
        cabeza = new Nodo<T>(otra.cabeza->dato);
        Nodo<T>* actualOtra = otra.cabeza->siguiente;
        Nodo<T>* actualEsta = cabeza;
        
        while (actualOtra != nullptr) {
            actualEsta->siguiente = new Nodo<T>(actualOtra->dato);
            actualEsta = actualEsta->siguiente;
            actualOtra = actualOtra->siguiente;
        }
        
        cantidad = otra.cantidad;
    }
    
public:
    /**
     * @brief Constructor por defecto
     */
    ListaSensor() : cabeza(nullptr), cantidad(0) {}
    
    /**
     * @brief Destructor
     */
    ~ListaSensor() {
        liberar();
    }
    
    /**
     * @brief Constructor de copia (Regla de Tres)
     * @param otra Lista a copiar
     */
    ListaSensor(const ListaSensor& otra) : cabeza(nullptr), cantidad(0) {
        copiar(otra);
    }
    
    /**
     * @brief Operador de asignación (Regla de Tres)
     * @param otra Lista a asignar
     * @return Referencia a esta lista
     */
    ListaSensor& operator=(const ListaSensor& otra) {
        if (this != &otra) {
            liberar();
            copiar(otra);
        }
        return *this;
    }
    
    /**
     * @brief Agrega un elemento al final
     * @param valor Valor a agregar
     */
    void agregar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        
        cantidad++;
    }
    
    /**
     * @brief Calcula el promedio de los valores
     * @return Promedio (tipo T)
     */
    T calcularPromedio() const {
        if (cantidad == 0) return T(0);
        
        T suma = T(0);
        Nodo<T>* actual = cabeza;
        
        while (actual != nullptr) {
            suma = suma + actual->dato;
            actual = actual->siguiente;
        }
        
        return suma / cantidad;
    }
    
    /**
     * @brief Obtiene el número de elementos
     * @return Cantidad de elementos
     */
    int getCantidad() const {
        return cantidad;
    }
    
    /**
     * @brief Imprime todos los valores
     */
    void imprimir() const {
        Nodo<T>* actual = cabeza;
        std::cout << "[";
        while (actual != nullptr) {
            std::cout << actual->dato;
            if (actual->siguiente != nullptr) {
                std::cout << ", ";
            }
            actual = actual->siguiente;
        }
        std::cout << "]";
    }
    
    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía
     */
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

#endif
