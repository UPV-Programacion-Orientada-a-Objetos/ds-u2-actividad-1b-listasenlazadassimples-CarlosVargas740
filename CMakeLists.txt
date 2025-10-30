cmake_minimum_required(VERSION 3.10)

# Información del proyecto
project(SistemaIoTSensores 
    VERSION 1.0.0
    DESCRIPTION "Sistema de Gestión Polimórfica de Sensores para IoT"
    LANGUAGES CXX)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opciones de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Directorios
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Incluir directorios de cabecera
include_directories(${INCLUDE_DIR})

# Archivo principal ejecutable
add_executable(sensor_iot ${SRC_DIR}/main.cpp)

# Información del ejecutable
set_target_properties(sensor_iot PROPERTIES
    OUTPUT_NAME "sistema_sensores_iot"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Mensajes informativos
message(STATUS "========================================")
message(STATUS "Sistema IoT de Sensores - Configuración")
message(STATUS "========================================")
message(STATUS "Versión: ${PROJECT_VERSION}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Directorio de include: ${INCLUDE_DIR}")
message(STATUS "Directorio de fuentes: ${SRC_DIR}")
message(STATUS "========================================")

# Instalación
install(TARGETS sensor_iot
    RUNTIME DESTINATION bin
    COMPONENT applications)

# Generar documentación con Doxygen (si está disponible)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)
    
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generando documentación con Doxygen"
        VERBATIM)
    
    message(STATUS "Doxygen encontrado. Use 'make doc' para generar documentación.")
else()
    message(STATUS "Doxygen no encontrado. Documentación no disponible.")
endif()

# Tests (opcional)
option(BUILD_TESTS "Compilar tests unitarios" OFF)
if(BUILD_TESTS)
    enable_testing()
    message(STATUS "Tests habilitados")
endif()

# CPack para distribución
include(CPack)
set(CPACK_PACKAGE_NAME "SistemaIoTSensores")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Sistema de gestión polimórfica de sensores IoT")
set(CPACK_PACKAGE_VENDOR "Carlos Vargas")
