#include "database.h"

#include <iostream>
#include <string>

#define INITIAL_SIZE 16

Entry *create(Type type, std::string key, void *value) {
    Entry *entry = new Entry();
    entry->type = type;
    entry->key = key;
    entry->value = value;
    return entry;
}

void init(Database &database) {
    database.currentSize = 0;
    database.maxSize = INITIAL_SIZE;
    database.entries = new Entry*[database.maxSize];
}

void add(Database &database, Entry *entry) {
    if (database.currentSize >= database.maxSize) {
        database.maxSize *= 2;
        Entry **newEntry = new Entry*[database.maxSize];
        for (int entryIndex = 0; entryIndex < database.currentSize; entryIndex++) {
            newEntry[entryIndex] = database.entries[entryIndex];
        }
        delete[] database.entries;
        database.entries = newEntry;
    }
    database.entries[database.currentSize] = entry;
    database.currentSize ++;
}

Entry *get(Database &database, std::string &key) {
    for (int entryIndex = 0; entryIndex < database.currentSize; entryIndex++) {
        if (database.entries[entryIndex]->key.compare(key) == 0) {
            return database.entries[entryIndex];
        }
    }
    return NULL;
}

void remove(Database &database, std::string &key) {
    for (int entryIndex = 0; entryIndex < database.currentSize; entryIndex++) {
        if (database.entries[entryIndex]->key.compare(key) == 0) {
            deleteEntry(database.entries[entryIndex]);
            while(entryIndex < database.currentSize - 1) {
                database.entries[entryIndex] = database.entries[entryIndex + 1];
                entryIndex ++;
            }
            database.currentSize --;
            return;
        }
    }
}

void destroy(Database &database) {
    for (int entryIndex = 0; entryIndex < database.currentSize; entryIndex++) {
        deleteEntry(database.entries[entryIndex]);
    }
    delete[] database.entries;
}

std::string getKey() {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;
    return key;
}

void deleteArray(Array *array) {
    switch (array->type) {
        case INT:
            delete[] static_cast<int *>(array->items);
            break;
        case DOUBLE:
            delete[] static_cast<double *>(array->items);
            break;
        case STRING:
            delete[] static_cast<std::string *>(array->items);
            break;
        case ARRAY:
            deleteArray(static_cast<Array *>(array->items));
            delete[] static_cast<Array *>(array->items);
            break;
    }
}

void deleteVoidPointer(Type type, void* value) {
    switch(type) {
        case INT:
            delete static_cast<int *>(value);
            break;
        case DOUBLE:
            delete static_cast<double *>(value);
            break;
        case STRING:
            delete static_cast<std::string *>(value);
            break;
        case ARRAY:
            Array* array = static_cast<Array*>(value);
            deleteArray(array);
            delete array;
            break;
    }
}

void deleteEntry(Entry *entry) {
    deleteVoidPointer(entry->type, entry->value);
    delete entry;
}

Type getType() {
    std::string typeString;
    std::cout << "type (int, double, string, array): ";
    std::cin >> typeString;

    if (typeString.compare("int") == 0) return INT;
    else if (typeString.compare("double") == 0) return DOUBLE;
    else if (typeString.compare("string") == 0) return STRING;
    else return ARRAY;
}


void printValue(Type type, void* value) {
    if (type == INT) {
        std::cout << *(static_cast<int*>(value));
    } else if (type == DOUBLE) {
        std::cout << std::to_string(*(static_cast<double*>(value)));
    } else if (type == STRING) {
        std::cout << "\"" << *(static_cast<std::string*>(value)) << "\"";
    } 
}

// template <typename T>
// void printV(Type type, T value) {
//     for(int arrayIndex = 0; arrayIndex < array->size -1; arrayIndex++) {
//         printValue(type, &(static_cast<T*>(array->items)[arrayIndex]));
//         std::cout << ", ";
//     }
//     printValue(array->type, &(static_cast<T*>(array->items)[array->size - 1]));
// }

