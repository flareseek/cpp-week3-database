#ifndef DATABASE_H
#define DATABASE_H

#include <string>

#define INT_STRING "int"
#define DOUBLE_STRING "double"
#define STRING_STRING "string"
#define ARRAY_STRING "array"
#define EXIT_STRING "exit"

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  int currentSize;
  int maxSize;
  Entry **entries;
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value);

// 데이터베이스를 초기화한다.
void init(Database &database);

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);

// ---------------------------------------------
// key값을 받아옵니다.
std::string getKey();

// type값을 받아옵니다.
Type getType();

// 타입에 맞게 데이터를 받고 그 주소를 반환합니다.
void* getTypeValueAddress(Type type);

// 배열을 삭제합니다.
void deleteArray(Array *array);

// void 포인터를 해제합니다.
void deleteVoidPointer(Type type, void* value);

// entry를 해제합니다.
void deleteEntry(Entry *entry);

// 타입에 맞게 값을 출력합니다.
void printValue(Type type, void* value);

// 배열을 출력합니다.
void arrayPrint(Array* array);

// 배열을 생성합니다.
Array* createArray();

// entry를 출력합니다.
void printEntry(Entry* entry);
#endif
