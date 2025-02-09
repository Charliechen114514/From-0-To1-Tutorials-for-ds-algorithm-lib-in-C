# Start from scratch and rub the data structure algorithm library based on C language

## 0: Before starting

### 0.0 What is data structure and algorithm

 Before we start our rubbing, we often need to understand what is algorithm and what is data structure.

 In general textbooks, or any learning websites such as Youtube, Bilibili, etc., you will be told the following definition seriously.

> :question: Algorithm: An algorithm is a series of clear steps or instructions to solve a specific problem. It describes the calculation process from input to output, ensuring that the result is obtained within a finite number of steps:question:.
>
> :question: Data structure: Data structure is a way to organize and store data for efficient access and modification. It involves the relationship between data elements and operations on them.

 Very good, I don’t know what you are talking about after reading it. The author has something to say:

> :exclamation: Algorithms explain how we follow the steps, use the given information, solve the given problems, and pursue the fastest and lowest cost output we expect
>
> :exclamation: Data structures constrain how we store our data? Is it fragmented? Is it stored with subscripts? Or is it stored in pairs? (The storage method of data in computers is not the focus of our tutorial. You just need to imagine how to arrange your tourists to sit in designated places in a huge restaurant instead of letting them run around everywhere)

### 0.1 How to measure our data structures and algorithms

 Well, we must admit that we need an indicator to evaluate the quality of a data structure algorithm system that excludes subjective factors. We say that whether an algorithm is good or not, whether a data structure is good or not, depends on whether it can efficiently solve the difficult problems in the demand field of our target. To solve this problem, we need to understand the advantages and disadvantages of each data structure and each algorithm, their implementation, their potential problems and the difficulties they can solve. Of course, this tests my ability, and it is also an important reason why I advocate learning data structures and algorithms by hand, rather than by consuming them in a hurry!

 So, back to our question, how to measure our data structures and algorithms? Let's imagine carefully that for a small amount of data, the execution time of a super-powerful algorithm that I carefully optimized and an algorithm that is so crazy and violent that outsiders feel stupid, and the consumed hardware resources (such as our computer memory, hard storage, etc.) seem to be not very different, and a computer can still run.

 However, when the amount of data is large, the former's careful low-overhead design can ensure that the correct results are still run with almost no time change and almost no special expansion of hardware resources; in sharp contrast, the latter makes you irritable to find that the program is stuck and the computer is on strike, and you have to awkwardly turn off your computer, reopen your VSCode or any editor you like, and then struggle to think about where your algorithm went wrong. In this way, we need a clear scenario to evaluate the pros and cons of an algorithm - at least one! That is the size of our data.

> :heavy_check_mark: ：A good algorithm is **one that is **insensitive** to the size of the input data for a given problem and scenario**. Given a large amount of data, its execution time and processing resources are low-growth, and it can handle scenarios with almost any data size
>
> :negative_squared_cross_mark: ：Of course, a poor algorithm is the opposite. We almost only dare to beg our superiors, our colleagues, and our co-workers not to put the code we wrote into a production environment with large amounts of data, because it is obvious that such an algorithm cannot solve the given problem at all - generally, the excessive amount of data leads to the rigid processing and the program running time is almost unacceptable!

Therefore, we introduced the concept of algorithmic complexity, which measures the time and hardware (usually space) resource size of an algorithm when it is dealing with a data size of N (it can be several, dozens, tens, hundreds of thousands, tens of millions, or hundreds of millions of data). In other words, how much time and space does our algorithm take to process and execute data of a certain size? Generally, we use something called Big O counting to measure the complexity of our algorithm, which is an approximate, not an accurate description.

For example, we will call an algorithm with an O(N) complexity an algorithm with linear growth in complexity, because the time and resources it consumes are approximately positively correlated with the size of the data. For example, a classic traversal search algorithm.

```c
int find_target_linear(const int value, const int* array, const int array_size)
{
	for(int i = 0; i < array_size; i++)
    {
        if(value == array[i])
            return i;	// we find the value, so returns the index for the outlier usage
    }
    return -1;	// we find nothing, how saddy!
}
```

​	For ten pieces of data, we will have to search for ten times at worst. For one hundred pieces of data, we will have to search for a hundred times at worst. . . What about more? Well, there is nothing we can do about it. Of course, search is a very, very big topic in this tutorial, so don't worry. When you think that the search of linear traversal is really dull, the search algorithm we will introduce later will always surprise you.

 	Common algorithm complexity is as follows:

| Complexity | Name                             | Description                                                  | Example Algorithm                                     |
| ---------- | -------------------------------- | ------------------------------------------------------------ | ----------------------------------------------------- |
| O(1)       | Constant Time Complexity         | The execution time of the algorithm does not change with the input size and is always constant. | Array index access, hash table search                 |
| O(log n)   | Logarithmic Time Complexity      | The execution time of the algorithm grows logarithmically with the input size, and is highly efficient. | Binary search, balanced binary search tree operation  |
| O(n)       | Linear Time Complexity           | The execution time of the algorithm is proportional to the input size. | Linear search, traversal array                        |
| O(n log n) | Linear Logarithmic Complexity    | The execution time of the algorithm grows linearly with the input size, which is common in efficient sorting algorithms. | Quick sort, merge sort, heap sort                     |
| O(n²)      | Quadratic Time Complexity        | The execution time of the algorithm is proportional to the square of the input size, and is less efficient. | Bubble sort, selection sort, insertion sort           |
| O(n³)      | Cubic time complexity            | The execution time of the algorithm is proportional to the cube of the input size, which is less efficient. | Simple matrix multiplication                          |
| O(2ⁿ)      | Exponential time complexity      | The execution time of the algorithm grows exponentially with the input size, which is usually unacceptable. | Exhaustive search, some recursive problems            |
| O(n!)      | Factorial time complexity        | The execution time of the algorithm grows with the factorial of the input size, which is extremely inefficient. | Exhaustive solution to the traveling salesman problem |
| O(n^k)     | Polynomial complexity            | The execution time of the algorithm is proportional to a power of the input size, k is a constant. | Some dynamic programming problems                     |
| O(m + n)   | Linear addition complexity       | The execution time of the algorithm is proportional to the sum of the two input sizes. | Breadth-first search (BFS) of a graph                 |
| O(m * n)   | Linear multiplication complexity | The execution time of the algorithm is proportional to the product of the two input sizes. | Nested loops traverse a two-dimensional array         |

​	There are many new terms, don't worry, we will discuss them slowly, please don't worry! What we need to do is to try to get our algorithm close to O(1), or in other words, close to a theoretical limit! So, this hand-rubbing must be a difficult process!