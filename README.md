# Simple Concordance Tool

A lightweight command-line tool for text analysis created with C++, providing basic corpus linguistics functionality.

## Features

- **Keyword in Context (KWIC)**: Find specific words and see their surrounding context
- **Word Frequency Analysis**: Generate sorted lists of word frequencies
- **N-gram Analysis**: Identify common word sequences in text

## Building the Project

### Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++14 support

### Build Instructions

1. Clone the repository
2. Create a build directory:

mkdir build cd build

### Generate the build files:
cmake ..

### Build the project:
cmake --build .

## Usage
After building the project, you can run the executable:
.\\build\\Debug\\concordance_tool.exe

### Available Commands
The tool provides an interactive command-line interface with the following commands:

- `load <filename>` - load a text file for analysis 
- Example: `load sample.txt`
- Note: Provide the full path if the file is not in the current directory

- `kwic <word> <context>` - Find keyword in context
- `<word>`: The word to search for 
- `<context>`: Number of words to show before and after (default: 5)
- Example: `kwic mountain 3`

- `freq [n]` - Show word frequencies
- `[n]` : Optional parameter to limit output to top n words
- Example: `freq 10` (shows 10 most frequent words)
- Example: `freq` (shows all words)

- `ngram <n>` - Generate n-grams (sequences of n words)
  - `<n>`: Length of word sequences to analyze
  - Example: `ngram 2` (finds all 2-word sequences)

- `help` - Display available commands

- `exit` - Exit the program

### Example Session

load sample.txt
File loaded successfully.

kwic mountain 3
... cottage high in the [mountain] in a tiny ...
... all the way up [mountain] from the village ...
... the way he belonged [mountain] made him peaceful ...
... every treasure the [mountain] and her life ...

freq 5
WORD                FREQUENCY

the                 87
and                 42
to                  38
a                   36
she                 35

ngram 2
2-GRAM                         FREQUENCY

of the                         12
in the                         9
on the                         7
to the                         6
she had                        5


## Project Structure

- `main.cpp` - Main program logic and command handling
- `concordance.h` - Header file defining the ConcordanceAnalyzer class
- `concordance.cpp` - Implementation of text analysis functionality
- `CMakeLists.txt` - CMake build configuration

## Implementation Details

The concordance tool implements several text analysis algorithms:

1. **Tokenization**: Breaks text into individual words, handling punctuation and case normalization
2. **Frequency Analysis**: Counts occurrences of each word and sorts by frequency
3. **Context Extraction**: Identifies instances of keywords and extracts surrounding words
4. **N-gram Generation**: Creates and counts sequences of adjacent words

## Limitations

- Currently handles only plain text files
- Character encoding is limited to ASCII and basic UTF-8
- Large files may impact performance

## Future Improvements

Potential enhancements for future versions:

- Support for multiple file analysis
- Advanced search with regular expressions
- Collocation analysis
- Visualization of word distributions
- Export results to CSV or other formats

## License

This project is open source and available under the MIT License.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.