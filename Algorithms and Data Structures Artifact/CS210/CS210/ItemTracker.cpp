#include "ItemTracker.h"
#include <cctype>
#include <iomanip>
#include <algorithm>

/*
 * ItemTracker Implementation
 * --------------------------------------------------------
 * Implements all methods declared in ItemTracker.h
 * Processes a file, counts item frequencies, displays
 * results as list, histogram, or top-N frequent items,
 * and saves data to a file.
 */

 // Helper function for case-insensitive string conversion
std::string ToLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

/*
 * Constructor
 * --------------------------------------------------------
 * Reads the input file and populates the itemFrequency map.
 * Converts all items to lowercase to allow case-insensitive searches.
 */
ItemTracker::ItemTracker() {
    std::ifstream file("CS210_Project_Three_Input_File.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return;
    }

    std::string item;
    while (file >> item) {
        item = ToLower(item);
        itemFrequency[item]++; // Increment count in map
    }

    file.close();
}

/*
 * DisplayMenu
 * --------------------------------------------------------
 * Shows the main menu to the user.
 */
void ItemTracker::DisplayMenu() {
    std::cout << "\nItem Tracker Menu:" << std::endl;
    std::cout << "1. Search for item frequency" << std::endl;
    std::cout << "2. Display all item frequencies" << std::endl;
    std::cout << "3. Display histogram" << std::endl;
    std::cout << "4. Display most frequent items" << std::endl;
    std::cout << "5. Exit program" << std::endl;
    std::cout << "Enter your choice: ";
}

/*
 * FindItem
 * --------------------------------------------------------
 * Search for a specific item in the map and display its frequency.
 */
void ItemTracker::FindItem(const std::string& inputWord) {
    std::string key = ToLower(inputWord);

    auto it = itemFrequency.find(key);
    if (it != itemFrequency.end()) {
        std::cout << key << " was found " << it->second << " times." << std::endl;
    }
    else {
        std::cout << key << " was not found in the dataset." << std::endl;
    }
}

/*
 * PrintList
 * --------------------------------------------------------
 * Prints all items and their frequencies in alphabetical order.
 */
void ItemTracker::PrintList() {
    if (itemFrequency.empty()) {
        std::cout << "No items to display." << std::endl;
        return;
    }

    std::cout << "\nItem Frequency List:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for (const auto& pair : itemFrequency) {
        std::cout << std::setw(15) << std::left << pair.first
            << " : " << pair.second << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

/*
 * PrintHistogram
 * --------------------------------------------------------
 * Prints all items with a histogram of asterisks representing frequency.
 */
void ItemTracker::PrintHistogram() {
    if (itemFrequency.empty()) {
        std::cout << "No items to display." << std::endl;
        return;
    }

    std::cout << "\nItem Histogram:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for (const auto& pair : itemFrequency) {
        std::cout << std::setw(15) << std::left << pair.first << " : ";
        for (int i = 0; i < pair.second; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

/*
 * PrintMostFrequent
 * --------------------------------------------------------
 * Prints the top-N most frequent items in descending order.
 */
void ItemTracker::PrintMostFrequent(int numberOfItems) {
    if (itemFrequency.empty()) {
        std::cout << "No items to display." << std::endl;
        return;
    }

    // Convert map to vector for sorting
    std::vector<std::pair<std::string, int>> items(itemFrequency.begin(), itemFrequency.end());

    // Sort by frequency descending
    std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::cout << "\nTop " << numberOfItems << " Most Frequent Items:" << std::endl;
    std::cout << "---------------------------" << std::endl;

    for (int i = 0; i < std::min(numberOfItems, (int)items.size()); ++i) {
        std::cout << std::setw(15) << std::left << items[i].first
            << " : " << items[i].second << std::endl;
    }

    std::cout << "---------------------------" << std::endl;
}

/*
 * FileCreation
 * --------------------------------------------------------
 * Saves all items and their frequencies to frequency.dat.
 */
void ItemTracker::FileCreation() {
    std::ofstream outFile("frequency.dat");

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not create output file." << std::endl;
        return;
    }

    for (const auto& pair : itemFrequency) {
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
    std::cout << "Data saved to frequency.dat" << std::endl;
}

/*
 * GetItemCount
 * --------------------------------------------------------
 * Returns the total number of unique items stored in the map.
 * This allows the program to display the maximum number of
 * items available for Option 4.
 */
int ItemTracker::GetItemCount() {
    return itemFrequency.size();
}