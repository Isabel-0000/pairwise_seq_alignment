# pairwise_seq_alignment
A project to compare efficiencies and memory usage for pairwise sequence alignment algorithms

The Needleman-Wunsch and Hirschberg algorithms are implemented in C for comparison of CPU time and memory usage.
These are longest common substring algorithms, which find the longest string common to two strings.
An application for this is pairwise sequence alignment of DNA, RNA, or amino acids in bioinformatics.
Needleman-Wunsch takes O(mn) time and O(mn) space, where m and n are the lengths of the strings being compared.
Hirschberg takes O(mn) time and O(min(m,n)) space.

To use, run the executables hirschberg and needleman-wunsch or compile algorithm classes with their runners. 
time was run to find CPU efficiency (user + sys) and valgrind was used to find memory usage.
