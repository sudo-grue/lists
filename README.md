## Follow steps to run:
1. make -B          // This builds your library and places it in /StudentLibrary
2. make -B solution // This shows the solution library being loaded
3. make -B test     // Tests your code

## While testing remember to valgrind your output.
valgrind --leak-check=full ./Tests/testAll

# Note: This is a work in progress. 