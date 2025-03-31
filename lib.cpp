#include "lib.h"
#include <vector>
#include <string>
#include <set>
#include <fstream>

using namespace std;

vector<string> cargar_listado(const string & nombre_archivo){
    ifstream listadoPalabra(nombre_archivo);

    // Compruebo que no haya errores
    if(listadoPalabra.good() == false) { 
        exit(1);
    }

    vector<string> res;
    string linea;

    // Agrego cada linea/palabra al vector
    while(!listadoPalabra.eof()) {
        getline(listadoPalabra, linea);
        // Condición para evitar copiar renglones vacios
        if(linea.length() == 5) {
            res.push_back(linea);;
        }
    }
    listadoPalabra.close();

    return res;
}

bool intento_valido(const string & intento, const string & palabra_secreta, const vector<string> &listado){
    // Intento valido sii tiene la misma longitud que palabra secreta
    if(intento.length() != palabra_secreta.length()) {
        return 0;
    } 
    
    // Busco el intento en el listado de palabras
    for(int i=0; i<listado.size(); ++i) {
        if(listado[i] == intento) {
            return 1;
        }
    }

    // En este punto, intento no está en el listado
    return 0;
}

vector<EstadoLetra> evaluar_intento(const string & intento, const string & palabra_secreta){
    vector<EstadoLetra> res;
    
    // Armo un conjunto con las letras de la palabra secreta 
    // Uso este algoritmo para evitar correr loops dentro de loops
    set<char> set_palabra_secreta;
    for(int i=0; i<palabra_secreta.length(); ++i) {
        set_palabra_secreta.insert(palabra_secreta[i]);
    }

    // Recorro la palabra intento y asigno un estado a cada letra
    for(int i=0; i<intento.length(); ++i) {
        if(set_palabra_secreta.contains(intento[i])) { // la letra esta en la palabra
            if(intento[i] == palabra_secreta[i]) { // la letra esta en el lugar correcto
                res.push_back(EstadoLetra::LugarCorrecto);
            } else {
                res.push_back(EstadoLetra::LugarIncorrecto);
            }
        } else {
            res.push_back(EstadoLetra::NoPresente);
        }
    }

    return res;   
}

string respuesta_en_string(const vector<EstadoLetra> & respuesta){
    string res = "";
    for(int i=0; i<respuesta.size(); ++i) {
        if(respuesta[i] == EstadoLetra::LugarCorrecto) {
            res.append("+");
        } else if(respuesta[i] == EstadoLetra::LugarIncorrecto) {
            res.append("-");
        } else {
            res.append("X");
        }
    }

    return res;
}