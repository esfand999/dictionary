#include<iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// An AVL tree node
struct Node {
    string key;
    struct Node *left;
    struct Node *right;
    int count = 0;
    int depth;
};

int counter;
int countArray;

int depth(struct Node *N){
    if (N == NULL)
        return 0;
    return N->depth;
}

int max(int a, int b) {
    if(a>b)
        return a;
    else
        return b;
}

struct Node* newNode(string key)  {
    struct Node* node = new Node;
    node->key = key;
    node->left   = NULL;
    node->right  = NULL;
    node->count = 0;
    node->depth = 0;
    return(node);
}

struct Node *rightRotate(struct Node *y)  {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->depth = max(depth(y->left), depth(y->right))+1;
    x->depth = max(depth(x->left), depth(x->right))+1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->depth = max(depth(x->left), depth(x->right))+1;
    y->depth = max(depth(y->left), depth(y->right))+1;

    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return depth(N->left) - depth(N->right);
}

int compareStrings(string s1, string s2) {
    int x = s1.compare(s2);

    if (x == 0) {
        return 0;
    }
    else if (x > 0) {
        return -1;
    }
    else{
        return 1;
    }
}

struct Node* insert(struct Node* node, string key)  {
    if (node == NULL)
        return(newNode(key));

    if (compareStrings(node->key, key) == -1)
        node->left  = insert(node->left, key);
    else if (compareStrings(node->key, key) == 1)
        node->right = insert(node->right, key);
    else
        return node;

    node->depth = 1 + max(depth(node->left), depth(node->right));

    int balance = getBalance(node);


    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key){
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void InOrder(struct Node *root)  {
    if(root != NULL){
        InOrder(root->left);
        cout<< root->key << "\n";
        InOrder(root->right);
    }
}

void InOrderCount(struct Node *root)  {
    if(root != NULL){
        InOrderCount(root->left);
        cout <<  root->key << " " << root->count << endl;
        InOrderCount(root->right);
    }
}

void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout<< root->key <<"\n";
        preOrder(root->left);
        preOrder(root->right);
    }
}

Node* minValue(struct Node* Node)  {
    struct Node* current = Node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)  {
        current = current->left;
    }
    return(current);
}

