#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <cstdlib>
#include <iomanip>  
#include <sstream>
using namespace std;

// 🎨 COLORES ANSI
#define RESET "\033[0m"
#define ROJO "\033[31m"
#define VERDE "\033[32m"
#define AMARILLO "\033[33m"
#define AZUL "\033[34m"
#define MAGENTA "\033[35m"
#define CIAN "\033[36m"
#define BLANCO "\033[37m"
#define NEGRITA "\033[1m"

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


// ⬇️ AGREGAR ESTAS DOS ESTRUCTURAS AQUÍ ⬇️
struct Partido {
    int id = 0;
    string liga = "";
    string equipoLocal = "";
    string equipoVisitante = "";
    double cuotaLocal = 0.0;
    double cuotaEmpate = 0.0;
    double cuotaVisitante = 0.0;
    string fecha = "";
};

struct Apuesta {
    int idPartido = 0;
    string equipoApostado = "";
    double cuota = 0.0;
    double monto = 0.0;
};


bool esMayorDeEdad(int edad);
void registrarUsuario();
void iniciarSesion();
void menuUsuario(Usuario& u);
void depositarDinero(Usuario& u);
void actualizarSaldoEnArchivo(const Usuario& u);

// ⬇️ AGREGAR ESTAS DECLARACIONES AQUÍ ⬇️
void verPartidosDisponibles();
void crearApuesta(Usuario& u);
void verMisApuestas(const Usuario& u);
void inicializarPartidos();
vector<Partido> cargarPartidos();
void guardarApuesta(const Usuario& u, const vector<Apuesta>& apuestas, double cuotaTotal, double montoTotal);

