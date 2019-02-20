Variant-98 - A C++98 Compatible Variant Implementation
---

### Motivation ###
I find variant types incredibly useful and I wanted an implementation that 
supports older platforms that may be constrained in what toolsets can be used 
(e.g. stock RHEL5 32 bit). I was discouraged by the apparent high cost of using 
*Boost*'s variant type. Copying instances of its variant can cause heap 
allocation, for example.

The aim of this project is to provide a C++98 compatible, low (or zero) 
overhead implemenation of a *Variant* that is syntactically similar to 
the C++17 `std::variant` type.

In keeping with supporting older toolsets, I also aim for this library to be 
compatible wih early versions of *CMake* (i.e. 2.6 onwards).
