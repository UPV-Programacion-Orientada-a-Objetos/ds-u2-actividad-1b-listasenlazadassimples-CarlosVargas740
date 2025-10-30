/**
 * @file SensorPresion.h
 * @brief Sensor de presión atmosférica (valores enteros)
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorPresion
 * @brief Sensor que mide presión atmosférica en hPa (tipo int)
 * 
 * Hereda de SensorBase e implementa procesamiento específico
 * para datos de presión.
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> lecturas;  ///< Lista de lecturas de presión
    
public:
    /**
     * @brief Constructor
     * @param id Identificador del sensor
     * @param ubi Ubicación del sensor
     */
    SensorPresion(const char* id, const char* ubi) 
        : SensorBase(id, ubi) {}
    
    /**
     * @brief Agrega una lectura de presión
     * @param valor Presión en hPa
     */
    void agregarLectura(int valor) {
        lecturas.agregar(valor);
    }
    
    /**
     * @brief Procesa las lecturas de presión
     * 
     * Calcula promedio y verifica límites (980-1050 hPa)
     */
    void procesarLectura() override {
        if (lecturas.getCantidad() == 0) {
            std::cout << "  No hay lecturas" << std::endl;
            return;
        }
        
        int promedio = lecturas.calcularPromedio();
        std::cout << "  Promedio: " << promedio << " hPa" << std::endl;
        
        if (promedio < 980) {
            std::cout << "  ALERTA: Presion baja (tormenta)" << std::endl;
        } else if (promedio > 1050) {
            std::cout << "  ALERTA: Presion alta" << std::endl;
        } else {
            std::cout << "  Estado: Normal" << std::endl;
        }
    }
    
    /**
     * @brief Imprime información del sensor
     */
    void imprimirInfo() const override {
        std::cout << "\n[PRESION]" << std::endl;
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
    const ListaSensor<int>& getLecturas() const {
        return lecturas;
    }
};

#endif
