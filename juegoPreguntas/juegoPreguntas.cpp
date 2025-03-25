#include <iostream>
#include <vector>
#include <string>

// Estructura per a representar una pregunta.
struct Pregunta {
    // String de la pregunta
    std::string pregunta;
    // Vector d'opcions de resposta
    std::vector<std::string> opcions;
    // Índex de la resposta correcta
    int respostaCorrecte;
};

// Funció per fer una pregunta i actualitzar la puntuació i la ratxa
void ferPregunta(const Pregunta& q, int& puntuacio, int& raxa, std::vector<int>& respostesCorrectes, std::vector<int>& respostesIncorrectes) {
    // Mostrar la pregunta i les opcions
    std::cout << q.pregunta << std::endl;
    for (size_t i = 0; i < q.opcions.size(); ++i) {
        std::cout << i + 1 << ". " << q.opcions[i] << std::endl;
    }

    int resposta;
    std::cin >> resposta;

    // Comprovar si la resposta és correcta
    if (resposta - 1 == q.respostaCorrecte) {
        raxa++;
        puntuacio += raxa;
        respostesCorrectes.push_back(resposta);
        std::cout << "Correcte! La teva puntuació actualment és: " << puntuacio << std::endl;
    }
    else {
        raxa = 0;
        puntuacio -= 1;
        respostesIncorrectes.push_back(resposta);
        std::cout << "Incorrecte! La resposta correcta era: " << q.opcions[q.respostaCorrecte] << std::endl;
        std::cout << "La teva puntuació actualment és: " << puntuacio << std::endl;
    }
}

int main() {
    // Vector de preguntes
    // No he posat accents perquè a la terminal es veuen malament.
    std::vector<Pregunta> preguntes = {
        {"Quin és el llenguatge de programació més usat?", {"Python", "C++", "Java", "JavaScript"}, 3},
        {"Quin any va començar Internet?", {"1969", "1983", "1991", "2000"}, 1},
        {"Qui va inventar el llenguatge C?", {"Dennis Ritchie", "Bjarne Stroustrup", "James Gosling", "Guido van Rossum"}, 0},
        {"Quina és la capital de França?", {"Madrid", "Berlín", "París", "Roma"}, 2},
        {"Quants planetes té el sistema solar?", {"7", "8", "9", "10"}, 1},
        {"Quin és l'animal més ràpid del món?", {"Guepard", "Cavall", "Falcó pelegrí", "Lleó"}, 2},
        {"Qui va escriure 'El Quixot'?", {"Miguel de Cervantes", "Lope de Vega", "Garcilaso de la Vega", "Quevedo"}, 0},
        {"Quina és la fórmula química de l'aigua?", {"H2O", "O2", "CO2", "NaCl"}, 0},
        {"Quina és la moneda del Japó?", {"Iuan", "Ien", "Dòlar", "Euro"}, 1},
        {"Quin és el país més gran del món?", {"Canadà", "Estats Units", "Rússia", "Xina"}, 2}
    };

    // Puntuació inicial
    int puntuacio = 0;
    // Ratxa inicial
    int raxa = 0;
    // Respostes correctes
    std::vector<int> respostesCorrectes;
    // Respostes incorrectes
    std::vector<int> respostesIncorrectes;

    // Fer les preguntes
    for (size_t i = 0; i < preguntes.size(); ++i) {
        ferPregunta(preguntes[i], puntuacio, raxa, respostesCorrectes, respostesIncorrectes);
    }

    // Pregunta addicional si la puntuació és inferior a 20
    if (puntuacio < 20) {
        std::cout << "Puntuació per sota de 20. Has de respondre una altra pregunta." << std::endl;
        Pregunta preguntaExtra = { "Quina és la capital d'Itàlia?", {"Berlín", "Madrid", "París", "Roma"}, 3 };
        ferPregunta(preguntaExtra, puntuacio, raxa, respostesCorrectes, respostesIncorrectes);
    }

    // Informar del resultat final
    std::cout << "Game over! La teva puntuació és: " << puntuacio << std::endl;
    std::cout << "Respostes correctes: ";
    for (int ans : respostesCorrectes) {
        std::cout << ans << " ";
    }
    std::cout << std::endl;

    std::cout << "Respostes incorrectes: ";
    for (int ans : respostesIncorrectes) {
        std::cout << ans << " ";
    }
    std::cout << std::endl;

    return 0;
}