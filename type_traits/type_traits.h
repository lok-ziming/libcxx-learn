#include <cxxabi.h> // GCC/Clang 需要这个来 demangle
#include <string>
#include <string_view>

// 类型名称解构函数（GCC/Clang）
// 还是运行时的，应该会有编译器宏可以做到编译期拿到type的string
template <typename T> std::string rt_type_name() {
  int status;
  char *demangled =
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status);
  std::string result = (status == 0) ? demangled : typeid(T).name();
  free(demangled);
  return result;
}

template <typename T> std::string rt_type_name_v = rt_type_name<T>();

// 通过编译器宏和string_view实现编译期类型名称获取（GCC/Clang）
template <typename T> constexpr std::string_view ct_type_name() {
  constexpr std::string_view pretty_function = __PRETTY_FUNCTION__;
  constexpr std::size_t begin = pretty_function.find_first_of('=') + 1;
  constexpr std::size_t trimmed_begin =
      pretty_function.find_first_not_of(' ', begin);
  constexpr std::size_t end = pretty_function.find_last_of(']');
  constexpr std::size_t trimmed_end =
      pretty_function.find_last_not_of(' ', end);
  return pretty_function.substr(trimmed_begin, trimmed_end - trimmed_begin);
}

template <typename T>
constexpr std::string_view ct_type_name_v = ct_type_name<T>();