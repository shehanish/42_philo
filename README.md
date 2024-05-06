# 42_philo

## About the Project

The Push Swap project is a challenging sorting algorithm problem designed as part of the 42 programming school's curriculum. The goal of the project is to sort a stack of numbers using a limited set of operations (push, swap, and rotate) on two stacks (A and B) while aiming to minimize the number of operations performed. This project sharpens your understanding of algorithm efficiency, data structure manipulation, and creative problem-solving.

For this project, I utilized the following methods and techniques:

    - Radix Sort: I implemented the radix sorting method to efficiently sort the stack. Radix sort is a non-comparison-based sorting algorithm that organizes numbers based on their individual digits.

    Linked Lists: The stacks in Push Swap were managed using linked lists, which allowed for dynamic data manipulation and efficient stack operations.

    Bitwise Operations: Bitwise operations were used to manipulate individual digits of the numbers efficiently during the sorting process. This enabled quick sorting and reordering based on specific digit positions.

Radix Sort Explanation

Radix sort processes numbers one digit at a time, starting with the least significant digit and progressing to the most significant. Here’s how the process works:

    Preparation: The algorithm begins with preparing the data for sorting. The focus is on the least significant digit initially, and the process moves to higher significant digits.

    Bucket Sorting: For each digit position, numbers are sorted into different buckets based on the value of the current digit. This is performed using bitwise operations for speed and efficiency.

    Reassemble Buckets: After sorting the numbers into buckets, the data is reassembled into a single list while maintaining the sorted order within each bucket.

    Repeat Process: The sorting process repeats for each digit position, gradually organizing the data based on each level of significance.

Implementation Details

In my implementation, I combined the following techniques:

    Dynamic Stack Management: I utilized linked lists to represent the stacks (A and B) as they offer dynamic resizing and efficient insertions and deletions.

    Bitwise Operations: I employed bitwise operations such as shifting and masking to efficiently sort numbers based on individual digits. These operations allowed for rapid identification and manipulation of digits at each stage of the sorting process.

    Optimized Stack Operations: Using a careful combination of stack operations (push, swap, rotate), I minimized the total number of operations to efficiently sort the stack.

Through this approach, I achieved an efficient solution for the Push Swap project, demonstrating how advanced data structures and algorithms can work together to solve complex sorting problems.

I hope you enjoy exploring the Push Swap project and find it a valuable exercise in sorting algorithm implementation, data manipulation, and advanced coding techniques.
