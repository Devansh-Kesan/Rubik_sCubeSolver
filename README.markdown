# Rubik's Cube Solver

This project is a C++ implementation of a Rubik's Cube solver that explores various data structures and AI search algorithms to find solutions to a scrambled cube. The primary goal is to implement Korf's algorithm, which uses the Iterative Deepening A* (IDA*) search algorithm with pattern databases to find optimal solutions.

## 🌟 Features

- **Multiple Cube Representations**: Implements three different ways to model the Rubik's Cube, each with its own trade-offs in terms of speed and memory.
- **Variety of Solving Algorithms**: Includes implementations for several graph traversal algorithms.
- **Heuristic Search with Pattern Databases**: Utilizes a pre-computed Corner Pattern Database to provide an admissible heuristic for the IDA* algorithm, dramatically speeding up the search for a solution.
- **Object-Oriented Design**: Heavily leverages OOP principles like inheritance, polymorphism, and operator overloading to create a modular and extensible codebase.
- **Generic Solvers via Templates**: Uses C++ templates to create generic solver classes that can operate on any of the implemented cube representations without code duplication.

## 🗺️ Cube Indexing and Planar Representation

To represent the 3D cube in code, we unfold it into a 2D "planar" structure. The faces are indexed consistently throughout the project, which is crucial for applying moves correctly.

**Face Indexing**:
- 0: Up (White)
- 1: Left (Green)
- 2: Front (Red)
- 3: Right (Blue)
- 4: Back (Orange)
- 5: Down (Yellow)

Each sticker on a face is also indexed, typically from 0 to 8. This unfolded view is fundamental to understanding how the 1D and 3D array representations work.

## 🎲 Cube Representations

The project models the Rubik's Cube using three distinct data structures. A generic `RubiksCube` abstract class defines a common interface, which each representation implements.

| Representation | Structure       | Memory | Performance | Best For                              |
|----------------|-----------------|--------|-------------|---------------------------------------|
| 3D Array       | T[6][3][3]      | High   | Slow        | Initial prototyping, easy visualization of logic. |
| 1D Array       | T[54]           | Medium | Moderate    | Simpler storage and serialization.    |
| Bitboard       | uint64_t[6]     | Low    | Very Fast   | High-performance solvers, complex algorithms. |

1. **3D Array Representation**: An intuitive model where the cube is a [side][row][column] array.
2. **1D Array Representation**: A flattened representation that stores the 54 sticker colors in a single-dimensional array.
3. **Bitboard Representation**: A highly compact and efficient representation using an array of six 64-bit integers, where each integer represents a face.

## 🤖 Solving Algorithms

The core of the project is solving the cube. This is treated as a graph traversal problem: the scrambled cube is the start state, the solved cube is the goal state, and each move is an edge to a new state.

| Algorithm | Optimal Solution? | Time Complexity | Space Complexity | Key Characteristic                              |
|-----------|-------------------|-----------------|------------------|------------------------------------------------|
| DFS       | No                | O(b^d)          | O(bd)            | Simple, low memory, but finds non-optimal paths. |
| BFS       | Yes               | O(b^d)          | O(b^d)           | Guarantees shortest path, but high memory usage. |
| IDDFS     | Yes               | O(b^d)          | O(bd)            | Combines DFS's space-efficiency with BFS's optimality. |
| IDA*      | Yes               | O(b^d)          | O(bd)            | Most efficient: Heuristic-guided search for optimal solutions. |

*Note*: `b` is the branching factor, `d` is the solution depth.

### IDA* (Iterative Deepening A*) Solver

This is the centerpiece of the project, designed to find optimal solutions efficiently. It uses a heuristic function `f(n) = g(n) + h(n)` to guide its search.

## 🧠 Heuristics and Pattern Databases

To make the IDA* search effective, a good heuristic is required. This project uses a **Corner Pattern Database** as its heuristic function. This is a pre-computed lookup table that stores the minimum number of moves required to solve the 8 corners of the cube, ignoring the edges.

## 🛠️ Technical Implementation

**Language**: C++

**Key Concepts Used**:

| C++ Concept          | Application in Project                                           |
|----------------------|-----------------------------------------------------------------|
| Abstract Classes     | `RubiksCube`, `PatternDatabase` to define a common interface.    |
| Inheritance          | Concrete representations (3DArray, Bitboard) inheriting from `RubiksCube`. |
| Templates            | Creating generic `Solver` classes that work with any cube representation. |
| Operator Overloading | `==`, `=` for using cube objects in STL containers and ensuring deep copies. |
| Bit Manipulation     | Core of the Bitboard representation and `NibbleArray` for pattern databases. |
| File I/O             | To generate, save, and load the large pattern database file.     |

## 🚀 How to Build and Run

### Prerequisites
- A C++ compiler that supports C++11 or newer (e.g., g++, Clang).
- `make` or an IDE like Visual Studio or CLion.
- Included utility files for permutation indexing: `math.h`, `math.cpp`, `PermutationIndexer.h`.

### Step 1: Generate the Pattern Database

Before you can run the IDA* solver, you must first generate the corner pattern database.

```bash
# Compile the database generator
g++ -std=c++11 -O3 DBMaker.cpp math.cpp -o DBMaker

# Run the generator (this may take some time)
./DBMaker
```

This will create a file (e.g., `corner_db.dat`) containing the pre-computed heuristics.

### Step 2: Compile and Run the Solver

Place your main solver code in a file (e.g., `main.cpp`). Compile the project:

```bash
g++ -std=c++11 -O3 main.cpp math.cpp -o solver
```

Run the solver:

```bash
./solver
```

The solver should then load the pattern database, shuffle a cube, and use the IDA* algorithm to find an optimal solution.

## 🎓 Key Learnings

- Modeling a real-world object like a Rubik's Cube using different data structures.
- Applying classic AI search algorithms (BFS, DFS, IDDFS, A*) to a complex problem.
- Understanding and implementing heuristic search using pre-computed pattern databases.
- Practical application of advanced C++ features, including OOP, templates, and operator overloading.
- The power of bit manipulation for creating high-performance, memory-efficient code.