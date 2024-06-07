### reference.md

A quick reference for the purposes of early development.

## Matricies

# Matrix class

The entries are stored in object.entry_v (A vector<vector<matrix::matrix>>).
They can accessed indirectly via the method
object.entry(i)(j), or directly as object.entry_v.at(i).at(j).

# asdLDU class
Contains pointers to four matricies, P, L, D, and U. It is used to return the matricies from the ldu () function.
