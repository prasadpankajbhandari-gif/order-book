
#include <bits/stdc++.h>
using namespace std;

struct order
{
    long long id;
    int sell1buy0;      
    int noofunits;
    int price;
    int arrivalsequence;
};

map<int, list<order>> sells;

map<int, list<order>, greater<int>> buys;

struct OrderLocation
{
    bool isSell;
    int price;
    list<order>::iterator it;
};

unordered_map<long long, OrderLocation> orderIndex;


void matchOrders()
{
    while (!buys.empty() && !sells.empty())
    {
        auto buyLevel = buys.begin();
        auto sellLevel = sells.begin();

        if (buyLevel->first < sellLevel->first)
            break;

        order& b = buyLevel->second.front();
        order& s = sellLevel->second.front();

        int quantity = min(b.noofunits, s.noofunits);
        int tradePrice;

        if (b.arrivalsequence < s.arrivalsequence)
            tradePrice = b.price;
        else
            tradePrice = s.price;

        long long buyID = b.id;
        long long sellID = s.id;

        cout << "TRADE: Buy ID " << buyID
             << " with Sell ID " << sellID
             << " | Quantity: " << quantity
             << " | Price: " << tradePrice << '\n';

        b.noofunits -= quantity;
        s.noofunits -= quantity;

        if (b.noofunits == 0)
        {
            orderIndex.erase(buyID);
            buyLevel->second.pop_front();
        }
        if (s.noofunits == 0)
        {
            orderIndex.erase(sellID);
            sellLevel->second.pop_front();
        }

        if (buyLevel->second.empty())
            buys.erase(buyLevel);

        if (sellLevel->second.empty())
            sells.erase(sellLevel);
    }
}


void receiveOrder(const order& o)
{
    if (o.noofunits <= 0)
    {
        cout << "Invalid quantity\n";
        return;
    }

    if (o.sell1buy0 != 0 && o.sell1buy0 != 1)
    {
        cout << "Invalid order type\n";
        return;
    }

    if (orderIndex.count(o.id))
    {
        cout << "Duplicate order ID\n";
        return;
    }

    if (o.sell1buy0 == 1)
    {
        auto& level = sells[o.price];

        auto it = level.insert(level.end(), o);

        orderIndex.emplace(
            o.id,
            OrderLocation{true, o.price, it}
        );
    }
    else
    {
        auto& level = buys[o.price];

        auto it = level.insert(level.end(), o);

        orderIndex.emplace(
            o.id,
            OrderLocation{false, o.price, it}
        );
    }

    matchOrders();
}

bool Modifyorder(long long id, int desired_price)
{
    auto found = orderIndex.find(id);

    if(found == orderIndex.end())
    {
        cout << "Order with ID: " << id << "not found" << "\n";
        return;
    }
    bool isSell = found->second.isSell;
    int price = found->second.price;
    auto it = found->second.it;
    order sampleorder = *it;
    cancelOrder(sampleorder.id);
    sampleorder.price = desired_price;
    receiveOrder(sampleorder);
}
bool cancelOrder(long long id)
{
    auto found = orderIndex.find(id);

    if (found == orderIndex.end())
    {
        cout << "Order " << id << " not found\n";
        return false;
    }

    bool isSell = found->second.isSell;
    int price = found->second.price;
    auto it = found->second.it;

    if (isSell)
    {
        auto level = sells.find(price);

        level->second.erase(it);

        if (level->second.empty())
            sells.erase(level);
    }
    else
    {
        auto level = buys.find(price);

        level->second.erase(it);

        if (level->second.empty())
            buys.erase(level);
    }

    orderIndex.erase(found);

    return true;
}


void displayBook()
{
    cout << "\n--- SELL ORDERS (lowest price first) ---\n";

    for (auto& level : sells)
    {
        for (auto& o : level.second)
        {
            cout << "ID: " << o.id
                 << " | Price: " << o.price
                 << " | Quantity: " << o.noofunits << '\n';
        }
    }

    cout << "\n--- BUY ORDERS (highest price first) ---\n";

    for (auto& level : buys)
    {
        for (auto& o : level.second)
        {
            cout << "ID: " << o.id
                 << " | Price: " << o.price
                 << " | Quantity: " << o.noofunits << '\n';
        }
    }

    cout << '\n';
}


int main()
{
    receiveOrder({101, 1, 10, 100, 1});
    receiveOrder({102, 1, 20, 105, 2});

    receiveOrder({201, 0, 15, 110, 3});

    displayBook();

    cancelOrder(102);

    displayBook();

    return 0;
}
