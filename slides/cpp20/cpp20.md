<!-- .slide: style="text-align: left;"> -->

title: C++20
<span style="font-size:.4em; margin-right:0">v0.1</span>

author: Kristoffel Pirard

url: https://github.com/xtofl/cpp11training/blob/add-function-signatures-workshop/slides/cpp20/cpp20.md

style: sioux.css


[single-page version](/?print-pdf&pdfSeparateFragments=false)

<div style="font-size:.4em">
This slide deck is intended for use with reveal.js;
</div>
<div style="font-size:.4em">
```
articles> make cpp20/cpp20.reveal
```
</div>

---

# C++ 20

---

## Concepts

* More expressive type requirements
* Better compiler messages

--

### Definition

```C++
template <class T>
concept bool EqualityComparable() {
    return requires(T a, T b) {
        {a == b} -> Boolean;
        // Boolean is the concept defining
        // a type usable in boolean context
        {a != b} -> Boolean;
    };
}
```


--

### Use

```C++
void f(const EqualityComparable&)
```

```C++
template<EqualityComparable T>
auto find(range<T> ts, T needle);

--

### Predefined

Chapter 17 - Concepts library

* Language related
  * `Same<T, U>`, `Assignable<A, B>`, ...
* Comparison
  * `StrictTotallyOrdered<T>`
* Callable
  * `Invocable<F, ...As>`, `Predicate<F, ...As>`

---

## Coroutines

Non-preemptive multitasking

Two functions 'being nice'.

* cf. Python, C#, Lua, ...
* can suspend execution to be resumed later
* stackless

--

### New Keywords

* `co_await` vs. `co_yield`
* `co_yield` `co_return`

--

### New (known) concepts

* Promise object

--

cf. [cppreference](https://en.cppreference.com/w/cpp/language/coroutines)

---

## Modules

* Faster builds
* Better interface/implementation split

[draft paper](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3347.pdf)

--

### But how?

* compiler-generated interface files (`lib.mpp`)
* `#import Lib;`

--

### Module definition

```C++
export Lib:
public:
    struct S { void f() {} };
    class C { void f() {} };
```

--

### Standard Modules

* `std.core`
* `std.threading`
* `std.memory`
* `std.filesystem`
* ...

---

## And much more

