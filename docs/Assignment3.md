Assignment 3 - Library Restructuring System
================================================================
---

In this assignment, we plan to build a sophisticated feature for a library management system that involves creating a 
graph of books based on borrowing patterns, clustering related books together, and optimizing the placement of books on 
library shelves. The goal is to enhance the library experience for patrons by providing a well-structured and 
user-friendly shelving arrangement. To accomplish this task, you will need to implement `MergeSort` and `RadixSort` 
algorithms (you will also use the `HashTable` and `UnorderedSet` modules which you completed in the previous assignment). 
Browsing `include` directory, you can find the initially necessary datastructures in `Utils.h`. 
As well, you can find the ADT designs of the two required classes in `MergeSort.h` and `RadixSort.h`. 
You need to implement the specified functions of each header file in a .cpp file with the exact same name (i.e. 
`MergeSort.cpp`, and `RadixSort.cpp`) inside `src/` directory. Please do not modify the header files as you will not 
be submitting those files at the end.

Step-by-step guide:
-------------------
* **Important note**: for each module, after the implementation make sure its provided test cases run flawlessly.
  * running the test cases will give you the grade that you will get for that module. 
  * You are **not allowed** to use any STL data structures in your final submission except for `vector` and `list`.
    * You must use your implemented `Stack` class whenever a stack is required. You will lose marks if you use `vector` or `list` in those cases.
  * You are allowed to use the `algorithm` library in the `.cpp` files you implement.

1. Copy your completed `Stack`,`HashTable` and `UnorderedSet` implementations from assignment 2 into `src` directory.
2. After the _Sorting_ lecture, get started on implementation of the sorting algorithms (`MergeSort` and `RadixSort`).
   Once done, test them using `tests/MergeSortTests.h` and `tests/RadixSortTests.h`.
3. After the _Graphs_ lecture, using the previously implemented modules, implement the `LibraryRestructuring` class 
   which can be used in the following scenario:

- Call the constructor of `LibraryRestructuring` to create the graph of books. Each pair of books gets a connecting edge 
  if they are borrowed with the same patron. Using this graph the library wants to restructure the shelves to put 
  relevant books together. Don't forget to properly initialize `allBooks` and `bookBorrowingTime` while constructing the
  `graph` (which will be stored as an adjacency list). `Date::diffDuration` might come in handy at this stage.
- Call `clusterAndSort` to perform the restructuring and return the clusters of the books. The method returns a 
  list (`std::vector`) containing the clusters each of which is a list (`std::vector<std::string>`) of book ISBNs.
  You may use the `dfs` method to find the disjoint clusters within the `graph` of books.
  There are two kinds of necessary sorting formats that the clusters must adhere to:
  - The list of clusters of type (`std::vector<std::vector<std::string>>`) must be sorted based on the average duration 
    of the borrowed time of the books in each cluster so that the frequently borrowed books are placed closer to the 
    library counter; i.e. the cluster with the books averaging 45 days of borrowed time must appear before a cluster 
    with average borrowing time of 2 days. You will need to implement and use `getAverageBorrowingTime` to find the 
    average borrowing time for each `cluster`.
  - Within each cluster (representing a library shelf), the books must be able to be sorted based on the `title`, the 
    `author` or the `yearPublished`.
- Use `tests/LibraryRestructuringTests.h` for testing your implementation.

## Submission and Grading:

As stated earlier, you are not supposed to change the content of the files inside `docs`, `include` and `tests` folders.
Therefore, zip out your `src` folder which is expected to contain `Stack.cpp`, `HashTable.cpp`, `UnorderedSet.cpp`, 
`MergeSort.cpp`, `RadixSort.cpp`, and `LibraryRestructuring.cpp` and submit it. Your submitted `src` files must be able 
to be compiled and run with the provided `CMakeLists.txt` file. If you compile and run the `main.cpp` file, you must be 
able to see the grade which will be submitted to https://learn.bcit.ca for this assignment, if you have done everything 
properly, you will see the following output:
```
>> MergeSort:				Total tests passed: 17 out of 17 (100%)
>> RadixSort:				Total tests passed: 26 out of 26 (100%)
>> Library Restructuring System: 	Total tests passed: 11 out of 11 (100%)
```

### Rubric:
As the feedback you will receive an output similar to the one posted above, with a difference; if your tests fail or the
submission crashes you will also receive the error message, so you can follow up on the error to improve your 
understanding of this assignment. Here is the breakdown of the grades for this assignment:

* MergeSort: 10 marks
* RadixSort: 15 marks
* Library Restructuring System: 25 marks
* Documentation inside the code for public functions: 5 marks
* Submission of extra files in addition to requested (`Stack.cpp`, `HashTable.cpp`, `UnorderedSet.cpp`, `MergeSort.cpp`, `RadixSort.cpp`, `LibraryRestructuring.cpp`) penalty: -4 marks

Your final grade for assignment 3 will therefore be calculated from 55 marks.

### Important Notes Regarding Your Submission:
* I will be compiling/testing your code on a Linux OS, so please do not put in any Windows-specific code in your submission.
  I want to emphasize on this point specially since some of you use VSCode in Windows, and it tends to have its own
  default settings which in the past has led to confusion and grade deductions.
  * Please **do make sure** your code
    compiles and runs without any specific dependency on Windows.
  * Please note, it does not matter if the code runs on your
    machine! it must run on my machine. I hope this reduces the need for me to recite this in a few future correspondences!
* Your submission has a maximum allowed time to run! if it does not finish running in 2 minutes, it is considered timed
  out and will receive an automatic grade of 0.
* Please make sure you submit the final source files and download and check your files after the final submission.
  I have had students who accidentally had forgotten to check the files, and it had turned out that they had submitted
  the original assignment files instead of the completed assignment. Please do check this, as once the grading is done
  and the assignment is graded 0, nothing can be done (if such a thing happened please do not email me, as I will give
  you the exact same answer as is written here).
* As mentioned earlier, I will throw away any files submitted in addition to the requested three `.cpp` files (and you
  will receive 4 marks penalty if anything extra is submitted), so please make sure you do not rely on changing the
  content of any file in `include` and `tests` directories as they will not be present in my side and your code will be
  broken and will receive a 0 for compilation errors.

Good luck and happy programming!