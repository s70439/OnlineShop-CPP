#include <iostream>
#include <windows.h>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#define BOLD "\033[1m"
#define RESET "\033[0m"
using namespace std;

class Customer;
class Option;

class Authorization {
private:
    static string Login[5];
    static string Password[5];
public:
    void LoginScreen();
    void changePassword(string pas);
    void changeLogin(string log);
    static string currentPassword, currentLogin;
    static int IndexID;
};

class Option {
private:
    int choice;
public:
    void ShowMenu();
};

class Product {
public:
    string name;
    string category;
    string variety;
    double price;

    Product(string n, string c, string v, double p)
        : name(n), category(c), variety(v), price(p) {
    }
};

class ShoppingCart {
private:
    vector<Product> items;
    double totalPrice;

public:
    ShoppingCart() : totalPrice(0) {}

    void addToCart(const Product& product) {
        items.push_back(product);
        totalPrice += product.price;
        cout << " " << product.name << " added to cart!\n";
    }

    void showCart() {
        system("cls");
        cout << "========================================================================\n";
        cout << "|                           SHOPPING CART                             |\n";
        cout << "========================================================================\n\n";

        if (items.empty()) {
            cout << "Cart is empty!\n";
        }
        else {
            for (int i = 0; i < items.size(); i++) {
                cout << i + 1 << ". " << items[i].name << " - " << items[i].variety
                    << " (" << items[i].price << " USD)\n";
            }
            cout << "\n----------------------------------------\n";
            cout << "Total: " << totalPrice << " USD\n";
        }
        cout << "========================================================================\n";
    }

    void clearCart() {
        items.clear();
        totalPrice = 0;
        cout << " Cart cleared!\n";
    }

    double getTotalPrice() const {
        return totalPrice;
    }

    int getItemCount() const {
        return items.size();
    }
};

class ProductManager {
private:
    vector<Product> products;
    ShoppingCart cart;

public:
    void ShowCatalog();
    void addSampleProducts() {
        products = {
            Product("Apples", "Fruits", "Granny Smith", 12.50),
            Product("Apples", "Fruits", "Golden", 9.50),
            Product("Apples", "Fruits", "Red Delicious", 11.00),
            Product("Bananas", "Fruits", "Cavendish", 8.90),
            Product("Plums", "Fruits", "Caucasian", 14.00),
            Product("Tangerines", "Fruits", "Mini", 16.00),
            Product("Persimmon", "Fruits", "Shi Bu", 18.00),
            Product("Pears", "Fruits", "Chinese", 9.00),
            Product("Grapes", "Fruits", "Red Globe", 21.00),
            Product("Oranges", "Fruits", "Selected", 17.00),
            Product("Plums", "Fruits", "President", 19.99),
            Product("Grapes", "Fruits", "Black", 14.99),
            Product("Pomelo", "Fruits", "Pink", 16.49),
            Product("Lemons", "Fruits", "Royal", 26.99),
            Product("Oranges", "Fruits", "Navel", 15.00),
            Product("Milk", "Dairy", "Pasteurized", 8.50),
            Product("Milk", "Dairy", "Kuban", 14.49),
            Product("Cottage Cheese", "Dairy", "Korovka", 14.49),
            Product("Ryazhenka", "Dairy", "Agrocomplex", 13.49),
            Product("Tan", "Dairy", "Milk Station", 4.79),
            Product("Snegok", "Dairy", "Kuban", 7.69),
            Product("Kefir", "Dairy", "Prostokvashino", 7.00),
            Product("Apple Juice", "Beverages", "Freshly Squeezed", 20.00),
            Product("Walnuts", "Nuts", "Royal Walnut", 25.00)
        };
    }

    Product getProduct(int index) const {
        if (index >= 0 && index < products.size()) {
            return products[index];
        }
        return Product("", "", "", 0);
    }

    int getProductCount() const {
        return products.size();
    }

