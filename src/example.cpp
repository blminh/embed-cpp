#include <iostream>

class Base
{
protected:
    int m_value{1};

public:
    Base() {}
    Base(int value) : m_value{value}
    {
        if (value < 5)
            throw 1;
    }
    ~Base() {}

    virtual void print() { std::cout << "Base\n"; }
    virtual std::string_view getName() const { return "Base"; }
    virtual int getValue() const { return m_value; }
};

class Derived : public Base
{
public:
    Derived() {}
    Derived(int value)
    try : Base{value}
    {
    }
    catch (...)
    {
        std::cerr << "Exception caught \n";
        throw;
    }
    ~Derived() {}

    void print() override { std::cout << "Derived\n"; }
    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};
class Doomed
{
public:
    ~Doomed()
    {
        std::cout << "Doomed destructed\n";
    }
};

void thrower()
{
    std::cout << "Throwing exception\n";
    throw 1;
}

void pt()
{
    std::cout << "pt (potentially throwing) called\n";
    // This object will be destroyed during stack unwinding (if it occurs)
    Doomed doomed{};
    thrower();
    std::cout << "This never prints\n";
}

void nt() noexcept
{
    std::cout << "nt (noexcept) called\n";
    // This object will be destroyed during stack unwinding (if it occurs)
    Doomed doomed{};
    thrower();
    std::cout << "this never prints\n";
}

void tester(int c) noexcept
{
    std::cout << "tester (noexcept) case " << c << " called\n";
    try
    {
        (c == 1) ? pt() : nt();
    }
    catch (...)
    {
        std::cout << "tester caught exception\n";
    }
}
void runExample()
{
    std::cout << "+++++ Example file! +++++ \n";

    std::cout << std::unitbuf;   // flush buffer after each insertion
    std::cout << std::boolalpha; // print boolean as true/false
    tester(1);
    std::cout << "Test successful\n\n";
    tester(2);
    std::cout << "Test successful\n";

    // try
    // {
    //     Derived derived{-5};

    //     // These are both legal!
    //     Base &rBase{derived};
    //     Base *pBase{&derived};

    //     std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    //     std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    //     std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
    // }
    // catch (int)
    // {
    //     std::cout << "Oops\n";
    // }

    // try
    // {
    //     try
    //     {
    //         throw Derived{};
    //     }
    //     catch (Base &b)
    //     {
    //         std::cout << "Caught Base b, which is actually a ";
    //         b.print();
    //         std::cout << std::endl;
    //         throw b;
    //     }
    // }
    // catch (Base &b)
    // {
    //     std::cout << "Caught Base b, which is actually a ";
    //     b.print();
    //     std::cout << std::endl;
    // }
}