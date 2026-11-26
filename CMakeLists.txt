cmake_minimum_required(VERSION 3.16)

project(Bomberman_22541083_22441370 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
    controladorjuego.h controladorjuego.cpp



    main.cpp
    ventanajuego.h ventanajuego.cpp

    boton.h boton.cpp

    Jugador/jugador.h Jugador/jugador.cpp
    Jugador/controladorjugador.h Jugador/controladorjugador.cpp

    Item/tipoitem.h Item/tipoitem.cpp
    Item/pilaitem.h Item/pilaitem.cpp
    Item/sistemaitems.h Item/sistemaitems.cpp

    Bombas/bomba.h Bombas/bomba.cpp
    Bombas/nodobomba.h Bombas/nodobomba.cpp
    Bombas/colabomba.h Bombas/colabomba.cpp
    Bombas/sistemaexplosion.h Bombas/sistemaexplosion.cpp
    Bombas/sistemabombas.h Bombas/sistemabombas.cpp

    MapaYCasillas/mapa.h MapaYCasillas/mapa.cpp
    MapaYCasillas/celda.h MapaYCasillas/celda.cpp

    Enemigos/enemigoAleatorio.h Enemigos/enemigoAleatorio.cpp
    Enemigos/gestorenemigos.h Enemigos/gestorenemigos.cpp
    Recursos.qrc
    panelvida.h panelvida.cpp

    Enemigos/enemigoautonomo.h Enemigos/enemigoautonomo.cpp

    usuario.h usuario.cpp
    listausuarios.h listausuarios.cpp
    nodousuario.h nodousuario.cpp
    ventanaprincipal.h ventanaprincipal.cpp
    ventanamenu.h ventanamenu.cpp
    ventanabienvenida.h ventanabienvenida.cpp
    ventanainiciosesion.h ventanainiciosesion.cpp
    ventanaregistro.h ventanaregistro.cpp
    sistemausuarios.h sistemausuarios.cpp
    ventanaranking.h ventanaranking.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bombas"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos"
    "${CMAKE_CURRENT_SOURCE_DIR}/Jugador"
    "${CMAKE_CURRENT_SOURCE_DIR}/Item"
    "${CMAKE_CURRENT_SOURCE_DIR}/MapaYCasillas"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
