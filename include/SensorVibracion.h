/**
 * @file SensorVibracion.h
 * @brief Sensor de vibración (valores enteros)
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef SENSOR_VIBRACION_H
#define SENSOR_VIBRACION_H

#include "SensorBase.h"
#include "ListaSensor.h"

/**
 * @class SensorVibracion
 * @brief Sensor que mide intensidad de vibración (tipo int)
 * 
 * Hereda de SensorBase e implementa procesamiento específico
 * para datos de vibración/aceleración.
 */
class SensorVibracion : public SensorBase {
private:
    ListaSensor<int> lecturas;  ///< Lista de lecturas de vibración
    
public:
    /**
     * @brief Constructor
     * @param id Identificador del sensor
     * @param ubi Ubicación del sensor
     */
    SensorVibracion(const char* id, const char* ubi) 
        : SensorBase(id, ubi) {}
    
    /**
     * @brief Agrega una lectura de vibración
     * @param valor Intensidad (0-100)
     */
    void agregarLectura(int valor) {
        lecturas.agregar(valor);
    }
    
    /**
     * @brief Procesa las lecturas de vibración
     * 
     * Calcula promedio y verifica niveles de alerta (0-100)
     */
    void procesarLectura() override {
        if (lecturas.getCantidad() == 0) {
            std::cout << "  No hay lecturas" << std::endl;
            return;
        }
        
        int promedio = lecturas.calcularPromedio();
        std::cout << "  Promedio: " << promedio << std::endl;
        
        if (promedio < 30) {
            std::cout << "  Estado: Normal" << std::endl;
        } else if (promedio < 60) {
            std::cout << "  ALERTA: Vibracion moderada" << std::endl;
        } else {
            std::cout << "  ALERTA: Vibracion alta - revisar!" << std::endl;
        }
    }
    
    /**
     * @brief Imprime información del sensor
     */
    void imprimirInfo() const override {
        std::cout << "\n[VIBRACION]" << std::endl;
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
