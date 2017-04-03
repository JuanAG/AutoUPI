#ifndef AUTOUPI_PROGRAMA_H
#define AUTOUPI_PROGRAMA_H

#include <string>
#include <ctime>
#include <vector>

using namespace std;

class Programa{
public:
    Programa();
    Programa(std::vector<string> datos);
    Programa(string str);
    std::string getNombre();
    std::string getFechaInstalacion();
    std::string getRuta();
    bool getAccesoDirectoCreado();
    std::string getAccesoDirectoCreadoStr();
    std::string getNombrAccesoDirecto();
    std::vector<string> getDatos();
    std::string getCadenaDatos();
    std::string getIcono();
    std::string getOrganizacion();
    //TODO Poner el destructor

private:
    std::string nombre;
    std::string fechaInstalacion;
    std::string ruta;
    bool accesoDirectoCreado;
    std::string nombreAccesoDirecto;
    std::string icono;
    std::string organizacion;
};


#endif //AUTOUPI_PROGRAMA_H
