#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Electronic library management system

class books {

public:
    // members variables
    private:
    string titles;
    string nameAuthors;
    int id;
    int price;

public:
    // default constructor
    books() {

    }

    // parametrized constructor
    books(string t, string n, int i, int p) {
        titles = t;
        nameAuthors = n;
        id = i;
        price = p;
    }

    // getter of titles
    string get_titles() const {
        return titles;
    }

    // getter of nameAuthors
    string get_nameAuthors() const {
        return nameAuthors;
    }

    // getter of id
    int get_id() const {
        return id;
    }

    // getter of price
    int get_price() const {
        return price;
    }

    // function that shows information of books

    void info_Book() const {
        cout << get_titles() << " " << get_nameAuthors() << " " << get_id() << " " << get_price() << endl;
    }
};

class members {

private:
    string name;
    int age;
    int id;

public:
    static int default_age;
    members() {
    }

    members(string n, int a, int i) : name(n), id(i) {
        set_age(a);
    }

    void set_name(string n) {
        name = n;
    }

    string get_name() const {
        return name;
    }

    void set_age(int a) {
        if (a > 0 && a >= default_age) {
            age = a;
        } else {
            cout << "Sorry, your age is too small" << endl;
        }
    }

    int get_age() const {
        return age;
    }

    void set_id(int i) {
        id = i;
    }

    int get_id() const {
        return id;
    }

    virtual void info_members() const {
        cout << get_name() << " " << get_age() << " " << get_id() << endl;
    }

    // Virtual destructor for dynamic_cast

    virtual ~members() {

    }
};

// static variables

int members::default_age = 18;

class member_premium : public members {

private:
    int membership_duration;
    int membership_discount;
    int salary;

public:
    static int days;
    member_premium(int _duration, int _discount, int s, string n, int a, int i) : members(n, a, i) {
        membership_duration = _duration;
        membership_discount = _discount;
        salary = s;
    }

    // getter of duration 
    int get_duration() const {
        return membership_duration;
    }

    // getter of discount
    int get_discount() const {
        return membership_discount;
    }

    int get_salary() const {
        return salary;
    }

    void calc_discount() {
        if (membership_duration > 3) {
            membership_discount = (salary / 3);
        } else {
            membership_discount = (salary / 2);
        }
    }

    void info_members() const override {
        members::info_members();
        cout << get_duration() << " " << get_discount() << " " << get_salary() << endl;
    }
};

void info_manu() {
    cout << "Choice an Option" << endl;
    cout << "1. add new book" << endl;
    cout << "2. add new member" << endl;
    cout << "3. view all the books" << endl;
    cout << "4. view all the members" << endl;
    cout << "5. calculate the discount for premium members" << endl;
    cout << "6. Delete Item from Books OR Members List" << endl;
    cout << "7. Find a Book Within Budget"<<endl;
    cout << "8. Find a Book by Budget and Name"<<endl;
    cout << "9. Exiting....."<<endl;
}
             // تعديل دالة remove_item لتكون متوافقة مع فئات متعددة مثل books و members
   template<class T>
     void remove_item(vector<T>& list, int id) {
      bool found = false;
       for (auto it = list.begin(); it != list.end();) {
             if (it->get_id() == id) {
                it = list.erase(it);                                // Remove element from list
                cout << "Item Deleted Successfully." << endl;
                found = true;
              } else {
                ++it;
               } 
        }

    if (!found) {
        cout << "Item Not Found." << endl;
    }
}
    void remove_item_from_books(vector<books>& books_list, int id) {
        bool found = false;
             for (auto it = books_list.begin(); it != books_list.end();) {
                 if (it->get_id() == id) {
                 it = books_list.erase(it);                       // Remove book from list
                 cout << "Book Deleted Successfully." << endl;
                found = true;
               } else {
            ++it;
           }

    }
    if (!found) {
        cout << "Book Not Found." << endl;
    }
}

void remove_item_from_members(vector<members*>& members_list, int id) {
    bool found = false;
    for (auto it = members_list.begin(); it != members_list.end();) {
        if ((*it)->get_id() == id) {
            delete *it;                                          // delete member from memory
            it = members_list.erase(it);                         // delete member from list
            cout << "Member Deleted Successfully." << endl; 
            found = true;
        } else {
            ++it;
        }
    }

    if (!found) {
        cout << "Member Not Found." << endl;
    }
}

// Greedy Algorithm

const books* find_Book_Within_Budget(const vector<books>&books_list, int budget){
    if (books_list.empty()){
        throw runtime_error("The Book List is Empty");
        return nullptr;  
    }
    
    const books* best_book=nullptr;               // store the best book 

    for (const auto &book: books_list){
        if (book.get_price()<=budget){
            if (!best_book|| book.get_price() <best_book->get_price()){
                best_book=&book;
            }
        }
    }

    if (!best_book){
        throw runtime_error("NO Found Book Within Your Budget");
    }
    return best_book;
}


