#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "leveldb/db.h"
using namespace std;

int main(int argc, const char* argv[]) {

	if (argc != 3) {
		printf( "Must put <input_file> <out_index>\n");
		return 0;
	}

	char* input_file = (char*)argv[1];
	char* out_index = (char*)argv[2];

	// Initialize LevelDB
	leveldb::DB *db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, out_index, &db);
  assert(status.ok());

  leveldb::WriteOptions woptions;

  // Open the random file
	std::ifstream data(input_file);
	std::string line;

	while(std::getline(data,line)) {
		std::stringstream lineStream(line);
		std::string cell;

		leveldb::Slice key;
		leveldb::Slice value;

		std::getline(lineStream,cell,',');

		db->Put(woptions, cell.c_str(), "");
	}

	delete db;
	return 0;
}