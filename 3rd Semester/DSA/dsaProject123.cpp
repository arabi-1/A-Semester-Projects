#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
using namespace std;

//User classs
class User {
public:
    string username;
    string password;
    vector<int> bookingPNRs;//to book passenger name records(pnr)

    User() {}
    User(string uname, string pass) {
        username = uname;
        password = pass;
    }

    void viewBookings() {
        cout << "Bookings of " << username << ":\n";
        for (int pnr : bookingPNRs) {//iterate over the bookingPNRs vector, each element is given a name pnr
            cout << "PNR: " << pnr << endl;
        }
    }
};

// Booking class 
class Booking {
public:
    int pnr;
    string username;
    int trainID;
    int seatNumber;
    string bookingDate;

    Booking() {}

    Booking(int p, string uname, int tID, int seat, string date) {
        pnr = p;
        username = uname;
        trainID = tID;
        seatNumber = seat;
        bookingDate = date;
    }

    void printSummary() {
        cout << "PNR: " << pnr << ", User: " << username
             << ", Train ID: " << trainID << ", Seat: " << seatNumber
             << ", Date: " << bookingDate << endl;
    }
};

// Train class 
class Train {
public:
    int trainID;
    string trainName;
    string source;
    string destination;
    string date;
    int totalSeats;
    vector<bool> seats;

    Train() {}

    Train(int id, string name, string src, string dest, string d, int seatCount) {
        trainID = id;
        trainName = name;
        source = src;
        destination = dest;
        date = d;
        totalSeats = seatCount;
        seats = vector<bool>(seatCount, false);
    }
    //method to show the number of available seats in the Train
    void showAvailability() {
        cout << "Available seats in Train " << trainID << " (" << trainName << "): ";
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    //method to book a seat
    bool bookSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats)
            return false;
        if (seats[seatNumber - 1])//here we check if the seat is booked, if no, fasle is returned
            return false;
        seats[seatNumber - 1] = true;//means seat is booked
        return true;
    }

    void cancelSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats) {
            seats[seatNumber - 1] = false;//unbooked the booked seat
        }
    }
};

// here a stack is made, with generic nature 
template<typename T>
class MyStack {
private:
    int capacity;
    int topIndex;
    T* arr;

public:
    MyStack(int size = 100) {
        capacity = size;
        topIndex = -1;
        arr = new T[capacity];
    }

    ~MyStack() {
        delete[] arr;
    }

    void push(T value) {
        if (topIndex >= capacity - 1) {
            cout << "Stack overflow\n";
            return;
        }
        arr[++topIndex] = value;
    }

    void pop() {
        if (topIndex < 0) {
            cout << "Stack underflow\n";
            return;
        }
        topIndex--;
    }

    T top() {
        if (topIndex < 0) {
            throw out_of_range("Stack is empty");
        }
        return arr[topIndex];
    }

    bool empty() {
        return topIndex == -1;
    }

    int size() {
        return topIndex + 1;
    }
};

// BookingManager class 
class BookingManager {
private:
    static int currentPNR;
    unordered_map<int, Booking> allBookings;//key is of type int, and value is of type Bookings O(1)
    MyStack<int> bookingHistory;

public:
    BookingManager() {}
    //method to book a ticket
    int bookTicket(string username, int trainID, int seatNumber, string date) {
        int pnr = ++currentPNR;
        Booking newBooking(pnr, username, trainID, seatNumber, date);
        allBookings[pnr] = newBooking;
        bookingHistory.push(pnr);
        cout << "Ticket booked successfully. PNR: " << pnr << endl;
        return pnr;
    }
    // ethod to cancel a ticket
    void cancelTicket(int pnr) {
        if (allBookings.find(pnr) != allBookings.end()) {
            allBookings.erase(pnr);
            cout << "Booking with PNR " << pnr << " has been cancelled.\n";
        } else {
            cout << "Invalid PNR. No such booking found.\n";
        }
    }

    void printBooking(int pnr) {
        if (allBookings.find(pnr) != allBookings.end()) {
            allBookings[pnr].printSummary();
        } else {
            cout << "No booking found for PNR: " << pnr << endl;
        }
    }

