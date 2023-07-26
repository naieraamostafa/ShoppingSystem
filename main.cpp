#include <iostream>
#include <vector>
using namespace std;

class Item {
private:
    int ID;
    string name;
    int quantity;
    double price;

public:
    //Default Constructor
    Item(){
    name = "";
    ID = 0;
    quantity = 0;
    price = 0.0;
}
    //Parameterized Constructor
    Item(int id,string n,int q,double p){
    name = n;
    id = id;
    quantity = q;
    price = p;
}
    //Copy Constructor
    Item(const Item& item){
    name = item.name;
    ID= item.ID;
    quantity = item.quantity;
    price = item.price;
}
    bool operator==(const Item& other) const {
        return name == other.name;
    }

    Item& operator+=(const Item& other) {
        quantity += other.quantity;
        return *this;
    }

    Item& operator-=(int soldQuantity) {
        if (quantity >= soldQuantity)
            quantity -= soldQuantity;
        else
            cout << "Insufficient quantity available.\n";
        return *this;
    }

    friend ostream& operator<<(ostream& os, const Item& item) {
        os << "ID: " << item.ID << ", Name: " << item.name << ", Quantity: " << item.quantity << ", Price: " << item.price;
        return os;
    }

    friend istream& operator>>(istream& is, Item& item) {
        cout << "Enter ID: ";
        is >> item.ID;
        cout << "Enter Name: ";
        is >> item.name;
        cout << "Enter Quantity: ";
        is >> item.quantity;
        cout << "Enter Price: ";
        is >> item.price;
        return is;
    }
    //setter for id
    void setID(int id) {
        ID = id;
    }
    //setter for name
    void setName(const string& n) {
        name = n;
    }
    //setter for quantity
    void setQuantity(int q) {
        quantity = q;
    }
    //setter for price
    void setPrice(double p) {
        price = p;
    }
    //getter for id
    int getID() const {
        return ID;
    }
    //getter for name
    string getName() const {
        return name;
    }
    //getter for quantity
    int getQuantity() const {
        return quantity;
    }
    //getter for price
    double getPrice() const {
        return price;
    }
};

class Seller {
private:
    string name;
    string email;
    vector<Item> items;
    int maxItems;

public:
    Seller(string n, string e, int max) : name(n), email(e), maxItems(max) {}

    bool AddItem(const Item& newItem) {
        if (items.size() >= maxItems) {
            cout << "Seller's item limit reached. Cannot add more items.\n";
            return false;
        }

        bool itemExists = false;
        for (Item& item : items) {
            if (item == newItem) {
                item += newItem;
                itemExists = true;
                break;
            }
        }

        if (!itemExists) {
            items.push_back(newItem);
        }

        return true;
    }

    bool SellItem(const string& itemName, int quantity) {
        bool itemFound = false;
        for (Item& item : items) {
            if (item == Item(0, itemName, 0, 0.0)) {
                itemFound = true;
                item -= quantity;
                return true;
            }
        }
        return false;
    }

    void PrintItems() const {
        for (const Item& item : items) {
            cout << item << endl;
        }
    }

    Item* FindById(int id) {
        for (Item& item : items) {
            if (item.getID() == id)
                return &item;
        }
        return nullptr;
    }

    void setName(const string& n) {
        name = n;
    }

    void setEmail(const string& e) {
        email = e;
    }

    void setMaxItems(int max) {
        maxItems = max;
    }

    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    int getMaxItems() const {
        return maxItems;
    }

    friend ostream& operator<<(ostream& os, const Seller& seller) {
        os << "Name: " << seller.name << ", Email: " << seller.email << ", Max Items: " << seller.maxItems;
        return os;
    }
};

int main() {
    string name, email;
    int maxItems;
    cout << "Please input your details:\n";
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your E-mail: ";
    cin >> email;
    cout << "Enter the max number of items: ";
    cin >> maxItems;

    Seller s1(name, email, maxItems);

    int C = 0;
    while (C != 6) {
        cout << "\nChoose "<<endl;
        cout << "1. Print My Details\n";
        cout << "2. Add an Item\n";
        cout << "3. Sell an Item\n";
        cout << "4. Print Items\n";
        cout << "5. Find an Item by ID\n";
        cout << "6. Exit\n"<<endl;
        cout << " Enter Your choice: ";
        cin >> C;

        while (C < 1 || C > 6) {
            cout << "Invalid choice ";
            cin >> C;
        }

        if (C == 1) {
            cout << "\n" << s1 << endl;

        } else if (C == 2) {
            Item item;
            cout << "\n";
            cin >> item;
            if (s1.AddItem(item))
                cout << "Item added successfully.\n";
        } else if (C == 3) {
            string name;
            int quantity;
            cout << "\nEnter the name of item: ";
            cin >> name;
            cout << "Enter the quantity of item to be sold: ";
            cin >> quantity;
            if (!s1.SellItem(name, quantity))
                cout << "Item not found or insufficient quantity available.\n";

        } else if (C == 4) {
            cout << "\n";
            s1.PrintItems();
        } else if (C == 5) {
            int id;
            cout << "\nEnter the ID of item to be found: ";
            cin >> id;
            Item* item = s1.FindById(id);
            if (item == nullptr)
                cout << "Item not found!\n";
            else {
                cout << "Item found:\n";
                cout << *item << endl;
            }
        } else if (C == 6) {
            return 0;
        }
    }

    return 0;
}
