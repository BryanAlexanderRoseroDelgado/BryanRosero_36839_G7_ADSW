#include "EstudianteController.h"
#include <stdexcept>
#include <cctype>

std::string EstudianteController::trim(const std::string& str) {
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == std::string::npos) {
        return "";
    }
    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

EstudianteController::EstudianteController() : repositorio() {}

EstudianteController::EstudianteController(const EstudianteRepositorio& repositorio) : repositorio(repositorio) {}

void EstudianteController::validar(const std::string& id, const std::string& nombre,
                                   const std::string& apellido, const std::string& direccion) const {
    if (!Estudiante::esIdValido(id)
        || trim(nombre).empty()
        || trim(apellido).empty()
        || trim(direccion).empty()) {
        throw std::invalid_argument("El ID debe tener el formato L00XXXXXX y los campos no pueden quedar vacios.");
    }
}

void EstudianteController::registrar(const std::string& id, const std::string& nombre,
                                     const std::string& apellido, const std::string& direccion) {
    validar(id, nombre, apellido, direccion);
    repositorio.registrar(Estudiante(id, trim(nombre), trim(apellido), trim(direccion)));
}

std::vector<Estudiante> EstudianteController::consultarTodos() const {
    return repositorio.obtenerTodos();
}

Estudiante EstudianteController::consultarPorId(const std::string& id) const {
    if (!Estudiante::esIdValido(id)) {
        throw std::invalid_argument("El ID debe tener el formato L00XXXXXX.");
    }
    return repositorio.obtenerPorId(id);
}

void EstudianteController::modificar(const std::string& id, const std::string& nombre,
                                     const std::string& apellido, const std::string& direccion) {
    validar(id, nombre, apellido, direccion);
    repositorio.actualizar(Estudiante(id, trim(nombre), trim(apellido), trim(direccion)));
}

void EstudianteController::eliminar(const std::string& id) {
    if (!Estudiante::esIdValido(id)) {
        throw std::invalid_argument("El ID debe tener el formato L00XXXXXX.");
    }
    repositorio.eliminar(id);
}

