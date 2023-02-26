

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
//============================================================================
// Name        : LinkedList.cpp
// Author      : Scott Dixon
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include "CSVparser.hpp"
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 
//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    //Internal structure for list entries, housekeeping variables
    struct Node {
        Bid bid;
        Node *next;

        // default constructor
        Node() {
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) {
            bid = aBid;
            next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};


 // Default constructor
 // FIXME (1): Initialize housekeeping variables
    //set head and tail equal to null


LinkedList::LinkedList() {
    // Initialize housekeeping variables
    head = nullptr;
    tail = nullptr;
    size = 0;
}


 
 
    //Destructor
 
LinkedList::~LinkedList() {
    // Start at the head
    Node* current = head;
    Node* temp;

    // Loop over each node, detach from list then delete
    while (current != nullptr) {
        temp = current; // Hang on to current node
        current = current->next; // Make current the next node
        delete temp; // Delete the orphan node
    }
}

    


/**
 * Append a new bid to the end of the list
 */
 // FIXME (2): Implement append logic - Done
void LinkedList::Append(Bid bid) {
    // Create a new node with the given bid
    Node* newNode = new Node(bid);

    // If the list is empty, set the head and tail pointers to the new node
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        // Otherwise, insert the new node at the end of the list
        tail->next = newNode;
        tail = newNode;
    }

    // Increase the size count
    size++;
}

    
    //Create new node
    //if there is nothing at the head...
            // new node becomes the head and the tail
    //else 
        // make current tail node point to the new node
        // and tail becomes the new node
    //increase size count


/**
 * Prepend a new bid to the start of the list
 */
 
// FIXME (3): Implement prepend logic - Done 
void LinkedList::Prepend(Bid bid) {
    // Create a new node with the given bid
    Node* newNode = new Node(bid);

    // If the list is not empty, insert the new node at the beginning
    if (head != nullptr) {
        newNode->next = head;
    }

    // Set the head of the list to the new node
    head = newNode;

    // Increase the size count
    size++;
}



/**
 *  output of all bids in the list
 */
 
 // FIXME (4): Implement print logic - Done
void LinkedList::PrintList() {
    // Start at the head
    Node* current = head;

    // Loop over each node in the list
    while (current != nullptr) {
        // Output the bid's details
        cout << current->bid.bidId << ": "
             << current->bid.title << " >> "
             << current->bid.amount << " >> "
             << current->bid.fund << endl;

        // Move to the next node
        current = current->next;
    }
}


    // while loop over each node looking for a match
   

 // FIXME (5): Implement remove logic - Done ???
/**
 * Remove a specified bid
 *
 */
void LinkedList::Remove(string bidId) {
    // Special case: matching node is the head
    if (head != nullptr && head->bid.bidId == bidId) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    // Look for a match in the rest of the list  decrease size count
       // then return
       
    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->bid.bidId == bidId) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            // decrease size count
            size--;
            return;
        }
        current = current->next;// curretn node is equal to next node
    }
}
    
    




  // FIXME (6): Implement search logic - Done check
  
Bid LinkedList::Search(string bidId) {
    // Special case: matching node is the head
    if (head != nullptr && head->bid.bidId == bidId) {
        return head->bid;
    }

    // Search for a match in the rest of the list
    Node* current = head;
    while (current != nullptr) {
        if (current->bid.bidId == bidId) {
            return current->bid;
        }
        current = current->next;
    }

    // No match found
    return Bid();
}

/**
 * Returns the current size of list
 */
int LinkedList::Size() {
    return size;
}

    

    
        
     




//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98129"; // Test with different Bid Key
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.txt";
        bidKey = "98129";  // Test with different Bid Key
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);
            
            cout << " bid is now removed." << endl;
            cout << " Bid Register Empty." << endl;
            break;
        }
    }

    cout << "Good bye, thank you for using Linked List program for this week!" << endl;

    return 0;
}
