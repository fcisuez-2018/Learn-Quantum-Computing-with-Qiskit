// file: example.c
#include <stdio.h>
#include <stdint.h>
#include <complex.h>
#include <qiskit.h>
 
int main(int argc, char* argv[]) {
    // build a 100-qubit empty observable
    u_int32_t num_qubits = 100;
    QkObs *obs = qk_obs_zero(num_qubits);
 
    // add the term 2 * (X0 Y1 Z2) to the observable
    complex double coeff = 2;  // on MSVC use: _Dcomplex coeff = {2, 0}
    QkBitTerm bit_terms[3] = {QkBitTerm_X, QkBitTerm_Y, QkBitTerm_Z};  // bit terms: X Y Z
    uint32_t indices[3] = {0, 1, 2};  // indices: 0 1 2
    QkObsTerm term = {coeff, 3, bit_terms, indices, num_qubits};
    qk_obs_add_term(obs, &term);  // append the term
 
    // print some properties and the observable itself
    printf("num_qubits: %i\n", qk_obs_num_qubits(obs));
    printf("num_terms: %lu\n", qk_obs_num_terms(obs));
    printf("observable: %s\n", qk_obs_str(obs));
 
    // free the memory allocated for the observable
    qk_obs_free(obs);
 
    return 0;
}