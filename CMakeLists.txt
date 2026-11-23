cmake_minimum_required(VERSION 3.16)

project(Bomberman_22541083_22441370 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Bomberman_22541083_22441370 main.cpp
    ventanajuego.h ventanajuego.cpp
    MapaYCasillas/mapa.h MapaYCasillas/mapa.cpp
    boton.h boton.cpp
    Bombas/bomba.h Bombas/bomba.cpp
    Bombas/nodobomba.h Bombas/nodobomba.cpp
    Bombas/colabomba.h Bombas/colabomba.cpp
    Bombas/sistemaexplosion.h Bombas/sistemaexplosion.cpp
    MapaYCasillas/celda.h MapaYCasillas/celda.cpp
    Jugador/jugador.h Jugador/jugador.cpp
    Enemigos/enemigo.h Enemigos/enemigo.cpp)
target_link_libraries(Bomberman_22541083_22441370 PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS Bomberman_22541083_22441370
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