int main() {
    inicializarPartidos();
    int opcion;

    do {
        cout << AMARILLO <<"\n=====================================\n";
        cout << VERDE << "        🏆  KickOffBet  🏆\n";
        cout << CIAN <<"    Sistema de Apuestas Deportivas\n";
        cout << AMARILLO << "=====================================\n";
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
            cout << VERDE << "\nGracias por visitar KickOffBet. ¡Hasta pronto!\n";
            break;
        default:
            cout << ROJO << "⚠  Opción no válida. Intente de nuevo.\n";
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
        cout << "⚠ Error al abrir el archivo de registro.\n";
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
        cout << "⚠ No se pudo abrir el archivo de usuarios.\n";
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

        if (correoLeido == correo && cedulaLeida == cedula)
            u.nombre = nombre;
        u.apellidos = apellidos;
        u.edad = stoi(edadStr);
        u.correo = correoLeido;
        u.cedula = cedulaLeida;
        u.cuentaBancaria = cuenta;
        u.telefono = tel;
        u.saldo = stod(saldoStr); {
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
        cout << "3. Ver partidos disponibles\n";
        cout << "4. Crear apuesta combinada\n";
        cout << "5. Ver mis apuestas\n";
        cout << "6. Cerrar sesión\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "\n💰 Tu saldo actual es: $" << fixed << setprecision(2) << u.saldo << endl;
            break;
        case 2:
            depositarDinero(u);
            break;
        case 3:                          // ⬅️ NUEVO
            verPartidosDisponibles();    // ⬅️ NUEVO
            break;                       // ⬅️ NUEVO
        case 4:                          // ⬅️ NUEVO
            crearApuesta(u);             // ⬅️ NUEVO
            break;                       // ⬅️ NUEVO
        case 5:                          // ⬅️ NUEVO
            verMisApuestas(u);           // ⬅️ NUEVO
            break;                       // ⬅️ NUEVO
        case 6:                          // ⬅️ CAMBIÓ DE 3 A 6
       
            cout << "\n👋 Sesión cerrada. ¡Hasta pronto, " << u.nombre << "!\n";
            break;
        default:
            cout << "⚠ Opción no válida.\n";
        }
    } while (opcion != 6);
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
void inicializarPartidos() {
    ofstream archivo("partidos.txt", ios::trunc);
    if (archivo.is_open()) {
        // La Liga
        archivo << "1,La Liga,Real Madrid,Barcelona,2.10,3.40,3.20,2024-12-15\n";
        archivo << "2,La Liga,Atletico Madrid,Sevilla,1.85,3.50,4.00,2024-12-16\n";
        archivo << "3,La Liga,Valencia,Villarreal,2.50,3.20,2.80,2024-12-17\n";

        // Premier League
        archivo << "4,Premier League,Manchester City,Liverpool,2.30,3.60,2.90,2024-12-15\n";
        archivo << "5,Premier League,Arsenal,Chelsea,2.20,3.30,3.10,2024-12-16\n";
        archivo << "6,Premier League,Manchester United,Tottenham,2.60,3.40,2.70,2024-12-17\n";

        // Serie A
        archivo << "7,Serie A,Juventus,Inter Milan,2.40,3.20,2.95,2024-12-15\n";
        archivo << "8,Serie A,AC Milan,Napoli,2.35,3.25,3.00,2024-12-16\n";
        archivo << "9,Serie A,Roma,Lazio,2.15,3.30,3.40,2024-12-17\n";

        // Bundesliga
        archivo << "10,Bundesliga,Bayern Munich,Borussia Dortmund,1.90,3.70,3.80,2024-12-15\n";
        archivo << "11,Bundesliga,RB Leipzig,Bayer Leverkusen,2.25,3.40,3.00,2024-12-16\n";

        // Ligue 1
        archivo << "12,Ligue 1,PSG,Marseille,1.75,3.80,4.50,2024-12-15\n";
        archivo << "13,Ligue 1,Lyon,Monaco,2.45,3.30,2.85,2024-12-16\n";

        archivo.close();
    }
}

vector<Partido> cargarPartidos() {
    vector<Partido> partidos;
    ifstream archivo("partidos.txt");

    if (!archivo.is_open()) {
        return partidos;
    }

    string linea;
    while (getline(archivo, linea)) {
        Partido p;
        stringstream ss(linea);
        string temp;

        getline(ss, temp, ','); p.id = stoi(temp);
        getline(ss, p.liga, ',');
        getline(ss, p.equipoLocal, ',');
        getline(ss, p.equipoVisitante, ',');
        getline(ss, temp, ','); p.cuotaLocal = stod(temp);
        getline(ss, temp, ','); p.cuotaEmpate = stod(temp);
        getline(ss, temp, ','); p.cuotaVisitante = stod(temp);
        getline(ss, p.fecha, ',');

        partidos.push_back(p);
    }

    archivo.close();
    return partidos;
}

void verPartidosDisponibles() {
    vector<Partido> partidos = cargarPartidos();

    if (partidos.empty()) {
        cout << "⚠ No hay partidos disponibles.\n";
        return;
    }

    cout << "\n======================================== PARTIDOS DISPONIBLES ========================================\n";
    cout << left << setw(4) << "ID" << setw(18) << "LIGA" << setw(20) << "LOCAL"
        << setw(20) << "VISITANTE" << setw(8) << "LOCAL" << setw(8) << "EMPATE"
        << setw(8) << "VISIT." << "FECHA\n";
    cout << "======================================================================================================\n";

    for (const auto& p : partidos) {
        cout << left << setw(4) << p.id
            << setw(18) << p.liga
            << setw(20) << p.equipoLocal
            << setw(20) << p.equipoVisitante
            << setw(8) << fixed << setprecision(2) << p.cuotaLocal
            << setw(8) << p.cuotaEmpate
            << setw(8) << p.cuotaVisitante
            << p.fecha << endl;
    }
    cout << "======================================================================================================\n";
}

void crearApuesta(Usuario& u) {
    vector<Partido> partidos = cargarPartidos();

    if (partidos.empty()) {
        cout << "⚠ No hay partidos disponibles.\n";
        return;
    }

    cout << "\n=== CREAR APUESTA COMBINADA ===\n";
    cout << "Puedes combinar partidos de diferentes ligas\n";

    vector<Apuesta> apuestas;
    char continuar = 's';
    double cuotaTotal = 1.0;

    while (continuar == 's' || continuar == 'S') {
        verPartidosDisponibles();

        int idPartido;
        cout << "\nIngrese el ID del partido: ";
        cin >> idPartido;

        // Buscar el partido
        Partido* partidoSeleccionado = nullptr;
        for (auto& p : partidos) {
            if (p.id == idPartido) {
                partidoSeleccionado = &p;
                break;
            }
        }

        if (partidoSeleccionado == nullptr) {
            cout << "❌ Partido no encontrado.\n";
            continue;
        }

        cout << "\n" << partidoSeleccionado->equipoLocal << " vs " << partidoSeleccionado->equipoVisitante << "\n";
        cout << "1. " << partidoSeleccionado->equipoLocal << " (Cuota: " << partidoSeleccionado->cuotaLocal << ")\n";
        cout << "2. Empate (Cuota: " << partidoSeleccionado->cuotaEmpate << ")\n";
        cout << "3. " << partidoSeleccionado->equipoVisitante << " (Cuota: " << partidoSeleccionado->cuotaVisitante << ")\n";

        int opcion;
        cout << "Seleccione su apuesta: ";
        cin >> opcion;

        Apuesta a;
        a.idPartido = idPartido;

        switch (opcion) {
        case 1:
            a.equipoApostado = partidoSeleccionado->equipoLocal;
            a.cuota = partidoSeleccionado->cuotaLocal;
            break;
        case 2:
            a.equipoApostado = "Empate";
            a.cuota = partidoSeleccionado->cuotaEmpate;
            break;
        case 3:
            a.equipoApostado = partidoSeleccionado->equipoVisitante;
            a.cuota = partidoSeleccionado->cuotaVisitante;
            break;
        default:
            cout << "❌ Opción no válida.\n";
            continue;
        }

        apuestas.push_back(a);
        cuotaTotal *= a.cuota;

        cout << "✅ Apuesta agregada: " << a.equipoApostado << " (Cuota: " << a.cuota << ")\n";
        cout << "Cuota total acumulada: " << fixed << setprecision(2) << cuotaTotal << "\n";

        cout << "\n¿Desea agregar otro partido a la apuesta combinada? (s/n): ";
        cin >> continuar;
    }

    if (apuestas.empty()) {
        cout << "❌ No se agregaron apuestas.\n";
        return;
    }

    // Mostrar resumen
    cout << "\n=== RESUMEN DE APUESTA COMBINADA ===\n";
    for (size_t i = 0; i < apuestas.size(); ++i) {
        cout << i + 1 << ". Partido #" << apuestas[i].idPartido
            << " - " << apuestas[i].equipoApostado
            << " (Cuota: " << apuestas[i].cuota << ")\n";
    }
    cout << "Cuota total: " << fixed << setprecision(2) << cuotaTotal << "\n";

    double monto;
    cout << "\nIngrese el monto a apostar: $";
    cin >> monto;

    if (monto <= 0) {
        cout << "❌ El monto debe ser mayor que 0.\n";
        return;
    }

    if (monto > u.saldo) {
        cout << "❌ Saldo insuficiente. Tu saldo actual es: $" << u.saldo << endl;
        return;
    }

    double gananciasPotenciales = monto * cuotaTotal;
    cout << "\nGanancias potenciales: $" << fixed << setprecision(2) << gananciasPotenciales << "\n";

    char confirmar;
    cout << "¿Confirmar apuesta? (s/n): ";
    cin >> confirmar;

    if (confirmar == 's' || confirmar == 'S') {
        u.saldo -= monto;
        actualizarSaldoEnArchivo(u);
        guardarApuesta(u, apuestas, cuotaTotal, monto);

        cout << "\n✅ ¡Apuesta realizada con éxito!\n";
        cout << "Nuevo saldo: $" << fixed << setprecision(2) << u.saldo << endl;
    }
    else {
        cout << "❌ Apuesta cancelada.\n";
    }
}

void guardarApuesta(const Usuario& u, const vector<Apuesta>& apuestas, double cuotaTotal, double montoTotal) {
    ofstream archivo("apuestas.txt", ios::app);
    if (archivo.is_open()) {
        time_t now = time(0);
        tm tiempoLocal;
#ifdef _WIN32
        localtime_s(&tiempoLocal, &now);
#else
        localtime_r(&now, &tiempoLocal);
#endif

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tiempoLocal);
        string fecha = buffer;

        archivo << u.cedula << "|" << fecha << "|" << montoTotal << "|" << cuotaTotal << "|";

        for (size_t i = 0; i < apuestas.size(); ++i) {
            archivo << apuestas[i].idPartido << ":" << apuestas[i].equipoApostado << ":" << apuestas[i].cuota;
            if (i < apuestas.size() - 1) {
                archivo << ";";
            }
        }
        archivo << endl;
        archivo.close();
    }
}

