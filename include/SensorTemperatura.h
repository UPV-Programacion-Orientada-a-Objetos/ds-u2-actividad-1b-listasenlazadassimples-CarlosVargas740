/**
 * @file SensorTemperatura.h
 * @brief Sensor de temperatura (valores flotantes)
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorTemperatura
 * @brief Sensor que mide temperatura en °C (tipo float)
 * 
 * Hereda de SensorBase e implementa procesamiento específico
 * para datos de temperatura.
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> lecturas;  ///< Lista de lecturas de temperatura
    
public:
    /**
     * @brief Constructor
     * @param id Identificador del sensor
     * @param ubi Ubicación del sensor
     */
    SensorTemperatura(const char* id, const char* ubi) 
        : SensorBase(id, ubi) {}
    
    /**
     * @brief Agrega una lectura de temperatura
     * @param valor Temperatura en °C
     */
    void agregarLectura(float valor) {
        lecturas.agregar(valor);
    }
    
    /**
     * @brief Procesa las lecturas de temperatura
     * 
     * Calcula promedio y verifica límites (15-30°C)
     */
    void procesarLectura() override {
        if (lecturas.getCantidad() == 0) {
            std::cout << "  No hay lecturas" << std::endl;
            return;
        }
        
        float promedio = lecturas.calcularPromedio();
        std::cout << "  Promedio: " << promedio << " C" << std::endl;
        
        if (promedio < 15.0f) {
            std::cout << "  ALERTA: Temperatura baja" << std::endl;
        } else if (promedio > 30.0f) {
            std::cout << "  ALERTA: Temperatura alta" << std::endl;
        } else {
            std::cout << "  Estado: Normal" << std::endl;
        }
    }
    
    /**
     * @brief Imprime información del sensor
     */
    void imprimirInfo() const override {
        std::cout << "\n[TEMPERATURA]" << std::endl;
        std::cout << "  ID: " << id << std::endl;
        std::cout << "  Ubicacion: " << ubicacion << std::endl;
        std::cout << "  Lecturas (" << lecturas.getCantidad() << "): ";
        lecturas.imprimir();
        std::cout << std::endl;
    }
    
    /**
     * @brief Obtiene la lista de lecturas
     * @return Referencia a la lista
     */
    const ListaSensor<float>& getLecturas() const {
        return lecturas;
    }
};

#endif
