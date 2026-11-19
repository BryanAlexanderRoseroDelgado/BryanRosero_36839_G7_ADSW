#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>

class Estudiante {
private:
    std::string id;
    std::string nombre;
    std::string apellido;
    std::string direccion;

public:
    Estudiante();
    Estudiante(const std::string& id, const std::string& nombre, const std::string& apellido, const std::string& direccion);

    static bool esIdValido(const std::string& id);

    // Getters
    std::string getId() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getDireccion() const;

    // Setters
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setDireccion(const std::string& direccion);
};

#endif // ESTUDIANTE_H

