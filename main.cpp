#include "Enigma.h"
#include <iostream>
#include <string>


int main() {
    // Example Enigma machine setup
    EnigmaMachine enigma("EKMFLGDQVZNTOWYHXUSPAIBRCJ", "AJDKSIRUXBLHWTMCQGZNPYFVOE", "BDFHJLCPRTXVZNYEIWGAKMUSQO", "YRUHQSLDPXNGOKMIEBFZCWVJAT");
    enigma.setRotorPositions(5, 7, 21);

    std::string message = "Esto es un mensaje que jamas van a poder leer los alemanes.";
    std::string encodedMessage;
    std::string decodedMessage;


    for (char c : message) {
        if (isalpha(c)) {
            encodedMessage += enigma.encode(toupper(c));
        } else {
            encodedMessage += c;
        }
    }

    std::cout << "Encoded Message: " << encodedMessage << std::endl;

    // Reset rotor positions
    enigma.setRotorPositions(5, 7, 21);

    for (char c : encodedMessage) {
        if (isalpha(c)) {
            decodedMessage += enigma.decode(toupper(c));
        } else {
            decodedMessage += c;
        }
    }

    std::cout << "Decoded Message: " << decodedMessage << std::endl;

    return 0;
}
