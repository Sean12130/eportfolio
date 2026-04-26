#include "ItemTracker.h"
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>


/*
 * generateLargeInputFile
 * --------------------------------------------------------
 * Creates a large dataset of fruits and vegetables
 * for testing ItemTracker performance and functionality.
 */
void generateLargeInputFile() {
    std::ofstream file("CS210_Project_Three_Input_File.txt");

    std::vector<std::string> items = {
        "Spinach","Radishes","Broccoli","Peas","Cranberries","Potatoes",
        "Cucumbers","Peaches","Zucchini","Cantaloupe","Beets","Cauliflower",
        "Onions","Yams","Apples","Celery","Limes","Garlic","Pumpkins",
        "Pears","Tomatoes","Carrots","Mangoes","Bananas","Strawberries",
        "Blueberries","Raspberries","Blackberries","Kale","Lettuce",
        "Eggplant","Corn","GreenBeans","Cherries","Plums","Apricots",
        "Watermelon","Grapes","Oranges","Pineapple","Kiwi","Avocado"
    };

    srand(time(0));

    // Generate 2100 lines
    for (int i = 0; i < 2100; i++) {
        file << items[rand() % items.size()] << std::endl;
    }

    file.close();
    std::cout << "Large input file generated successfully.\n";
}
/*
 * Source Program
 * --------------------------------------------------------
 * Provides a menu-driven interface for users to interact
 * with the ItemTracker class.
 *
 * Features:
 * - Search item frequency
 * - Display all items
 * - Display histogram
 * - Display top-N frequent items
 * - Exit and save data
 */
int main() {
    generateLargeInputFile(); 
    ItemTracker tracker; // Initialize tracker and process file
    int choice = 0;

    while (choice != 5) {
        tracker.DisplayMenu();
        std::cin >> choice;

        // Input validation
        while (!std::cin || choice < 1 || choice > 5) {
            std::cout << "Invalid input! Enter an integer between 1-5: ";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cin >> choice;
        }

        if (choice == 1) {
            std::cout << "Enter item to search: ";
            std::string searchItem;
            std::cin >> searchItem;
            tracker.FindItem(searchItem);
        }
        else if (choice == 2) {
            tracker.PrintList();
        }
        else if (choice == 3) {
            tracker.PrintHistogram();
        }
        else if (choice == 4) {

            // Get the maximum number of unique items available
            int maxItems = tracker.GetItemCount();
            std::cout << "\nMaximum available items: "
                << maxItems << std::endl;

            std::cout << "How many items would you like to display? ";
            int numberOfItems;
            std::cin >> numberOfItems;

            // Input validation with maximum limit
            while (!std::cin || numberOfItems <= 0 || numberOfItems > maxItems) {
                std::cout << "Invalid input! Enter a number between 1 and "
                    << maxItems << ": ";

                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cin >> numberOfItems;
            }

            tracker.PrintMostFrequent(numberOfItems);
        }
        else if (choice == 5) {
            std::cout << "Exiting program..." << std::endl;
            tracker.FileCreation();
        }
    }

    return 0;
}