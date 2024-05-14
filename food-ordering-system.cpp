#include <iostream>
#include <string>
using namespace std;

int const MENU_SIZE = 100;
int const CART_SIZE = 100;
int const ORDER_SIZE = 100;

struct menuItem
{
    int ID = 0;
    string name = "";
    double price = 0.0;
    bool isAvailable = false;
};

class Menu
{
public:
    menuItem list[MENU_SIZE];
    static int ID;

    void displayMenu()
    {
        cout << "\nMENU ITEMS: " << endl;

        bool isMenuEmpty = true;

        for (int i = 0; i < MENU_SIZE; i++)
        {
            if (list[i].ID == 0)
                continue;

            cout << "\n\t\tID: " << list[i].ID << endl
                 << "\t\tName: " << list[i].name << endl
                 << "\t\tPrice: " << list[i].price << endl
                 << "\t\tAvailability: " << (list[i].isAvailable ? "Yes" : "No") << endl;
            isMenuEmpty = false;
        }

        if (isMenuEmpty)
            cout << "\n\t\tNo items in Menu to show" << endl;
        cout << endl;
    }

    void addItemToMenu()
    {
        int i = 0;
        while (i < MENU_SIZE && list[i].ID != 0)
            i++;

        if (i == MENU_SIZE)
        {
            cout << "\n\t\tMenu is already full!" << endl;
            return;
        }

        menuItem item;

        item.ID = ++ID;

        cout << "\n\t\tEnter the name of the item: ";
        cin >> item.name;

        cout << "\t\tEnter the price of the item: ";
        cin >> item.price;

        cout << "\t\tIs the item available? (1 for yes, 0 for no): ";
        cin >> item.isAvailable;

        list[i] = item;
    }

    void deleteItemFromMenu()
    {
        if (list[0].ID == 0)
        {
            cout << "\n\t\tNothing there in menu to delete!" << endl;
            return;
        }

        int ID;

        cout << "\n\t\tEnter the ID of the item you want to delete: ";
        cin >> ID;

        bool isItemFound = false;
        int i = 0;
        while (i < MENU_SIZE)
        {
            if (list[i].ID == ID)
            {
                isItemFound = true;
                break;
            }
            i++;
        }

        if (!isItemFound)
        {
            cout << "\n\t\tItem not found with this ID!" << endl;
            return;
        }

        list[i].ID = 0;
        cout << "\n\t\tItem deleted successfully!" << endl;
    }

    void updateItemInMenu()
    {
        if (list[0].ID == 0)
        {
            cout << "\n\t\tNothing there in menu to delete!" << endl;
            return;
        }

        int ID;

        cout << "\n\t\tEnter the ID of the item you want to update: ";
        cin >> ID;

        bool isItemFound = false;
        int i = 0;
        while (i < MENU_SIZE)
        {
            if (list[i].ID == ID)
            {
                isItemFound = true;
                break;
            }
            i++;
        }

        if (!isItemFound)
        {
            cout << "\n\t\tItem not found with this ID!" << endl;
            return;
        }

        cout << "\t\tEnter the new price of the item: ";
        cin >> list[i].price;

        cout << "\t\tIs the item available? (1 for yes, 0 for no): ";
        cin >> list[i].isAvailable;

        cout << "\n\t\tItem deleted successfully!" << endl;
    }
};

int Menu::ID = 11000;

class Cart
{
public:
    int cart[CART_SIZE];
    int TOP;

    Cart()
    {
        TOP = -1;
    }

    void viewCart()
    {
        cout << "\n\t\tItems in Cart: " << endl;

        if (TOP == -1)
        {
            cout << "\n\t\tNo items in Cart to show" << endl;
            return;
        }

        int i = 0;
        while (i <= TOP)
        {
            if (cart[i] != 0)
                cout << "\t\t" << cart[i] << endl;

            i++;
        }
    }

    void addItemToCart(Menu &menu)
    {
        if (TOP == CART_SIZE - 1)
        {
            cout << "\t\tCart is already full!" << endl;
            return;
        }

        int ID = 0;

        cout << "\n\t\tEnter the ID of the item you want to add to cart: ";
        cin >> ID;

        while (ID == 0)
        {
            cout << "\t\tItem ID can't be zero. Enter again: ";
            cin >> ID;
        }

        bool isItemFound = false;
        int i = 0;
        while (i < MENU_SIZE)
        {
            if (menu.list[i].ID == ID)
            {
                isItemFound = true;
                break;
            }

            i++;
        }

        if (!isItemFound)
        {
            cout << "\n\t\tItem not found in menu with this ID!" << endl;
            return;
        }

        if (!menu.list[i].isAvailable)
        {
            cout << "\n\t\tItem is not available to purchase!" << endl;
            return;
        }

        TOP++;
        cart[TOP] = ID;
        cout << "\n\t\tItem added to cart successfully!" << endl;
    }

    void deleteItemFromCart()
    {
        if (TOP == -1)
        {
            cout << "\t\tCart has no item to delete!" << endl;
            return;
        }

        TOP--;
        cout << "\n\t\tItem deleted from top of cart successfully!" << endl;
    }

