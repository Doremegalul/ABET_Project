/********************************
The following mySwap works like the swap function in the library.

Your name: Minh Tran
Your programmer number: 37
Hours spent: Less than 1 hours
Any difficulties?: 1/10  
********************************/

/*
This void function is to swap two data

T& is the template to use any data like int or character
*/
template <class T>
void mySwap(T& a, T& b)
{
  T temp = a; //Temporary holder
  a = b;
  b = temp;
}

/*
???? mySwapI(?????)
{

}
*/
