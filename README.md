# The Robson Traversal #

Hey y'all, this is a pretty cool tree traversal algorithm I've got here.
I wrote this for my data-structures class mostly late at night,
so please feel free to hate my ugly, poorly commented/written code, but feel even ***freer*** to contribute!

## Running ##

The Robson traversal supports pre-, in-, and pos- order traversals.

The link inversion traversal supports pre-, in-, and post-order.

Threaded traversals only support in-order processing.

    $ make all # instead of using all the other make commands
    $ make robson
    $ ./robson.x -rno 1 2 5 4 7 3 8 10 0 11
    $ make threaded
    $ ./threaded.x -rno 1 2 5 4 7 3 8 10 0 11
    $ make inversion
    $ ./link_inversion.x -rno 1 2 5 4 7 3 8 10 0 11
    $ make clean # when you are done.

## TODO: ##

* Blog post on Traversals. Then replace the next section with a link to that.
* Testing!
    * Need tests using specific trees, not just random, to make sure certain cases are checked.
* Warning when no options are given for runner-programs

## Why do I need the Robson traversal? ##

A Robson traversal is a binary tree traversal in `O(n)` time, and ***`O(1)`*** (!!!) space.

The basic depth-first search traversal algorithm is `O(n)` space, and the threaded and link-inversion methods both are also `O(n)` space complexity.

The Robson traversal takes the best of the link-inversion and threaded methods to create an `O(1)` space algorithm.

## Helpful links ##

There is very little information on the internet for this algorithm, so I hope that the core
algorithm in `robson.c` is annotated enough to give an idea of its core process.

I am currently writing a blog post about Robson and the other traversals in this repository,
so please stay tuned on https://drs.is for that!

I included the paper by JM Robson here (algorithm written in ALGOL 68-R!!).
It is relatively hard to get a copy of it, so I decided its worth it to include.

Here are some of the resources I found helpful when studying the Robson Traversal:

* **(PDF warning) [Temple University lecture slides](https://cis.temple.edu/~wolfgang/cis551/Week06.pdf)**

This was a really important link for me, after lots of studying their C++ algorithm and their example images,
I figured out how to do it with much less dumb OOP stuff.

* **Data Structures, Algorithms and Program Style Using C by James F. Korsh and Leonard J. Garrett, Chapter 13.6.3 Robson Traversal**
    * available
[online](http://mindfulintegrations.com/books/Technology/computer_science/algo/start.htm)
or on [amazon](https://www.amazon.com/Structures-Algorithms-Program-Style-Using/dp/087150099X)

This was also extremely helpful, but again did not give the whole picture. The example starts in the middle of a traversal, and the text is unhelpful without extremely careful scrutiny.

Both of these resources were helpful in the end, and I'm glad I was able to divine a somewhat understandable solution thanks to these.

## License ##

This code is licensed with the MIT License! Please check LICENSE.md for more info!

## Special Thanks ##

Thank you Jason Filippou for telling me about this cool algorithm. UMCP students take his classes!
