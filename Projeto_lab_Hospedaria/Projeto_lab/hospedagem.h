#ifndef HOSPEDAGENS_H
#define HOSPEDAGENS_H

// Função para iniciar a hospedagem (check-in)
void iniciarHospedagem(int codigoReserva);

// Função para finalizar a hospedagem (check-out)
void finalizarHospedagem(int codigoReserva);

// Função para mostrar todas as hospedagens de um cliente
void mostrarHospedagensPorCliente(char cpfCliente[14]);

#endif