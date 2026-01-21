#include <coroutine>
#include <print>

template <typename T> struct Promise {
  Promise() { std::println("Promise constructed"); }
  ~Promise() { std::println("Promise destructed"); }

  auto get_return_object() {
    std::println("get_return_object called");
    return std::coroutine_handle<Promise>::from_promise(*this);
  }

  auto initial_suspend() {
    std::println("initial_suspend called");
    // awaiter 是对于某一个挂起点的控制
    return std::suspend_never{};
  }
  auto final_suspend() noexcept {
    std::println("final_suspend called");
    return std::suspend_never{};
  }

  auto return_value(T val) { value = val; }

  T value;
};

struct Task {}