#from trade import Trade
import heapq as hq

class Exchange:
    # implement this!

    def __init__(self, initialBalance):
        """Initial Balance is the amount that each account should start with."""
        self.balances = {}
        self.positions = {}
        self.initBalance = initialBalance
        self.bids = [] #represented with negatives to make the queue easier to work with
        self.asks = []

    def add_trade(self, trade):
        """Adds a trade to the exchange (validation required)
        and returns a match if required. It is up to you on how you will
        handle representing trades. 
        trade will be : (price, quantity, trader)
        The sign of the price will determine bid or ask
        Assumes all inputs are well formed and dont need to be checked
        """
        price = trade[0]
        quantity = trade[1]
        trader = trade[2]
        if not trader in self.balances.keys():
            self.balances[trader] = self.initBalance

        if not trader in self.positions.keys():
            self.positions[trader] = 0

        # handle if it is a sell:
        # positive price is sell since we want smallest sell price to be enqueued in front
        
        if price > 0:
            # check if it meets any current bid prices
            # otherwise enqueue it
            if len(self.bids) > 0:
                bestbidtrade = self.bids[0]
                bestbid = abs(bestbidtrade[0])
                while bestbid > price and quantity > 0:
                    actionqty = min(quantity, bestbidtrade[1])
                    quantity -= actionqty
                    self.bids[0] = (bestbidtrade[0], bestbidtrade[1] - actionqty, bestbidtrade[2])
                    bestbidtrade = self.bids[0]
                    self.balances[trader] += actionqty*bestbid
                    self.positions[trader] -= actionqty #selling stock
                    self.balances[bestbidtrade[2]] -= actionqty*bestbid
                    self.positions[bestbidtrade[2]] += actionqty #buying stock

                    if bestbidtrade[1] == 0:
                        hq.heappop(self.bids)
                        if len(self.bids) > 0:
                            bestbidtrade = self.bids[0]
                            bestbid = abs(bestbidtrade[0])
                        else:
                            break
                    else: 
                        break
                
                # no more existing trades to match to
                # add the sell to the asks
            if quantity > 0:
                hq.heappush(self.asks, (price, quantity, trader))

        # handle if it is a buy:
        # negative price is buy since we want largest magnitude buy price to be enqueued in front
        
        else:
            # price <= 0
            # check if it meets any current ask prices
            # otherwise enqueue it
            if len(self.asks) > 0:
                bestasktrade = self.asks[0]
                bestask = abs(bestasktrade[0])
                while bestask < abs(price) and quantity > 0:
                    actionqty = min(quantity, bestasktrade[1])
                    quantity -= actionqty
                    self.asks[0] = (bestasktrade[0], bestasktrade[1] - actionqty, bestasktrade[2])
                    bestasktrade = self.asks[0]
                    self.balances[trader] -= actionqty*bestask
                    self.positions[trader] += actionqty # buying stock
                    self.balances[bestasktrade[2]] += actionqty*bestask
                    self.positions[bestasktrade[2]] -= actionqty #selling stock

                    if bestasktrade[1] == 0:
                        hq.heappop(self.asks)
                        if len(self.asks) > 0:
                            bestasktrade = self.asks[0]
                            bestask = abs(bestasktrade[0])
                        else:
                            break
                    else: 
                        break
                
                # no more existing trades to match to
                # add the sell to the asks
            if quantity > 0:
                hq.heappush(self.bids, (price, quantity, trader))

def main():
    ex = Exchange(0)
    for i in range(50):
        price = float(input("enter price"))
        quantity = int(input("enter qty"))
        trader = input("enter trader name")
        ex.add_trade((price, quantity, trader))
        print(f"balances {ex.balances}")
        print(f"positions: {ex.positions}")
        print(f"bids: {ex.bids}")
        print(f"asks: {ex.asks}")
        


if __name__ == "__main__":
    main()