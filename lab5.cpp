#include <iostream>
#include <string>

// Базовий клас StudentRecord
class StudentRecord {
protected:
    std::string last_name;
    std::string first_name;
    std::string home_address;
    std::string phone;
    std::string birth_date;

public:
    StudentRecord(std::string ln, std::string fn, std::string addr, std::string ph, std::string bd)
        : last_name(ln), first_name(fn), home_address(addr), phone(ph), birth_date(bd) {}

    virtual void display() const {
        std::cout << "Last Name: " << last_name << "\n"
            << "First Name: " << first_name << "\n"
            << "Home Address: " << home_address << "\n"
            << "Phone: " << phone << "\n"
            << "Birth Date: " << birth_date << "\n";
    }

    std::string getLastName() const {
        return last_name;
    }

};

// Похідний клас
class SpecializedStudentRecord : public StudentRecord {
private:
    std::string major;
    double gpa;

public:
    SpecializedStudentRecord(std::string ln, std::string fn, std::string addr, std::string ph, std::string bd, std::string maj, double g)
        : StudentRecord(ln, fn, addr, ph, bd), major(maj), gpa(g) {}

    void display() const override {
        StudentRecord::display();
        std::cout << "Major: " << major << "\n"
            << "GPA: " << gpa << "\n";
    }

};

// керування журналом студентів
class StudentJournal {
private:
    StudentRecord** records;
    int size;
    int capacity;

    void resize(int new_capacity) {
        StudentRecord** new_records = new StudentRecord * [new_capacity];
        for (int i = 0; i < size; ++i) {
            new_records[i] = records[i];
        }
        delete[] records;
        records = new_records;
        capacity = new_capacity;
    }

public:
    StudentJournal() : size(0), capacity(10) {
        records = new StudentRecord * [capacity];
    }

    ~StudentJournal() {
        for (int i = 0; i < size; ++i) {
            delete records[i];
        }
        delete[] records;
    }

    void addRecord(StudentRecord* record) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        records[size++] = record;
    }

    void deleteRecord(const std::string& last_name) {
        for (int i = 0; i < size; ++i) {
            if (records[i]->getLastName() == last_name) {
                delete records[i];
                for (int j = i; j < size - 1; ++j) {
                    records[j] = records[j + 1];
                }
                --size;
                return;
            }
        }
    }

    void displayRecords() const {
        for (int i = 0; i < size; ++i) {
            records[i]->display();
            std::cout << "\n";
        }
    }
};

// Функція для введення даних студента
StudentRecord* createStudentRecord() {
    std::string last_name, first_name, home_address, phone, birth_date;

    std::cout << "Enter last name: ";
    std::getline(std::cin, last_name);
    std::cout << "Enter first name: ";
    std::getline(std::cin, first_name);
    std::cout << "Enter home address: ";
    std::getline(std::cin, home_address);
    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);
    std::cout << "Enter birth date (YYYY-MM-DD): ";
    std::getline(std::cin, birth_date);

    return new StudentRecord(last_name, first_name, home_address, phone, birth_date);
}

// Функція для введення даних спеціалізованого студента
SpecializedStudentRecord* createSpecializedStudentRecord() {
    std::string last_name, first_name, home_address, phone, birth_date, major;
    double gpa;

    std::cout << "Enter last name: ";
    std::getline(std::cin, last_name);
    std::cout << "Enter first name: ";
    std::getline(std::cin, first_name);
    std::cout << "Enter home address: ";
    std::getline(std::cin, home_address);
    std::cout << "Enter phone: ";
    std::getline(std::cin, phone);
    std::cout << "Enter birth date (YYYY-MM-DD): ";
    std::getline(std::cin, birth_date);
    std::cout << "Enter major: ";
    std::getline(std::cin, major);
    std::cout << "Enter GPA: ";
    std::cin >> gpa;
    std::cin.ignore();  

    return new SpecializedStudentRecord(last_name, first_name, home_address, phone, birth_date, major, gpa);
}


int main() {
    StudentJournal journal;
    int choice;

    while (true) {
        std::cout << "1. Add Student Record\n";
        std::cout << "2. Add Specialized Student Record\n";
        std::cout << "3. Display Records\n";
        std::cout << "4. Delete Record by Last Name\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  

        if (choice == 1) {
            journal.addRecord(createStudentRecord());
        }
        else if (choice == 2) {
            journal.addRecord(createSpecializedStudentRecord());
        }
        else if (choice == 3) {
            journal.displayRecords();
        }
        else if (choice == 4) {
            std::string last_name;
            std::cout << "Enter last name of the record to delete: ";
            std::getline(std::cin, last_name);
            journal.deleteRecord(last_name);
        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
