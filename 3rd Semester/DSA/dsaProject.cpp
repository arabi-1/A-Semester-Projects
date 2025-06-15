#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
using namespace std;

// -------------------- User Class --------------------
class User {
public:
    string username;
    string password;
    vector<int> bookingPNRs;

    User() {}
    User(string uname, string pass) {
        username = uname;
        password = pass;
    }

    void viewBookings() {
        cout << "Bookings of " << username << ":\n";
        for (int pnr : bookingPNRs) {
            cout << "PNR: " << pnr << endl;
        }
    }
};

// -------------------- Booking Class --------------------
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

// -------------------- Train Class --------------------
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

    void showAvailability() {
        cout << "Available seats in Train " << trainID << " (" << trainName << "): ";
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }

    bool bookSeat(int seatNumber) {
        if (seatNumber < 1 || seatNumber > totalSeats)
            return false;
        if (seats[seatNumber - 1])
            return false;
        seats[seatNumber - 1] = true;
        return true;
    }

    void cancelSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats) {
            seats[seatNumber - 1] = false;
        }
    }
};

// -------------------- Custom Stack --------------------
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

// -------------------- BookingManager Class --------------------
class BookingManager {
private:
    static int currentPNR;
    unordered_map<int, Booking> allBookings;
    MyStack<int> bookingHistory;

public:
    BookingManager() {}

    int bookTicket(string username, int trainID, int seatNumber, string date) {
        int pnr = ++currentPNR;
        Booking newBooking(pnr, username, trainID, seatNumber, date);
        allBookings[pnr] = newBooking;
        bookingHistory.push(pnr);
        cout << "Ticket booked successfully. PNR: " << pnr << endl;
        return pnr;
    }

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

        while (!tempStack.empty()) {
            bookingHistory.push(tempStack.top());
            tempStack.pop();
        }
    }
};

int BookingManager::currentPNR = 1000;

// -------------------- Linked List for Trains --------------------
class TrainNode {
public:
    Train train;
    TrainNode* next;

    TrainNode(Train t) {
        train = t;
        next = nullptr;
    }
};

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

    Train* getTrainByID(int id) {
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

// -------------------- Train Manager --------------------
class TrainManager {
private:
    TrainLinkedList trainList;
public:
    void addTrain(const Train& t) {
        trainList.addTrain(t);
    }

    void searchTrains(const string& source, const string& destination, const string& date) {
        trainList.searchTrains(source, destination, date);
    }

    void listAllTrains() {
        trainList.displayAllTrains();
    }

    Train* getTrain(int trainID) {
        return trainList.getTrainByID(trainID);
    }
};

// -------------------- Custom Queue --------------------
template<typename T>
class MyQueue {
private:
    int frontIndex, rearIndex, capacity;
    T* arr;

public:
    MyQueue(int size = 100) {
        capacity = size;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
    }

    ~MyQueue() {
        delete[] arr;
    }

    void enqueue(T value) {
        if (rearIndex >= capacity - 1) {
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
        throw out_of_range("Queue is empty");
    }

    bool isEmpty() {
        return frontIndex > rearIndex;
    }

    int size() {
        return rearIndex - frontIndex + 1;
    }
};

// -------------------- User Manager --------------------
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

// -------------------- Main --------------------
int main() {
    BookingManager bookingManager;
    TrainManager trainManager;
    MyQueue<User> userQueue;

    userQueue.enqueue(User("Mohammad", "12345"));
    // userQueue.enqueue(User("Arabi", "pass456"));

    Train t1(101, "Greenline ", " Lahore ", " Karachi ", " 2025-06-20", 10);
    Train t2(102, "JaffarExpress ", " Lahore ", " Quetta ", " 2025-06-21 ", 8);
    trainManager.addTrain(t1);
    trainManager.addTrain(t2);

    while (!userQueue.isEmpty()) {
        User currentUser = userQueue.front();
        userQueue.dequeue();

        cout << "\nProcessing user: " << currentUser.username << endl;

        cout << "\nAvailable Trains:\n";
        trainManager.listAllTrains();

        cout << "\nSearching trains from Lahore to Karachi on 2025-06-20:\n";
        trainManager.searchTrains("Lahore", "Karachi", "2025-06-20");

        Train* selectedTrain = trainManager.getTrain(101);

        if (selectedTrain != nullptr) {
            selectedTrain->showAvailability();

            int seatNumber = 2;
            if (selectedTrain->bookSeat(seatNumber)) {
                int pnr = bookingManager.bookTicket(currentUser.username, 101, seatNumber, "2025-06-20");
                currentUser.bookingPNRs.push_back(pnr);
            } else {
                cout << "Seat not available.\n";
            }
        }

        currentUser.viewBookings();

        bookingManager.showRecentBookings();
    }

    return 0;
}
