#!/usr/bin/bash

echo "Welcome to installation wizard for installing Re-ToDo2.1 Test Version 2.1.1"

read -p "Do you want to continue the installation? (y/n):" confirm && [[ $confirm ==[yY] || $confirm == [yY][eE][sS] ]] || exit 1;

# Setup Location
LOCATION="$(pwd)/data"
DATEANDTIME="Date and Time $(date '+%H:%M:%S %d/%m/%Y')";
echo "$DATEANDTIME"

# Make sure to also change the location in C Program source code and then compile it.

if [ -d "$LOCATION" ]; then
    echo "\"data/\" Directory exist."
    echo "Checking for the subsequent files."

    if [[ -f "$LOCATION/logs.txt" && -f "$LOCATION/list.txt" ]]; then
        echo "All subsequent files exist."
    else
        echo "Data files Doesn't exist. Creating New Files."

        echo "Re-ToDo2.1 Test Version 2.1.1 - $DATEANDTIME - LOGS FIlES" >> $LOCATION/logs.txt;
        echo "Re-ToDo2.1 Test Version 2.1.1 - $DATEANDTIME - LIST" >> $LOCATION/list.txt;

        echo "Subsequent Files Created."
    fi
else 
    echo "\"data/\" Directory Doesn't exist."
    echo "Creating \"data/\" directory and the subsequent files."

    mkdir "data/";
    
    echo "Re-ToDo2.1 Test Version 2.1.1 - $DATEANDTIME - LOGS FIlES" >> $LOCATION/logs.txt;
    echo "Re-ToDo2.1 Test Version 2.1.1 - $DATEANDTIME - LIST" >> $LOCATION/list.txt;

    echo "All files created."
fi

# Compile c code with gcc
gcc -o re main.c corelib.h -lsqlite3;
echo "Compile C Code - \"gcc -o re main.c corelib.h -lsqlite3\"";
echo "Setup Complete.";
echo "Use ./re init [DATABASE NAME] to initialize the database.";
echo "use \"-h\" for more information.";

echo "[$DATEANDTIME]: INITIAL SETUP COMPLETE. IN [$LOCATION]." >> $LOCATION/logs.txt;

exit 0;