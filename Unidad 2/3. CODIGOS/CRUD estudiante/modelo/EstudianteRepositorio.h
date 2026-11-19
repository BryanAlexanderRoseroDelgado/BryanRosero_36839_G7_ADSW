#ifndef ESTUDIANTE_REPOSITORIO_H
#define ESTUDIANTE_REPOSITORIO_H

#include "Estudiante.h"
#include <vector>
#include <string>

class EstudianteRepositorio {
private:
    std::string rutaArchivo;

    void guardar(const std::vector<Estudiante>& estudiantes) const;
    Estudiante leerRegistro(const std::string& linea, int numeroLinea) const;
    std::vector<std::string> leerCampos(const std::string& linea) const;
    std::string entreComillas(const std::string& valor) const;
    std::string convertirIdAntiguo(const std::string& id) const;
    void asegurarDirectorio() const;

public:
    EstudianteRepositorio();
    explicit EstudianteRepositorio(const std::string& rutaArchivo);

    std::vector<Estudiante> obtenerTodos() const;
    Estudiante obtenerPorId(const std::string& id) const;
    void registrar(const Estudiante& estudiante);
    void actualizar(const Estudiante& estudiante);
    void eliminar(const std::string& id);
};

#endif // ESTUDIANTE_REPOSITORIO_H

