#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class RestaurantException : public std::exception
{
private:
    string message;
public:
    RestaurantException(const string& msg) : message(msg) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class InsufficientFundsException : public RestaurantException
{
public:
    InsufficientFundsException(const string& msg) : RestaurantException(msg) {}
};

class InsufficientIngredientsException : public RestaurantException
{
public:
    InsufficientIngredientsException(const string& msg) : RestaurantException(msg) {}
};

class NotFoundException : public RestaurantException
{
public:
    NotFoundException(const string& msg) : RestaurantException(msg) {}
};

class AuthenticationException : public RestaurantException
{
public:
    AuthenticationException(const string& msg) : RestaurantException(msg) {}
};

class InvalidInputException : public RestaurantException
{
public:
    InvalidInputException(const string& msg) : RestaurantException(msg) {}
};

class Ingredient
{
private:
    int id;
    string name;
    double quantityKg;
    double pricePerKg;

public:
    Ingredient(int id, const string& name, double quantityKg, double pricePerKg)
        : id(id), name(name), quantityKg(quantityKg), pricePerKg(pricePerKg)
    {
        if (id <= 0) throw InvalidInputException("Ingredient ID must be positive");
        if (quantityKg < 0) throw InvalidInputException("Ingredient quantity cannot be negative");
        if (pricePerKg < 0) throw InvalidInputException("Ingredient price cannot be negative");
        if (name.empty()) throw InvalidInputException("Ingredient name cannot be empty");
    }

    int getId() const { return id; }
    string getName() const { return name; }
    double getQuantityKg() const { return quantityKg; }
    double getPricePerKg() const { return pricePerKg; }

    void setQuantityKg(double quantity) {
        if (quantity < 0) throw InvalidInputException("Quantity cannot be negative");
        quantityKg = quantity;
    }

    void setPricePerKg(double price) {
        if (price < 0) throw InvalidInputException("Price cannot be negative");
        pricePerKg = price;
    }

    void increaseQuantity(double amount) {
        if (amount < 0) throw InvalidInputException("Amount to increase cannot be negative");
        quantityKg += amount;
    }

    void decreaseQuantity(double amount)
    {
        if (amount < 0) throw InvalidInputException("Amount to decrease cannot be negative");

        if (quantityKg < amount)
        {
            throw InsufficientIngredientsException("Insufficient quantity of " + name +
                ". Available: " + to_string(quantityKg) + " kg, Required: " + to_string(amount) + " kg");
        }
        quantityKg -= amount;
    }

    void display() const
    {
        cout << "ID: " << id << " | " << name << " | "
            << quantityKg << " kg | $" << pricePerKg << "/kg" << endl;
    }
};

class DishIngredient
{
private:
    Ingredient* ingredientItem;
    double quantityKg;

public:
    DishIngredient(Ingredient* ingredient, double quantity)
        : ingredientItem(ingredient), quantityKg(quantity)
    {
        if (ingredient == nullptr) throw InvalidInputException("Ingredient cannot be null");
        if (quantity <= 0) throw InvalidInputException("Ingredient quantity must be positive");
    }

    Ingredient* getIngredient() const { return ingredientItem; }
    double getQuantityKg() const { return quantityKg; }

    void display() const
    {
        cout << "  - " << ingredientItem->getName() << ": " << quantityKg << " kg" << endl;
    }
};

class Dish
{
private:
    int id;
    string name;
    string description;
    double price;
    vector<DishIngredient> ingredients;

public:
    Dish(int id, const string& name, const string& description, double price)
        : id(id), name(name), description(description), price(price)
    {
        if (id <= 0) throw InvalidInputException("Dish ID must be positive");
        if (name.empty()) throw InvalidInputException("Dish name cannot be empty");
        if (price < 0) throw InvalidInputException("Dish price cannot be negative");
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    const vector<DishIngredient>& getIngredients() const { return ingredients; }

    void addIngredient(Ingredient* ingredient, double quantity)
    {
        if (ingredient == nullptr) throw InvalidInputException("Ingredient cannot be null");

        auto it = find_if(ingredients.begin(), ingredients.end(),
            [ingredient](const DishIngredient& di)
            {
                return di.getIngredient()->getId() == ingredient->getId();
            });

        if (it != ingredients.end()) {
            throw InvalidInputException("Ingredient " + ingredient->getName() + " already exists in dish");
        }

        ingredients.push_back(DishIngredient(ingredient, quantity));
    }

    bool removeIngredient(int ingredientId)
    {
        auto it = find_if(ingredients.begin(), ingredients.end(),
            [ingredientId](const DishIngredient& di)
            {
                return di.getIngredient()->getId() == ingredientId;
            });

        if (it != ingredients.end())
        {
            ingredients.erase(it);
            return true;
        }
        return false;
    }

    bool isAvailable(const vector<Ingredient*>& warehouseIngredients) const
    {
        for (const auto& dishIng : ingredients)
        {
            auto ingredient = dishIng.getIngredient();
            auto warehouseIt = find_if(warehouseIngredients.begin(), warehouseIngredients.end(),
                [ingredient](Ingredient* wi) {
                    return wi->getId() == ingredient->getId();
                });

            if (warehouseIt == warehouseIngredients.end() || (*warehouseIt)->getQuantityKg() < dishIng.getQuantityKg())
            {
                return false;
            }
        }
        return true;
    }

    void display() const
    {
        cout << "ID: " << id << " | " << name << " | $" << price << endl;
        cout << "Description: " << description << endl;
        cout << "Ingredients:" << endl;

        for (const auto& ing : ingredients)
        {
            ing.display();
        }
    }

    void displaySimple() const
    {
        cout << "ID: " << id << " | " << name << " | $" << price << endl;
    }
};

class RestaurantBudget
{
private:
    double total;

public:
    RestaurantBudget(double initial = 10000.0) : total(initial)
    {
        if (initial < 0) throw InvalidInputException("Initial budget cannot be negative");
    }

    void decrease(double amount)
    {
        if (amount < 0) throw InvalidInputException("Amount to decrease cannot be negative");

        if (amount > total)
        {
            throw InsufficientFundsException("Insufficient budget. Available: $" +
                to_string(total) + ", Required: $" + to_string(amount));
        }
        total -= amount;
    }

    void increase(double amount)
    {
        if (amount < 0) throw InvalidInputException("Amount to increase cannot be negative");
        total += amount;
    }

    double getTotal() const { return total; }

    void display() const
    {
        cout << "Restaurant Budget: $" << total << endl;
    }
};

class Order
{
private:
    static int nextId;
    int id;
    vector<Dish*> dishes;
    double totalPrice;

public:
    Order() : id(nextId++), totalPrice(0) {}

    int getId() const { return id; }
    double getTotalPrice() const { return totalPrice; }
    const vector<Dish*>& getDishes() const { return dishes; }

    void addDish(Dish* dish)
    {
        if (dish == nullptr) throw InvalidInputException("Dish cannot be null");

        auto it = find_if(dishes.begin(), dishes.end(),
            [dish](Dish* d)
            {
                return d->getId() == dish->getId();
            });

        if (it != dishes.end()) {
            throw InvalidInputException("Dish " + dish->getName() + " already exists in order");
        }

        dishes.push_back(dish);
        totalPrice += dish->getPrice();
    }

    void removeDish(int dishId)
    {
        auto it = find_if(dishes.begin(), dishes.end(),
            [dishId](Dish* dish)
            {
                return dish->getId() == dishId;
            });

        if (it != dishes.end())
        {
            totalPrice -= (*it)->getPrice();
            dishes.erase(it);
        }
        else
        {
            throw NotFoundException("Dish with ID " + to_string(dishId) + " not found in order");
        }
    }

    void display() const
    {
        cout << "Order #" << id << " | Total: $" << totalPrice << endl;

        for (const auto& dish : dishes)
        {
            cout << "  - " << dish->getName() << " ($" << dish->getPrice() << ")" << endl;
        }
    }
};

int Order::nextId = 1;

class Warehouse
{
private:
    vector<Ingredient*> ingredients;

public:
    ~Warehouse()
    {
        for (auto& ing : ingredients)
        {
            delete ing;
        }
    }

    void addIngredient(Ingredient* ingredient)
    {
        if (ingredient == nullptr) throw InvalidInputException("Ingredient cannot be null");

        auto it = find_if(ingredients.begin(), ingredients.end(),
            [ingredient](Ingredient* ing)
            {
                return ing->getId() == ingredient->getId();
            });

        if (it != ingredients.end()) {
            throw InvalidInputException("Ingredient with ID " + to_string(ingredient->getId()) + " already exists");
        }

        ingredients.push_back(ingredient);
    }

    Ingredient* getIngredientById(int id)
    {
        auto it = find_if(ingredients.begin(), ingredients.end(),
            [id](Ingredient* ing)
            {
                return ing->getId() == id;
            });

        if (it == ingredients.end()) {
            throw NotFoundException("Ingredient with ID " + to_string(id) + " not found");
        }

        return *it;
    }

    vector<Ingredient*>& getIngredients() { return ingredients; }
    const vector<Ingredient*>& getIngredients() const { return ingredients; }

    bool restockIngredient(int ingredientId, double quantity, RestaurantBudget& budget)
    {
        try {
            auto ingredient = getIngredientById(ingredientId);
            if (ingredient)
            {
                double cost = quantity * ingredient->getPricePerKg();

                budget.decrease(cost);
                ingredient->increaseQuantity(quantity);
                return true;
            }
        }

        catch (const NotFoundException& e)
        {
            throw NotFoundException("Cannot restock: " + string(e.what()));
        }

        catch (const InsufficientFundsException& e)
        {
            throw InsufficientFundsException("Cannot restock: " + string(e.what()));
        }

        return false;
    }

    void consumeIngredients(const Order& order)
    {
        for (const auto& dish : order.getDishes())
        {
            for (const auto& dishIng : dish->getIngredients())
            {
                auto ingredient = dishIng.getIngredient();

                try
                {
                    auto warehouseIng = getIngredientById(ingredient->getId());
                    warehouseIng->decreaseQuantity(dishIng.getQuantityKg());
                }
                catch (const NotFoundException& e)
                {
                    throw InsufficientIngredientsException("Missing ingredient for dish " + dish->getName() + ": " + e.what());
                }
                catch (const InsufficientIngredientsException& e)
                {
                    throw InsufficientIngredientsException("Insufficient ingredients for dish " + dish->getName() + ": " + e.what());
                }
            }
        }
    }

    void display() const
    {
        cout << "=== WAREHOUSE ===" << endl;

        for (const auto& ing : ingredients)
        {
            ing->display();
        }
    }

    void displaySimple() const
    {
        cout << "=== AVAILABLE INGREDIENTS ===" << endl;
        for (const auto& ing : ingredients)
        {
            cout << "ID: " << ing->getId() << " | " << ing->getName()
                << " | " << ing->getQuantityKg() << " kg | $"
                << ing->getPricePerKg() << "/kg" << endl;
        }
    }
};

class Menu
{
private:
    vector<Dish*> dishes;
    Warehouse* warehouse;

public:
    Menu(Warehouse* wh) : warehouse(wh)
    {
        if (wh == nullptr) throw InvalidInputException("Warehouse cannot be null");
    }

    ~Menu()
    {
        for (auto& dish : dishes)
        {
            delete dish;
        }
    }

    void addDish(Dish* dish)
    {
        if (dish == nullptr) throw InvalidInputException("Dish cannot be null");

        auto it = find_if(dishes.begin(), dishes.end(),
            [dish](Dish* d)
            {
                return d->getId() == dish->getId();
            });

        if (it != dishes.end()) {
            throw InvalidInputException("Dish with ID " + to_string(dish->getId()) + " already exists");
        }

        dishes.push_back(dish);
    }

    bool removeDish(int dishId)
    {
        auto it = find_if(dishes.begin(), dishes.end(),
            [dishId](Dish* dish)
            {
                return dish->getId() == dishId;
            });

        if (it != dishes.end())
        {
            delete* it;
            dishes.erase(it);
            return true;
        }

        throw NotFoundException("Dish with ID " + to_string(dishId) + " not found");
    }

    vector<Dish*> getAvailableDishes() const
    {
        vector<Dish*> availableDishes;
        for (const auto& dish : dishes)
        {
            if (dish->isAvailable(warehouse->getIngredients()))
            {
                availableDishes.push_back(dish);
            }
        }
        return availableDishes;
    }

    Dish* getDishById(int id)
    {
        auto it = find_if(dishes.begin(), dishes.end(),
            [id](Dish* dish)
            {
                return dish->getId() == id;
            });

        if (it == dishes.end())
        {
            throw NotFoundException("Dish with ID " + to_string(id) + " not found");
        }

        return *it;
    }

    void displayAvailable() const
    {
        cout << "=== AVAILABLE DISHES ===" << endl;
        auto available = getAvailableDishes();
        for (const auto& dish : available)
        {
            dish->display();
            cout << "-------------------" << endl;
        }
    }

    void displayAll() const
    {
        cout << "=== ALL DISHES ===" << endl;
        for (const auto& dish : dishes)
        {
            dish->display();
            cout << "Available: " << (dish->isAvailable(warehouse->getIngredients()) ? "Yes" : "No") << endl;
            cout << "-------------------" << endl;
        }
    }

    void displayAllSimple() const
    {
        cout << "=== ALL DISHES ===" << endl;
        for (const auto& dish : dishes)
        {
            dish->displaySimple();
        }
    }

    int getNextDishId() const
    {
        if (dishes.empty()) return 1;
        int maxId = 0;
        for (const auto& dish : dishes)
        {
            if (dish->getId() > maxId) maxId = dish->getId();
        }
        return maxId + 1;
    }
};

class User
{
private:
    string username;
    string password;
    double budget;

public:
    User(const string& username, const string& password, double budget)
        : username(username), password(password), budget(budget)
    {
        if (username.empty()) throw InvalidInputException("Username cannot be empty");
        if (password.empty()) throw InvalidInputException("Password cannot be empty");
        if (budget < 0) throw InvalidInputException("Budget cannot be negative");
    }

    string getUsername() const { return username; }
    double getBudget() const { return budget; }

    bool checkPassword(const string& pwd) const
    {
        return password == pwd;
    }

    void decreaseBudget(double amount)
    {
        if (amount < 0) throw InvalidInputException("Amount to decrease cannot be negative");

        if (amount > budget)
        {
            throw InsufficientFundsException("Insufficient user funds. Available: $" +
                to_string(budget) + ", Required: $" + to_string(amount));
        }
        budget -= amount;
    }

    void display() const
    {
        cout << "User: " << username << " | Budget: $" << budget << endl;
    }
};

class CartItem
{
private:
    Dish* dish;

public:
    CartItem(Dish* dish) : dish(dish)
    {
        if (dish == nullptr) throw InvalidInputException("Dish cannot be null");
    }

    Dish* getDish() const { return dish; }
};

class Cart
{
private:
    vector<CartItem> items;

public:
    void addDish(Dish* dish)
    {
        if (dish == nullptr) throw InvalidInputException("Dish cannot be null");

        auto it = find_if(items.begin(), items.end(),
            [dish](const CartItem& item)
            {
                return item.getDish()->getId() == dish->getId();
            });

        if (it == items.end())
        {
            items.push_back(CartItem(dish));
        }
        else
        {
            throw InvalidInputException("Dish " + dish->getName() + " already in cart");
        }
    }

    void removeDish(int dishId)
    {
        auto it = find_if(items.begin(), items.end(),
            [dishId](const CartItem& item)
            {
                return item.getDish()->getId() == dishId;
            });

        if (it != items.end())
        {
            items.erase(it);
        }
        else
        {
            throw NotFoundException("Dish with ID " + to_string(dishId) + " not found in cart");
        }
    }

    double getTotalPrice() const
    {
        double total = 0;
        for (const auto& item : items)
        {
            total += item.getDish()->getPrice();
        }
        return total;
    }

    Order createOrder() const
    {
        if (items.empty()) {
            throw InvalidInputException("Cannot create order from empty cart");
        }

        Order order;
        for (const auto& item : items)
        {
            order.addDish(item.getDish());
        }
        return order;
    }

    void display() const
    {
        cout << "=== CART ===" << endl;
        if (items.empty()) {
            cout << "Cart is empty" << endl;
            return;
        }
        for (const auto& item : items)
        {
            cout << "ID: " << item.getDish()->getId() << " | "
                << item.getDish()->getName() << " ($"
                << item.getDish()->getPrice() << ")" << endl;
        }
        cout << "Total: $" << getTotalPrice() << endl;
    }

    void clear() { items.clear(); }
    bool isEmpty() const { return items.empty(); }

    const vector<CartItem>& getItems() const { return items; }
};

class Admin
{
private:
    string username;
    string password;

public:
    Admin(const string& username, const string& password)
        : username(username), password(password)
    {
        if (username.empty()) throw InvalidInputException("Admin username cannot be empty");
        if (password.empty()) throw InvalidInputException("Admin password cannot be empty");
    }

    bool authenticate(const string& uname, const string& pwd) const
    {
        if (username != uname || password != pwd) {
            throw AuthenticationException("Invalid admin credentials");
        }
        return true;
    }
};

class RestaurantSystem
{
private:
    Warehouse* warehouse;
    Menu* menu;
    RestaurantBudget budget;
    Admin admin;
    vector<User> users;

public:
    RestaurantSystem() : warehouse(new Warehouse()), menu(new Menu(warehouse)), budget(10000.0), admin("admin", "admin123")
    {
        try {
            users.push_back(User("user1", "pass1", 500.0));
            users.push_back(User("user2", "pass2", 300.0));

            initializeIngredients();
            initializeDishes();
        }
        catch (const exception& e) {
            delete menu;
            delete warehouse;
            throw;
        }
    }

    ~RestaurantSystem()
    {
        delete menu;
        delete warehouse;
    }

private:
    void initializeIngredients()
    {
        try {
            warehouse->addIngredient(new Ingredient(1, "Flour", 50.0, 2.0));
            warehouse->addIngredient(new Ingredient(2, "Tomato", 20.0, 3.0));
            warehouse->addIngredient(new Ingredient(3, "Cheese", 15.0, 8.0));
            warehouse->addIngredient(new Ingredient(4, "Chicken", 25.0, 6.0));
            warehouse->addIngredient(new Ingredient(5, "Rice", 40.0, 1.5));
            warehouse->addIngredient(new Ingredient(6, "Beef", 30.0, 10.0));
            warehouse->addIngredient(new Ingredient(7, "Potato", 35.0, 1.0));
            warehouse->addIngredient(new Ingredient(8, "Onion", 25.0, 1.2));
        }
        catch (const exception& e) {
            throw RestaurantException("Failed to initialize ingredients: " + string(e.what()));
        }
    }

    void initializeDishes() {
        try {
            auto pizza = new Dish(1, "Pizza", "Delicious cheese pizza", 12.99);
            pizza->addIngredient(warehouse->getIngredientById(1), 0.3);
            pizza->addIngredient(warehouse->getIngredientById(2), 0.2);
            pizza->addIngredient(warehouse->getIngredientById(3), 0.15);
            menu->addDish(pizza);

            auto chickenRice = new Dish(2, "Chicken Rice", "Tasty chicken with rice", 9.99);
            chickenRice->addIngredient(warehouse->getIngredientById(4), 0.2);
            chickenRice->addIngredient(warehouse->getIngredientById(5), 0.15);
            menu->addDish(chickenRice);
        }
        catch (const exception& e) {
            throw RestaurantException("Failed to initialize dishes: " + string(e.what()));
        }
    }

public:
    bool completeOrder(User& user, Cart& cart)
    {
        try {
            if (cart.isEmpty())
            {
                throw InvalidInputException("Cart is empty!");
            }

            double total = cart.getTotalPrice();

            user.decreaseBudget(total);
            Order order = cart.createOrder();
            for (const auto& dish : order.getDishes())
            {
                if (!dish->isAvailable(warehouse->getIngredients()))
                {
                    throw InsufficientIngredientsException("Dish '" + dish->getName() + "' is no longer available!");
                }
            }

            budget.increase(total);
            warehouse->consumeIngredients(order);
            cart.clear();

            cout << "Order completed successfully!" << endl;
            order.display();
            return true;
        }
        catch (const exception& e) {
            throw RestaurantException("Order failed: " + string(e.what()));
        }
    }

    bool adminLogin(const string& username, const string& password)
    {
        return admin.authenticate(username, password);
    }

    void adminAddDish(const string& name, const string& desc, double price, const vector<pair<int, double>>& ingredients)
    {
        try {
            int newId = menu->getNextDishId();
            auto dish = new Dish(newId, name, desc, price);

            for (const auto& ing : ingredients) {
                auto ingredient = warehouse->getIngredientById(ing.first);
                dish->addIngredient(ingredient, ing.second);
            }

            menu->addDish(dish);
            cout << "Dish added successfully with ID: " << newId << endl;
        }
        catch (const exception& e) {
            throw RestaurantException("Failed to add dish: " + string(e.what()));
        }
    }

    void adminRestockIngredient(int ingId, double quantity)
    {
        try {
            if (warehouse->restockIngredient(ingId, quantity, budget))
            {
                cout << "Ingredient restocked successfully!" << endl;
            }
        }
        catch (const exception& e) {
            throw RestaurantException("Failed to restock ingredient: " + string(e.what()));
        }
    }

    User* userLogin(const string& username, const string& password)
    {
        auto it = find_if(users.begin(), users.end(),
            [&](const User& user)
            {
                return user.getUsername() == username && user.checkPassword(password);
            });

        if (it == users.end()) {
            throw AuthenticationException("Invalid username or password");
        }

        return &(*it);
    }

    Menu* getMenu() { return menu; }
    Warehouse* getWarehouse() { return warehouse; }
    RestaurantBudget& getBudget() { return budget; }

    void displaySystemStatus() {
        cout << "\n=== SYSTEM STATUS ===" << endl;
        budget.display();
        warehouse->display();
        cout << "=====================" << endl;
    }
};

class RestaurantConsole
{
private:
    RestaurantSystem system;

public:
    void run()
    {
        try {
            while (true)
            {
                cout << "\n=== RESTAURANT MANAGEMENT SYSTEM ===" << endl;
                cout << "1. Admin Login" << endl;
                cout << "2. User Login" << endl;
                cout << "3. Exit" << endl;
                cout << "Choose option: ";

                int choice;
                cin >> choice;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number." << endl;
                    continue;
                }

                try {
                    switch (choice)
                    {
                    case 1: adminInterface(); break;
                    case 2: userInterface(); break;
                    case 3:
                        cout << "Thank you for using Restaurant Management System!" << endl;
                        return;
                    default:
                        cout << "Invalid choice! Please select 1, 2, or 3." << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Fatal error: " << e.what() << endl;
            cout << "System shutting down..." << endl;
        }
    }

private:
    void adminInterface()
    {
        string username, password;
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        try {
            if (!system.adminLogin(username, password))
            {
                cout << "Invalid credentials!" << endl;
                return;
            }

            cout << "Admin login successful!" << endl;

            while (true)
            {
                cout << "\n=== ADMIN PANEL ===" << endl;
                cout << "1. View System Status" << endl;
                cout << "2. Manage Menu" << endl;
                cout << "3. Manage Warehouse" << endl;
                cout << "4. Logout" << endl;
                cout << "Choose option: ";

                int choice;
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number." << endl;
                    continue;
                }

                try {
                    switch (choice)
                    {
                    case 1:
                        system.displaySystemStatus();
                        break;
                    case 2:
                        manageMenu();
                        break;
                    case 3:
                        manageWarehouse();
                        break;
                    case 4:
                        cout << "Admin logged out." << endl;
                        return;
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Operation failed: " + string(e.what()) << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Authentication failed: " << e.what() << endl;
        }
    }

    void manageMenu()
    {
        while (true)
        {
            cout << "\n=== MENU MANAGEMENT ===" << endl;
            cout << "1. View All Dishes" << endl;
            cout << "2. Add New Dish" << endl;
            cout << "3. Remove Dish" << endl;
            cout << "4. Back" << endl;
            cout << "Choose option: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            try {
                switch (choice)
                {
                case 1:
                    system.getMenu()->displayAll();
                    break;
                case 2:
                    addNewDish();
                    break;
                case 3:
                    removeDish();
                    break;
                case 4:
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                }
            }
            catch (const exception& e) {
                cout << "Menu operation failed: " << e.what() << endl;
            }
        }
    }

    void addNewDish()
    {
        string name, desc;
        double price;
        vector<pair<int, double>> ingredients;

        cout << "Dish name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Description: ";
        getline(cin, desc);

        system.getWarehouse()->displaySimple();

        cout << "\n=== ADD INGREDIENTS ===" << endl;
        cout << "Enter ingredient IDs one by one (enter 0 to finish):" << endl;

        while (true) {
            int ingId;
            cout << "Enter ingredient ID (0 to finish): ";
            cin >> ingId;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            if (ingId == 0) {
                break;
            }

            try {
                auto ingredient = system.getWarehouse()->getIngredientById(ingId);
                double quantity;
                cout << "Enter quantity (kg) for " << ingredient->getName() << ": ";
                cin >> quantity;

                if (cin.fail() || quantity <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid quantity! Please enter a positive number." << endl;
                    continue;
                }

                ingredients.push_back({ ingId, quantity });
                cout << "Ingredient added!" << endl;

            }
            catch (const NotFoundException& e) {
                cout << "Ingredient with ID " << ingId << " not found!" << endl;
            }
        }

        cout << "Price: ";
        cin >> price;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Invalid price format");
        }

        system.adminAddDish(name, desc, price, ingredients);
    }

    void removeDish()
    {
        system.getMenu()->displayAllSimple();

        int dishId;
        cout << "Enter dish ID to remove: ";
        cin >> dishId;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Invalid dish ID format");
        }

        try {
            if (system.getMenu()->removeDish(dishId))
            {
                cout << "Dish removed successfully!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Failed to remove dish: " << e.what() << endl;
        }
    }

    void manageWarehouse()
    {
        while (true)
        {
            cout << "\n=== WAREHOUSE MANAGEMENT ===" << endl;
            cout << "1. View Warehouse" << endl;
            cout << "2. Restock Ingredient" << endl;
            cout << "3. Back" << endl;
            cout << "Choose option: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            try {
                switch (choice)
                {
                case 1:
                    system.getWarehouse()->display();
                    break;
                case 2:
                    restockIngredient();
                    break;
                case 3:
                    return;
                default:
                    cout << "Invalid choice!" << endl;
                }
            }
            catch (const exception& e) {
                cout << "Warehouse operation failed: " << e.what() << endl;
            }
        }
    }

    void restockIngredient()
    {
        int ingId;
        double quantity;

        system.getWarehouse()->display();

        cout << "Enter ingredient ID: ";
        cin >> ingId;

        cout << "Enter quantity to add (kg): ";
        cin >> quantity;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Invalid input format");
        }

        system.adminRestockIngredient(ingId, quantity);
    }

    void userInterface()
    {
        string username, password;
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        try {
            User* user = system.userLogin(username, password);

            cout << "User login successful!" << endl;
            user->display();

            Cart cart;

            while (true)
            {
                cout << "\n=== USER PANEL ===" << endl;
                cout << "1. View Available Menu" << endl;
                cout << "2. Add Dish to Cart" << endl;
                cout << "3. View Cart" << endl;
                cout << "4. Remove Dish from Cart" << endl;
                cout << "5. Checkout" << endl;
                cout << "6. Logout" << endl;
                cout << "Choose option: ";

                int choice;
                cin >> choice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number." << endl;
                    continue;
                }

                try {
                    switch (choice)
                    {
                    case 1:
                        system.getMenu()->displayAvailable();
                        break;
                    case 2:
                        addToCart(cart);
                        break;
                    case 3:
                        cart.display();
                        break;
                    case 4:
                        removeFromCart(cart);
                        break;
                    case 5:
                        if (system.completeOrder(*user, cart)) {
                            cout << "Order completed successfully!" << endl;
                        }
                        break;
                    case 6:
                        cout << "User logged out." << endl;
                        return;
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                }
                catch (const exception& e) {
                    cout << "Operation failed: " << e.what() << endl;
                }
            }
        }
        catch (const exception& e) {
            cout << "Login failed: " << e.what() << endl;
        }
    }

    void addToCart(Cart& cart)
    {
        system.getMenu()->displayAvailable();
        int dishId;
        cout << "Enter dish ID to add: ";
        cin >> dishId;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Invalid dish ID format");
        }

        try {
            auto dish = system.getMenu()->getDishById(dishId);
            cart.addDish(dish);
            cout << "Dish added to cart!" << endl;
        }
        catch (const exception& e) {
            cout << "Failed to add dish to cart: " << e.what() << endl;
        }
    }

    void removeFromCart(Cart& cart)
    {
        cart.display();

        if (cart.isEmpty())
        {
            cout << "Cart is empty!" << endl;
            return;
        }

        int dishId;
        cout << "Enter dish ID to remove: ";
        cin >> dishId;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException("Invalid dish ID format");
        }

        try
        {
            cart.removeDish(dishId);
            cout << "Dish removed from cart!" << endl;
        }

        catch (const exception& e)
        {
            cout << "Failed to remove dish from cart: " << e.what() << endl;
        }
    }
};

int main(void)
{
    try
    {
        RestaurantConsole console;
        console.run();
    }

    catch (const exception& e)
    {
        cout << "Critical system error => " << e.what() << endl;
        return 1;
    }

    return 0;
}