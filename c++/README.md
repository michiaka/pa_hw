## Assignment  
**Spreadsheet Processor**

## Overview  
This project aims to develop a class that simulates the backend of a spreadsheet processor. The spreadsheet provides an interface for cell operations such as setting values, computing values, and copying cells. It supports expressions to define cell values, detects circular dependencies between cells, and allows saving/loading the spreadsheet to/from a file.

## Goals  
- Set values to spreadsheet cells and compute their values.
- Dynamically compute cell values using expressions.
- Detect and handle circular dependencies between cells.
- Save the spreadsheet to a file and restore it later.

## Implementation Details  
This project includes the following main classes and functions:

### `CSpreadsheet`  
Represents the spreadsheet processor itself. Each instance corresponds to one sheet. Implements the following features:
- `setCell(CPos pos, std::string contents)`: Sets a value or expression in the specified cell.
- `getValue(CPos pos)`: Computes and retrieves the value of the specified cell.
- `copyRect(CPos dstCell, CPos srcCell, int w, int h)`: Copies a rectangular range of cells.
- `save(std::ostream &os)`: Saves the content of the spreadsheet.
- `load(std::istream &is)`: Loads the content of the spreadsheet.

### `CPos`  
Identifies a cell within the spreadsheet. Parses identifiers (e.g., A1, B2) into internal representation.

### `CExpressionBuilder`  
An abstract class that provides builder objects for parsing expression syntax.

### `CValue`  
Represents a cell value, which may be undefined, numeric, or a string.

### `parseExpression`  
Parses an expression and passes the result to a builder object. This function is implemented using a provided parser.

## Challenges  
This project involved several technical challenges:
- Managing dependencies between cells and detecting circular references.
- Parsing expressions and building an efficient AST (Abstract Syntax Tree) for evaluation.
- Handling absolute and relative references in the `copyRect` function.

## Technologies Used  
- C++  
- Git

## How to Run  
This program uses a test-based execution environment. The following operations are conducted via the `main` function:

- `setCell()`: Sets the value of a cell  
- `copyRect()`: Copies a range of cells to another range  
- `save()`: Saves the spreadsheet content  
- `load()`: Loads the spreadsheet content  
- `getValue()`: Retrieves and prints cell values after operations for testing

### Steps to Run:

1. **Compile the program in the cloned directory**:  
    ```bash
    g++ -pedantic -Wall -Wextra -g3 -fsanitize=address -std=c++20 -L ./ main.cpp -l:libexpression_parser.a -o main
    ```

2. **Run the program**:  
    ```bash
    ./main
    ```
