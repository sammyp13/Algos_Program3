#include <iostream>
#include <vector>
#include "BigThree.h"

BigThreeDigit::BigThreeDigit() // initialize to 0
	{
	  c = 0;
	}

    // initialize the digit, return error if the integer value is not between 0 and 2
BigThreeDigit::BigThreeDigit(int x) 
        {
          c = x;
          if ((c < 0) || (c > 2))
		{
		   cerr << "Error, digit out of range\n";
		   exit(0);
		}
        }

    // initialize the digit, return error if the character is not '0', '1', '2'
BigThreeDigit::BigThreeDigit(char x) 
        {
          c = x - '0';
          if ((c < 0) || (c > 2))
		{
		   cerr << "Error, digit out of range\n";
		   exit(0);
		}
        }

bool BigThreeDigit::isZero()
    	{
	   return (c == 0);
    	}

// add the current digit with d, return a new digit that store the value, plue whether there is a carry
pair<BigThreeDigit, bool>  BigThreeDigit::add(BigThreeDigit d) 
        {
	   bool carry = false;
	   int x = c + d.c;
	   if (x > 2)
		{
		  x = x - 3;
		  carry = true ;
		}
           BigThreeDigit b(x);
           return(make_pair(b, carry));
        }

// increment digit by one, return a new digit that store the value, plue whether there is a carry
pair<BigThreeDigit, bool>  BigThreeDigit::incr() 
        {
	   bool carry = false;
	   int x = c + 1; 
	   if (x > 2)
		{
		  x = x - 3;
		  carry = true ;
		}
           BigThreeDigit b(x);
           return(make_pair(b, carry));
        }

// subtract d from the current digit, return a new digit that store the value, plue whether there is a borrow necessary
pair<BigThreeDigit, bool>  BigThreeDigit::sub(BigThreeDigit d) 
        {
	   bool borrow = false;
	   int x = c - d.c;
	   if (x < 0)
		{
		  x = x + 3;
		  borrow = true ;
		}
           BigThreeDigit b(x);
           return(make_pair(b, borrow));
        }

// decrement digit by one, return a new digit that store the value, plue whether there is a borrow necessary
pair<BigThreeDigit, bool>  BigThreeDigit::decr() 
        {
	   bool borrow = false;
	   int x = c - 1; 
	   if (x < 0)
		{
		  x = x + 3;
		  borrow = true ;
		}
           BigThreeDigit b(x);
           return(make_pair(b, borrow));
        }

    // multiply the current digit with d, return a new digit that store the value, plue whether there is a carry
pair<BigThreeDigit, bool>  BigThreeDigit::multiply(BigThreeDigit d) 
        {
	   bool carry = false;
	   int x = c * d.c;
	   if (x > 2)
		{
		  x = x - 3;
		  carry = true ;
		}
           BigThreeDigit b(x);
           return(make_pair(b, carry));
        }




BigThree::BigThree() 
   {
     BigThreeDigit b(0);
     s.push_back(b);
   }

   // Convert a string into the number
   // Notice that the number is represented in the string in normal order
   // e.g. the number 10 should be represented as the string as "10"
   //      but will be stored in the vector as 0-1
 
BigThree::BigThree(string t)
   {
      for (int i = t.length() - 1; i >= 0; i--)
	{
	   BigThreeDigit b(t[i]);
	   s.push_back(b);
	}
   }

   // copy constructor
BigThree::BigThree(const BigThree& bt)
   {
      s = bt.s;
   }

   // assignement of bt to the current number. 
BigThree& BigThree::operator=(BigThree &bt)
   {
      s = bt.s;
      return *this;
   }

   // add the numebr bt to the current number, return a new number (current number not modified)
BigThree BigThree::operator+(BigThree& bt)
   {
      // res is storing the solution
      BigThree res;

      // notice that the number is always initialied with a '0' digit. So we want to remove it to make the algorithm run smomother.
      res.s.pop_back();

      // s1 = length of the smaller numebr (e.. "11012", "212111", the shorter length is 5)
      int s1 = (s.size() <= bt.s.size() ? s.size() : bt.s.size());

      bool carry = false;
      pair<BigThreeDigit, bool> b0;


      //adding digits present in both number 
      for (int i = 0; i < s1; i++)
	{
           bool nextcarry = false;

	   // adding the digit, check if there is a carry necessary
           b0 = s[i].add(bt.s[i]);
           nextcarry = b0.second;
           
           // if there is a carry from the previous digit, then add 1 to the sum 
           if (carry)
		{
                   b0 = b0.first.incr();
                   res.s.push_back(b0.first);
		}
	   else
		{
                   res.s.push_back(b0.first);
		}

           // check if there is a carry forward to the next digit
           carry = nextcarry || b0.second;
	}

     // if the two numbers are of different length, we add back the digits of the larger number
     if (s1 < s.size())
	{
           for (int j = s1; j < s.size(); j++)
		{
		   if (carry)
			{
			   b0 = s[j].incr();
			   res.s.push_back(b0.first);
                           carry = b0.second;
			}
		   else
			{
			   res.s.push_back(s[j]);
			}

		}
	}
     else if (s1 < bt.s.size())
	{
           for (int j = s1; j < bt.s.size(); j++)
		{
		   if (carry)
			{
			   b0 = bt.s[j].incr();
			   res.s.push_back(b0.first);
                           carry = b0.second;
			}
		   else
			{
			   res.s.push_back(bt.s[j]);
			}

		}
	}

      // there may be one more carry at the end, if so, add a 1 to the front
      if (carry)
	{
	   BigThreeDigit one(1);
	   res.s.push_back(one);

	}
     return res;
   }

   // subtract the number bt to the current number, return a new number (current number not modified)
   // notice that it assume bt is smaller than the number
   // otherwise it will return an error and quit
