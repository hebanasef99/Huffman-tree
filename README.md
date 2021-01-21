# Huffman-tree
Implemtin huffman tree and use it for encoding and decoding
Description :

Huffman algorithm : It is a technique of compressing data to reduse it is size to not lose time while sending/recieving it .
Program :the program read the desired text file by the user , build the huffman tree ,by assigning unique code for each character according to their frequency(the least frequency have the longest string) ,it is compressed and written back to in file 'output.txt'in ASCII when decoding 'output.txt' is read and converted to binary then decoded.


Algorithms used and its complexity:
In this algorithm, a variable-length code is assigned to input different characters. The code length is related to how frequently characters are used. Most frequent characters have the smallest codes and longer codes for least frequent characters.
Complexity for assigning the code for each character according to their frequency is O(n log n)
Complexity for traversing :
Assume an encoded text string of length n and an alphabet of k symbols.

For every encoded symbol you have to traverse the tree in order to decode that symbol. The tree contains k nodes and, on average, it takes O(log k) node visits to decode a symbol. So the time complexity would be O(n log k).

Input: string to be encoded , map contain each character with it's frquency 
Begin
   define a node with character, frequency, left and right child of the node for Huffman tree.
 
   for all type of character ch do
         add ch and its frequency as a node of priority queue Q.
Then :
until the size of tree is only 1(root) which means tree is complete
do
remove the char with the least frequency(highest priority) from priority queue
remove the char with the second least frequency(highest priority) from priority queue
create node with the sum and its left and right are the least freq
Make root the top of the queue

Output: Root 

Compression steps :
1)Put data read from file in string
2)Create map to save frequency of every char
3)Get the standard code for each character (8 bits) to compare sizes
4)Build huffman tree
5)Pass empty map(huffman map) with char and its encoded code to function encode
6)The encode function traverse the tree and add zero to left child and 1 to right child to fill the huffman map
7)Convert the binary bits in ASCII and write it in the file

Decompression steps :
1)convert the ascii read from to file to binary
2)Remove extra zeros
3)Pass the binary string and root to decode function
4)Decode function :it loop the binary string until it is empty
5) if the element is zero it recursively decode the left child
6)if the element is one it recursively decode the left child
7)until leave node is reached and it add it's coressponding character to the string(which it return )
