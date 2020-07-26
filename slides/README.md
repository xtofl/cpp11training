# Resources

To solve the exercises you can work through numerous resources.  The ones enumerated here
can give you a good idea.

## basics

A brief guide through 'basic' c++ concepts.  Actually this is kindof required knowledge for starting the rest of the course.
[In pdf format](/slides/0.C++Basics.pdf) or on [google drive](https://docs.google.com/presentation/d/1gPbW8i_sN0PeqGqzjUAUlveDML-lbBXqXRyuz21b6Cc/edit?usp=sharing).

## coreextensions

[This presentation](/slides/1.coreextensions-c11-121213071023-phpapp02-reordered.pptx/) is a reordered form of [This One](http://www.slideshare.net/adankevich/c11-15621074)

    vector<Slide> slides("http://www.slideshare.net/adankevich/c11-15621074");
    auto rest = std::partition(begin(slides), end(slides),
        [](const auto &Slide) { slide.tags.contains("core-extensions"); });
    slides.erase(rest, end(slides));


## lambda-functions

[This presentation](/slides/2.lambdas-c11-121213071023-phpapp02-reordered.pptx/) is a reordered form of [This One](http://www.slideshare.net/adankevich/c11-15621074)

    vector<Slide> slides("http://www.slideshare.net/adankevich/c11-15621074");
    auto rest = std::partition(begin(slides), end(slides),
        [](const auto &Slide) { slide.tags.contains("lambda-functions"); });
    slides.erase(rest, end(slides));


## Smart Pointers:

[c11-smart-pointer](http://www.slideshare.net/mine260309/c11-smart-pointer-50203051)


## Move semantics

[Move-Semantics-Part-1](http://becpp.org/blog/wp-content/uploads/2015/01/Bert-Rodiers-Move-Semantics-Part-1.pptx)

(Move-addicts can read on about perfect forwarding and move-function idioms in [the follow-up](http://becpp.org/blog/wp-content/uploads/2015/01/Bert-Rodiers-Move-Semantics-Part-2.pptx))


## STL Algorithms

[STL Algorithms.pdf](/slides/5.b.STL Algorithms.pdf/)


## Multithreading

[c11-multithreading-futures](http://www.slideshare.net/GlobalLogicUkraine/c11-multithreading-futures)


## Variadic templates

[Alexandrescu's Going Native 2012 slides](/slides/docslide.us_gn12variadictemplatesarefunadic.pdf/)
If you've got a hour, [watch his talk on youtube](https://youtu.be/dD57tJjkumE)
