#include "Enigma.h"

int main() {
    // Define rotor and reflector wirings
    std::string rotor1Wiring = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    std::string rotor2Wiring = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    std::string rotor3Wiring = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    std::string reflectorWiring = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    // Initialize the Enigma machine with rotor and reflector wirings
    EnigmaMachine enigma(rotor1Wiring, rotor2Wiring, rotor3Wiring, reflectorWiring);

    // Set initial rotor positions
    enigma.setRotorPositions(5, 12, 21); // Positions for rotor1, rotor2, and rotor3

    // Add plugboard mappings
    enigma.addPlugboardMapping('A', 'B');
    enigma.addPlugboardMapping('C', 'Z');
    enigma.addPlugboardMapping('E', 'H');
    enigma.addPlugboardMapping('T', 'Y');
    enigma.addPlugboardMapping('M', 'L');

    // Encode a single character
    char encodedChar = enigma.encode('H');
    std::cout << "Encoded Character: " << encodedChar << std::endl;

    // Encode a string
    std::string message = "HELLO";
    std::string encodedMessage;
    for (char c : message) {
        encodedMessage += enigma.encode(c);
    }
    std::cout << "Encoded Message: " << encodedMessage << std::endl;

    return 0;
}
