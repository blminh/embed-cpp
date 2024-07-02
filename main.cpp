#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
  std::cout << "Parse json file!" << std::endl;

  std::ifstream ifs("config.json");
  json jf = json::parse(ifs);
  std::cout << jf["key"] << std::endl;

  return 0;
}

// // #include "includes/Fraction.hpp"
// // #include "src/bench.cpp"
// #include "src/example.cpp"

// int main()
// {
//   runExample();

//   // >>> Fraction:
//   // std::cout << "Enter the numerator: ";
//   // int numerator{};
//   // std::cin >> numerator;
//   // std::cout << "Enter the denominator: ";
//   // int denominator{};
//   // std::cin >> denominator;

//   // try
//   // {
//   //   Fraction f{numerator, denominator};
//   //   std::cout << "Your fraction is: " << f << '\n';
//   // }
//   // catch (const std::exception &e)
//   // {
//   //   std::cerr << e.what() << '\n';
//   // }

//   // bench_test();

//   return 0;
// }