    void addToCart(int productIndex) {
        if (productIndex >= 0 && productIndex < products.size()) {
            cart.addToCart(products[productIndex]);
        }
    }

    void showCart() {
        cart.showCart();
    }

    void clearCart() {
        cart.clearCart();
    }

    double getCartTotal() const {
        return cart.getTotalPrice();
    }

    ShoppingCart& getCart() {
        return cart;
    }
};

// INITIALIZATION of static arrays
string Authorization::Login[5] = { "", "", "admin", "", "" };
string Authorization::Password[5] = { "", "", "admin", "", "" };
string Authorization::currentPassword = "";
string Authorization::currentLogin = "";
int Authorization::IndexID = 0;

void Authorization::LoginScreen() {
    string inputLogin, inputPassword;
    int attempts = 0;

    cout << "========================================================================\n";
    cout << "|                            LOGIN SCREEN                              |\n";
    cout << "========================================================================\n\n";
    cout << "Login: ";
    cin >> inputLogin;
    cout << "Password: ";
    cin >> inputPassword;

    for (int i = 0; i < 5; i++) {
        if (Login[i] == inputLogin && Password[i] == inputPassword) {
            currentPassword = Password[i];
            currentLogin = Login[i];
            IndexID = i;
            cout << "========================================================================\n";
            cout << "|                          WELCOME!                                   |\n";
            cout << "========================================================================\n\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            Option opt;
            opt.ShowMenu();
            return;
        }
        else {
            attempts++;
        }
    }

    if (attempts == 5) {
        cout << "========================================================================\n";
        cout << "|               INCORRECT LOGIN OR PASSWORD!                          |\n";
        cout << "========================================================================\n\n";
        system("pause");
        LoginScreen();
    }
}

void Authorization::changePassword(string pas) {
    Password[IndexID] = pas;
    currentPassword = pas;
}

void Authorization::changeLogin(string log) {
    Login[IndexID] = log;
    currentLogin = log;
}

class Customer {
private:
    int choice;
public:
    void ShowCustomerMenu();
    void ChangePassword();
    void ChangeLogin();
    void ChangeColor();
    void Logout();
};

void Customer::Logout() {
    string choice;
    cout << "========================================================================\n";
    cout << "|                    ARE YOU SURE YOU WANT TO LOGOUT?                  |\n";
    cout << "========================================================================\n";
    cout << "|            YES(yes)             |             NO(no)                 |\n";
    cout << "========================================================================\n\n";
    cin >> choice;
    if (choice == "no") {
        system("cls");
        ShowCustomerMenu();
    }
    else if (choice == "yes") {
        system("cls");
        Authorization auth;
        auth.LoginScreen();
    }
    else {
        cout << "Unknown command! ";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
        ShowCustomerMenu();
    }
}

void Customer::ChangePassword() {
    system("cls");
    cout << "========================================================================\n";
    cout << "|                         CHANGE PASSWORD                             |\n";
    cout << "========================================================================\n";
    string oldPass, newPass1, newPass2;
    cout << "Enter your old password: ";
    cin >> oldPass;

    if (oldPass == Authorization::currentPassword) {
        cout << "Enter your new password: ";
        cin >> newPass1;
        cout << "Repeat new password: ";
        cin >> newPass2;

        if (newPass1 != newPass2) {
            cout << "========================================================================\n";
            cout << "|                 ERROR! PASSWORDS DO NOT MATCH.                     |\n";
            cout << "========================================================================\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            ChangePassword();
        }
        else {
            Authorization auth;
            auth.changePassword(newPass1);
            cout << "========================================================================\n";
            cout << "|                     PASSWORD CHANGED SUCCESSFULLY!                  |\n";
            cout << "========================================================================\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            ShowCustomerMenu();
        }
    }
    else {
        cout << "========================================================================\n";
        cout << "|               INCORRECT OLD PASSWORD!                               |\n";
        cout << "========================================================================\n";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
        ChangePassword();
    }
}

