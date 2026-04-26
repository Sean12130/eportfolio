#ifndef ITEMTRACKER_H
#define ITEMTRACKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

/*
 * ItemTracker Class
 * --------------------------------------------------------
 * Tracks item frequencies from an input file. The class
 * processes items efficiently using a map and provides
 * multiple ways to display results.
 *
 * Design Purpose:
 * - Efficiently count item occurrences
 * - Provide case-insensitive search
 * - Display items as a list, histogram, or top-N frequent items
 * - Save results to a file
 *
 * Software Design Principles Used:
 * - Encapsulation
 * - Separation of concerns
 * - Use of efficient data structures
 * - Maintainability and readability
 */

class ItemTracker {
private:
    /*
     * Data Storage
     * --------------------------------------------------------
     * itemFrequency stores each unique item as a key and
     * its count as the value. Using a map provides:
     * - Efficient search and insertion
     * - Automatic uniqueness of keys
     */
    std::map<std::string, int> itemFrequency;

public:
    // Constructor: processes file and builds map
    ItemTracker();

    // Menu display
    void DisplayMenu();

    // Search for a single item and display its frequency
    void FindItem(const std::string& inputWord);

    // Display all items and their frequencies
    void PrintList();

    // Display a histogram of items
    void PrintHistogram();

    // Display top-N most frequent items
    void PrintMostFrequent(int numberOfItems);

    // Save all items and counts to a file
    void FileCreation();

    // Returns the number of unique items in the dataset
    int GetItemCount();

};

#endif // ITEMTRACKER_H