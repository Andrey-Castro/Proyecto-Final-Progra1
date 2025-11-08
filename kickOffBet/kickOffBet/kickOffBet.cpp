#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
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

int main() {
    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         🏆  KickOffBet  🏆\n";
        cout << "    Sistema de Apuestas Deportivas\n";
        cout << "=====================================\n";
        cout << "1. Registrar nuevo jugador\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarUsuario();
            break;
        case 2:
            cout << "\nGracias por visitar KickOffBet. ¡Hasta pronto!\n";
            break;
        default:
            cout << "⚠️  Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 2);

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

bool esMayorDeEdad(int edad) {
    return edad >= 18;
}

void registrarUsuario() {
    Usuario u;

    cout << "\n=== REGISTRO DE NUEVO JUGADOR ===\n";
    cout << "Nombre: ";
    cin >> u.nombre;
    cout << "Apellidos (sin espacios): ";
    cin >> u.apellidos;
    cout << "Edad: ";
    cin >> u.edad;

    if (!esMayorDeEdad(u.edad)) {
        cout << "❌ Solo mayores de 18 años pueden registrarse.\n";
        return;
    }

    cout << "Correo electrónico: ";
    cin >> u.correo;
    cout << "Cédula: ";
    cin >> u.cedula;
    cout << "Cuenta bancaria: ";
    cin >> u.cuentaBancaria;
    cout << "Teléfono: ";
    cin >> u.telefono;

    u.saldo = 100.0;

    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << u.nombre << "," << u.apellidos << "," << u.edad << ","
                << u.correo << "," << u.cedula << "," << u.cuentaBancaria << ","
                << u.telefono << "," << u.saldo << endl;
        archivo.close();
        cout << "\n✅ Registro completado con éxito. ¡Bienvenido, " << u.nombre << "!\n";
    } else {
        cout << "⚠️ Error al guardar el archivo.\n";
    }
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

    string nombre, apellidos, edadStr, correoLeido, cedulaLeida, cuenta, tel, saldoStr;
    bool encontrado = false;

    while (archivo.good()) {
        getline(archivo, nombre, ',');
        getline(archivo, apellidos, ',');
        getline(archivo, edadStr, ',');
        getline(archivo, correoLeido, ',');
        getline(archivo, cedulaLeida, ',');
        getline(archivo, cuenta, ',');
        getline(archivo, tel, ',');
        getline(archivo, saldoStr, '\n');

        if (correoLeido == correo && cedulaLeida == cedula) {
            cout << "\n👤 Bienvenido de nuevo, " << nombre << " " << apellidos << "!\n";
            cout << "Saldo actual: $" << saldoStr << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "\n❌ Correo o cédula incorrectos.\n";
    }

    archivo.close();
}

int main() {
    int opcion;

    do {
        cout << "\n=====================================\n";
        cout << "         🏆  KickOffBet  🏆\n";
        cout << "    Sistema de Apuestas Deportivas\n";
        cout << "=====================================\n";
        cout << "1. Registrar nuevo jugador\n";
        cout << "2. Iniciar sesión\n";
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
            cout << "⚠️ Opción no válida.\n";
        }
    } while (opcion != 3);

    return 0;
}