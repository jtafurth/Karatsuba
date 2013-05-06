Karatsuba Multiplicator v1.

Author: Juan Camilo Tafurth Zuñiga

Developed in c++ using Qt(http://qt-project.org/) as GUI.

Size in latest commit: 70,8MB.

Description:

Simple program that performs a multiplication using Karatsuba fast multiplication algorithm. Its supports negative, odd, and diferent sized numbers. Fail-safes for non-number strings and very high integers are implemented. When a fail-safe is in effect the result of the multiplication will be 0.

Usage:

The program does not require installation, its a simple executable link to shared libraries. Any modern machine should be able to run it.

The main inputs of the programs are located in the top part of the main window where you enter the numbers in the first two slots and the result will be displayed in the third.

The console window will output most of the operations performed in order to complete the multiplication. This is a recursive algorithm so it may be a little confusing to read the console but it is explained here in detail.

Pseudo code:

procedure karatsuba(num1, num2)
  if (num1 < 10) or (num2 < 10)
    return num1*num2;

  else
  /*if numbers have different bit size, 0 will be added to equal them*/
  /*if any number is odd, next even digit will be used*/
  n = max(size(num1),size(num2)
  low1, low2 = lower half of num1, num2
  high1, high2 = higher half of num1, num2
  z0 = karatsuba(low1,low2)
  z1 = karatsuba((low1+high1),(low2+high2))
  z2 = karatsuba(high1,high2)
  c1 = pow(2,n)-pow(2,n/2);
  c2 = pow(2,n/2);
  c3 = 1-pow(2,n/2);
  return c1*z2+c2*z1+c3*z0

How to read the console:

Consoles Outputs:

 Get numbers: 1 if the characters in the input boxes are valid and only contain   positive  or negative numbers. 0 otherwise. If 0 program will not compute.

 Thread Started: Starts different thread that computes the iterations.

 Direct Multiplication: Numbers are so small Karatsuba algorithm is not needed, numbers  are multiplicated in the traditional way.

 Karatsuba Iteration Started: Started the iterations method of the two numbers.

 Lower Half: decimal representation of the lower binary half of the number.
 Higher Half: decimal representation of the higher binary half of the number.

If the numbers have 2 or more decimal digits, iteration method will be called, which means z0,z1 and z3 have to be computed, this will start another instance of Karutsaba with a slower number until direct multiplication can be made.

