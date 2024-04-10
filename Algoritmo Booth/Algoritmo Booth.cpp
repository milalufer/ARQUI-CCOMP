// Algoritmo Booth.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <cstdint>
using namespace std;

void desplazamiento_derecha(uint32_t& A, uint32_t& Q, uint32_t& Q_1) {
    bool bit_menos_significativo_A = A & 1;
    bool bit_menos_significativo_Q = Q & 1;

    A >>= 1; // Desplazar A  derecha
    Q >>= 1; // Desplazar Q derecha
    Q |= (bit_menos_significativo_A << 31); // bit LSB Q se asigna MSB de A
    A |= (bit_menos_significativo_A << 31); 
    Q_1 = bit_menos_significativo_Q; 
}

bool calcular_acarreo(bool a, bool b, bool acarreo) {
    return (a & b) | (a & acarreo) | (b & acarreo);
}


void suma_binaria(uint32_t& A, const uint32_t& M) {
    bool acarreo = false;
    for (size_t i = 0; i < 32; ++i) {
        bool b_A = (A >> i) & 1;
        bool b_M = (M >> i) & 1;

        A ^= ((b_M ^ b_A ^ acarreo) << i); 
        acarreo = calcular_acarreo(b_A, b_M, acarreo); 
    }
}


void resta_compDos(uint32_t& A, const uint32_t& M) {
    uint32_t neg_M = ~M; 
    suma_binaria(A, neg_M); //  A + complemento M
}

void imprimir_valores(uint32_t A, uint32_t Q) {
    cout << "A: ";
    for (int i = 31; i >= 0; --i) {
        cout << ((A >> i) & 1);
    }
    cout << endl;

    cout << "Q: ";
    for (int i = 31; i >= 0; --i) {
        cout << ((Q >> i) & 1);
    }
    cout << endl;
}


void multiplicacion_booth(uint32_t M, uint32_t Q) {
    uint32_t A = M; 
    uint32_t q = Q; 
    uint32_t q_1 = 0; // Inicializar Q_1 como 0

    cout << "Iteracion 0:" << endl;
    imprimir_valores(A, Q);

    for (size_t i = 0; i < 32; ++i) {
        cout << "Iterar, paso " << i + 1 << ":" << endl;
        if ((q & 1) == 0 && q_1 == 1) { // Restar M de A si Q_1Q = 10
            resta_compDos(A, M);
            cout << "Restar M de A:" << endl;
        }
        else if ((q & 1) == 1 && q_1 == 0) { // Sumar M a A si Q_1Q = 01
            suma_binaria(A, M);
            cout << "Sumar M a A:" << endl;
        }
        desplazamiento_derecha(A, q, q_1); // Desplazamiento aritmético hacia la derecha
        imprimir_valores(A, q);
    }
}

int main() {
    int32_t multiplicando, multiplicador;
    cout << "Ingresa multiplicando: ";
    cin >> multiplicando;
    cout << "Ingresa multiplicador: ";
    cin >> multiplicador;

    uint32_t M = static_cast<uint32_t>(multiplicando);
    uint32_t Q = static_cast<uint32_t>(multiplicador);

    multiplicacion_booth(M, Q);

    return 0;
}


