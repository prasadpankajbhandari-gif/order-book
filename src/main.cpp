#include<bits/stdc++.h>
using namespace std;

struct order
{
    long long id;
    int sell1buy0;
    int noofunits;
    int price;
    int arrivalsequence;
    void printdetails()
    {
        if(sell1buy0 == 0)
        {
        cout << "orderid: " << id << "\n";
        cout << "this is buy order" << "\n";
        cout << "maximum price to buy: " << price << "\n";
        cout << "no of units: " << noofunits << "\n";
        cout << "details complete" << "\n" << "\n";
        }
        else
        {
        cout << "orderid: " << id << "\n";
        cout << "this is sell order" << "\n";
        cout << "minimum price to sell: " << price << "\n";
        cout << "no of units: " << noofunits << "\n";
        cout << "details complete" << "\n" << "\n";
        }
    }
};

template <typename SellPQ, typename BuyPQ>
void checktradepossibilty(SellPQ& sellorders, BuyPQ& buyorders)
{
    while (!buyorders.empty() && !sellorders.empty() &&
           buyorders.top().price >= sellorders.top().price)
    {
        order b = buyorders.top();   buyorders.pop();
        order s = sellorders.top();  sellorders.pop();

        int qty = min(b.noofunits, s.noofunits);

        int tradePrice = (b.arrivalsequence < s.arrivalsequence) ? b.price : s.price;

        cout << "TRADE: buy " << b.id << " / sell " << s.id
             << " | " << qty << " units @ " << tradePrice << "\n";

        b.noofunits -= qty;
        s.noofunits -= qty;

        if (b.noofunits > 0) buyorders.push(b);
        if (s.noofunits > 0) sellorders.push(s);
    }
    cout << "all possible transactions already done\n\n";
}



int main(void)
{
    auto cmp1 = [](const order& a, const order&b)
    {
        if(a.price == b.price)
        {
            return a.arrivalsequence > b.arrivalsequence;
        }
        return a.price < b.price;
    };
    auto cmp2 = [](const order& a, const order&b)
    {
        if(a.price == b.price)
        {
            return a.arrivalsequence > b.arrivalsequence;
        }
        return a.price > b.price;
    };
    priority_queue <order, vector <order>, decltype(cmp2)> qsell(cmp2);
    priority_queue <order, vector <order>, decltype(cmp1)> qbuy(cmp1);
    struct order o1;
    o1.id = 50;
    o1.sell1buy0 = 1;
    o1.noofunits = 30;
    o1.price = 100;
    o1.arrivalsequence = 0;
    qsell.push(o1);
    struct order o3;
     o3.id = 52;
    o3.sell1buy0 = 1;
    o3.noofunits = 30;
    o3.price = 100;
    o3.arrivalsequence = 1;
    qsell.push(o3);
    struct order o4;
    o4.id = 51;
    o4.sell1buy0 = 0;
    o4.noofunits = 4;
    o4.price = 67;
    o4.arrivalsequence = 4;
    qbuy.push(o4);
    struct order o2;
    o2.id = 51;
    o2.sell1buy0 = 0;
    o2.noofunits = 4;
    o2.price = 67;
    o2.arrivalsequence = 3;
    qbuy.push(o2);

    checktradepossibilty(qsell, qbuy);
    while(!qsell.empty())
    {
        struct order orders = qsell.top();
        qsell.pop();
        orders.printdetails();
    }
    while(!qbuy.empty())
    {
        struct order orders = qbuy.top();
        qbuy.pop();
        orders.printdetails();
    }
}
