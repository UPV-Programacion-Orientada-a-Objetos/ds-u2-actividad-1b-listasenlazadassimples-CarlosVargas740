/**
 * @file SensorBase.h
 * @brief Clase base abstracta para todos los sensores
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <iostream>
#include <cstring>

/**
 * @class SensorBase
 * @brief Clase abstracta que define la interfaz para todos los sensores
 * 
 * Esta clase utiliza polimorfismo para permitir procesamiento uniforme
 * de diferentes tipos de sensores a través de métodos virtuales puros.
 */
class SensorBase {
protected:
    char* id;           ///< Identificador único del sensor
    char* ubicacion;    ///< Ubicación física del sensor
    
public:
    /**
     * @brief Constructor parametrizado
     * @param id Identificador del sensor
     * @param ubi Ubicación del sensor
     */
    SensorBase(const char* id, const char* ubi) {
        this->id = new char[strlen(id) + 1];
        strcpy(this->id, id);
        
        this->ubicacion = new char[strlen(ubi) + 1];
        strcpy(this->ubicacion, ubi);
    }
    
    /**
     * @brief Destructor virtual (crítico para polimorfismo)
     */
    virtual ~SensorBase() {
        delete[] id;
        delete[] ubicacion;
    }
    
    /**
     * @brief Procesa una lectura del sensor (método virtual puro)
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Imprime información del sensor (método virtual puro)
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * @brief Obtiene el ID del sensor
     * @return Puntero al identificador
     */
    const char* getId() const { return id; }
    
    /**
     * @brief Obtiene la ubicación del sensor
     * @return Puntero a la ubicación
     */
    const char* getUbicacion() const { return ubicacion; }
};

#endif
