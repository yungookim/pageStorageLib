#!/bin/bash
sqlite3 A.db < A.sql
time sqlite3 -separator '   ' A.db < query
rm -f tmp