# Hierarchical Text Classification System

This project implements a **Hierarchical Text Classification System** that integrates a Trie-based data structure with a **Large Language Model (LLM)** for advanced text processing and classification. The system leverages the LLM to enhance classification accuracy, handle complex inputs, and intelligently interact with hierarchical data.

---

## Features

- **Hierarchical Data Management**: Insert, classify, and erase hierarchical text paths using a Trie.
- **LLM-Assisted Classification**: Utilize the power of a Large Language Model to process and refine classification results.
- **Command-Based Interaction**: Intuitive commands for users to interact with the system.
- **Dynamic Memory Management**: Efficiently allocate and deallocate memory during operations.
- **Batch File Processing**: Load and manage classifications from external files.

---

## How It Works

### Core Functionality

1. **Trie Data Structure**:
   - The Trie stores hierarchical labels where each node can have up to 15 children.
   - Each node is marked as "terminal" to signify valid end-points for classifications.

2. **LLM Integration**:
   - The LLM analyzes input classifications, enabling:
     - **Intelligent Path Suggestions**: When users provide partial or ambiguous inputs, the LLM predicts the most likely continuation.
     - **Validation**: Ensures user-provided paths align with existing hierarchies.
     - **Context-Aware Classification**: Interprets and classifies input labels based on context and hierarchical relationships.
   - For example:
     - Input: `classify,subcategory`
     - The LLM predicts the most appropriate path: `root,category,subcategory`.

3. **Command-Based Operations**:
   - **Insert**: Add classifications with LLM-assisted validation.
   - **Classify**: Use the LLM to match inputs to the most relevant hierarchical paths.
   - **Erase**: Remove classifications while preserving hierarchy integrity.
   - **Print**: Visualize the entire Trie structure.

4. **Memory and Error Handling**:
   - Efficient recursive methods for node traversal and memory cleanup.
   - Validation of inputs to prevent invalid operations.

---

## LLM Integration

The integration of the LLM adds intelligence to the classification system by:

1. **Enhanced Path Validation**:
   - The LLM predicts and validates paths based on hierarchical relationships.
   - Example:
     - Input: `root,cat`
     - LLM Suggestion: `root,category`.

2. **Context-Aware Classification**:
   - The LLM interprets user inputs, even when incomplete or ambiguous.
   - It dynamically suggests the best-matching paths within the Trie.

3. **Intelligent Error Handling**:
   - Provides descriptive feedback for invalid inputs.
   - Example:
     - Input: `clasify` (typo)
     - LLM Response: "Did you mean `classify`?"

4. **Interactive Decision-Making**:
   - Supports users with real-time suggestions for incomplete commands or labels.

---

## Advanced Features

- **Recursive Traversals**:
  - The system uses recursive algorithms for traversing and manipulating the Trie.
  - Combines the predictive capabilities of the LLM for decision-making.

- **Dynamic Node Management**:
  - Dynamically creates and deletes Trie nodes based on user operations.

- **Efficient Path Validation**:
  - Ensures hierarchical consistency using LLM insights.

- **Batch Loading**:
  - Load hierarchical data from text files for scalability.

---

## Technical Skills Demonstrated

1. **LLM Integration**:
   - Leveraged the predictive and contextual capabilities of the LLM for advanced classification tasks.

2. **Data Structures**:
   - Designed and implemented a Trie for hierarchical data storage.
   - Recursive methods for efficient traversal and node management.

3. **Memory Management**:
   - Dynamic allocation and deallocation of nodes.
   - Robust destructors to prevent memory leaks.

4. **File Handling**:
   - Line-by-line processing of hierarchical data from files.

5. **Command-Based Interaction**:
   - Developed a flexible system for interpreting and executing user commands.

---

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC)
- Basic understanding of C++ and Trie data structures.

### Compilation
```bash
g++ -std=c++17 -o hierarchical_text_classification p3.cpp
