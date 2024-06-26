#ifndef ENIGMA_H
#define ENIGMA_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

class Rotor {
private:
    std::vector<int> wiring;
    int position;

public:
    Rotor(const std::string& wiringStr, int startPosition) : position(startPosition) {
        for (char c : wiringStr) {
            wiring.push_back(c - 'A');
        }
    }

    void rotate() {
        position = (position + 1) % 26;
    }

    int encodeForward(int input) {
        int index = (input + position) % 26;
        return (wiring[index] - position + 26) % 26;
    }

    int encodeBackward(int input) {
        int index = std::find(wiring.begin(), wiring.end(), (input + position + 26) % 26) - wiring.begin();
        return (index - position + 26) % 26;
    }

    void setStartPosition(int startPosition) {
        position = startPosition;
    }

    int getPosition() const {
        return position;
    }
};

class Reflector {
private:
    std::vector<int> wiring;

public:
    Reflector(const std::string& wiringStr) {
        for (char c : wiringStr) {
            wiring.push_back(c - 'A');
        }
    }

    int reflect(int input) {
        return wiring[input];
    }
};

class Plugboard {
private:
    std::unordered_map<int, int> mapping;

public:
    Plugboard() {
        for (int i = 0; i < 26; ++i) {
            mapping[i] = i;
        }
    }

    void addMapping(char from, char to) {
        int fromIndex = from - 'A';
        int toIndex = to - 'A';
        mapping[fromIndex] = toIndex;
        mapping[toIndex] = fromIndex;
    }

    int map(int input) const {
        return mapping.at(input);
    }
};

class EnigmaMachine {
private:
    Rotor rotor1;
    Rotor rotor2;
    Rotor rotor3;
    Reflector reflector;
    Plugboard plugboard;

public:
    EnigmaMachine(const std::string& rotor1Wiring, const std::string& rotor2Wiring, const std::string& rotor3Wiring,
                  const std::string& reflectorWiring)
            : rotor1(rotor1Wiring, 0), rotor2(rotor2Wiring, 0), rotor3(rotor3Wiring, 0), reflector(reflectorWiring) {}

    void setRotorPositions(int pos1, int pos2, int pos3) {
        rotor1.setStartPosition(pos1);
        rotor2.setStartPosition(pos2);
        rotor3.setStartPosition(pos3);
    }

    void addPlugboardMapping(char from, char to) {
        plugboard.addMapping(from, to);
    }

    char encode(char input) {
        int letter = input - 'A';

        // Pass through plugboard
        letter = plugboard.map(letter);

        // Pass through rotors (forward)
        letter = rotor3.encodeForward(letter);
        letter = rotor2.encodeForward(letter);
        letter = rotor1.encodeForward(letter);

        // Pass through reflector
        letter = reflector.reflect(letter);

        // Pass through rotors (backward)
        letter = rotor1.encodeBackward(letter);
        letter = rotor2.encodeBackward(letter);
        letter = rotor3.encodeBackward(letter);

        // Pass through plugboard again
        letter = plugboard.map(letter);

        // Rotate rotors
        rotor1.rotate();

        if (rotor1.getPosition() % 26 == 0) {
            rotor2.rotate();
        }
        if (rotor2.getPosition() % 26 == 0) {
            rotor3.rotate();
        }

        return static_cast<char>(letter + 'A');
    }

    char decode(char input) {
        // Enigma machine encoding and decoding process are identical.
        return encode(input);
    }
};

#endif // ENIGMA_H
