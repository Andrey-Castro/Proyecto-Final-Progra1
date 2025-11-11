#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
#include <iomanip>  
#include <sstream>
using namespace std;

struct Usuario {
    string nombre;
    string apellidos;
    int edad;
    string correo;
    string cedula;
    string cuentaBancaria;
    string telefono;
    double saldo;
};


bool esMayorDeEdad(int edad);
void registrarUsuario();
void iniciarSesion();
void menuUsuario(Usuario& u);
void depositarDinero(Usuario& u);
void actualizarSaldoEnArchivo(const Usuario& u);

int main() {
    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         🏆  KickOffBet  🏆\n";
        cout << "    Sistema de Apuestas Deportivas\n";
        cout << "=====================================\n";
        cout << "1. Registrar nuevo jugador\n";
        cout << "2. Iniciar Sesion\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarUsuario();
            break;
        case 2:
            iniciarSesion();
            break;

        case 3:
            cout << "\nGracias por visitar KickOffBet. ¡Hasta pronto!\n";
            break;
        default:
            cout << "⚠️  Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}

void registrarUsuario() {
    Usuario u;
    cout << "\n=== REGISTRO DE NUEVO JUGADOR ===\n";

    cout << "Nombre: ";
    cin >> u.nombre;

    cout << "Apellidos: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, u.apellidos);

    cout << "Edad: ";
    cin >> u.edad;

    if (!esMayorDeEdad(u.edad)) {
        cout << "❌ Lo sentimos, solo mayores de 18 años pueden registrarse en KickOffBet.\n";
        return;
    }

    cout << "Correo electrónico: ";
    cin >> u.correo;

    cout << "Cédula: ";
    cin >> u.cedula;

    cout << "Cuenta bancaria: ";
    cin >> u.cuentaBancaria;

    cout << "Número de teléfono: ";
    cin >> u.telefono;

    u.saldo = 100.0; // saldo inicial ficticio

    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << u.nombre << ","
            << u.apellidos << ","
            << u.edad << ","
            << u.correo << ","
            << u.cedula << ","
            << u.cuentaBancaria << ","
            << u.telefono << ","
            << u.saldo << endl;
        archivo.close();
        cout << "\n✅ Bienvenido a KickOffBet, " << u.nombre << "!\n";
        cout << "Tu registro se ha completado correctamente.\n";
        cout << "Saldo inicial: $" << u.saldo << endl;
    }
    else {
        cout << "⚠️ Error al abrir el archivo de registro.\n";
    }
}

bool esMayorDeEdad(int edad) {
    return edad >= 18;
}
void iniciarSesion() {
    string correo, cedula;
    cout << "\n=== INICIO DE SESIÓN ===\n";
    cout << "Correo: ";
    cin >> correo;
    cout << "Cédula: ";
    cin >> cedula;

    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "⚠️ No se pudo abrir el archivo de usuarios.\n";
        return;
    }
    Usuario u;
    string nombre, apellidos, edadStr, correoLeido, cedulaLeida, cuenta, tel, saldoStr;
    bool encontrado = false;

    while (getline(archivo, nombre, ',')) {
        getline(archivo, apellidos, ',');
        getline(archivo, edadStr, ',');
        getline(archivo, correoLeido, ',');
        getline(archivo, cedulaLeida, ',');
        getline(archivo, cuenta, ',');
        getline(archivo, tel, ',');
        getline(archivo, saldoStr, '\n');

        if (correoLeido == correo && cedulaLeida == cedula) {
            // ✅ Cargar correctamente todos los datos del usuario
            u.nombre = nombre;
            u.apellidos = apellidos;
            u.edad = stoi(edadStr);
            u.correo = correoLeido;
            u.cedula = cedulaLeida;
            u.cuentaBancaria = cuenta;
            u.telefono = tel;
            u.saldo = stod(saldoStr);
            cout << "\n👤 Bienvenido de nuevo, " << nombre << " " << apellidos << "!\n";
            cout << "Saldo actual: $" << saldoStr << endl;
            encontrado = true;
            menuUsuario(u);
            break;
        }
    }

    if (!encontrado) {
        cout << "\n❌ Correo o cédula incorrectos.\n";
    }

    archivo.close();
}
void menuUsuario(Usuario& u) {
    int opcion;
    do {
        cout << "\n=== MENÚ DEL USUARIO ===\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Cerrar sesión\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "\n💰 Tu saldo actual es: $" << fixed << setprecision(2) << u.saldo << endl;
            break;
        case 2:
            depositarDinero(u);
            break;
        case 3:
            cout << "\n👋 Sesión cerrada. ¡Hasta pronto, " << u.nombre << "!\n";
            break;
        default:
            cout << "⚠ Opción no válida.\n";
        }
    } while (opcion != 3);
}

void depositarDinero(Usuario& u) {
    double monto;
    cout << "\n=== DEPÓSITO DE DINERO ===\n";
    cout << "Ingrese el monto a depositar: $";
    cin >> monto;

    if (monto <= 0) {
        cout << "⚠ El monto debe ser mayor que 0.\n";
        return;
    }

    u.saldo += monto;
    actualizarSaldoEnArchivo(u);
    cout << "✅ Depósito exitoso. Nuevo saldo: $" << fixed << setprecision(2) << u.saldo << endl;
}

void actualizarSaldoEnArchivo(const Usuario& u) {
    ifstream archivoEntrada("usuarios.txt");
    if (!archivoEntrada.is_open()) {
        cout << "⚠ No se pudo abrir el archivo para actualizar el saldo.\n";
        return;
    }

    vector<string> lineas;
    string linea;
    while (getline(archivoEntrada, linea)) {
        vector<string> campos;
        string temp;
        for (char c : linea) {
            if (c == ',') {
                campos.push_back(temp);
                temp.clear();
            }
            else {
                temp += c;
            }
        }
        campos.push_back(temp);

        if (campos.size() == 8 && campos[3] == u.correo && campos[4] == u.cedula) {
            // ✅ guarda el saldo correctamente con 2 decimales
            campos[7] = to_string(u.saldo);
        }

        string nuevaLinea;
        for (size_t i = 0; i < campos.size(); ++i) {
            nuevaLinea += campos[i];
            if (i != campos.size() - 1)
                nuevaLinea += ",";
        }
        lineas.push_back(nuevaLinea);
    }
    archivoEntrada.close();

    ofstream archivoSalida("usuarios.txt", ios::trunc);
    for (const auto& l : lineas) {
        archivoSalida << l << endl;
    }
    archivoSalida.close();
}