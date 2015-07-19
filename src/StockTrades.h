#include "stdafx.h"

class Bargain {
public:
				Bargain(const int &newid, const double &newprice, const int &newsize) : id(newid), price(newprice), size(newsize) {};
	virtual		~Bargain() {};
	unsigned	id;
	double		price;
	int			size;
};


class StockTrades {
public:
				StockTrades();
	virtual		~StockTrades();
	void		StockCreateBuy(const int &id, const double &price, const int &size);
	void		StockCreateSell(const int &id, const double &price, const int &size);
	void		StockUpdate(const int &id, const int &new_size);
	void		StockDelete(const int &id);
	double		RetrieveMaxPriceBuy(const int &rank);
	double		RetrieveMinPriceSell(const int &rank);
	int			RetrieveMaxPriceBuyInventory(const int &rank);
	int			RetrieveMinPriceSellInventory(const int &rank);
private:
	vector<Bargain>		BuyHistory;
	vector<Bargain>		SellHistory;
	vector<char>		SideHistory;
	vector<unsigned>	MapHistory;
	map<double, int>	BuyPrice2Rank;
	map<double, int>	SellPrice2Rank;
	map<double, int>	BuyPrice2Inventory;
	map<double, int>	SellPrice2Inventory;
};