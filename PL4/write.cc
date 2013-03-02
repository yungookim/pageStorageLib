#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include "leveldb/db.h"

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "./leveldb_dir", &db);
    assert(status.ok());

    leveldb::WriteOptions woptions;
    leveldb::Slice s = "hello";
    leveldb::Slice t = "World";

    printf("Writing <hello, world>\n");
    db->Put(woptions, s, t);

    delete db;
}
