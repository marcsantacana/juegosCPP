#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

// Nombre de caselles per arribar a la meta.
const int META = 50;

// Enumeració per als diferents tipus d'objectes que els jugadors poden obtenir.
enum Objecte {
    CAP,
    DAU_ADICIONAL,
    RETROCEDEIX_ENEMIC,
	// Poso "avanza" perque amb la ç no em deixa compilar.
    AVANZA_1_3
};

// Estructura per representar un jugador.
struct Jugador {
    // Posició actual del jugador.
    int posicio;
    // Objecte que el jugador té actualment.
    Objecte objecte;
};

// Funció per tirar un dau i obtenir un número entre 1 i 6.
int tirarDau() {
    return rand() % 6 + 1;
}

// Funció per mostrar les posicions dels jugadors.
void mostrarPosicions(const Jugador& jugador1, const Jugador& jugador2) {
    std::cout << "Jugador 1 esta a la casella " << jugador1.posicio << std::endl;
    std::cout << "Jugador 2 esta a la casella " << jugador2.posicio << std::endl;
}

// Funció per intercanviar les posicions dels jugadors en caselles especials.
void intercanviarPosicions(Jugador& jugador1, Jugador& jugador2, int casella1, int casella2) {
    if (jugador1.posicio == casella1) {
        jugador1.posicio = casella2;
    }
    else if (jugador1.posicio == casella2) {
        jugador1.posicio = casella1;
    }
    if (jugador2.posicio == casella1) {
        jugador2.posicio = casella2;
    }
    else if (jugador2.posicio == casella2) {
        jugador2.posicio = casella1;
    }
}

// Funció per aplicar l'efecte de l'objecte del jugador.
void aplicarObjecte(Jugador& jugador, Jugador& rival) {
    if (jugador.objecte == DAU_ADICIONAL) {
        std::cout << "Tens un Dau adicional! Tira dos daus." << std::endl;
        jugador.posicio += tirarDau();
        jugador.posicio += tirarDau();
    }
    else if (jugador.objecte == RETROCEDEIX_ENEMIC) {
        std::cout << "Tens un Retrocedeix enemic! El rival retrocedeix." << std::endl;
        int retrocedeix = tirarDau();
        rival.posicio -= retrocedeix;
        if (rival.posicio < 0) rival.posicio = 0;
    }
    else if (jugador.objecte == AVANZA_1_3) {
        std::cout << "Tens un Avanza 1-3! Tria quantes caselles vols avanzar (1-3)." << std::endl;
		// Poso "avanza" perque amb la ç no em deixa compilar.
        int avanza;
        std::cin >> avanza;
        if (avanza < 1) avanza = 1;
        if (avanza > 3) avanza = 3;
        jugador.posicio += avanza;
    }
    // Després d'utilitzar l'objecte, el jugador ja no el té.
    jugador.objecte = CAP;
}

// Funció per obtenir un objecte aleatori si el jugador no en té cap.
void obtenirObjecte(Jugador& jugador) {
    if (jugador.objecte == CAP) {
        int objecte = rand() % 3 + 1;
        jugador.objecte = static_cast<Objecte>(objecte);
        std::cout << "Has obtingut un objecte!" << std::endl;
    }
}

// Funció per jugar un torn del jugador.
void jugarTorn(Jugador& jugador, Jugador& rival) {
    // Comprovar si el jugador té un objecte i si vol utilitzar-lo.
    if (jugador.objecte != CAP) {
        std::cout << "Tens un objecte. Vols utilitzar-lo? (s/n)" << std::endl;
        char resposta;
        std::cin >> resposta;
        if (resposta == 's') {
            aplicarObjecte(jugador, rival);
        }
    }

    // Tirar el dau i avançar la posició del jugador.
    int tirada = tirarDau();
    std::cout << "Has tirat un " << tirada << std::endl;
    jugador.posicio += tirada;

    // Comprovar si el jugador ha caigut en una casella múltiple de 5.
    if (jugador.posicio % 5 == 0) {
        std::cout << "Has caigut en una casella multiple de 5! Tira de nou." << std::endl;
        jugador.posicio += tirarDau();
    }

    // Comprovar si el jugador ha caigut en una casella especial per intercanviar posicions.
    if (jugador.posicio == 7 || jugador.posicio == 12) {
        intercanviarPosicions(jugador, rival, 7, 12);
    }
    else if (jugador.posicio == 19 || jugador.posicio == 24) {
        intercanviarPosicions(jugador, rival, 19, 24);
    }
    else if (jugador.posicio == 31 || jugador.posicio == 40) {
        intercanviarPosicions(jugador, rival, 31, 40);
    }

    // Comprovar si el jugador ha caigut en una casella per obtenir un objecte.
    if (jugador.posicio == 3 || jugador.posicio == 13 || jugador.posicio == 23 || jugador.posicio == 33 || jugador.posicio == 43) {
        obtenirObjecte(jugador);
    }

    // Assegurar que la posició del jugador no supera la meta.
    if (jugador.posicio >= META) {
        jugador.posicio = META;
    }
}

int main() {
    std::cout << " + - - - - - - - - - - - - - - - - - - + " << std::endl;
    std::cout << " |     juegoCarreras - Marc Santacana  |" << std::endl;
    std::cout << " + - - - - - - - - - - - - - - - - - - + " << std::endl;

    // Inicialitzar el generador de nombres aleatoris.
    srand(static_cast<unsigned int>(time(0)));

    // Inicialitzar el jugador 1.
    Jugador jugador1 = { 0, CAP };
    // Inicialitzar el jugador 2.
    Jugador jugador2 = { 0, CAP };

    // Bucle principal del joc.
    while (jugador1.posicio < META && jugador2.posicio < META) {
        std::cout << "Torn del Jugador 1" << std::endl;
        jugarTorn(jugador1, jugador2);
        mostrarPosicions(jugador1, jugador2);

        if (jugador1.posicio >= META) break;

        std::cout << "Torn del Jugador 2" << std::endl;
        jugarTorn(jugador2, jugador1);
        mostrarPosicions(jugador1, jugador2);
    }

    // Determinar el guanyador.
    if (jugador1.posicio >= META) {
        std::cout << "Jugador 1 ha guanyat!" << std::endl;
    }
    else {
        std::cout << "Jugador 2 ha guanyat!" << std::endl;
    }
    return 0;
}