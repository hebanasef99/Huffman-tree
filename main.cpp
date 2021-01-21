#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <math.h>
#include <chrono>
using namespace std;
string str;


int arraysize=0;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};
string decode2(struct Node* root, string str)
{
    struct Node* r = root;
    string og = "";

    for (int i=0;i<str.size();i++)//loop the size of the strings of zero and 1
    {
    if (str[i] == '0')
       r = r->left;
     else
       r = r->right;

    if (r->left==NULL and r->right==NULL)//reached the correct char
        {og += r->ch;//add character to the string
        r = root;//r is root again
        }
    }
    og=og+'\0';
    return og;
}
// Function to allocate a new tree node
Node* newNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}


struct compare
{
    bool operator()(Node* l, Node* r)
    {

        return l->freq > r->freq;//returns 1 if freq of right item is more which means it has higher priority
    }
};



void encode(Node* root, string str, map<char, string> &decodedCode)
{
    if (root == nullptr) {
        return;
    }
   if(root->left == nullptr && root->right == nullptr) {//if tree consists of 1 node
        decodedCode[root->ch] = (str != "") ? str : "1";//str="1"
    }
    encode(root->left, str + "0", decodedCode);//encode the left and add 0
    encode(root->right, str + "1", decodedCode);//encode right and add 1
}




Node* huffmanTree(string data,map<char, int> &frequency)
{

    Node* emp=NULL;//if the string is empty
    if (data == "") {
        return emp ;
    }
    priority_queue<Node* ,vector<Node*> ,compare> pq;// priority queue to store live nodes of huffman tree
   for (auto x: frequency) {
        pq.push(newNode(x.first, x.second, nullptr, nullptr));//create node for char in frequency map and push into priority queue
        arraysize++;//number of nodes or characters in file
    }
   while (pq.size() != 1)//until the size of tree is only 1(root) which means tree is complete
    {
        Node *left = pq.top(); pq.pop();//remove the char with the least frequency(highest priority) from priority queue
        Node *right = pq.top();pq.pop();//remove the char with the second least frequency(highest priority) from priority queue
        //tree
        int sum = left->freq + right->freq;//add freq of these nodes
        pq.push(newNode('\0', sum, left, right));//create node with the sun and its left and right are the least freq
    }
    Node* root = pq.top();//root is the top of the queue


    return root;//returns the root(tree)
}

Node* huffmanTree2(map<char, string> &huffmanCode)
{

    priority_queue<Node* ,vector<Node*> ,compare> pq;// priority queue to store live nodes of huffman tree
    Node* node;Node* n;
    Node *root=newNode('|',1,nullptr,nullptr);
    printf("5555555555\n");
   // newNode(NULL,NULL,NULL,NULL);
   for (auto pair2: huffmanCode) {
        string s= pair2.second;
        node=root;
         //printf("mmmmmm %s\n",pair2.second);
         cout<<pair2.second;
        //Node* newNode(char ch, int freq, Node* left, Node* right)

       for(int i=0;i<s.length();i++)
       {
            if(s[i]='0')
            {
                if (node->left==NULL)
                {
                    node->left=newNode('|', 0, nullptr, nullptr);
                }


                    node=node->left;
            }

            else
               {
                if (node->right==NULL)
                {
                    node->right=newNode('|', 0, nullptr, nullptr);
                }


                    node=node->right;
                 }

       }
         node->ch=pair2.first;

   }

    return root;//returns the root(tree)
}
int getfreq(int a[],int b[],int sum1)
{
    int sum=0;float r;
   for(int i=0;i<arraysize;i++)
    sum+=a[i]*b[i];//muliply freq by no bits after it is decoded
   printf("Before %d\n",sum1);
   printf("After %d\n",sum);
   float sumf1=sum1;float sumf=sum;
   r=sumf1/sumf;
   printf("Ratio %f\n",r);//print ratio
   return sum;
}
char encoded_bytes [10];

char* tobytes(string str,string FILENAME2)
{


    string zero ="0" ;
    int new_L =0 ;
    string neweightBits;


    int j = 0 ;
    int decimal_num=0 ;
    int num_zeros=0 ;
    int l=str.length()%8;

    while (l!=0)//if length of string of bits<8 add zeros
    {
        str=str.append(zero);
        l=str.length()%8;
        num_zeros++;
    }
    // cout << "\n string after adding zeros is:\n" << str << '\n';
     new_L=str.length()/8;//value of array of bytes

      encoded_bytes[0]=num_zeros ;
       //ofstream file;
       std::ofstream file;
       file.open(FILENAME2, std::ios_base::app); // append instead of overwrite
       //file.open("output.txt");
       file<< encoded_bytes[0];



     int v=0 ;
    for (int k=0;k<new_L;k++)
     {
      neweightBits= str.substr(v, 8); //b-copy el 8 bits el 3ayza a7wlhom binary
      v+=8 ;
     decimal_num = std::stoi(neweightBits, 0, 2);//get decimal number
	 encoded_bytes[0]=decimal_num;
	 file<<encoded_bytes[0];//add byte to file

    }
     file.flush();
     file.close();

    return encoded_bytes ;

}
string tobinary(int m)//function that takes a decimal value and returns a its equivalent binary as a string
{
    int a[8];
    string s;


      for(int i=0; i<8; i++)
      {
       a[i]=m%2;
       m= m/2;
       if(i==7)
       {
           if(a[i]==1)
            s="1";
           else
            s="0";
       }
      }
      for(int m=6 ;m>=0 ;m--)
      {

        std::string tmp = std::to_string(a[m]);
        char const *num_char =tmp.c_str();
        s=s+num_char;


      }
      return s;
}
void print_tree_structure(Node *bt, int spaces)
{
  if(bt != NULL)
  {
    print_tree_structure(bt->right, spaces + 5);
    for(int i = 0; i < spaces; i++)
      	cout << ' ';
    	cout << "   " << bt->ch << endl;
    print_tree_structure(bt->left, spaces + 5);
  }
}
string removeDuplicate(string str)
{
  unsigned short int index = 0;
  std::string chars;
  const std::string::size_type size = str.size();

    for (char c : str)
    {
        if (chars.find(c) != std::string::npos)
        {
            str.erase(str.begin() + index);
            str.resize(size);
        }
        else
        {
            chars.push_back(c);
        }
        ++index;
    }

    str.shrink_to_fit();


      std::cout << chars << '\n';

 return chars ;
 }

