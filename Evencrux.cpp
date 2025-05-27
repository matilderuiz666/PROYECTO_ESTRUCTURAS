#include <iostream>
#include "Usuario.h"
#include "Organizador.h"
#include "Dato.h"
#include "Ubicacion.h"
#include "Evento.h"
#include <fstream>
#include "string"  //no es necesario
#include <sstream>

using namespace std;

void menuPrincipal();
void menuCliente(Usuario& gestorUsuario, const string& correo);
void menuOrganizador(Organizador& gestorOrganizadores, const string& correo);
void menuCuenta(int opcionPrincipal);
void registroCliente(Usuario& gestorUsuarios);
void inicioSesionCliente(Usuario& gestorUsuarios);
void registroOrganizador(Usuario& gestorOrganizadores);
void inicioSesionOrganizador(Organizador& gestorOrganizadores);
string obtenerNombrePorCorreo(const Organizador& gestor, const string& correo);
void editarEventoOrganizador(Organizador& gestorOrganizadores, const string& nombreOrganizador);
Evento* pedirDatos(const string& nombreOrganizador, const string& nombreExistente = "");
void eliminarEventoOrganizador(Organizador& gestorOrganizadores);
void mostrarEstadisticasOrganizador(const Organizador& gestor);
void mostrarBoletosVendidos(const Organizador& gestor);
void mostrarComentarios(const Organizador& gestor);
void buscarEventosDesdeArchivo(const string& archivo); //muestra los eventos
void mostrarEventosRecomendados(const string& archivo);
void registrarBoleto(const string& correoCliente, const string& nombreEvento);
void verMisBoletos(const string& correoCliente);
void comentarEvento();
void verHistorialEventos(const string& correoCliente);

int main() {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    Usuario gestorUsuarios;
    int opcion;
    do {
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "1. Registrarse" << endl;
        cout << "2. Iniciar sesion" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            menuCuenta(opcion);
            break;
        case 2:
            menuCuenta(opcion);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 0);
}

