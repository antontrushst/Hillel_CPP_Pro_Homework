// Програма імплементує алгоритми for_each, all, count_if і демонструє їх
// роботу в блоці main.

#include <iostream>
#include <functional>
#include <vector>

// Функція вищого порядку для виконання викликаємої функції над кожним елементом
// вказаного вектора.
void for_each(std::vector<int>& vector, std::function<void(int&)> f)
{
    for (auto& element : vector)
        f(element);
}

bool all(std::vector<int>& vector, std::function<bool(int&)> p)
{
    bool result = true;
    for (auto element : vector)
    {
        result = p(element);
        if (p(element) == false)
            break;
    }
    
    return result;
}

int count_if(std::vector<int>& vector, std::function<bool(int&)> f)
{
    int result = 0;
    for (auto element : vector)
        if (f(element) == true)
            result++;
    
    return result;
}

// Функція, що возводить число у другу ступінь.
void square(int& num)
{
    num *= num;
}

// Функція, що виводить елемент (число) у строку термінала.
void print(int element)
{
    std::cout << element << std::endl;
}

// Функція, що повертає true, якщо число позитивне.
bool is_positive(int& num)
{
    return num > 0;
}

int main()
{
    std::vector<int> vec = {1, 2, 3};

    // Змінна з числом 3 для демонстрації роботи функцій.
    int minus = -1;

    // C-шний вказівник на функцію print для демонстрації приймання вищими
    // функціями подібних вказівників у якості аргументів.
    void (*func_pointer)(int) = &print;

    // Демонстрація for_each.
    std::cout << "\n--- Демонстрація роботи вищої функції for_each ---\n\n"
              << "1. Виведення незміненого вектора за допомогою передачі "
              << "С-шного вказівника:\n";
    for_each(vec, func_pointer);

    std::cout << "\n2. Виклик функції square на кожен елемент:\n";
    for_each(vec, square);
    for_each(vec, func_pointer);

    std::cout << "\n3. Виклик лямбда-функції, що помножує змінну minus на "
              << "кожен елемент:\n";
    for_each(vec, [minus](int& num){ num *= minus; });
    for_each(vec, func_pointer);
    std::cout << "-------------------------------------------------------------";

    // Демонстрація all.
    std::cout << "\n--- Демонстрація роботи вищої функції all ---\n\n";
    std::cout << std::boolalpha;
    std::cout << "1. Чи є всі числа вектора позитивними: "
              << all(vec, is_positive);
    std::cout << "\nВиведемо вектор подивитись:\n";
    for_each(vec, func_pointer);

    std::cout << "\n2. Змінимо знак всіх елементів. Чи є тепер всі позитивними: ";
    for_each(vec, [minus](int& num){ num *= minus; });
    std::cout << all(vec,[](int& num){ return num > 0; });
    std::cout << "\nВиведемо вектор подивитись:\n";
    for_each(vec, func_pointer);

    std::cout << "\n3. Змінимо знак одного елемента. Чи зараз всі позитивні: ";
    vec[1] *= minus;
    std::cout << all(vec, is_positive);
    std::cout << "\nВиведемо вектор подивитись:\n";
    for_each(vec, func_pointer);
    std::cout << "-------------------------------------------------------------";

    // Демонстрація count_if.
    std::cout << "\n--- Демонстрація роботи вищої функції count_if ---\n\n";
    std::cout << "1. Порахуємо позитивні числа останнього вектора: "
              << count_if(vec, is_positive);
    std::cout << "\nВиведемо вектор подивитись:\n";
    for_each(vec, func_pointer);

    std::cout << "\n2. Змінимо друге число вектора теж на позитивне і знов порахуємо "
              << "кількість позитивних чисел: ";
    vec[1] *= minus;
    std::cout << count_if(vec, [](int& num){ return num > 0; });
    std::cout << "\nВиведемо вектор подивитись:\n";
    for_each(vec, func_pointer);

    return 0;
}