void arrayPrint(Array* array) {
    std::cout << "[";
    if (array->type == ARRAY) {
        for(int arrayIndex = 0; arrayIndex < array->size - 1; arrayIndex++) {
            arrayPrint(&(static_cast<Array*>(array->items)[arrayIndex]));
            std::cout << ", ";
        }
        arrayPrint(&(static_cast<Array*>(array->items)[array->size - 1]));
    } else if (array->type == INT) {
        for(int arrayIndex = 0; arrayIndex < array->size -1; arrayIndex++) {
            printValue(array->type, &(static_cast<int*>(array->items)[arrayIndex]));
            std::cout << ", ";
        }
        printValue(array->type, &(static_cast<int*>(array->items)[array->size - 1]));
    } else if (array->type == DOUBLE) {
        for(int arrayIndex = 0; arrayIndex < array->size -1; arrayIndex++) {
            printValue(array->type, &(static_cast<double*>(array->items)[arrayIndex]));
            std::cout << ", ";
        }
        printValue(array->type, &(static_cast<double*>(array->items)[array->size - 1]));
    } else if (array->type == STRING) {
        for(int arrayIndex = 0; arrayIndex < array->size -1; arrayIndex++) {
            printValue(array->type, &(static_cast<std::string*>(array->items)[arrayIndex]));
            std::cout << ", ";
        }
        printValue(array->type, &(static_cast<std::string*>(array->items)[array->size - 1]));
    }

    std::cout << "]";
}

Array* createArray() {
    Array* array = new Array();
    array->type = getType();
    std::cout << "size: ";
    std::cin >> array->size;

    if (array->type == INT) {
        int* items = new int[array->size];
        for (int itemIndex = 0; itemIndex < array->size; itemIndex++) {
            std::cout << "item[" << itemIndex << "]: ";
            int* value = static_cast<int*>(getTypeValueAddress(array->type));
            items[itemIndex] = *value;
            delete value;
        }
        array->items = items;
    } else if (array->type == DOUBLE) {
        double* items = new double[array->size];
        for (int itemIndex = 0; itemIndex < array->size; itemIndex++) {
            std::cout << "item[" << itemIndex << "]: ";
            double* value = static_cast<double*>(getTypeValueAddress(array->type));
            items[itemIndex] = *value;
            delete value;
        }
        array->items = items;
    } else if (array->type == STRING) {
        std::string* items = new std::string[array->size];
        for (int itemIndex = 0; itemIndex < array->size; itemIndex++) {
            std::cout << "item[" << itemIndex << "]: ";
            std::string* value = static_cast<std::string*>(getTypeValueAddress(array->type));
            items[itemIndex] = *value;
            delete value;
        }
        array->items = items;
    } else if (array->type == ARRAY) {
        Array* items = new Array[array->size];
        for (int itemIndex = 0; itemIndex < array->size; itemIndex++) {
            std::cout << "item[" << itemIndex << "]: ";
            Array* value = static_cast<Array*>(getTypeValueAddress(array->type));
            items[itemIndex] = *value;
            delete value;
        }
        array->items = items;
    }

    return array;
}

void* getTypeValueAddress(Type type) {
    std::cout << "value: ";
    void* result;
    if (type == INT) { 
        result = new int;
        std::cin >> *(static_cast<int*>(result));
    } else if (type == DOUBLE) {
        result = new double;
        std::cin >> *(static_cast<double*>(result));
    } else if (type == STRING) {
        result = new std::string;
        std::cin.ignore();
        std::getline(std::cin, *(static_cast<std::string*>(result)));
    } else if (type == ARRAY) {
        result = createArray();
    } else {
        std::cout << "Invalid Value" << std::endl;
        return NULL;
    }
    return result;
}

void printEntry(Entry* entry) {
    std::cout << entry->key << ": ";
    if (entry->type == ARRAY) {
        arrayPrint(static_cast<Array*>(entry->value));
    } else {
        printValue(entry->type, entry->value);
    }
}
