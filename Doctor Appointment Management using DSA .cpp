#include <iostream>
#include <string>
using namespace std;

#define MAX_APPOINTMENTS 100
#define DOCTOR_COUNT 4
#define SURGEON_COUNT 4
#define SLOTS_PER_DAY 10

struct Node {
    string data;
    Node* next;

    Node(string d) : data(d), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void append(string data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void remove(string data) {
        if (head == nullptr) return;
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != data) {
            temp = temp->next;
        }
        if (temp->next == nullptr) return;
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class Queue {
public:
    Node* front;
    Node* rear;

    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(string data) {
        Node* newNode = new Node(data);
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    void dequeue() {
        if (front == nullptr) return;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    string getFront() {
        if (front == nullptr) return "";
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void display() {
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool contains(string data) {
        Node* temp = front;
        while (temp != nullptr) {
            if (temp->data == data) return true;
            temp = temp->next;
        }
        return false;
    }

    void remove(string data) {
        if (front == nullptr) return;
        if (front->data == data) {
            Node* temp = front;
            front = front->next;
            if (front == nullptr) rear = nullptr;
            delete temp;
            return;
        }
        Node* temp = front;
        while (temp->next != nullptr && temp->next->data != data) {
            temp = temp->next;
        }
        if (temp->next == nullptr) return;
        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        if (nodeToDelete == rear) rear = temp;
        delete nodeToDelete;
    }
};

struct BSTNode {
    string name;
    int triageLevel;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string n, int t) : name(n), triageLevel(t), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, string name, int triageLevel) {
        if (node == nullptr) return new BSTNode(name, triageLevel);
        if (triageLevel < node->triageLevel)
            node->left = insert(node->left, name, triageLevel);
        else
            node->right = insert(node->right, name, triageLevel);
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    BSTNode* remove(BSTNode* node, int triageLevel) {
        if (node == nullptr) return node;
        if (triageLevel < node->triageLevel)
            node->left = remove(node->left, triageLevel);
        else if (triageLevel > node->triageLevel)
            node->right = remove(node->right, triageLevel);
        else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = findMin(node->right);
            node->name = temp->name;
            node->triageLevel = temp->triageLevel;
            node->right = remove(node->right, temp->triageLevel);
        }
        return node;
    }

    void inorder(BSTNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << "Patient: " << node->name << ", Triage Level: " << node->triageLevel << endl;
        inorder(node->right);
    }

    BST() : root(nullptr) {}

    void insert(string name, int triageLevel) {
        root = insert(root, name, triageLevel);
    }

    void remove(int triageLevel) {
        root = remove(root, triageLevel);
    }

    BSTNode* getRoot() {
        return root;
    }

    void display() {
        inorder(root);
    }
};

class AppointmentManagement {
public:
    Queue* appointments[MAX_APPOINTMENTS];

    AppointmentManagement() {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            appointments[i] = new Queue();
        }
    }

    bool isSlotAvailable(string doctorName, string time) {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = appointments[i]->front;
            while (temp != nullptr) {
                if (temp->data.find("Doctor: " + doctorName) != string::npos && temp->data.find("Time: " + time) != string::npos) {
                    return false;
                }
                temp = temp->next;
            }
        }
        return true;
    }

    void bookAppointment(string patientName, string doctorName, string time) {
        if (!isSlotAvailable(doctorName, time)) {
            cout << "This slot is already booked for " << doctorName << " at " << time << endl;
            return;
        }

        string appointment = "Patient: " + patientName + ", Doctor: " + doctorName + ", Time: " + time;
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            if (appointments[i]->isEmpty() || appointments[i]->getFront().find(doctorName) != string::npos) {
                appointments[i]->enqueue(appointment);
                cout << "Your appointment is booked: " << appointment << endl;
                return;
            }
        }
        cout << "No available slots for " << doctorName << " at " << time << endl;
    }

    void updateAppointmentStatus(string doctorName, string patientName, bool isCompleted) {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = appointments[i]->front;
            while (temp != nullptr) {
                if (temp->data.find(doctorName) != string::npos && temp->data.find(patientName) != string::npos) {
                    temp->data += ", Status: " + string(isCompleted ? "Completed" : "Pending");
                    return;
                }
                temp = temp->next;
            }
        }
    }

    void cancelAppointment(string doctorName, string patientName) {
        string appointmentPrefix = "Patient: " + patientName + ", Doctor: " + doctorName;
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = appointments[i]->front;
            Node* prev = nullptr;
            while (temp != nullptr) {
                if (temp->data.find(appointmentPrefix) != string::npos) {
                    if (prev == nullptr) {
                        appointments[i]->dequeue();
                    } else {
                        prev->next = temp->next;
                        if (temp == appointments[i]->rear) {
                            appointments[i]->rear = prev;
                        }
                        delete temp;
                    }
                    cout << "Appointment cancelled: " << appointmentPrefix << endl;
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
        }
        cout << "Appointment not found: " << appointmentPrefix << endl;
    }

    void showAppointments(string doctorName) {
        bool found = false;
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = appointments[i]->front;
            while (temp != nullptr) {
                if (temp->data.find(doctorName) != string::npos) {
                    cout << temp->data << endl;
                    found = true;
                }
                temp = temp->next;
            }
        }
        if (!found) {
            cout << "No appointments for " << doctorName << endl;
        }
    }
};

