#ifndef ESTUDIANTE_CONTROLLER_H
#define ESTUDIANTE_CONTROLLER_H

#include "../modelo/Estudiante.h"
#include "../modelo/EstudianteRepositorio.h"
#include <vector>
#include <string>

class EstudianteController {
private:
    EstudianteRepositorio repositorio;

    void validar(const std::string& id, const std::string& nombre,
                 const std::string& apellido, const std::string& direccion) const;
    static std::string trim(const std::string& str);

public:
    EstudianteController();
    explicit EstudianteController(const EstudianteRepositorio& repositorio);

    void registrar(const std::string& id, const std::string& nombre,
                   const std::string& apellido, const std::string& direccion);
    std::vector<Estudiante> consultarTodos() const;
    Estudiante consultarPorId(const std::string& id) const;
    void modificar(const std::string& id, const std::string& nombre,
                   const std::string& apellido, const std::string& direccion);
    void eliminar(const std::string& id);
};

#endif // ESTUDIANTE_CONTROLLER_H

