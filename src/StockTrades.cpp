#include "stdafx.h"
#include "StockTrades.h"

StockTrades::StockTrades() {
	BuyHistory.reserve(10000);
	SellHistory.reserve(10000);
	SideHistory.reserve(10000);
	MapHistory.reserve(10000);
	BuyHistory.push_back(Bargain(0, 0.0, 0));
	SellHistory.push_back(Bargain(0, 0.0, 0));
	SideHistory.resize(1);
	MapHistory.resize(1);
}

StockTrades::~StockTrades() {
}

void StockTrades::StockCreateBuy(const int &id, const double &price, const int &size) {
	BuyHistory.push_back(Bargain(id, price, size));
	SideHistory.push_back('B');
	MapHistory.push_back(BuyHistory.size() - 1);
	if(BuyPrice2Rank.find(price) == BuyPrice2Rank.end()) BuyPrice2Rank.insert(std::make_pair(price, 1));
	else BuyPrice2Rank[price] += 1;
	BuyPrice2Inventory[price] += size;
}

void StockTrades::StockCreateSell(const int &id, const double &price, const int &size) {
	SellHistory.push_back(Bargain(id, price, size));
	SideHistory.push_back('S');
	MapHistory.push_back(SellHistory.size() - 1);
	if(SellPrice2Rank.find(price) == SellPrice2Rank.end()) SellPrice2Rank.insert(std::make_pair(price, 1));
	else SellPrice2Rank[price] += 1;
	SellPrice2Inventory[price] += size;
}

void StockTrades::StockUpdate(const int &id, const int &new_size) {
	if(SideHistory[id] == 'B') {
		BuyPrice2Inventory[BuyHistory[MapHistory[id]].price] += new_size - BuyHistory[MapHistory[id]].size;
		BuyHistory[MapHistory[id]].size = new_size;
	}
	if(SideHistory[id] == 'S') {
		SellPrice2Inventory[SellHistory[MapHistory[id]].price] += new_size - SellHistory[MapHistory[id]].size;
		SellHistory[MapHistory[id]].size = new_size;
	}
	return;
}

void StockTrades::StockDelete(const int &id) {
	if(SideHistory[id] == 'B') {
		BuyHistory[MapHistory[id]].id = 0;
		BuyPrice2Inventory[BuyHistory[MapHistory[id]].price] -= BuyHistory[MapHistory[id]].size;
		if(BuyPrice2Inventory[BuyHistory[MapHistory[id]].price] == 0) BuyPrice2Inventory.erase(BuyHistory[MapHistory[id]].price);
		if(BuyPrice2Rank[BuyHistory[MapHistory[id]].price] == 1) BuyPrice2Rank.erase(BuyHistory[MapHistory[id]].price);
		else --BuyPrice2Rank[BuyHistory[MapHistory[id]].price];
	}
	if(SideHistory[id] == 'S') {
		SellHistory[MapHistory[id]].id = 0;
		SellPrice2Inventory[SellHistory[MapHistory[id]].price] -= SellHistory[MapHistory[id]].size;
		if(SellPrice2Inventory[SellHistory[MapHistory[id]].price] == 0) SellPrice2Inventory.erase(SellHistory[MapHistory[id]].price);
		if(SellPrice2Rank[SellHistory[MapHistory[id]].price] == 1) BuyPrice2Rank.erase(SellHistory[MapHistory[id]].price);
		else --SellPrice2Rank[SellHistory[MapHistory[id]].price];
	}
	return;
}

double StockTrades::RetrieveMaxPriceBuy(const int &rank) {
	auto i = BuyPrice2Rank.end();
	std::advance(i, -rank);
	return i->first;
}

double StockTrades::RetrieveMinPriceSell(const int &rank) {
	auto i = SellPrice2Rank.begin();
	std::advance(i, rank - 1);
	return i->first;
}

int StockTrades::RetrieveMaxPriceBuyInventory(const int &rank) {
	auto i = BuyPrice2Rank.end();
	std::advance(i, -rank);
	return BuyPrice2Inventory[i->first];
}

int StockTrades::RetrieveMinPriceSellInventory(const int &rank) {
	auto i = SellPrice2Rank.begin();
	std::advance(i, rank - 1);
	return SellPrice2Inventory[i->first];
}