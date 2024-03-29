/*
 **************************************************************
 *         C++ Mathematical Expression Toolkit Library        *
 *                                                            *
 * Simple Example 3                                           *
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
void polynomial()
{
   std::string expression_string = "25x^5 - 35x^4 - 15x^3 + 40x^2 - 15x + 1";

   T r0 = T(0);
   T r1 = T(1);
   T  x = T(0);

   exprtk::symbol_table<T> symbol_table;
   symbol_table.add_variable("x",x);

   exprtk::expression<T> expression;
   expression.register_symbol_table(symbol_table);

   exprtk::parser<T> parser;
   parser.compile(expression_string,expression);

   const T delta = T(1.0 / 100.0);

   for (x = r0; x <= r1; x += delta)
   {
      printf("%19.15f\t%19.15f\n",x,expression.value());
   }
}

int main()
{
   polynomial<double>();
   return 0;
}
