#include "lib.h"
#include <iostream>

using namespace std;

int main(){
    // Preparo el listado de palabras
    string ruta_archivo;
    cout << "Ruta al listado de palabras: ";
    getline(cin, ruta_archivo);
    vector<string> listado = cargar_listado(ruta_archivo);
    
    // Elijo la palabra secreta
    srand(time(0));
    string palabra_secreta = listado[rand() % listado.size()];
    cout << "La palabra secreta tiene 5 letras." << endl;
    
    // Juego
    int intentos = 6;
    string intento;
    while(intentos) {
        cout<<"Te quedan " << (intentos-1) << " intentos." << endl;
        getline(cin, intento);
        if(intento_valido(intento, palabra_secreta, listado)) {
            vector<EstadoLetra> respuesta = evaluar_intento(intento, palabra_secreta);
            string respuesta_string = respuesta_en_string(respuesta);
            if(respuesta_string == "+++++") {
                cout << "¡Correcto!" << endl;
                return 0;
            }
            cout << respuesta_en_string(respuesta) << endl;
            intentos--;
        } else {
            cout << "El intento no es valido. Escriba un nuevo intento." << endl;
        }
    }

    cout << "Incorrecto. Te quedaste sin intentos." << endl;
    cout << "La palabra secreta era " << palabra_secreta << ". Termina el juego." << endl;

    return 0;
}
