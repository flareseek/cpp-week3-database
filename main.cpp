#include "database.h"

#include <iostream>
#include <string>

void addEvent(Database &database) {
    std::string key = getKey();
    Type type = getType();

    void* value = getTypeValueAddress(type);
    if (value == NULL) {
        std::cout << "Invalid value" << std::endl;
        return;
    }

    Entry* entry = get(database, key);
    if (entry == NULL) {
        entry = create(type, key, value);
        add(database, entry);
    } else {
        entry->type = type;
        entry->value = value;
    }
}

void getEvent(Database &database) {
    std::string key = getKey();
    Entry* entry = get(database, key);

    if (entry == NULL) {
        std::cout << "Invalid key" << std::endl;
        return;
    }
    printEntry(entry);
    std::cout << std::endl;
}

void listEvent(Database &database) {
    for(int entryIndex = 0; entryIndex < database.currentSize; entryIndex++) {
        Entry *entry = database.entries[entryIndex];
        printEntry(entry);
        std::cout << std::endl;
    }
}

void deleteEvent(Database &database) {
    std::string key = getKey();
    remove(database, key);
}

void exitEvent(Database &database) {
    destroy(database);
    exit(0);
}

void commandController(Database &database) {
    std::string cmd;
    std::cout << "command (list, add, get, del, exit): ";
    std::cin >> cmd;

    if (cmd.compare("list") == 0) {
        listEvent(database);
    } else if (cmd.compare("add") == 0) {
        addEvent(database);
    } else if (cmd.compare("get") == 0) {
        getEvent(database);
    } else if (cmd.compare("del") == 0) {
        deleteEvent(database);
    } else if (cmd.compare("exit") == 0) {
        exitEvent(database);
    }
    std::cout << std::endl;
}

int main() {
    Database database;
    init(database);
    while (true) {
        commandController(database);
    }
    return 0;
}
