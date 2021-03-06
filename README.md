INTRODUCTION:

"Intal" is a structure which stores very huge numbers in the form of strings terminated by '/0' character.Ex: "1232121111111111111132131231231231232131222222222222223213213123" etc. It is not same as the traditional integer type in c which is limited to handling not so huge numbers whereas intal on the other hand can handle numbers with upto 1000 digits.

The application of intals is very widespread , The main point being it can store very huge numbers so it can also support arithmetic operations on very huge numbers. We can say it is similar to the "BIG INT" class of python.With the help of intals we can model real life scenarious dealing with very huge numbers easily.


APPROACH:

Intal_add:

My algorithm scans the intals from right to left converting the digits(single digit of each) into integer adds them and pushes the carry towards the left.Then finally converts the resultant digit of sum into character and pushes it into the result intal.
sum=(digit1+digit2+carry)%10
carry=(digit1+digit2+carry)/10

Intal_compare:

In this method I first compare the length of the numbers if they are not equal then I can easily judge which is the greater number.If the lengths are equal I iterate over both the intals from right to left and the moment I encounter 2 digits which are unequal I can easily judge which is the greater one.If I dont encounter any digits which are unequal (Lengths being equal) I conclude that they are equal "INTALS".

Intal_diff:

My algorithm first compares the 2 intals if they are the same it returns "0" else I decide the length of my result based on whichever is greater, Then I start scanning from right to left.As i subtract(digit by digit) if my answer is negative I set borrow to 1 and also add 10 to my negative difference to make it positive(This will be strictly a single digit number after adding 10),Borrow is reset to 0 only when The next non negative difference is encountered else this borrow carries on.This logic will work even if the lengths are unequal.

Intal_multiply:

In this function if one of the intals is 0 I just return "0".Otherwise I reverse the numbers and use 2 loops. The outer loop traverses the smaller number the inner loop the larger number.Multiplication is performed digit by digit the product and carry is calculated accordingly.Once the loops finish execution I strip the results from any beginning zeroes and return the result.
product =(digit1 * digit2 + carry) % 10
carry=(digit1 * digit2 + carry) / 10

Intal_pow:

This algorithm is a recursive one. First I store power(a,n/2) lets say "pow" in a variable then I check whether n is odd if it is I return a*pow*pow else I return pow*pow.This works in O(logn).
Intal_multiply is used here to perform multiplication.

Intal_mod:

This algorithm has been implemented on the idea of long division Where we take each didgit of intal1 and if this is greater than intal2 we keep on subtracting intal2 from this till it becomes lesser than intal2 Then we proceed to the next digit of intal1,while doing this we also keep track of the previous result.

Intal_gcd:

This is an implementation of the traditional euclidian algo to find gcd.It is a recursive one, Lets say it is defined as gcd(a,b) base case will be if a==0 return b else we will be returning gcd(b%a,a).We use intal_mod in this function to perform modulus operation on intals.

Intal_fibonacci:

This algo goes like this, lets take a,b,c and intialize a=0 and b=1 Then we run a loop from 1 to n we store the nth fibonacci number in c which is c=(a+b) then we assign a=b and b=c and repeat n steps to get the nth fibonacci number.Intal_add is used in this function.

Intal_factorial:

In this method we iterate from 1 to n and also keep an intal initialized to 0 which keeps track what to multiply and this is added to one after each iteration This is basically the intal version of the counter i , we multiply the prd with this intal version of the counter ensuring intal_multiply gets both parameters as strings.Then we return product.

Intal_bincoeff:

My algorithm makes use of the pascal's identity which is given but also the concept of remembering function calls.This is implemented by taking an array of size (k+1) , The functionality of this is to remember the i-1th row when constructing the ith row of pascal's triangle.The pascal's triangle goes like this:
														
													1     			   C(1,1)
												1	2	1		C(2,0),C(2,1),C(2,2)
											  1	  3   3	  1		C(3,0),C(3,1),C(3,2),C(3,3)		
											1	4	6	4	1   C(4,0),C(4,1),C(4,2),C(4,3),C(4,4)
											.................

Intal_max:

This is implemented by taking an element and intializing to 0 an then comparing each element with this if it is greater we update this element with the latter.

Intal_min:

Similar approach as Intal_max we just compare if there exists a lesser element

Intal_search:

We iterate across the array as soon as we encounter the element equal to the key we store the index of the elemet and break out of the loop.

Intal_binsearch:

This is a classic divide and conquer algo , we follow the same approach as that of binary search (i.e if we find an element greater than mid we comtinue on the right half else left half till mid element is the key).One small modification to find the first occurence of the key We check whether the mid element is the key as well as if it is greater than the previous element to make sure it is the first occurence.

Intal_sort:

We implement the known "Quick sort" algorithm with the help of intal_compare.

Intal_coin_row:

The recursion used here is F(a,n)=max{F(a,n-2)+C[n],F(a,n-1)} , we use a window of size 2 which stores each of the result Then we build the solution in a bottom up fashion.


Helper functions I used:

ts:

This function helped convert integer to character

td:

This function helped convert character to integer

strrev:

Helped reverse a given string

strip:

Helped strip leading zeroes of the result and return it

swap:
 helped swap two intals 

swap_n:

helped swap 2 intals in an array of intals
and I also used a macro max which returns max of 2 integers


FUTURE WORK:

1)Implement divison 
2)Factoring huge numbers
3)Prime factoring huge numbers
4)Implement rsa function which helps in encrypting messages as this is based on factoring huge numbers into primes
5)Implement Pollard Rho's algorithm
6)finding square root of huge numbers 
7)Other potential number theory related algorithms.
