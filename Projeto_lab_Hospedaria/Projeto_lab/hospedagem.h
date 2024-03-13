#ifndef HOSPEDAGENS_H
#define HOSPEDAGENS_H

// Fun��o para iniciar a hospedagem (check-in)
void iniciarHospedagem(int codigoReserva);

// Fun��o para finalizar a hospedagem (check-out)
void finalizarHospedagem(int codigoReserva);

// Fun��o para mostrar todas as hospedagens de um cliente
void mostrarHospedagensPorCliente(char cpfCliente[14]);

#endif