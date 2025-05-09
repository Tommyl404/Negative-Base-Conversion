#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

// Convert single digit character to integer
int charToDigit(char c) {
    if (std::isdigit(c)) return c - '0';
    if (std::isalpha(c)) return std::toupper(c) - 'A' + 10;
    throw std::invalid_argument("Invalid character in input");
}

int negativeRadixToDecimal(const std::string& input, int radix) {
    if (radix >= 0 || radix < -36) {
        throw std::invalid_argument("Radix must be negative and >= -36");
    }

    int result = 0;
    int power = 1;
    int absRadix = std::abs(radix);

    for (int i = input.size() - 1; i >= 0; --i) {
        int digit = charToDigit(input[i]);
        if (digit >= absRadix) {
            throw std::invalid_argument("Digit out of range for given radix");
        }
        result += digit * power;
        power *= radix;
    }

    return result;
}

int main() {
    std::string input;
    int radix;

    std::cout << "Enter number in negative base (e.g. 1A for base -16): ";
    std::cin >> input;
    std::cout << "Enter negative base (e.g. -2, -10, -16): ";
    std::cin >> radix;

    try {
        int decimal = negativeRadixToDecimal(input, radix);
        std::cout << input << " in base " << radix << " is " << decimal << " in decimal." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
