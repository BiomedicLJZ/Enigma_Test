#include "Enigma.h"
#include <iostream>

void displayMenu() {
    std::cout << "Enigma Machine Configuration Menu" << std::endl;
    std::cout << "1. Set Rotor Positions" << std::endl;
    std::cout << "2. Add Plugboard Mapping" << std::endl;
    std::cout << "3. Encrypt a Message" << std::endl;
    std::cout << "4. Decrypt a Message" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    // Define rotor and reflector wirings
    std::string rotor1Wiring = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    std::string rotor2Wiring = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    std::string rotor3Wiring = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    std::string reflectorWiring = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    // Initialize the Enigma machine with rotor and reflector wirings
    EnigmaMachine enigma(rotor1Wiring, rotor2Wiring, rotor3Wiring, reflectorWiring);

    int choice;
    while (true) {
        displayMenu();
        std::cin >> choice;

        if (choice == 1) {
            int pos1, pos2, pos3;
            std::cout << "Enter Rotor 1 Position (0-25): ";
            std::cin >> pos1;
            std::cout << "Enter Rotor 2 Position (0-25): ";
            std::cin >> pos2;
            std::cout << "Enter Rotor 3 Position (0-25): ";
            std::cin >> pos3;
            enigma.setRotorPositions(pos1, pos2, pos3);
            std::cout << "Rotor positions set to " << pos1 << ", " << pos2 << ", " << pos3 << std::endl;
        } else if (choice == 2) {
            char from, to;
            std::cout << "Enter Plugboard Mapping (e.g., A B): ";
            std::cin >> from >> to;
            enigma.addPlugboardMapping(from, to);
            std::cout << "Plugboard mapping " << from << " -> " << to << " added." << std::endl;
        } else if (choice == 3) {
            std::string message, encryptedMessage;
            std::cout << "Enter message to encrypt: ";
            std::cin >> std::ws; // To ignore any leading whitespaces
            std::getline(std::cin, message);
            for (char c : message) {
                if (c >= 'A' && c <= 'Z') {
                    encryptedMessage += enigma.encode(c);
                } else if (c >= 'a' && c <= 'z') {
                    encryptedMessage += enigma.encode(c - 'a' + 'A');
                } else {
                    encryptedMessage += c; // Non-alphabetic characters are not encoded
                }
            }
            std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
        } else if (choice == 4) {
            std::string message, decryptedMessage;
            std::cout << "Enter message to decrypt: ";
            std::cin >> std::ws; // To ignore any leading whitespaces
            std::getline(std::cin, message);
            for (char c : message) {
                if (c >= 'A' && c <= 'Z') {
                    decryptedMessage += enigma.decode(c);
                } else if (c >= 'a' && c <= 'z') {
                    decryptedMessage += enigma.decode(c - 'a' + 'A');
                } else {
                    decryptedMessage += c; // Non-alphabetic characters are not decoded
                }
            }
            std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
        } else if (choice == 5) {
            std::cout << "Exiting..." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
