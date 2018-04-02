# The Robson Traversal #

Hey y'all, this is a pretty cool tree traversal algorithm I've got here.
I wrote this for my data-structures class mostly late at night,
so please feel free to hate my ugly, poorly commented/written code, but feel even ***freer*** to contribute!


## Running ##

Robson and Link Inversion functions take 3 visitor functions for pre/in/post order traversals.

Threaded traversals only supports in-order processing.

Please note that only preorder traversal is currently supported.

    $ make all # instead of using all the other make commands
    $ make robson
    $ ./robson.x 1 2 5 4 7 3 8 10 0 11
    $ make threaded
    $ ./threaded.x 1 2 5 4 7 3 8 10 0 11
    $ make inversion
    $ ./link_inversion.x 1 2 5 4 7 3 8 10 0 11
    $ make clean # when you are done.

All of these files should correctly compile with c89 support.

## TODO: ##

* Blog post on Traversals. Then replace the next section with a link to that.

## Why do I need a robson traversal? ##

A Robson traversal is a binary tree traversal in `O(n)` time, and ***`O(1)`*** (!!!!) space.

The basic depth-first search traversal algorithm is `O(n)` space, and the threaded and link-inversion methods both are also `O(n)` space complexity.

The robson traversal takes the best of the link-inversion and threaded methods to create an `O(1)` space algorithm.

## Helpful links ##

There is very little information on the internet for this algorithm, so I hope that the core
algorithm in `robson.c` is annotated enough to give an idea of its core process.

I am currently writing a blog post about Robson and the other traversals in this repository,
so please stay tuned on https://drs.is for that!

I have the original paper by JM Robson (algorithm written in ALGOL 68-R!!),
but I probably cant share it publicly. Ask me if you want a copy!

## License ##

This code is licensed with the MIT License! Please check LICENSE.md for more info!

## Special Thanks ##

Thank you Jason Filippou for telling me about this cool algorithm. UMCP students take his classes!
