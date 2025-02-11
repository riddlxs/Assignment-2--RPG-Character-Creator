// Liana Hockin
// Assignment 2
//October 22nd 2024

#include <iostream>
#include <string>
#include <vector>
#include <limits> //new library used specifically for numeric limits!
//include the libraries

class Character { //need to make a character class to store all the character data!
public:
    std::string name; //character name
    std::string ancestry; //character ancestry
    std::string className; //character classname (rouge etc)
    int abilityScores[6]; //characters ability scores
    int ancestryBonus[6]; // Ancestry bonuses for ability scores


    // create a constructor to initialize ability score to 0
    Character() {
        for (int& score : abilityScores) {
            score = 0; // starting all new characters out at 0 ability scores
        }
            for (int& bonus : ancestryBonus) {
                bonus = 0; // Initialize ancestry bonuses to 0
            }
        }

    void applyAncestryBonus() { // need to actually apply the bonuses
        if (ancestry == "Human") {
            abilityScores[0] = 2; // Strength because it is 0 
            abilityScores[1] = 2; // Dexterity because it is 1! follow the same pattern below
        }
        else if (ancestry == "Moonshadow Elf") {
            abilityScores[1] = 3; // 1 calls upon dexterity and 3 is the amount of bonus points given
            abilityScores[5] = 4;
        }
        else if (ancestry == "Dragonborn") {
            abilityScores[0] = 6;
            abilityScores[3] = 3;
        }
        else if (ancestry == "Gnome") {
            abilityScores[0] = 2;
            abilityScores[1] = 4;
        }
        else if (ancestry == "Shadowblood Human") {
            abilityScores[4] = 1;
            abilityScores[5] = 2;
        }
        else if (ancestry == "Aetherkin") {
            abilityScores[2] = 5;
            abilityScores[1] = 3;
        }
    }

    void printCharacter() { //print out all the characters traits!
        std::cout << "\nCharacter Traits:\n\n"; // the basic presenting line, this shows the player the title, which is character traits!
        std::cout << "Name: " << name << "\n\n"; // the characters name
        std::cout << "Ancestry: " << ancestry << "\n\n";// the characters ancestry
        std::cout << "Class: " << className << "\n\n";// the characters class 
        std::cout << "Ability Scores:\n\n";// presenting line for the characters ability scores
        // the ability scores have numbers next to them to identify them. using numbers like 0 = strength, makes strength easier to be called upon in code!! 
        std::cout << "Strength: " << abilityScores[0] << "\n"; // start at 0, not 1
        std::cout << "Dexterity: " << abilityScores[1] << "\n";
        std::cout << "Constitution: " << abilityScores[2] << "\n";
        std::cout << "Wisdom: " << abilityScores[3] << "\n";
        std::cout << "Intelligence: " << abilityScores[4] << "\n";
        std::cout << "Charisma: " << abilityScores[5] << "\n\n";
    }
};

std::string trim(const std::string& str) { //learned new tool named trim, it helps remove any leading or trailing spaces from a string, which is the users inputted name
    size_t first = str.find_first_not_of(' '); // finds the first character that is not a space
    if (first == std::string::npos) return ""; // if the first inputted character is not a space
    size_t last = str.find_last_not_of(' '); // it finds now the last character that is not a space
    return str.substr(first, last - first + 1); //finds first character that isnt a space then takes the last character before a space and subtracts it by the first then adds one. we add one because of the first character being space.
}


bool isValidName(const std::string& name) { //create function to make sure the player doesnt input a name longer than 10 characters or blank! 
    // return !name.empty() check to see if the name is empty
    // && = and, in which both must apply
    return !name.empty() && name.length() <= 10; //<= 10 or fewer
}

bool isValidScore(int score) { //create function true or false for score to make sure it works only if things are met
    return score >= 1 && score <= 18; //score must be higher than 1, and lower than 18
}

