#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << " + - - - - - - - - - - - - - - - - - - - +" << std::endl;
    std::cout << " |   juegoAdivinar - Marc Santacana      |" << std::endl;
    std::cout << " + - - - - - - - - - - - - - - - - - - - +" << std::endl;
    std::cout << " " << std::endl;
    // Inicialitzar el generador de nombres aleatoris amb el temps actual.
    srand(static_cast<unsigned int>(time(0)));

    // Definir el rang del número secret.
    const int MIN = 1;
    const int MAX = 100;

    // Seleccionar aleatòriament el número secret dins del rang especificat.
    int numeroSecret = rand() % (MAX - MIN + 1) + MIN;

    // Variables per guardar la suposició del jugador i el nombre d'intents realitzats.
    int intent;
    int intentsRealitzats = 0;
    bool encertat = false;

    // Missatge de benvinguda i instruccions inicials.
    std::cout << " Benvingut al joc de 'Endevina el numero'!" << std::endl;
    std::cout << " Seleccionat un numero secret entre " << MIN << " i " << MAX << "." << std::endl;

    // Bucle principal del joc.
    while (!encertat) {
        // Demanar al jugador que introdueixi la seva suposició.
        std::cout << " Introdueix la resposta: ";
        std::cin >> intent;
        intentsRealitzats++;

        // Comprovar si la suposició del jugador és correcta.
        if (intent == numeroSecret) {
            // El jugador ha encertat el número secret.
            encertat = true;
            std::cout << " Felicitats! Has encertat el numero secret en " << intentsRealitzats << " intents." << std::endl;
        }
        else if (intent < numeroSecret) {
            // Proporcionar una pista si la suposició és menor que el número secret.
            std::cout << " El numero secret es mes gran que " << intent << "." << std::endl;
        }
        else {
            // Proporcionar una pista si la suposició és major que el número secret.
            std::cout << " El numero secret es mes petit que " << intent << "." << std::endl;
        }
    }
    return 0;
}