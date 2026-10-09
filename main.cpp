#include <iostream>
#include <iostream>
#include <fstream>
#include <ctime>

// Given n, generate a random sequence of integers of n length from 1 to a
int randomCode(const int n, const int a)
{
    int randomSequence = 0;
    for (int i = 0; i < n; i++)
    {
        const int randomNumber = rand() % (a+1);
        randomSequence = (randomSequence * 10) + randomNumber;
    }
    return randomSequence;
}
int gameStart()
{
    std::cout << "Mastermind: A code-cracker game" << "\n\n";
    std::cout << "Enter A for default mode (5 numbers, 5 guesses)" << '\n';
    std::cout << "Enter B for customized mode (Customizable numbers/guesses)" << '\n';

    char input;
    std::cin >> input;
    std::cin.clear();

    std::ofstream logFile("log.txt");

    if (input == 'A' || input == 'a')
    {
        // Set default values in text file
        logFile << randomCode(5, 5) << '\n';
        logFile << 5 << '\n'; // Numbers in sequence range from 1 to a
        logFile << 5 << '\n'; // Guesses
        logFile << 5; // Guesses Remaining
        return 0;
    }
    if (input == 'B' || input == 'b')
    {

        int codeRange = 0;
        int codeLength = 0;
        int guesses = 0;

        //more prompts
        std::cout << "\nHow many numbers should be in the code?" << '\n';
        std::cin >> codeRange;
        std::cin.clear();

        std::cout << "How long should the code be?" << '\n';
        std::cin >> codeLength;
        std::cin.clear();

        std::cout << "How many guesses would you like to guess the code?" << '\n';
        std::cin >> guesses;
        std::cin.clear();

        // set values in text file
        logFile << randomCode(codeRange, codeLength) << '\n';
        logFile << codeLength << '\n'; // Numbers in sequence range from 1 to a
        logFile << guesses << '\n'; // Guesses
        logFile << guesses; // Guesses Remaining
        return 1;
    }
    std::cout << input;
    return -1;
}
int main()
{
    std::srand(time(0));

    int result = gameStart();

    return 0;
}