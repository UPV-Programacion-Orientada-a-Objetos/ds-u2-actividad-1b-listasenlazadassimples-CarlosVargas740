/**
 * @file SimuladorSerial.h
 * @brief Simulador de comunicación serial Arduino
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#ifndef SIMULADOR_SERIAL_H
#define SIMULADOR_SERIAL_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

/**
 * @class SimuladorSerial
 * @brief Simula datos recibidos por puerto serial desde Arduino
 * 
 * Genera datos aleatorios en formato "TIPO:ID:VALOR" simulando
 * el comportamiento del sketch Arduino.
 */
class SimuladorSerial {
private:
    bool inicializado;  ///< Estado de inicialización
    
public:
    /**
     * @brief Constructor
     */
    SimuladorSerial() : inicializado(false) {}
    
    /**
     * @brief Inicializa el generador de números aleatorios
     */
    void inicializar() {
        if (!inicializado) {
            srand(static_cast<unsigned int>(time(nullptr)));
            inicializado = true;
        }
    }
    
    /**
     * @brief Genera una lectura de temperatura
     * @param buffer Buffer donde escribir el dato
     * @param tam Tamaño del buffer
     */
    void generarTemperatura(char* buffer, int tam) {
        float temp = 20.0f + (rand() % 100) / 10.0f;
        snprintf(buffer, tam, "TEMP:T-001:%.1f", temp);
    }
    
    /**
     * @brief Genera una lectura de presión
     * @param buffer Buffer donde escribir el dato
     * @param tam Tamaño del buffer
     */
    void generarPresion(char* buffer, int tam) {
        int presion = 1000 + (rand() % 50);
        snprintf(buffer, tam, "PRES:P-105:%d", presion);
    }
    
    /**
     * @brief Genera una lectura de vibración
     * @param buffer Buffer donde escribir el dato
     * @param tam Tamaño del buffer
     */
    void generarVibracion(char* buffer, int tam) {
        int vibracion = rand() % 80;
        snprintf(buffer, tam, "VIBR:V-201:%d", vibracion);
    }
    
    /**
     * @brief Genera una lectura aleatoria de cualquier tipo
     * @param buffer Buffer donde escribir el dato
     * @param tam Tamaño del buffer
     */
    void generarLecturaAleatoria(char* buffer, int tam) {
        int tipo = rand() % 3;
        
        switch (tipo) {
            case 0:
                generarTemperatura(buffer, tam);
                break;
            case 1:
                generarPresion(buffer, tam);
                break;
            case 2:
                generarVibracion(buffer, tam);
                break;
        }
    }
    
    /**
     * @brief Simula recepción de datos del Arduino
     * @param buffer Buffer donde se escribirán los datos
     * @param tam Tamaño del buffer
     * @param numLecturas Número de lecturas a generar
     */
    void simularRecepcion(char* buffer, int tam, int numLecturas = 5) {
        inicializar();
        
        std::cout << "\n=== Simulando Arduino ===" << std::endl;
        std::cout << "Generando " << numLecturas << " lecturas..." << std::endl;
        
        for (int i = 0; i < numLecturas; i++) {
            generarLecturaAleatoria(buffer, tam);
            std::cout << "  " << buffer << std::endl;
        }
    }
};

#endif
