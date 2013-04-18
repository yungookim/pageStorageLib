#!/bin/bash
sqlite3 A.db < A_index.sql
time sqlite3 -separator '   ' A.db < query
rm -f tmp