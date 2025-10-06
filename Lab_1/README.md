# Assignment: Set Operations using Bit Manipulation

Roll No: 25MCMI15

---

## Files included

1. union.c
2. intersect.c
3. difference.c
4. subset.c
5. membership.c
6. mylib.c
7. mylib.h
8. Makefile
9. README

---

## Compilation

Use the provided Makefile.

1. To build all executables:
   make

2. To build only a specific executable:
   make union
   make intersect
   make difference
   make subset
   make membership

---

## Execution

1. **Union**:
   ./union set1.txt set2.txt
   → Output will be in output.txt and prints the size of the union set to console

2. **Intersection**:
   ./intersect set1.txt set2.txt
   → Output will be in output.txt and prints the size of the intersection set to console

3. **Difference**:
   ./difference set1.txt set2.txt
   → Output will be in output.txt and prints the size of the difference set to console

4. **Subset Check**:
   ./subset set1.txt set2.txt
   → Output will be TRUE or FALSE in output.txt and prints 1 or 0 to console

5. **Membership Check**:
   ./membership set1.txt element
   → Prints whether element belongs to set1

---

## Notes

- Input sets must be given as text files (set1.txt, set2.txt) with integers separated by newlines.
- Output is written to output.txt (for set operations).
- Error handling is included for invalid files and invalid inputs.

---

## Acknowledgement

I completed this assignment independently.  
I did not take help from anyone except classroom discussions, teacher instructions, and TA clarifications.
