#include "sistemausuarios.h"

bool SistemaUsuarios::registrar(const std::string& nombre,const std::string& contrasena,std::string& error){
    error.clear();

    if (nombre.empty() || contrasena.empty()) {
        error = "El nombre y la contraseña son obligatorios.";
        return false;
    }

    if (usuarios.buscarPorNombre(nombre) != nullptr) {
        error = "Ese nombre de usuario ya está registrado.";
        return false;
    }

    const bool agregado = usuarios.agregar(nombre,contrasena,1,0);

    if (!agregado) {
        error = "No se pudo crear la cuenta.";
        return false;
    }

    nombreActivo = nombre;
    return true;
}

bool SistemaUsuarios::iniciarSesion(const std::string& nombre,const std::string& contrasena,std::string& error){
    error.clear();

    NodoUsuario* encontrado = usuarios.iniciarSesion(nombre,contrasena);

    if (encontrado == nullptr) {
        error = "Nombre o contraseña incorrectos.";
        return false;
    }

    nombreActivo = encontrado->usuario.obtenerNombre();
    return true;
}

std::string SistemaUsuarios::obtenerNombreActivo() const{
    return nombreActivo;
}
void SistemaUsuarios::cerrarSesion(){
    nombreActivo.clear();
}

bool SistemaUsuarios::borrarCuentaActiva(){
    if (nombreActivo.empty()) {
        return false;
    }

    const bool eliminada = usuarios.eliminar(nombreActivo);

    if (!eliminada) {
        return false;
    }

    cerrarSesion();
    return true;
}



void SistemaUsuarios::cargarContactosDesdeArchivo(){
    std::ifstream archivoEntrada(NOMBRE_ARCHIVO.c_str());
    usuarios.vaciar();

    if (!archivoEntrada. is_open()){
        return;
    }

    std::string linea;

    while (getline(archivoEntrada, linea)){
        if (linea.empty()){
            continue;
        }

        size_t p1 = linea.find(DELIMITADOR);
        size_t p2 = (p1 == std::string::npos) ?std::string::npos : linea.find(DELIMITADOR, p1 + 1);
        size_t p3 = (p2 == std::string::npos) ? std::string::npos : linea.find(DELIMITADOR, p2 + 1);

        if (p1 == std::string::npos || p2 == std::string::npos ||  p3 == std::string::npos ){
            continue;
        }

        std::string nombre = linea.substr(0, p1);
        std::string PIN = linea.substr(p1 + 1, p2 - (p1 + 1));
        std::string nivelTexto = linea.substr(p2 + 1, p3 - (p2 + 1));
        std::string trofeosTexto = linea.substr(p3 + 1);
        int nivel= 0;
        int trofeo=0;


        try{
             nivel = stoi(nivelTexto);
        }
        catch (...){
            continue;
        }

        try{
             trofeo = stoi(trofeosTexto);
        }
        catch (...){
            continue;
        }
        usuarios.agregar(nombre,PIN,nivel, trofeo);
    }

    archivoEntrada.close();
}


void  SistemaUsuarios::guardarAgendaEnArchivo(){
    std::ofstream archivoSalida(NOMBRE_ARCHIVO.c_str(),  std::ios::trunc);

    if (!archivoSalida.is_open()){
        return;
    }

    for (int indice = 0; indice < (int)usuarios.obtenerCantidad(); indice++){
        archivoSalida << usuarios.obtenerPorIndice(indice)->usuario.obtenerNombre() << DELIMITADOR<< usuarios.obtenerPorIndice(indice)->usuario.obtenerContrasena() << DELIMITADOR<< usuarios.obtenerPorIndice(indice)->usuario.obtenerNivel() << DELIMITADOR << usuarios.obtenerPorIndice(indice)->usuario.obtenerTrofeos() << "\n";
    }

    archivoSalida.close();
}

ListaUsuarios& SistemaUsuarios:: obtenerListas(){
    return usuarios;
}
