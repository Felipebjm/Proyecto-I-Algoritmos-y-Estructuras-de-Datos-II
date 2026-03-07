cmake_minimum_required(VERSION 3.20)
project(Proyecto_I_Datos_II)

set(CMAKE_CXX_STANDARD 20)

# Buscar todos los cpp dentro de src
file(GLOB archivos CONFIGURE_DEPENDS "src/*.cpp")

# Crear un ejecutable por cada archivo
foreach(archivo ${archivos})
    get_filename_component(nombre ${archivo} NAME_WE)
    add_executable(${nombre} ${archivo})
endforeach()