Node* deleteNode(Node* root, string key)  {
    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    else {
        if( (root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)  {
                temp = root;
                root = NULL;
            }

            else
                *root = *temp;
            free(temp);
        }

        else {
            Node* temp = minValue(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->depth = 1 + max(depth(root->left), depth(root->right));

    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)  {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool checkMutated(string s1, string s2){

    bool check = false;

    char c;
    char d;

    int len = 0;
    int count = 0;

    if(s1.length() == 1 || s1.length() == 0 || s2.length() == 1 || s2.length() == 1 ||
        s1.length() == 2 || s2.length() == 2){
        return check;
    }

    if (s1.length() > s2.length()) {
        len = s2.length();
        for (int i = 0; i < len; i++) {
            c = s1[i];
            d = s2[i];

            if (c == d) {
                count++;
            }
        }
        if (len - count == 0) {
            cout << "Original word: " << s2 << endl;
            cout << "Corrected word: " << s1 << endl;
            return true;
        }
    } else if (s1.length() < s2.length()) {
        len = s1.length();
        for (int i = 0; i < len; i++) {
            c = s1[i];
            d = s2[i];

            if (c == d) {
                count++;
            }
        }
        if (len - count == 0) {
            cout << "Original word: " << s2 << endl;
            cout << "Corrected word: " << s1 << endl;
            return true;
        }
    } else if (s1.length() == s2.length()){
        len = s1.length();
        for (int i = 0; i < len; i++) {
            c = s1[i];
            d = s2[i];

            if (c == d) {
                count++;
            }
        }
        if (len - count == 1) {
            cout << "Original word: " << s2 << endl;
            cout << "Corrected word: " << s1 << endl;
            return true;
        }
    }

//    for (int i = 0; i < len; i++) {
//        c = s1[i];
//        d = s2[i];
//
//        if ( c == d ) {
//            count++;
//        }
//    }

//    if ( s1.length() - count == 1 || s2.length() - count == 1) {
//        cout << "Original word: " << s2 << endl;
//        cout << "Corrected word: " << s1 << endl;
//        check = true;
//    }
//    else if (s1.length() - count == 0 || s2.length() - count == 0) {
//        check = true;
//    }
    return check;
}

int countNodes(Node* root){
    int count = 1;
    if (root->left != NULL) {
        count += countNodes (root->left);
    }
    if (root->right != NULL) {
        count += countNodes (root->right);
    }
    return count;
}

void removePunctuation(string inputFile[]){
    for (int i= 0; i <500; ++i) {
        string text = inputFile[i];
        for (int j = 0, len = text.size(); j < len; j++) {
            if (ispunct(text[j])) {
                text.erase(j--, 1);
                len = text.size();
            }
        }
        inputFile[i] = text;
    }

    //double check for punctuation
    for (int i= 0; i <500; ++i) {
        string text = inputFile[i];
        for (int j = 0, len = text.size(); j < len; j++) {

            if (ispunct(text[j])) {
                text.erase(j--, 1);
                len = text.size();
            }
        }
        inputFile[i] = text;
    }
}

bool Search(Node *root, string key){
    if (root == NULL)
        return false;

    if (root->key == key)
        return true;

    bool res1 = Search(root->left, key);

    if(res1==true) {
        return true;
    }

    bool res2 = Search(root->right, key);
    return res2;
}

void countFrequency(Node *root, string word) {
    if (root != NULL) {
        countFrequency(root->left, word);
        if (root->key == word) {
            root->count += 1;
        }
        countFrequency(root->right, word);
    }
}

void convertToLowerCase(string inputFile[]){
    for (int i = 0; i < 500; i++) {
        transform(inputFile[i].begin(), inputFile[i].end(), inputFile[i].begin(), ::tolower);
    }
}

void compare(Node *root, Node *root2)
{
    if (root == NULL)
        return;

    compare(root->left, root2);
    checkMutated(root->key, root2->key);
    compare(root->right, root2);
}

void traverse(Node *root2, Node *root)
{
    if (root2 == NULL)
        return;

    traverse(root2->left, root);
    compare(root, root2);
    traverse(root2->right, root);
}


int main() {

    cout << "\n/////////////////////// DICTIONARY /////////////////////// \n";

    struct Node *root = NULL;
    struct Node *root2 = NULL;

    //insert dictionary to AVL
    ifstream file(R"(C:\Users\esfan\Desktop\Dictionary\dictionary.txt)");
    string dictionary[289];

    if (file.is_open()) {
        for (int i = 0; i < 289; ++i) {
            file >> dictionary[i];
        }
    }
    for (int i = 0; i < 289; i++) {
        root = insert(root, dictionary[i]);
    }

    //insert a text file to test
    ifstream file2(R"(C:\Users\esfan\Desktop\Dictionary\Clean.txt)");
    string inputFile[500];

    if (file2.is_open()) {
        for (int i = 0; i < 500; ++i) {
            file2 >> inputFile[i];
        }
    }

    //remove punctuation and convert to lowercase
    removePunctuation(inputFile);
    convertToLowerCase(inputFile);

    for (int i = 0; i < 500; i++) {
        if (inputFile[i] != "") {
            root2 = insert(root2, inputFile[i]);
            countArray += 1;
        }
    }


    //Runner
    int selection;
    do {
        cout << "\n Enter your choice: ";
        cout << "\n 1. Count number of words in the input file.";
        cout << "\n 2. Check for spelling mistakes.";
        cout << "\n 3. Insert a new word in the dictionary.";
        cout << "\n 4. Delete a word from dictionary.";
        cout << "\n 5. Search for a word in dictionary.";
        cout << "\n 6. Display dictionary.";
        cout << "\n 7. Count frequency of dictionary words in test file.";
        cout << "\n 8. Count number of words in dictionary.";
        cout << "\n Enter 0 to exit.";
        cout << "\n ->";

        cin >> selection;

        if (selection == 1) {
            cout << "Number of words in input file: " << countArray <<endl;
        } else if (selection == 2) {
            /**sus code
             * check again
             * test it
             * */
                traverse(root2, root);
        } else if (selection == 3) {
            string word;
            cout << "Enter word to insert in dictionary: ";
            cin >> word;
            insert(root, word);
            cout << "Word successfully inserted! \n";
        } else if (selection == 4) {
            string word;
            cout << "Enter word to delete from dictionary: ";
            cin >> word;
            deleteNode(root, word);
            cout << "Word successfully deleted! \n";
        } else if (selection == 5) {
            string word;
            cout << "Enter word to search in dictionary: ";
            cin >> word;
            if (Search(root, word)){
                cout << "Word present in dictionary.";
            }
            else{
                cout << "Word not present in dictionary.";
            };
        } else if (selection == 6) {
            cout <<"Displaying dictionary: " << endl;
            cout << "-----------------------------------------------------";
            InOrder(root);
        } else if (selection == 7) {
            for (int i = 0; i < 500; i++) {
                countFrequency(root, inputFile[i]);
            }
            InOrderCount(root);
        } else if (selection == 8){
            cout << "Number of words in dictionary: " << countNodes(root);
        } else if (selection == 0) {
            cout << "\n Exiting... ";
        } else {
            cout << "\n Please select a valid option. ";
        }
    }
    while(selection != 0);
}
