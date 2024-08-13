  # ✨ CustomLinkedList
  Darkuz_69 here!! This is my take on linked list, the first of my custom libraries project.
  This is in preparation for my DSA subject.

  #  🤖 Methods
  This linked-list implementation is written in C++. I used "classes" for this one
~~~c++
LinkedList<int> myList;
~~~
I will be using the inputs "[0, 1, 2]" for this explanation. Here are the methods:
  - 🫸 offer(data) -> pushes/inserts a node at the start of the list
~~~c++
  myList.offer(0); // [] -> [0]
~~~
  - 🫸 push(data) -> pushes/inserts a node at the end of the list
~~~c++
  myList.push(2); // [0] -> [0, 2]
~~~
  - 🫸 insert(index, data) -> pushes/inserts a node at the nth position
~~~c++
  myList.insert(1, 1); // [0, 2] -> [0, 1, 2]
~~~
  - 🗑️ poll() -> removes the node at the start of the list
~~~c++
  myList.poll(); // [0, 1, 2] -> [1, 2]
~~~
  - 🗑️ pop() -> removes the node at the end of the list
~~~c++
  myList.pop(); // [0, 1, 2] -> [0, 1]
~~~
  - 🗑️ remove(data) -> removes the node with the same data
~~~c++
  myList.remove(1); // [0, 1, 2] -> [0, 2]
~~~
  - 👀 peekFirst() -> returns a read-only version of the data of the head node
~~~c++
  myList.peekFirst(); // -> 0
~~~
  - 👀 peekLast() -> returns a read-only version of the data of the last node
~~~c++
  myList.peekLast(); // -> 2
~~~
  - 👀 peekAt(index) -> returns a read-only version of the data of the nth node 
~~~c++
  myList.peekAt(1); // -> 1
~~~
  - 🖨️ toString() -> returns a string of contents of the list in forward manner
~~~c++
  myList.toString(); // -> [0, 1, 2]
~~~
  - 🖨️ toStringReversed() -> returns a string of contents of the list in reversed manner
~~~c++
  myList.toString(); // -> [2, 1, 0];
~~~
  - 🚚 getSize() -> returns the current size of the list (read-only)
~~~c++
  myList.getSize(); // -> 3
~~~
  - 📪 isEmpty() -> returns true if the list is empty
~~~c++
  myList.isEmpty(); // -> false;
~~~
  - 👉 indexOf(data) -> returns the index of the data given
~~~c++
  myList.indexOf(2); // -> 2
~~~

  📢 Disclaimer
  - 🔔 This implementation uses 0-based indexing
  - 🔔 The "toString()" and "toStringReversed()" currently supports only the following types: bool, char, double, int, std::string. 


There are also exception classes for error handling:
 - ⚠️ LinkedListisEmptyException
 - ⚠️ LinkedListIndexOutofRangeException
 - ⚠️ LinkedListMemoryAllocationException
 - ⚠️ LinkedListMaximumLimitException

# 📜 Log.txt
These file contains the "behind-the-scenes" process as I create this project. Some phrases are written in my native language, so apologies in advance (if someone finds this repo)
