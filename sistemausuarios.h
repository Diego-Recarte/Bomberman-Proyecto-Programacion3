#ifndef SISTEMAUSUARIOS_H
#define SISTEMAUSUARIOS_H

#include <string>
#include <fstream>

#include "listausuarios.h"

class SistemaUsuarios{
public:
    bool registrar(const std::string& nombre,const std::string& contrasena,std::string& error);

    bool iniciarSesion(const std::string& nombre,const std::string& contrasena,std::string& error);

    std::string obtenerNombreActivo() const;
    void cerrarSesion();
    bool borrarCuentaActiva();
    void cargarContactosDesdeArchivo();
    void guardarAgendaEnArchivo();
    ListaUsuarios &obtenerListas();


private:
    ListaUsuarios usuarios;
    std::string nombreActivo;
    const std::string NOMBRE_ARCHIVO = "archivoUsuario.txt";
    const char DELIMITADOR = '|';


};

#endif // SISTEMAUSUARIOS_H