void Customer::ChangeLogin() {
    system("cls");
    cout << "========================================================================\n";
    cout << "|                          CHANGE LOGIN                               |\n";
    cout << "========================================================================\n";
    string oldLogin, newLogin1, newLogin2;
    cout << "Enter your old login: ";
    cin >> oldLogin;

    if (oldLogin == Authorization::currentLogin) {
        cout << "Enter your new login: ";
        cin >> newLogin1;
        cout << "Repeat new login: ";
        cin >> newLogin2;

        if (newLogin1 != newLogin2) {
            cout << "========================================================================\n";
            cout << "|                  ERROR! LOGINS DO NOT MATCH.                       |\n";
            cout << "========================================================================\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            ChangeLogin();
        }
        else {
            Authorization auth;
            auth.changeLogin(newLogin1);
            cout << "========================================================================\n";
            cout << "|                      LOGIN CHANGED SUCCESSFULLY!                   |\n";
            cout << "========================================================================\n";
            this_thread::sleep_for(chrono::seconds(2));
            system("cls");
            ShowCustomerMenu();
        }
    }
    else {
        cout << "========================================================================\n";
        cout << "|               INCORRECT OLD LOGIN!                                 |\n";
        cout << "========================================================================\n";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
        ChangeLogin();
    }
}

void Customer::ChangeColor() {
    system("cls");
    cout << "========================================================================\n";
    cout << "|                     CHANGE CONSOLE COLOR                            |\n";
    cout << "========================================================================\n\n";
    cout << "Choose color: \n";
    cout << "Gray (default) (1) \n";
    cout << "Black (2) \n";
    cout << "Blue (3) \n";
    cout << "Green (4) \n";
    cout << "Red (5) \n";
    cout << "White (6) \n";
    cout << "Back (7) \n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        system("color 80");
    }
    else if (choice == 2) {
        system("color 07");
    }
    else if (choice == 3) {
        system("color 14");
    }
    else if (choice == 4) {
        system("color 26");
    }
    else if (choice == 5) {
        system("color 40");
    }
    else if (choice == 6) {
        system("color 70");
    }

    if (choice >= 1 && choice <= 6) {
        cout << "========================================================================\n";
        cout << "|                    COLOR CHANGED SUCCESSFULLY!                      |\n";
        cout << "========================================================================\n";
        this_thread::sleep_for(chrono::seconds(2));
    }

    system("cls");
}

void Customer::ShowCustomerMenu() {
    system("cls");
    cout << "========================================================================\n";
    cout << "|                     CUSTOMER SETTINGS MENU                         |\n";
    cout << "========================================================================\n";
    cout << "| Change login (1)                                                    |\n";
    cout << "| Change password (2)                                                 |\n";
    cout << "| Return to main menu (3)                                             |\n";
    cout << "| Change console color (4)                                            |\n";
    cout << "| Logout (5)                                                          |\n";
    cout << "========================================================================\n";
    cin >> choice;
    if (choice == 1) {
        ChangeLogin();
    }
    else if (choice == 2) {
        ChangePassword();
    }
    else if (choice == 3) {
        system("cls");
        Option opt;
        opt.ShowMenu();
    }
    else if (choice == 4) {
        ChangeColor();
        system("cls");
        ShowCustomerMenu();
    }
    else if (choice == 5) {
        Logout();
    }
    else {
        cout << "Invalid choice! ";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
        ShowCustomerMenu();
    }
}

