#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "leveldb/db.h"
using namespace std;

int main(int argc, const char* argv[]) {
	if (argc != 3) {
		printf( "Must put <csv_file> <db_name>\n");
		return 0;
	}
	const char* csv_file = argv[1];
	char* db_name = (char*)argv[2];

	// Initialize LevelDB
	leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, db_name, &db);
  assert(status.ok());

  leveldb::WriteOptions woptions;

	// Open the csv file
	std::ifstream data(csv_file);
	std::string line;

	while(std::getline(data,line)) {
		std::stringstream lineStream(line);
		std::string cell;

		int i = 0;
		leveldb::Slice key;
		leveldb::Slice value;

		while(std::getline(lineStream,cell,',')) {
			char* attribute = (char *)malloc(sizeof(cell.c_str()));
			strcpy(attribute, cell.c_str());
			// Need to decide on how we are going to store the csv file
			// in KV setting
			if (i == 0){
				key = attribute;
			} else if (i == 1){
				value = attribute;
			}
			i++;
		}
		db->Put(woptions, key, value);
	}

	delete db;
	return 0;
}
