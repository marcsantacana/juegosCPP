#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Funció per seleccionar una paraula aleatòria d'una llista predefinida.
std::string seleccionarParaula() {
	// Llista de paraules predefinides. Sense accents perque per terminal no es veuen bé.
    std::vector<std::string> paraules = { "programacio", "ordinador", "teclat", "pantalla", "ratoli" };
    // Seleccionar un índex aleatori dins del rang de la llista de paraules.
    int index = rand() % paraules.size();
    // Retornar la paraula seleccionada.
    return paraules[index];
}

// Funció per mostrar l'estat actual de la paraula endevinada.
void mostrarEstat(const std::string& paraula, const std::vector<bool>& encertades) {
    // Recórrer cada lletra de la paraula
    for (size_t i = 0; i < paraula.size(); ++i) {
        // Si la lletra ha estat encertada, mostrar-la.
        if (encertades[i]) {
            std::cout << paraula[i] << " ";
        }
        else {
            // Si la lletra no ha estat encertada, mostrar un guió baix.
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}

// Funció per revelar una lletra no mostrada quan queden 2 intents.
void revelarLletra(const std::string& paraula, std::vector<bool>& encertades) {
    // Recórrer cada lletra de la paraula.
    for (size_t i = 0; i < paraula.size(); ++i) {
        // Si la lletra no ha estat encertada, revelar-la.
        if (!encertades[i]) {
            encertades[i] = true;
            break;
        }
    }
}

int main() {
	std::cout << " + - - - - - - - - - - - - - - - - - - +" << std::endl;
    std::cout << " |   juagoAhorcado - Marc Santacana    | " << std::endl;
    std::cout << " + - - - - - - - - - - - - - - - - - - +" << std::endl;
    std::cout << " " << std::endl;
    // Inicialitzar el generador de nombres aleatoris.
    srand(static_cast<unsigned int>(time(0)));

    // Seleccionar una paraula aleatòria.
    std::string paraula = seleccionarParaula();
    // Vector per marcar les lletres encertades.
    std::vector<bool> encertades(paraula.size(), false);
    // Nombre d'intents permesos.
    int intents = 6;

    std::cout << " Benvingut al joc de 'El penjat'!" << std::endl;
    std::cout << " La paraula te " << paraula.size() << " lletres." << std::endl;
	std::cout << " " << std::endl;

    // Bucle principal del joc.
    while (intents > 0) {
        // Mostrar l'estat actual de la paraula endevinada.
        mostrarEstat(paraula, encertades);
		std::cout << " " << std::endl;
        std::cout << " Introdueix una lletra: ";
        char lletra;
        std::cin >> lletra;

        bool encert = false;
        // Comprovar si la lletra introduïda està a la paraula.
        for (size_t i = 0; i < paraula.size(); ++i) {
            if (paraula[i] == lletra && !encertades[i]) {
                encertades[i] = true;
                encert = true;
            }
        }

        // Si la lletra no està a la paraula, restar un intent.
        if (!encert) {
            intents--;
            std::cout << " Lletra incorrecta. Et queden " << intents << " intents." << std::endl;
        }

        // Comprovar si el jugador ha endevinat tota la paraula.
        bool completada = true;
        for (bool encertada : encertades) {
            if (!encertada) {
                completada = false;
                break;
            }
        }

        // Si la paraula ha estat completada, felicitar el jugador i acabar el joc.
        if (completada) {
            std::cout << " Felicitats! Has endevinat la paraula: " << paraula << std::endl;
            break;
        }

        // Revelar una lletra si queden 2 intents.
        if (intents == 2) {
            revelarLletra(paraula, encertades);
            std::cout << " Se't revela una lletra perque nomes et queden 2 intents." << std::endl;
        }
    }

    // Si el jugador es queda sense intents, mostrar la paraula correcta.
    if (intents == 0) {
        std::cout << " Has perdut! La paraula era: " << paraula << std::endl;
    }
    return 0;
}