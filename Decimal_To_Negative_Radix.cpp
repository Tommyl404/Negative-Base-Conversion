#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

// Convert int [0..35] to character ('0'-'9', 'A'-'Z')
char digitToChar(int digit) {
    if (digit >= 0 && digit <= 9) return '0' + digit;
    else return 'A' + (digit - 10);
}

// Convert integer part to negative base with step logging
std::string convertIntegerPart(int n, int base) {
    if (n == 0) {
        std::cout << "Step: 0 is 0 in any base.\n";
        return "0";
    }

    std::string result;
    std::cout << "Integer part conversion (decimal: " << n << ", base: " << base << "):\n";
    while (n != 0) {
        int original_n = n;
        int remainder = n % base;
        n /= base;

        if (remainder < 0) {
            remainder += std::abs(base);
            n += 1;
        }

        std::cout << "  n = " << original_n 
                  << ", remainder = " << remainder 
                  << ", updated n = " << n << "\n";

        result = digitToChar(remainder) + result;
    }

    return result;
}

// Convert fractional part to negative base with step logging
std::string convertFractionalPart(double frac, int base, int maxDigits = 10) {
    std::string result;
    int count = 0;

    std::cout << "Fractional part conversion (decimal: " << frac << ", base: " << base << "):\n";

    while (frac != 0 && count < maxDigits) {
        double original = frac;
        frac *= base;
        int digit = static_cast<int>(std::floor(frac));

        if (digit < 0) {
            digit += std::abs(base);
            frac += 1.0;
        }

        std::cout << "  Step " << count+1 << ": frac × base = " << original << " × " << base
                  << " = " << frac << ", digit = " << digit << ", remaining frac = " << frac - digit << "\n";

        result += digitToChar(digit);
        frac -= digit;
        count++;
    }

    return result;
}

// Main conversion function with logging
std::string decimalToNegativeBase(double value, int base, int maxFracDigits = 10) {
    if (base >= 0 || base < -36) {
        throw std::invalid_argument("Base must be negative and >= -36");
    }

    std::cout << "\n=== Converting " << value << " to base " << base << " ===\n";

    int intPart = static_cast<int>(std::floor(std::abs(value)));
    double fracPart = std::abs(value) - intPart;
    if (value < 0) intPart = -intPart;

    std::string intStr = convertIntegerPart(intPart, base);
    std::string fracStr = convertFractionalPart(fracPart, base, maxFracDigits);

    std::cout << "=== Final result ===\n";
    return fracStr.empty() ? intStr : intStr + "." + fracStr;
}
int main() {
    double value;
    int base;

    std::cout << "Enter decimal number: ";
    std::cin >> value;
    std::cout << "Enter negative base (e.g. -2, -10): ";
    std::cin >> base;

    try {
        std::string converted = decimalToNegativeBase(value, base);
        std::cout << value << " in base " << base << " is: " << converted << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
