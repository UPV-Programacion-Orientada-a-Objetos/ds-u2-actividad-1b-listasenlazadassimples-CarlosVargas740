/**
 * @file main.cpp
 * @brief Programa principal SIMPLIFICADO del Sistema IoT
 * @author Carlos Vargas
 * @date 30 de octubre de 2025
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../include/ListaSensor.h"
#include "../include/SensorBase.h"
#include "../include/SensorTemperatura.h"
#include "../include/SensorPresion.h"
#include "../include/SensorVibracion.h"
#include "../include/ListaGestion.h"
#include "../include/SimuladorSerial.h"

using namespace std;

void mostrarMenu() {
    cout << "\n=== Sistema IoT de Sensores ===" << endl;
    cout << "1. Crear Sensor Temperatura" << endl;
    cout << "2. Crear Sensor Presion" << endl;
    cout << "3. Crear Sensor Vibracion" << endl;
    cout << "4. Agregar Lectura Manual" << endl;
    cout << "5. Simular Arduino (5 lecturas)" << endl;
    cout << "6. Procesar Sensores" << endl;
    cout << "7. Mostrar Sensores" << endl;
    cout << "8. Salir" << endl;
    cout << "Opcion: ";
}

void procesarDatoArduino(char* buffer, ListaGestion& listaGestion) {
    char tipo[10] = "";
    char id[20] = "";
    char valor[20] = "";
    
    // Dividir el string "TIPO:ID:VALOR"
    char* token = strtok(buffer, ":");
    if (token) strcpy(tipo, token);
    
    token = strtok(nullptr, ":");
    if (token) strcpy(id, token);
    
    token = strtok(nullptr, ":");
    if (token) strcpy(valor, token);
    
    cout << "  Dato Arduino: " << tipo << " | " << id << " | " << valor << endl;
    
    // Buscar sensor
    SensorBase* sensor = listaGestion.buscarPorId(id);
    
    // Si no existe, crearlo
    if (sensor == nullptr) {
        if (strcmp(tipo, "TEMP") == 0) {
            sensor = new SensorTemperatura(id, "Arduino");
            listaGestion.agregarSensor(sensor);
        } else if (strcmp(tipo, "PRES") == 0) {
            sensor = new SensorPresion(id, "Arduino");
            listaGestion.agregarSensor(sensor);
        } else if (strcmp(tipo, "VIBR") == 0) {
            sensor = new SensorVibracion(id, "Arduino");
            listaGestion.agregarSensor(sensor);
        }
        sensor = listaGestion.buscarPorId(id);
    }
    
    // Agregar lectura según tipo
    if (sensor) {
        SensorTemperatura* temp = dynamic_cast<SensorTemperatura*>(sensor);
        if (temp) {
            temp->agregarLectura(atof(valor));
            return;
        }
        
        SensorPresion* pres = dynamic_cast<SensorPresion*>(sensor);
        if (pres) {
            pres->agregarLectura(atoi(valor));
            return;
        }
        
        SensorVibracion* vibr = dynamic_cast<SensorVibracion*>(sensor);
        if (vibr) {
            vibr->agregarLectura(atoi(valor));
        }
    }
}

int main() {
    cout << "\n=== Sistema IoT - POO ===" << endl;
    
    ListaGestion listaGestion;
    SimuladorSerial arduino;
    int opcion = 0;
    
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                char id[50], ubicacion[50];
                cout << "ID del sensor (ej: T-001): ";
                cin.getline(id, 50);
                cout << "Ubicacion: ";
                cin.getline(ubicacion, 50);
                
                SensorBase* sensor = new SensorTemperatura(id, ubicacion);
                listaGestion.agregarSensor(sensor);
                cout << "Sensor creado!\n";
                break;
            }
            
            case 2: {
                char id[50], ubicacion[50];
                cout << "ID del sensor (ej: P-105): ";
                cin.getline(id, 50);
                cout << "Ubicacion: ";
                cin.getline(ubicacion, 50);
                
                SensorBase* sensor = new SensorPresion(id, ubicacion);
                listaGestion.agregarSensor(sensor);
                cout << "Sensor creado!\n";
                break;
            }
            
            case 3: {
                char id[50], ubicacion[50];
                cout << "ID del sensor (ej: V-201): ";
                cin.getline(id, 50);
                cout << "Ubicacion: ";
                cin.getline(ubicacion, 50);
                
                SensorBase* sensor = new SensorVibracion(id, ubicacion);
                listaGestion.agregarSensor(sensor);
                cout << "Sensor creado!\n";
                break;
            }
            
            case 4: {
                char id[50];
                cout << "ID del sensor: ";
                cin.getline(id, 50);
                
                SensorBase* sensor = listaGestion.buscarPorId(id);
                if (sensor == nullptr) {
                    cout << "Sensor no encontrado!\n";
                    break;
                }
                
                // Intentar convertir a cada tipo
                SensorTemperatura* temp = dynamic_cast<SensorTemperatura*>(sensor);
                if (temp) {
                    float valor;
                    cout << "Temperatura (C): ";
                    cin >> valor;
                    cin.ignore();
                    temp->agregarLectura(valor);
                    cout << "Lectura agregada!\n";
                    break;
                }
                
                SensorPresion* pres = dynamic_cast<SensorPresion*>(sensor);
                if (pres) {
                    int valor;
                    cout << "Presion (hPa): ";
                    cin >> valor;
                    cin.ignore();
                    pres->agregarLectura(valor);
                    cout << "Lectura agregada!\n";
                    break;
                }
                
                SensorVibracion* vibr = dynamic_cast<SensorVibracion*>(sensor);
                if (vibr) {
                    int valor;
                    cout << "Vibracion (0-100): ";
                    cin >> valor;
                    cin.ignore();
                    vibr->agregarLectura(valor);
                    cout << "Lectura agregada!\n";
                }
                break;
            }
            
            case 5: {
                arduino.inicializar();
                
                cout << "\nSimulando 5 lecturas del Arduino...\n";
                
                for (int i = 0; i < 5; i++) {
                    char buffer[100];
                    arduino.generarLecturaAleatoria(buffer, 100);
                    procesarDatoArduino(buffer, listaGestion);
                }
                cout << "Simulacion completada!\n";
                break;
            }
            
            case 6: {
                listaGestion.procesarTodosSensores();
                break;
            }
            
            case 7: {
                listaGestion.mostrarTodos();
                break;
            }
            
            case 8: {
                cout << "\nCerrando sistema...\n";
                break;
            }
            
            default:
                cout << "Opcion invalida.\n";
        }
        
    } while (opcion != 8);
    
    cout << "\nSistema cerrado.\n";
    return 0;
}
