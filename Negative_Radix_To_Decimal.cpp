#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

int charToDigit(char c) {
    if (std::isdigit(c)) return c - '0';
    if (std::isalpha(c)) return std::toupper(c) - 'A' + 10;
    throw std::invalid_argument("Invalid character in input");
}

double negativeRadixToDecimal(const std::string& input, int radix) {
    if (radix >= 0 || radix < -36) {
        throw std::invalid_argument("Radix must be negative and >= -36");
    }

    std::string intPart, fracPart;
    size_t dotPos = input.find('.');
    if (dotPos != std::string::npos) {
        intPart = input.substr(0, dotPos);
        fracPart = input.substr(dotPos + 1);
    } else {
        intPart = input;
    }

    double result = 0.0;
    int power = 0;
    int absRadix = std::abs(radix);

    // Integer part: right to left
    for (int i = intPart.size() - 1; i >= 0; --i) {
        int digit = charToDigit(intPart[i]);
        if (digit >= absRadix)
            throw std::invalid_argument("Digit out of range for given radix");
        result += digit * std::pow(radix, power++);
    }

    // Fractional part: left to right, powers -1, -2, ...
    double fracPower = radix;
    for (char c : fracPart) {
        int digit = charToDigit(c);
        if (digit >= absRadix)
            throw std::invalid_argument("Digit out of range for given radix");
        result += digit / fracPower;
        fracPower *= radix;
    }

    return result;
}

int main() {
    std::string input;
    int radix;

    std::cout << "Enter number in negative base (e.g. 1A.C): ";
    std::cin >> input;
    std::cout << "Enter negative base (e.g. -2, -10, -16): ";
    std::cin >> radix;

    try {
        double decimal = negativeRadixToDecimal(input, radix);
        std::cout << input << " in base " << radix << " is " << decimal << " in decimal." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
