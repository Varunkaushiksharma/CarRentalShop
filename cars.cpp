#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
using namespace std;

void rentACar();
void returnACar();
void sellACar();
string genrateInvoice(string carName, double rate, int hour);
void details();
void cars();
void mainMenu();

// Customer details
string name, mob, address;
int age;

void details()
{

  cout << "Enter your personal details to rent a car:" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  ofstream fin;
  fin.open("userdetails.txt", ios::app);

  cout << "Enter your Name: ";
  getline(cin, name);

  cout << "Enter your mobile number: ";
  getline(cin, mob);

  cout << "Enter your age: ";
  cin >> age;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Enter your address: ";
  getline(cin, address);

  if (fin.is_open())
  {
    // Save all details in a structured way (for readability)
    fin << "Name: " << name << ", Mobile: " << mob << ", Age: " << age << ", Address: " << address << endl;
    fin.close(); // Close the file after writing
    cout << "Sign up completed! \n";
  }
  else
  {
    cout << "Failed to sign up" << endl;
  }

  cout << "Thanks, " << name << "! Your details have been successfully entered!" << endl;
}
string trim(const string &str)
{
  size_t start = str.find_first_not_of(" \t");
  size_t end = str.find_last_not_of(" \t");
  return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to simulate user login
bool login(string inputName, string inputMob)
{
  string fileLine, storedName, storedMob;
  ifstream fin("userdetails.txt");

  if (fin.is_open())
  {
    while (getline(fin, fileLine))
    {
      // Split the line at commas and extract Name and Mobile
      size_t namePos = fileLine.find("Name: ");
      size_t mobPos = fileLine.find("Mobile: ");

      if (namePos != string::npos && mobPos != string::npos)
      {
        // Extract name (trim spaces before and after)
        storedName = fileLine.substr(namePos + 6, mobPos - (namePos + 8)); // Adjusted substring extraction
        storedMob = fileLine.substr(mobPos + 8, 10);                       // Mobile is 10 digits long

        // Trim spaces from extracted data and input before comparing
        storedName = trim(storedName);
        storedMob = trim(storedMob);
        inputName = trim(inputName);
        inputMob = trim(inputMob);

        // Compare trimmed values
        if (storedName == inputName && storedMob == inputMob)
        {
          fin.close();
          return true; // User is authenticated
        }
      }
    }
    fin.close();
  }

  return false; // User not found or incorrect details
}

void cars()
{
  cout << "********************************" << endl;
  cout << "******Cars Available************" << endl;

  int car;
  cout << "  Cars      ->     Rent Per Hour" << endl;
  cout << " 1. Skoda       ->     $40" << endl;
  cout << " 2. Swift       ->     $30" << endl;
  cout << " 3. Nano        ->     $15" << endl;
  cout << " 4. Alto        ->     $20" << endl;
  cout << " 5. Bugatti     ->     $130" << endl;
  cout << " 6. Lamborghini ->     $90" << endl;
  cout << " 7. Seltos       ->     $10" << endl;
  cout << "Choose which one you would like to rent: ";
  cin >> car;

  string carName;
  int rate;
  switch (car)
  {
  case 1:
    carName = "Skoda";
    rate = 40;
    break;
  case 2:
    carName = "Swift";
    rate = 30;
    break;
  case 3:
    carName = "Nano";
    rate = 15;
    break;
  case 4:
    carName = "Alto";
    rate = 20;
    break;
  case 5:
    carName = "Bugatti";
    rate = 130;
    break;
  case 6:
    carName = "Lamborghini";
    rate = 90;
    break;
  case 7:
    carName = "Seltos";
    rate = 10;
    break;
  default:
    cout << "Invalid selection. Please choose a valid car." << endl;
    return;
  }

  int hours;
  cout << "For how many hours would you like to rent the " << carName << "? ";
  cin >> hours;

  // Generate invoice string
  string invoice = genrateInvoice(carName, rate, hours);
  cout << "Total amount to pay:" << invoice << endl;
  // Write invoice to file
  ofstream fin;
  fin.open("userdetails.txt", ios::app);
  if (fin.is_open())
  {
    fin << name << " total amount to pay: " << invoice << endl;
    fin.close();
  }
  else
  {
    cout << "Error opening file." << endl;
  }
}
string genrateInvoice(string carName, double rate, int hour)
{
  double result = hour * rate;
  ostringstream oss;
  oss << "Car: " << carName << ", Hours: " << hour << ", Rate: " << rate << ", Total: $2 " << result;

  return oss.str();
}
void mainMenu()
{
  int choice;
  do
  {
    cout << "\nWelcome to our Shop" << endl;
    cout << "What would you like to do?" << endl;
    cout << "\n1. Rent A Car\n2. Return A Car\n3. Sell Your Car\n4. Exit\n"
         << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      rentACar();
      break;
    case 2:
      returnACar();
      break;
    case 3:
      sellACar();
      break;
    case 4:
      exit(EXIT_SUCCESS);
      break;
    default:
      cout << "Invalid input. Please enter a valid choice." << endl;
    }
  } while (choice != 4);
}

void rentACar()
{
  details();
  cars();
  cout << "Our terms and services:" << endl;
  cout << "1. You need to pay one hour rent in advance and we deliver the car at your address." << endl;
  cout << "2. You can take a car for a whole day or week; you just need to pay for that." << endl;
  cout << "3. You are responsible for any physical damage and need to pay for it." << endl;
  cout << "4. Return the car through our website where you booked it; we'll take the car from your address." << endl;

  int choice;
  cout << "1. Main Menu\n2. Exit\n";
  cin >> choice;
  switch (choice)
  {
  case 1:
    mainMenu();
    break;
  case 2:
    exit(EXIT_SUCCESS);
    break;
  default:
    cout << "Invalid input. Returning to main menu." << endl;
  }
}

