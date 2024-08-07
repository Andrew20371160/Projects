8/7/2024 (thesse aren't upadtes I've redesigned the whole project)
will post updates tomorrow.
if you are intested you can run and test for yourself 
I've introduced a wiring system so all previous problems are gone.
saving and loading with wiring of the whole system saved aswell.

feel free to use any code.

7/28/2024 huge updates:
1-added save and load 
  save allows you to save the whole board in a series of trees (check the documentation)
  load allows you to load one component at a time and append it to the tree
  will be adding a series of youtube videos where i try to implement a desing of a 4-bit microprocessor 
  which was a task I had in college 
  this would be the ultimate test of the software 

2-fixed a bug in load which caused a segmentation fault if you load one leaf (my bad)

3-half_adder0,1 are the sum and carry unit of the half adder i've built them and tested them 
you load twice one for the left and one for the right (0&1)
you have to enter input for a,b where a , b are input pins 3 times 

it's not the best simulation but it works :) 

4-if you found any bugs please let me know 

5-feel free to use any code :)

7/25/2024 update :
1-fixed an issue where if you append a gate from the right if there is a parent gate it's array of booeans wasn't deleted
(it gets deleted anyway in the remove function)

7/23/2024 update :
1-fixed a memory leak that would be caused if you removed the root node
2-added xnor and buffer gates


The idea of the project revolves around digital logic design. It aims to provide a board or graph where you can design some complex logic components (as close as it can to real-life).

from logic gates : and, or, not... ....etc

In the main you can find a testing code that I've made.

I've fixed and eliminated a lot of segmentation faults and memory leaks; it's stable now (though if there is a segmentation fault, please let me know).

This is still in beta, and I will add more updates to it

One of the updates I want to make is the ability to save and load a component after designing it to reuse it.

Feel free to use any code :)
