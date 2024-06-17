#include "includes/storageTemplates.hpp"

int main()
{
    double d{1.2};

    storageTemplates::Storage s1{d};
    s1.print();

    storageTemplates::Storage s2{&d};
    s2.print();

    return 0;
}