    void showRecentBookings(int count = 5) {
        cout << "Recent " << count << " bookings:\n";
        MyStack<int> tempStack;
        int shown = 0;

        while (!bookingHistory.empty() && shown < count) {
            int recentPNR = bookingHistory.top();
            bookingHistory.pop();
            printBooking(recentPNR);
            tempStack.push(recentPNR);
            shown++;
        }

        while (!tempStack.empty()) {//stores the original order of the booking history stack after displaying the recent bookings
            bookingHistory.push(tempStack.top());
            tempStack.pop();
        }
    }
};

int BookingManager::currentPNR = 1000;//a static variable declared outside the class, because it is independent of instances

//Here a linkedlist is made, for managing trains
class TrainNode {
public:
    Train train;
    TrainNode* next;

    TrainNode(Train t) {
        train = t;
        next = nullptr;
    }
};
//this class mamanges the train linkedlist
class TrainLinkedList {
private:
    TrainNode* head;
public:
    TrainLinkedList() {
        head = nullptr;
    }

    void addTrain(Train t) {
        TrainNode* newNode = new TrainNode(t);
        if (!head) {
            head = newNode;
        } else {
            TrainNode* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void searchTrains(const string& source, const string& destination, const string& date) {
        TrainNode* temp = head;
        bool found = false;
        cout << "Available trains from " << source << " to " << destination << " on " << date << ":\n";
        while (temp) {
            if (temp->train.source == source && temp->train.destination == destination && temp->train.date == date) {
                cout << "Train ID: " << temp->train.trainID << ", Name: " << temp->train.trainName << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "No trains found.\n";
        }
    }

    void displayAllTrains() {
        TrainNode* temp = head;
        while (temp) {
            cout << "Train ID: " << temp->train.trainID
                 << ", Name: " << temp->train.trainName
                 << ", From: " << temp->train.source
                 << ", To: " << temp->train.destination
                 << ", Date: " << temp->train.date << endl;
            temp = temp->next;
        }
    }

    Train* getTrainByID(int id) {//searches for a train with the given id, if found then a pointer to that train object is returned, else return nullptr
        TrainNode* temp = head;
        while (temp) {
            if (temp->train.trainID == id) {
                return &(temp->train);
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

//Train manager class 
class TrainManager {
private:
    TrainLinkedList trainList;
public:
    void addTrain(const Train& t) {
        trainList.addTrain(t);
    }

    void searchTrains(const string& source, const string& destination, const string& date) {//the ampersand here means that the reference to orginical string is passed and const makes sure that the string may not be modified
        trainList.searchTrains(source, destination, date);
    }

    void listAllTrains() {
        trainList.displayAllTrains();
    }

    Train* getTrain(int trainID) {
        return trainList.getTrainByID(trainID);
    }
};

//Custom queue 
template<typename T>
class MyQueue {
private:
    int frontIndex, rearIndex, capacity;
    T* arr;//pointer to a dynamic array of type T

public:
    MyQueue(int size = 100) {
        capacity = size;
        arr = new T[capacity];//an array of type T is made
        frontIndex = 0;
        rearIndex = -1;
    }

    ~MyQueue() {
        delete[] arr;
    }

    void enqueue(T value) {
        if (rearIndex >= capacity - 1) {//checks if the queue has reached maximum size
            cout << "Queue Overflow!\n";
            return;
        }
        arr[++rearIndex] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow!\n";
            return;
        }
        frontIndex++;
    }

    T front() {
        if (!isEmpty()) {
            return arr[frontIndex];
        }
        throw out_of_range("Queue is empty");//if queue is empty, exception is thrown
    }

    bool isEmpty() {
        return frontIndex > rearIndex;
    }

    int size() {
        return rearIndex - frontIndex + 1;
    }
};

//User Manager 
class UserManager {
private:
    unordered_map<string, User> users;
    MyQueue<User> registrationQueue;

public:
    void registerUser(string username, string password) {
        if (users.find(username) != users.end()) {
            cout << "Username already exists. Choose another.\n";
            return;
        }

        User newUser(username, password);
        users[username] = newUser;
        registrationQueue.enqueue(newUser);

        cout << "Registration successful. Welcome, " << username << "!\n";
    }

    bool loginUser(string username, string password) {
        if (users.find(username) == users.end()) {
            cout << "User not found.\n";
            return false;
        }
        if (users[username].password != password) {
            cout << "Incorrect password.\n";
            return false;
        }

        cout << "Login successful. Welcome back, " << username << "!\n";
        return true;
    }

    void showRegistrationQueue() {
        MyQueue<User> tempQueue = registrationQueue;
        cout << "Users in Registration Queue:\n";
        while (!tempQueue.isEmpty()) {
            User u = tempQueue.front();
            cout << "User: " << u.username << "\n";
            tempQueue.dequeue();
        }
    }

    User* getUser(string username) {
        if (users.find(username) != users.end()) {
            return &users[username];
        }
        return nullptr;
    }
};

// Main function
#include <iostream>
using namespace std;



int main() {
    BookingManager bookingManager;
    TrainManager trainManager;
    UserManager userManager;
    MyQueue<User*> userQueue;  // Queue of pointers to avoid data loss

    // Register and login user
    userManager.registerUser("Mohammad", "12345");
    userManager.loginUser("Mohammad", "12345");

    // here registration queue is shown
    userManager.showRegistrationQueue();

    // Enqueue users from UserManager
    User* user = userManager.getUser("Mohammad");
    if (user != nullptr) {
        userQueue.enqueue(user);
    }

    // Add Trains
    trainManager.addTrain(Train(101, "Greenline", "Peshawar", "Karachi", "2025-06-01", 10));
    trainManager.addTrain(Train(102, "JaffarExpress", "Lahore", "Peshawar", "2025-06-02", 8));
    trainManager.addTrain(Train(103, "KarachiExpress", "Lahore", "Karachi", "2025-06-20", 15));

    // Display All Trains
    cout << "\nHere is the list of All Trains\n";
    trainManager.listAllTrains();

    // Process each user
    while (!userQueue.isEmpty()) {
        User* currentUser = userQueue.front();
        userQueue.dequeue();

        cout << "\nProcessing user: " << currentUser->username << endl;

        cout << "\nSearching trains from Lahore to Karachi on 2025-06-20:\n";
        trainManager.searchTrains("Lahore", "Karachi", "2025-06-20");

        // Booking a ticket
        Train* selectedTrain = trainManager.getTrain(103);
        int seatNumber = 5;

        if (selectedTrain != nullptr) {
            selectedTrain->showAvailability();

            if (selectedTrain->bookSeat(seatNumber)) {
                int pnr = bookingManager.bookTicket(currentUser->username, 103, seatNumber, "2025-06-20");
                currentUser->bookingPNRs.push_back(pnr);
                cout << "Booked seat " << seatNumber << " with PNR: " << pnr << endl;
            } else {
                cout << "Seat " << seatNumber << " already booked.\n";
            }

            // Optional second booking 
            int secondSeat = 6;
            if (selectedTrain->bookSeat(secondSeat)) {
                int newPNR = bookingManager.bookTicket(currentUser->username, 103, secondSeat, "2025-06-20");
                currentUser->bookingPNRs.push_back(newPNR);
                cout << "Second booking successful. PNR: " << newPNR << " for seat " << secondSeat << endl;
            }
        }

        // Show bookings
        currentUser->viewBookings();

        // we will ask if user wants to cancel
        char choice;
        cout << "\nDo you want to cancel any of your bookings? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (!currentUser->bookingPNRs.empty()) {
                cout << "Here are your PNRs:\n";
                for (int i = 0; i < currentUser->bookingPNRs.size(); ++i) {
                    cout << i + 1 << ". PNR: " << currentUser->bookingPNRs[i] << endl;
                }

                cout << "Enter the number of the booking you want to cancel: ";
                int cancelIndex;
                cin >> cancelIndex;

                if (cancelIndex >= 1 && cancelIndex <= currentUser->bookingPNRs.size()) {
                    int cancelPNR = currentUser->bookingPNRs[cancelIndex - 1];
                    bookingManager.cancelTicket(cancelPNR);
                    
                    // Cancel seat in the Train as well
                    
                    
                    selectedTrain->cancelSeat(seatNumber); 

                    // Remove PNR from vector
                    currentUser->bookingPNRs.erase(currentUser->bookingPNRs.begin() + cancelIndex - 1);
                    cout << "Cancelled booking with PNR: " << cancelPNR << endl;
                } else {
                    cout << "Invalid selection.\n";
                }
            } else {
                cout << "No bookings to cancel.\n";
            }
        }
    }

    return 0;
}
