#include <thread>

template<typename T> struct Diced {
    T thing;
};
template<typename T> struct Grated{
    T thing;
};
template<typename T> struct Cooked{
    T thing;
};

using gramms = int;

template<typename T>
struct Ingredient {
    T thing;
    gramms amount;
};

template<typename T> auto diced(T t, gramms amount) {
    std::this_thread::sleep_for(std::chrono::milliseconds(amount * 2));
    return Ingredient<Diced<T>>{{t}, amount};
}

template<typename T> auto cooked(T t, gramms amount) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + amount));
    return Ingredient<Cooked<T>>{{t}, amount};
}

template<typename T> auto grated(T t, gramms amount) {
    std::this_thread::sleep_for(std::chrono::milliseconds(amount));
    return Ingredient<Grated<T>>{{t}, amount};
}

struct Carrot{};
struct Paprika{};
struct Pasta{};
struct Emmental{};
struct Meat{};