int getAbilityScore(const std::string& prompt, int remainingPoints) {

    int score; // variable to store the ability score
    while (true) { // loop to keep asking for input until the response is valid

        // prompt  = message asking the user to enter a score
        std::cout << "Enter " << prompt << " (1-18, remaining points: " << remainingPoints << "): ";
        std::cout << "Press 100 to exit.\n"; // Exit message incase the player wants to leave
        std::cin >> score; // the user inputted score then gets moved to the score variable for them!

        if (score == 100) {
            std::cout << "Exiting...\n";
            exit(0); // Exit the program if the user enters 0
        }

        // cin fail reads if the user did not input a number, isvalid score reads if its not 1 - 18, ! means not. score > means that the score is more than remaining points the player has left so it is invaild.
        if (std::cin.fail() || !isValidScore(score) || score > remainingPoints) {
            std::cin.clear(); // like assignment 1, when shown an error the code repeats endlessly. this clears the input so the player can try again
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //cin ignore like in assignment 1, it ignores all the invalid characters entered and lets the user try again
            //using \n means that the program will ignore as many characters as possible until it reaches that new line
            // use max when you want to get rid of all the bad characters entered and let the user insert a whole new try.
            // numeric limits is from the c++ standard library
            //streamsize is also from c++ standard library
            //using both numeric limits and streamsize it helps the code ignore all the characters and then stop ignoring it once the new \n is created which is a new line
            std::cout << "Invalid input! Please enter a number between 1 and 18 that does not exceed your remaining points.\n"; //cout for the user to read
        }
        else { //else statement to return the correct valid score
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //clears any extra input 
            return score; //returns the score once its valid!
        }
    }
}

std::string getAncestry() {
    std::vector<std::string> ancestries = { //list out ancestries
        "Human", "Moonshadow Elf", "Dragonborn", "Gnome","Shadowblood Humans", "Aetherkin"
    };
    std::vector<std::string> blurbs = { //created a list called blurbs since its a blurb of text i wrote regarding the ancestrys
         "\n""Good choice! Humans are adaptable and ambitious, known for their versatility." "\nYou gain +2 Strength and +2 Dexterity.\n",

        "\n""Nice pick! Elusive and graceful, Moonshadow Elves are skilled in stealth and magic.""\nYou gain +3 Dexterity and +4 Charisma \n",

        "\n""Nice one, Born of dragon blood, Dragonborn are fierce warriors.""\nYou gain +6 Strength and +3 Wisdom \n",

        "\n""Brilliant choice, Gnomes are amazing inventors and clever tricksters.""\nYou gain +2 Intelligence and +4 Charisma.\n",

        "\n""Nice! These mysterious humans are rumored to possess very ancient powers.""\nYou gain +1 Strength and +2 Dexterity.\n",

        "\n""Poweful! Aetherkin are beings of pure insane amounts of energy, often considered otherworldly.""\nYou gain +5 Constitution and +3 Dexterity.\n"
    };

    std::cout << "Select Ancestry:\n";
    int index = 1; // start at 1 for the index. The index will help print out the ancestry options above!!!
    for (const auto& ancestry : ancestries) { // the const auto like all the other codes will help look at each one of the ancestries in the vector
        std::cout << index++ << ". " << ancestry << "\n"; // this prints the current value of index, then the name of the ancestry. If the index is 1, itll print human, since human is first. index++ means itll go up for each loop, so next will be 2.
    }
    int choice; // needs to store the users choice, so a variable is made to hold it
    while (true) {
        std::cout << "Enter choice (1-" << ancestries.size() << ") or 100 to exit: "; // this shows the user that they have 1- the size of the vector which is 6 for the ancestry
        std::cin >> choice; // sends in the user input into choice

        if (choice == 100) { // wanted to have an 'exit' feature implemented a couple times throughout the code just incase
            std::cout << "Exiting...\n"; // if the cin choice is 100 then the game exits and returns 0
            exit(0);
        }

        if (choice >= 1 && choice <= ancestries.size()) { // checks if the choice is between one and 6 (the ancestries size) and makes sure the choice is above one
            std::cout << blurbs[choice - 1] << "\n";
            return ancestries[choice - 1]; // since vectors start at 0 and not one, i need to code -1 so it starts at 0 and goes down everytime to call upon the correct ancestry
        }
        else {
            std::cout << "Invalid choice. Please try again.\n"; // if invalid, shows this to the user!
        }
    }
}