    void clearAllCart()
    {
        if (TOP < 0)
        {
            cout << "\n\t\tCart is already empty!" << endl;
            return;
        }

        TOP = -1;

        cout << "\n\t\tCart is cleared successfully!" << endl;
    }
};

struct orderDetails
{
    int ID = 0;
    string customerName = "GUEST";
    int itemsOrderedIDs[ORDER_SIZE] = {0};
    double totalAmount = 0.0;
    string status = "Pending";
};

class Order
{
public:
    orderDetails list[ORDER_SIZE];
    int FRONT = -1, REAR = -1;
    static int ID;

    void placeAnOrder(Cart &cart, Menu &menu)
    {
        if (cart.TOP < 0)
        {
            cout << "\nCart is empty! Please add items to cart first." << endl;
            return;
        }

        if (REAR >= ORDER_SIZE - 1)
        {
            cout << "\nMaximum orders already placed! Cannot place more orders." << endl;
            return;
        }

        orderDetails newOrder;

        newOrder.ID = ++ID;

        cout << "\n\t\tEnter the name of the customer: ";
        cin >> newOrder.customerName;

        for (int i = 0; i <= cart.TOP; i++)
        {
            newOrder.itemsOrderedIDs[i] = cart.cart[i];

            int j = 0;
            while (j < MENU_SIZE && menu.list[j].ID != cart.cart[i])
            {
                j++;
            }

            newOrder.totalAmount += menu.list[j].price;
        }

        if (FRONT == -1)
            FRONT++;

        REAR++;
        list[REAR] = newOrder;

        cart.TOP = -1;

        cout << "\n\t\tOrder placed successfully!" << endl;
    }

    void processAnOrder()
    {
        if (FRONT == -1)
        {
            cout << "\n\t\tNo orders to process!" << endl;
            return;
        }

        list[FRONT].status = "Processed";

        FRONT++;

        cout << "\n\t\tOrder processed successfully!" << endl;
    }

    void displayProcessedOrders()
    {
        if (FRONT < 0)
        {
            cout << "\n\t\tNo orders processed yet!" << endl;
            return;
        }

        cout << "\nProcessed Orders: " << endl;

        bool isProcessedOrderFound = false;

        for (int i = 0; i < ORDER_SIZE; i++)
        {
            if (list[i].status == "Pending")
                return;

            cout << "\n\t\tOrder No: " << list[i].ID << endl
                 << "\t\tCustomer Name: " << list[i].customerName << endl
                 << "\t\tTotal Amount: " << list[i].totalAmount << endl
                 << "\t\tStatus: " << list[i].status << endl
                 << "\t\tItems: " << endl;

            for (int j = 0; j < ORDER_SIZE; j++)
            {
                if (list[i].itemsOrderedIDs[j] == 0)
                    continue;

                cout << "\t\t" << list[i].itemsOrderedIDs[j] << endl;
            }
            isProcessedOrderFound = true;
        }

        if (!isProcessedOrderFound)
            cout << "\n\t\tNo orders processed yet!" << endl;
    }
};

int Order::ID = 99000;

int main()
{
    cout << "\n*** Welcome to Food Ordering System ***" << endl;

    Menu menu;
    Cart cart;
    Order order;

    int choice;
    do
    {
        cout << "\nMAIN MENU:" << endl
             << "\t1.\tDisplay Menu" << endl
             << "\t2.\tAdd Item to Menu" << endl
             << "\t3.\tDelete Item From Menu" << endl
             << "\t4.\tUpdate Item in Menu" << endl
             << "\t5.\tView Cart" << endl
             << "\t6.\tAdd Item to Cart" << endl
             << "\t7.\tDelete Item From Cart" << endl
             << "\t8.\tClear All Cart" << endl
             << "\t9.\tPlace An Order" << endl
             << "\t10.\tProcess An Order" << endl
             << "\t11.\tDisplay Processed Orders" << endl
             << "\t0.\tExit the Program" << endl
             << endl
             << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            menu.displayMenu();
            break;
        case 2:
            menu.addItemToMenu();
            break;
        case 3:
            menu.deleteItemFromMenu();
            break;
        case 4:
            menu.updateItemInMenu();
            break;
        case 5:
            cart.viewCart();
            break;
        case 6:
            cart.addItemToCart(menu);
            break;
        case 7:
            cart.deleteItemFromCart();
            break;
        case 8:
            cart.clearAllCart();
            break;
        case 9:
            order.placeAnOrder(cart, menu);
            break;
        case 10:
            order.processAnOrder();
            break;
        case 11:
            order.displayProcessedOrders();
            break;
        case 0:
            break;
        default:
            cout << "\nInvalid choice! Please enter a valid choice." << endl;
            break;
        }

        if (choice != 0)
        {
            cout << "\nEnter 99 to go to main menu again or 0 to exit: ";
            cin >> choice;
        }
    } while (choice != 0);

    cout << "\n*** Thank you for using Food Ordering System! ***" << endl
         << endl;

    return 0;
}