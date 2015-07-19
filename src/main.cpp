#include "stdafx.h"
#include "StockTrades.h"

int main(int argc, char* argv[])
{
	StockTrades myOrder;
	std::ifstream inputfile(argv[argc - 1]);
	string line, word, id, side, price, size, level;
	while(std::getline(inputfile, line)){
		std::istringstream iss(line);
		iss >> word;
		if(word == "c"){
			iss >> id;
			iss >> side;
			iss >> price;
			iss >> size;
			if(side[0] == 'b') myOrder.StockCreateBuy(stoi(id), stod(price), stoi(size));
			else myOrder.StockCreateSell(stoi(id), stod(price), stoi(size));
		} else if(word == "u") {
			iss >> id;
			iss >> size;
			myOrder.StockUpdate(stoi(id), stoi(size));
		} else if(word == "d") {
			iss >> id;
			myOrder.StockDelete(stoi(id));
		} else if(word == "tp") {
			iss >> side;
			iss >> level;
			if(side[0] == 'b') cout << myOrder.RetrieveMaxPriceBuy(stoi(level)) << endl;
			else cout << myOrder.RetrieveMinPriceSell(stoi(level)) << endl;
		} else if(word == "ts") {
			iss >> side;
			iss >> level;
			if(side[0] == 'b') cout << myOrder.RetrieveMaxPriceBuyInventory(stoi(level)) << endl;
			else cout << myOrder.RetrieveMinPriceSellInventory(stoi(level)) << endl;
		} else {
			cout << "undefined instruction. Stop" << endl;
			exit(1);
		}
	}
	return 0;
}

