#include "Programa.h"

Programa::Programa() {
    nombre = " ";
    fechaInstalacion = time(0);
    ruta = " ";
    accesoDirectoCreado = false;
    nombreAccesoDirecto = " ";
    icono = " ";
    organizacion = " ";
}

Programa::Programa(std::vector<string> datos){
    nombre = datos[0];
    fechaInstalacion = datos[1];
    ruta = datos[2];
    accesoDirectoCreado = std::stoi(datos[3].c_str());
    nombreAccesoDirecto = datos[4];
    icono = datos[5];
    organizacion = datos[6];
}

Programa::Programa(string str){
    // Separo los datos buscando el caracter separador
    std::vector<string> datos;
    std::size_t start = 0, end = 0;
    while ((end = str.find("#", start)) != std::string::npos){
        datos.push_back(str.substr(start, end-start));
        start = end + 1; // +1 para quitar el caracter separador
    }
    datos.push_back(str.substr(start));
    // Lo construyo usando el constructor anterior
    this(datos);
}

std::string Programa::getNombre(){
    return this->nombre;
}

std::string Programa::getFechaInstalacion(){
    return this->fechaInstalacion;
}

std::string Programa::getRuta(){
    return this->ruta;
}

bool Programa::getAccesoDirectoCreado(){
    return this->accesoDirectoCreado;
}

std::string Programa::getAccesoDirectoCreadoStr() {
    return this->accesoDirectoCreado ? "true" : "false";
}

std::string Programa::getNombrAccesoDirecto(){
    return this->nombreAccesoDirecto;
}

std::string Programa::getIcono() {
    return this->icono;
}

std::string Programa::getOrganizacion(){
    return this->organizacion;
}

std::string Programa::getCadenaDatos(){
    std::string respuesta = "";
    respuesta.append(this->getNombre()+"#");
    respuesta.append(this->getFechaInstalacion()+"#");
    respuesta.append(this->getRuta()+"#");
    respuesta.append(this->getAccesoDirectoCreadoStr()+"#");
    respuesta.append(this->getNombrAccesoDirecto()+"#");
    respuesta.append(this->getOrganizacion());
    return respuesta;
}

std::vector<string> Programa::getDatos(){
    std::vector<string> respuesta;
    respuesta.push_back(this->getNombre());
    respuesta.push_back(this->getFechaInstalacion());
    respuesta.push_back(this->getRuta());
    respuesta.push_back(this->getAccesoDirectoCreadoStr());
    respuesta.push_back(this->getNombrAccesoDirecto());
    respuesta.push_back(this->getOrganizacion());
    return respuesta;
}
