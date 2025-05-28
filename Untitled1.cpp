#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Product class
class Product {
private:
    int id;
    string name;
    string category;
    double price;

public:
    Product(int prodId, string prodName, string prodCategory, double prodPrice)
        : id(prodId), name(prodName), category(prodCategory), price(prodPrice) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
};

// User class
class User {
private:
    string username;

public:
    User(string uname) : username(uname) {}
    string getUsername() const { return username; }
};

// ShoppingCart class
class ShoppingCart {
private:
    vector<Product> cartItems;

public:
    void addProduct(const Product& product) {
        cartItems.push_back(product);
        cout << product.getName() << " added to your cart!" << endl;
    }

    void showCart() const {
        if (cartItems.empty()) {
            cout << "\nYour cart is empty." << endl;
            return;
        }
        cout << "\n--- Your Cart ---" << endl;
        double total = 0;
        int idx = 1;
        for (const auto& item : cartItems) {
            cout << idx << ". " << item.getName() << " (" << item.getCategory()
                 << ") - Rs. " << item.getPrice() << endl;
            total += item.getPrice();
            idx++;
        }
        cout << "Total: Rs. " << total << endl;
    }

    vector<Product> getItems() const { return cartItems; }
    void clearCart() { cartItems.clear(); }
    bool isEmpty() const { return cartItems.empty(); }
};

// Order class
class Order {
private:
    vector<Product> orderedItems;
    string placedBy;
    double totalAmount;

public:
    Order(const vector<Product>& items, const string& username)
        : orderedItems(items), placedBy(username), totalAmount(0) {
        for (const auto& item : orderedItems) {
            totalAmount += item.getPrice();
        }
    }

    void showOrder() const {
        cout << "\nOrder placed by: " << placedBy << endl;
        cout << "Items:" << endl;
        int count = 1;
        for (const auto& item : orderedItems) {
            cout << count << ". " << item.getName() << " (" << item.getCategory()
                 << ") - Rs. " << item.getPrice() << endl;
            count++;
        }
        cout << "Total Amount: Rs. " << totalAmount << endl;
    }
};

int main() {
    vector<Product> productList = {
        Product(1, "Shirt", "Clothes", 1200),
        Product(2, "Pants", "Clothes", 1500),
        Product(3, "Trousers", "Clothes", 1800),
        Product(4, "Necklace", "Jewelry", 5000),
        Product(5, "Earrings", "Jewelry", 3000),
        Product(6, "Bangles", "Jewelry", 2500),
        Product(7, "Concealer", "Makeup", 800),
        Product(8, "Foundation", "Makeup", 1500),
        Product(9, "Lipstick", "Makeup", 600),
        Product(10, "Joggers", "Shoes", 2200),
        Product(11, "Sandals", "Shoes", 1300),
        Product(12, "Slippers", "Shoes", 700)
    };

    vector<string> registeredUsers;
    string username;
    int choice;

    cout << "=== Welcome to the Shopping System ===" << endl;
    cout << "1. Sign Up\n2. Sign In\nEnter choice: ";
    cin >> choice;
    cin.ignore(10000, '\n');

    if (choice == 1) {
        cout << "Sign Up ? Enter a username: ";
        getline(cin, username);
        bool exists = false;
        for (const auto& u : registeredUsers) {
            if (u == username) {
                exists = true;
                break;
            }
        }
        if (exists) {
            cout << "Username already exists! Restart and sign in." << endl;
            return 0;
        }
        registeredUsers.push_back(username);
        cout << "Sign-up successful! Now sign in." << endl;
        cout << "Enter username: ";
        getline(cin, username);
    } else if (choice == 2) {
        cout << "Sign In ? Enter username: ";
        getline(cin, username);
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 0;
    }

    User currentUser(username);
    ShoppingCart cart;
    vector<Order> orderHistory;

    cout << "\nWelcome, " << currentUser.getUsername() << "!" << endl;

    int menuOption;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Browse Categories\n";
        cout << "2. Add Product to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Place Order\n";
        cout << "5. View Order History\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";

        if (!(cin >> menuOption)) {
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        if (menuOption == 1) {
            cout << "\nCategories:\n1. Clothes\n2. Jewelry\n3. Makeup\n4. Shoes\n";
            cout << "Choose category number: ";
            int catChoice;
            if (!(cin >> catChoice)) {
                cout << "Invalid input!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore(10000, '\n');

            string selectedCategory;
            if (catChoice == 1) selectedCategory = "Clothes";
            else if (catChoice == 2) selectedCategory = "Jewelry";
            else if (catChoice == 3) selectedCategory = "Makeup";
            else if (catChoice == 4) selectedCategory = "Shoes";
            else {
                cout << "Invalid category." << endl;
                continue;
            }

            cout << "\n--- Products in " << selectedCategory << " ---" << endl;
            for (const auto& product : productList) {
                if (product.getCategory() == selectedCategory) {
                    cout << product.getId() << ". " << product.getName()
                         << " - Rs. " << product.getPrice() << endl;
                }
            }
        }
        else if (menuOption == 2) {
            cout << "\nEnter Product ID to add: ";
            int prodId;
            if (!(cin >> prodId)) {
                cout << "Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            cin.ignore(10000, '\n');

            bool found = false;
            for (const auto& product : productList) {
                if (product.getId() == prodId) {
                    cart.addProduct(product);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Product not found. Please try again." << endl;
            }
        }
        else if (menuOption == 3) {
            cart.showCart();
        }
        else if (menuOption == 4) {
            if (cart.isEmpty()) {
                cout << "Cart is empty! Add products first." << endl;
            } else {
                Order newOrder(cart.getItems(), currentUser.getUsername());
                orderHistory.push_back(newOrder);
                newOrder.showOrder();
                cart.clearCart();
            }
        }
        else if (menuOption == 5) {
            if (orderHistory.empty()) {
                cout << "No orders placed yet." << endl;
            } else {
                int orderNum = 1;
                for (const auto& order : orderHistory) {
                    cout << "\nOrder #" << orderNum << ":" << endl;
                    order.showOrder();
                    orderNum++;
                }
            }
        }
        else if (menuOption == 0) {
            cout << "Thanks for visiting! Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid menu option. Try again." << endl;
        }
    }

    return 0;
}
