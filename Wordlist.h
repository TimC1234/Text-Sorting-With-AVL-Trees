// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Kuan Ting (Tim) Chou
// St.# : 301562019
// Email: tim_chou@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height; // height of the node
    };

    Node *root = nullptr;

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //

    // helper function for destructor
    // uses post_order traversal to delete nodes
    void destruct_helper(Node *N)
    {
        if (N == nullptr)
        {
            return;
        }
        destruct_helper(N->left);
        destruct_helper(N->right);
        delete N;
    }

    // helper function for num_different_words()
    int num_unique_words(Node *N) const
    {
        Node *temp = N;

        if (temp == nullptr)
        {
            return 0;
        }

        int unique_words_left = num_unique_words(temp->left);
        int unique_words_right = num_unique_words(temp->right);
        return 1 + unique_words_left + unique_words_right;
    }

    // helper function for total_words
    int total_helper(Node *N) const
    {
        if (N == nullptr)
        {
            return 0;
        }
        int total_words_left = total_helper(N->left);
        int total_words_right = total_helper(N->right);
        return N->count + total_words_left + total_words_right;
    }

    // helper function for most_frequent
    void most_freq(Node *N, int &max, string &w) const
    {
        if (N == nullptr)
        {
            return;
        }

        if (N->count > max)
        {
            max = N->count;
            w = N->word;
        }

        most_freq(N->left, max, w);
        most_freq(N->right, max, w);
    }

    // num_singletons helper function
    void num_singles(Node *N, int &singles) const
    {
        if (N == nullptr)
        {
            return;
        }
        if (N->count == 1)
        {
            singles++;
        }
        num_singles(N->left, singles);
        num_singles(N->right, singles);
    }

    // helper function for print_words
    void print_helper(Node *N, int &counter) const
    {
        // uses inOrder Traversal

        if (N == nullptr)
        {
            return;
        }

        print_helper(N->left, counter);

        // uses "\"" to print the quotation marks
        cout << to_string(counter) << ". {\"" << N->word << "\", " << N->count << "}\n";
        counter++;
        print_helper(N->right, counter);
    }

    // helper comparison function to return bigger value
    int max(int x, int y)
    {
        // is x bigger than y?
        // if yes returns x else return y
        return (x > y) ? x : y;
    }

    // helper function to assign heights to the nodes
    // this helper function will allow me to check if the left or right child exist
    // then it will return their heights if they exist
    int height(Node *N)
    {
        if (N == nullptr)
        {
            return 0;
        }
        return N->height;
    }

    // balance factor getter function
    int balance_factor(Node *N)
    {
        if (N == nullptr)
        {
            return 0;
        }

        // balance factor = height of left child - height of right child
        return (height(N->left) - height(N->right));
    }

    // code built upon from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    // right rotation helper function
    Node *rotate_right(Node *y)
    {

        // Set x as the left child of y and T2 as the right child of x.
        Node *x = y->left;
        Node *T2 = x->right;

        // update the pointers
        x->right = y;
        y->left = T2;

        // update their heights
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));

        // return rotated root
        return x;
    }

    // code built upon from https://www.geeksforgeeks.org/insertion-in-an-avl-tree/
    // helper function for left rotation
    Node *rotate_left(Node *x)
    {

        // Set y as the right child of x and T2 as the left child of y.
        Node *y = x->right;
        Node *T2 = y->left;

        // update the pointers
        y->left = x;
        x->right = T2;

        // update their heights
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));

        // return rotated root
        return y;
    }

    Node *insert(Node *node, const string &word)
    {
        if (node == nullptr)
        {
            // this will become the root since its the first node added
            // will immediately return since it will be in sorted order
            // and height balance property will be satisfied
            //will set the new node's height to be 1 since all leaf nodes have height 1

            Node *newNode = new Node{word, 1, nullptr, nullptr, 1};
            return newNode;
        }

        if (word < node->word)
        {
            node->left = insert(node->left, word);
        }

        else if (word > node->word)
        {
            node->right = insert(node->right, word);
        }

        else
        {
            // found duplicate
            node->count++;
        }

        // Update height of the current node.
        node->height = 1 + max(height(node->left), height(node->right));

        // check the balance factor of the node
        int balance = balance_factor(node);

        // Left skewed
        if (balance > 1)
        {
            // Left Left case so rotate right
            if (word < node->left->word)
            {
                return rotate_right(node);
            }

            // Left Right case so rotate left then rotate right
            else
            {
                node->left = rotate_left(node->left);
                return rotate_right(node);
            }
        }

        // Right skewed
        if (balance < -1)
        {
            // Right Right case so rotate left
            if (word > node->right->word)
            {
                return rotate_left(node);
            }

            // Right Left case so rotate right then rotate left
            else
            {
                node->right = rotate_right(node->right);
                return rotate_left(node);
            }
        }

        return node;
    }

public:
    // default constructor
    Wordlist()
    {

    }

    // file constructor
    Wordlist(const string &filename)
    {
        // code taken from my assignment 1 submission
        ifstream file(filename);
        if (!file.is_open())
        {
            throw runtime_error("File failed to open");
        }

        string input;

        // redirects the strings in the file into the string variable input
        while (file >> input)
        {
            // separates the strings into separate words then adds it to the avl tree
            add_word(input);
        }
        file.close();
    }

    // destructor
    ~Wordlist()
    {
        // uses post-order traversal to delete nodes
        destruct_helper(root);
        root = nullptr;
    }

    int get_count(const string &w) const
    {
        Node *temp = root;
        while (temp != nullptr)
        {
            if (w == temp->word)
            {
                return temp->count;
            }
            else if (w < temp->word)
            {
                temp = temp->left;
            }
            else if (w > temp->word)
            {
                temp = temp->right;
            }
        }
        return 0;
    }

    int num_different_words() const
    {

        return num_unique_words(root);
    }

    int total_words() const
    {
        return total_helper(root);
    }

    bool is_sorted() const
    {
        return true;
    }

    string most_frequent() const
    {
        int max = 0;
        string most_common;

        // calls helper function
        most_freq(root, max, most_common);

        // to_string converts an int to its string representation
        return most_common + " " + to_string(max);
    }

    int num_singletons() const
    {
        int singles = 0;
        num_singles(root, singles);
        return singles;
    }

    void print_words() const
    {
        int counter = 1;
        print_helper(root, counter);
    }

    void add_word(const string &w)
    {
        root = insert(root, w);
    }

}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//