void verMisApuestas(const Usuario& u) {
    ifstream archivo("apuestas.txt");
    if (!archivo.is_open()) {
        cout << "⚠ No tienes apuestas registradas.\n";
        return;
    }

    vector<Partido> partidos = cargarPartidos();
    bool tieneApuestas = false;
    string linea;
    int numeroApuesta = 1;

    cout << "\n=== MIS APUESTAS ===\n";

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string cedula, fecha, monto, cuotaTotal, partidosStr;

        getline(ss, cedula, '|');

        if (cedula != u.cedula) continue;

        tieneApuestas = true;

        getline(ss, fecha, '|');
        getline(ss, monto, '|');
        getline(ss, cuotaTotal, '|');
        getline(ss, partidosStr, '|');

        cout << "\n--- Apuesta #" << numeroApuesta++ << " ---\n";
        cout << "Fecha: " << fecha << "\n";
        cout << "Monto apostado: $" << fixed << setprecision(2) << stod(monto) << "\n";
        cout << "Cuota total: " << stod(cuotaTotal) << "\n";
        cout << "Ganancia potencial: $" << stod(monto) * stod(cuotaTotal) << "\n";
        cout << "Partidos:\n";

        stringstream ssPartidos(partidosStr);
        string partido;
        int num = 1;

        while (getline(ssPartidos, partido, ';')) {
            stringstream ssPartido(partido);
            string idStr, equipo, cuota;

            getline(ssPartido, idStr, ':');
            getline(ssPartido, equipo, ':');
            getline(ssPartido, cuota, ':');

            int id = stoi(idStr);
            for (const auto& p : partidos) {
                if (p.id == id) {
                    cout << "  " << num++ << ". " << p.equipoLocal << " vs " << p.equipoVisitante
                        << " - Apuesta: " << equipo << " (Cuota: " << cuota << ")\n";
                    break;
                }
            }
        }
    }

    if (!tieneApuestas) {
        cout << "No tienes apuestas registradas.\n";
    }

    archivo.close();
}
