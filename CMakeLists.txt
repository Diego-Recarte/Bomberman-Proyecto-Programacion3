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

    Enemigos/enemigoPersecutor.h Enemigos/enemigoPersecutor.cpp

    Usuario/usuario.h Usuario/usuario.cpp
    Usuario/listausuarios.h Usuario/listausuarios.cpp
    Usuario/nodousuario.h Usuario/nodousuario.cpp
    Usuario/sistemausuarios.h Usuario/sistemausuarios.cpp

    Ventanas/ventanajuego.h Ventanas/ventanajuego.cpp
    Ventanas/ventanaprincipal.h Ventanas/ventanaprincipal.cpp
    Ventanas/ventanamenu.h Ventanas/ventanamenu.cpp
    Ventanas/ventanabienvenida.h Ventanas/ventanabienvenida.cpp
    Ventanas/ventanainiciosesion.h Ventanas/ventanainiciosesion.cpp
    Ventanas/ventanaregistro.h Ventanas/ventanaregistro.cpp

    Ventanas/ventanaranking.h Ventanas/ventanaranking.cpp
    Enemigos/fantasma.h Enemigos/fantasma.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Bombas"
    "${CMAKE_CURRENT_SOURCE_DIR}/Enemigos"
    "${CMAKE_CURRENT_SOURCE_DIR}/Jugador"
    "${CMAKE_CURRENT_SOURCE_DIR}/Item"
    "${CMAKE_CURRENT_SOURCE_DIR}/MapaYCasillas"
    "${CMAKE_CURRENT_SOURCE_DIR}/Ventanas"
    "${CMAKE_CURRENT_SOURCE_DIR}/Usuario"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
