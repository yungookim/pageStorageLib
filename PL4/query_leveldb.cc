#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "leveldb/db.h"
#include <vector>
using namespace std;

typedef std::vector<string> Record;

int main(int argc, const char* argv[]) {
	if (argc != 4) {
		printf( "Must put <db_name> <start> <end>\n");
		return 0;
	}

	char* db_name = (char*)argv[1];
	char* start_arg = (char*)argv[2];
	char* end_arg = (char*)argv[3];

	// SELECT SUBSTRING(A2, 1, 5), COUNT(*) FROM T
	//  WHERE A1 >= start AND A1 <= end
	//  GROUP BY SUBSTRING(A2, 1, 5) 

	// Initialize LevelDB
	leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, db_name, &db);
  assert(status.ok());

	leveldb::Slice start(start_arg, sizeof(start_arg));
	leveldb::Slice end(end_arg, sizeof(end_arg));

	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

	// Initialize Record
	Record records;
	for (it->Seek(start); it->Valid() && it->key().ToString().compare(end.ToString()) <= -1; it->Next()) {
		// leveldb::Slice key = it->key();
		leveldb::Slice value = it->value();

		// std::string key_str = key.ToString();
		// std::string val_str = value.ToString();
		std:string val = value.ToString().substr(12, 5);

		records.push_back(val);

		// cout << key_str << ": "  << val_str << endl;
		// cout << val << "\n";
	}
	assert(it->status().ok());  // Check for any errors found during the scan

	for (int i = 0; i < records.size(); i++){
		int counter = 1;
		int k = i + 1;
		while (k < records.size()){
			if (records.at(i).compare(records.at(k)) == 0){
				counter++;
				records.erase(records.begin() + k);
			} else {
				k++;
			}
		}

		cout << records.at(i) << " " << counter << "\n";
	}

	delete it;
}