# The Robson Traversal #

Hey y'all, this is a pretty cool tree traversal algorithm I've got here.
I wrote this for my data-structures class mostly late at night,
so please feel free to hate my ugly, poorly commented/written code, but feel even ***freer*** to contribute!


## Running ##

Robson and Link Inversion functions take 3 visitor functions for pre/in/post order traversals.

Threaded traversals only supports in-order processing.

Please note that only preorder traversal is currently supported.

    $ make robson
    $ ./rob.x 1 2 5 4 7 1 3 8 10 1 11
    $ make threaded
    $ ./thread.x 1 2 5 4 7 1 3 8 10 1 11
    $ make inversion
    $ ./inv.x 1 2 5 4 7 1 3 8 10 1 11

All of these files should correctly compile with c89 support.

## TODO: ##

* Blog post on Traversals. Then replace the next section with a link to that.

## Why do I need a robson traversal? ##

A Robson traversal is a binary tree traversal in `O(n)` time, and ***`O(1)`*** (!!!!) space.

The basic depth-first search traversal algorithm is `O(n)` space, and the threaded and link-inversion methods both are also `O(n)` space complexity.

The robson traversal takes the best of the link-inversion and threaded methods to create an `O(1)` space algorithm.

## Helpful links ##

There is very little help on the internet for this algorithm, but I have uploaded
(a possibly old version of) my slides on the topic. It is available as RobsonTraversal.pdf on this repository.

Here is a link to my slides (which are possibly more updated if the link is not dead):

https://docs.google.com/presentation/d/1JjU2X-EBaaXrfmHUqCavvxs3IIunZzOb9u1hJTFe8zo/edit?usp=sharing

I have the original paper (algorithm written in ALGOL 68-R!!), but I probably cant share it publicly.
Ask me if you want a peek!

I am hoping to write a blog post on this, so motivate me to do that please!

## License ##

This code is licensed with the MIT License! Please check LICENSE.txt for more info!

## Special Thanks ##

Thank you Jason Filippou for telling me about this cool algorithm. UMCP students take his classes!