void Option::ShowMenu() {
    static ProductManager productManager;

    system("cls");
    cout << "========================================================================\n";
    cout << "|                       MAIN MENU                                    |\n";
    cout << "========================================================================\n";
    cout << "| Customer settings (1)                                               |\n";
    cout << "| Product catalog (2)                                                 |\n";
    cout << "| Go to shopping cart (3)                                             |\n";
    cout << "| Checkout (4)                                                        |\n";
    cout << "| Exit program (5)                                                    |\n";
    cout << "========================================================================\n";
    cin >> choice;

    if (choice == 1) {
        system("cls");
        Customer cust;
        cust.ShowCustomerMenu();
        system("cls");
        ShowMenu();
    }
    else if (choice == 2) {
        system("cls");
        productManager.ShowCatalog();
        system("cls");
        ShowMenu();
    }
    else if (choice == 3) {
        system("cls");
        productManager.showCart();
        cout << "\n1. Clear cart\n";
        cout << "2. Return to menu\n";
        cout << "Choose action: ";
        int cartChoice;
        cin >> cartChoice;

        if (cartChoice == 1) {
            productManager.clearCart();
            cout << "Cart cleared! Press Enter...";
            cin.ignore();
            cin.get();
        }
        system("cls");
        ShowMenu();
    }
    else if (choice == 4) {
        system("cls");
        double total = productManager.getCartTotal();
        if (total > 0) {
            cout << "========================================================================\n";
            cout << "|                            CHECKOUT                                 |\n";
            cout << "========================================================================\n";
            cout << "Total amount to pay: " << total << " USD\n";
            cout << "Payment successful! Thank you for your purchase!\n";
            productManager.clearCart();
        }
        else {
            cout << "Cart is empty! Add products before checkout.\n";
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("cls");
        ShowMenu();
    }
    else if (choice == 5) {
        system("cls");
        cout << "Exiting program..." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        exit(0);
    }
    else {
        cout << "Invalid choice! ";
        this_thread::sleep_for(chrono::seconds(2));
        system("cls");
        ShowMenu();
    }
}

void ProductManager::ShowCatalog() {
    system("cls");

    if (products.empty()) {
        addSampleProducts();
    }

    int choice;

    while (true) {
        system("color 80");

        cout << "========================================================================\n";
        cout << "|                         PRODUCT CATALOG                            |\n";
        cout << "========================================================================\n";
        cout << "| Items in cart: " << setw(39) << left << cart.getItemCount() << " |\n";
        cout << "| Total cost: " << setw(41) << left << cart.getTotalPrice() << " USD |\n";
        cout << "========================================================================\n\n";

        string currentCategory = "";
        int productNumber = 1;

        for (int i = 0; i < products.size(); i++) {
            const auto& product = products[i];

            if (product.category != currentCategory) {
                currentCategory = product.category;
                cout << "\n" << " " << currentCategory << "\n";
                cout << "----------------------------------------\n";
            }

            cout << productNumber << ". " << product.name << " - " << product.variety
                << " (" << product.price << " USD)\n";
            productNumber++;
        }

        cout << "\n========================================================================\n";
        cout << "Enter product number to add to cart\n";
        cout << "Or choose action:\n";
        cout << "0. View cart\n";
        cout << "99. Return to menu\n";
        cout << "Your choice: ";
        cin >> choice;

        if (choice == 0) {
            system("cls");
            cart.showCart();
            cout << "\n1. Clear cart\n";
            cout << "2. Return to catalog\n";
            cout << "Choose action: ";
            int cartChoice;
            cin >> cartChoice;

            if (cartChoice == 1) {
                cart.clearCart();
                cout << "Cart cleared! Press Enter...";
                cin.ignore();
                cin.get();
            }

            system("cls");
            continue;
        }
        else if (choice == 99) {
            break;
        }
        else if (choice >= 1 && choice <= products.size()) {
            int productIndex = choice - 1;
            cart.addToCart(products[productIndex]);
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            system("cls");
        }
        else {
            cout << "Invalid choice! Press Enter...";
            cin.ignore();
            cin.get();
            system("cls");
        }
    }
}

int main() {
    system("chcp 65001 > nul"); // UTF-8 encoding for English
    system("color 80");
    Authorization auth;
    auth.LoginScreen();
    return 0;
}












