#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "market.h"
#include "user.h"
#include "order.h"
#include "stock.h"

Market *newMarket(char name[], int nstocks, int nusers, int norders){
  Market *market; 
  market = malloc(sizeof(Market));
  strcpy(market->name, name);
  market->nstocks = nstocks;
  market->nusers = nusers;
  market->norders_buy = norders;
  market->norders_sell = norders;
  market->stocks = malloc(sizeof(Stock)*nstocks);
  market->users = malloc(sizeof(User)*nusers);
  market->orders_buy = malloc(sizeof(Order)*norders);
  market->orders_sell = malloc(sizeof(Order)*norders);
  market->index_stock = 0;
  market->index_user = 0;
  market->index_order_buy = 0;
  market->index_order_sell = 0;
  return market;
}

int addStock(Market *market, Stock stock){
  market->stocks[market->index_stock] = stock;
  market->index_stock++;
  return 1;
}

int addUser(Market *market, User user){
  market->users[market->index_user] = user;
  market->index_user++;
  return 1;
}
//returns the number of stocks bought by the user.
int buy_OPI(Stock *stock, User *user, int nstocks, float value){
  if (nstocks > stock->nstocks && stock->nstocks > 0) {
    nstocks = stock->nstocks;
  if (user->money >= nstocks*value){
    user->money -= nstocks*value;
    stock->nstocks -= nstocks;
    insert(user,stock->code,nstocks);
    return nstocks;
  }else{
    return 0;
  }
  }else{
    return 0;
  }
}

void printMarket(Market *market){
  printf("Stocks:\n");
  for(int i=0; i < market->index_stock; i++){
    printf("%s\t%f\t%i\n",market->stocks[i].code,market->stocks[i].price,market->stocks[i].nstocks);
  }
  printf("Users:\n");
  for(int i=0; i < market->index_user; i++){
    printf("%i\t%f\n",market->users[i].index, market->users[i].money);
    printMap(market->users[i]);
  }
}

int closeMarket(Market *market){
  free(market->stocks);
  free(market->users);
  free(market->orders_buy);
  free(market->orders_sell);
  free(market);
  return 1;
}
int remain_stocks(Market market) {
    for (int i = 0; i < market.index_stock; i++) {  // Recorre los stocks
        if (market.stocks[i].nstocks > 0) {         // Verifica si hay stocks disponibles
            return 1;  // Si hay algún stock, retorna 1
        }
    }
    return 0;  // Si todos los stocks son 0, retorna 0
}

