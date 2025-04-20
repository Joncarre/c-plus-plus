# EspacioMatic

You are a prestigious videogame designer, and you are now working on a game called EspacioMatic, in which there will be spaceships with different modules (engines, cockpits, shields, lasers, etc.). You will need to implement, at least, the following operations:

- *espacioMatic*: initialize the game system.

- *shipEquipaNave*: given a ship identifier, a module name (a string such as "engine", "cockpit", "laser", etc.) and a level of functionality (an integer >= 1 ), add the module corresponding to that ship with the indicated level. If that ship already had that module, the new level is added to the previous one (this allows repairing ship modules). It does not return anything.

- *shipDestroyShip*: given the identifier of a ship, and a module name, subtract 1 to the level of > 0). Returns true if the module existed and had a positive level before doing the subtraction, or false if it was impossible to subtract that module in that ship (assuming it had a level since the module did not exist or was already at 0.

- *shipsDefective*: returns a list of ship identifiers that have one or more modules completely broken (with a level of 0).

- *shipModules*: given the identifier of a ship, returns a list with the names of the modules it has equipped (whatever level they have), ordered alphabetically.
