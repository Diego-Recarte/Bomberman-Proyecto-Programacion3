cmake_minimum_required(VERSION 3.16)

project(Bomberman_22541083_22441370 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    # Archivos principales
    main.cpp
    ventanajuego.h
    ventanajuego.cpp

    # Boton
    boton.h
    boton.cpp

    # Jugador: archivos ubicados en la raiz
    jugador.h
    jugador.cpp

    # Items: archivos ubicados en la raiz
    tipoitem.h
    tipoitem.cpp
    pilaitem.h
    pilaitem.cpp

    # Bombas
    Bombas/bomba.h
    Bombas/bomba.cpp
    Bombas/nodobomba.h
    Bombas/nodobomba.cpp
    Bombas/colabomba.h
    Bombas/colabomba.cpp
    Bombas/sistemaexplosion.h
    Bombas/sistemaexplosion.cpp

    # Enemigos
    Enemigos/enemigo.h
    Enemigos/enemigo.cpp

    # Mapa y casillas
    MapaYCasillas/mapa.h
    MapaYCasillas/mapa.cpp
    MapaYCasillas/celda.h
    MapaYCasillas/celda.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bombas"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos"
    "${CMAKE_CURRENT_SOURCE_DIR}/MapaYCasillas"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)