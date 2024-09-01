9/1/2024 fixed issues regarding indexing of files while saving and loading 
added new components will upload the new video soon.
8/31/2024 fixed a major bug where gates initialized with zero number of pins would take a garbage value as input size
also fixed some issues regarding evaluating input of certain gates


8/12/2024 small update:
added some input validation so that the system doesn't crash due to minor reasons.

8/10/2024 : Posted the first video in the series of creating a 4-bit microprocessor ALU check it out here:
https://www.youtube.com/watch?v=gNgUllowSiA&list=PLbDnyrrfgzH4v5_NiBz46QS6W0CPb2-qB

8/9/2024 updates : added edit which allows you to resize input size or edit gate type.
also yesterday I've eliminated some bugs which caused unsuccessful loading of the system now works fine.

8/7/2024 updates :
1-introduced a wiring system so that you don't have to repeat a component
for ex : in the half_adder you have "OR" which is the sum and "and" which is the carry 
now you can connect the wire from "a" ,"b" to the carry and it behaves as normal logic gates.

2-made a separation between gate ,graph classes so that gate issues are handled in a separate class and now the code is way better , readable and most importantly maintainable.

3-save,load say you made a component with its wiring now the whole component is saved into files ,and 
the wiring of the whole system 
-save function saves each major tree of the graph into a list of .txt files and then saves the wiring (if exists) into a separate file.
-load function now loads the whole component (from each file with same name for ex: path\ha0.txt ,path\ha1.txt...etc) where from each file it loads the major tree and then append it to the right of the component's root and it handles the wiring of the loaded component, if the board is empty then root of the graph is assigned the new component else you can append the component as a child or to the right of an existing node in the board.

4-you can have a gate with no input but wires connected to it as a source of input.

5-I've tried it last night it was so good.

6-added documentation to header 


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
