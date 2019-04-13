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
<div style="font-size:.4em">credit: Bartosz Milewski</div>

--

Hidden slide

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
* form: 'non-functional'
    * sync/async
    * side effects
    * error handling indications

---

## Context

* what is a function
* single entry/exit...
    * exceptions
    * coroutines

---

## Rationale

* why bother?
    * readability/learnability/usability
* what is the essence the function does
* goals
    * client view: make it
        * easy to use => client code clutter
        * easy to understand => client code correctness
        * easy to learn => reusability
    * maintainer view
        * make it easy to adapt => maintainability
* Abstraction levels
    * cognitive limitations (5 +- 2)
    * function length = indicator

---

## Our Tool Belt

* typing
* naming
* contextual, implicit, domain knowledge
    * e.g. `std::lerp`, `std::iota`
* documentation

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