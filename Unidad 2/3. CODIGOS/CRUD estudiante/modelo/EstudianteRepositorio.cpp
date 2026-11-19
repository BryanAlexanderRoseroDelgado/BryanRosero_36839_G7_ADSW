#include "EstudianteRepositorio.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#include <cctype>

namespace fs = std::filesystem;

EstudianteRepositorio::EstudianteRepositorio() : rutaArchivo("datos/estudiantes.txt") {}

EstudianteRepositorio::EstudianteRepositorio(const std::string& rutaArchivo) : rutaArchivo(rutaArchivo) {}

void EstudianteRepositorio::asegurarDirectorio() const {
    fs::path p(rutaArchivo);
    if (p.has_parent_path()) {
        fs::create_directories(p.parent_path());
    }
}

std::string EstudianteRepositorio::entreComillas(const std::string& valor) const {
    std::string resultado = "\"";
    for (char c : valor) {
        if (c == '\\') {
            resultado += "\\\\";
        } else if (c == '"') {
            resultado += "\\\"";
        } else {
            resultado += c;
        }
    }
    resultado += "\"";
    return resultado;
}

std::string EstudianteRepositorio::convertirIdAntiguo(const std::string& id) const {
    // Si tiene formato antiguo: L00-1234 -> L00001234
    if (id.rfind("L00-", 0) == 0 && id.length() > 4) {
        std::string num = id.substr(4);
        bool soloDigitos = true;
        for (char c : num) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                soloDigitos = false;
                break;
            }
        }
        if (soloDigitos && num.length() <= 6) {
            std::string relleno(6 - num.length(), '0');
            return "L00" + relleno + num;
        }
    }
    return id;
}

std::vector<std::string> EstudianteRepositorio::leerCampos(const std::string& linea) const {
    std::vector<std::string> campos;
    size_t pos = 0;
    const size_t len = linea.length();

    while (pos < len) {
        while (pos < len && std::isspace(static_cast<unsigned char>(linea[pos]))) {
            pos++;
        }
        if (pos >= len) {
            break;
        }

        if (linea[pos] == '"') {
            pos++; // Salta comilla inicial
            std::string valor;
            bool cerrado = false;

            while (pos < len) {
                char c = linea[pos++];
                if (c == '\\' && pos < len) {
                    valor += linea[pos++];
                } else if (c == '"') {
                    cerrado = true;
                    break;
                } else {
                    valor += c;
                }
            }

            if (!cerrado) {
                throw std::invalid_argument("Comilla sin cerrar");
            }
            campos.push_back(valor);
        } else {
            size_t inicio = pos;
            while (pos < len && !std::isspace(static_cast<unsigned char>(linea[pos]))) {
                pos++;
            }
            campos.push_back(linea.substr(inicio, pos - inicio));
        }
    }

    return campos;
}

Estudiante EstudianteRepositorio::leerRegistro(const std::string& linea, int numeroLinea) const {
    std::vector<std::string> campos;
    try {
        campos = leerCampos(linea);
    } catch (...) {
        throw std::runtime_error("Registro invalido en " + rutaArchivo + ", linea " + std::to_string(numeroLinea) + ".");
    }

    if (campos.size() == 4) {
        campos[0] = convertirIdAntiguo(campos[0]);
    }

    if (campos.size() != 4 || !Estudiante::esIdValido(campos[0])) {
        throw std::runtime_error("Registro invalido en " + rutaArchivo + ", linea " + std::to_string(numeroLinea) + ".");
    }

    return Estudiante(campos[0], campos[1], campos[2], campos[3]);
}

std::vector<Estudiante> EstudianteRepositorio::obtenerTodos() const {
    std::vector<Estudiante> estudiantes;
    if (!fs::exists(rutaArchivo)) {
        return estudiantes;
    }

    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return estudiantes;
    }

    std::string linea;
    int numLinea = 0;
    while (std::getline(archivo, linea)) {
        numLinea++;
        // Quitar espacios en blanco al inicio y final
        size_t inicio = linea.find_first_not_of(" \t\r\n");
        if (inicio == std::string::npos) {
            continue; // Linea vacia
        }
        size_t fin = linea.find_last_not_of(" \t\r\n");
        std::string lineaLimpia = linea.substr(inicio, fin - inicio + 1);

        estudiantes.push_back(leerRegistro(lineaLimpia, numLinea));
    }

    return estudiantes;
}

Estudiante EstudianteRepositorio::obtenerPorId(const std::string& id) const {
    std::vector<Estudiante> lista = obtenerTodos();
    for (const auto& est : lista) {
        if (est.getId() == id) {
            return est;
        }
    }
    throw std::invalid_argument("No se encontro un estudiante con ese ID.");
}

void EstudianteRepositorio::guardar(const std::vector<Estudiante>& estudiantes) const {
    asegurarDirectorio();
    std::ofstream archivo(rutaArchivo, std::ios::out | std::ios::trunc);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escritura: " + rutaArchivo);
    }

    for (const auto& est : estudiantes) {
        archivo << est.getId() << ' '
                << entreComillas(est.getNombre()) << ' '
                << entreComillas(est.getApellido()) << ' '
                << entreComillas(est.getDireccion()) << '\n';
    }
}

void EstudianteRepositorio::registrar(const Estudiante& estudiante) {
    std::vector<Estudiante> lista = obtenerTodos();
    for (const auto& existente : lista) {
        if (existente.getId() == estudiante.getId()) {
            throw std::invalid_argument("Ya existe un estudiante con ese ID.");
        }
    }
    lista.push_back(estudiante);
    guardar(lista);
}

void EstudianteRepositorio::actualizar(const Estudiante& estudiante) {
    std::vector<Estudiante> lista = obtenerTodos();
    for (size_t i = 0; i < lista.size(); ++i) {
        if (lista[i].getId() == estudiante.getId()) {
            lista[i] = estudiante;
            guardar(lista);
            return;
        }
    }
    throw std::invalid_argument("No se encontro un estudiante con ese ID.");
}

void EstudianteRepositorio::eliminar(const std::string& id) {
    std::vector<Estudiante> lista = obtenerTodos();
    for (size_t i = 0; i < lista.size(); ++i) {
        if (lista[i].getId() == id) {
            lista.erase(lista.begin() + i);
            guardar(lista);
            return;
        }
    }
    throw std::invalid_argument("No se encontro un estudiante con ese ID.");
}