class SurgeryScheduling {
public:
    LinkedList* schedules[MAX_APPOINTMENTS];

    SurgeryScheduling() {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            schedules[i] = new LinkedList();
        }
    }

    bool isSlotAvailable(string operatingRoom, string time) {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = schedules[i]->head;
            while (temp != nullptr) {
                if (temp->data.find("Room: " + operatingRoom) != string::npos && temp->data.find("Time: " + time) != string::npos) {
                    return false;
                }
                temp = temp->next;
            }
        }
        return true;
    }

    void scheduleSurgery(string patientName, string surgeryType, string time, string operatingRoom) {
        if (!isSlotAvailable(operatingRoom, time)) {
            cout << "This slot is already booked for operating room " << operatingRoom << " at " << time << endl;
            return;
        }

        string surgery = "Patient: " + patientName + ", Surgery: " + surgeryType + ", Time: " + time + ", Room: " + operatingRoom;
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            if (schedules[i]->head == nullptr || schedules[i]->head->data.find(operatingRoom) != string::npos) {
                schedules[i]->append(surgery);
                cout << "Your surgery is booked: " << surgery << endl;
                return;
            }
        }
        cout << "No available slots for operating room " << operatingRoom << " at " << time << endl;
    }

    void showSurgeries(string operatingRoom) {
        bool found = false;
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            Node* temp = schedules[i]->head;
            while (temp != nullptr) {
                if (temp->data.find(operatingRoom) != string::npos) {
                    cout << temp->data << endl;
                    found = true;
                }
                temp = temp->next;
            }
        }
        if (!found) {
            cout << "No surgeries for operating room " << operatingRoom << endl;
        }
    }
};

