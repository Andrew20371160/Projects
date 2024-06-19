
/*Includes*/
#include <iostream>
#include <conio.h>
#include <queue>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//used these in testing you can delete these if you want
#include <chrono>
#include <thread>
#include <random>



using namespace std ;



//node structure conataining template data type
template <typename DataType>
struct node{
    DataType data ;
    node<DataType>*left;
    node<DataType>*right ;
    node<DataType>*parent ;
};

//helper functions to take right input
//if user enters a character while expecting an integer or vice versa it doesn't cause issues
bool getInput(char& choice);
bool getInput(int& choice);



    /*
    to_string overloading for different data types
    needed for custom_data and save and load
    if overloading occurs for very large integers these will produce wrong out put

    */
    string to_string(const int &data);
    string to_string(const char &data);
    string to_string(const double &data);
    string to_string(const float &data);
    string to_string(const long &data);
    string to_string(const double &data);
    string to_string(const bool &data);
    string to_string(const unsigned int&data);
    string to_string(const string&data);

    //turns a vector into a string
    //this bst an be used to store vectors
    template<typename DataType>
    string to_string(const vector<DataType>&vec);

    bool openFileForWriting(const string& filePath);
    bool openFileForReading(const string& filePath);


enum {not_sorted=0,sorted} ;


//class bst
template<typename DataType>
class bst{
    //root of the bst
    node<DataType>*root ;
    //this pointer is used in traversing the tree and search and deltetion
    //its mutable so that when searching in a const tree it doesn't cause an error
    mutable node<DataType>*traverser;

    //number of nodes inside the tree
    long long size ;

    /*
    helper functions that aren't accessible by the user
    */

    //helper function to allocate memory for a new node
    node<DataType>*get_node(const DataType& _data);//passed

    //this function promts the user (if the tree contains data)
    // if he/she wants to save the tree before deletion
    //since loading is done on an empty tree
    void del_to_load(void) ;

    //checks if ptr is left or right child or is the root
    bool is_left(node<DataType>*ptr)const ;//passed
    bool is_right(node<DataType>*ptr)const ;//passed
    bool is_root(node<DataType>*ptr)const ;//passed

    /*
    this function makes ptr's parent's link pointing at ptr point at another destiniation
    for example ptr is left child of a parent left and we want it to point to another node
    this function takes care of it
    */
    void fix_parent(node<DataType>*ptr,node<DataType>*dest);//passed

    //returns a pointer to maximum data or rightmost node in the tree
    node<DataType>* get_max(node<DataType>*)const ;//passed

    //returns a pointer to minimum data or leftmost node in the tree
    node<DataType>* get_min(node<DataType>*)const ;//passed

    //takes a root pointer of some tree or a subtree and then makes a copy and then
    //returns resulting root (used in operator=)
    node<DataType>* copy_bst(const node<DataType>*) ;//passed

    //deletes a tree or a subtree where root is ptr
    void del_tree(node<DataType>*ptr) ;//passed

    /*
    these functions fill a bst from sorted data in linear time (O(N))
    and returns the root of the treee
    one from an array and the other one from a file but the indexing file must exist(used in load)
    */
    node<DataType>*fill_sorted(const DataType*arr,long long  beg,long long  size,node<DataType>*ptr);//passed
    node<DataType>*fill_sorted(const vector<DataType>&arr,long long  beg,long long  size,node<DataType>*ptr);//passed
    node<DataType>*fill_sorted(ifstream&file,ifstream&index_file,long long  beg,long long  size,node<DataType>*ptr);//passed


    /*
    this function saves the bst in a file with an index_file (inorder)
    index_file contains for each row it contains the starting point of data in the saved file
    think of computer organization how stack pointer works with stack
    data is pushed and the stack pointer is pointing at the new data
    so for row one it contains 0 for row 2 it contains sizeof(data1)
    for row3 it contains sizeof(data1+data2) and so on
    if index file is removed or the name is altered (the .bin file )
    data may not be loaded correctly or it would take O(NlogN) since it assumes that its not sorted
    if the .bin doesn't exist
    */
    void inorder_save(node<DataType>*ptr=NULL, ofstream& file=NULL, ofstream& index_file=NULL)const;

    //load data from data that's not ordered
    bool load_unorder(ifstream&file) ;
    //loads data from a file that's ordered
    bool load_inorder(ifstream&file,ifstream&index_file) ;

public:
    //empty tree
    bst(void);//passed
    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    bst(const DataType*arr,const long long  size);//passed

    //tree filled from an array
    //if data is sorted its filled in O(N) else O(Nlog2N)
    bst(const vector<DataType>&arr);//passed

    //copy constructor
    bst(const bst&src);//passed

    //destructor of the tree
    ~bst(void) ;//passed

    //assignment operator
    //if src is empty then the phantom will be deleted aswell it assigns src to phantom
    //so be careful
    void operator=(const bst&src) ;//passed


    //returns true if data in an array is sorted
    bool is_sorted(const DataType*arr,long long  size);
    //returns true if data in a file is sorted
    bool is_sorted(ifstream&file);

