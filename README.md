# Shopping-List
The program takes in a sequence of store inventories and containerizes it for later use. Then, using an inputted shopping list, the program determines the best deal possible based on the list.

The format for the stores' inventories:

4 Stores:
Local Grocery
East Lansing
Apples,10,$4.76
Sandwich,2,$1.99
Olive Bread,3,$2.99
Milk,7,$1.25
Eggs,40,$0.78
Candy,4,$0.51

Electronics R Here
Ann Arbor
Bargain Phone,2,$200.00
S Phone,4,$650.00
Fruit Phone,2,$700.00

Corner Store
East Lansing
Milk,30,$2.00
Eggs,2,$0.50
Candy,6,$1.00
Soda,5,$1.56
Bargain Phone,3,$185.00

Sparty's
East Lansing
Candy,10,$0.85
Soda,4,$1.50
Sandwich,3,$2.99

The first line of each store is the store's name, the next line is the store's location. The rest of the lines (before the blank line) is the inventory. For each inventory line, there is the item's name, the quantity, and the price.

After reading in the store information, the program outputs a summary with two sections: store related information and item related information.

After reading in the lsit of desired items the porgram then determines the best deal possible based on what's available in the inventory. For each item, I want to get the best deal possible, even if that means going to different stores.

For example, if I want to buy 15 of one item, I would need to go to the store with the cheapest option for that item and buy from them. If they don't have enough to satisfy the amount specified from the list, then go to the next cheapest place and buy from them and continue the process until satisfied. The porgram also determines the cumulative cost throughout the process.

Example Input:

3 items on my shopping list:
15 Candy
100 Soda
1 S Phone

Example Output:

Shopping:
Trying to order 15 Candy(s).
3 store(s) sell Candy.
Total price: $11.54
Order 4 from Local Grocery in East Lansing
Order 10 from Sparty's in East Lansing
Order 1 from Corner Store in East Lansing

Trying to order 100 Soda(s).
2 store(s) sell Soda.
Total price: $13.80
Order 4 from Sparty's in East Lansing
Order 5 from Corner Store in East Lansing

Trying to order 1 S Phone(s).
1 store(s) sell S Phone.
Total price: $650.00
Order 1 from Electronics R Here in Ann Arbor

Be sure to bring $675.34 when you leave for the stores.