int main() {
    AppointmentManagement apptMgr;
    BST emergencyCare;
    SurgeryScheduling surgerySched;

    const string doctors[DOCTOR_COUNT] = { "Dr. Huzaifa", "Dr. Umer", "Dr. Fiza", "Dr. Ali" };
    const string doctorSlots[SLOTS_PER_DAY] = { "09:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "01:00 PM", "02:00 PM", "03:00 PM", "04:00 PM", "05:00 PM", "06:00 PM" };

    const string surgeons[SURGEON_COUNT] = { "Dr. Fiza", "Dr. Imran", "Dr. Ali", "Dr. biggie" };
    const string surgeonExpertise[SURGEON_COUNT] = { "Cardiology", "Neurology", "Orthopedics", "General Surgery" };

    int choice;
    do {
        cout << "\nChoose a module:\n1. Appointment Management\n2. Emergency Care\n3. Surgery Scheduling\n4. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1: {
            int apptChoice;
            do {
                cout << "Appointment Management:\n1. Book Appointment\n2. Update Appointment Status\n3. Cancel Appointment\n4. Show Appointments\n5. Back to main menu\n";
                cin >> apptChoice;

                switch (apptChoice) {
                case 1: {
                    string patientName, doctorName, time;
                    cout << "Enter patient name: ";
                    cin >> patientName;
                    cout << "Available doctors:\n";
                    for (int i = 0; i < DOCTOR_COUNT; ++i) {
                        cout << i + 1 << ". " << doctors[i] << endl;
                    }
                    int docIndex;
                    cout << "Choose doctor by number: ";
                    cin >> docIndex;
                    if (docIndex < 1 || docIndex > DOCTOR_COUNT) {
                        cout << "Invalid doctor choice." << endl;
                        break;
                    }
                    doctorName = doctors[docIndex - 1];
                    cout << "Available time slots:\n";
                    for (int i = 0; i < SLOTS_PER_DAY; ++i) {
                        cout << i + 1 << ". " << doctorSlots[i] << endl;
                    }
                    int timeIndex;
                    cout << "Choose time slot by number: ";
                    cin >> timeIndex;
                    if (timeIndex < 1 || timeIndex > SLOTS_PER_DAY) {
                        cout << "Invalid time slot choice." << endl;
                        break;
                    }
                    time = doctorSlots[timeIndex - 1];
                    apptMgr.bookAppointment(patientName, doctorName, time);
                    break;
                }
                case 2: {
                    string patientName, doctorName;
                    bool status;
                    cout << "Enter patient name: ";
                    cin >> patientName;
                    cout << "Available doctors:\n";
                    for (int i = 0; i < DOCTOR_COUNT; ++i) {
                        cout << i + 1 << ". " << doctors[i] << endl;
                    }
                    int docIndex;
                    cout << "Choose doctor by number: ";
                    cin >> docIndex;
                    if (docIndex < 1 || docIndex > DOCTOR_COUNT) {
                        cout << "Invalid doctor choice." << endl;
                        break;
                    }
                    doctorName = doctors[docIndex - 1];
                    cout << "Enter status (0 for pending, 1 for completed): ";
                    cin >> status;
                    apptMgr.updateAppointmentStatus(doctorName, patientName, status);
                    break;
                }
                case 3: {
                    string patientName, doctorName;
                    cout << "Enter patient name: ";
                    cin >> patientName;
                    cout << "Available doctors:\n";
                    for (int i = 0; i < DOCTOR_COUNT; ++i) {
                        cout << i + 1 << ". " << doctors[i] << endl;
                    }
                    int docIndex;
                    cout << "Choose doctor by number: ";
                    cin >> docIndex;
                    if (docIndex < 1 || docIndex > DOCTOR_COUNT) {
                        cout << "Invalid doctor choice." << endl;
                        break;
                    }
                    doctorName = doctors[docIndex - 1];
                    apptMgr.cancelAppointment(doctorName, patientName);
                    break;
                }
                case 4: {
                    string doctorName;
                    cout << "Available doctors:\n";
                    for (int i = 0; i < DOCTOR_COUNT; ++i) {
                        cout << i + 1 << ". " << doctors[i] << endl;
                    }
                    int docIndex;
                    cout << "Choose doctor by number: ";
                    cin >> docIndex;
                    if (docIndex < 1 || docIndex > DOCTOR_COUNT) {
                        cout << "Invalid doctor choice." << endl;
                        break;
                    }
                    doctorName = doctors[docIndex - 1];
                    apptMgr.showAppointments(doctorName);
                    break;
                }
                case 5:
                    cout << "Returning to main menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            } while (apptChoice != 5);
            break;
        }
        case 2: {
            int emergChoice;
            do {
                cout << "Emergency Care:\n1. Admit Patient\n2. Treat Patient\n3. Back to main menu\n";
                cin >> emergChoice;

                switch (emergChoice) {
                case 1: {
                    string name;
                    int triageLevel;
                    cout << "Enter patient name: ";
                    cin >> name;
                    cout << "Enter triage level (1-5): ";
                    cin >> triageLevel;
                    emergencyCare.insert(name, triageLevel);
                    break;
                }
                case 2: {
                    if (emergencyCare.getRoot() != nullptr) {
                        cout << "Treating patient: " << emergencyCare.getRoot()->name << endl;
                        emergencyCare.remove(emergencyCare.getRoot()->triageLevel);
                    } else {
                        cout << "No patients to treat." << endl;
                    }
                    break;
                }
                case 3:
                    cout << "Returning to main menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            } while (emergChoice != 3);
            break;
        }
        case 3: {
            int surgChoice;
            do {
                cout << "Surgery Scheduling:\n1. Schedule Surgery\n2. Show Surgeries\n3. Back to main menu\n";
                cin >> surgChoice;

                switch (surgChoice) {
                case 1: {
                    string patientName, surgeryType, time, operatingRoom;
                    cout << "Enter patient name: ";
                    cin >> patientName;
                    cout << "Available surgeons and their expertise:\n";
                    for (int i = 0; i < SURGEON_COUNT; ++i) {
                        cout << i + 1 << ". " << surgeons[i] << " - " << surgeonExpertise[i] << endl;
                    }
                    int surgeonIndex;
                    cout << "Choose surgeon by number: ";
                    cin >> surgeonIndex;
                    if (surgeonIndex < 1 || surgeonIndex > SURGEON_COUNT) {
                        cout << "Invalid surgeon choice." << endl;
                        break;
                    }
                    cout << "Enter surgery type: ";
                    cin >> surgeryType;
                    cout << "Available time slots:\n";
                    for (int i = 0; i < SLOTS_PER_DAY; ++i) {
                        cout << i + 1 << ". " << doctorSlots[i] << endl;
                    }
                    int timeIndex;
                    cout << "Choose time slot by number: ";
                    cin >> timeIndex;
                    if (timeIndex < 1 || timeIndex > SLOTS_PER_DAY) {
                        cout << "Invalid time slot choice." << endl;
                        break;
                    }
                    time = doctorSlots[timeIndex - 1];
                    cout << "Enter operating room: ";
                    cin >> operatingRoom;
                    surgerySched.scheduleSurgery(patientName, surgeryType, time, operatingRoom);
                    break;
                }
                case 2: {
                    string operatingRoom;
                    cout << "Enter operating room: ";
                    cin >> operatingRoom;
                    surgerySched.showSurgeries(operatingRoom);
                    break;
                }
                case 3:
                    cout << "Returning to main menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice." << endl;
                    break;
                }
            } while (surgChoice != 3);
            break;
        }
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}