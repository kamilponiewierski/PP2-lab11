#include <iostream>
#include "VectoredList.h"

int main()
{
    ////////////////////////////////////////////////////////////////////////////////

    auto v = VectoredList();
    for (int i = 0; i < 102; i++)
    {
        v.push_back(std::to_string(i));
    }

    std::cout << std::endl << "Test operatora []" << std::endl;


    // TESTY: Proszę tak dodać 101 elementów i przejść od odwrotnej strony po elementach. [1p za operator[] i push_back]
    for (int i = 101; i >= 0; --i)
    {
        std::cout << v[i] << std::endl;
    }

    std::cout << std::endl << "Test iteratora" << std::endl;

    ////////////////////////////////////////////////////////////////////////////////


    auto vIter = VectoredList();
    for (int i = 0; i < 42; i++)
    {
        vIter.push_back(std::to_string(i));
    }

    // TEST: VectoredList v(...);  // [1p]
    // for (auto& element : v)
    for (auto &element : v)
    { std::cout << element << std::endl; }


    ////////////////////////////////////////////////////////////////////////////////

    // TEST: VectoredList v(...);
    //{
    //   VectoredList v2(...);
    //   v = v2;
    //}
    // teraz wyświetlić v, oraz po zakończeniu programu nic nie powinno się wywalić // [1p]

    std::cout << std::endl << "Test operatora =" << std::endl;

    auto v2 = VectoredList();

    for (int i = 10; i < 150; i += 10)
    {
        v2.push_back(std::to_string(i));
    }

    v = v2;

    std::cout << v;
}
