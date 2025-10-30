# Instrucciones para compilar y ejecutar

## Requisitos Previos
- GCC/G++ 7.0 o superior
- CMake 3.10 o superior
- Make
- Doxygen (opcional, para documentación)

## Pasos de Compilación

### 1. Navegar al directorio del proyecto
```bash
cd sistema-sensores-iot
```

### 2. Crear directorio de compilación
```bash
mkdir build
cd build
```

### 3. Configurar con CMake
```bash
cmake ..
```

### 4. Compilar
```bash
make
```

### 5. Ejecutar el programa
```bash
./bin/sistema_sensores_iot
```

## Generar Documentación (Opcional)

```bash
# Desde el directorio build/
make doc

# La documentación se generará en build/docs/html/
# Abrir en navegador:
xdg-open docs/html/index.html
```

## Limpiar Proyecto

```bash
# Desde el directorio build/
make clean

# O eliminar todo el directorio build/
cd ..
rm -rf build/
```

## Análisis de Memoria con Valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./bin/sistema_sensores_iot
```

## Cargar Código en Arduino

1. Abrir Arduino IDE
2. Abrir archivo: `arduino/simulador_arduino.ino`
3. Seleccionar placa: Herramientas → Placa → Arduino Uno/Nano
4. Seleccionar puerto: Herramientas → Puerto → /dev/ttyUSB0
5. Cargar código: Botón "Subir" (→)

## Configurar Permisos de Puerto Serial (Linux)

```bash
# Opción 1: Dar permisos temporales
sudo chmod 666 /dev/ttyUSB0

# Opción 2: Agregar usuario al grupo dialout (permanente)
sudo usermod -a -G dialout $USER
# Luego cerrar sesión y volver a iniciar
```

## Problemas Comunes

### Error: "cmake: command not found"
```bash
sudo apt-get install cmake
```

### Error: "g++: command not found"
```bash
sudo apt-get install build-essential
```

### Error: "cannot find -lstdc++"
```bash
sudo apt-get install libstdc++-dev
```

### Error: "Permission denied" al acceder al puerto serial
```bash
sudo chmod 666 /dev/ttyUSB0
```