// Brute Focre Algorithm

void Find_A_Book_By_Budget_and_Name(const vector<books>&books_list,int budget, const string Books_Name){
    bool found=false;
    for(const auto &book:books_list){
        if (book.get_titles()==Books_Name){
            cout<<"Book Found"<<endl;
            book.info_Book();
            found=true;
            break;
        }
    } 
    if (!found){
        cout<<"No Book Within Budget And Matching This Name"<<endl;
    }
}

int main() {
    vector<books> books_list;                                   // use vector to store books
    vector<members*> members_list;                              // pointer to store members

    // Add a member premium manually
    members* premium_member = new member_premium(5, 20, 3000, "ahmed khaled", 24, 5);
    members_list.push_back(premium_member);

    // Add another member
    members* new_member = new members("Mohamed Ali", 30, 2);
    members_list.push_back(new_member);

    int choice;

    do {
        info_manu();  // show info_manu
        cin >> choice;

        switch (choice) {
            case 1: {
                string titles, authors;
                int id, price;
                cout << "Enter the book title" << endl;
                cin.ignore();  // ignore the newline reminder
                getline(cin, titles);  // to use getline because that use spaces 
                cout << "Enter the author's name" << endl;
                getline(cin, authors);  
                cout << "Enter book ID" << endl;
                cin >> id;
                cout << "Enter the price of the book" << endl;
                cin >> price;

                books add_newBooks(titles, authors, id, price);
                books_list.push_back(add_newBooks);  // add newbook to the list
                break;
            }

            case 2: {
                string name;
                int age, _id;
                cout << "Enter the member's name" << endl;
                cin.ignore();  // ignore the newline reminder
                getline(cin,name);  // to use getline because that use spaces 
                cout << "Enter your age" << endl;
                cin >> age;
                cout << "Enter your ID" << endl;
                cin >> _id;

                members* add_newMembers = new members(name, age, _id);
                members_list.push_back(add_newMembers);  // add new members to the list
                break;
            }

            case 3:
                cout << "Books List in Library:" << endl;
                if (books_list.empty()) {
                    cout << "No books available in the library" << endl;
                } else {
                    for (const auto& book : books_list)
                        book.info_Book();
                }
                break;

            case 4:
                cout << "Members List in Library:" << endl;
                if (members_list.empty()) {
                    cout << "No members available in the library" << endl;
                } else {
                    for (const auto& member : members_list)
                        member->info_members();
                }
                break;

            case 5: {
                int member_id;
                cout << "Enter the Premium Member ID to calculate the discount: ";
                cin >> member_id;

                bool found = false;
                bool isPremium = false;
                for (const auto& member_pre : members_list) {
                    if (member_pre->get_id() == member_id) {
                        member_premium* premium_member = dynamic_cast<member_premium*>(member_pre);

                        if (premium_member) {
                            isPremium = true;
                            premium_member->calc_discount();
                            premium_member->info_members();
                        } else {
                            cout << "This is not a premium member" << endl;
                        }

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Member not found" << endl;
                }
                break;
            }

            case 6: {                                               // Delete Item from Books OR Members List
                int id;
                cout << "Enter ID OF Item to Delete:" << endl;
                cin >> id;
                remove_item_from_books(books_list, id);           // delete book from list
                remove_item_from_members(members_list, id);      // delete member from list
                break;
            }
            case 7:{
                try
                {
                    int budget;
                    cout<<"Enter Your Budget"<<endl;
                    cin>>budget;

                    if (cin.fail()){
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');        // تجاهل المدخلات الغير صحيحه
                        throw invalid_argument("Invalid Input. plz Enter A Vaild Integer Budget");
                    }

                    const books* best_book=find_Book_Within_Budget(books_list,budget);
                    cout<<"You Can Buy This Book"<<endl;
                    best_book->info_Book();

                }

                catch(const runtime_error& e)
                {
                    cout<<"Error : "<< e.what() <<endl;
                }

                catch(const invalid_argument& e)
                {
                    cout<<"Invalid Input : "<< e.what() <<endl;
                }

                break;
            }

            case 8:{
                int Budget;
                cout<<"Enter Your Budget"<<endl;
                cin>>Budget;
                string Book_Name;
                cout<<"Enter the Book Name"<<endl;
                cin.ignore();                          // To handle the newline after budget input
                getline(cin,Book_Name);
                Find_A_Book_By_Budget_and_Name(books_list,Budget,Book_Name);
                break;
            }

            case 9:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid option, please try again" << endl;
        }

    } while (choice != 9);

    // clean dynamic allocation
    for (auto& member : members_list) {
        delete member;
    }
    
    return 0;
}