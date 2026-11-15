# PA2 Reflection

## 1. Every function I wrote (TODO 1–19)

TODO 1 – Scene constructor. The constructor takes the scene’s data and its number of choices.
If the scene has at least one choice, it creates an array of exactly numChoices empty slots for the child scenes.
Every slot is set to nullptr, because new leaves garbage addresses in them, and the destructor would crash trying to delete garbage.
The loop runs at most 3 times because MAX_CHOICES is 3, so it doesn’t grow with the number of scenes: O(1).

TODO 2 - Scene destructor. The destructor frees the memory the scene owns. Starting with the child, then the slot, then the data. Deleting one scene frees the entire subtree.
Order matters, if you delete the array first then the pointers to the children would have no connection and would lead to a leak.
Deleting one scene is just O(1) simple, since at most that scene will have 3 choice slots. Depending on where the scene is the time will change.
If you delete the root for example, it will be O(n) time since the entire subtree would also be gone.

TODO 3 - isEnding. very simple, check if the number of choices available is 0, return true if it is, end. Runs to O(1) time.

TODO 4 - getChoice. Another simple one, checks if the array is out of bounds, that is if the index it is less than 0 or greater than or equal to number of choices. Returns nullptr if true.
Otherwise it returns the child scene stored in that slot. Runs constant time always, O(1).

TODO 5 - setChoice. Checks that the index is a valid slot. If it's out of bounds, it does nothing.
Otherwise it stores the given child scene into that slot. readScene uses this to plug in each child. Runs constant time, O(1).

TODO 6 - countScenes. This function uses recursion and counts every scene from the scene down. The base case is when the scene is nullptr, meaning there's no scene at that choice, and it returns 0.
Otherwise, it counts this scene as valid, uses a +1 to mark it, then calls itself and adds the counts from the other choices. On my story this gives 24 scenes. It runs to O(n) time.

TODO 7 - countEndings. Similar to previous, first checks for if the scene points to null, returns 0. then if the scene is a ending, meaning leaf, returns a 1.
After, it recursively calls itself and gets the ending choices from the other branches, adds them up to return the overall value of how many endings the story has. On my story this gives 10 endings.
Runs to O(n) time.

TODO 8 - height. This function finds the tallest branch of our tree. From root to ending. First checks if theres anything at all, if empty returns -1 since theres no height.
Otherwise, it gets the height of each subtree, and assigns a variable to the tallest of them + 1. The + 1 is to include the choice that leads into the subtree.
My story's height is 8. Each scene gets visited once, runs to O(n) time.

TODO 9 - clear. Very simple function, deletes the root, causing the entire subtree to be deleted as well. Assigns the root to point to null.
Also assigns root to nullptr for memory cleanup instead of having garbage assigned to root. Because it deletes everything, it goes to O(n) time.

TODO 10 - load. Opens the story file and generates the tree. If file does not open, prints a error, returns false. Next, uses readField to read the starting hp.
Converts that number into the startHp. Then the function calls read scene which recursively reads the entire story and returns the root. If anything in the file is invalid,
it returns nullptr so the load returns false. Otherwise, it gives the root to the tree using setRoot. Everything else is constant, but readScene reads all n scenes, so overall O(n).

TODO 11 - readScene. This function reads the specific scenes lines in order: scene, hp, loot, item, choices. If a line is missing or wrong, returns nullptr.
Then the function checks that the choices are between 0 and 3, if not returns nullptr. Then creates the moment and scene in memory.
For each choice, it checks the label line, and calls itself to read the child scene. Each child is stored with setChoice after its read.
If a child fails to load, it deletes the scene, which also frees any children already stored in its slots, and returns nullptr, so nothing leaks.
O(n) complexity it runs once per scene with a fixed amount of work.

TODO 12 - askChoice. Simple function, asks the user for their choice, reads with getline. If input ends, it returns 0.
Checks the input isnt empty and is at most 9 chars, all digits. Converts the input and checks if it is between 1 and num choices. if valid
returns the number, else reprompts. Runs to O(1) time, doesnt change with n size.

TODO 13 - play. The actual function in charge of playing the game. Starting at the root with the start hp, loot at 0. and empty bag list.
adds the scene hp everytime a new scene is entered, also the loot. prints dashes and text. Prints the hp and loot as well.
Checks if HP is <= 0, prints game over. if it is a end scene, prints the end. checks for death first. Else it prints the choice labels.
Prints HP loot and inventory at the end. It runs in a loop, where the height is checked, which will at most equal n, and also the items in the bag are searched.
this is in another O(n), together in the worst case scenario it runs to O(n^2).

TODO 14 - printStats. Calls the count scenes, endings, and height. Prints the three statistics. Each call is in O(n) so the overall is 3n giving O(n).

TODO 15 - printSpoilers. Simple function, it starts the printEndings at the root with a empty path so the entire subtree of root gets printed.
This is in O(n) time.

TODO 16 - printEndings. First checks if scene is null and prints nothing. Else, it checks if the scene is an ending, prints the path for it. Otherwise it recursively calls itself for each choice tree, calls it in order and prints before the next list.
O(n) complexity since every scene is visited once.

TODO 17 - greedyRun. Plays from the root and adds up hp and loot similar to play but does not print scene or handle bag items.
Stops if HP goes to 0. Looks at the next choice, compares the loot of each child and moves to the biggest one. Records
each choice using extendPath and prints the path, loot you got, and result. IE dead or alive.
Runs in O(n) time since it walks down one straight path.

TODO 18 - bestLoot. This function returns -1 if a nullptr is read meaning there is no survival. Adds the scenes hp and if its <= 0, returns -1.
At a ending, sets bestpath to that path. returns the endings loot. Otherwise, it calls itself on each choice set, keeps the higher result of loot.
Returns best loot path plus the scenes loot. O(n) since every scene is visited once.

TODO 19 - optimalRun. Calls best loot with root, start hp, and bestpath once. This searches the entire tree for the most optimal run.
If -1 is returned, prints no path to survive. else it prints the best path with the loot attainable. One call that checks the entire tree, O(n).


## 2. Why exact-size allocation instead of choices_[3]?

Exact size allocation allows us to save memory instead of hard lining at 3 choices. In my story, if it was hard fixed to 3, all the scens would take 72 slots.
But my tree only needs 23 slots, one per choice, so exact size saves 49 slots. Endings hold nullptr in choices because theres no nodes for them to point to which have valid data.


## 3.Scene destructor
Scene destructor deletes the child, slot, then data, if the choices ran first then the child of those choices would have no access back into the tree, so a memory leak would occur. The pointers to the children are stored in the array, so deleting it first means the children can't be reached anymore. For example, deleting my Captain's den would free 7 scenes.

## 4. Greedy vs optimal
Greedy takes the path 2-1-1. gets 14 loot and dies. Optimal takes the path 1-1-1-1-2-2-1, gets 30 loot, and survives.
Greedy loses because it only checks for loot one step ahead, and never checks HP.

## 5. Why bestLoot is O(n), not exponential
In a tree, every ending has exactly one path from the root to it. bestLoot tries each path but does not walk them separately from the root.
At each scene it visits the child of that scene, comes back up and explores the next. This means every scene is visited exactly once and every choice twice.
this gives 2n time, ignoring constants gives O(n).


## 6. List methods my game uses
My version uses search, addFront, size, and print. First, search checks whether the bag has a item in it or not so a dupe is not added.
addFront simply just adds new items to the bag and the list takes ownership. Also why newest first gets printed.
One search costs k time, where k is the amount of items in the bag. In my story the bag never holds more than 3 items, so each search stays quick.