    bool is_sorted(const vector<DataType>&arr);

    //inserts data into the bst
    //data isn't inserted if the unique value is repeated
    //check documentation below the class of the necessary operations you must include in your object
    //so that this bst works
    bool insert(const DataType&data) ;//passed
    //this function puts traverser on the node containing data if found
    //and returns true
    bool search(const DataType&data)const  ;//passed
    //this function removes node contatining data if found
    //returns true if node is found
    bool remove(const DataType&data) ;

    //this function removes the whole bst
    bool remove_tree(void);//passed

    //this function looks for the node containing data and remvoes the node
    //and the subtree below it
    //if its the root node then whole tree is deleted
    bool remove_subtree(const DataType&data) ;

    /*
    this function saves the bst in a file with an index_file (inorder)
    index_file contains for each row it contains the starting point of data in the saved file
    think of computer organization how stack pointer works with stack
    data is pushed and the stack pointer is pointing at the new data
    so for row one it contains 0 for row 2 it contains sizeof(data1)
    for row3 it contains sizeof(data1+data2) and so on
    if index file is removed or the name is altered (the .bin file )
    data may not be loaded correctly or it would take O(NlogN) since it assumes that its not sorted
    if the .bin doesn't exist
    */
    bool save(void)const ;
    /*
    this function has 2 features one is loading from a sorted file which takes O(N)
    and the other is loading from unordered file which takes O(NlogN)
    if the .bin file (index_file) doesn't exist then it assumes the latter option which is loading
    in O(NLog2N) if the tree contains data then it promts user about it
    */
    bool load(void) ;
    /*
    printing functions
    */
    void inorder(node<DataType>*ptr=NULL)const ;//passed

    void preorder(node<DataType>*ptr=NULL)const ;//passed

    void postorder(node<DataType>*ptr=NULL)const ;//passed

    void breadth_first(node<DataType>*ptr=NULL)const ;//passed

    //equality of 2 bst is if they have same structure and same data
    //so breadth first equality is checked via this function
    bool operator==(const bst&src)const  ;
    //compares max of phantom is less than max of src
    bool operator <(const bst&src) const ;
    //compares if max of phantom is bigger than max of src
    bool operator >(const bst&src) const ;
    //turns a bst into a string and stores it into str
    //used in cout<<
    void to_string(string&str,node<DataType>*ptr=NULL)const ;

    //moves traverser in the tree via a set of controls
    void move(void) ;//passed

    //returns number of elements stored in the tree
    long long  get_size() ;
    /*
    if you saved a tree1 in a file and loaded it again using load breadth first the
    loaded tree has same structure and elements of tree1
    */
    void save_breadth_first(void)const;
    //loads the bst in the same structure it was saved in
    void  load_breadth_first(void);


