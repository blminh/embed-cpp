
#include "../includes/storage_templates.h"

void storage_templates::templates()
{
    double d{1.2};

    Storage s1{d};
    s1.print();

    Storage s2{&d};
    s2.print();
}