std::string getClass() {
    std::vector<std::string> classes = {
        "Sorcerer", "Paladin", "Rogue", "Bard", "Ranger", "Cleric", "Artificer" // these are the classes the player can choose from, creates a list
    };
    std::vector<std::string> blurbs = { // same as before, another blurb of information to show to the player
        "\n""Harness the raw power of magic as a Sorcerer.""\n",
        "\n""A protector of the innocent, Paladins wield both sword and divine magic.""\n",
       "\n" "Insanely quick and cunning, Rogues excel in stealth and deception.""\n",
        "\n""Bards weave magic through music and stories.""\n",
        "\n""Rangers are skilled trackers and hunters.""\n",
        "\n""Clerics channel the power of their deities to heal.""\n",
        "\n""Artificers blend magic with machinery!""\n"
    };

    std::cout << "Select Class:\n"; // cout for the player to choose their class
    for (size_t i = 0; i < classes.size(); ++i) { // like above, start counting from 0, not one. runs the loop until i is less than the number of classes, and then increases 1 by one to circle through them all
        std::cout << i + 1 << ". " << classes[i] << "\n"; // prints the number and the name of each class! add one since the player should see it start at 1, not 0, but the computer starts at 0
    }

    int choice; // stores the users choice
    while (true) {
        std::cout << "Enter choice (1-" << classes.size() << "): "; // asks the user to input their choice from 1 to the valid class size (7)
        std::cin >> choice; // Get what the user inputs and stores it in choice

        if (choice == 100) { // if the users choice equals 100, then code returns 0. i chose 100 since there is no 100 the user should be typing into the console. numbers also are read instead of numbers easier
            std::cout << "Exiting...\n";
            exit(0);
        }

        if (choice >= 1 && choice <= classes.size()) { // Check if the choice is valid (between 1 and the number of classes, which is 7)
            std::cout << blurbs[choice - 1] << "\n";
            return classes[choice - 1]; // Subtract 1 because lists start at 0
        }
        else {
            std::cout << "Invalid choice. Please try again.\n"; // if invalid, shows this to the user!
        }
    }
}

int main() { // the main function, that actually makes the code work and show to the user
    Character character; // creates a variable from the type character. so we can use character name, ancestry, class name, ability scores etc! 
    char continueChoice; // needs to store whether or not the player wants to create a new player

    std::cout << "RPG Character Creator v1.0\n" << std::endl;

    do {
        std::cout << "Enter character name (max 10 characters): "; // ask the player to input their name
        std::string inputName;
        std::getline(std::cin, inputName); // get the inputted name using cin
        character.name = trim(inputName); // new tool named 'trim', it trims the "useless" spaces in the entered name! 

        while (!isValidName(character.name)) {
            std::cout << "Invalid name. Please enter a valid name (max 10 characters): "; // if name entered doesnt follow the validname guidelines set, it sends out this message
            std::getline(std::cin, inputName); // same as above, gets the inputted name using cin
            character.name = trim(inputName); // trims again like earlier once name is valid
            }

        std::cout << "\nWelcome " << character.name << ", Shape Your Destiny... \n" << std::endl; // welcome line to say hi to the player!!


    character.ancestry = getAncestry(); //get both ancestry and class for main part of code now
    character.applyAncestryBonus();
    character.className = getClass(); 

    int totalPoints = 30; // create 30 total points for the user to use! these make it so they can only use 30 total points so they must use them wisely the 6
    std::cout << "You have a total of " << totalPoints << " points to use among the 6 ability scores!\n"; //cout line of code so the user knows how much points they have

    std::string abilities[] = { "Strength", "Dexterity", "Constitution", "Wisdom", "Intelligence", "Charisma" }; // the abilityscore names
    for (int i = 0; i < 6; ++i) { // starts at i = 0, since computers read 0 as one. when i is smaller than 6 increase i by one since there is 6 abilityscores! 
        character.abilityScores[i] = getAbilityScore(abilities[i], totalPoints); // this shows the score for each ability and then the totalpoints
        totalPoints -= character.abilityScores[i]; // this deducts points from the total points after purchasing abilitypoints
        for (int i = 0; i < 6; ++i) { // same logic above to apply bonuses
            character.abilityScores[i] += character.ancestryBonus[i]; // applies the bonus
        }
    }

    character.applyAncestryBonus();

    character.printCharacter(); // prints all the characters details all at once. this shows all the character traits such as name, ancestry, class and all ability scores

    std::cout << "Generate another character? (y/n): "; // asks user if they would like to create another character before the code ends
    std::cin >> continueChoice; // the users input is then stored into continuechoice
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // using ignore like in the pervious codes and using numeric limits and streamsize max to clear anything left in the input buffer that could cause issues
    // input buffer is a place where the computer holds storage. like if i were to type hello and hit enter, the computer holds it for when later in the code it needs to be called upon
    } while (continueChoice == 'y' || continueChoice == 'Y'); // if the user inputs either lowercase or uppercase y, then the loop contuines and lets the user create their character from the beggining! 

    std::cout << "\nMay we meet again in another life traveler... \n" << std::endl; // closing line if user does not choose to continue

    return 0; //always end c++ code with return 0;
}
