graph_proto
===========

Simple graph manipulation class written in c++(11). It is just a kind of prototype, but it work.


It uses a adjacency matrix inside so it's really not made for a large number of node.
It has 2 type of iterator, one for iterating through the nodes and another to iterate through the edges of a node.

There's a ton of amelioration that can be made and some are noted in the comments. There's some:
  - Error handling could be better. (It always can...).
  - Make an interface (abstract class) of Graph and multiple implementation.
  - Make an implementation with *sparse matrix*, another one with *set of pair*.
  - Add properties (i.e. name, weight, etc.) to the link between the nodes.
  - Make it more "STL complient".
    + Make the iterators like the STL ones (i.e. they lack some typedefs)
    + Add some template parameters for the memory allocation for example.
      * Should look at the *Loki* library to have some examples of template parameters (hehe..)

License
========
Later...
