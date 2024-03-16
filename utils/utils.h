#ifndef UTILS_H
#define UTILS_H
using namespace std;

/*!
 * @typedef     Argument
 *              Arguments used during execution.
 * @field       help        Show help info.
 * @field       output      Pointer to data output.
 * @field       input       Pointer to data entry.
 * @field       solution    Show solution.
 * @field       initial     Initial vertex.
 * @field       final       Final vertex.
*/
struct Argument {
  bool help = false;
  ostream* output = &cout;
  istream* input = &cin;
  bool solution = false;
  int initial = -1;
  int final = -1;
};

/*!
 * @function    get_arguments
 * @abstract    Get arguments from terminal.
 * @param       argc    Quantity of arguments.
 * @param       argv    Array of arguments.
 * @param       args    Pointer to the Argument struct.
 * @result      Success confirmation.
*/
bool get_arguments(int argc, char** argv, Argument* args);

/*!
 * @function    get_arguments
 * @abstract    Get arguments from terminal.
 * @param       top_text    Algorithm summary.
 * @param       start       Show help for initial vertex argument.
 * @param       end         Show help for final vertex argument.
*/
void help_arguments(string top_text, bool start = true, bool end = true);

#endif