    DataType access_traverser(void) ;
};



    //turns bst into a string
    template<typename DataType>
    string to_string(const bst<DataType>&tree);


    //you can cout a bst
    template<typename DataType>
    ostream& operator<<(std::ostream& os, const bst<DataType>& obj) ;

    //you can cin>>  into a bst
    //it stops reading data when it sees '\n' you have to type it manulally
    template<typename DataType>
    istream& operator>>(std::istream& is, bst<DataType>& obj);





    /*
    for a bst it has 2 things for data stored (In my opinion) one is a unique parameter which data is sorted
    according to it and some other data following the unique_parameter
    for example : you have a unique ID or social security number but 10000 person can have your name ,age ....etc
    so for a bst to store such thing the structure will be like this

    struct person{
    int id ;
    int age ;
    string first_name ;
    string last_name  ;
    string address ;
    };

    so you would need 2 int and 3 strings one of the int is unique_parameter and the rest could be duplicates
    hence custom_data and other_data are used
    other_data stores pointers for data that's allocated it contains a pointer to long,double,string,char,bool
    these pointers could be nulls (not allocated) or used
    and an array of five elements each containing size allocated for each array

    */

    enum{unique_element = 0 ,long_count=1,double_count,string_count,char_count,bool_count };

        class other_data{
            /*
            here are set of pointers for necessary data types to store elements
            */
            string *strings ;
            double *doubles ;
            //long is used since its standrdized to be 4 bytes in size
            //better than int which is compiler dependent
            long * longs ;
            char *characters;
            bool *booleans ;
            //contains size of each array
            int data_type_count[5];
            //custom_data is friend to other_data
            template<typename unique_data_type>
            friend class custom_data ;
        public:
            //empty other_data
            other_data(void);

            //set size of each array according
            //use same arrangement of enumerators you see to allocate memory
            //ldscb ->long ,double ,string ,character,bool
            //if you don't need memeory for a certain data type just type zero
            //or a value less than zero it won't allocate and no seg-fault will occur
            //easier to set the size of each vector in custom_data though
            other_data(int arr[5]) ;
            other_data(int integer_array_size,int floating_point_array_size, int string_array_size,int char_array_size ,int bool_array_size) ;

            //delete each array
            ~other_data() ;
            //assign operator for other_data
            void operator=(const other_data&)  ;
            //not implemented
            bool operator==(const other_data&)const ;
            //turns other_data into a string
            //used in saving/loading ,cout of other data
            string to_string(void) const ;

    };

    //ldscb class

    /*
    custom_data is the class to interface with
    it contains a template data type (unique_parameter)
    that's used in to saving elements in a bst (strings,integers ,floats....etc)

    unique_data_type is the data type of the unique_parameter
    for example id of a person requires an int
    if you use names then string
    like this custom_data<int> (custom_data where the unique parameter is an int)
    for the bst its bst<custom_data<int>> a bst that stores data type of custom_data and the unique parameter in custom_data
    is an int
    with this class you can create your own custom data base where you allocate size you want for each data type
    and the bst handles the rest
    */
    template<typename unique_data_type>
    class custom_data{
        private:
            /*
            element used in storing in the bst
            must be unique or data won't be inserted
            */
            unique_data_type unique_parameter;
            /*
                other_data you may want to store in the class
            */
            other_data other ;

        public:
            //empty constructor
            custom_data(void) ;
            //copy constructor
            custom_data(const custom_data&) ;

            //same constructor idea used in custom_data
            //pass an array of elements indicating size wanted for each data type
            //and size of it
            custom_data(int*arr,int size );
            custom_data(int integer_array_size,int floating_point_array_size, int string_array_size,int char_array_size ,int bool_array_size) ;

            //destructor (empty since the destructor is already implemented in other_data class)
            ~custom_data() ;
            /*
            here you set the size or resize each vector independently
            you pass the enumerator value e.g. long_count and the new size
            if size<=0 vector is deleted and the data_type_count array is updated
            */
            void set_data_type_size(int data_type_enum_value,int size);

            /*
            logical and assignment operators overloaded to save the custom_data in the bst
            */
            //assign custom_data into another custom_data
            //note that vectors and their sizes of other_data are assigned aswell
            //no seg-faults
            void operator=(const custom_data&)  ;
            /*
            logical operators
            here the unique_parameter is compared only not the other data
            used in storing data in the bst
            if the unique parameter is a complex structure you need to implement those
            but i don't see a need for a complex structure since this custom_data class contains the necessary data types (in my opinion)
            you also need to implement << and >> for that complex structure and the to_string
            */
            bool operator<(const custom_data&)const;
            bool operator>(const custom_data&)const;
            bool operator<=(const custom_data&)const;
            bool operator>=(const custom_data&)const;
            bool operator==(const custom_data&)const;
            bool operator!=(const custom_data&)const;
            //turns custom_data (whole data including vectors of other data into a string )
            /*
            in this order unique_parameter->vector size of each data type in this order ldscb or (long double string char bool)
            and then each vector in same previous order
            */
            string to_string(void)const ;
            //get size stored of a vector of that data type
            int get_data_type_count(int dt) const ;
            /*
            accessor for each element in the custom_data class
            */
            //access and update the unique element
            unique_data_type& at_unique(void);
            const unique_data_type& at_unique(void) const;
            /*
                access and update for an index of each data type used in other_data
                if and index is out of bounds it returns nothing
            */
            //at index of long data type array
            long& at_longs(int index);
            const long& at_longs(int index) const;

            //at index of long data type array
            double& at_doubles(int index);
            const double& at_doubles(int index) const;
            //at index of char data type array
            char& at_chars(int index);
            const char& at_chars(int index) const;

            string& at_strings(int index);
            const string& at_strings(int index) const;

            bool& at_bools(int index);
            const bool& at_bools(int index) const;

        };
    //turns custom_data into a string with all its content
    template<typename unique_data_type>
    string to_string(const custom_data<unique_data_type>&p);
    string to_string(const unsigned int&data);
    //overloaded operator for writing and reading (used in loading and saving )
    //for cout its opvious
    template<typename unique_data_type>
    ostream& operator<<(ostream& os, const custom_data<unique_data_type>& obj) ;

    /*
    you can input into an obj here is how it takes input
    the unique parameter ->size of each vector in this order ldscb input of each array
    note if an array is empty it doesn't cause segmentation fault and btw when you input the size of each array
    it allocates or deallocate for that vector (used in saving and loading)
    */
    template<typename unique_data_type>
    istream& operator>>(istream& is, custom_data<unique_data_type>& obj);


    /*
    the following class is an example of how to use the code
    */
    //enum for ease of use of the array of strings
    enum{first_name =0,last_name,birth_date,city};
    class civil_record{
        //ldscb->long or integers ,floating point values->strings->characters->booleans

        //say we store age ,height ,life_status first name ,last name ,city of residance
        //date of birth , say a character indicating hair color or something similar
        bst<custom_data<int>> data_base;
        //we interface with the user using this object
        custom_data<int> person;

        public:
            civil_record() ;
            ~civil_record() ;

            void insert_person(void) ;
            void delete_person(void) ;
            void search_person(void) ;
            void save_data_base(void) ;
            void load_data_base(void) ;
            void delete_data_base(void) ;
            void show_data_base(void) ;


    };