BigThree BigThree::operator-(BigThree& bt)
   {

     if (bt.s.size() > s.size())
	{
	   cerr << "Error (1), parameter is larger than the number itself, can't subtract\n";
	   exit(0);
	}

      // res is storing the solution
      BigThree res;

      // notice that the number is always initialied with a '0' digit. So we want to remove it to make the algorithm run smomother.
      res.s.pop_back();

      bool borrow = false;
      pair<BigThreeDigit, bool> b0;


      //adding digits present in both number 
      for (int i = 0; i < bt.s.size() ; i++)
	{
           bool nextborrow = false;

	   // adding the digit, check if there is a borrow necessary
           b0 = s[i].sub(bt.s[i]);
           nextborrow = b0.second;
           
           // if there is a borrow from the previous digit, then sub 1 to the sum 
           if (borrow)
		{
                   b0 = b0.first.decr();
                   res.s.push_back(b0.first);
		}
	   else
		{
                   res.s.push_back(b0.first);
		}

           // check if there is a borrow forward to the next digit
           borrow = nextborrow || b0.second;
	}

     // take the extra digit of the number, need to consider the borrow
     if (bt.s.size() < s.size())
	{
           for (int j = bt.s.size(); j < s.size(); j++)
		{
		   if (borrow)
			{
			   b0 = s[j].decr();
			   res.s.push_back(b0.first);
                           borrow = b0.second;
			}
		   else
			{
			   res.s.push_back(s[j]);
			}

		}

	}

     // if there is still borrow, that means the number is smaller than bt
     if (borrow)
	{
	   cerr << "Error (2), parameter is larger than the number itself, can't subtract\n";
	   exit(0);
	}
     res.RemoveFrontZeros();
     return res;

   }

   // remove the zeros at the front of the number (in this case at the end of the error
   // for example: 00121 becomes 121
void BigThree::RemoveFrontZeros()
	{
          bool done = false;
          while (!done && (s.size() > 1))
		{
		   if (s.rbegin()->isZero())
			s.pop_back();
		   else
			done = true;
		}
	  

	}

   // Add n zeros to the right of the number
   // e.g. if number is 1010, then AddZero(3) will change the number to 1010000
   void BigThree::AddZeros(int n)
	{
	   BigThreeDigit b;
 	   int cursize = s.size();
           for (int i = n; i >= 1; i--)
		    s.push_back(s[cursize - i]); 
	   for (int i = cursize - 1; i >=  n; i--)
		    s[i] = s[i-n];
	   for (int i = n - 1; i >= 0; i--)
		    s[i] = b;
		
	}

   // add the numebr bt to the current number, return a new number (current number not modified)
BigThree BigThree::operator*(BigThreeDigit& d)
{
      // res is storing the solution
      BigThree res;
      if (d.isZero())
	  return res;

      // notice that the number is always initialied with a '0' digit. So we want to remove it to make the algorithm run smomother.
      res.s.pop_back();

      bool carry = false;
      pair<BigThreeDigit, bool> b0;

      //adding digits present in both number 
      for (int i = 0; i < s.size(); i++)
	{
           bool nextcarry = false;

	   // adding the digit, check if there is a carry necessary
           b0 = s[i].multiply(d);
           nextcarry = b0.second;
           
           // if there is a carry from the previous digit, then add 1 to the sum 
           if (carry)
		{
                   b0 = b0.first.incr();
                   res.s.push_back(b0.first);
		}
	   else
		{
                   res.s.push_back(b0.first);
		}

           // check if there is a carry forward to the next digit
           carry = nextcarry || b0.second;
	}


      // there may be one more carry at the end, if so, add a 1 to the front
      if (carry)
	{
	   BigThreeDigit one(1);
	   res.s.push_back(one);

	}
     return res;
   }

// split the number into two, one with the rightmost d digits, the other one with the rest
// return error if the total number of digits of the number is less then or equal to d
pair<BigThree, BigThree> BigThree::split(int d)
{
   if ((s.size() < d) || (d <= 0))
	{
	   cerr << "Invalid parameter for d\n";
	   exit(0);
	}

  BigThree left_d, right_d;
  left_d.s.pop_back();
  right_d.s.pop_back();
 
  for (int i = d; i < s.size(); i++)
	{
	   left_d.s.push_back(s[i]);
	}

  for (int i = 0; i < d; i++)
	{
	   right_d.s.push_back(s[i]);
	}

  left_d.RemoveFrontZeros();
  right_d.RemoveFrontZeros();
  return make_pair(left_d, right_d);

}


ostream& operator<<(ostream& os, BigThreeDigit& t)
{
   os << t.c;
   return os;
}

ostream& operator<<(ostream& os, BigThree& t)
{
   for (int i = t.s.size() - 1; i >= 0; i--)
	os << t.s[i];
   return os;
}
