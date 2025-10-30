/**
 * @file ListaGestion.h
 * @brief Lista polimórfica para gestionar sensores
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef LISTA_GESTION_H
#define LISTA_GESTION_H

#include "SensorBase.h"
#include <iostream>

/**
 * @struct NodoSensor
 * @brief Nodo que almacena punteros a sensores (polimórfico)
 */
struct NodoSensor {
    SensorBase* sensor;     ///< Puntero polimórfico a sensor
    NodoSensor* siguiente;  ///< Siguiente nodo
    
    /**
     * @brief Constructor
     * @param s Puntero al sensor
     */
    NodoSensor(SensorBase* s) : sensor(s), siguiente(nullptr) {}
};

/**
 * @class ListaGestion
 * @brief Lista enlazada de sensores con gestión polimórfica
 * 
 * Almacena punteros a SensorBase, permitiendo procesamiento
 * uniforme de diferentes tipos de sensores.
 */
class ListaGestion {
private:
    NodoSensor* cabeza;  ///< Primer nodo
    int cantidad;        ///< Número de sensores
    
    /**
     * @brief Libera memoria de todos los sensores
     */
    void liberar() {
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            NodoSensor* temp = actual;
            actual = actual->siguiente;
            delete temp->sensor;  // Llama al destructor virtual
            delete temp;
        }
        cabeza = nullptr;
        cantidad = 0;
    }
    
public:
    /**
     * @brief Constructor
     */
    ListaGestion() : cabeza(nullptr), cantidad(0) {}
    
    /**
     * @brief Destructor
     */
    ~ListaGestion() {
        liberar();
    }
    
    /**
     * @brief Agrega un sensor a la lista
     * @param sensor Puntero al sensor (será propiedad de la lista)
     */
    void agregarSensor(SensorBase* sensor) {
        NodoSensor* nuevo = new NodoSensor(sensor);
        
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            NodoSensor* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        
        cantidad++;
    }
    
    /**
     * @brief Busca un sensor por ID
     * @param id Identificador a buscar
     * @return Puntero al sensor o nullptr si no existe
     */
    SensorBase* buscarPorId(const char* id) {
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            if (strcmp(actual->sensor->getId(), id) == 0) {
                return actual->sensor;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    
    /**
     * @brief Procesa todos los sensores (polimórfico)
     * 
     * Llama a procesarLectura() de cada sensor mediante
     * despachado dinámico (virtual).
     */
    void procesarTodosSensores() {
        if (cantidad == 0) {
            std::cout << "\nNo hay sensores registrados" << std::endl;
            return;
        }
        
        std::cout << "\n=== Procesando " << cantidad << " sensores ===" << std::endl;
        
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            std::cout << "\nSensor: " << actual->sensor->getId() << std::endl;
            actual->sensor->procesarLectura();  // Llamada polimórfica
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Muestra información de todos los sensores
     */
    void mostrarTodos() const {
        if (cantidad == 0) {
            std::cout << "\nNo hay sensores registrados" << std::endl;
            return;
        }
        
        std::cout << "\n=== Sensores registrados: " << cantidad << " ===" << std::endl;
        
        NodoSensor* actual = cabeza;
        while (actual != nullptr) {
            actual->sensor->imprimirInfo();  // Llamada polimórfica
            actual = actual->siguiente;
        }
    }
    
    /**
     * @brief Obtiene la cantidad de sensores
     * @return Número de sensores
     */
    int getCantidad() const {
        return cantidad;
    }
};

#endif