void returnACar()
{
  cout << "Ok, you want to return a car that you rented:" << endl;
  string inputName, inputMobile;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // Use getline() to allow spaces in the name
  cout << "Enter your name: ";
  getline(cin, inputName); // Using getline instead of cin >> for full name

  // Use getline() to capture full mobile number (in case of spaces or formatting issues)
  cout << "Enter your mobile number: ";
  getline(cin, inputMobile); // Using getline for mobile number as well

  // Call the login function to check if the user exists
  if (login(inputName, inputMobile))
  {
    cout << "Login successfully! Now you can return the car." << endl;
    ifstream fin;
    fin.open("userdetails.txt");
    if (!fin)
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }
    string line;
    double totalAmount = 0.0;
    while (getline(fin, line))
    {
      if (line.find("Total: ") != string::npos)
      {
        stringstream ss(line);
        string temp;
        double amount;

        while (ss >> temp)
        {
          if (temp == "Total:")
          {
            if (ss >> amount) // Try to extract the number after "Total:"
            {
              totalAmount += amount;
            }
            break;
          }
        }
      }
    }
    fin.close();
    cout << "Your total amount is: $ " << totalAmount << endl;
  }
  else
  {
    cout << "Invalid name or mobile number! Please try again." << endl;
  }

  int choice;
  cout << "1. Main Menu\n2. Exit\n";
  cin >> choice;
  switch (choice)
  {
  case 1:
    mainMenu();
    break;
  case 2:
    exit(EXIT_SUCCESS);
    break;
  default:
    cout << "Invalid input. Returning to main menu." << endl;
  }
}

void sellACar()
{
  string model, type, condition, service, accident, selling, agree;
  int year, miles, owner, askingPrice, offerPrice;

  cout << "You want to sell the car !" << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  cout << "Enter the make and model of your car: ";
  getline(cin, model);

  cout << "Which year was the car manufactured: ";
  cin >> year;

  cout << "How many kilometers/miles has the car been driven: ";
  cin >> miles;

  // Clear the input buffer before the next getline (after numeric input)
  cin.ignore();

  cout << "What is the fuel type (e.g., Petrol, Diesel, CNG, Electric, Hybrid): ";
  getline(cin, type);

  cout << "What is the condition of the car (e.g., Excellent, Normal, Good, Fair, New, Used): ";
  getline(cin, condition);

  cout << "How many previous owners has the car had: ";
  cin >> owner;

  cout << "What is your asking price: ";
  cin >> askingPrice;

  // Clear the input buffer before the next getline (after numeric input)
  cin.ignore();

  cout << "Has the car been in any accidents (yes/no)? If yes, describe the damage: ";
  getline(cin, accident);

  cout << "Does the car have a full service history (yes/no)? ";
  getline(cin, service);

  cout << "Why are you selling the car: ";
  getline(cin, selling);
  // File handling for logging car sale details
  ofstream file("car_sales.txt", ios::app);
  if (file.is_open())
  {
    file << "Model: " << model << "\n";
    file << "Year: " << year << "\n";
    file << "Mileage: " << miles << " km\n";
    file << "Fuel Type: " << type << "\n";
    file << "Condition: " << condition << "\n";
    file << "Asking Price: $" << askingPrice << "\n";
    file << "Final Offer: $" << offerPrice << endl;
    file << "Negotiation Result: " << (agree == "yes" ? "Accepted" : "Declined") << "\n\n";
    file.close();
  }
  else
  {
    cout << "Error opening file for saving sales data." << endl;
  }

  cout << "We see the condition of your car " << endl;
  offerPrice = askingPrice - (askingPrice / 10);
  cout << "We offer you " << offerPrice << endl;
  cout << "You agree with this (yes/no)" << endl;
  getline(cin, agree);
  while (agree != "yes" && agree != "no")
  {
    cout << "Please respond with 'yes' or 'no': ";
    getline(cin, agree);
  }
  // Loop for negotiation rounds
  int round = 1;
  while (agree == "no" && round <= 3) // Ensure up to 3 rounds
  {
    if (round == 1)
      offerPrice = askingPrice - (askingPrice / 9);
    else if (round == 2)
      offerPrice = askingPrice - (askingPrice / 8.5);
    else if (round == 3)
      offerPrice = askingPrice - (askingPrice / 8); // Third round adjustment

    cout << "We offer you $" << offerPrice << ". Do you agree with this? (yes/no): ";
    getline(cin, agree);

    // Ensure valid response
    while (agree != "yes" && agree != "no")
    {
      cout << "Please respond with 'yes' or 'no': ";
      getline(cin, agree);
    }

    round++;
  }

  int choice;
  cout << "\n 1.MainMenu \n 2.Exit. \n";
  cin >> choice;
  if (choice == 1)
  {
    mainMenu();
  }
  else if (choice == 2)
  {
    exit(EXIT_SUCCESS);
  }
  else
  {
    cout << "enter vaild input:" << endl;
  }
}

int main()
{
  cout << "***********************" << endl;
  cout << "Forever Car Rental Shop" << endl;
  cout << "***********************" << endl;
  mainMenu();
  return 0;
}