void menuCuenta(int opcionPrincipal) {
    Usuario gestorUsuarios;
    Organizador gestorOrganizadores;
    int tipoCuenta;
    do {
        cout << "\n=== TIPO DE CUENTA ===" << endl;
        cout << "1. Cuenta Cliente" << endl;
        cout << "2. Cuenta Organizador" << endl;
        cout << "0. Atras" << endl;
        cout << "Ingrese una opcion: ";
        cin >> tipoCuenta;
        cin.ignore();
        switch (tipoCuenta) {
        case 1:
            if (opcionPrincipal == 1)
                registroCliente(gestorUsuarios);
            else {
                gestorUsuarios.cargarDesdeArchivo("usuarios.txt");
                inicioSesionCliente(gestorUsuarios);
            }
            break;
        case 2:
            if (opcionPrincipal == 1)
                registroOrganizador(gestorOrganizadores);
            else {
                gestorOrganizadores.cargarDesdeArchivo("organizadores.txt");
                inicioSesionOrganizador(gestorOrganizadores);
            }
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (tipoCuenta != 0);
}

void registroCliente(Usuario& gestorUsuarios) {  //funciona
    cout << "\n=== REGISTRO CLIENTE ===" << endl;
    string nombre, correo, contrasena, pais, ciudad, direccion;
    double lat, lon;

    cout << "Nombre: "; getline(cin, nombre);
    do {
        cout << "Correo (Gmail): "; getline(cin, correo);
        if (!gestorUsuarios.validarCorreo(correo))
            cout << "Correo no valido" << endl;
        if (!gestorUsuarios.correoUnico(correo))
            cout << "Este correo ya existe" << endl;
    } while (!gestorUsuarios.validarCorreo(correo) || !gestorUsuarios.correoUnico(correo)); //se tiene que usar si o si gestorUsuarios porque en ese estan cargados los datos, si se crea otro objeto seria un objeto vacio y no funcionaria ya que en correo existente al ser un objeto vacio no tendria nada y siempre devolveria true
    cout << "Pais: "; getline(cin, pais);
    cout << "Ciudad: "; getline(cin, ciudad);
    cout << "Direccion: "; getline(cin, direccion);
    cout << "Latitud: "; cin >> lat;
    cin.ignore();
    cout << "Longitud: "; cin >> lon;
    cin.ignore();
    do {
        cout << "Contraseña: "; getline(cin, contrasena);
        if (gestorUsuarios.validarContrasena(contrasena))
            cout << "Registro exitoso";
        else
            cout << "La contrasena debe tener minimamente 8 digitos, al menos una mayuscula, una minuscula y un numero. " << endl;
    } while (!gestorUsuarios.validarContrasena(contrasena));



    Ubicacion ubi(pais, ciudad, direccion, lat, lon);
    static int idGenerado = 1; // simula un id único
    Dato nuevo(idGenerado++, nombre, correo, contrasena, ubi);

    // Guardar en lista
    gestorUsuarios.agregarUsuario(nuevo);

    // Guardar en archivo
    gestorUsuarios.guardarEnArchivo("usuarios.txt");

    cout << "\nCliente registrado exitosamente y guardado en archivo!\n";
}

void registroOrganizador(Usuario& gestorOrganizadores) {  //funciona
    cout << "\n=== REGISTRO ORGANIZADOR ===" << endl;
    string nombre, correo, contrasena;

    cout << "Nombre: "; getline(cin, nombre);
    do {
        cout << "Correo (Gmail): "; getline(cin, correo);
        if (!gestorOrganizadores.validarCorreo(correo))
            cout << "Correo no valido" << endl;
        if (!gestorOrganizadores.correoUnico(correo))
            cout << "Este correo ya existe" << endl;
    } while (!gestorOrganizadores.validarCorreo(correo) || !gestorOrganizadores.correoUnico(correo));
    do {
        cout << "Contraseña: "; getline(cin, contrasena);
        if (gestorOrganizadores.validarContrasena(contrasena))
            cout << "Registro exitoso";
        else
            cout << "La contrasena debe tener minimamente 8 digitos, al menos una mayuscula, una minuscula y un numero. " << endl;
    } while (!gestorOrganizadores.validarContrasena(contrasena));

    // Ubicación vacía
    Ubicacion ubi;
    static int idGenerado = 1000;

    Dato nuevo(idGenerado++, nombre, correo, contrasena, ubi);
    gestorOrganizadores.agregarUsuario(nuevo);
    gestorOrganizadores.guardarEnArchivo("organizadores.txt");

    cout << "\nOrganizador registrado exitosamente y guardado en archivo!\n";
}

void inicioSesionOrganizador(Organizador& gestorOrganizadores) {  //revisar, probar para que salga incorrecto
    cout << "\n=== INICIO DE SESION ORGANIZADOR ===" << endl;
    string correo, contrasena;

    cout << "Correo (Gmail): ";
    getline(cin, correo);
    cout << "Contraseña: ";
    getline(cin, contrasena);

    if (gestorOrganizadores.autenticar(correo, contrasena)) {
        cout << "Inicio de sesion exitoso!\n";
        menuOrganizador(gestorOrganizadores, correo);
    }
    else {
        cout << "Correo o contraseña incorrectos.\n";
    }
}

void menuOrganizador(Organizador& gestorOrganizadores, const string& correo) {
    int opcion;
    Evento* nuevoEvento = nullptr;
    string nombre = obtenerNombrePorCorreo(gestorOrganizadores, correo);
    do {
        cout << "=== MENU ORGANIZADOR ===" << endl;
        cout << "\n1. Crear evento";
        cout << "\n2. Editar evento existente";
        cout << "\n3. Eliminar evento";
        cout << "\n4. Ver estadisticas de mis cuentas";
        cout << "\n5. Ver boletos vendidos";
        cout << "\n6. Ver comentarios de mis eventos";
        cout << "\n0. Cerrar sesion";
        cout << "\nIngrese su opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
        case 1:
            cout << "\n=== CREAR EVENTO ===" << endl;
            nuevoEvento = pedirDatos(nombre);
            gestorOrganizadores.crearEvento(nuevoEvento);
            gestorOrganizadores.guardarEventosEnArchivo("eventos.txt");
            cout << "Evento creado exitosamente.\n";
            break;
        case 2:
            cout << "\n=== EDITAR EVENTO ===" << endl;
            editarEventoOrganizador(gestorOrganizadores, nombre);
            break;
        case 3:
            cout << "\n=== ELIMINAR EVENTO ===" << endl;
            eliminarEventoOrganizador(gestorOrganizadores);
            break;
        case 4:
            cout << "\n=== ESTADISTICAS DEL EVENTO ===" << endl;
            mostrarEstadisticasOrganizador(gestorOrganizadores);
            break;
        case 5:
            cout << "\n=== BOLETOS VENDIDOS ===" << endl;
            mostrarBoletosVendidos(gestorOrganizadores);
            break;
        case 6:
            cout << "\n=== COMENTARIOS ===" << endl;
            mostrarComentarios(gestorOrganizadores);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "opcion invalida" << endl;
            break;
        }
    } while (opcion != 0);
}

void mostrarComentarios(const Organizador& gestor) {
    NodoEvento* actual = gestor.getCabezaEvento();
    while (actual != nullptr) {
        Evento* e = actual->getEvento();
        string nombreArchivo = "comentarios_" + e->getNombre() + ".txt";
        ifstream archivo(nombreArchivo);

        cout << "\nEvento: " << e->getNombre() << endl;
        if (archivo.is_open()) {
            string linea;
            while (getline(archivo, linea)) {
                cout << "- " << linea << endl;
            }
            archivo.close();
        }
        else {
            cout << "Sin comentarios aún." << endl;
        }
        actual = actual->getSiguiente();
    }
}

void mostrarBoletosVendidos(const Organizador& gestor) { //suponiendo que cada invitado representa un boleto vendido
    NodoEvento* actual = gestor.getCabezaEvento();
    while (actual != nullptr) {
        Evento* e = actual->getEvento();
        cout << "\nEvento: " << e->getNombre() << " | Boletos: " << e->getCantidadInvitados() << " | Total recaudado: $" << e->getCantidadInvitados() * e->getPrecio() << endl;
        actual = actual->getSiguiente();
    }
}

void mostrarEstadisticasOrganizador(const Organizador& gestor) {
    NodoEvento* actual = gestor.getCabezaEvento();
    int totalEventos = 0;
    int totalInvitados = 0;
    int totalGanancia = 0;

    while (actual != nullptr) {
        Evento* e = actual->getEvento();
        totalEventos++;
        totalInvitados += e->getCantidadInvitados();
        totalGanancia += e->getCantidadInvitados() * e->getPrecio();
        actual = actual->getSiguiente();
    }

    cout << "\nTotal de eventos creados: " << totalEventos << endl;
    cout << "Total de invitados acumulados: " << totalInvitados << endl;
    cout << "Ganancia estimada: $" << totalGanancia << endl;
}

void eliminarEventoOrganizador(Organizador& gestorOrganizadores) {
    gestorOrganizadores.mostrarEventos();

    cout << "Ingrese el nombre del evento a eliminar: ";
    string nombreEvento;
    cin.ignore();
    getline(cin, nombreEvento);

    if (gestorOrganizadores.eliminarEvento(nombreEvento)) {
        gestorOrganizadores.guardarEventosEnArchivo("eventos.txt");
        cout << "Evento eliminado exitosamente.\n";
    }
    else {
        cout << "No se encontró un evento con ese nombre.\n";
    }
}

void editarEventoOrganizador(Organizador& gestorOrganizadores, const string& nombreOrganizador) {
    gestorOrganizadores.mostrarEventos();

    cout << "Ingrese el nombre del evento a modificar: ";
    string nombreEvento;
    cin.ignore();
    getline(cin, nombreEvento);

    Evento* nuevoEvento = pedirDatos(nombreOrganizador, nombreEvento);

    if (gestorOrganizadores.modificarEvento(0, nuevoEvento)) {
        cout << "Evento modificado exitosamente.\n";
        gestorOrganizadores.guardarEventosEnArchivo("eventos.txt");
    }
    else {
        cout << "No se encontró el evento para modificar.\n";
    }
}

Evento* pedirDatos(const string& nombreOrganizador, const string& nombreExistente) {
    Evento* nuevoEvento = new Evento();

    string nombre = nombreExistente;
    if (nombre.empty()) {
        cout << "Nombre del evento: ";
        getline(cin, nombre);
    }

    string fecha, horaInicio, horaFinal, descripcion, estado, etiqueta;
    int cantidad, distancia, precio;
    string pais, ciudad, direccion;
    double lat, lon;

    cout << "Fecha (dd/mm/aaaa): ";
    getline(cin, fecha);
    cout << "Hora de inicio: ";
    getline(cin, horaInicio);
    cout << "Hora de finalizacion: ";
    getline(cin, horaFinal);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    cout << "Estado del evento: ";
    getline(cin, estado);
    cout << "Etiqueta: ";
    getline(cin, etiqueta);

    cout << "Cantidad de invitados: ";
    cin >> cantidad; cin.ignore();
    cout << "Distancia al destino (km): ";
    cin >> distancia; cin.ignore();
    cout << "Precio: ";
    cin >> precio; cin.ignore();

    cout << "Ubicacion - Pais: ";
    getline(cin, pais);
    cout << "Ubicacion - Ciudad: ";
    getline(cin, ciudad);
    cout << "Ubicacion - Direccion: ";
    getline(cin, direccion);
    cout << "Ubicacion - Latitud: ";
    cin >> lat; cin.ignore();
    cout << "Ubicacion - Longitud: ";
    cin >> lon; cin.ignore();

    Ubicacion ubi(pais, ciudad, direccion, lat, lon);

    nuevoEvento->setNombre(nombre);
    nuevoEvento->setFecha(fecha);
    nuevoEvento->setHoraInicio(horaInicio);
    nuevoEvento->setHoraFinal(horaFinal);
    nuevoEvento->setDescripcion(descripcion);
    nuevoEvento->setEstado(estado);
    nuevoEvento->setEtiqueta(etiqueta);
    nuevoEvento->setCantidadInvitados(cantidad);
    nuevoEvento->setDistanciaDestino(distancia);
    nuevoEvento->setPrecio(precio);
    nuevoEvento->setUbicacion(ubi);
    nuevoEvento->setOrganizador(nombreOrganizador);

    return nuevoEvento;
}

void inicioSesionCliente(Usuario& gestorUsuarios) {  //revisar
    cout << "\n=== INICIO DE SESION CLIENTE ===" << endl;
    string correo, contrasena;

    cout << "Correo (Gmail): ";
    getline(cin, correo);
    cout << "Contraseña: ";
    getline(cin, contrasena);

    if (gestorUsuarios.autenticar(correo, contrasena)) {
        cout << "Inicio de sesion exitoso!\n";
        menuCliente(gestorUsuarios, correo);
    }
    else {
        cout << "Correo o contraseña incorrectos.\n";
    }
}

void menuCliente(Usuario& gestorUsuario, const string& correo) {  //se le manda correo debido a algunos metodos que necesitan esa variable
    int opcion;
    string nombreEvento;
    do {
        cout << "=== MENU CLIENTE ===" << endl;
        cout << "\n1. Buscar evento";
        cout << "\n2. Ver eventos recomendados";
        cout << "\n3. Ver mis boletos";
        cout << "\n4.Ver historial de eventos";
        cout << "\n5. Comentar eventos";
        cout << "\n6. Ver notificaciones";
        cout << "\n0. Cerrar sesión";
        cout << "\ningrese su opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "\n=== EVENTOS DISPONIBLES ===\n";
            buscarEventosDesdeArchivo("eventos.txt");

            cout << "\nEscribí el NOMBRE EXACTO del evento al que deseas registrarte: ";
            cin.ignore();
            getline(cin, nombreEvento);

            registrarBoleto(correo, nombreEvento);
            break;
        case 2:
            mostrarEventosRecomendados("eventos.txt");
            break;
        case 3:
            verMisBoletos(correo);
            break;
        case 4:
            verHistorialEventos(correo);
            break;
        case 5:
            buscarEventosDesdeArchivo("eventos.txt");
            comentarEvento();
            break;
        case 6:
            verNotificaciones(correo);
            break;
        case 0:
            cout << "Saliendo... " << endl;
            break;
        default:
            cout << "opcion invalida" << endl;
            break;
        }
    } while (opcion != 0);

}

