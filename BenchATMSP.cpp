#include "BenchATMSP.h"

//#include <windows.h>
#include <cmath>

// atmsp
#include "atmsp/atmsp.h"


//-------------------------------------------------------------------------------------------------
BenchATMSP::BenchATMSP()
: Benchmark()
{
   m_sName = "atmsp 1.0.4";
}

//-------------------------------------------------------------------------------------------------
std::string BenchATMSP::replaceAll(std::string result,
                                   const std::string& replaceWhat,
                                   const std::string& replaceWithWhat)
{
   int start = 0;
   while(1)
   {
      int pos = result.find(replaceWhat, start);

      if (pos==-1)
         break;

      result.replace(pos,replaceWhat.size(),replaceWithWhat);
      start = pos + replaceWithWhat.length();
   }
   return result;
}

//-------------------------------------------------------------------------------------------------
void BenchATMSP::PreprocessExpr(std::vector<std::string>& vExpr)
{
   // atmsp is using $ to mark a constant
   for (std::size_t i = 0; i < vExpr.size(); ++i)
   {
      PreprocessExpr(vExpr[i]);
   }
}

//-------------------------------------------------------------------------------------------------
void BenchATMSP::PreprocessExpr(std::string& s)
{
   s = replaceAll(s, std::string("pi"),  std::string("$pi"));
   s = replaceAll(s, std::string("-e*"), std::string("-$e*"));
   s = replaceAll(s, std::string("/e*"), std::string("/$e*"));
   s = replaceAll(s, std::string("(e*"), std::string("($e*"));
   s = replaceAll(s, std::string("-e/"), std::string("-$e/"));
   s = replaceAll(s, std::string("e^"),  std::string("$e^"));
   s = replaceAll(s, std::string("+e)"), std::string("+$e)"));
   s = replaceAll(s, std::string("(e+"), std::string("($e+"));
   s = replaceAll(s, std::string("(e-"), std::string("($e-"));
   s = replaceAll(s, std::string("(-e"), std::string("(-$e"));
   s = replaceAll(s, std::string("-e)"), std::string("-$e)"));
   s = replaceAll(s, std::string("(e)"), std::string("($e)"));
   s = replaceAll(s, std::string("/e)"), std::string("/$e)"));
   s = replaceAll(s, std::string("/e/"), std::string("/$e/"));
   s = replaceAll(s, std::string("*e+"), std::string("*$e+"));
   s = replaceAll(s, std::string("*e)"), std::string("*$e)"));
   s = replaceAll(s, std::string("/e)"), std::string("/$e)"));
   s = replaceAll(s, std::string("(e/"), std::string("($e/"));
}

//-------------------------------------------------------------------------------------------------
double BenchATMSP::DoBenchmark(const std::string& sExpr, long iCount)
{
   ATMSB<double> bc;

   // Parsing/bytecode generation with error check. In a scope here JUST to
   // demonstrate that a parser-instance itself is NOT needed later on
   ATMSP<double> p;

   unsigned int err = p.parse(bc, sExpr, "a, b, c, x, y, z, w");

   if (err)
   {
      StopTimerAndReport(p.errMessage(err));
   }
   else
   {
      // Set variable values for x,y,z. Here always 1,2,3
      bc.var[0] = 1.1;
      bc.var[1] = 2.2;
      bc.var[2] = 3.3;
      bc.var[3] = 2.123456;
      bc.var[4] = 3.123456;
      bc.var[5] = 4.123456;
      bc.var[6] = 5.123456;

      // Calculate/bench and show result finally
      double fRes (0);
      double fSum (0);

      fRes = bc.run();

      StartTimer();
      for (int j = 0; j < iCount; ++j)
      {
         fSum += bc.run();
         std::swap(bc.var[0], bc.var[1]);
         std::swap(bc.var[3], bc.var[4]);
      }
      StopTimer(fRes, fSum, iCount);
   }
   return m_fTime1;
}
