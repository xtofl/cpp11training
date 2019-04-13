<!-- .slide: style="text-align: left;"> -->

title: Function Signature Design
<span style="font-size:.4em; margin-right:0">v0.1</span>

author: Kristoffel Pirard

url: https://github.com/xtofl/cpp11training/blob/add-function-signatures-workshop/slides/function_signature_design/function_signature_design.md
style: night.css

<div style="font-size:.4em">
[(single-page version)](?print-pdf&pdfSeparateFragments=false)
</div>

<div style="font-size:.4em">
This slide deck is intended for use with reveal.js;
</div>
<div style="font-size:.4em">
```
articles> make function_signature_design/function_signature_design.reveal
```
</div>

---

# Function Signature Design


![pig throwing flares at itself](milewski_monoid.jpg) <!-- .element: width="300" style="display: block; margin-left: auto; margin-right: auto;" -->
<div style="font-size:.4em">credit: Bartosz Milewski</div>reveal
reveal
--reveal
reveal
Hidden slidereveal
reveal
Slidedeck mainline


* CONTEXT
    * what is a function
    * single entry/exit...
        * exceptions
        * coroutines
* RATIONALE
    * why?  readability/learnability/usability
    * what is the essence the function does
    * goals of function signature
        * understand the code that uses it
        * limit documentation to the "why"
    * Abstraction levels
        * cognitive limitations (5 +- 2)
        * function length = indicator
* Our Tool Belt
    * typingontext vs. repetition
    * naming
    * contextual, implicit, domain knowledge
        * e.g. `std::lerp`, `std::iota`
    * documentation
* Types convey meaning
    * vocabulary types
    * argument type
    * argument qualifiers (sinks)
    * member function qualifiers
    * return type
    * return type qualifiers
    * Note: parameters = signature <-> arguments = call+implementation
* naming
    * explain what it does
        * to your colleague
        * to your dad
        * to your kid
    * verbs, nouns, adjectives
        * NEED INTERACTION HERE; an execise?
    * role vs. type
    * fish in the same pont
        * begin/end start/stop first/last
        * more examples?
    * context vs. repetition
    * C++: name lookup/overloading
        * asInt, asBool, asString... cast operator!
        * fromInt, fromBool, ... overloads
        * compatibility <-> onion arch. adapters
    * C++: conventional functions
        * construct/destruct
        * indexing
        * converting
        * calling (?)
    * Note: ~~foo~~ ~~bar~~
## Rationale

* why bother?
    * readability/learnability/usability
* form: 'non-functional'
    * sync/async
    * side effects
    * error handling indications

---

## Context

* Why do we have functions
* Structured Programming
    * => a tool for the user
    * 'Structure' = divide and conquer
        * -> how fine?  how coarse?
        * how even?
        <img src="http://www.rosslawinc.com/wp-content/uploads/2014/02/14B11-Stairs-1.jpg" style="width:200px"/>

--

### Notation

(TODO: find better name for 'our_function')

* No more ~~foo~~ and ~~bar~~
    * `ret_t our_function(arg_t)`
    * ```
    void client_code() {
        ...
        auto x = our_function(a);
        ...
    }```

--

### Notes

* single entry/exit...
    * exceptions
    * coroutines


---

## Rationale

* why bother?
    * readability/learnability/usability

--


### Goals of the Function Signature

* what is the essence the function does?

--

### Audience

* new code/maintenance
* reading/writing
* lib author/user
* finding/learning/using

-- 

### Audience

* client view: make it
    * easy to use => client code clutter
    * easy to understand => client code correctness
    * easy to learn => reusability
* maintainer view
    * make it easy to adapt => maintainability

--

### Goal

Make the essence of the function

* as clear as possible
* to all needed parties
* in all needed situations

---

## Our Tool Belt

* types: built-in, library, custom
* naming
* contextual, implicit, domain knowledge
    * e.g. `std::lerp`, `std::iota`
* documentation
    * out of scope: we want to limit this to the "why"

---

## Types Convey Meaning

* vocabulary types
* argument type
* argument qualifiers (sinks)
* member function qualifiers
* return type
* return type qualifiers
* Note: parameters = signature <-> arguments = call+implementation

---

## Naming is Hard

* explain what it does
    * to your colleague
    * to your dad
    * to your kid

--

## The word type

* Noun
* Verb
* Adjective

--

## Word type: Noun


* immutable
* pure
* object?

--

## Wordt Type: Verb

* action
* side-effect
* non-pure

--

## Wordt Type: Adjective

* property
* predicate
    * replace `isBig()` with `big()`
    * replace `hasX()` with `optional<X> x()` or `withX(callback)`

--

## Roles vs. Types

* `power_consumption(const Machine &machine)`
    * duplication!
* `get_first(const std::vector<X> &xs)`

--

## Consistent Dictionary Chapter

* fish in the same pont
    * begin/end start/stop first/last
    * more examples?
* even level of abstraction


--

## Context avoids Repetition

* `math::sin` vs. `confession::sin`
* `myMachine.startMachine()`???

--

## C++ has Overloads!

context is provided by the argument type

* Argument Dependent Lookup
* conversions _from_ `X`
    * `operator R() () const`
    * `auto r = static_cast<R>(x)`
* conversions _to_ `X`
    * `static X from(int i)`
    * `auto [xi, xs] = X::from(10), X::from("10")`

--

## C++ conventional functions

* indexing with `operator[]`
* calling with `operator()`
* comparing with `operator <=>()`
* ...

---

## The Non Functional Aspects

* sync/async
* side effects
* error handling indications

---

## Testing the Signature

--

###  Design Time

* Time to find a proper name
* Long time => wrong abstraction?
* Tools for validation
    * Rubber Duck
    * Polls

--

### Review Time

* One Shot opportunity for "learnability"
    * => Pay Attention!
* What questions are asked
    * Missing context?
    * Ambiguity?
    * "Too smart"?
* What is unclear
* "Taste" vs. reality

--

### Life Time

Bugs occuring from this signature?


---

## Conclusion

* Use the Tool Belt
* Naming is Hard
    * => Test it


---

examples

* plurals indicate containerss