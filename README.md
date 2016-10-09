# Accacia

## What is this?

A tiny project from 2006 :)

Accacia is a lib which puts together some console I/O functions. This library
is suitable for systems with Ansi Color Coding terminals.

As you can see by the acronym that the name of this lib is based:

``A``nsi ``c``olor ``c``oding ``a``nd ``c``onsole ``i``nput ``a``vailable.

When I did it I'd decided to follow the old Borland's "conio.h" style, because
the motivation to create Accacia was the lack of an easy way to get a colored
output in a console mode program on Linux.

I think libcurses impractical when dealing with simple things.

## How to build it?

In order to build Accacia you need to use [Hefesto](http://github.com/rafael-santiago/hefesto.git).

After follow the steps to install Hefesto in your system, all you need to do
(on shell) inside accacia src subdirectory is invoke hefesto. Something like this:

```
root@zephyr:~/src/accacia/src# hefesto
```

In order to build the samples... being inside the subdirectory "src/samples", just type "hefesto":

```
root@zephyr:~/src/accacia/src/samples# hefesto
```

It must work fine and you'll find your samples at "accacia/samples".

Enjoy!
