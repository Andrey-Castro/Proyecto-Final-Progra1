#include <iostream>
#include <fstream>
#include <string>
#include <limits>
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

