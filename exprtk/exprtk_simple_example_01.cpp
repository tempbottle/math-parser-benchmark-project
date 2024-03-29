/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Simple Example 1                                           *
 * Author: Arash Partow (1999-2015)                           *
 * URL: http://www.partow.net/programming/exprtk/index.html   *
 *                                                            *
 * Copyright notice:                                          *
 * Free use of the Mathematical Expression Toolkit Library is *
 * permitted under the guidelines and in accordance with the  *
 * most current version of the Common Public License.         *
 * http://www.opensource.org/licenses/cpl1.0.php              *
 *                                                            *
 **************************************************************
*/


#include <cstdio>
#include <string>
#include "exprtk.hpp"


template <typename T>
void trig_function()
{
   std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";
   T x;
   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",x);
   symbol_table.add_constants();

   exprtk::expression<T> expression;
   expression.register_symbol_table(symbol_table);

   exprtk::parser<T> parser;
   parser.compile(expression_string,expression);

   for (x = T(-5); x <= T(+5); x += T(0.001))
   {
      T y = expression.value();
      printf("%19.15f\t%19.15f\n",x,y);
   }
}

int main()
{
   trig_function<double>();
   return 0;
}
