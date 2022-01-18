#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

def usage():
	print "Usage: find_differences.py OLD_FILE NEW_FILE"



def main():
	if len(sys.argv) != 3:
		usage()
		sys.exit()

	file1 = open(sys.argv[1])
	lines1 = set(line.strip() for line in file1)
	file1.close()

	file2 = open(sys.argv[2])
	lines2 = set(line.strip() for line in file2)
	file2.close()

	removed = lines1 - lines2
	print "\n"
	print ">>>> Removed"
	for i in removed:
		print("%s\n" %i)

	added = lines2 - lines1
	print "\n"
	print ">>>> Added"
	for i in added:
		print("%s\n" %i)



if __name__ == '__main__':
	main()