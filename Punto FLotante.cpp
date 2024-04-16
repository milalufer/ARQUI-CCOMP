// Punto FLotante.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
#include <iostream>
#include <iostream>
#include <bitset>
#include <cmath>
#include <limits>

using namespace std;

struct Float32 {
    bool signo;
    int exponente;
    float significand;
};

void obtenerPatronesDeBits(Float32 numero) {
    bitset<1> signo(numero.signo);
    bitset<8> exponente(numero.exponente);
    bitset<23> significando(*(unsigned int*)&numero.significand);

    cout << "Signo: " << signo << endl;
    cout << "Exponente: " << exponente << endl;
    cout << "Significando: " << significando << endl;
}

Float32 multiplicar(Float32 a, Float32 b) {
    Float32 resultado;

    if (a.significand == 0 || b.significand == 0) {
        resultado.signo = false; // El signo se establece positivo
        resultado.exponente = 0;
        resultado.significand = 0;
        return resultado;
    }

    resultado.significand = a.significand * b.significand;


    resultado.signo = (a.signo == b.signo) ? false : true;

    // Sumar los exponentes
    resultado.exponente = a.exponente + b.exponente - 127;

    if (resultado.exponente > numeric_limits<unsigned char>::max()) {
        cout << "Desbordamiento detectado." << endl;
        resultado.exponente = numeric_limits<unsigned char>::max();
    }
    else if (resultado.exponente < numeric_limits<unsigned char>::min()) {
        cout << "Underflow detectado." << endl;
        resultado.exponente = numeric_limits<unsigned char>::min();
    }

    return resultado;
}

int main() {
    Float32 a, b;

    cout << "Ingrese el primer valor en punto flotante: ";
    cin >> a.significand;

    cout << "Ingrese el segundo valor en punto flotante: ";
    cin >> b.significand;

    a.signo = (a.significand < 0) ? true : false;
    b.signo = (b.significand < 0) ? true : false;

    a.exponente = 127;
    b.exponente = 127;

    //  operación en C++ Original
    Float32 resultadoorignal;
    resultadoorignal.significand = a.significand * b.significand;

    cout << "\nResultado de la multiplicacion (C++):" << endl;
    obtenerPatronesDeBits(resultadoorignal);

    //Funcion creada
    Float32 resultado = multiplicar(a, b);

    cout << "\nResultado de la multiplicacion (Funcion propia):" << endl;
    obtenerPatronesDeBits(resultado);

    return 0;
}