void verHistorialEventos(const string& correoCliente) {
    ifstream archivo("boletos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de boletos." << endl;
        return;
    }

    string linea;
    bool tieneHistorial = false;

    cout << "\n=== HISTORIAL DE EVENTOS ASISTIDOS ===\n";

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string correo, evento;
        getline(ss, correo, ',');
        getline(ss, evento);

        if (correo == correoCliente) {
            cout << "- " << evento << endl;
            tieneHistorial = true;
        }
    }

    if (!tieneHistorial) {
        cout << "No hay historial de eventos.\n";
    }

    archivo.close();
}

void comentarEvento() {
    string evento;
    cout << "¿Qué evento querés comentar?: ";
    cin.ignore();
    getline(cin, evento);

    string comentario;
    cout << "Escribí tu comentario: ";
    getline(cin, comentario);

    ofstream archivo("comentarios_" + evento + ".txt", ios::app);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de comentarios.\n";
        return;
    }

    archivo << comentario << endl;
    archivo.close();
    cout << "Comentario guardado!\n";
}

void verNotificaciones(const string& correo) {
    cout << "\n=== NOTIFICACIONES ===\n";

    // Notificaciones simuladas personalizadas (si querés usar el correo)
    cout << "- ¡Hola " << correo << "! No olvides revisar tus eventos para este fin de semana.\n";
    cout << "- Hay un nuevo evento recomendado en tu ciudad.\n";
    cout << "- Recordatorio: deja un comentario en el último evento que asististe.\n";
}

