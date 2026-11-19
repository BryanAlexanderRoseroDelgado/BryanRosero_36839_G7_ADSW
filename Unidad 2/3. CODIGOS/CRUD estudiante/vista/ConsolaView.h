#ifndef CONSOLA_VIEW_H
#define CONSOLA_VIEW_H

#include "../controlador/EstudianteController.h"
#include <string>

class ConsolaView {
private:
    EstudianteController& controlador;

    int leerEntero(const std::string& mensaje) const;
    std::string leerTexto(const std::string& mensaje) const;

    void registrar();
    void consultar();
    void modificar();
    void eliminar();
    void mostrar(const Estudiante& estudiante) const;
    void mostrarError(const std::exception& error) const;

public:
    explicit ConsolaView(EstudianteController& controlador);
    void ejecutar();
};

#endif // CONSOLA_VIEW_H

