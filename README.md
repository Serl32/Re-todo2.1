# Re-todo2.1
A Simple Terminal To-Do Program written in C for my Arch Linux with Apache Cassandra.
___
*Edit: 6:31 PM, Saturday, November 25.*

### A Simple To-Do Terminal Program written in C for my Arch Linux with SQLite Database.
Clone the repository and compile the ```main.c```, ```corelib.h```, with sqlite library ```-lsqlite```.
    ```gcc -o ree main.c corelib.h -lsqlite3```

The program is built/written in C. It also has a bash script which could be ran to install/compile the setup easily.
*The bash script isn't edited, and needs some customization to install the program clearnly.*

**Notes:**
    * I had more plans to build this program, more efficient, stability, and more complex. First the program was planed to built with Apache Cassandra Database, without much knowledge on databases I decided to build with Cassandra. As I reasearched more I learned that it would be a bit too much having a huge database, database server for a simple program. So later found out it would be much efficient and compact to use an embedded database, such as SQLITE.
    * TIP: Always make sure or double check when compiling the file with correct file names. I re-compiled the ```main.c``` file without adding the argument for the compiled file name or given the ```main.c``` as the compiled file by mistake and it wiped out my works on ```main.c``` file and filled it with byte codes and special characters. I ended up re-writing the ```main.c``` file again. I didn't have the backups or version control to restore when i was testing.
    * I had so many functionalities to add into this program. I wanted to try and use C as my first official program/project for my official first terminal project.
    * I've also removed some functionalities which was causing bugs and for simplicity.
