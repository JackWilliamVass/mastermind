#include <iostream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>


// TO-DO: Fix feedback logic (try entering 55555 for a guess and you'll see what i mean)
int pow(int a, int b)
{
    int result = a;
    for (int i = 0; i < b; i++)
    {
        result *= a;
    }
    return result;
}
// Grabs the character from a in position b
int grabInteger(int a, int b, int l)
{
    int big = 1;
    if (b != l) {big = pow (10, l-b-1);}
    big = a / big;
    big = big % 10;
    return big;
}
// Given userGuess - a, and generatedCode - b,
// Output a sequence of +'s and -'s with +'s displayed at the front and -'s displayed after.
// if a[i] and b[i] match, append an + to the output, else if a[i] is contained within b then append
// a -. Else, append nothing. Repeat for the full length of a
std::string getFeedback(int userGuess, int generatedCode, int codeLength)
{
    // try making a char array function that works off a pointer; as modifying a
    // array is less prone to weird errors
    std::string feedback;
    int generatedCodeCopy = 0;
    for (int i = 0; i < codeLength; i++)
    {
        int firstNum = grabInteger(userGuess, i+1, codeLength);
        int secondNum = grabInteger(generatedCode, i+1, codeLength);
        std::cout<< "second num: " << secondNum << '\n';

        if (firstNum == secondNum) {
            feedback.append("+");
        }
        else {
            std::cout << "Comparing " << firstNum << " and " << secondNum << '\n';
            generatedCodeCopy = (generatedCodeCopy * 10) + secondNum;
        }
    }
    std::cout << generatedCodeCopy << '\n';

    // Compare generatedCodeCopy and userGuess for -
    // Then sort the string in place to place the + first and the - second
    return feedback;
}
// Core repeating game logic; input is taken from log.txt
int startRound()
{
    // Grab relevant round information from log.txt
    std::ifstream file("./log.txt");
    if (!file.is_open())
    {
        std::cout << "File didn't open successfully" << '\n';
    }
    int generatedCode, codeLength, guesses, guessesRemaining;
    std::vector<std::string> previousGuesses;
    std::string guess;

    file >> generatedCode >> codeLength >> guesses >> guessesRemaining;
    while (std::getline(file, guess))
    {
        previousGuesses.push_back(guess);
    }

    file.close();

    // Display relevant round information
    std::cout << "\nMASTERMIND" << '\n';
    std::cout << "Guesses remaining: " << guessesRemaining << "/" << guesses << '\n';
    std::cout << "\nPrevious guesses: " << '\n';
    for (const std::string previousGuess : previousGuesses)
    {
        std::cout << previousGuess << '\n';
    }
    //
    // Input code guess
    int userGuess = 0;
    std::cout << "Enter your guess: ";
    std::cin >> userGuess;
    std::cin.clear();

    // Game over/Win logic
    if (userGuess == generatedCode)
    {
        //GameWin();
        std::cout << "You've won!" << '\n';
        //gameRestart();
        return 0;
    }
    if (userGuess != generatedCode && guessesRemaining == 1)
    {
        //GameOver();
        std::cout << "Game Over!" << '\n';
        //gameRestart();
        return 0;
    }
    // Update log.txt
    std::string feedback = "ROUND "+std::to_string(guesses-guessesRemaining)+": " + getFeedback(userGuess, generatedCode, codeLength);
    previousGuesses.push_back(feedback);
    guessesRemaining -= 1;

    std::ofstream logFile("log.txt");

    logFile << generatedCode << '\n';
    logFile << codeLength << '\n'; // Numbers in sequence range from 1 to a
    logFile << guesses << '\n'; // Guesses
    logFile << guessesRemaining; // Guesses Remaining

    for (const std::string tempIter : previousGuesses)
    {
        logFile << tempIter << '\n';
    }

    logFile.close();
    startRound();
    return 0;
}
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
// Prompt and save details required prior to game start
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
        logFile << 5 << '\n'; // Guesses Remaining

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

    }
    logFile.close();
    startRound();
    return 1;
}
int main()
{
    std::srand(time(0));

    int result = gameStart();


    //std::cout << pow(10, 5) << '\n';
    //std::cout << 12344 / (pow(10, 5-5)) % 10 << '\n';
    //std::cout << grabInteger(12344,5,5) << '\n';

    return 0;
}