#include "type_traits.h"
#include <iostream>
#include <ostream>
#include <type_traits>

int main() {
  std::cout << "test 1" << std::endl;
  std::cout << "rt int: " << rt_type_name_v<int> << std::endl;
  std::cout << "ct int: " << ct_type_name_v<int> << std::endl;

  std::cout << "test 2" << std::endl;
  std::cout << "ct const int&&: " << ct_type_name_v<const int &&> << std::endl;
  std::cout
      << ct_type_name_v<std::add_lvalue_reference_t<const int &&>> << std::endl;

  std::cout << ct_type_name_v<std::add_pointer_t<int &&>> << std::endl;

  std::cout << ct_type_name_v<std::add_rvalue_reference_t<int &>> << std::endl;
}