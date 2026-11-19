#include "ConsolaView.h"
#include <iostream>
#include <sstream>

ConsolaView::ConsolaView(EstudianteController& controlador) : controlador(controlador) {}

int ConsolaView::leerEntero(const std::string& mensaje) const {
    while (true) {
        std::cout << mensaje;
        std::string linea;
        if (!std::getline(std::cin, linea)) {
            return 0;
        }

        // Limpiar espacios
        size_t inicio = linea.find_first_not_of(" \t\r\n");
        if (inicio == std::string::npos) {
            std::cout << "Ingrese un numero entero valido.\n";
            continue;
        }
        size_t fin = linea.find_last_not_of(" \t\r\n");
        std::string limpia = linea.substr(inicio, fin - inicio + 1);

        try {
            size_t idx = 0;
            int valor = std::stoi(limpia, &idx);
            if (idx == limpia.length()) {
                return valor;
            }
        } catch (...) {}

        std::cout << "Ingrese un numero entero valido.\n";
    }
}

std::string ConsolaView::leerTexto(const std::string& mensaje) const {
    while (true) {
        std::cout << mensaje;
        std::string linea;
        if (!std::getline(std::cin, linea)) {
            throw std::runtime_error("No hay mas datos de entrada.");
        }

        size_t inicio = linea.find_first_not_of(" \t\r\n");
        if (inicio != std::string::npos) {
            size_t fin = linea.find_last_not_of(" \t\r\n");
            return linea.substr(inicio, fin - inicio + 1);
        }

        std::cout << "El campo no puede quedar vacio.\n";
    }
}

void ConsolaView::registrar() {
    try {
        std::string id = leerTexto("ID (L00XXXXXX): ");
        std::string nombre = leerTexto("Nombre: ");
        std::string apellido = leerTexto("Apellido: ");
        std::string direccion = leerTexto("Direccion: ");

        controlador.registrar(id, nombre, apellido, direccion);
        std::cout << "Estudiante registrado.\n";
    } catch (const std::exception& error) {
        mostrarError(error);
    }
}

void ConsolaView::consultar() {
    try {
        std::string id = leerTexto("ID (L00XXXXXX, o 0 para consultar todos): ");
        if (id == "0") {
            std::vector<Estudiante> estudiantes = controlador.consultarTodos();
            if (estudiantes.empty()) {
                std::cout << "No hay estudiantes registrados.\n";
                return;
            }
            for (const auto& est : estudiantes) {
                mostrar(est);
            }
        } else {
            Estudiante est = controlador.consultarPorId(id);
            mostrar(est);
        }
    } catch (const std::exception& error) {
        mostrarError(error);
    }
}

void ConsolaView::modificar() {
    try {
        std::string id = leerTexto("ID (L00XXXXXX): ");
        std::string nombre = leerTexto("Nuevo nombre: ");
        std::string apellido = leerTexto("Nuevo apellido: ");
        std::string direccion = leerTexto("Nueva direccion: ");

        controlador.modificar(id, nombre, apellido, direccion);
        std::cout << "Estudiante modificado.\n";
    } catch (const std::exception& error) {
        mostrarError(error);
    }
}

void ConsolaView::eliminar() {
    try {
        std::string id = leerTexto("ID (L00XXXXXX): ");
        controlador.eliminar(id);
        std::cout << "Estudiante eliminado.\n";
    } catch (const std::exception& error) {
        mostrarError(error);
    }
}

void ConsolaView::mostrar(const Estudiante& estudiante) const {
    std::cout << "\nID: " << estudiante.getId() << "\n";
    std::cout << "Nombre: " << estudiante.getNombre() << "\n";
    std::cout << "Apellido: " << estudiante.getApellido() << "\n";
    std::cout << "Direccion: " << estudiante.getDireccion() << "\n";
}

void ConsolaView::mostrarError(const std::exception& error) const {
    std::cout << "Error: " << error.what() << "\n";
}

void ConsolaView::ejecutar() {
    int opcion = -1;
    do {
        std::cout << "\n=== CRUD de estudiantes ===\n";
        std::cout << "1. Registrar estudiante\n";
        std::cout << "2. Consultar estudiantes\n";
        std::cout << "3. Modificar estudiante\n";
        std::cout << "4. Eliminar estudiante\n";
        std::cout << "0. Salir\n";
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1:
                registrar();
                break;
            case 2:
                consultar();
                break;
            case 3:
                modificar();
                break;
            case 4:
                eliminar();
                break;
            case 0:
                std::cout << "Hasta luego.\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 0);
}