void Standard_encode(string s)
{
int i;
int count=0 ; //hhnmmm
 for (char ch: s)
    {

        /* perform bitwise AND for every bit of the character */
        for(i = 7; i >= 0; --i)

            {
                (ch & 1 << i) ? putchar('1') : putchar('0');

            }


cout<< ch;
printf(" <= %c\n", ch);
putchar('\n');




    }
}
int main()
{
    string FILENAME,FILENAME2;
    int option=1;
    int count=0;

   int trial=0;
   while(option==1 ||option==2)
{
    printf("1)For compression press 1\n2)For Decompression press 2\n3)Press any other key to exit \n");
    scanf("%d",&option);
    if (option==1)
    {
        cout << "Enter the file name you want to encode: " << endl;
        cin >> FILENAME;
        cout << "Enter the output file name: " << endl;
        cin >> FILENAME2;


        trial++;
    }
    else if (option==2 && trial==0)
    {
        cout << "Enter the name of the original file: " << endl;
        cin >> FILENAME;
        cout << "Enter the output file name: " << endl;
        cin >> FILENAME2;

        trial++;
    }

   std::ifstream in(FILENAME);
   std::stringstream data;
   data << in.rdbuf();//put data read from file in string data
   std::string contents(data.str());


    using namespace std::chrono;
    auto start1 = high_resolution_clock::now();

    map<char, int> frequency;//map to save frequency of every char
    for (char ch: data.str()) {//when reading a char increase its frequency by one
        frequency[ch]++;

    }
    Node* root=huffmanTree(data.str(),frequency);

     map<char, string> huffmanCode;//empty map

    if(option==1){//encode
        string jh=" ";

        encode(root, "", huffmanCode);//returns the map with char and its encoded code


        int a[arraysize];//arraysize globel variable with the number of char in the file
        int i=0;int sum=0;

        for (auto pair2: frequency) {//loop on frequency map to add the total number of bits in original file
            a[i]=pair2.second;//saves the frequency of each char
            sum+= pair2.second*8;//the total number of bits in original file
            jh+=pair2.first;
            i++;
        }



        cout << "\nOriginal string is:\n" << data.str() << '\n';
        if(trial!=1)
            str="";

        for (char ch: data.str()) {
          str += huffmanCode[ch];
        }


        int b[arraysize];i=0;
        ofstream file;
        file.open(FILENAME2);
        string h=" ";
         Standard_encode(jh) ;
         cout << "The new values of codes:\n" << '\n';

        for (auto pair: huffmanCode) {//loop on huffman map to print the char and its equivalent code
        cout << pair.first << " " << pair.second << '\n';
         file<< pair.second;
         file<< pair.first;

        b[i]=pair.second.length();//saves the length of bits of each variable
        i++;
        }
        file<<h;
        file.close();

       // cout << "\nEncoded string is:\n" << str << '\n';
        tobytes(str,FILENAME2);//convert the bits into bytes
        getfreq(a,b,sum);//the total number of bits in encoded file
    using namespace std::chrono;
    auto stop = high_resolution_clock::now();//end of time for encoding
    auto duration = duration_cast<microseconds>(stop - start1);
    cout << "Time taken to encode: "
         << duration.count() << " microseconds" << endl;

     //print_tree_structure(root,1);
    }

    else if(option==2)

   {

     using namespace std::chrono;
     auto start = high_resolution_clock::now();
     int index = -1;

     string s;string filename=FILENAME2;
     cout << "\nDecoded file is:\n";


  std::ifstream input( FILENAME2, std::ios::binary ); // aw compressed.txt 3ady bardo
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
     int test=0; char mn;
     int kl=0;char c;string chck;

     while(test!=1)
     {
         mn=buffer[kl];kl++;
         chck=mn;
        // printf(" %c  ",chck);
         mn=buffer[kl];
         while(mn=='0' || mn=='1')
         {

             chck=chck+mn;
             kl++; mn=buffer[kl];

         }
          //cout << chck;
         c=buffer[kl];kl++;
        // printf("%c\n",c);
         //
         huffmanCode.insert({ c, chck });
         mn=buffer[kl];
         if (mn==' ')
            test=1;
     }
     for (auto pair: huffmanCode) {//loop on huffman map to print the char and its equivalent code
        cout << pair.first << " " << pair.second << '\n';
     }
     //Node* root2=huffmanTree2(huffmanCode);
     int m;kl++;
     int zeros = buffer[kl];
     m = buffer[kl+1];
     str=tobinary(m);
    for(int i=kl+2; i < buffer.size(); i++){
            m = buffer[i];
            string g=tobinary(m);//convert the ascii read from to file to binary
            str.append(g);//appeend to string

    }
    str = str.substr(0, str.size()-zeros);

   string j=decode2(root,str);//decode str
   cout << j;//print decoded string
    using namespace std::chrono;
     printf("\n");
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken to decode: "
         << duration.count() << " microseconds" << endl;
         printf("\n");
        // print_tree_structure(root2, 1);
   }


}



    return 0;
}
