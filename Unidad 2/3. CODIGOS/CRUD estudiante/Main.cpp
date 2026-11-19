#include "controlador/EstudianteController.h"
#include "vista/ConsolaView.h"
#include <iostream>

int main() {
    try {
        EstudianteController controlador;
        ConsolaView vistaConsola(controlador);
        vistaConsola.ejecutar();
    } catch (const std::exception& error) {
        std::cerr << "Error inesperado en el sistema: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
