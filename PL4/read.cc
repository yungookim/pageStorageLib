#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <iostream>
#include "leveldb/db.h"

using namespace std;

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    leveldb::Status status = leveldb::DB::Open(options, "./leveldb_dir", &db);
    assert(status.ok());

    leveldb::ReadOptions roptions;

    leveldb::Iterator* it = db->NewIterator(roptions);
    printf("Reading database\n");
    for(it->SeekToFirst(); it->Valid(); it->Next()) {
        leveldb::Slice s = it->key();
        leveldb::Slice t = it->value();
        cout << "<" 
             << s.ToString() 
             << ", " 
             << t.ToString() 
             << ">" 
             << endl;
    }

    delete db;
}
