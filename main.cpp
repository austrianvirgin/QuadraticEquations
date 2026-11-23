#include "Quadratic.h"

int main() {
    try {
        std::cout << "Тест 1: x^2 - 4x + 3\n";
        RealValue a1(1), b1(-4), c1(3);
        Value *res11 = nullptr;
        Value *res12 = nullptr;
        Solve(a1, b1, c1, res11, res12);
        std::cout << "Корень 1: ";
        res11 -> Print(); std::cout << "\n";
        std::cout << "Корень 2: ";
        res12 -> Print(); std::cout << "\n";
        delete res11; delete res12;
    
        std::cout << "Тест 2: x^2 + 3\n";
        ComplexValue a2(1), b2(0), c2(3);
        Value *res21 = nullptr;
        Value *res22 = nullptr;
        Solve(a2, b2, c2, res21, res22);
        std::cout << "Корень 1: ";
        res21 -> Print(); std::cout << "\n";
        std::cout << "Корень 2: ";
        res22 -> Print(); std::cout << "\n";
        delete res21; delete res22;
    
        std::cout << "Тест 3: ошибка, корень из отрицательного числа\n";
        RealValue a3(1), b3(0), c3(1);
        Value *res31 = nullptr;
        Value *res32 = nullptr;
        Solve(a3, b3, c3, res31, res32);
        
    }
    catch (const Error& e) {
        std::cerr << "Перехвачено исключение: " << e.what() << "\n";
    }    
    return 0;
}
