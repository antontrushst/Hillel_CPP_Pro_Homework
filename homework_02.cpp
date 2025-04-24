// Програма створює власну реалізацію класа unique_ptr та тестує його в блоці main()
#include <iostream>

template <class T>
class UniquePtr
{
private:
    T* m_ptr = nullptr;

public:
    // Конструктор за замовчуванням
    UniquePtr() : m_ptr(nullptr) {}

    // Конструктор з rvalue
    UniquePtr(T* ptr) : m_ptr(ptr) {}

    // Видалений конструктор з lvalue
    UniquePtr(T ptr) = delete;
    
    // Видалений конструктор-копіювальник
    UniquePtr(const UniquePtr&) = delete;

    // Конструктор переміщення
    UniquePtr(UniquePtr&& other) : m_ptr(other.m_ptr)
    {
        other.m_ptr = nullptr;
    }

    // Деструктор
    ~UniquePtr()
    {
        delete(m_ptr);
        m_ptr = nullptr;
    }
    
    // Видалений оператор присвоєння за lvalue
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Оператор присвоєння за rvalue
    UniquePtr& operator=(UniquePtr&& other)
    {
        if (this != &other)
        {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    // Оператор bool, що показує чи володіє юнік чимось чи ні
    operator bool () const
    {
        return m_ptr != nullptr;
    }

    // Геттер для вмісту юніка
    T* get() const
    {
        return m_ptr;
    }

    // Скидання юніка з значенням за замовчуванням nullptr
    void reset(T* ptr = nullptr)
    {
        delete m_ptr;
        m_ptr = ptr;
    }
};

class Test
{
private:
    int* m_int = nullptr;

public:
    Test() : m_int(new int(0)) {}
    Test(int val) :m_int(new int(val)) {}
    ~Test() {}

    int get_my_number() const
    {
        return *m_int;
    }
};

int main()
{
    int* i = new int(3);
    UniquePtr<int> uptr_1;
    UniquePtr<int> uptr_2(i);

    // Перевірка роботи оператора bool
    std::cout << "Перевірка роботи оператора bool:\n";
    if (uptr_1)
        std::cout << "uptr1:\tI own something!\n";
    else
        std::cout << "uptr_1:\tI have nothing.\n";

    if (uptr_2)
        std::cout << "uptr_2:\tI own something!\n";
    else
        std::cout << "uptr_2:\tI have nothing.\n";
        
    // Перевірка роботи геттера та скидання та операторів * і ->
    int* c = new int(5);
    std::cout << "\nПеревірка роботи скидання та операторів * та ->:\n";
    std::cout << "resetting uptr_1 to c(5) ...\n";
    uptr_1.reset(c);
    std::cout << "resetting uptr_2...\n";
    uptr_2.reset();
    std::cout << "*uptr_1: " << *uptr_1 << std::endl;
    if (uptr_2)
        std::cout << "uptr_2:\tI own something!\n";
    else
        std::cout << "uptr_2:\tI have nothing.\n";
    
    std::cout << "\nСтворення юніка uptr_3 який вміщає клас Test для виконання\n"
              << "його внутрішньої функції get_my_number() за допомогою\n"
              << "оператора ->:\n";
    Test* test = new Test(13);
    UniquePtr<Test> uptr_3(test);
    std::cout << "uptr_3->get_my_number(): " << uptr_3->get_my_number() << std::endl;
    
    return 0;
}