void verMisBoletos(const string& correoCliente) {
    ifstream archivo("boletos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de boletos." << endl;
        return;
    }

    string linea;
    bool encontrado = false;
    cout << "\n=== TUS BOLETOS ===\n";
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string correo, evento;
        getline(ss, correo, ',');
        getline(ss, evento);

        if (correo == correoCliente) {
            cout << "- Evento registrado: " << evento << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No tenés boletos registrados todavía.\n";

    archivo.close();
}

void registrarBoleto(const string& correoCliente, const string& nombreEvento) {
    ofstream archivo("boletos.txt", ios::app);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir boletos.txt\n";
        return;
    }

    archivo << correoCliente << "," << nombreEvento << endl;
    archivo.close();
    cout << "\nTe has registrado exitosamente al evento: " << nombreEvento << endl;
}

void mostrarEventosRecomendados(const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo de eventos.\n";
        return;
    }

    cout << "Ingrese una palabra clave (ej: musica, cine, arte): ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    string linea;
    bool hayCoincidencias = false;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string datos[16]; // suponemos 16 campos
        for (int i = 0; i < 16; ++i)
            getline(ss, datos[i], ',');

        if (datos[6].find(keyword) != string::npos) { // etiqueta
            hayCoincidencias = true;
            cout << "\nEvento: " << datos[0] << " | Etiqueta: " << datos[6] << " | Ciudad: " << datos[11] << endl;
        }
    }

    if (!hayCoincidencias)
        cout << "No se encontraron eventos con esa etiqueta.\n";

    file.close();
}

void buscarEventosDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de eventos." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, fecha, horaInicio, horaFinal, descripcion, estado, etiqueta;
        string cantidadStr, distanciaStr, precioStr, pais, ciudad, direccion, latStr, lonStr, organizador;

        getline(ss, nombre, ',');
        getline(ss, fecha, ',');
        getline(ss, horaInicio, ',');
        getline(ss, horaFinal, ',');
        getline(ss, descripcion, ',');
        getline(ss, estado, ',');
        getline(ss, etiqueta, ',');
        getline(ss, cantidadStr, ',');
        getline(ss, distanciaStr, ',');
        getline(ss, precioStr, ',');
        getline(ss, pais, ',');
        getline(ss, ciudad, ',');
        getline(ss, direccion, ',');
        getline(ss, latStr, ',');
        getline(ss, lonStr, ',');
        getline(ss, organizador);

        cout << "\nEvento: " << nombre
            << "\nFecha: " << fecha
            << "\nHora: " << horaInicio << " - " << horaFinal
            << "\nDescripcion: " << descripcion
            << "\nEtiqueta: " << etiqueta
            << "\nUbicacion: " << ciudad << ", " << pais
            << "\nPrecio: $" << precioStr
            << "\nOrganizador: " << organizador
            << "\n-----------------------------\n";
    }
    archivo.close();
}

string obtenerNombrePorCorreo(const Organizador& gestor, const string& correo) {
    Nodo* actual = gestor.getCabeza();
    while (actual != nullptr) {
        if (actual->getDato().getCorreo() == correo) {
            return actual->getDato().getNombre();
        }
        actual = actual->getSiguiente();
    }
    return "Desconocido";
}

