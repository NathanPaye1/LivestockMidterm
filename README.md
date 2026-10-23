# LivestockMidterm
Midterm using algorithms and data structures
The Purpose of this app is to assist in tracking the animals and medical history of creatures on a farm
It uses the terminal and a mix of number and text input to navigate the menu and enter animal info.
Has full crud functionallity for both animals and medical visits.
The map uses int ID as the key and a custom struct Animal. Animals are made of names, ages, and species.
The other major container is the vector of a second custom object called a Medical Visit. This includes a
date, Animal and a breif description of the medical visit. Vecotr is appropriate because I didn't feel
the medical visits needed an ID per say just a date. Then there could be a day where more than one animal
is treated. That combined with the variable length of the vecotr led me to that decision. 

I used many for_each loops to go through my map and vector. It is just a convenient way to do it.
I also used the sort with a lambda that I should've turned into it's own function becuase I used it like
3 times, but I got sick of adding new functions to my header file. so i didn't. It takes the medical 
visits by reference and sorts them by date then animal name.
