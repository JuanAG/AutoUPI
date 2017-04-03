#include "Programa.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#define WIDTH   800
#define HEIGHT  600
#define URL     "http://www.google.com"

using namespace Awesomium;

using namespace std;

void instalar();
void desinstalar();
std::vector<Programa> programasInstalados();
void guardarListaProgramas(std::vector<Programa> programas);
Programa pedirDatosPrograma();

int main(int argc, char *argv[])
{
    std::string datoLeido;
    do{
        cin >> datoLeido;
        if(datoLeido == "install"){
            //Instalar un nuevo programa
            instalar();
        }
        else if(datoLeido == "uninstall"){
            // Desisntalar un programa ya instalado
            desinstalar();
        }
        else if(datoLeido == "programas"){
            // Lista de programas ya instalados
            programasInstalados();
        }
        else if(datoLeido == "help"){
            std::cout << "The commands are: install, uninstall, programas and exit" << endl;
        }
    }
    while(datoLeido != "exit");

    return 0;
}

Programa pedirDatosPrograma(){
    std::string programa = "";
    std::string aux;

    // Pedir los datos
    std::cout << "Nombre del programa: ";
    cin >> aux;
    programa.append(aux+"#");

    time_t fechaInstalacion = time(0);
    programa.append(fechaInstalacion+"#");

    // La ruta de instalacion
    programa.append("/home/"+aux+"#");

    std::cout << "¿Crear acceso directo? ";
    cin >> aux;
    if(aux == "n"){
        // El hueco corresponde al nombre
        programa.append(false+"# #");
    }
    else if(aux == "y"){
        programa.append(true+"#");
        std::cout << "Nombre del acceso directo: ";
        cin >> aux;
        programa.append(aux+"#");
    }

    std::cout << "Nombre del creador: ";
    cin >> aux;
    programa.append(aux);

    // Construyo el programa
    Programa app {programa};

    return app;
}

void instalar(){
    std::string aux;
    Programa programa;

    // Pido los datos del programa
    programa = pedirDatosPrograma();

    // La ruta donde esta el fichero
    std::cout << "Ruta y nombre del programa a instalar: ";
    cin >> aux;

    // Instalar el programa
    std::string textoInstalar = "";

        // Crear la carpeta del programa
        textoInstalar.append("mkdir $HOME/"+programa.getRuta() + "&&");
        // Extraer en esa carpeta el tar.gz y el tar.bz2
        textoInstalar.append("tar -xvzf" + aux + "-C $HOME/"+programa.getRuta() + "&&");
        textoInstalar.append("tar -xvjf" + aux + "-C $HOME/"+programa.getRuta() + "&&");
        textoInstalar.append("cd " + programa.getRuta()+ " ./configure &&"); // Configurar
        textoInstalar.append("cd " + programa.getRuta() + "make &&");
        textoInstalar.append("cd " + programa.getRuta() + "make install"); // Instalar

    system(textoInstalar.c_str());

    // Crear el acceso directo si procede
    if(programa.getAccesoDirectoCreado()){
        // Creamos el contenido del .desktop
        std::string lanzador = "";

            lanzador.append("[Desktop Entry]\n");
            lanzador.append("Name="+programa.getNombrAccesoDirecto()+"\n");
            lanzador.append("Exec="+programa.getRuta() + programa.getNombre() + "\n");
            lanzador.append("Terminal=false\n");
            lanzador.append("Type=Application\n");
            lanzador.append("Categories=Utility;\n");
            lanzador.append("StartupNotify=false\n");
            lanzador.append("Icon="+programa.getIcono());

        // La ruta de los accesos directos es /usr/share/applications/
        std::string carpetaLanzadores {"/usr/share/applications/"};
        std::ofstream ofs(carpetaLanzadores + programa.getNombrAccesoDirecto()
                          +".desktop", std::ofstream::trunc); // Que lo trunque
        ofs << lanzador; //TODO Mirar tema de permisos
        ofs.close();
    }

    // Guardarlo en el fichero de programas instalados
    std::ofstream ofs("programs.upi", std::ofstream::ate); // Que lo ponga al final del fichero
    ofs << Programa(programa).getCadenaDatos() << "\n";
    ofs.close();
}

void guardarListaProgramas(vector<Programa> programas){
    // Que lo borre y empieze de cero
    std::ofstream ofs("programs.upi", std::ofstream::trunc);
    for(Programa app: programas) {
        ofs << app.getCadenaDatos() << "\n";
    }
    ofs.close();
}

void desinstalar(){
    std::vector<Programa> programas;
    int contador = 0;
    // Mostramos la lista de los programas instalados
    programas = programasInstalados();

    std::string nombre;
    // Pedimos cual queremos borrar
    std::cout << "Cual es el que se quiere borrar: ";
    cin >> nombre;

    // Buscamos cual de todos ellos es el que queremos borrar
    for(Programa app: programas) {
        if (app.getNombre() == nombre) {
            // Es el que queremos borrar
            std::string aux = "rm -rf " + app.getRuta();
            system(aux.c_str());

            // Si hay un acceso directo tambien lo borramos
            if (app.getAccesoDirectoCreado()) {
                // Hay que borrar el acceso directo
                aux = "rm /usr/share/applications/" + app.getNombrAccesoDirecto() +".desktop";
                system(aux.c_str());
            }

            // Lo borramos de la lista
            programas.erase(programas.begin() + contador);

            // Guardamos la nueva lista en el fichero de texto
            guardarListaProgramas(programas);
            break;
        }
        contador++;
    }
}

std::vector<Programa> programasInstalados(){
    std::vector<Programa> respuesta;
    // Abrir el fichero de programas instalados
    std::ifstream ifs("programs.upi");
    std::string programa;
    if(!ifs){
        std::cout << "No hay programas instalados" << endl;
    }
    else{
       while(ifs){
           ifs >> programa;
           // Construimos ese programa
           Programa app {programa};
           // Imprimimos el programa instalado
           std::cout << app.getNombre() << "\t" << app.getFechaInstalacion() << endl;
           // Lo insertamos en la "lista"
           respuesta.push_back(app);
        }
    }
    return respuesta;
}
