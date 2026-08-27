# StringMetrics String Similarity Calculator

**WORK CURRENTLY IN PROGRESS**

## StringMetrics

StringMetrics is a simple C++ tool for calculating various metrics of string similarity. Wide characters support is implemented. 
This program works with string in Unicode encoding formats (UTF-8, UTF-16, UTF-32).

Metrics currently available:
1. Levenshtein distance
2. Damerau–Levenshtein distance
3. Lowest common subsequence
4. Hamming distance

## Requirements

This project uses Qt 6 and requires Core, Gui and Widgets modules. 
Additionally, unit tests are available (in the /test/ folder) that require Qt Test module.