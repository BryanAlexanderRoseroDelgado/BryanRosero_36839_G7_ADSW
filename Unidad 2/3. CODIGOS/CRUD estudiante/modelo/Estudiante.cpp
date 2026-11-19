#include "Estudiante.h"
#include <cctype>

Estudiante::Estudiante() : id(""), nombre(""), apellido(""), direccion("") {}

Estudiante::Estudiante(const std::string& id, const std::string& nombre, const std::string& apellido, const std::string& direccion)
    : id(id), nombre(nombre), apellido(apellido), direccion(direccion) {}

bool Estudiante::esIdValido(const std::string& id) {
    if (id.length() != 9) {
        return false;
    }
    if (id[0] != 'L' || id[1] != '0' || id[2] != '0') {
        return false;
    }
    for (size_t i = 3; i < 9; ++i) {
        if (!std::isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }
    return true;
}

std::string Estudiante::getId() const { return id; }
std::string Estudiante::getNombre() const { return nombre; }
std::string Estudiante::getApellido() const { return apellido; }
std::string Estudiante::getDireccion() const { return direccion; }

void Estudiante::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Estudiante::setApellido(const std::string& apellido) { this->apellido = apellido; }
void Estudiante::setDireccion(const std::string& direccion) { this->direccion = direccion; }

