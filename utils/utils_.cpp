#include <iostream>
#include <fstream>
#include <unistd.h>

#include "utils_.h"

bool get_arguments(int argc, char** argv, Argument* args) {
  int opt;

  while((opt = getopt(argc, argv, ":ho:f:si:l:")) != -1) {
    switch(opt) { 
      case 'h':
        args->help = true;
        break;
      case 'o':
        args->output = optarg;
        break;
      case 'f':
        args->input = optarg;
        break;
      case 's':
        args->solution = true;
        break;
      case 'i':
        args->initial = atoi(optarg);
        break;
      case 'l':
        args->final = atoi(optarg);
        break;
      case ':':
        return false;
        break;
      case '?':
        return false;
        break;
    }
  }

  return true;
}

void help_arguments(string top_text, bool solution) {
  cout << top_text << endl << endl;
  cout << "-h        : show help" << endl;
  cout << "-o <file> : redirect the output to the 'file'" << endl;
  cout << "-f <file> : indicates the 'file' that contains the input graph" << endl;
  if (solution) cout << "-s        : shows the solution (in ascending order)" << endl;
  cout << "-i        : start vertex" << endl;
}