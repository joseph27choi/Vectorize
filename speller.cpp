#include <iostream>

// declarations
int main();

// node
class Node {
    private:
        int key;
        char* value;
        Node* next;
    
    public:
        // constructor
        Node(int key, char* val_param){
            this->key = 0;
            this->value = val_param;
            this->next = NULL;
        }

        // encapsulation
        char* get_value() {return this->value;}
        void set_value(char* val_param) {this->value = val_param;}
        int get_key() {return this->key;}
        void set_key(int key_param) {this->key = key_param;}
        Node* get_next() {return this->next;}
        void set_next(Node* p_next_param) { this->next = p_next_param;}
};

// create the class
class HashTable {
private:
    int size;
    Node** p_table; // pointing to a node pointer
    // the array

public:
    // constructor
    HashTable();

    // encapsulation
    Node** get_p_table() {return this-> p_table;}

    void M(int);

    // hash function -- returns 
    void insert(char*);

    // read from dictionary
    
  
    // tokenize
    int get_token(char*);

    // search
    bool retrieve(int);
};

HashTable::HashTable() {
    this->size = 0;
    this->p_table = NULL;
};

void HashTable::M(int m) {
    this->size = m;
    this->p_table = new Node*[m];
    std::cout << "success" << std::endl;
};


void HashTable::insert(char* word_p) {
    // get the tockenization, d_index means dictionary index, meaning the order of encounter
    int d_index = 0;
    // find token, the sum of ascii values
    int token = this->get_token(word_p);
    // find the bucket position, t_index means table index
    int t_index = token % this->size;

    std::cout << t_index << std::endl;

    // make a node to store the word and key
    Node* p_node = new Node(d_index, word_p);
    
    std::cout << "here" << std::endl;

    // no chain yet
    if (this->p_table[t_index] == nullptr) {
        std::cout << "no chain yet" << std::endl;
        /* is setting allowed without encapsulation? */
        this->p_table[t_index] = p_node;
        p_node = nullptr;
    }
    // chain already exists, traverse the list to check for duplicates, then link at front
    else {
        std::cout << "already chain" << std::endl;
        // check if word already exists, if it does, exit
        if (this->retrieve(d_index) == true) {
            return;
        }
        // if word does not exist already, chain to the front
        Node* p_en = this->p_table[t_index]->get_next();
        p_node->set_next(p_en);
        this->p_table[t_index]->set_next(p_node);
    }

    // if word has been inserted then indicate it
    std::cout << "success" << std::endl;
    return;
};

int HashTable::get_token(char* word_p) {
    // insert into hash function given it's number
    int sum = 0;
    for (int w_index = 0; word_p[w_index] != '\0'; w_index++) {
        if (
             (word_p[w_index] >= 'A' && word_p[w_index] <= 'Z') || 
             (word_p[w_index] >= 'a' && word_p[w_index] <= 'z')
            )
        {
            // it is an alphabet
            sum = sum + word_p[w_index];
        }
        else {
            return 0;
        }
    }

    // key is the sum of characters
    int d_index = sum;

    return d_index;
}

bool HashTable::retrieve(int d_index) {
    if (d_index != 0) {
        int t_index = d_index % this->size;
        Node* p_en = this->p_table[t_index];

        // find the index
        while (p_en != nullptr) {
            if (p_en->get_key() == d_index) {
                std::cout << p_en->get_value() << std::endl;
                return true;
            } 
            p_en->set_next(p_en->get_next());   
        }
    }

    // could not find matching word
    std::cout << "UNKNOWN" << std::endl;
    return false;
};


// definitions
int main() {
    // creating hash table
    std::cout << "Enter your hash size: ";
    int m;
    std::cin >> m;
    std::cout << std::endl;

    // create hastable in stack
    HashTable hash;

    hash.M(m);

    char word[] = "Any";
    char collide[] = "ZzG";

    hash.insert(word);
    hash.insert(collide);

    return 0;
}