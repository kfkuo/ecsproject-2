# Project 2 README

Student 1: Katelyn Kuo (923189082)

Student 2: Emilia Moore (922041095)

## Project Status
This project has implemented and documented the C++ classes, generating and parsing DSV and XML files. These classes are tested through GoogleTest tests, and are compiled and ran through our Makefile. The Makefile has been updated from Project 1, to be tailored to the requirements of this project. 

## Known Issues
There were issues in pushing our changes to the code, when working with GitHub, as there would be an error:

```cpp
fatal: refusing to merge unrelated histories
```

## Code References
* [How to use a stack in C++](https://www.geeksforgeeks.org/cpp/stack-in-cpp-stl/)
* [What is a DSV Parser](https://www.logviewplus.com/docs/dsv_parser.html)

## Generative AI Use
I used ChatGPT to figure out how to iterate over all characters in a string in C++17 (Prompt 1), and what a successful DSVWriterTest and DSVReaderTest should look like and test (Prompts 2 & 3).

### Prompt 1
How do I iterate over all characters in a string in C++17?

### Response 1
In C++17, you can iterate over all characters in a string using a range-based for loop. Here's an example:
```cpp
#include <iostream>
#include <string>

int main() {
    std::string myString = "Hello, World!";

    // Using range-based for loop to iterate over characters in the string
    for (char c : myString) {
        std::cout << c << " ";
    }

    return 0;
}
```
In this example, the `for (char c : myString)` loop iterates over each character in the string `myString`, and the variable `c` takes on the value of each character in turn. The loop body prints each character followed by a space.

This is a concise and readable way to iterate over the characters in a string in C++17.

### Changes 1
I only needed the `for` loop part, and my string was named `bar` so I changed it to just:
```cpp
// AI Generated
for (char c : bar) {
```

### Prompt 2
What are good areas to test for a DSVWriterTest?

### Response 2
The DSVTest.cpp file validates correctness, robustness, and edge-case handling for both the DSV reader and writer. Tests include:
* Basic functionality: reading and writing single and multiple rows with the correct delimiter
* Empty and minimal cases: empty input, empty rows, consecutive delimiters, and end-of-file behavior
* Quoted values: fields containing delimiters, escaped quotes, and quote handling consistency
* Multiple rows to ensure data is processed line by line

Example Test Categories
```cpp
TEST(DSVWriterTest, EmptyRowTest)
TEST(DSVWriterTest, SingleRowTest)
TEST(DSVWriterTest, MultipleRowsTest)
TEST(DSVWriterTest, LeadingTrailingSpace)
```

### Changes 2
I didn't have anything written for the DSVTest.cpp file so this information gave me more clarity in what kind of tests should be created, and what each test is for. As a result, I used the areas that were recommended, in order to write these testcases with the same names. 

### Prompt 3
What are good areas to test for a DSVReaderTest?

### Response 3
For DSVReader, you want to show that it can correctly read data, handle edge cases, and stop at the right time
* Empty input: Input string is empty, ReadRow should return false, No data should be added to the row vector
* Single row: One line of data with the delimiter, values split correctly into a vector
* Multiple rows: Input contains more than one line, Each call to ReadRow reads exactly one row, Stops reading at end-of-file
* Different delimiters: Use something other than a comma (like | or \t), Confirms delimiter is not hard-coded
* Leading and trailing spaces: Values with spaces before or after characters: Reader should behave consistently (either preserve or trim)

Example Test Categories
```cpp
TEST(DSVReaderTest, EmptyInputTest)
TEST(DSVReaderTest, SingleRowTest)
TEST(DSVReaderTest, MultipleRowsTest)
TEST(DSVReaderTest, DifferentDelimiterTest)
```

### Changes 3
Using this information, I was given more clarity as to how I should write my test cases for DSVReaderTest. With these definitions, it also made it easier for me to understnad what each test case expected and how to write it, also based off of Prompt 2. I didn't have anythign originally so there's nothing that changed, except me writing these tests in.
